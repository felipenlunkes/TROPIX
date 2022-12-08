/*
 ****************************************************************
 *								*
 *			prgrp.c					*
 *								*
 *	Gerenciador de contas					*
 *								*
 *	Vers�o	1.5.0, de 04.06.84				*
 *		3.0.0, de 30.07.97				*
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

#include "../h/edusr.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_prgrp_help (void);

/*
 ****************************************************************
 *	Imprime os usu�rios					*
 ****************************************************************
 */
void
do_prgrp (int argc, const char *argv[])
{
	int		opt;
	const PASSWD	*pw;
	const GROUP	*gr;
	const char	*group_nm = NOSTR, *str;
	int		total, group_gid = -1;


	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_prgrp_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_prgrp_help ();
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

	if (*argv != NOSTR)
		{ do_prgrp_help (); return; }

	/*
	 *	Verifica o grupo � num�rico
	 */
	if (group_nm != NOSTR && isdigit (group_nm[0]))
	{
		if ((group_gid = strtol (group_nm, &str, 0)) < 0 || *str != '\0')
		{
			error ("N�mero de grupo \"%s\" inv�lido", group_nm);
			return;
		}
	}

	/*
	 *	Em primeiro lugar, procura o grupo
	 */
	if (group_nm != NOSTR)
	{
		if (group_gid >= 0)
			gr = getgrgid (group_gid);
		else
			gr = getgrnam (group_nm);

		if (gr == NOGROUP)
		{
			error ("Grupo \"%s\" desconhecido", group_nm);
			return;
		}
	}

	/*
	 *	Imprime a lista
	 */
	printf ("GRUPO            GID  USU�RIOS\n\n");

	setgrent ();

	while ((gr = getgrent ()) != NOGROUP)
	{
		if (group_nm != NOSTR)
		{
			if   (group_gid >= 0)
			{
				if (group_gid != gr->gr_gid)
					continue;
			}
			elif (!streq (group_nm, gr->gr_name))
			{
				continue;
			}
		}

		total = 0;

		setpwent ();

		while ((pw = getpwent ()) != NOPASSWD) 
		{
			if (gr->gr_gid == pw->pw_gid)
				total++;
		}

		printf
		(	"%-14s %5d    %6d\n",
			gr->gr_name, gr->gr_gid, total
		);

	   /***	endpwent (); ***/

	}	/* Malha pelo arquivo de grupos */

	putchar ('\n');

   	endpwent ();
   	endgrent ();

}	/* end do_prgrp */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_prgrp_help (void)
{
	fprintf
	(	stderr,
		"%s - imprime a lista de grupos\n"
		"\nSintaxe:\n"
		"\t%s [<grupo>]\n"
		"\nObs.:\tSe <grupo> n�o for dado, imprime todos os grupos\n",
		cmd_nm, cmd_nm
	);

}	/* end do_prgrp_help */
