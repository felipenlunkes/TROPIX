/*
 ****************************************************************
 *								*
 *			tr1.c					*
 *								*
 *	Teste do TRACE -- FILHO					*
 *								*
 *	Vers�o	1.0.0, de 11.02.88				*
 *		3.0.0, de 18.08.95				*
 *								*
 *	M�dulo: KERNEL						*
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

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	*pgname;	/* Nome do programa */

int		vflag;		/* Verbose */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int	help (void);

/*
 ****************************************************************
 *	Programa de teste do TRACE				*
 ****************************************************************
 */
main (int argc, register const char *argv[])
{
	register int	opt;

	pgname = argv[0];

	/*
	 *	Analisa as op��es.
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();
		}

	}

	argv += optind;
	argc -= optind;

	/*
	 *	Aqui executa o filho
	 */
	printf ("FILHO: iniciando\n");

	printf ("FILHO: terminando\n");
	
	exit (0);

}	/* end tr0 */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
int
help (void)
{
	fprintf (stderr, "%s - programa.\n", pgname);
	fprintf (stderr, "\tVers�o: 1.0 de x.88.\n");
	fprintf (stderr, "\nSintaxe:\n");
	fprintf (stderr, "\t%s [-op��es] arg\n", pgname);
	fprintf (stderr, "\nOp��es:\t-x: op��o.\n");
	fprintf (stderr, "\t-y: op��o.\n");
	fprintf (stderr, "\nObs.:\tobserva��o.\n");
	exit (2);

}	/* end help */
