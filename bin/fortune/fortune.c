/*
 ****************************************************************
 *								*
 *			fortune.c				*
 *								*
 *	Imprime uma FORTUNE					*
 *								*
 *	Vers�o	2.0.0, de 26.09.88				*
 *		3.2.3, de 19.04.00				*
 *								*
 *	M�dulo: games						*
 *		Utilit�rios absolutamente sup�rfluos		*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/times.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	elif	else if

char		*pgversion =  "Vers�o:	3.2.3, de 19.04.00";

#define	STR(x)	# x
#define	XSTR(x)	STR (x)

const char	*FORFILE = XSTR (DATADIR)
				"/fortune.data"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
				"\0\0\0\0\0\0\0\0\0\0\0\0\0\0<=";

int		vflag;		/* Verbose */
int		nflag;		/* Dado o n�mero */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Programa de imprimir uma FORTUNE			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, c;
	FILE		*fp;
	int		count, percent_seen = 0;
	MUTM		mutm;
	unsigned long	u, index = 0;

	/*
	 *	Analisa as op��es.
	 */
	while ((opt = getopt (argc, argv, "vn:f:H")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'n':			/* dado o n�mero */
			nflag++;
			index = atoi (optarg);
			break;

		    case 'f':			/* dado o arquivo */
			FORFILE = optarg;
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

	if ((fp = fopen (FORFILE, "r")) == NOFILE)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", FORFILE);
		exit (1);
	}

	/*
	 *	Calcula o n�mero da FORTUNE
	 */
	count = getw (fp);

	if (nflag)
	{
		u = index;

		if (u >= count)
		{
			printf ("�ndice inv�lido\n");
			exit (2);
		}
	}
	else
	{
		mutime (&mutm);
		u = 10 * mutm.mu_time + getpid ();
		u %= count;
	}

	if (vflag)
	{
		printf
		(	"Data = \"%s\", Count = %d, u = %u\n",
			FORFILE, count, u
		);
	}

	fseek (fp, (u + 1) * sizeof (int), L_SET); 

	fseek (fp, getw (fp), 0);

	percent_seen = 0;

	while ((c = getc (fp)) != EOF)
	{
		if   (c == '%')
		{
			percent_seen++;
		}
		elif (c == '\n')
		{
			if (percent_seen)
				exit (0);

			putchar ('\n');
		}
		else	/* Nem "%" nem <nl> */
		{
			if (percent_seen)
				putchar ('%');

			putchar (c);
			percent_seen = 0;
		}
	}

	return (0);

}	/* end fortune */

#if (0)	/*******************************************************/
/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf (stderr, "%s - Imprime uma FORTUNE\n", pgname);
	fprintf (stderr, "\n%s\n", pgversion);
	fprintf (stderr, "\nSintaxe:\n");
	fprintf (stderr, "\t%s [-v] [-f <datafile>] [-n <index>]\n", pgname);
	fprintf (stderr, "\nOp��es:\t-v: verbose\n");
	fprintf (stderr, "\t-n: � impressa a fortune <index>\n");
	fprintf (stderr, "\t-f: A fortune � obtida de <datafile> (ao inv�s de \"" XSTR (\n");
	exit (2);

}	/* end help */
#endif	/*******************************************************/
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
		"%s - imprime uma frase do dia\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-v] [-f <arquivo>] [-n <�ndice>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: verbose\n"
		"\t-n: � impressa a frase do dia de <�ndice> dado\n"
		"\t-f: A frase do dia � obtida do <arquivo>\n"
		"\t    (ao inv�s de \"%s\")\n", FORFILE
	);

	exit (2);

}	/* end help */
