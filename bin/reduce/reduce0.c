/*
 ****************************************************************
 *								*
 *			reduce0.c				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.0, de 27.08.90				*
 *		2.3.4, de 14.01.91				*
 *								*
 *	M�dulo: reduce						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <signal.h>
#include <string.h>

#include "reduce.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	2.3.4, de 14.01.91";

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	rflag;		/* N�o gera/confere CRCs */
entry int	uflag;		/* Uncompress */
entry int	fflag;		/* Force */
entry int	vflag;		/* Verbose */
entry int	tflag;		/* Tabela */
entry int	dflag;		/* Debug */
entry int	cflag;		/* Imprime os c�digos */

entry long	in_cnt, out_cnt; /* Total de caracteres de entrada/sa�da */

entry const char *in_nm, *out_nm; /* Nomes dos arquivos */

entry int	code_area[NC];	/* Cabem sempre NC c�digos at� de 16 bits */

entry R_HEADER	r_header;	/* O cabe�alho */

/*
 ****** Par�metros de compress�o ********************************
 */
entry int	MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

entry int	MAX_BIT_USED;	/* N�mero de bits realmente usados */ 

entry int	MAX_CODE;	/* Nunca pode usar este c�digo */

entry int	CODE_SOURCE;	/* Fonte de novos c�digos */

entry int	TEST_POINT;	/* Pr�ximo teste de performance */

entry int	bit_sz;		/* Tamanho atual */

entry int	max_code;	/* �ltimo c�digo do tamanho atual */

/*
 ****************************************************************
 *   Comprime/expande um arquivo segundo o algoritmo LZW	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	char		*cp;
	const char	*str, *bit_sz_str = NOSTR;
	STAT		s;

#if (0)	/*******************************************************/
	/*
	 *	O nome do programa � o �ltimo do caminho
	 */
	if (str = strrchr (pgname = argv[0], '/'))
		pgname = str + 1;
#endif	/*******************************************************/

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "b:ruftvdcH")) != EOF)
	{
		switch (opt)
		{
		    case 'b':			/* No. m�ximo de bits */
			bit_sz_str = optarg;
			break;

		    case 'r':			/* N�o processa CRCs */
			rflag++;
			break;

		    case 'u':			/* Uncompress */
			uflag++;
			break;

		    case 'f':			/* Force */
			fflag++;
			break;

		    case 't':			/* Tabela */
			tflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'd':			/* Debug */
			dflag++;
			vflag++;
			break;
		    case 'c':			/* Imprime os c�digos */
			cflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Prepara o terminal para consultas
	 */
	if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui abrir \"/dev/tty\"\n",
			pgname
		);
		perror (pgname);
		exit (1);
	}

	/*
	 *	Prepara os sinais
	 */
	signal (SIGBUS,  getbuserror);
	signal (SIGSEGV, getbuserror);

	/*
	 *	Analisa as v�rias op��es
	 */
	argv += optind;
	argc -= optind;

	if (streq (pgname, "rcat"))
		uflag++;

	if (argc < 1  ||  argc > 2)
		help ();

	if (uflag  &&  bit_sz_str != NOSTR)
	{
		fprintf
		(	stderr,
			"%s: No. de bits ignorado: \"%s\"\n",
			pgname, bit_sz_str
		);

		bit_sz_str = NOSTR;
	}

	/*
	 *	A op��o "-b" pode ser dada tamb�m no ambiente
	 */
	if ((cp = (char *)getenv ("REDUCE")) == NOSTR)
		cp = "";

	for (cp = strtok (cp, ","); cp != NOSTR; cp = strtok (NOSTR, ","))
	{
		if (*cp >= '0'  &&  *cp <= '9')
		{
			if (!uflag  &&  bit_sz_str == NOSTR)
				bit_sz_str = cp;
		}
	}

	/*
	 *	Analisa o n�mero de bits
	 */
	if (bit_sz_str != NOSTR)
	{
		if
		(	(MAX_BIT_SZ = strtol (bit_sz_str, &str, 0)) < 9 ||
			MAX_BIT_SZ > 16 ||
			*str != '\0'
		)
		{
			fprintf
			(	stderr,
				"No. de bits inv�lido: \"%s\"\n\n",
				bit_sz_str
			);
			help ();
		}

	}	/* end if (bit_sz_str != NOSTR) */
	else
	{
		MAX_BIT_SZ = DEF_BIT_SZ;
	}

	/*
	 *	Analisa os arquivos
	 */
	if (streq (argv[0], "-") == 0)
	{
		if (freopen (argv[0], "r", stdin) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\"\n",
				pgname, argv[0]
			);
			perror (pgname);
			exit (1);
		}

		in_nm = argv[0];
	}
	else
	{
		in_nm = "stdin";
	}

	if (argv[1] != NOSTR)
	{
		if (!fflag && stat (argv[1], &s) >= 0 && S_ISREG (s.st_mode))
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe. Reescreve? (n): ",
				pgname, argv[1]
			);
	
			if (askyesno () <= 0)
				exit (1);
		}

		if (freopen (argv[1], "w", stdout) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\"\n",
				pgname, argv[1]
			);
			perror (pgname);
			exit (1);
		}

		out_nm = argv[1];
	}
	else
	{
		out_nm = "stdout";
	}

	/*
	 *	Executa a opera��o desejada
	 */
	if (uflag)
		unreduce ();
	else
		reduce ();

	return (exit_code);

}	/* end main */

/*
 ****************************************************************
 *	Imprime o fator de compress�o				*
 ****************************************************************
 */
void
printtotal (off_t orig, off_t comp, int flag)
{
	fprintf
	(	stderr,
		"Original = %d bytes, Comprimido = %d bytes, ",
		orig, comp
	);

	if (flag)
	{
		fprintf
		(	stderr,
			"Compress�o = (%s %%, %d)\n",
			editpercent (getpercent (orig - comp, orig)),
			MAX_BIT_USED
		);
	}
	else
	{
		fprintf
		(	stderr,
			"Compress�o = %s %%\n",
			editpercent (getpercent (orig - comp, orig))
		);
	}

}	/* end printtotal */

/*
 ****************************************************************
 *	Imprime a tabela					*
 ****************************************************************
 */
void
printtable (CODETB *codetb, int code_source)
{
	CODETB		*hp;
	int		omega_K;
	char		STACK[8000];
	char		*sp = STACK;

	for (omega_K = code_source--; omega_K >= FIRST_CODE; omega_K = code_source--)
	{
		fprintf (stderr, "%4d: \"", omega_K);

		while (omega_K >= FIRST_CODE) 
		{
			hp = &codetb[omega_K];

			*sp++ = hp->h_K;
			omega_K = hp->h_omega;
		}

		*sp++ = omega_K;

		while (sp-- > STACK)
		{
			if (*sp == '\n')
				putc ('.', stderr);
			else
				putc (*sp, stderr);
		}

		sp++;

		fprintf (stderr, "\"\n");
	}

}	/* end printtable */

/*
 ****************************************************************
 *	Intercepta os sinais					*
 ****************************************************************
 */
void
getbuserror (int signo, ...)
{
	fprintf
	(	stderr,
		"%s: %s\n"
		"%s: Provavelmente formato do arquivo de entrada "
		"\"%s\" inv�lido\n",
		pgname, sigtostr (signo), pgname, in_nm
	);

	exit (1);

}	/* end getbuserror */

/*
 ****************************************************************
 *	Edita uma percentagem					*
 ****************************************************************
 */
char *
editpercent (int quoc)
{
	static char	buf[8];
	char		*sinal;

	if (quoc < 0)
		{ sinal = "-"; quoc = -quoc; }
	else
		sinal = "";


	sprintf (buf, "%s%d.%02d", sinal, quoc / 100, quoc % 100);
	
	return (buf);

}	/* end editpercent */

/*
 ****************************************************************
 *	Calcula uma percentagem					*
 ****************************************************************
 */
int
getpercent (long numer, long denom)
{
	int		quoc;

	/*
	 *	Tenta evitar overflow
	 */
	if (numer > (0x7FFFFFFF / 10000))
		quoc = numer / (denom / 10000);
	else
		quoc = 10000 * numer / denom;

	return (quoc);

}	/* end percent */

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
		"%s - comprime/expande um arquivo segundo o algoritmo LZW\n",
		pgname
	);

	pgname = "reduce";

	fprintf
	(	stderr,
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-b <n>] [-rfv] <original> [<comprimido>]\n"
		"\t%s -u [-ft] <comprimido> [<original>]\n"
		"\t%ccat <comprimido> [<original>]\n",
		pgversion, pgname, pgname, pgname[0]
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-b: Utiliza c�digos de no m�ximo <n> bits "
			"(9 a 16, por omiss�o " xstr (DEF_BIT_SZ) ")\n"
		"\t-r: N�o gera/confere CRCs\n"
		"\t-f: O arquivo destino existente � reescrito silenciosamente\n"
		"\t-v: Imprime os totais de caracteres processados "
			"e o fator de compress�o\n"
		"\t-u: Opera��o de expans�o\n"
		"\t-t: Imprime a tabela de cadeias utilizada\n"

		"\nObs.:\tSe o nome do arquivo de entrada for \"-\" � lida "
		"a entrada padr�o.\n\tSe o arquivo de sa�da n�o for dado, "
		"ele � escrito na sa�da padr�o\n"
	);

	exit (1);

}	/* end help */
