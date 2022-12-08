/*
 ****************************************************************
 *								*
 *			chknet.c				*
 *								*
 *	Programa para verificar o estado da rede		*
 *								*
 *	Vers�o	4.9.0, de 10.09.08				*
 *		4.9.0, de 10.09.08				*
 *								*
 *	M�dulo: chknet						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2008 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <xti.h>
#include <time.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 4.9.0, de 10.09.08";

#define	DEVNAME	"/dev/rtl0"

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

const char	tcp_dev_nm[] = "/dev/itntcp";

entry int	static_log_fd;	/* Para "error" */
entry FILE	*static_log_fp;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
void		proc_file (char *);

/*
 ****************************************************************
 *	Programa para verificar o estado da rede		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, fd, pid;

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
			fprintf (stderr, "\n");
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Libera quem mandou executar
	 */
	if ((pid = fork ()) < 0)
		error ("$*N�o consegui dar \"fork\"");

	if (pid > 0)
		exit (0);

	/*
	 *	Em primeiro lugar, espera algum tempo ...
	 */
#define	DEBUG
#ifdef	DEBUG
	error ("Come�ando");
#endif	DEBUG

	sleep (30);

#ifdef	DEBUG
	error ("Acordando");
#endif	DEBUG

	/*
	 *	Agora, examina o estado da rede
	 */
	if ((fd = open (DEVNAME, O_RDWR)) >= 0)
	{
#ifdef	DEBUG
		error ("A rede est� ativa");
#endif	DEBUG
		close (fd); return (0);
	}

	/*
	 *	A rede N�O est� ativa ...
	 */
#ifdef	DEBUG
	error ("A rede N�O est� ativa");
#endif	DEBUG

	system ("reboot");

	return (exit_code);

}	/* end chknet */

/*
 ****************************************************************
 *	Imprime uma mensagem de erro (servidor)			*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	va_list		args;
	const char	*fmt = format;
	FILE		*log_fp;
	char		err, abrt;
	int		save_errno = errno;
	time_t		time_loc;

	va_start (args, format);

	/*
	 *	Procura o arquivo de "log"
	 */
	if (static_log_fd == 0)
	{
		if ((static_log_fd = open ("/var/adm/itnetlog", O_WRONLY|O_APPEND)) >= 0)
		{
			if ((static_log_fp = fdopen (static_log_fd, "w")) == NOFILE)
				static_log_fd = -1;
		}
	}

	log_fp = static_log_fp;

	/*
	 *	Processa os argumentos da cadeia
	 */
	if (fmt == NOSTR)
		fmt = "$*Erro de entrada/sa�da de TCP";

	if ((abrt = *fmt) == '$')
		fmt++;

	if ((err = *fmt) == '*')
		fmt++;

	/*
	 *	Escreve as mensagens
	 */
	if (log_fp != NOFILE)
	{
		/* Escreve a mensagem com o tempo */

		fprintf  (log_fp, pgname);

		time (&time_loc);
		fprintf (log_fp, " (%.24s)", btime (&time_loc));

		fprintf  (log_fp, ": ", pgname);
		vfprintf (log_fp, fmt, args);

		/* Escreve o tipo do erro */

		if (err == '*' && save_errno != 0)
			fprintf (log_fp, " (%s)", strerror (save_errno));

		putc ('\n', log_fp); fflush (log_fp);
	}

	if (abrt == '$')
		exit (1);

	va_end (args);

}	/* end error */

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
		"%s - programa\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-op��es] arg\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-x: op��o\n"
		"\t-y: op��o\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados argumentos\n"
		"\nObs.:\tobserva��o\n"
	);

	exit (2);

}	/* end help */
