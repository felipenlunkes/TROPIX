/*
 ****************************************************************
 *								*
 *			file.c					*
 *								*
 *	Tenta identificar o conte�do de um arquivo		*
 *								*
 *	Vers�o  2.0.0, de 02.12.86				*
 *		4.2.0, de 24.04.02				*
 *								*
 *	M�dulo: file						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/a.out.h>
#include <sys/syscall.h>

#include <stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 24.04.02";

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

#define	elif	else if

/*
 ****** �rea de leitura do arquivo ******************************
 */
#define	AREASZ	1024		/* Deve englobar o HEADER do "a.out" */

entry char	area_seq[AREASZ]; /* �rea para an�lise de seq��ncias */

entry char	area_word[AREASZ]; /* �rea para an�lise de palavras */

/*
 ****** Tabela de palavras chaves *******************************
 */
typedef	struct
{
	char	*c_seq[10];
	char	*c_word[8];

}	CARAC;

const CARAC	SROFF =
{
	"\n.he", "\n.fo", "\n.in", "\n.lp", "\n.pp", "\n.sp", "\n.b", NOSTR, NOSTR, NOSTR,
	NOSTR
};

const CARAC	C =
{
	"++", "!=", "&&", "||", "+=", "-=",  "*=", NOSTR, NOSTR, NOSTR,
	"<stdio.h>", "#define", "#include", "printf", NOSTR
};

const CARAC	SH =
{
	"#1", "&", ">>", "2>", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"esac", "fi", NOSTR
};

const CARAC	PASCAL =
{
	":=", "(*", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"var", "writeln", "readln", NOSTR
};

const CARAC	FORTRAN =
{
	NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"format", "subroutine", NOSTR
};

const CARAC	BASIC =
{
	"gosub", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"rem", NOSTR
};

const CARAC	ASSEMBLER =
{
	"\n|*", "\n\t.", "\n\tmov", "$:", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	NOSTR
};

const CARAC	MAKEFILE =
{
	":\t", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	NOSTR
};

const CARAC	INGLES =
{
	"th", "wh", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"have", "is", "are", "take", NOSTR
};

const CARAC	PORTUGUES =
{
	"�o", "�e", "lh", "�", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"de", "que", "para", NOSTR
};

const CARAC	FRANCES =
{
	NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"est", "et", "un", "il", "suis", "ont", "sont", NOSTR
};

const CARAC	ALEMAO =
{
	"sch", NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR, NOSTR,
	"ist", "ich", NOSTR
};

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		analysis_begin (const char *);
int		language_analysis (const CARAC *, int);
void		no_nl_print (char *);
void		help (void);

/*
 ****************************************************************
 *	Tenta identificar o conte�do de um arquivo		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vNH")) != EOF)
	{
		switch (opt)
		{
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
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
		{ error ("Os argumentos sup�rfluos ser�o ignorados\n"); *argv = NOSTR; }

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR)		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (512);

		while (fngets (area, 512, stdin) != NOSTR)
			analysis_begin (area);
	}
	else
	{
		/*
		 *	Foram dados argumentos
		 */
		for (/* vazio */; *argv; argv++)
			analysis_begin (*argv);
	}

	return (exit_code);

}	/* end file */

/*
 ****************************************************************
 *	Inicia a an�lise de um arquivo				*
 ****************************************************************
 */
void
analysis_begin (const char *filenm)
{
	char		*cp;
	int		fd, sz;
	STAT		s;

	/*
	 *	Inicialmente, obt�m o estado do arquivo
	 */
	printf ("\"%s\": \t", filenm);

	if (stat (filenm, &s) < 0)
	{
		printf ("N�o consegui obter o estado (%s)\n", strerror (errno));
		exit_code++;
		return;
	}

	switch (s.st_mode & S_IFMT)
	{
	    case S_IFREG:
		break;

	    case S_IFDIR:
		printf ("� um diret�rio\n");
		return;

	    case S_IFIFO:
		printf ("� um FIFO\n");
		return;

	    case S_IFBLK:
		printf ("� um arquivo especial de blocos (estruturado)\n");
		return;

	    case S_IFCHR:
		printf ("� um arquivo especial de caracteres (n�o-estruturado)\n");
		return;

	    default:
		printf ("� um arquivo de TIPO INV�LIDO\n");
		exit_code++;
		return;

	}	/* end switch */

	/*
	 *	S� sobrou o regular
	 */
	if (s.st_size == 0)
	{
		printf ("� um arquivo regular vazio\n");
		return;
	}

	if ((fd = open (filenm, O_RDONLY)) < 0)
	{
		printf ("N�o consegui abrir (%s)\n", strerror (errno));
		exit_code++;
		return;
	}

	if ((sz = read (fd, area_seq, AREASZ)) < 0)
	{
		printf ("N�o consegui ler (%s)\n", strerror (errno));
		exit_code++;
		close (fd);
		return;
	}

	close (fd);

	/*
	 *	Verifica se � um m�dulo objeto
	 */
	if (sz >= sizeof (HEADER))
	{
		int		magic = ((HEADER *)area_seq)->h_magic;

		if   (magic == FMAGIC || magic == NMAGIC)
		{
			printf ("� um m�dulo objeto\n");
			return;
		}
		elif (magic == SMAGIC)
		{
			printf ("� uma biblioteca compartilhada\n");
			return;
		}
	}

	/*
	 *	Identifica a �rea de palavras em tokens e separadores
	 */
	memset (area_seq + sz, '\0', AREASZ - sz);

	for (cp = area_seq; cp < area_seq + sz; cp++)
		*cp = tolower (*cp);

	memcpy (area_word, area_seq, AREASZ);

	for (cp = area_word; cp < area_word + sz; cp++)
	{
		switch (*cp)
		{
		    case ' ':
		    case '\n':
		    case '\t':
		    case ')':
		    case '(':
		    case ';':
		    case ',':
		    case ':':
			*cp = '\0';
		}
	}

	/*
	 *	Tenta as v�rias linguagens
	 */
	if (language_analysis (&SROFF, sz))
	{
		printf ("Aparentemente � um arquivo fonte para o SROFF\n");
		return;
	}

	if (language_analysis (&C, sz))
	{
		printf ("Aparentemente � um programa em \"C\"\n");
		return;
	}

	if (language_analysis (&SH, sz))
	{
		printf ("Aparentemente � um arquivo de comandos para o SH\n");
		return;
	}

	if (language_analysis (&PASCAL, sz))
	{
		printf ("Aparentemente � um programa em PASCAL\n");
		return;
	}

	if (language_analysis (&FORTRAN, sz))
	{
		printf ("Aparentemente � um programa em FORTRAN\n");
		return;
	}

	if (language_analysis (&BASIC, sz))
	{
		printf ("Aparentemente � um programa em BASIC\n");
		return;
	}

	if (language_analysis (&ASSEMBLER, sz))
	{
		printf ("Aparentemente � um programa em ASSEMBLY\n");
		return;
	}

	if (language_analysis (&MAKEFILE, sz))
	{
		printf ("Aparentemente � um MAKEFILE\n");
		return;
	}

	if (language_analysis (&INGLES, sz))
	{
		printf ("Aparentemente � um texto em INGLES\n");
		return;
	}

	if (language_analysis (&PORTUGUES, sz))
	{
		printf ("Aparentemente � um texto em PORTUGU�S\n");
		return;
	}

	if (language_analysis (&FRANCES, sz))
	{
		printf ("Aparentemente � um texto em FRANC�S\n");
		return;
	}

	if (language_analysis (&ALEMAO, sz))
	{
		printf ("Aparentemente � um texto em ALEM�O\n");
		return;
	}

	printf ("N�o consegui identificar\n");

}	/* end analysis_begin */

/*
 ****************************************************************
 *	Analisa uma linguagem					*
 ****************************************************************
 */
int
language_analysis (const CARAC *lp, int sz)
{
	char	* const	*cpp;
	char		*cp;
	char		c;
	int		n;

	/*
	 *	Procura palavras caracter�sticas
	 */
	for (cp = area_word; cp < area_word + sz; cp++)
	{
		if (*cp == '\0')
			continue;

		for (cpp = lp->c_word; *cpp != NOSTR; cpp++)
		{
			if (streq (cp, *cpp))
			{
				if (vflag)
					no_nl_print (*cpp);

				return (1);
			}
		}

		cp = strend (cp) - 1;
	}

	/*
	 *	Procura seq��ncias caracter�sticas
	 */
	for (cpp = lp->c_seq; *cpp != NOSTR; cpp++)
	{
		c = **cpp;	n = strlen (*cpp);

		for (cp = area_seq; cp < area_seq + sz; cp++)
		{
			if (*cp != c)
				continue;

			if (strncmp (cp, *cpp, n) == 0)
			{
				if (vflag)
					no_nl_print (*cpp);
				return (1);
			}
		}
	}

	return (0);

}	/* end language_analysis */

/*
 ****************************************************************
 *	Imprime um texto, sem os <nl>				*
 ****************************************************************
 */
void
no_nl_print (char *cp)
{
	printf ("(\"");

	for (/* vazio */; *cp != '\0'; cp++)
	{
		if (*cp == '\n')
			printf ("\\n");
		else
			putchar (*cp);
	}

	printf ("\") ");

}	/* end no_nl_print */

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
		"%s - tenta identificar o conte�do de um arquivo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-vN] [<arquivo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: Indica o elemento l�xico que possibilitou a identifica��o\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados argumentos\n"
	);

	exit (2);

}	/* end help */
