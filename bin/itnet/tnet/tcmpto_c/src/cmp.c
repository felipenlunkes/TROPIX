/*
 ****************************************************************
 *								*
 *			cmp.c					*
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
#include <unistd.h>
#include <fcntl.h>
#include <a.out.h>
#include <xti.h>

#include "../../tnet.h"
#include "../h/tcmpto_c.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry int	crc_diff;		/* Contador de CRCs diferentes */

/*
 ******	Prot�tipos **********************************************
 */
int		regular_file_cmp (const char *, STAT *, STAT *, HEADER *);
int		no_regular_file_cmp (const char *, STAT *, STAT *);

/*
 ****************************************************************
 *	Compara um Arquivo					*
 ****************************************************************
 */
int
file_cmp (const char *file_nm, STAT *lsp)
{
	STAT		local_s, remote_s;
	STAT		*rsp = (STAT *)NULL;
	char		*rmsg;
	char		*local_link_nm = NOSTR;
	char		remote_link_nm[BLSZ];
	char		file_printed = 0;
	HEADER		h, *hp = &h;

	/*
	 *	Retorna:
	 *		 0 se deve continuar a caminhada em uma �rvore
	 *		 1 se N�O deve continuar a caminhada em uma �rvore
	 */

	/*
	 *	Obtem o estado local
	 */
	if (lsp == (STAT *)NULL  &&  lstat (file_nm, &local_s) >= 0)
		lsp = &local_s;

	/*
	 *	Verifica se o arquivo existe no n� local
	 *	e obt�m o nome do elo f�sico local (se houver)
	 */
	if (lsp != (STAT *)NULL)
	{
		local_link_nm = local_link_proc (file_nm, lsp);
	}
	else
	{
		print_file_nm (file_nm, lsp, ":\n", &file_printed);
		msg ("*N�o consegui obter o estado do arquivo em \"%s\"", local_node_nm);
	}

	/*
	 *	Verifica se o arquivo existe no n� remoto
	 */
	if (t_rcv_msg (&rmsg) < 0)
	{
		print_file_nm (file_nm, lsp, ":\n", &file_printed);
		msg ("N�o consegui obter o estado do arquivo em \"%s\" (%s)", remote_node_nm, rmsg);

		diff_files_cnt++;

		if (lsp == (STAT *)NULL)
			return (0);

		if (!fromflag && local_link_nm != NOSTR)
		{
			msg
			(	"O arquivo deveria ser um elo f�sico a \"%s\" em \"%s\"",
				local_link_nm, remote_node_nm
			);

			return (save_op_info (file_nm, lsp, rsp, R_LINK, local_link_nm));
		}
		else
		{
			return (save_op_info (file_nm, lsp, rsp, CPTO));
		}
	}

	/*
	 *	Recebe o estado remoto
	 */
	if (t_rcv (tcp_fd, rsp = &remote_s, sizeof (STAT), (int *)NULL) < 0)
		error (NOSTR);

#ifdef	LITTLE_ENDIAN
	stat_endian_cv (rsp, rsp);
#endif	LITTLE_ENDIAN

	/*
	 *	Recebe o nome do elo f�sico remoto (se houver)
	 */
	if (t_rcv_msg (&rmsg) > 0)
		strcpy (remote_link_nm, rmsg);
	else
		remote_link_nm[0] = '\0';

	/*
	 *	Verifica se deve receber o cabe�alho de um m�dulo objeto
	 */
	if (qflag)
	{
		if (t_rcv_msg (&rmsg) > 0)
		{
			if (t_rcv (tcp_fd, hp, sizeof (HEADER), (int *)NULL) < 0)
				error (NOSTR);
#ifdef	LITTLE_ENDIAN
			header_endian_cv (hp);
#endif	LITTLE_ENDIAN
		}
		else
		{
			hp = (HEADER *)NULL;
		}
	}

	/*
	 *	Se o arquivo n�o existe no n� local, ...
	 */
	if (lsp == (STAT *)NULL)
	{
		print_file_nm (file_nm, rsp, ":\n", &file_printed);

		diff_files_cnt++;

		if (fromflag && remote_link_nm[0] != '\0')
		{
			msg
			(	"O arquivo deveria ser um elo f�sico a "
				"\"%s\" em \"%s\"",
				remote_link_nm, local_node_nm
			);

			return (save_op_info (file_nm, lsp, rsp, L_LINK, remote_link_nm));
		}
		else
		{
			return (save_op_info (file_nm, lsp, rsp, CPFROM));
		}
	}

	/*
	 *	Os arquivos existem c� e l�; verifica se os elo f�sico conferem
	 */
	print_file_nm (file_nm, lsp, ":\n", &file_printed);

	if (local_link_nm == NOSTR)
	{
		if (remote_link_nm[0] != '\0')
		{
			if (fromflag)
			{
				msg
				(	"O arquivo deveria ser um elo f�sico a "
					"\"%s\" em \"%s\"",
					remote_link_nm, local_node_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, L_RM_LINK, remote_link_nm));
			}
			else
			{
				msg
				(	"O arquivo tem um elo f�sico esp�rio com "
					"\"%s\" em \"%s\"",
					remote_link_nm, remote_node_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, R_RM_CPTO));
			}
		}
	}
	else	/* local_link_nm != NOSTR) */
	{
		if   (remote_link_nm[0] == '\0')
		{
			if (fromflag)
			{
				msg
				(	"O arquivo tem um elo f�sico esp�rio com "
					"\"%s\" em \"%s\"",
					local_link_nm, local_node_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, L_RM_CPFROM));
			}
			else
			{
				msg
				(	"O arquivo deveria ser um elo f�sico a "
					"\"%s\" em \"%s\"",
					local_link_nm, remote_node_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, R_RM_LINK, local_link_nm));
			}
		}
		elif (!streq (local_link_nm, remote_link_nm))
		{
			if (fromflag)
			{
				msg ("O arquivo tem um elo f�sico inv�lido em \"%s\"", local_node_nm);

				msg
				(	"O elo f�sico deveria ser \"%s\" "
					"ao inv�s de \"%s\"",
					remote_link_nm, local_link_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, L_RM_LINK, remote_link_nm));
			}
			else
			{
				msg
				(	"O arquivo tem um elo f�sico inv�lido em "
					"\"%s\"", remote_node_nm
				);

				msg
				(	"O elo f�sico deveria ser \"%s\" "
					"ao inv�s de \"%s\"",
					local_link_nm, remote_link_nm
				);

				diff_files_cnt++;

				return (save_op_info (file_nm, lsp, rsp, R_RM_LINK, local_link_nm));
			}
		}
		else	 	/* O elo f�sico confere */
		{
			return (0);
		}
	}

	/*
	 *	Verifica se o tipo de arquivo � o mesmo
	 */
	if ((lsp->st_mode & S_IFMT) != (rsp->st_mode & S_IFMT))
	{
		msg
		(	"Os arquivos t�m tipos diferentes (%c :: %c)",
			modetostr (lsp->st_mode)[0], modetostr (rsp->st_mode)[0]
		);

		diff_files_cnt++;

		time_cmp (lsp->st_mtime, rsp->st_mtime);

		return (save_op_info (file_nm, lsp, rsp, CP, lsp->st_mtime, rsp->st_mtime));
	}

	/*
	 *	Compara, dependendo do tipo de arquivo
	 */
	if (S_ISREG (lsp->st_mode))
		regular_file_cmp (file_nm, lsp, rsp, hp);
	else
		return (no_regular_file_cmp (file_nm, lsp, rsp));

	return (0);

}	/* end file_cmp */

/*
 ****************************************************************
 *	Compara��o de arquivos regulares			*
 ****************************************************************
 */
int
regular_file_cmp (const char *file_nm, STAT *lsp, STAT *rsp, HEADER *rhp)
{
	int		i, mod;
	off_t		n;
	int		fd;
	int		base;
	char		buf[BLSZ];
	ushort		client_crc_buf[SEGCRCSZ];
	ushort		serv_crc_buf[SEGCRCSZ];

	/*
	 *	Se o tamanho for o mesmo, abre o arquivo para os CRCs
	 */
	if (lsp->st_size != rsp->st_size)
	{
		msg
		(	"Os arquivos t�m tamanhos diferentes (%d :: %d)",
			lsp->st_size, rsp->st_size
		);

		diff_files_cnt++;

		time_cmp (lsp->st_mtime, rsp->st_mtime);

		return (save_op_info (file_nm, lsp, rsp, CP, lsp->st_mtime, rsp->st_mtime));
	}

	if ((fd = inopen (lsp->st_dev, lsp->st_ino)) < 0)
	{
		msg ("*N�o consegui abrir o arquivo em \"%s\"", local_node_nm);

		diff_files_cnt++;

		return (save_op_info (file_nm, lsp, rsp, CPFROM));
	}

	/*
	 *	Verifica se � compara��o r�pida de m�dulos objeto
	 */
	if (qflag && rhp != (HEADER *)NULL)
	{
		HEADER		lh;

		if (read (fd, &lh, sizeof (HEADER)) < 0)
			error ("$*Erro de leitura do arquivo \"%s\"", file_nm);

		if (lh.h_time == rhp->h_time)
			{ close (fd); return (0); }

		lseek (fd, 0, SEEK_SET);
	}

	/*
	 *	Pede � esta��o remota para enviar os CRCs
	 */
	t_snd_msg (FCMP, NOSTR);

	/*
	 *	Compara os CRCs dos blocos
	 */
	for
	(	i = 0, mod = 0, crc_diff = 0, base = 0;
		(n = read (fd, buf, BLSZ)) > 0;
		i++
	)
	{
		/*
		 *	Verifica se � um m�dulo objeto
		 */
		if (i == 0)
		{
			rhp = (HEADER *)buf;

			if (rhp->h_magic == NMAGIC || rhp->h_magic == FMAGIC || rhp->h_magic == SMAGIC)
				rhp->h_time = 0;
		}

		/*
		 *	Calcula e guarda o CRC do bloco lido
		 */
		client_crc_buf[mod] = crc16 (buf, n);

		/*
		 *	Verifica se encheu um bloco de CRCs
		 */
		if (++mod >= SEGCRCSZ)
		{
			if (t_rcv (tcp_fd, serv_crc_buf, SEGCRCSZ * sizeof (short), (int *)NULL) < 0)
				error (NOSTR);

			crc_cmp (client_crc_buf, serv_crc_buf, SEGCRCSZ, base);

			mod = 0; base += SEGCRCSZ;
		}

	}	/* loop pelo blocos */

	close (fd);

	if (n < 0)
		error ("$*Erro de leitura do arquivo \"%s\"", file_nm);

	/*
	 *	Processa o bloco incompleto de CRCs
	 */
	if (mod > 0)
	{
		if (t_rcv (tcp_fd, serv_crc_buf, mod * sizeof (short), (int *)NULL) < 0)
			error (NOSTR);

		crc_cmp (client_crc_buf, serv_crc_buf, mod, base);
	}

	/*
	 *	Verifica se houve diferen�as
	 */
	if (!crc_diff)
		return (0);

	diff_files_cnt++;

	time_cmp (lsp->st_mtime, rsp->st_mtime);

	return (save_op_info (file_nm, lsp, rsp, CP, lsp->st_mtime, rsp->st_mtime));

}	/* end regular_file_cmp */

/*
 ****************************************************************
 *	Compara vetores de CRCs					*
 ****************************************************************
 */
void
crc_cmp (ushort bcrcv[], ushort rcrcv[], int n, int bloco)
{
	int		i;

	/*
	 *	O resultado � dado em "crc_diff"
	 */
	for (i = 0; i < n; i++)
	{
		if (bcrcv[i] != ENDIAN_SHORT (rcrcv[i]))
		{
			if   (crc_diff <  5)
				msg ("Os arquivos diferem no bloco %d", bloco + i);
			elif (crc_diff == 5)
				msg ("N�mero excessivo de blocos diferentes");
			crc_diff++;
		}
	}

}	/* end crc_cmp */

/*
 ****************************************************************
 *	Compara��o de arquivos N�O regulares			*
 ****************************************************************
 */
int
no_regular_file_cmp (const char *file_nm, STAT *lsp, STAT *rsp)
{
	char		*local_symlink_nm, *remote_symlink_nm;

	/*
	 *	Analisa o tipo de arquivo
	 */
	switch (lsp->st_mode & S_IFMT)
	{
	    case S_IFBLK:
	    case S_IFCHR:
		if (lsp->st_rdev == rsp->st_rdev)
			return (0);

		msg
		(	"S�o dispositivos diferentes (%d/%d :: %d/%d)",
			MAJOR (lsp->st_rdev), MINOR (lsp->st_rdev),
			MAJOR (rsp->st_rdev), MINOR (rsp->st_rdev)
		);

		diff_files_cnt++;
		time_cmp (lsp->st_mtime, rsp->st_mtime);

		return (save_op_info (file_nm, lsp, rsp, CP, lsp->st_mtime, rsp->st_mtime));

	    case S_IFLNK:
		local_symlink_nm  = alloca (lsp->st_size + 1);
		remote_symlink_nm = alloca (rsp->st_size + 1);

		if (readlink (file_nm, local_symlink_nm, lsp->st_size + 1) < 0)
		{
			msg ("*N�o consegui obter o conte�do do elo em \"%s\"", local_node_nm);
			diff_files_cnt++;

			return (save_op_info (file_nm, lsp, rsp, CPFROM));
		}

		/* Pede ao servidor para enviar o conte�do do elo */

		t_snd_msg (FCMP, NOSTR);

		if (t_rcv (tcp_fd, remote_symlink_nm, rsp->st_size + 1, (int *)NULL) < 0)
			error (NOSTR);

		if (streq (local_symlink_nm, remote_symlink_nm))
			return (0);

		msg
		(	"Os conte�dos dos elos s�o diferentes (\"%s\" :: \"%s\")",
			local_symlink_nm, remote_symlink_nm
		);

		diff_files_cnt++;
		time_cmp (lsp->st_mtime, rsp->st_mtime);

		return (save_op_info (file_nm, lsp, rsp, CP, lsp->st_mtime, rsp->st_mtime));

	    case S_IFDIR:
	    case S_IFIFO:
		return (0);

	    default:
		msg ("Tipo %d inv�lido de arquivo", (lsp->st_mode & S_IFMT) >> 12);
		return (0);

	}	/* end switch */

}	/* end no_regular_file_cmp */
