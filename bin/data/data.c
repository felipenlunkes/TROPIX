/*
 ****************************************************************
 *								*
 *			data.c					*
 *								*
 *	Mostra/atualiza a data/hora corrente do sistema		*
 *								*
 *	Vers�o	2.3.0, de 22.07.90				*
 *		3.1.0, de 26.10.98				*
 *								*
 *	M�dulo: data/date/datagmt				*
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
#include <string.h>
#include <time.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.1.0, de 26.10.98";

#define	elif	else if

typedef enum {	DATA, DATE, DATAGMT }	FUNCTION;

entry FUNCTION	function = DATA; /* Define se "data", "date", "datagmt" */

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
const char	*last_id (const char *);
void		help (void);

/*
 ****************************************************************
 *	Mostra/atualiza a data/hora corrente do sistema		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int			opt;
	const char		*cp;
	time_t			TEMPO;
	char			bad = 0;

	/*
	 *	Analisa o modo de funcionamento
	 */
	cp = last_id (pgname);

	if   (streq (cp, "date"))
		function = DATE;
	elif (streq (cp, "datagmt"))
		function = DATAGMT;

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
	 *	Obt�m o tempo GMT
	 */
	time (&TEMPO);

	/*
	 *	Atualiza a data
	 */
	if   (argc == 1)
	{
		switch (function)
		{
		    case DATA:
		    case DATE:
			if ((TEMPO = strtotime (argv[0], localtime (&TEMPO))) == -1)
				bad++;

			TEMPO -= gettzmin () * 60;	/* Volta para GMT */

			break;

		    case DATAGMT:
			if ((TEMPO = strtotime (argv[0], gmtime (&TEMPO))) == -1)
				bad++;

			break;

		}	/* end switch */

		if (bad)
		{
			fprintf
			(	stderr,
				"Sintaxe de data/hora inv�lida: \"%s\"\n\n",
				argv[0]
			);

			help ();
		}

		if (time ((time_t *)NULL) > TEMPO)
		{
			fprintf
			(	stderr,
				"Esta data � anterior � atual. Atualiza? (n): "
			);

			if (askyesno () <= 0)
				exit (0);
		}

		if (stime (&TEMPO) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui atualiza a data/hora (%s)\n",
				pgname, strerror (errno)
			);
			exit (1);
		}

	}
	elif (argc != 0)
	{
		help ();
	}

	/*
	 *	Mostra a data
	 */
	switch (function)
	{
	    case DATA:
		printf ("%s", brasctime (localtime (&TEMPO)));
		break;

	    case DATE:
		printf ("%s", asctime (localtime (&TEMPO)));
		break;

	    case DATAGMT:
		printf ("%s", brasctime (gmtime (&TEMPO)));
		break;

	}	/* end switch */

	return (0);

}	/* end data */

/*
 ****************************************************************
 *	Obt�m o �ltimo componente de um nome			*
 ****************************************************************
 */
const char *
last_id (const char *pathname)
{
	char		*cp;

	if (cp = strrchr (pathname, '/'))
		return (cp + 1);
	else
		return (pathname);

} 	/* end last_id */

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
		"%s - mostra/atualiza a data/hora corrente %s do sistema\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [[[[[<ano>]<m�s>]<dia>]<hora>]<minuto>][:<segundo>]\n",
		pgname,
		function == DATAGMT ? "GMT" : "LOCAL",
		pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nObs.:"
		"\tCada componente (<ano>, <m�s>, ...) deve ser dado "
		"na forma de 2\n\td�gitos decimais. "
		"O caractere \".\" pode ser usado ao inv�s de \":\"\n"
	);

	exit (2);

}	/* end help */
