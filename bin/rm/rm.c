/*
 ****************************************************************
 *								*
 *			rm.c					*
 *								*
 *	Remove arquivos						*
 *								*
 *	Vers�o	1.0.0, de 13.05.86				*
 *		4.2.0, de 02.05.02				*
 *								*
 *	M�dulo: rm						*
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
#include <unistd.h>
#include <stat.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 02.05.02";

entry int	vflag;		/* Verbose */
entry int	fflag;		/* op��o '-f' */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

const char	**color_vector;	/* Para as cores dos modos */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		remove (const char *);
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
	while ((opt = getopt (argc, argv, "fivNH")) != EOF)
	{
		switch (opt)
		{
		    case 'f':			/* For�a */
			fflag++;
			break;

		    case 'i':			/* Interativo */
			fflag = 0;
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
	 *	Prepara o terminal para consultas
	 */
	if (!fflag)
	{
		if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
			error ("$*N�o consegui abrir \"/dev/tty\"");

		askyesno_set (1);	/* Permite o modo "de for�a" */
	}

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stderr)), (void *)NULL, &color_vector);

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
		{ error ("Os argumentos sup�rfluos ser�o ignorados"); *argv = NOSTR; }

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR)		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
			ret += remove (area);
	}
	else				/* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
			ret += remove (*argv);
	}

	return (ret);

}	/* end main */	

/*
 ****************************************************************
 *	Analisa a  remo��o					*
 ****************************************************************
 */
int
remove (const char *file_nm)
{
	STAT		s;
	int		code, save_errno;

	/*
	 *	Obt�m o estado da fonte
	 */
	s.st_mode = 0;

	code = lstat (file_nm, &s);

	save_errno = errno;

	/*
	 *	Normalmente, questiona o usu�rio sobre a remo��o
	 */
	if (!fflag || vflag)
	{
		fprintf (stderr, "%c", modetostr (s.st_mode)[0]);

		if (S_ISREG (s.st_mode))
			fprintf (stderr, " %d", s.st_size);

		fprintf
		(	stderr,
			" %s%s%s",
			color_vector[(s.st_mode & S_IFMT) >> 12],
			file_nm,
			color_vector[MC_DEF]
		);

		if (code >= 0 && !fflag)
		{
			fprintf (stderr, "? (n): ");

			if (askyesno () <= 0)
				return (0);
		}
		else
		{
			fprintf (stderr, "\n");
		}
	}

	if (code < 0)
	{
		errno = save_errno;

		error ("*N�o consegui obter o estado de \"%s\"", file_nm);
		return (1);
	}

	if (S_ISDIR (s.st_mode))
	{
		error ("\"%s\" � um diret�rio", file_nm);
		return (1);
	}

	/*
	 *	Verifica possibilidade de remo��o
	 */
	if (!fflag && !S_ISLNK (s.st_mode) && access (file_nm, W_OK) < 0)
	{
		fprintf
		(	stderr,
			"%s: \"%s\" n�o tem permiss�o de escrita. Remove? (n): ",
			pgname, file_nm
		);

		if (askyesno () <= 0)
			return (0);
	}

	/*
	 *	Remove
	 */
	if (unlink (file_nm) < 0)
		{ error ("*N�o consegui remover \"%s\"", file_nm); return (1); }

	if (s.st_nlink-- > 1)
		error ("Ainda h� %d elo(s) f�sico(s) para \"%s\"", s.st_nlink, file_nm);

	return (0);

}	/* end remove */

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
		"%s - Remove arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-ifvN] [<arquivo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: Pede confirma��o do usu�rio para a remo��o "
			"de cada <arquivo>\n"
		"\t    (modo normal)\n"
		"\t-f: Remove o <arquivo> sem pedir confirma��o do usu�rio\n"
		"\t-v: Verboso\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados <arquivo>s\n"
	);

	exit (2);

}	/* end help */
