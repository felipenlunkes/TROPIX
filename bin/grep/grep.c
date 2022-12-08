/*
 ****************************************************************
 *								*
 *			grep.c					*
 *								*
 *	Procura por Express�es Regulares em Arquivos		*
 *								*
 *	Vers�o	1.0.0, de 21.01.87				*
 *		4.2.0, de 08.05.02				*
 *								*
 *	M�dulo: grep						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <a.out.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	LINESZ	1024	/* Tamanho de uma linha nos arquivos */
#define	MAXEXP	20	/* No. max. de expr. regulares */

#define	elif	else if

typedef	enum { NORMAL, COUNT, NUMBER, SILENT, LIST }	PRINT;

/*
 ******	Vari�veis ***********************************************
 */
entry const char	pgversion[] =  "Vers�o:	4.2.0, de 08.05.02";

entry char		mflag;		/* Ma�usculas e min�sculas iguais */
entry char		rflag;		/* Selecione as linhas SEM padr�es */
entry char		Nflag;		/* Nomes dos pgms no <stdin> */

entry PRINT		print = NORMAL;	/* Modo de mostrar a ocorr�ncia */

entry int		print_name;	/* Imprime ou n�o o nome do arquivo */

entry const char	*exp_list[MAXEXP+1]; /* Forma compilada das  expr. reg. */
entry int		nexpr = 0;	/* N�mero de expr. regulares */

entry int		exit_code = 1;	/* Valor para exit */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void			grep (const char *, FILE *);
int			isobj (FILE *);
char			*lower_conv (char *, const char *);
void			erro (void);
void			help (void);

/*
 ****************************************************************
 *	Procura por Express�es Regulares em Arquivos		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	const char	*op;
	char		*p;
	int		opt;
	FILE		*fp;

	/*
	 *	Leitura das Op��es e Argumentos
	 */
	while ((opt = getopt (argc, argv, "clnsmrNH")) != EOF)
	{
		switch (opt)
		{
		    case 'c':
			if (print == NORMAL)
				print = COUNT;
			else
				erro ();
			break;

		    case 'l':
			if (print == NORMAL)
				print = LIST;
			else
				erro ();
			break;

		    case 'n':
			if (print == NORMAL)
				print = NUMBER;
			else
				erro ();
			break;

		    case 's':
			if (print == NORMAL)
				print = SILENT;
			else
				erro ();
			break;

		    case 'm':			/* Mai�sculas e min�sculas iguais */
			mflag++;
			break;

		    case 'r':			/* Selecione linhas SEM os padr�es */
			rflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'H':
			help ();
			break;

		    case '?':
			putc ('\n', stderr);
			help ();
			break;

		}	/* end switch (opt) */

	}	/* end while getopt */

	argv += optind;

	/*
	 *	Separa��o das express�es regulares
	 */
	if ((op = *argv++) == NOSTR)
		help ();

	if (mflag)
		lower_conv ((char *)op, op);

	while ((p = strchr (op, '|')) != NOSTR  &&  nexpr < MAXEXP)
	{
		/*
		 *	Verifica se ocorr�ncia de "\|", sem ser de "\\|"
		 */
	    testfalseor:
		if (p > op + 1  &&  *(p - 1) == '\\')
		{
			if (*(p -2) != '\\')
			{
				if ((p = strchr (p + 1, '|')) != NOSTR)
					goto testfalseor;
				else
					break;
			}
		}

		*p = '\0';

		/*
		 *	Compila��o da Express�o Regular
		 */
		if ((exp_list[nexpr++] = regcmp (op)) == NOSTR)
			error ("$N�o consigo compilar \"%s\"", op);

		*p++ = '|'; op = p;
	}

	/*
	 *	Compila��o da Express�o Regular restante
	 */
	if ((exp_list[nexpr++] = regcmp (op)) == NOSTR)
			error ("$N�o consigo compilar \"%s\"", op);

	exp_list[nexpr] = NOSTR;

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag == 0)
	{
		if (*argv == NOSTR)
		{
		   /***	print_name = 0; ***/

			grep ("stdin", stdin);
			exit (exit_code);
		}
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
	if (*argv == NOSTR) 		 /* N�o foram dados argumentos: l� os nomes do "stdin" */
	{
		char		*area = alloca (1024);

		print_name++;

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if ((fp = fopen (area, "r")) == NOFILE)
			{
				error ("*N�o consigo abrir \"%s\"", area);
				exit_code = 2;
			}
			else
			{
				grep (area, fp);
				fclose (fp);
			}
		}
	}
	else 				 /* Foram dados argumentos */
	{
		if (argv[1])
			print_name++;

		for (/* vazio */; *argv; argv++)
		{
			if ((fp = fopen (*argv, "r")) == NOFILE)
			{
				error ("*N�o consigo abrir \"%s\"", *argv);
				exit_code = 2;
			}
			else
			{
				grep (*argv, fp);
				fclose (fp);
			}
		}
	}

	return (exit_code);

}	/* end main */

/*
 ****************************************************************
 *	Procura a Express�o Regular em um Arquivo		*
 ****************************************************************
 */
void
grep (const char *file_nm, FILE *fp)
{
	const char	**exp;
	int		number = 0;	/* Ordem da linha atual no arquivo atual */
	int		count = 0;	/* No. de linhas onde a expr. (n�o) ocorreu */
	int		ocount;
	char		*line_ptr;
	char		read_line[LINESZ], cmp_line[LINESZ], match[LINESZ];
	STAT		s;

	/*
	 *	Se o arquivo n�o for a entrada padr�o, ...
	 */
	if (fp != stdin)
	{
		if (fstat (fileno (fp), &s) < 0)
		{
			error ("*N�o consigo obter o estado de \"%s\"", file_nm);
			exit_code = 2;
			return;
		}	

		/*
		 *	Verifica se o arquivo � regular
		 */
		if ((s.st_mode & S_IFMT) != S_IFREG)
		{
			error ("\"%s\" n�o � um arquivo regular", file_nm);
			exit_code = 2;
			return;
		}	

		/*
		 *	Testa se � um programa objeto apenas se n�o
		 *	for "stdin", pois n�o podemos dar "rewind" em um pipe
		 */
		if (isobj (fp))
		{
			error ("\"%s\" � um programa objeto", file_nm);
			exit_code = 2;
			return;
		}
	}

	/*
	 *	L� as linhas do arquivo
	 */
	while (fngets (read_line, LINESZ, fp) != NOSTR)
	{
		number++; ocount = count;

		if (mflag)
			line_ptr = lower_conv (cmp_line, read_line);
		else
			line_ptr = read_line;

		for (exp = exp_list; *exp != NOSTR; exp++)
		{
			if (regex (*exp, line_ptr, match) != NOSTR)
			{
				if (!rflag)
					count++;
			}
			else
			{
				if (rflag)
					count++;
			}
		}

		if (count > ocount)
		{
			switch (print)
			{
			    case NORMAL:
				if (print_name)
					printf ("%s:\t%s\n", file_nm, read_line);
				else
					printf ("%s\n", read_line);
				break;

			    case NUMBER:
				printf
				(	"%s (%d):\t%s\n", file_nm,
					number,
					read_line
				);
				break;

			    case LIST:
				puts (file_nm);
				return;

			    default:
				break;
			}
		}

	}	/* end while fngets */

	if (print == COUNT)
		printf ("%s:\t%d\n", file_nm, count);

	if (exit_code == 1)
	{
		if   (!rflag && count > 0)
			exit_code = 0;
		elif (rflag && count < number)
			exit_code = 0;
	}

}	/* end grep */

/*
 ****************************************************************
 *	Testa se o arquivo � objeto				*
 ****************************************************************
 */
int
isobj (FILE *fp)
{
	HEADER		h;
	int		magic;

	if ((fread (&h, sizeof (HEADER), 1, fp)) == 1)
	{
		magic = h.h_magic;

		if (magic == FMAGIC || magic == NMAGIC || magic == SMAGIC)
			return (1);
	}

	rewind (fp);

	return (0);

}	/* end isobj */

/*
 ****************************************************************
 *	Converte uma cadeia para min�scula			*
 ****************************************************************
 */
char *
lower_conv (char *cmp_line, const char *read_line)
{
	int		c;
	const char	*bp;
	char		*cp;

	for (bp = read_line, cp = cmp_line; (c = *bp) != '\0'; bp++, cp++)
		*cp = tolower (c);

	*cp = '\0';

	return (cmp_line);

}	/* lower_conv */

/*
 ****************************************************************
 *	Aborta quando as op��es s�o mutuamente exclusivas	*
 ****************************************************************
 */
void
erro (void)
{
	error ("$Op��es mutuamente exclusivas");

}	/* end erro */

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
		"%s - busca de padr�es em arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-clnsmrN] <padr�o>[|<padr�o> ...] [<arquivo> ...]\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Imprime as linhas selecionadas\n"
		"\t-c: Conta as linhas selecionadas\n"
		"\t-l: Lista os nomes dos arquivos contendo linhas selecionadas\n"
		"\t-n: Precede � linha, o seu n�mero\n"
		"\t-s: Modo silencioso, apenas o c�digo de ret�rno\n"
		"\t-m: Trata ma�sculas e min�sculas como iguais\n"
		"\t-r: Seleciona as linhas que n�o cont�m "
			"nenhum dos padr�es\n"
		"\t-N: L� os nomes dos arquivos de \"stdin\".\n"
		"\t    Se n�o forem dados arquivos, nem a op��o \"-N\",\n"
		"\t    o conte�do do arquivo ser� lido de \"stdin\"\n"
		"\nObs.:\tAs op��es \"c\", \"l\", \"n\" e \"s\" "
		"s�o mutuamente exclusivas\n"
	);

	exit (2);

}	/* end help */
