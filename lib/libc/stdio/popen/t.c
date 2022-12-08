/*
 ****************************************************************
 *								*
 *			t.c					*
 *								*
 *	Programa de teste para POPEN				*
 *								*
 *	Vers�o	1.0.0, de 03.11.87				*
 *		3.2.3, de 05.01.00				*
 *								*
 *	M�dulo: popen/pclose					*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

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
void		help (void);

/*
 ****************************************************************
 *	Programa de teste para POPEN				*
 ****************************************************************
 */
main (int argc, register const char *argv[])
{
	register int	opt, r, i = 0;
	register FILE	*fp;
	register int	ch;
	register int	tipo;

	pgname = argv[0];
	tipo = 1;		/* Write */

	/*
	 *	Analisa as op��es.
	 */
	while ((opt = getopt (argc, argv, "iovH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    case 'o':
			tipo = 1;
			break;

		    case 'i':
			tipo = 0;
			break;

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();
		}

	}

	argv += optind;
	argc -= optind;

	if (*argv == NULL)
		help ();

	fprintf (stderr, "%s em \"%s\"\n", tipo? "Escrevendo":"Lendo", *argv);

	if ((fp = popen (*argv, tipo? "w":"r")) == NOFILE)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", *argv);
		exit (1);
	}
	
	if (tipo)
	{
		while ((ch = getchar ()) != EOF)
			{ putc (ch, fp); i++; }
	}
	else
	{
		while ((ch = getc (fp)) != EOF)
			{ putchar (ch); i++; }
	}

	r = pclose (fp);

	fprintf (stderr, "PCLOSE retornou %d. Escrevi/li %d caracteres\n", r, i);

	exit (0);

}	/* end t */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf (stderr, "%s - teste de \"popen\".\n", pgname);
	fprintf (stderr, "Vers�o: 1.0 de x.87.\n");
	fprintf (stderr, "\nSintaxe:\n");
	fprintf (stderr, "\t%s [-iovH] comando\n", pgname);
	fprintf (stderr, "\nOp��es:\t-i: entrada.\n");
	fprintf (stderr, "\t-o: sa�da.\n");
	fprintf (stderr, "\t-v: verbose.\n");
	fprintf (stderr, "\t-H: ensina a usar o programa.\n");
	fprintf (stderr, "\nObs.:\tobserva��o.\n");
	exit (2);

}	/* end help */
