/*
 ****************************************************************
 *								*
 *			expir.c					*
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
#include <time.h>
#include <errno.h>
#include <string.h>

#include "../h/edusr.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_expir_help (void);

/*
 ****************************************************************
 *	Altera a data de expira��o da conta de usu�rio		*
 ****************************************************************
 */
void
do_expir (int argc, const char *argv[])
{
	int		opt;
	const char	*expir_nm;
	time_t		n;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_expir_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_expir_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc > 1)
		{ do_expir_help (); return; }

	/*
	 *	Imprime o "expir" corrente
	 */
	if (argc == 0)
		{ do_expir_current (); return; }

	/*
	 *	Processa a nova data de expira��o
	 */
	expir_nm = argv[0];

	if   (streq (expir_nm, "-") || streq (expir_nm, "0"))
	{
		n = 0;
	}
	elif ((n = time_to_internal_cv (expir_nm)) < 0)
	{
		error ("Data de expira��o \"%s\" inv�lida", expir_nm);
		return;
	}

	current_expir_date = n;

	do_expir_current ();

}	/* end do_expir */

/*
 ****************************************************************
 *	Imprime a data de expira��o corrente			*
 ****************************************************************
 */
void
do_expir_current (void)
{
	if (current_expir_date == 0)
		printf ("N�o h� data de expira��o corrente\n");
	else
		printf ("A data de expira��o corrente � %s\n", time_to_external_cv (current_expir_date));

}	/* end do_expir_current */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_expir_help (void)
{
	fprintf
	(	stderr,
		"%s - altera a data de expira��o da conta de usu�rio\n"
		"\nSintaxe:\n"
		"\t%s [<expir>]\n"
		"\nObs.:\tSe <expir> n�o for dada, � impressa a data de expira��o corrente.\n"
		"\tO formato de <expir> deve ser \"dd.mm.aa\", ou \"0\" significando\n"
		"\ta aus�ncia de data de expira��o\n",
		cmd_nm, cmd_nm
	);

}	/* end do_expir_help */
