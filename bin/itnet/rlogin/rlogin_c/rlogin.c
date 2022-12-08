/*
 ****************************************************************
 *								*
 *			rlogin.c				*
 *								*
 *	Comunica��o com esta��o remota (cliente)		*
 *								*
 *	Vers�o	2.3.0, de 06.10.92				*
 *		3.0.2, de 08.08.97				*
 *								*
 *	M�dulo: ITNET						*
 *		Utilit�rios de comunica��o			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
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
#include <pwd.h>
#include <termio.h>
#include <signal.h>
#include <errno.h>
#include <xti.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.2, de 08.08.97";

#define RLOGIN_PORT	513

#define MIN_PORT	513
#define MAX_PORT	1023

#define	EVER	;;
#define	elif	else if

entry int	vflag;		/* Verbose */
entry int	iflag;		/* N�o converte o c�digo dos caracteres */

/*
 ****** Vari�veis da linha/tela *********************************
 */
int		global_tcp_fd;	/* Para o TCP */

entry TERMIO	ovideo, video;	/* modos do terminal */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		read_write_loop (int);
void		send_window_information (int);
void		error (const char *, ...);
void		on_SIGTERM (int, ...);
void		tcp_abort (void);
void		quit (int);
void		help (void);

/*
 ****************************************************************
 *	Comunica��o com esta��o remota				*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	register char	*cp;
	register PASSWD	*pw;
	const char	*client_user_name = NOSTR;
	const char	*server_user_name = NOSTR;
	const char	*term = NOSTR;
	const char	*node_nm;
	int		tcp_fd;
	T_BIND		bind;
	INADDR		addr;
	T_CALL		call;
	const char	*str;
	int		flag;
	long		serv_addr;
	char		c;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "l:ivH")) != EOF)
	{
		switch (opt)
		{
		    case 'l':			/* login name */
			server_user_name = optarg;
			break;

		    case 'i':			/* Sem convers�o de c�digo */
			iflag++;
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
	 *	Examina a entrada padr�o
	 */
	if (ioctl (0, TCGETS, &ovideo) < 0  ||  isatty (1) == 0)
		error ("$O <stdin> e/ou <stdout> n�o � um terminal");

	/*
	 *	Obt�m o nome do usu�rio local (cliente)
	 */
	client_user_name = getlogin ();

	if (client_user_name == NOSTR)
		client_user_name = getenv ("USER");

	if (client_user_name == NOSTR && (pw = getpwuid (getuid ())) != NOPASSWD)
		client_user_name = pw->pw_name;

	if (client_user_name == NOSTR)
		error ("$N�o consegui obter o nome do pr�prio usu�rio local");

	/*
	 *	Obt�m os nome do <n�_remoto> e do usu�rio remoto (servidor)
	 */
	if ((cp = strchr (argv[0], '@')) == NOSTR)
	{
		node_nm = argv[0];
	}
	else
	{
		cp[0] = '\0'; node_nm = cp + 1;

		if (server_user_name != NOSTR)
			help ();

		server_user_name = argv[0];
	}

	if (server_user_name == NOSTR)
		server_user_name = client_user_name;

	if (vflag)
	{
		printf ("client_user_name  = \"%s\"\n", client_user_name);
		printf ("server_user_name = \"%s\"\n", server_user_name);
		printf ("node_name = \"%s\"\n", node_nm);
	}

	/*
	 *	Obt�m o terminal local
	 */
	if ((term = getenv ("TERM")) == NOSTR)
		term = "network";

	if (vflag)
		printf ("term:   %s\n", term);

	/*
	 *	Abre o "endpoint"
	 */
	str = "/dev/itntcp";

	if ((tcp_fd = t_open (str, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", str);

	global_tcp_fd = tcp_fd;

	/*
	 *	Obt�m o endere�o do n� remoto
	 */
	if ((serv_addr = t_node_to_addr (tcp_fd, node_nm, (long *)NULL)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", node_nm);

	if (vflag)
		printf ("serv_addr dado: %08X (%s)\n", serv_addr, node_nm);

	/*
	 *	Associa um endere�o local
	 */
	bind.addr.len	 = sizeof (INADDR);
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &addr;

	bind.qlen	 = 0;

	for (addr.a_port = MAX_PORT; /* teste abaixo */; addr.a_port--)
	{
		if (addr.a_port <= MIN_PORT)
			error ("$Todos os \"ports\" est�o ocupados");

		if (t_bind (tcp_fd, &bind, &bind) >= 0)
			break;

		if (errno != TADDRBUSY)
			error ("$N�o consegui associar um endere�o");
	}

	if (vflag)
		printf ("Port_no do cliente obtido: %d\n", ((INADDR *)bind.addr.buf)->a_port);

	/*
	 *	D� o CONNECT
	 */
	addr.a_port	 = RLOGIN_PORT;
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
		printf ("port_no do servidor obtido: %d\n", ((INADDR *)call.addr.buf)->a_port);

	/*
	 *	Manda o byte NULO indicando que n�o tem o outro canal (sinais)
	 */
	if (t_snd (tcp_fd, "",  1, 0) < 0)
		error (NOSTR);

	/*
	 *	Manda o usu�rio local, remoto e terminal
	 */
#undef	TWICE_REMOTE
#ifdef	TWICE_REMOTE
	t_snd (tcp_fd, server_user_name, strlen (server_user_name) + 1, 0);
#else
	t_snd (tcp_fd, client_user_name,  strlen (client_user_name) + 1, 0);
#endif	TWICE_REMOTE

	t_snd (tcp_fd, server_user_name, strlen (server_user_name) + 1, 0);
	t_snd (tcp_fd, term,		strlen (term) + 1, T_PUSH);

	/*
	 *	Agora, espera a resposta (OK ou Erro)
	 */
	if (t_rcv (tcp_fd, &c, 1, &flag) != 1)
		error (NOSTR);

	if (c == '\0')
	{
		if (vflag)
			fprintf (stderr, "Recebi OK (flag = %X)\n", flag);
	}
	else
	{
		while (t_rcv (tcp_fd, &c, 1, &flag) == 1)
		{
			write (2, &c, 1);

			if (c == '\n' || c == '\0')
				break;
		}

		tcp_abort ();
	}

	/*
	 *	Poe o Terminal em RAW
	 */
	video = ovideo;

	video.c_oflag &= ~OPOST;
	video.c_lflag &= ~(ISIG|ICANON|ECHO);
	video.c_cc[VMIN] = 1;

	if (iflag)
	{
		video.c_lflag &= ~CODE;
	   /***	video.c_lflag |= ISO; ***/
	}

	ioctl (0, TCSETNR, &video);

	/*
	 *	Realiza o servi�o regular
	 */
	signal (SIGTERM, on_SIGTERM);

	read_write_loop (tcp_fd);

	/*
	 *	Termina a conex�o
	 */
	if (t_sndrel (tcp_fd) < 0)
		error ("$*Erro no SNDREL");

	if (t_rcvrel (tcp_fd) < 0)
		error ("$*Erro no RCVREL");

	ioctl (0, TCSETNR, &ovideo);

	printf ("Conex�o \"rlogin\" fechada\n");

	return (0);

}	/* end rlogin */

/*
 ****************************************************************
 *	Servi�o de entrada/sa�da regular			*
 ****************************************************************
 */
void
read_write_loop (int tcp_fd)
{
	register int	n;
	int		fd_vec[2];
	char		area[BLSZ];
	int		flag, index = -1;

	/*
	 *	Prepara a ATTENTION
	 */
	fd_vec[0] = 0;		/* TECLADO */
	fd_vec[1] = tcp_fd;	/* TCP */

	/*
	 *	Espera entrada do TCP ou do TECLADO
	 */
	for (EVER)
	{
		if ((index = attention (2, fd_vec, index, 0)) < 0)
		{
			if ((index = _attention_index) < 0)
			{
				if (errno == EINTR)
					{ index = -1; continue; }

				error ("$*Erro na chamada ao sistema \"attention\"");
			}
		}

		switch (index)
		{
		    case 0:		/* Teclado */
			if   ((n = read (0, area, BLSZ)) < 0)
				error ("*Erro na leitura do teclado");
			elif (n == 0)
				error ("EOF na leitura do teclado");
			elif (t_snd (tcp_fd, area, n, T_PUSH) < 0)
				error (NOSTR);
			break;

		    case 1:		/* TCP */
			if ((n = t_nread (tcp_fd)) < 0)
			{
				if (errno == TLOOK && t_look (tcp_fd) == T_ORDREL)
					return;		/* EOF */

				error (NOSTR);
			}

			if (n == 0)	/* Alarme Falso! */
				break;

			if (n > BLSZ)
				n = BLSZ;

			if ((n = t_rcv (tcp_fd, area, n, &flag)) < 0)
				error (NOSTR);

			if (flag & T_URGENT)
			{
				int		i;
#ifdef	DEBUG
				printf ("%s: Recebi %d bytes urgentes:", pgname, n);

				for (i = 0; i < n; i++)
					printf (" %02X", area[i]);

				printf ("\r\n");
#endif	DEBUG
				for (i = 0; i < n; i++)
				{
					if (area[i] == 0x80)
						send_window_information (tcp_fd);
				}

				break;
			}

			if (n == 0)	/* EOF */
				return;

			write (1, area, n);
			break;

		    default:
			error ("$A chamada ao sistema \"attention\" retornou o �ndice %d inv�lido", index);

		}	/* end switch */

	}	/* end for ever */

}	/* end read_write_loop */

/*
 ****************************************************************
 *	Envia a informa��o de tamanho de janela			*
 ****************************************************************
 */
void
send_window_information (int tcp_fd)
{
	char		window_info[12];

	memset (window_info, 0, sizeof (window_info));

	window_info[0] = 0xFF;
	window_info[1] = 0xFF;
	window_info[2] = 's';
	window_info[3] = 's';

	window_info[5] = video.t_nline;	/* BIG endian */
	window_info[7] = video.t_ncol;	/* BIG endian */

	if (t_snd (tcp_fd, window_info, sizeof (window_info), T_PUSH) < 0)
		error (NOSTR);
#ifdef	DEBUG
	error ("Mandei informa��o da janela");
#endif	DEBUG
 
}	/* end send_window_information */

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
			event = t_look (global_tcp_fd);
	
			fprintf (stderr, " (%s)", t_strevent (global_tcp_fd, event));
	
			if (event ==  T_DISCONNECT)
				{ fprintf (stderr, "\r\n"); quit (1); }
		}
		elif (save_errno != 0)
		{
			fprintf (stderr, " (%s)", strerror (save_errno));
		}
	}

	fprintf (stderr, "\r\n");

	if (abrt == '$')
		tcp_abort ();

	va_end (args);

}	/* end error */

/*
 ****************************************************************
 *	Se receber um sinal, ...				*
 ****************************************************************
 */
void
on_SIGTERM (int signo, ...)
{
	error ("$Recebi um SIGTERM, terminando ...");

	/* N�o retorna */

}	/* end on_SIGTERM */

/*
 ****************************************************************
 *	Encerra as atividades (desconectando o TCP)		*
 ****************************************************************
 */
void
tcp_abort (void)
{
	t_snddis (global_tcp_fd, (T_CALL *)NULL);

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
	ioctl (0, TCSETNR, &ovideo);

	exit (exit_code);

}	/* end on_SIGTERM */

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
		"%s - entra em sess�o em um n� remoto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-iv] [-l <usu�rio_remoto>] <n�_remoto>\n\n"
		"\t%s [-iv] [<usu�rio_remoto>@]<n�_remoto>\n",
		pgname, pgversion, pgname, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: N�o converte o c�digo na recep��o\n"
		"\t-v: Verboso\n"
		"\t-l: Define o nome do usu�rio remoto "
			"(pode ser dado como \"...@\")\n"
		"\t    (se n�o dado, � utilizado o nome do usu�rio local)\n"
	);

	exit (2);

}	/* end help */
