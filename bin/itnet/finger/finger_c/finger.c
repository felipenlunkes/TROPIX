/*
 ****************************************************************
 *								*
 *			finger.c				*
 *								*
 *	Obt�m informa��es sobre usu�rios remotos		*
 *								*
 *	Vers�o 	3.0.0, de 25.04.93				*
 *	 	3.0.1, de 23.08.97				*
 *								*
 *	M�dulo: ITNET						*
 *		Utilit�rios de comunica��o			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <xti.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.1, de 23.08.97";

#define FINGER_PORT	79

#define	EVER	;;
#define	elif	else if

entry int	vflag;		/* Verbose */

int		tcp_fd;		/* fd do TCP */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		error (const char *, ...);
void		tcp_abort (void);
void		quit (int);
void		help (void);

/*
 ****************************************************************
 *	Obt�m informa��es sobre usu�rios remotos		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt, n;
	register char	*cp;
	const char	*node_nm, *user_nm = NOSTR;
	T_BIND		bind;
	INADDR		addr;
	T_CALL		call;
	const char	*str;
	long		serv_addr;
	char		area[512];
	int		flag;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "u:vH")) != EOF)
	{
		switch (opt)
		{
		    case 'u':			/* Usu�rio dado */
			user_nm = optarg;
			break;

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

	if (argc != 1)
		help ();

	/*
	 *	Processa o nome do usu�rio
	 */
	if ((cp = strchr (argv[0], '@')) == NOSTR)
	{
		node_nm = argv[0];
	}
	else
	{
		cp[0] = '\0'; node_nm = cp + 1;

		if (user_nm != NOSTR)
			help ();

		user_nm = argv[0];
	}

	/*
	 *	Abre o "endpoint"
	 */
	str = "/dev/itntcp";

	if ((tcp_fd = t_open (str, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", str);

	/*
	 *	Obt�m o endere�o do n� remoto
	 */
	if ((serv_addr = t_node_to_addr (tcp_fd, node_nm, (long *)NULL)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", node_nm);

	if (vflag)
		error ("serv_addr dado: %08X (%s)", serv_addr, node_nm);

	/*
	 *	Associa um endere�o local
	 */
	bind.addr.len	 = 0;
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &addr;

	bind.qlen	 = 0;

	if (t_bind (tcp_fd, &bind, &bind) < 0)
		error ("$*N�o consegui associar um endere�o");

	if (vflag)
		error ("Port_no do cliente obtido: %d", addr.a_port);

	/*
	 *	D� o CONNECT
	 */
	addr.a_port	 = FINGER_PORT;
	addr.a_addr	 = serv_addr;

	call.addr.len	 = sizeof (INADDR);
	call.addr.maxlen = sizeof (INADDR);
	call.addr.buf	 = &addr;

	if (t_connect (tcp_fd, &call, &call) < 0)
	{
		if (errno == TLOOK && t_look (tcp_fd) == T_DISCONNECT)
		{
			error ("A conex�o foi recusada por \"%s\"", node_nm);
			quit (1);
		}

		error ("$*N�o consegui estabelecer conex�o");
	}

	if (vflag)
		error ("port_no do servidor obtido: %d", addr.a_port);

	/*
	 *	Envia a linha
	 */
	if (user_nm != NOSTR)
		t_snd (tcp_fd, user_nm, strlen (user_nm), 0);

	if (t_snd (tcp_fd, "\r\n", 2, T_PUSH) < 0)
		error (NOSTR);

	/*
	 *	L� a informa��o fornecida pelo servidor
	 */
	while ((n = t_rcv (tcp_fd, area, sizeof (area), &flag)) > 0)
		write (1, area, n);

	if (n < 0)
		error (NOSTR);

	/*
	 *	Termina a conex�o
	 */
	if (t_sndrel (tcp_fd) < 0)
		error ("$*Erro no SNDREL");

	if (t_rcvrel (tcp_fd) < 0)
		error ("$*Erro no RCVREL");

	return (0);

}	/* end finger */

/*
 ****************************************************************
 *	Imprime uma mensagem de erro (cliente)			*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	register va_list	args;
	register const char	*fmt = format;
	char			err, abrt;
	int			event, save_errno = errno;

	va_start (args, format);

	if (fmt == NOSTR)
		fmt = "$*Erro de entrada/sa�da de TCP";

	if ((abrt = *fmt) == '$')
		fmt++;

	if ((err = *fmt) == '*')
		fmt++;

	fprintf  (stderr, "%s: ", pgname);
	vfprintf (stderr, fmt, args);

	if (err == '*')
	{
		if (save_errno == TLOOK)
		{
			event = t_look (tcp_fd);
	
			fprintf (stderr, " (%s)", t_strevent (tcp_fd, event));
	
			if (event ==  T_DISCONNECT)
				{ putc ('\n', stderr); quit (1); }
		}
		elif (save_errno != 0)
		{
			fprintf (stderr, " (%s)", strerror (save_errno));
		}
	}

	putc ('\n', stderr);

	if (abrt == '$')
		tcp_abort ();

	va_end (args);

}	/* end error */

/*
 ****************************************************************
 *	Encerra as atividades (desconectando o TCP)		*
 ****************************************************************
 */
void
tcp_abort (void)
{
	t_snddis (tcp_fd, (T_CALL *)NULL);

	quit (1);

}	/* end tcp_abort */

/*
 ****************************************************************
 *	Restaura o estado do terminal e termina			*
 ****************************************************************
 */
void
quit (int exit_code)
{
	exit (exit_code);

}	/* end quit */

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
		"%s - obt�m informa��es sobre usu�rios remotos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-v] [-u <usu�rio_remoto>] <n�_remoto>\n"
		"\t%s [-v] [<usu�rio_remoto>@]<n�_remoto>\n",
		pgname, pgversion, pgname, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Informa��es sobre todos os usu�rios remotos em sess�o\n"
		"\t-u: Informa��es apenas sobre o <usu�rio_remoto> dado\n"
		"\t    (Esta op��o pode ser dada na forma com \"@\", como acima)\n"
		"\t-v: Verboso\n"
	);

	exit (2);

}	/* end help */
