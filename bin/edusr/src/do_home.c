/*
 ****************************************************************
 *								*
 *			home.c					*
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
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../h/edusr.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_home_help (void);

/*
 ****************************************************************
 *	Modifica o diret�rio contendo os arquivos dos usu�rios	*
 ****************************************************************
 */
void
do_home (int argc, const char *argv[])
{
	int		opt;
	const char	*nm;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_home_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_home_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc > 1)
		{ do_home_help (); return; }

	/*
	 *	Imprime o "home" corrente
	 */
	if (argc == 0)
		{ do_home_current (); return ; }

	/*
	 *	Processo o novo "home"
	 */
	nm = argv[0];

	if (*nm != '/')
	{
		error ("O nome do diret�rio \"%s\" N�O come�a por \"/\"", nm);
		return;
	}

	if (chdir (nm) < 0 )
	{
		error ("*N�o consegui mudar o diret�rio corrente para \"%s\"", nm);
		return;
	}

	strcpy (current_home, nm);

	do_home_current ();

}	/* end eddir */

/*
 ****************************************************************
 *	Imprime o valor corrente				*
 ****************************************************************
 */
void
do_home_current (void)
{
	printf
	(	"O diret�rio corrente � \"%s\"\n",
		current_home
	);

}	/* end do_home_current */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_home_help (void)
{
	fprintf
	(	stderr,
		"%s - altera o diret�rio \"home\"\n"
		"\nSintaxe:\n"
		"\t%s [<diret�rio>]\n"
		"\nObs.:\tSe o <diret�rio> n�o for dado, � impresso o \"home\" corrente\n",
		cmd_nm, cmd_nm
	);

}	/* end do_home_help */
