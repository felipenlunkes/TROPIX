/*
 ****************************************************************
 *								*
 *			size.c					*
 *								*
 *	Imprime tamanhos e caracter�sticas de m�dulos objeto	*
 *								*
 *	Vers�o	1.0.0, de 04.02.86				*
 *		4.6.0, de 11.08.04				*
 *								*
 *	M�dulo: size						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <a.out.h>
#include <time.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.6.0, de 11.08.04";

#define	elif	else if

entry int	sflag;		/* In�cio da se��o */
entry int	vflag;		/* Verbose */
entry int	cflag;		/* Common */
entry int	xflag;		/* N�meros em hexadecimal */
entry int	dflag;		/* data */
entry int	aflag;		/* Todos os arquivos */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		proc_file (const char *);
long		get_common_sz (const char *, HEADER *, int);
void		header_endian_conversion (HEADER *);
void		help (void);

/*
 ****************************************************************
 *	Programa principal					*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, ret = 0;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "sdcxavNH")) != EOF)
	{
		switch (opt)
		{
		    case 's':			/* In�cio */
			sflag++;
			break;

		    case 'd':			/* Data */
			dflag++;
			break;

		    case 'c':			/* Common */
			cflag++;
			break;

		    case 'x':			/* Hexadecimal */
			xflag++;
			break;

		    case 'a':			/* Examina todos arquivos */
			aflag++;
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

	/*
	 *	Imprime titulo
	 */
	printf ("MACH TIPO TS RL  VER  FLAG ");

	if (!sflag)
		printf ("    TEXTO      DATA");
	else
		printf ("--TEXTO--  --DATA--");

	printf ("     BSS%s   TOTAL", cflag ? "  COMMON   REFTB" : "");

#if (0)	/*******************************************************/
	printf
	(	"MACH TIPO TS RL  VER  FLAG     TEXTO      DATA     BSS%s   TOTAL",
		cflag ? "  COMMON   REFTB" : ""
	);
#endif	/*******************************************************/

	if (dflag)
		printf (" --------- DATA --------- ");

	printf ("\n");

	/*
	 *	Analisa os <nomes>
	 */
	if   (Nflag)
	{
		char		*area = alloca (1024);

		if (*argv != NOSTR)
			error ("Os argumentos sup�rfluos ser�o ignorados");

		while (fngets (area, 1024, stdin) != NOSTR)
			ret += proc_file (area);
	}
	elif (*argv != NOSTR)
	{
		for (/* vazio */; *argv; argv++)
			ret += proc_file (*argv);
	}
	else
	{
		ret += proc_file ("a.out");
	}

	return (ret);

}	/* end main */

/*
 ****************************************************************
 *	Imprime o tamanho de um arquivo objeto			*
 ****************************************************************
 */
int
proc_file (const char *mod_nm)
{
	int		fd;
	long		csize = 0;
	HEADER		h;
	STAT		s;

	/*
	 *	Abre o arquivo
	 */
	if ((fd = open (mod_nm, O_RDONLY)) < 0)
		{ error ("*N�o consigo abrir \"%s\"", mod_nm); return (1); }

	/*
	 *	Le o cabe�alho do arquivo
	 */
	if ((read (fd, &h, sizeof (HEADER))) != sizeof (HEADER))
	{
		close (fd);

		if (aflag)
		{
			error ("\"%s\" n�o � um m�dulo objeto\n", mod_nm);
			return (1);
		}

		return (0);
	}

	/*
	 *	Verifica se � um <m�dulo> objeto
	 */
	if (h.h_magic != FMAGIC && h.h_magic != NMAGIC && h.h_magic != SMAGIC)
	{
		close (fd);

		if (aflag)
		{
			error ("\"%s\" n�o � um m�dulo objeto\n", mod_nm);
			return (1);
		}

		return (0);
	}

	/*
	 *	Se � um programa reeentrante, obt�m o estado
	 */
	if (h.h_magic == NMAGIC && fstat (fd, &s) < 0)
	{
		error ("*N�o consegui obter o estado de \"%s\"", mod_nm);
		close (fd);
		return (1);
	}

	/*
	 *	Se foi pedido o tamanho do COMMON, ...
	 */
	if (cflag)
		csize = get_common_sz (mod_nm, &h, fd);

	close (fd);

	/*
	 *	Imprime a M�quina
	 */
	fprintf (stdout, "%04X ", h.h_machine);

	/*
	 *	Imprime se � reentrante
	 */
	if   (h.h_magic == FMAGIC)
	{
		fprintf (stdout, " .   ");
	}
	elif (h.h_magic == SMAGIC)
	{
		fprintf (stdout, " s   ");
	}
	elif (s.st_mode & S_IMETX)
	{
		fprintf (stdout, " n,m ");
	}
	elif (s.st_mode & S_ISVTX)
	{
		fprintf (stdout, " n,t ");
	}
	else
	{
		fprintf (stdout, " n   ");
	}

	/*
	 *	Imprime se tem tabela de s�mbolos
	 */
	if (h.h_ssize == 0)
		fprintf (stdout, " . ");
	else
		fprintf (stdout, " * ");

	/*
	 *	Imprime se tem reloca��o
	 */
	if (h.h_rtsize == 0  &&  h.h_rdsize == 0)
		fprintf (stdout, " . ");
	else
		fprintf (stdout, " * ");

	/*
	 *	Imprime a vers�o
	 */
	fprintf (stdout, "%4d ", h.h_version);
#if (0)	/*******************************************************/
	fprintf (stdout, "%d.%d ",  MAJOR (h.h_version), MINOR (h.h_version));
#endif	/*******************************************************/

	/*
	 *	Imprime os indicadores
	 */
	printf (" %04X", h.h_flags);

	/*
	 *	Imprime os tamanhos ou in�cios
	 */
	if (sflag)
		printf (" %P %P", h.h_tstart,  h.h_dstart);
	else
		printf (xflag ? " %9X %9X" : " %9d %9d", h.h_tsize,  h.h_dsize);

	printf (xflag ? "%8X" : "%8d", h.h_bsize);

	if (cflag)
		printf (xflag ? "%8X%8X" : "%8d%8d", csize, h.h_refsize);

	printf (xflag ? "%8X " : "%8d ", h.h_tsize + h.h_dsize + h.h_bsize);

	/*
	 *	Imprime a data
	 */
	if (dflag)
		printf ("%-24.24s ", btime (&h.h_time));

	/*
	 *	Imprime o nome do arquivo
	 */
	fprintf (stdout, "%s\n", mod_nm);

	return (0);

}	/* proc_file */

/*
 ****************************************************************
 *	Obt�m o tamanho do COMMON				*
 ****************************************************************
 */
long
get_common_sz (const char *mod_nm, HEADER *hp, int fd)
{
	SYM		*sp;
	long		csize = 0;
	SYM		*sym_tb, *end_sym_tb;
	int		sz;

	/*
	 *	Aloca mem�ria e le a tabela de s�mbolos
	 */
	if ((sz = hp->h_ssize) == 0)
	{
		/*
		 *	Se n�o tem tabela de s�mbolos, n�o tem COMMON ... 
		 */
#if (0)	/*************************************/
		error ("\"%s\" n�o tem tabela de s�mbolos\n", mod_nm);
#endif	/*************************************/

		return (0);
	}

#if (0)	/*******************************************************/
	if (sz % sizeof (SYM))
	{
		error ("A Tabela de s�mbolos de \"%s\" tem tamanho inv�lido\n",	mod_nm);

		return (0);
	}
#endif	/*******************************************************/

	sym_tb = alloca (sz);

	lseek (fd, sizeof (HEADER) + hp->h_tsize + hp->h_dsize, L_SET);

	if (read (fd, sym_tb, sz) != sz)
	{
		error ("*Erro na leitura da tabela de s�mbolos de \"%s\"", mod_nm);
		return (0);
	}

	/*
	 *	Percorre toda a tabela de s�mbolos
	 *
	 *	Repare a codifica��o estranha do COMMON
	 */
	for
	(	sp = sym_tb, end_sym_tb = (SYM *)((int)sp + sz);
		sp < end_sym_tb;
		sp = SYM_NEXT_PTR (sp)
	)
	{
		if (sp->s_type == UNDEF || sp->s_type == (UNDEF|EXTERN))
			csize += sp->s_value;
	}

	if (sp != end_sym_tb)
		error ("Defasamento na tabela de s�mbolos de \"%s\"", mod_nm);

	return (csize);

}	/* end get_common_sz */

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
		"%s - imprime tamanhos e caracter�sticas de m�dulos objeto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-sdcxaN] [<m�dulo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-s: Imprime os in�cios ao inv�s dos tamanhos das se��es\n"
		"\t-d: Imprime tamb�m a data de gera��o do <m�dulo>\n"
		"\t-c: Imprime tamb�m o tamanho das se��es COMMON e REFTB\n"
		"\t-x: Os tamanhos s�o dados em hexadecimal\n"
		"\t-a: Informa sobre arquivos que n�o s�o m�dulos objeto\n"
		"\t-N: L� os nomes dos <m�dulos> de \"stdin\"\n"
	);

	exit (2);

}	/* end help */
