/*
 ****************************************************************
 *								*
 *			pwd.c					*
 *								*
 *	Imprime o diret�rio corrente				*
 *								*
 *	Vers�o	1.0.0, de 04.04.86				*
 *		3.0.1, de 28.07.97				*
 *								*
 *	M�dulo: pwd						*
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
const char	pgversion[] =  "Vers�o:	3.0.1, de 28.06.97";

#define	elif	else if

#define		PWDNMSZ		512

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Imprime o diret�rio corrente				*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	char		*pwd;

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

	/*
	 *	Obt�m o diret�rio corrente
	 */
	if ((pwd = getcwd (NOSTR, PWDNMSZ)) == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o nome do diret�rio corrente (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Imprime o diret�rio corrente
	 */
	printf ("%s\n", pwd);

	return (0);

}	/* end pwd */

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
		"%s - imprime o diret�rio corrente\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
