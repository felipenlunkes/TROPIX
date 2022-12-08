/*
 ****************************************************************
 *								*
 *			write.c					*
 *								*
 *	Escreve mensagens para um outro usu�rio			*
 *								*
 *	Vers�o	1.0.0, de 06.02.87				*
 *		3.0.0, de 14.07.97				*
 *								*
 *	M�dulo: write						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utmp.h>
#include <stat.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 14.07.97";

#define	LINESZ	128

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	vflag;		/* Verbose */

/*
 ****** Nome dos arquivos globais *******************************
 */
const char	utmp_nm[]   = "/var/adm/utmp";

/*
 ****** Estado para "setjmp" ************************************
 */
entry jmp_buf	end_env;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
void		on_signal (int signo, ...);
void		write_end (void);

/*
 ****************************************************************
 *	Escreve mensagens para um outro usu�rio			*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	int		opt;
	FILE		*utmp_fp, *dst_fp;
	const char	*cp;
	const char	*my_user_nm = NOSTR, *my_tty_nm;
	const char	*my_complete_tty_nm;
	const char	*dst_user_nm, *dst_tty_nm;
	char		*dst_complete_tty_nm;
	int		dst_user_found = 0;
	const char	*dst_tty_given;
	UTMP		utmp;
	STAT		s;
	char		line[LINESZ];

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

	/*
	 *	Pequena consist�ncia
	 */
	argv += optind; 	argc -= optind;

	if (argc < 1 || argc > 2)
		help ();

	dst_user_nm = argv[0];  dst_tty_given = dst_tty_nm = argv[1];

	if (dst_tty_given  &&  (cp = strrchr (dst_tty_nm, '/')) != NOSTR)
		dst_tty_nm = cp + 1;

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

	my_complete_tty_nm = my_tty_nm;

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

		if (my_user_nm == NOSTR && streq ((char *)utmp.ut_line, my_tty_nm))
			my_user_nm = strdup ((char *)utmp.ut_name);

		if (!streq ((char *)utmp.ut_name, dst_user_nm))
			continue;

		if (dst_tty_given)
		{
			if (streq ((char *)utmp.ut_line, dst_tty_nm))
				dst_user_found++;
		}
		else
		{
			dst_user_found++;

			if (dst_tty_nm == NOSTR)
				dst_tty_nm = strdup ((char *)utmp.ut_line);
		}

	}	/* end for (EVER) */

	fclose (utmp_fp);

	/*
	 *	Verifica se foi encontrado o nome do pr�prio usu�rio
	 */
	if (my_user_nm == NOSTR)
	{
		fprintf
		(	stderr,
			"N�o achei a minha pr�pria entrada em \"%s\"\n",
			utmp_nm
		);
		exit (1);
	}

	/*
	 *	Verifica se foi encontrado o nome do <usu�rio>
	 */
	if (dst_user_found == 0)
	{
		fprintf (stderr, "O usu�rio \"%s\" n�o est� em sess�o", dst_user_nm);
		if (dst_tty_nm != NOSTR)
			fprintf (stderr, " no terminal \"%s\"", dst_tty_nm);
		fprintf (stderr, "\n");
		exit (1);
	}

	/*
	 *	Verifica se foi encontrado o nome do <usu�rio> mais de uma vez
	 */
	if (dst_user_found > 1)
	{
		fprintf
		(	stderr,
			"O usu�rio \"%s\" est� em sess�o em mais de um terminal!\n",
			dst_user_nm
		);
#if (0)	/*************************************/
		fprintf
		(	stderr,
			"Voc� est� conectado com \"%s\"\n",
			dst_tty_nm
		);
#endif	/*************************************/
	}

	/*
	 *	Verifica se est� escrevendo para o pr�prio terminal
	 */
	if (streq (dst_tty_nm, my_tty_nm))
	{
		fprintf (stderr, "Escrevendo para o pr�prio terminal?\n");
		exit (1);
	}

#undef	DEBUG
#ifdef	DEBUG
	printf ("my_user_nm  = \"%s\", my_tty_nm  = \"%s\"\n", my_user_nm, my_tty_nm);
	printf ("dst_user_nm = \"%s\", dst_tty_nm = \"%s\"\n", dst_user_nm, dst_tty_nm);
#endif	DEBUG

	/*
	 *     Verifica se o destinat�rio vai conseguir escrever no meu terminal
	 */
	if (stat (my_complete_tty_nm, &s) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado do terminal \"%s\" (%s)\n",
			pgname, my_complete_tty_nm, strerror (errno)
		);
		exit (2);
	}

	if ((s.st_mode & S_IWOTH) == 0)
	{
		fprintf
		(	stderr,
			"*** CUIDADO: "
			"A recep��o do seu terminal est� desabilitada!\n"
		);
	}

	/*
	 *	Abre o terminal do destinat�rio
	 */
	dst_complete_tty_nm = malloc (strlen (dst_tty_nm) + 6);

	strcpy (dst_complete_tty_nm, "/dev/");
	strcat (dst_complete_tty_nm, dst_tty_nm);

	if ((dst_fp = fopen (dst_complete_tty_nm, "w")) == NOFILE)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui abrir \"%s\" (%s)\n",
			pgname, dst_tty_nm, strerror (errno)
		);
		exit (1);
	}

	/*
	 *     Verifica se o destinat�rio est� com "mesg -y"
	 */
	if (fstat (fileno (dst_fp), &s) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado do terminal \"%s\" (%s)\n",
			pgname, dst_complete_tty_nm, strerror (errno)
		);
		exit (2);
	}

	if ((s.st_mode & S_IWOTH) == 0)
	{
		fprintf
		(	stderr,
			"N�o tenho permiss�o para escrever no terminal \"%s\"\n",
			dst_complete_tty_nm
		);
		exit (1);
	}

	/*
	 *	Envia o pr�logo para o destinat�rio
	 */
	fprintf
	(	dst_fp,
		"\a\nMENSAGEM de \"%s\" (%s):\n\n",
		my_user_nm, my_tty_nm
	);

   /***	fflush (dst_fp); ***/

	if (ferror (dst_fp))
	{
		fprintf
		(	stderr,
			"%s: N�o consegui enviar o pr�logo para \"%s\" (%s)\n",
			pgname, dst_tty_nm, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Prepara o "setjmp" para o encerramento
	 */
	if (setjmp (end_env))
	{
		fprintf
		(	dst_fp,
			"\nFIM da mensagem de \"%s\" (%s)\n",
			my_user_nm, my_tty_nm
		);
	
		fclose (dst_fp);
		exit (0);
	}

	/*
	 *	Prepara os sinais
	 */
	signal (SIGHUP,  on_signal);
	signal (SIGINT,  on_signal);
	signal (SIGQUIT, on_signal);

	/*
	 *	Envia a mensagem de confirma��o
	 */
	fprintf
	(	stderr,
		"\aConectado com o usu�rio \"%s\" no terminal \"%s\"\n",
		dst_user_nm, dst_tty_nm
	);

	/*
	 *	Envia as minhas diversas linhas
	 */
	for (EVER)
	{
		if (fngets (line, LINESZ, stdin) == NOSTR)
			break;

		/*
		 *	Verifica se � uma linha de comando
		 */
		if (line[0] == '!')
		{
			system (line + 1);
			fprintf (stderr, "!\n");
			continue;
		}

		/*
		 *     Verifica se o destinat�rio por acaso deu "mesg -n"
		 */
		if (fstat (fileno (dst_fp), &s) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui obter o estado do terminal \"%s\" (%s)\n",
				pgname, dst_complete_tty_nm, strerror (errno)
			);
			exit (2);
		}
	
		if ((s.st_mode & S_IWOTH) == 0)
		{
			fprintf
			(	stderr,
				"\aN�o consigo mais escrever no terminal \"%s\"\n",
				dst_complete_tty_nm
			);
			write_end ();
		}

		if (fnputs (line, dst_fp) < 0 /* (EOF) */)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui enviar a mensagem para \"%s\" (%s)\n",
				pgname, dst_tty_nm, strerror (errno)
			);
			exit (1);
		}

	}	/* end for (EVER) */

	write_end ();

}	/* end write */

/*
 ****************************************************************
 *	Em caso de sinal, ...					*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	longjmp (end_env, 1);

}	/* end on_signal */

/*
 ****************************************************************
 *	Encerra a comunica��o com o destinat�rio 		*
 ****************************************************************
 */
void
write_end (void)
{
	longjmp (end_env, 1);

}	/* end write_end */

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
		"%s - escreve mensagens para um outro usu�rio\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <usu�rio> [<tty>]\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
