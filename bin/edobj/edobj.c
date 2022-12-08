/*
 ****************************************************************
 *								*
 *			edobj.c					*
 *								*
 *	Editor de m�dulos objeto				*
 *								*
 *	Vers�o	2.3.0, de 27.07.90				*
 *		3.1.0, de 15.01.99				*
 *								*
 *	M�dulo: edobj						*
 *		Utilit�rios de edi��o				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.1.0, de 15.01.99";

#define	NOMEM	(char *)NULL
#define	elif	else if

#define	LINESZ	18		/* No. de bytes da linha */

#define	PSIZE	9		/* Tamanho do %P */

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	fflag;		/* Force */
entry int	pflag;		/* Padr�o */

entry int	OFFSET;		/* Deslocamento do in�cio da linha */

entry const char *nextp;	/* Usado por getescape */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		line_print (const char *, int, int, const char *, int);
int		getescape (const char *);
int		CINDEX (const char *);
int		CHEX (const char *);
int		COCTAL (const char *);
int		putcntchar (int, int);
void		help (void);

/*
 ****************************************************************
 *	Depurador de m�dulos objeto				*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	int		fd;
	char		*mod1, *pp, *rp;
	const char	*cp;
	char		c;
	char		*mod0;
	const char	*pattern = NOSTR;
	char		*cadeia0, *cadeia1;
	int		size0 = 0, size1 = 0;
	int		n;
	int		vezes = 0;
	STAT		s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "fp:vH")) != EOF)
	{
		switch (opt)
		{
		    case 'f':			/* Force */
			fflag++;
			break;

		    case 'p':			/* Padr�o */
			pflag++;
			pattern = optarg;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			fputc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Consist�ncia dos argumentos 
	 */
	argv += optind;
	argc -= optind;

	if (argc == 0)
		exit (0);

	if (pflag != 1)
	{
		fprintf
		(	stderr,
			"� necess�rio dar uma e somente uma cadeia de "
			"busca/substitui��o\n\n"
		);
		help ();
	}

	if (argc > 1)
	{
		fprintf (stderr, "S� pode ser dado UM m�dulo objeto\n\n");
		help ();
	}

	/*
	 *	Prepara o terminal para consultas
	 */
	if (!fflag)
	{
		if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"/dev/tty\" (%s)\n",
				pgname, strerror (errno)
			);
			exit (1);
		}
	}

	/*
	 *	Resolve seq��ncia de "escapes" da cadeia0 (de busca)
	 */
	if ((cadeia0 = pp = malloc (strlen (cp = pattern) + 1)) == NOMEM)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui alocar mem�ria para a cadeia0\n",
			pgname
		);
		exit (1);
	}

	while (*cp != '\0')
	{
		if   (*cp == '\\')
		{
			*pp++ = getescape (++cp);
			cp = nextp;
		}
		elif (*cp == ':')
		{
			break;
		}
		else
		{
			*pp++ = *cp++;
		}

		size0++;
	}

	*pp = '\0';

	/*
	 *	Resolve seq��ncia de "escapes" da cadeia1 (de substitui��o)
	 */
	if (*cp == ':')
	{
		if ((cadeia1 = pp = malloc (strlen (pattern) + 1)) == NOMEM)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui alocar mem�ria para a cadeia1\n",
				pgname
			);
			exit (1);
		}

		cp++;	/* Pula o ":" */

		while (*cp != '\0')
		{
			if   (*cp == '\\')
			{
				*pp++ = getescape (++cp);
				cp = nextp;
			}
			else
			{
				*pp++ = *cp++;
			}

			size1++;
		}

		*pp = '\0';

		if (size0 != size1)
		{
			fprintf
			(	stderr,
				"A cadeia de busca n�o tem o mesmo tamanho "
				"do que a de substitui��o (%d :: %d)\n\n",
				size0, size1
			);
			help ();
		}
	}
	else
	{
		cadeia1 = NOSTR;
		
	}	/* end if ":" */

	if (size0 == 0)
	{
		fprintf
		(	stderr,
			"Cadeia de busca/substitui��o sem caracteres?\n\n"
		);
		help ();
	}

	if (size0 > LINESZ - 2)
	{
		fprintf
		(	stderr,
			"As cadeias de busca/substitui��o n�o podem ter mais "
			"do que %d caracteres\n\n",
			LINESZ - 2
		);
		help ();
	}

	/*
	 *	L� o conte�do do arquivo
	 */
	if ((fd = open (argv[0], O_RDWR)) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui abrir \"%s\" (%s)\n",
			pgname, argv[0], strerror (errno)
		);
		exit (1);
	}

	if (fstat (fd, &s) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			pgname, argv[0], strerror (errno)
		);
		exit (1);
	}

	if (!S_ISREG (s.st_mode))
	{
		fprintf
		(	stderr,
			"%s: O arquivo \"%s\" n�o � regular\n",
			pgname, argv[0]
		);
		exit (1);
	}

	if ((mod0 = malloc (s.st_size)) == NOMEM)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui alocar mem�ria para \"%s\"\n",
			pgname, argv[0]
		);
		exit (1);
	}

	if (read (fd, mod0, s.st_size) != s.st_size)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui ler o arquivo \"%s\" (%s)\n",
			pgname, argv[0], strerror (errno)
		);
		exit (1);
	}

	mod1 = mod0 + s.st_size;

	/*
	 *	Procura o padr�o
	 */
	c = cadeia0[0];

	for (rp = mod0; rp < mod1; rp++)
	{
		if (rp[0] != c)
			continue;

		if (!memeq (rp, cadeia0, size0))
			continue;

		if (rp + size0 > mod1 + 1)
			continue;

		/*
		 *	Achou
		 */
		vezes++;

		OFFSET = (LINESZ - size0) / 2;

		if (OFFSET & 1)
			OFFSET--;

		rp -= OFFSET;

		if (rp + LINESZ > mod1)
			n = mod1 - rp;
		else
			n = LINESZ;

		line_print (rp, n, size0, mod0, 1 /* com zebra */);

		if (cadeia1 == NOSTR)
		{
			rp += OFFSET;
			continue;
		}

		/*
		 *	Substitui
		 */
		memcpy (rp + OFFSET, cadeia1, size1);

		line_print (rp, n, size1, mod0, 0 /* sem zebra */);

		rp += OFFSET;

		fprintf (stderr, "Deseja fazer a substitui��o? (n): ");

		if (fflag)
			fprintf (stderr, "SIM\n");
		else
			fflush (stderr);

		if (fflag || askyesno () > 0)
		{
			if (lseek (fd, rp - mod0, L_SET) < 0)
			{
				fprintf
				(	stderr,
					"%s: N�o consegui mover o ponteiro de "
					"posi��o do arquivo \"%s\" (%s)\n",
					pgname, argv[0], strerror (errno)
				);
				exit (1);
			}

			if (write (fd, rp, size1) != size1)
			{
				fprintf
				(	stderr,
					"%s: N�o consegui escrever a cadeia "
					"de substitui��o no arquivo \"%s\" (%s)\n",
					pgname, argv[0], strerror (errno)
				);
				exit (1);
			}

		}	/* if (quer substituir) */

	}	/* end for */

	if (fflag && vezes == 0)
	{
		fprintf
		(	stderr,
			"%s: A cadeia de busca \"%s\" n�o foi encontrada\n",
			pgname, cadeia0
		);
		exit_code++;
	}

	return (exit_code);

}	/* end edobj */

/*
 ****************************************************************
 *	Analisa Sequencias de Escape				*
 ****************************************************************
 */
int
getescape (const char *lp)
{
	int		c;

	/*
	 *	N�mero octal
	 */
	if (COCTAL (lp))
	{
		c = CINDEX (lp++);

		if (COCTAL (lp))
		{
			c = (c << 3) + CINDEX (lp++);

			if (COCTAL (lp))
				c = ((c << 3) + CINDEX (lp++)) & 0xFF;
		}

		nextp = lp;

		return (c);
	}

	/*
	 *	N�o � octal
	 */
	switch (*lp++)
	{
	    case 'a':
		c = 0x07;
		break;

	    case 'b':
		c = '\b';
		break;

	    case 'e':
		c = 0x1B;
		break;

	    case 'f':
		c = '\f';
		break;

	    case 'n':
		c = '\n';
		break;

	    case 'r':
		c = '\r';
		break;

	    case 't':
		c = '\t';
		break;

	    case 'v':
		c = 0x0B;
		break;

	    case 'x':
		if (CHEX (lp))
		{
			c = CINDEX (lp++);

			if (CHEX (lp))
			{
				c = (c << 4) + CINDEX (lp++);

				if (CHEX (lp))
					c = ((c << 4) + CINDEX (lp++)) & 0xFF;
			}

			nextp = lp;

			return (c);
		}

		/* cai atrav�s */

	    default:
		c = lp[-1];
		break;
	}

	nextp = lp;

	return (c);

}	/* end getescape */

/*
 ****************************************************************
 *	Verifica se um caractere � um d�gito octal		*
 ****************************************************************
 */
int
COCTAL (const char *lp)
{
	return (*lp >= '0' && *lp <= '7');

}	/* end COCTAL */

/*
 ****************************************************************
 *	Verifica se um caractere � um d�gito hexadecimal	*
 ****************************************************************
 */
int
CHEX (const char *lp)
{
	if (*lp >= '0' && *lp <= '9')
		return (1);

	if (*lp >= 'a' && *lp <= 'f')
		return (1);

	if (*lp >= 'A' && *lp <= 'F')
		return (1);

	return (0);

}	/* end CHEX */

/*
 ****************************************************************
 *	Obt�m o valor de um d�gito octal ou hexadecimal		*
 ****************************************************************
 */
int
CINDEX (const char *lp)
{
	if (*lp >= '0' && *lp <= '9')
		return (*lp - '0');

	if (*lp >= 'a' && *lp <= 'f')
		return (*lp - 'a' + 10);

	if (*lp >= 'A' && *lp <= 'F')
		return (*lp - 'A' + 10);

	return (0);

}	/* end CINDEX */

/*
 ****************************************************************
 *	Imprime uma linha					*
 ****************************************************************
 */
void
line_print (const char *dump, int count, int size, const char *begin, int zebra)
{
	const char 	*cp;
	int		c, i, total = 0;
	int		odd = 0;

	/*
	 *	Verifica se o endere�o � �mpar
	 */
	if ((int)dump & 1)
		{ dump--; odd++; }

	/*
	 *	P�e o endere�o
	 */
	printf ("%P:  ", dump - begin);

	/*
	 *	P�e a parte em HEXA
	 */
	for (i = 0; i < LINESZ; i++)
	{
		if ((i & 1) == 0)
			printf (" ");

		if (i < count)
			printf ("%02X", dump[i]);
		else
			printf ("  ");
	}

	printf ("   ");

	/*
	 *	Escreve caracteres em ascii
	 */
	for (cp = dump, i = 0; i < LINESZ && i < count; cp++, i++)
	{
		c = *cp;

		if (c < 0x20)
			c = '.';

		putchar (c);
	}

	fputc ('\n', stdout);

	/*
	 *	Imprime a ZEBRA Hexa
	 */
	if (!zebra)
		return;

	total += putcntchar (PSIZE + 4 + (OFFSET * 2) + (OFFSET / 2), ' ');

	if (odd)
		total += putcntchar (2, ' ');

	total += putcntchar (1, '|');

	total += putcntchar ((size * 2) + (size + 1) / 2 - 1 - 2, '/');

	if (odd && (size & 1) == 0)
		total += putcntchar (1, '/');

	total += putcntchar (1, '|');

	/*
	 *	Coloca o espa�o entre as zebras
	 */
	putcntchar (PSIZE + 4 + (LINESZ * 2) + (LINESZ / 2) - 1 + 3 - total, ' ');

	/*
	 *	Imprime a ZEBRA Iso
	 */
	for (i = 0; i < OFFSET; i++)
		fputc (' ', stdout);

	if (odd)
		fputc (' ', stdout);

	fputc ('|', stdout);

	for (i = 0; i < size - 2; i++)
		fputc ('/', stdout);

	if (size > 1)
		fputc ('|', stdout);

	fputc ('\n', stdout);

}	/* end line_print */

/*
 ****************************************************************
 *	Imprime uma seq��ncia de caracteres repetidos		*
 ****************************************************************
 */
int
putcntchar (int count, int c)
{
	int		i;

	for (i = 0; i < count; i++)
		fputc (c, stdout);

	return (count);

}	/* end putcntchar */

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
		"%s - editor de m�dulos objeto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-f] -p \"<busca>[:<substitui��o>]\" <mod>\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-f: Realiza a substitui��o sem consultar o usu�rio\n"
		"\t-p: Cadeias de <busca> e <substitui��o>\n"
		"\nObs.:\tSe n�o for dada a cadeia de <substitui��o>, "
			"ser� feita apenas a busca\n"
	);

	exit (2);

}	/* end help */
