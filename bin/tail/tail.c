/*
 ****************************************************************
 *								*
 *			tail.c					*
 *								*
 *	Obt�m a parte final de um arquivo			*
 *								*
 *	Vers�o	2.3.0, de 30.12.90				*
 *		3.0.0, de 12.07.97				*
 *								*
 *	M�dulo: tail						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 12.07.97";

#define	DEF_CHAR 'l'		/* Normalmente linhas */
#define	DEF_OFF	10		/* Normalmente 10 antes do final */

#define	ASZ	(4*1024)	/* Tamanho da �rea de busca do arquivo */

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	STDOUT	1

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	fflag;		/* Malha de leitura */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
void		new_lines_loop (const char *, STAT *, FILE *);

/*
 ****************************************************************
 *	Obt�m a parte final de um arquivo			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int		opt;
	register off_t		count = 0;
	register FILE		*fp;
	register char		*cp = NOSTR;
	register int		b_off  = -DEF_OFF;
	int			b_char = DEF_CHAR;
	const char		*str, *b_str = NOSTR;
	STAT			s;
	char			area[ASZ];

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "b:fvH")) != EOF)
	{
		switch (opt)
		{
		    case 'b':			/* Defini��o do come�o */
			b_str = optarg;
			break;

		    case 'f':			/* Malha de leitura */
			fflag++;
			break;

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

	/*
	 *	Verifica o n�mero de argumentos
	 */
	argv += optind;
	argc -= optind;

	if (argc > 1)
		help ();

	/*
	 *	Analisa a op��o "-b"
	 */
	if (b_str)
	{
		b_off = strtol (b_str, &str, 0);

		if   (b_off == 0)
			b_off = -DEF_OFF;
		elif (b_off > 0)		/* Provis�rio */
			b_off = -b_off;

		if (str[0] != '\0')
		{
			b_char = str[0];

			if (str[1] != '\0')
			{
			    bad:
				fprintf
				(	stderr,
					"Ponto de c�pia inv�lido: \"%s\"\n\n",
					b_str
				);
				help ();
			}
		}
	}

	/*
	 *	Abre o arquivo
	 */
	if (argv[0] != NOSTR)
	{
		if ((fp = fopen (argv[0], "r")) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, argv[0], strerror (errno)
			);
			exit (1);
		}
	}
	else
	{
		fp = stdin;
	}

	/*
	 *	Examina o arquivo
	 */
	if (fstat (fileno (fp), &s) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			pgname, argv[0], strerror (errno)
		);
		exit (1);
	}

	if (fp != stdin && !S_ISREG (s.st_mode))
	{
		fprintf
		(	stderr,
			"%s: O arquivo \"%s\" n�o � regular\n",
			pgname, argv[0]
		);
		exit (1);
	}

	/*
	 *	Consist�ncia da op��o "-f" 
	 */
	if (fflag  &&  fp == stdin)
	{
		fprintf
		(	stderr,
			"%s: A op��o \"-f\" n�o pode ser usada com a entrada padr�o\n",
			pgname
		);
		fflag = 0;
	}

	/*
	 *	L� o final do arquivo
	 */
	if (fp != stdin)
	{
		register off_t	n;

		if   (s.st_size < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui obter o tamanho de \"%s\"\n",
				pgname, argv[0]
			);
			exit (1);
		}
		elif (s.st_size == 0)
		{
			exit (0);
		}

		if (s.st_size > ASZ)
		{
			if (lseek (fileno (fp), s.st_size - ASZ, SEEK_SET) < 0)
			{
				fprintf
				(	stderr,
					"%s: Erro no seek de \"%s\" (%s)\n",
					pgname, argv[0], strerror (errno)
				);
				exit (1);
			}
			n = 0;
		}
		else
		{
			n = ASZ - s.st_size;
		}

		if ((count = read (fileno (fp), area + n, ASZ - n)) < 0)
		{
			fprintf
			(	stderr,
				"%s: Erro na leitura de \"%s\" (%s)\n",
				pgname, argv[0], strerror (errno)
			);
			exit (1);
		}
	}
	else	/* PIPE */
	{
		register short	c;
		register off_t	n = 0;
		char		prov_area[ASZ];

		for (cp = prov_area; (c = getchar ()) != EOF; /* veja abaixo */)
		{
			if (cp >= &prov_area[ASZ])
				cp = prov_area;

			*cp++ = c;	count++;
		}

		if (count > ASZ)
			count = ASZ;

		n = cp - prov_area;

		memmove (&area[ASZ - n], &prov_area[0], n);
		memmove (&area[0], &prov_area[n], ASZ - n);
	}

	/*
	 *	Procura as �ltimas por��es
	 */
	switch (b_char)
	{
	    case 'l':
		for (cp = &area[ASZ]; cp > &area[ASZ - count]; /* abaixo */)
		{
			if (*--cp == '\n')
			{
				if (b_off++ >= 0)
					{ cp++; break; }
			}
		}
		break;

	    case 'b':
		b_off *= BLSZ;
	    case 'c':
		if (b_off + count < 0)	/* Lembre-se: b_off < 0 */
			b_off = -count;
		if ((cp = &area[ASZ + b_off]) < &area[0])
			cp = &area[0];
		break;

	    default:
		goto bad;

	}	/* end switch */

	/*
	 *	Imprime as linhas
	 */
	write (STDOUT, cp, &area[ASZ] - cp);

	/*
	 *	Verifica se processa a malha de linhas adicionais
	 */
	if (fflag)
		new_lines_loop (argv[0], &s, fp);

	return (exit_code);

}	/* end tail */

/*
 ****************************************************************
 *	Malha de linhas adicionais				*
 ****************************************************************
 */
void
new_lines_loop (const char *filenm, STAT *sp, FILE *fp)
{
	register off_t	old_size, count;
	char		area[ASZ];

	for (EVER)
	{
		old_size = sp->st_size;

		sleep (1);

		if (fstat (fileno (fp), sp) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
				pgname, filenm, strerror (errno)
			);
			exit (1);
		}

		if (sp->st_size <= old_size)
			continue;

		if (lseek (fileno (fp), old_size, SEEK_SET) < 0)
		{
			fprintf
			(	stderr,
				"%s: Erro no seek de \"%s\" (%s)\n",
				pgname, filenm, strerror (errno)
			);
			exit (1);
		}

		if ((count = read (fileno (fp), area, ASZ)) < 0)
		{
			fprintf
			(	stderr,
				"%s: Erro na leitura de \"%s\" (%s)\n",
				pgname, filenm, strerror (errno)
			);
			exit (1);
		}

		write (STDOUT, area, count);

	}	/* end for ever */

}	/* new_lines_loop */

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
		"%s - obt�m a parte final de um arquivo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-b <n>[lbc]] [-f] [<arquivo>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-b: Inicia a parte final a <n> linhas (\"l\"), blocos (\"b\") ou\n"
		"\t    caracteres (\"c\") antes do final do <arquivo>.\n"
		"\t    (se a op��o n�o for dada, assume-se " XSTR (DEF_OFF) " linhas)\n"
		"\t-f: Entra em uma malha sem fim, lendo linhas adicionais\n"
		"\t    (de segundo em segundo)\n"
		"\nObs.:\tSe o <arquivo> n�o for dado, ser� lida a entrada padr�o\n"
	);

	exit (2);

}	/* end help */
