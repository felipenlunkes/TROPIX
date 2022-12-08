/*
 ****************************************************************
 *								*
 *			pr.c					*
 *								*
 *	Imprime arquivos					*
 *								*
 *	Vers�o	1.0.0, de 17.04.86				*
 *		4.7.0, de 30.12.04				*
 *								*
 *	M�dulo: pr						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <a.out.h>
#include <time.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.7.0, de 30.12.04";

#define	elif	else if

#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	STDOUT	1
#define	STDIN	0

#define	PAGESZ	75		/* Tamanho total da p�gina */
#define	UNUSEDSZ 10		/* Tamanho n�o usado para texto */

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	hflag;		/* Cabe�alho dado */
entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

/*
 ****** Vari�veis diversas **************************************
 */
entry const char *header;	/* Header */

entry int	init_pageno = 1; /* N�mero da p�gina inicial */

entry int	pagesz = PAGESZ - UNUSEDSZ;	/* Linhas por p�gina */ 

entry int	pagecnt;	/* Contador de p�ginas */

entry int	lastpage = 0;	/* �ltima p�gina */

entry int	linecnt;	/* Contador de linhas */

entry int	offset;		/* Deslocamento */

entry dev_t	stdout_dev;	/* Dispositivo da sa�da padr�o */
entry ino_t	stdout_ino;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
int		proc_file (const char *, FILE *, STAT *);

/*
 ****************************************************************
 *	Imprime arquivos					*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int			opt;
	FILE			*fp;
	const char		*pageno_str = NOSTR;
	const char		*lastpage_str = NOSTR;
	const char		*pagesz_str = NOSTR;
	const char		*offset_str = NOSTR;
	const char		*str;
	STAT			s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "o:p:e:h:l:vNH")) != EOF)
	{
		switch (opt)
		{
		    case 'o':			/* Deslocamento */
			offset_str = optarg;
			break;

		    case 'p':			/* P�gina de in�cio  */
			pageno_str = optarg;
			break;

		    case 'e':			/* P�gina de final  */
			lastpage_str = optarg;
			break;

		    case 'h':			/* Cabe�alho */
			header = optarg;
			hflag++;
			break;

		    case 'l':			/* Comprimento da p�gina */
			pagesz_str = optarg;
			break;

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

	argv += optind;
	argc -= optind;

	/*
	 *	Analisa o deslocamento
	 */
	if (offset_str != NOSTR)
	{
		if ((offset = strtol (offset_str, &str, 0)) < 0 || *str)
			error ("$Deslocamento inv�lido: \"%s\"", offset_str);
	}

	/*
	 *	Analisa o n�mero de p�gina dado
	 */
	if (pageno_str != NOSTR)
	{
		if ((init_pageno = strtol (pageno_str, &str, 0)) <= 0 || *str)
			error ("$N�mero de p�gina inicial inv�lido: \"%s\"", pageno_str);
	}

	/*
	 *	Analisa o n�mero da �ltima p�gina
	 */
	if (lastpage_str != NOSTR)
	{
		if ((lastpage = strtol (lastpage_str, &str, 0)) < init_pageno || *str)
			error ("$N�mero de p�gina final inv�lido: \"%s\"", lastpage_str);
	}

	/*
	 *	Analisa o tamanho de p�gina dado
	 */
	if (pagesz_str != NOSTR)
	{
		if ((pagesz = strtol (pagesz_str, &str, 0) - UNUSEDSZ) <= 0 || *str)
			error ("$Tamanho de p�gina inv�lido: \"%s\"", pagesz_str);
	}

	/*
	 *	Determina quem � o "stdout"
	 */
	fstat (STDOUT, &s);

	stdout_dev = s.st_dev;
	stdout_ino = s.st_ino;

	/*
	 *	Analisa o Nflag
	 */
	if   (Nflag)
	{
		if (*argv != NOSTR)
		{
			error ("Os argumentos sup�rfluos ser�o ignorados");
			*argv = NOSTR;
		}
	}
	elif (*argv == NOSTR)
	{
		/*
		 *	N�o foram dados argumentos, nem a op��o "-N"
		 */
		fstat (STDIN, &s);	time (&s.st_mtime);

		exit (proc_file ("stdin", stdin, &s));
	}

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR)		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if ((fp = fopen (area, "r")) == NOFILE)
			{
				error ("*N�o consegui abrir \"%s\"", area);
				continue;
			}
	
			fstat (fileno (fp), &s);

			exit_code += proc_file (area, fp, &s);

			fclose (fp);
		}
	}
	else				/* Foram dados argumentos */
	{
		/*
		 *	Foram dados argumentos
		 */
		for (/* vazio */; *argv; argv++)
		{
			if (streq (*argv, "-"))
			{
				fstat (STDIN, &s);	time (&s.st_mtime);

				exit_code += (proc_file ("stdin", stdin, &s));

				continue;
			}

			if ((fp = fopen (*argv, "r")) == NOFILE)
			{
				error ("*N�o consegui abrir \"%s\"", *argv);
				continue;
			}
	
			fstat (fileno (fp), &s);

			exit_code += proc_file (*argv, fp, &s);

			fclose (fp);
		}
	}

	return (exit_code);

}	/* end pr */

/*
 ****************************************************************
 *	Processa uma arquivo					*
 ****************************************************************
 */
int
proc_file (const char *filenm, FILE *fp, STAT *sp)
{
	int			i, c;
	HEADER			h;
	const char		*filetime;

	/*
	 *	Testa se � um diret�rio
	 */
	if (S_ISDIR (sp->st_mode))
	{
		error ("\"%s\" � um diret�rio", filenm);
		return (1);
	}

	/*
	 *	Verifica se n�o est� se tentanto imprimir a pr�pria sa�da!
	 */
	if (fp != stdin)
	{
		if (sp->st_dev == stdout_dev  &&  sp->st_ino == stdout_ino)
		{
			error ("\"%s\" � o pr�prio arquivo de sa�da", filenm);
			return (1);
		}
	}

	/*
	 *	Testa se � um programa objeto apenas se n�o for
	 *	"stdin"   (n�o podemos dar "rewind" em um pipe)
	 */
	if (fp != stdin && !S_ISFIFO (sp->st_mode))
	{
		if ((fread (&h, sizeof (h), 1, fp)) == 1)
		{
			if (h.h_magic == FMAGIC || h.h_magic == NMAGIC)
			{
				error ("\"%s\" � um programa objeto", filenm);
				return (1);
			}
		}

		rewind (fp);
	}

	/*
	 *	Obt�m a data do arquivo
	 */
	filetime = btime (&sp->st_mtime);

	/*
	 *	Se n�o foi dado "header", � usado o nome do arquivo
	 */
	if (!hflag)
		header = filenm; 

	/*
	 *	Le at� a p�gina onde deve comecar a impress�o
	 */
	pagecnt = 1; 	c = ' ';

	while (init_pageno > pagecnt  &&  c >= 0 /* != EOF */)
	{
		/*
		 *	L� uma p�gina
		 */
		linecnt = 1;

		while (linecnt <= pagesz  &&  c >= 0 /* != EOF */)
		{
			/*
			 *	Le uma linha
			 */
			while ((c = getc (fp)) >= 0 /* != EOF */  &&  c != '\n')
			{
				if (c == '\f')
				{
					if ((c = getc (fp)) != '\n')
						ungetc (c, fp);

					linecnt = pagesz - 1;
					break;
				}
			}

			linecnt++;
		}

		pagecnt++;
	}

	/*
	 *	Verifica se ainda n�o acabou o arquivo
	 */
	if (c < 0 /* == EOF */)
		return (0);

	/*
	 *	Imprime at� o fim do arquivo
	 */
	for (c = getc (fp); c >= 0 /* != EOF */; pagecnt++)
	{
		/*
		 *	Imprime o cabecalho
		 */
		printf ("\n\n");

		for (i = offset; i > 0; i--)
			putchar (' ');

		printf
		(	"%-24.24s     %s     pag. %d\n\n\n",
			filetime, header, pagecnt
		);

		/*
		 *	Imprime uma p�gina
		 */
		linecnt = 1;

		while (linecnt <= pagesz)
		{
			/*
			 *	Coloca o "offset"
			 */
			for (i = offset; i > 0; i--)
				putchar (' ');

			/*
			 *	Imprime uma linha
			 */
			while (c >= 0 /* != EOF */  &&  c != '\n'  &&  c != '\f')
			{
				putchar (c);
				c = getc (fp);
			}

			/*
			 *	Examina os caracteres EOF, <nl> e <np>
			 */
			switch (c)
			{
			    case '\n':
				putchar ('\n');
				c = getc (fp);
				linecnt++;
				break;

			    case EOF:
				while (linecnt++ <= pagesz)
					putchar ('\n');
				break;

			    case '\f':
				while (linecnt++ <= pagesz)
					putchar ('\n');
				if ((c = getc (fp)) == '\n')
					c = getc (fp);
				break;
			}
		
		}

		printf ("\n\n\n\n\n");

		/*
		 *	Verifica se chegou � �ltima p�gina
		 */
		if (lastpage > 0  &&  pagecnt >= lastpage)
			return (0);

	} 	/* end imprimindo as p�ginas */

	return (0);

}	/* end proc_file */

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
		"%s - imprime arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-o <o>] [-p <p>] [-e <e>] [-h \"<h>\"] "
			"[-l <l>] [-N] [<arquivo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-o: Desloca cada linha <o> caracteres para a direita\n"
		"\t-p: Come�a a imprimir a partir da p�gina <p>\n"
		"\t-e: Imprime somente at� a p�gina <e>\n"
		"\t-h: Utiliza <h> como cabe�alho das p�ginas\n"
		"\t    (ao inv�s dos nomes dos respectivos <arquivo>s)\n"
		"\t-l: Usa a p�gina com <l> linhas "
			"(ao inv�s de " XSTR (PAGESZ) ")\n"
		"\t-N: L� os nomes dos arquivos de \"stdin\"\n"
		"\nObs.:\tUm <arquivo> com nome \"-\" " 
			"representa a entrada padr�o\n"
	);

	exit (2);

}	/* end help */
