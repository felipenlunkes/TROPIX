/*
 ****************************************************************
 *								*
 *			walk.c					*
 *								*
 *	Compara��o remota de �rvores (cliente) 			*
 *								*
 *	Vers�o	2.3.0, de 28.10.91				*
 *		4.2.0, de 02.05.02				*
 *								*
 *	M�dulo: TCMPTO_C/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "../../tnet.h"
#include "../h/tcmpto_c.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry int	ftw_file_cnt = 0;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		file_cp (const char *, STAT *);

/*
 ****************************************************************
 *	Processa os nomes das �rvores (cliente)			*
 ****************************************************************
 */
void
walk (const char *argv[])
{
	/*
	 *	Processa os nomes das <�rvores>
	 */
	if (*argv == NOSTR) 	/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if (fromflag)
			{
				remote_walk (area);
			}
			else
			{
				ftw_file_cnt = 0;

				ftw (area, name_analysis);

#if (0)	/*******************************************************/
	STAT		ls, s;

				if
				(	lstat (area, &ls) >= 0 && S_ISLNK (ls.st_mode) &&
					stat (area, &s) >= 0   && !S_ISDIR (s.st_mode)
				)
				{
					name_analysis (area, &ls, FTW_SL);
				}
				else
				{
					ftw (area, name_analysis);
				}
#endif	/*******************************************************/
			}

			if (sigint_received)
				break;
		}
	}
	else			/* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
		{
			if (fromflag)
			{
				remote_walk (*argv);
			}
			else
			{
				ftw_file_cnt = 0;

				ftw (*argv, name_analysis);
#if (0)	/*******************************************************/
				if
				(	lstat (*argv, &ls) >= 0 && S_ISLNK (ls.st_mode) &&
					stat (*argv, &s) >= 0   && !S_ISDIR (s.st_mode)
				)
				{
					name_analysis (*argv, &ls, FTW_SL);
				}
				else
				{
					ftw (*argv, name_analysis);
				}
#endif	/*******************************************************/
			}

			if (sigint_received)
				break;
		}
	}

	t_snd_msg (-1, NOSTR);		/* EOF */

}	/* end walk */

/*
 ****************************************************************
 *	Caminha a �rvore remotamente 				*
 ****************************************************************
 */
void
remote_walk (const char *tree_nm)
{
	char		*rmsg;
	char		file_nm[BLSZ];
	int		code;

	t_snd_msg (0, tree_nm);

	for (EVER)
	{
		if (t_rcv_msg (&rmsg) < 0)
			break;

		strcpy (file_nm, rmsg);

		if (cpflag)
			code = file_cp (file_nm, (STAT *)NULL);
		else
			code = file_cmp (file_nm, (STAT *)NULL);

		if (code != 0)
			t_snd_msg (-2, NOSTR);	/* Para n�o caminhar a �rvore */
		else
			t_snd_msg (-1, NOSTR);
	}

}	/* end remote_walk */

/*
 ****************************************************************
 *	Analisa o nome de um arquivo				*
 ****************************************************************
 */
int
name_analysis (const char *file_nm, STAT *sp, int status)
{
	char		file_printed = 0;
	int		code;

	/*
	 *	Pr�logo
	 */
	ftw_file_cnt++;

	if (file_nm[0] == '.' && file_nm[1] == '/' && file_nm[2] != '\0')
		file_nm += 2;

	if (status == FTW_DNR)
	{
		print_file_nm (file_nm, sp, ":\n", &file_printed);
		msg ("*N�o consegui ler o diret�rio \"%s\" em \"%s\"", file_nm, local_node_nm);
		diff_files_cnt++;
		return (0);
	}

	if (status == FTW_NS)
		sp = (STAT *)NULL;

	/*
	 *	Crit�rios para aceitar (ou n�o) o arquivo
	 */
	if (status == FTW_D)
	{
		if (ftw_file_cnt > 1)
		{
			if (!dotflag)
			{
				if (patmatch (file_nm, ".!.*") || patmatch (file_nm, "*/.!.*"))
					return (1);
			}

			if (Lflag)
				return (1);
		}
	}
	else
	{
		if (gflag && streq (file_nm, garfield))
			return (0);

		if (!pattern_accept (file_nm))
			return (0);
	}

	/*
	 *	Envia o nome do arquivo e compara-o
	 */
	t_snd_msg (0, file_nm);

	if (cpflag)
		code = file_cp (file_nm, sp);
	else
		code = file_cmp (file_nm, sp);

	t_snd_msg (-1, NOSTR);

	return (code);

}	/* end name_analysis */

/*
 ****************************************************************
 *	Copia j� um arquivo					*
 ****************************************************************
 */
int
file_cp (const char *file_nm, STAT *lsp)
{
	char		*local_link_nm;
	STAT		local_s;
	char		*rmsg;
	char		file_printed = 0;

	/*
	 *	Verifica se � interativo
	 */
	if (iflag)
	{
		print_file_nm (file_nm, lsp, "? (n): ", &file_printed);

		if (askyesno () <= 0)
		{
			t_snd_msg_no_push (F_PASS, NOSTR);

			if (!fromflag && lsp != (STAT *)NULL && S_ISDIR (lsp->st_mode))
				return (1);
			else
				return (0);
		}
	}
	else 	/* n�o interativo */
	{
		print_file_nm (file_nm, lsp, ":\n", &file_printed);
	}

	/*
	 *	Processa a c�pia
	 */
	if (fromflag)
	{
		t_snd_msg (F_PROCESS, NOSTR);

		switch (t_rcv_msg (&rmsg))
		{
		    case CPFROM:
			copy_from (file_nm);
			break;

		    case L_LINK:
			link_local_file (file_nm, rmsg);
			break;

		    default:
			error ("$Esperava um CPFROM ou L_LINK");

		}	/* end switch */
	}
	else
	{
		/*
		 *	Obtem o estado local
		 */
		if (lsp == (STAT *)NULL  &&  lstat (file_nm, &local_s) >= 0)
			lsp = &local_s;
	
		/*
		 *	Obt�m o nome do LINK local (se houver)
		 */
		if (lsp != (STAT *)NULL)
			local_link_nm = local_link_proc (file_nm, lsp);
		else
			local_link_nm = NOSTR;

		if (local_link_nm == NOSTR)
			copy_to (file_nm);
		else
			link_remote_file (file_nm, local_link_nm);
	}

	return (0);

}	/* end file_cp */
