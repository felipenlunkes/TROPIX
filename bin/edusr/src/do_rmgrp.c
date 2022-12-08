/*
 ****************************************************************
 *								*
 *			rmgrp.c					*
 *								*
 *	Gerenciador de contas					*
 *								*
 *	Vers�o	1.5.0, de 04.06.84				*
 *		3.1.0, de 17.10.98				*
 *								*
 *	M�dulo: edusr						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <errno.h>

#include "../h/edusr.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_rmgrp_help (void);

/*
 ****************************************************************
 *	Remove a conta de um usu�rio				*
 ****************************************************************
 */
void
do_rmgrp (int argc, const char *argv[])
{
	int		opt;
	FILE		*tfp;
	const PASSWD	*pw;
	const GROUP	*gr;
	const char	*group_nm;
	int		gid = -1, n_user = 0;
	char		command_str[128];

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_rmgrp_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_rmgrp_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if ((group_nm = *argv) != NOSTR) 
	{
		if (streq (group_nm, "-"))
			group_nm = NOSTR;

		argv++;
	}

	if (*argv)
		do_rmgrp_help ();

	/*
	 *	Examina os argumentos
	 */
	if (group_nm == NOSTR)
	{
		error ("Faltando o nome do <grupo>", cmd_nm);
		return;
	}

	if (isdigit (group_nm[0]))
	{
		error ("� necess�rio dar o nome do <grupo>");
		return;
	}

	if (streq (group_nm, current_group_nm))
	{
		error ("N�o posso remover o <grupo> corrente \"%s\"", group_nm);
		return;
	}

	/*
	 *	Remove a entrada do grupo
	 */
	signal (SIGINT, SIG_IGN);
	tfp = tmpfile ();
	setgrent ();

	while ((gr = getgrent ()) != NOGROUP)
	{
		if (!streq (gr->gr_name, group_nm))
			{ putgrent (gr, tfp); continue; }

		gid = gr->gr_gid;

	}	/* malha copiando o arquivo de grupos */

	if (gid < 0)
	{
		error ("Grupo \"%s\" desconhecido", group_nm);
		goto abort;
	}

	/*
	 *	Conta o n�mero de usu�rio do <grupo> dado
	 */
	setpwent ();

	while ((pw = getpwent ()) != NOPASSWD)
	{
		if (pw->pw_gid == gid)
			n_user++;
	}

	endpwent ();

	/*
	 *	Confirma a remo��o
	 */
	fprintf (stderr, "\nGrupo\t\t   = %s (%d)\n", group_nm, gid);
	fprintf (stderr, "N�mero de usu�rios = %d\n", n_user);

	fprintf
	(	stderr,
		"\nDeseja remover o grupo "
		"(al�m dos seus usu�rios e arquivos? (n): "
	);

	if (askyesno () <= 0)
		goto abort;

	endgrent ();
	copyfile (tfp, group_file_nm);

	/*
	 *	Remove as entradas dos usu�rios (se houver)
	 */
	if (n_user <= 0)
		return;

	signal (SIGINT, SIG_IGN);
	tfp = tmpfile ();
	setpwent ();

	while ((pw = getpwent ()) != NOPASSWD)
	{
		if (pw->pw_gid != gid)
			{ putpwent (pw, tfp); continue; }

		/* Remove o HOME */

		printf ("Removendo o usu�rio \"%s\"\n", pw->pw_name);

#if (0)	/*******************************************************/
		strcpy (command_str, "rmtree -f ");
#endif	/*******************************************************/
		strcpy (command_str, "rmtree ");
		strcat (command_str, pw->pw_dir);

		if ((system (command_str) >> 8) != 0)
		{
			printf
			(	"N�o consegui remover os arquivos do usu�rio \"%s\"\n",
				pw->pw_name
			);
		}

		/* Remove a caixa postal */

		strcpy (mbox_nm_ptr, pw->pw_name);

		printf ("\n");
		strcpy (command_str, "rmtree ");
		strcat (command_str, mbox_nm);

		if ((system (command_str) >> 8) != 0)
		{
			printf
			(	"N�o consegui remover a caixa postal do usu�rio \"%s\"\n",
				pw->pw_name
			);
		}
	}

	endpwent ();
	copyfile (tfp, pwd_file_nm);
	signal (SIGINT, on_intr);
	return;

	/*
	 *	Interrompe a remo��o
	 */
    abort:
	endgrent ();
	endpwent ();
	fclose (tfp);
	signal (SIGINT, on_intr);

}	/* end do_rmgrp */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_rmgrp_help (void)
{
	fprintf
	(	stderr,
		"%s - remove um grupo (juntamente com os seus usu�rios e arquivos)\n"
		"\nSintaxe:\n"
		"\t%s <grupo>\n",
		cmd_nm, cmd_nm
	);

}	/* end do_rmgrp_help */
