/*
 ****************************************************************
 *								*
 *			wc.c					*
 *								*
 *	Contador de p�ginas, linhas, palavras e caracteres	*
 *								*
 *	Vers�o	1.1.0, de 27.08.85				*
 *		4.7.0, de 30.12.04				*
 *								*
 *	M�dulo: wc						*
 *		Utilit�rios B�sicos				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
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
const char	pgversion[] =  "Vers�o:	4.7.0, de 30.12.04";

#undef	OPTIONS			/* Permite op��es nunca usadas */

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

#ifdef	OPTIONS
entry int	pflag;		/* P�ginas */
entry int	lflag;		/* Linhas */
entry int	wflag;		/* Palavras */
entry int	cflag;		/* Caracteres */
#endif	OPTIONS

#define	DEF_LINE_PER_PAGE	75	/* No. de linhas default por pg. */

entry int	LINE_PER_PAGE = DEF_LINE_PER_PAGE;

/*
 ****** Totais **************************************************
 */
entry long	file_total;	/* Total de arquivos */

entry long	page_total;	/* Total de p�ginas */
entry long	line_total;	/* Total de linhas */
entry long	word_total;	/* Total de palavras */
entry long	char_total;	/* Total de caracteres */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
int		count_file (const char *);

/*
 ****************************************************************
 *	Contador de p�ginas, linhas, palavras e caracteres	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	*pg_str = NOSTR, *str;

	/*
	 *	Analisa as op��es
	 */
#ifdef	OPTIONS
	while ((opt = getopt (argc, argv, "plwcvP:NH")) != EOF)
#else
	while ((opt = getopt (argc, argv, "vl:NH")) != EOF)
#endif	OPTIONS
	{
		switch (opt)
		{
#ifdef	OPTIONS
		    case 'p':			/* P�ginas */
			pflag++;
			break;

		    case 'l':			/* Linhas */
			lflag++;
			break;

		    case 'w':			/* Palavras */
			wflag++;
			break;

		    case 'c':			/* Caracteres */
			cflag++;
			break;

		    case 'P':			/* Tamanho da p�gina */
			pg_str = optarg;
			break;
#else
		    case 'l':			/* Tamanho da p�gina */
			pg_str = optarg;
			break;
#endif	OPTIONS
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Pequenos acertos
	 */
	argv += optind;
	argc -= optind;

#ifdef	OPTIONS
	if (pflag + lflag + wflag + cflag == 0)
		{ pflag++; lflag++; wflag++; cflag++; }
#endif	OPTIONS

	/*
	 *	Analisa o tamanho da p�gina
	 */
	if (pg_str != NOSTR)
	{
		if ((LINE_PER_PAGE = strtol (pg_str, &str, 0)) <= 0 || *str)
			error ("$Tamanho de p�gina inv�lido: \"%s\"", pg_str);
	}

	/*
	 *	Coloca o cabe�alho
	 */
#ifdef	OPTIONS
	if (pflag)
		printf ("-P�GINAS--  ");

	if (lflag)
		printf ("--LINHAS--  ");

	if (wflag)
		printf ("-PALAVRAS-  ");

	if (cflag)
		printf ("CARACTERES  ");

	printf ("NOME\n");
#else
	printf
	(	"-P�GINAS--  "
		"--LINHAS--  "
		"-PALAVRAS-  "
		"CARACTERES  "
		"NOME\n"
	);
#endif	OPTIONS

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag == 0)
	{
		if (*argv == NOSTR)
			exit (count_file ("-"));
	}
	else
	{
		if (*argv != NOSTR)
		{
			error ("Os argumentos sup�rfluos ser�o ignorados");
			*argv = NOSTR;
		}
	}

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR) 		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
			exit_code += count_file (area);
	}
	else				/* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
			exit_code += count_file (*argv);
	}

	/*
	 *	Imprime o total
	 */
	if (file_total > 1)
	{
#ifdef	OPTIONS
		if (pflag)
			printf ("%10d  ", page_total);

		if (lflag)
			printf ("%10d  ", line_total);

		if (wflag)
			printf ("%10d  ", word_total);

		if (cflag)
			printf ("%10d  ", char_total);

		printf ("TOTAL\n");
#else
		printf
		(	"%10d  %10d  %10d  %10d  TOTAL\n",
			page_total, line_total, word_total, char_total
		);
#endif	OPTIONS
	}

	return (exit_code);

}	/* end wc */

/*
 ****************************************************************
 *	Conta as linhas, palavras e caracteres de um arquivo	*
 ****************************************************************
 */
int
count_file (const char *file_nm)
{
	FILE		*fp;
	int		c, in_word = 0, line_in_page = 0;
	long		line_cnt = 0, word_cnt = 0, char_cnt = 0;
	long		page_cnt = 0;

	file_total++;

	/*
	 *	Abre o arquivo
	 */
	if (streq (file_nm, "-"))
	{
		fp = stdin;	file_nm = "(stdin)";
	}
	else
	{
		if ((fp = fopen (file_nm, "r")) == NOFILE)
		{
			error ("*N�o consegui abrir \"%s\"", file_nm);
			return (1);
		}
	}

	/*
	 *	Conta
	 */
	while ((c = getc (fp)) >= 0)	/* != EOF */
	{
		char_cnt++;

		switch (c)
		{
		    case '\f':
			page_cnt++; 	line_in_page = 0;
			in_word = 0;

			if ((c = getc (fp)) == '\n')
				char_cnt++;
			else
				ungetc (c, fp);

			break;

		    case '\n':
			line_cnt++;

			if (++line_in_page >= LINE_PER_PAGE)
				{ page_cnt++; 	line_in_page = 0; }
		    case ' ':
		    case '\t':
			in_word = 0;
			break;

		    default:
			if (!in_word)
				{ word_cnt++; in_word++; }
			break;

		}	/* end switch */

	}	/* end while */

	if (line_in_page > 0)
		page_cnt++;

	if (ferror (fp))
	{
		error ("*Erro de leitura de \"%s\"", file_nm);
		return (1);
	}

	fclose (fp);

	/*
	 *	Imprime a linha deste arquivo
	 */
#ifdef	OPTIONS
	if (pflag)
		printf ("%10d  ", page_cnt);

	if (lflag)
		printf ("%10d  ", line_cnt);

	if (wflag)
		printf ("%10d  ", word_cnt);

	if (cflag)
		printf ("%10d  ", char_cnt);

	printf ("%s\n", file_nm);  
#else
	printf
	(	"%10d  %10d  %10d  %10d  %s\n",
		page_cnt, line_cnt, word_cnt, char_cnt, file_nm
	);
#endif	OPTIONS

	/*
	 *	Acumula
	 */
	page_total += page_cnt;
	line_total += line_cnt;
	word_total += word_cnt;
	char_total += char_cnt;

	return (0);

}	/* end count_file */

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
		"%s - contador de p�ginas, linhas, palavras e caracteres\n"
		"\n%s\n"
		"\nSintaxe:\n"
#ifdef	OPTIONS
		"\t%s [-plwcN] [-P <l>] [<arquivo> ...]\n",
#else
		"\t%s [-N] [-l <l>] [<arquivo> ...]\n",
#endif	OPTIONS
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
#ifdef	OPTIONS
		"\t-p: Imprime o n�mero de p�ginas\n"
		"\t-l: Imprime o n�mero de linhas\n"
		"\t-w: Imprime o n�mero de palavras\n"
		"\t-c: Imprime o n�mero de caracteres\n"
		"\t-P: A p�gina tem <l> linhas "
			"(ao inv�s de " XSTR (DEF_LINE_PER_PAGE) ")\n"
#else
		"\t-l: A p�gina tem <l> linhas "
			"(ao inv�s de " XSTR (DEF_LINE_PER_PAGE) ")\n"
#endif	OPTIONS
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\". Se n�o forem dados esta\n"
		"\t    op��o nem <arquivo>s, o conte�do do arquivo ser� lido de \"stdin\"\n"
#ifdef	OPTIONS
		"\nObs.:\tSem nenhuma das op��es \"-plwc\" s�o impressos todos os n�meros\n"
#endif	OPTIONS
	);

	exit (2);

}	/* end help */
