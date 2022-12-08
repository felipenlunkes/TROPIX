/*
 ****************************************************************
 *								*
 *			to.c					*
 *								*
 *	Escreve uma linha de mensagem para um usu�rio		*
 *								*
 *	Vers�o	1.0.0, de 26.11.86				*
 *		3.0.1, de 12.07.97				*
 *								*
 *	M�dulo: to						*
 *		Utilit�rios Bem B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <utmp.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.1, de 12.07.97";

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	allflag;	/* Todos os usu�rios */

/*
 ****** Valores constantes **************************************
 */
entry char	*my_tty_nm;	/* Nome do meu terminal */
entry char	*my_login_nm;	/* Meu nome */

/*
 ****** Nome dos arquivos globais *******************************
 */
const char	utmp_nm[]   = "/var/adm/utmp";

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
void		proc_user (UTMP *u, const char **argv);

/*
 ****************************************************************
 *	Escreve uma linha de mensagem para um usu�rio		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	register FILE	*utmp_fp;
	register char	*cp;
	int		found = 0;
	UTMP		utmp;

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
	argv += optind;
	argc -= optind;

	if (argc < 2)
		help ();

	if (streq (argv[0], "all"))
		allflag++;

	/*
	 *	Obt�m o meu nome de login
	 */
	if ((my_login_nm = getlogin ()) == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o meu nome de login\n",
			pgname
		);
		exit (1);
	}

	/*
	 *	Obt�m o nome do pr�prio terminal
	 */
	if ((my_tty_nm = ttyname (2 /* stderr */)) == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o nome do terminal\n",
			pgname
		);
		exit (1);
	}
 
	if ((cp = strrchr (my_tty_nm, '/')) != NOSTR)
		my_tty_nm = cp + 1;

	/*
	 *	Abre o arquivo do formato UTMP
	 */
	if ((utmp_fp = fopen (utmp_nm, "r")) == NOFILE)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui abrir \"%s\" (%s)\n",
			pgname, utmp_nm, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Procura o <usu�rio> no arquivo UTMP
	 */
	while (fread (&utmp, sizeof (UTMP), 1, utmp_fp) == 1)
	{
		if (utmp.ut_name[0] == '\0')
			continue;

		if (allflag || streq ((char *)utmp.ut_name, argv[0]))
		{
			found++;

			proc_user (&utmp, argv);
		}

	}	/* end for (EVER) */

	fclose (utmp_fp);

	if (found == 0)
	{
		fprintf
		(	stderr,
			"%s: O usu�rio \"%s\" n�o est� em sess�o\n",
			pgname, argv[0]
		);

		exit_code++;
	}

	return (exit_code);

}	/* end to */

/*
 ****************************************************************
 *	Envia a mensagem para um terminal			*
 ****************************************************************
 */
void
proc_user (register UTMP *u, register const char **argv)
{
	register FILE	*dst_fp;
	char		tty_nm[32];

	/*
	 *	Prepara o nome e abre o terminal
	 */
	strcpy (tty_nm, "/dev/");
	strcat (tty_nm, (char *)u->ut_line);

	if ((dst_fp = fopen (tty_nm, "w")) == NOFILE)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui abrir \"%s\", \"%s\" (%s)\n",
			pgname, tty_nm, u->ut_name, strerror (errno)
		);

		exit_code++; return;
	}

	/*
	 *	Escreve a mensagem
	 */
	fprintf
	(	dst_fp,
		"\n\r\aMENSAGEM de \"%s\" em \"%s\":",
		my_login_nm, my_tty_nm
	);

	for (argv++; *argv; argv++)
		fprintf (dst_fp, " %s", *argv);

	fprintf (dst_fp, "\n");

   /***	fflush (dst_fp); ***/

	if (ferror (dst_fp))
	{
		fprintf
		(	stderr,
			"%s: N�o consegui enviar a mensagem para \"%s\" (%s)\n",
			pgname, u->ut_name, strerror (errno)
		);
		exit_code++;
	}

	fclose (dst_fp);

}	/* end proc_user */

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
 		"%s - escreve uma linha de mensagem para um usu�rio\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <usu�rio> <mensagem>\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nObs.:\tSe <usu�rio> == \"all\", "
		"escreve para todos os usu�rios em sess�o\n"
	);

	exit (2);

}	/* end help */
