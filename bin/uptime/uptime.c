/*
 ****************************************************************
 *								*
 *			uptime.c				*
 *								*
 *	Fornece o tempo decorrido desde o �ltimo "boot"		*
 *								*
 *	Versao	1.0.0, de 09.02.87				*
 *		3.0.1, de 14.07.97				*
 *								*
 *	M�dulo: uptime						*
 *		Utilit�rios administrativos			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/times.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.1, de 14.07.97";

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
 *	Fornece o tempo decorrido desde o �ltimo "boot"		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int		opt;
	int			dias, hor, min, seg; 
	time_t			boot_time;
	TMS			tms;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vNH")) != EOF)
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

	/*
	 *	Pequena consist�ncia
	 */
   /***	argv += optind; ***/
	argc -= optind;

	if (argc > 0)
		help ();

	/*
	 *	Obt�m o tempo decorrido
	 */
	if ((seg = times (&tms)) < 0)
	{
		fprintf
		(	stderr,
			"%s: Erro na chamada \"times\" (%s)\n",
			strerror (errno)
		);
		exit (1);
	} 

	/*
	 *	Obt�m a hora do "boot"
	 */
	boot_time = time ((time_t *)NULL) - seg;

	/*
	 *	Calcula o tempo decorrido em dias, horas, ...
	 */
	min  = seg / 60;
	seg  = seg % 60;

	hor  = min / 60;
	min  = min % 60;

	dias = hor / 24;
	hor  = hor % 24;

	printf
	(	"%3d dias, %02d:%02d:%02d",
		dias, hor, min, seg
	);
	
	/*
	 *	Imprime a hora do "boot"
	 */
	printf ("\t(boot = %24.24s)\n", btime (&boot_time));

	return (0);

}	/* end uptime */

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
		"%s - fornece o tempo decorrido desde o �ltimo \"boot\"\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
