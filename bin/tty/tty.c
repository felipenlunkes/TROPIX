/*
 ****************************************************************
 *								*
 *			tty.c					*
 *								*
 *	Imprime o nome do terminal/v�deo			*
 *								*
 *	Vers�o	2.0.0, de 20.01.87				*
 *		3.0.0, de 13.07.97				*
 *								*
 *	M�dulo: tty						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.0, de 13.07.97";

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	sflag;		/* Silence */
entry int	vflag;		/* Verboso */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Imprime o nome do terminal/v�deo			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	const char	*tty_name;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "svH")) != EOF)
	{
		switch (opt)
		{
		    case 's':			/* Modo silencioso */
			sflag++;
			break;

		    case 'v':			/* Verboso */
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
	 *	Modo silencioso
	 */
	if (sflag)
	{
		int	code = isatty (0) ? 0 : 1;

		if (vflag)
			printf ("C�digo de retorno = %d\n", code);

		exit (code);
	}

	/*
	 *	Obt�m o nome do terminal
	 */
	if ((tty_name = ttyname (2)) == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: Terminal/v�deo desconhecido\n",
			pgname
		);
		exit (1);
	}

	printf ("%s\n", tty_name);

	return (0);

}	/* end tty */

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
		"%s - imprime o nome do terminal/v�deo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-s]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-s: Fornece apenas o c�digo de retorno\n"
		"\t    (0 se \"stdin\" � um terminal, 1 em caso contr�rio)\n"
	);

	exit (2);

}	/* end help */
