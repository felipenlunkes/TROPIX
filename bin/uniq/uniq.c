/*
 ****************************************************************
 *								*
 *			uniq.c					*
 *								*
 *	Indica linhas repetidas de um arquivo			*
 *								*
 *	Vers�o	2.0.0, de 03.09.85				*
 *		3.0.0, de 13.07.97				*
 *								*
 *	M�dulo: uniq						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 13.07.97";

#define	LINE_SZ	1024

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	nflag;		/* Apenas um exemplar de cada linha repetida */
entry int	uflag;		/* Escreve apenas as linhas n�o repetidas */
entry int	dflag;		/* Um exemplar somente das linhas repetidas */
entry int	cflag;		/* Contagem de freq��ncia */
entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
const char	*field_char_skip (const char *, int, int);

/*
 ****************************************************************
 *	Indica linhas repetidas de um arquivo			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	register int	opt, repetition;
	register int	field_cnt = 0, char_cnt = 0;
	char		line_buf_1[LINE_SZ], line_buf_2[LINE_SZ];
	char		*line_1 = line_buf_1, *line_2 = line_buf_2;
	const char	*field_1, *field_2;
	const char	*field_str = NOSTR, *char_str = NOSTR;
	int		flag_total;
	const char	*str;
	char		*t;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "nudcf:b:vH")) != EOF)
	{
		switch (opt)
		{
		    case 'n':	/* Apenas um exemplar de cada linha repetida */
			nflag++;
			break;

		    case 'u':	/* Escreve apenas as linhas n�o repetidas */
			uflag++;
			break;

		    case 'd':	/* Um exemplar somente das linhas repetidas */
			dflag++;
			break;

		    case 'c':	/* Contagem de freq��ncia */
			cflag++;
			break;

		    case 'f':			/* Campos a pular */
			field_str = optarg;
			break;

		    case 'b':			/* Bytes a pular */
			char_str = optarg;
			break;

		    case 'v':			
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Consist�ncia das op��es/argumentos
	 */
	argv += optind;
	argc -= optind;

	if (argc > 2)
		help ();

	if ((flag_total = nflag + uflag + dflag) > 1)
		help ();

	if (flag_total == 0) 
		nflag++;

	if (nflag)
		{ uflag++; dflag++; }

	/*
	 *	Analisa o n�mero de campos a pular
	 */
	if (field_str != NOSTR)
	{
		if ((field_cnt = strtol (field_str, &str, 0)) < 0 || *str != '\0')
		{
			fprintf
			(	stderr,
				"%s: N�mero de campos inv�lido: \"%s\"\n",
				pgname, field_str
			);
			exit (1);
		}
	}

	/*
	 *	Analisa o n�mero de caracteres a pular
	 */
	if (char_str != NOSTR)
	{
		if ((char_cnt = strtol (char_str, &str, 0)) < 0 || *str != '\0')
		{
			fprintf
			(	stderr,
				"%s: N�mero de caracteres inv�lido: \"%s\"\n",
				pgname, char_str
			);
			exit (1);
		}
	}

	/*
	 *	Abre o arquivo de entrada
	 */
	if (argc > 0  &&  !streq (argv[0], "-"))
	{
		if (freopen (argv[0], "r", stdin) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, argv[0], strerror (errno)
			);
			exit (1);
		}
	}

	/*
	 *	Abre o arquivo de sa�da
	 */
	if (argc > 1)
	{
		if (freopen (argv[1], "w", stdout) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, argv[1], strerror (errno)
			);
			exit (1);
		}
	}

	/*
	 *	L� a primeira linha
	 */
	repetition = 0;

	if (fngets (line_1, LINE_SZ, stdin) == NOSTR)
	{
		if (ferror (stdin))
		{
			fprintf
			(	stderr,
				"%s: Erro de leitura da <entrada> (%s)\n",
				pgname, strerror (errno)
			);
			exit (1);
		}

		exit (0);
	}

	field_1 = field_char_skip (line_1, field_cnt, char_cnt);

	/*
	 *	Vai lendo as linhas restantes, comparando sempre com a anterior
	 */
	while (fngets (line_2, LINE_SZ, stdin) != NOSTR)
	{
		field_2 = field_char_skip (line_2, field_cnt, char_cnt);

		if (streq (field_2, field_1))
			{ repetition++; continue; }

		if (dflag && repetition || uflag && !repetition)
		{
			if (cflag)
				printf ("%6d  ", repetition + 1);

			puts (line_1);
		}

		repetition = 0;

		field_1  = field_2;

		t = line_2; line_2 = line_1; line_1 = t;

	}	/* end while */

	/*
	 *	Escreve a �ltima linha
	 */
	if (dflag && repetition || uflag && !repetition)
	{
		if (cflag)
			printf ("%6d  ", repetition + 1);

		puts (line_1);
	}

	/*
	 *	Encerra a opera��o
	 */
	if (ferror (stdin))
	{
		fprintf
		(	stderr,
			"%s: Erro de leitura da <entrada> (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	fflush (stdout);

	if (ferror (stdout))
	{
		fprintf
		(	stderr,
			"%s: Erro de escrita na <sa�da> (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	return (0);

}	/* end uniq */

/*
 ****************************************************************
 *	Pula os campos/bytes					*
 ****************************************************************
 */
const char *
field_char_skip (const char *cp, int field_cnt, int char_cnt)
{
	if (field_cnt)
	{
		while (*cp == ' ' || *cp == '\t')
			cp++;

		while (field_cnt-- > 0)
		{
			while (*cp != ' ' && *cp != '\t' && *cp != '\0')
				cp++;

			while (*cp == ' ' || *cp == '\t')
				cp++;
		}
	}

	while (char_cnt-- > 0 && *cp != '\0')
		cp++;

	return (cp);

}	/* field_char_skip */

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
		"%s - indica linhas repetidas de um arquivo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-nudc] [-f <f>] [-b <b>] [<entrada> [<sa�da>]]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-n: Mant�m apenas um exemplar de cada linha repetida (modo normal)\n"
		"\t-u: Escreve apenas as linhas n�o repetidas\n"
		"\t-d: Escreve apenas um exemplar somente das linhas repetidas\n"
		"\t-c: Adiciona uma contagem de freq��ncia como prefixo\n"
		"\t-f: Na compara��o, ignora os <f> campos iniciais\n"
		"\t-b: Na compara��o, ignora os <b> caracteres iniciais\n"
		"\nObs.:\tSe <entrada> for \"-\", ser� lida a entrada padr�o\n"
	);

	exit (2);

}	/* end help */
