/*
 ****************************************************************
 *								*
 *			gfd.c					*
 *								*
 *	Gera o diret�rio de um arquivo FORTUNE			*
 *								*
 *	Vers�o	2.0.0, de 10.06.88				*
 *		3.0.0, de 23.11.97				*
 *								*
 *	M�dulo: gfd						*
 *		Utilit�rios absolutamente sup�rfluos		*
 *		Categoria B					*
 *								*
 *	PLURIX: Sistema Operacional Multiprocessado		*
 *		Um desenvolvimento do NCE/UFRJ			*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	MAXSZ	10000

const char	*pgname;	/* Nome do programa */

const char	pgversion[] =  "Vers�o:	3.0.0, de 23.11.97";

int		vflag;		/* Verbose */

entry int	vetor[MAXSZ];	/* Vetor de ponteiros */

/*
 ****************************************************************
 *	Estado do automata					*
 ****************************************************************
 */
typedef enum
{
	PERCENT,	/* Viu um "%" */
	INFOR		/* A linha � no interior de uma FORTUNE */

}	STATE;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	help (void);

/*
 ****************************************************************
 *	Gera o diret�rio de um arquivo FORTUNE			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, i, c;
	FILE		*fpin, *fpout;
	int		offset;
	STATE		state;
	char		line[256];
	int		count;
	int		lineno;
	int		begin;


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

	if ((fpin = fopen (argv[0], "r")) == NOFILE)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", argv[0]);
		exit (1);
	}

	if ((fpout = fopen (argv[1], "w")) == NOFILE)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", argv[1]);
		exit (1);
	}

	state = PERCENT;
	count = 0;
	lineno = 0;
	offset = 0;

	while (fngets (line, sizeof (line), fpin) != NOSTR)
	{
		lineno++;

		if (line[0] == '%' && line[1] == '\0')
		{
			/*
			 *	Linha com "%"
			 */
			state = PERCENT;

		}	/* end if */
		else
		{
			/*
			 *	Linha de FORTUNE
			 */ 
			switch (state)
			{
			    case PERCENT:
				vetor[count++] = offset;
				state = INFOR;
				break;

			    case INFOR:
				break;

			}	/* end switch */
		}

		offset += strlen (line) + 1;

	}	/* end while */

	printf ("Count = %d\n", count);

	printf
	(	"Vetor[0] = %X, Vetor[%d] = %X\n",
		vetor[0], count-1, vetor[count-1]
	);

	begin = sizeof (int) * (count + 1);

	printf ("Bytes ocupados pelos ponteiros = %d\n", begin);

	/*
	 *	Escreve o n�mero de ponteiros
	 */
	putw (count, fpout);

	/*
	 *	Escreve os ponteiros
	 */
	for (i = 0; i < count; i ++)
		putw (vetor[i] + begin, fpout);

	/*
	 *	Escreve o texto
	 */
	rewind (fpin);

	while ((c = getc (fpin)) != EOF)
		putc (c, fpout);

	return (0);

}	/* end gfd */

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
		"%s - Gera o diret�rio de um arquivo FORTUNE\n",
		pgname
	);
	fprintf (stderr, "\n%s\n", pgversion);
	fprintf (stderr, "\nSintaxe:\n");
	fprintf
	(	stderr,
		"\t%s [-v] <fortunes> <fortunes com ponteiros>\n",
		pgname
	);
	fprintf (stderr, "\nOp��es:\t-v: verboso\n");
	fprintf (stderr, "\nObs.:\tobserva��o\n");
	exit (2);

}	/* end help */
