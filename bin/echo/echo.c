/*
 ****************************************************************
 *								*
 *			echo.c					*
 *								*
 *	Ecoa os argumentos					*
 *								*
 *	Vers�o	1.0.0, de 10.07.86				*
 *		4.3.0, de 20.09.02				*
 *								*
 *	M�dulo: echo						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
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
const char	pgversion[] =  "Vers�o:	4.3.0, de 20.09.02";

entry int	nflag;		/* N�o p�e "\n" */
entry int	lflag;		/* Um por linha */
entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Ecoa os argumentos					*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, i, color = 0;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "nl1234567vH")) != EOF)
	{
		switch (opt)
		{
		    case 'n':			/* N�o p�e "\n" */
			nflag++;
			break;

		    case 'l':			/* Um por linha */
			lflag++;
			break;

		    case '1':			/* D� a cor */
		    case '2':
		    case '3':
		    case '4':
		    case '5':
		    case '6':
		    case '7':
			color = opt - '0';

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	if (lflag && nflag)
		help ();

	/*
	 *	Ecoa os argumentos
	 */
	if (color != 0)
		printf ("\e[3%dm", color);

	if (lflag)
	{
		for (i = 0; i < argc; i++)
			printf ("%s\n", argv[i]);
	}
	else
	{
		if (argc > 0)
			printf ("%s", argv[0]);

		for (i = 1; i < argc; i++)
			printf (" %s", argv[i]);

		if (!nflag)
			putchar ('\n');
	}

	if (color != 0)
		printf ("\e[0m", color);


	return (0);

}	/* end echo */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - ecoa os arqumentos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-nl1234567] [<argumento> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-n:   Termina a linha sem o <nl>\n"
		"\t-l:   Coloca cada argumento em uma linha\n"
		"\t-1-7: Usa a cor dada\n"
	);

	exit (2);

}	/* end help */
