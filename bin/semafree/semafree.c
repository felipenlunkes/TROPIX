/*
 ****************************************************************
 *								*
 *			semafree.c				*
 *								*
 *	Libera o sem�foro pelo qual o processo est� esperando	*
 *								*
 *	Vers�o	2.1.0, de 03.12.88				*
 *		3.0.0, de 30.06.97				*
 *								*
 *	M�dulo: semafree					*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/kcntl.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.0, de 30.06.97";

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
 *	Libera o sem�foro pelo qual o processo est� esperando	*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	int		opt, pid;
	const char	*str;

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
	 *	Retira o n�mero do processo
	 */
	if (argc != 1)
		help ();

	if ((pid = strtol (argv[0], &str, 0)) < 0 || *str != '\0')
	{
		fprintf
		(	stderr,
			"%s: N�mero de processo \"%s\" inv�lido\n",
			pgname, argv[0]
		);
		exit (1);
	}

	/*
	 *	Tenta liberar o recurso
	 */
	if (kcntl (K_SEMAFREE, pid) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui liberar o recurso (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	return (0);

}	/* end semafree */

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
		"%s - libera o sem�foro pelo qual o processo est� esperando\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-v] <pid>\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: verboso\n"
	);

	exit (2);

}	/* end help */
