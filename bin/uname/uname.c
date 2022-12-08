/*
 ****************************************************************
 *								*
 *			uname.c					*
 *								*
 *	Imprime a identifica��o do sistema			*
 *								*
 *	Vers�o	1.0.0, de 09.02.86				*
 *		3.0.0, de 13.07.97				*
 *								*
 *	M�dulo: uname						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/utsname.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 13.07.97";

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
 *	Imprime a identifica��o do sistema			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	UTSNAME		uts;

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
	 *	Pequena consist�ncia
	 */
	if (argc > 0)
		help ();

	/*
	 *	Obt�m a identifica��o do sistema
	 */
	if (uname (&uts) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter a identifica��o do sistema (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Imprime a identifica��o do sistema (prosa)
	 */
	if (!vflag)
	{
		printf
		(	"%s %s - Vers�o %s de %s �s %s em um %s (%s)\n",
			uts.uts_sysname, 	uts.uts_systype,
			uts.uts_version, 	uts.uts_date,
			uts.uts_time, 		uts.uts_machine,
			uts.uts_nodename
		);

#ifdef	ICA
		printf
		(	"\nNo. de s�rie: %s,   Uso autorizado para: %s, %s\n",
			uts.uts_sysserno, 	uts.uts_customer,
			uts.uts_depto
		);
#endif	ICA

		exit (0);
	}

	/*
	 *	Imprime a identifica��o do sistema (estrutura)
	 */
	printf
	(	"sysname 	= %s\n"	/* Nome do Sistema */
		"systype 	= %s\n"	/* Tipo do Sistema */
		"nodename	= %s\n"	/* Nome do n� */
		"version 	= %s\n"	/* Vers�o */
		"date		= %s\n"	/* Data */
		"time		= %s\n"	/* Tempo */
		"machine 	= %s\n"	/* Computador */
		"customer	= %s\n"	/* Nome do Cliente */
		"depto		= %s\n"	/* Nome do Departamento */
		"sysserno	= %s\n",/* Numero de serie */

		uts.uts_sysname,	/* Nome do Sistema */
		uts.uts_systype,	/* Tipo do Sistema */
		uts.uts_nodename,	/* Nome do n� */
		uts.uts_version,	/* Vers�o */
		uts.uts_date,		/* Data */
		uts.uts_time,		/* Tempo */
		uts.uts_machine,	/* Computador */
		uts.uts_customer,	/* Nome do Cliente */
		uts.uts_depto,		/* Nome do Departamento */
		uts.uts_sysserno	/* Numero de serie do Sistema */
	);

	return (0);

}	/* end uname */

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
	 	"%s - imprime a identifica��o do sistema\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-v]\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: Formato da estrutura \"uts\"\n"
	);

	exit (2);

}	/* end help */
