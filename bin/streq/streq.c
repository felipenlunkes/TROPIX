/*
 ****************************************************************
 *								*
 *			streq.c					*
 *								*
 *	Testa a igualdade de 2 cadeias de caracteres		*
 *								*
 *	Vers�o	3.0.0, de 11.05.93				*
 *		3.0.0, de 11.05.93				*
 *								*
 *	M�dulo: streq						*
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
#include <string.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.0, de 11.05.93";

#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Testa a igualdade de 2 cadeias de caracteres		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	register int	opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
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

	if (argc != 2)
		exit (1);

	if (streq (argv[0], argv[1]))
		exit (0);

	return (1);

}	/* end streq */

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
		"%s - testa a igualdade de 2 cadeias de caracteres\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <cadeia_1> <cadeia_2>\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
