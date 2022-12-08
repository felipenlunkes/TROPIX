/*
 ****************************************************************
 *								*
 *			nice.c					*
 *								*
 *	Executa um comando com prioridade modificada		*
 *								*
 *	Vers�o	1.0.0, de 30.07.87				*
 *		3.0.0, de 01.06.97				*
 *								*
 *	M�dulo: nice						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 01.06.97";

#define	DEFINC	10		/* Incremento padr�o */
#define	MAXINC	20		/* Incremento m�ximo */

#define	elif	else if

#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Executa um comando com prioridade modificada		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int		opt;
	register const char	*cp;
	const char		*inc_str = NOSTR;
	register int		incr = DEFINC;
	int			plus = 0;
	const char		*str;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "p:vH")) != EOF)
	{
		switch (opt)
		{
		    case 'p':			/* Incremento dado */
			if (inc_str)
				help ();
			inc_str = optarg;
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

	argv += optind;
	argc -= optind;

	/*
	 *	Analisa o incremento dado
	 */
	if ((cp = inc_str) != NOSTR)
	{
		if   (cp[0] == '+')
			{ plus++; cp++; }
		elif (cp[0] == '-')
			{ cp++; }

		incr = strtol (cp, &str, 0);

		if (*str != '\0' || (unsigned)incr > MAXINC)
		{
			fprintf
			(	stderr,
				"Incremento inv�lido: \"%s\"\n\n",
				inc_str
			);
			help ();
		}

		if (plus)
			incr = -incr;

	}	/* end if (inc_str != NOSTR) */

	/*
	 *	Altera a prioridade
	 */
	if (argv[0] == NOSTR)
		help ();

	if (nice (incr) < 0)
	{
		fprintf
		(	stderr,
			"%s: Erro na chamada ao sistema \"nice\" (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Executa o comando dado
	 */
	execvp (argv[0], &argv[0]);

	fprintf
	(	stderr,
		"%s: N�o consegui executar \"%s\" (%s)\n",
		pgname, argv[0], strerror (errno)
	);

	return (2);

}	/* end nice */

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
		"%s - executa um comando com prioridade modificada\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-p [+]<inc>] <comando> [<op��es>] [<argumentos>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-p: Decrementa a prioridade de <inc> "
			"(ao inv�s de " XSTR (DEFINC) ").\n"
		"\t    Usando o \"+\", a prioridade ser� "
			"incrementada de <inc>\n"
		"\t    (somente para superusu�rios)\n"
		"\nObs.:\tO valor de <inc> deve ser no m�ximo " XSTR (MAXINC)
			"\n"
	);

	exit (2);

}	/* end help */
