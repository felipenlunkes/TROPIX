/*
 ****************************************************************
 *								*
 *			telnet.c				*
 *								*
 *	Comunica��o com esta��o remota				*
 *								*
 *	Vers�o 	3.0.0, de 02.04.93				*
 *	 	3.0.3, de 31.08.98				*
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
#include <signal.h>
#include <termio.h>
#include <errno.h>
#include <xti.h>

#include "../telnet.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.3, de 31.08.98";

#undef	DEBUG

#define TELNET_PORT	23

#define	EVER	;;
#define	elif	else if

entry int	iflag;		/* N�o converte o c�digo dos caracteres */
entry int	lflag;		/* Modo de linha */
entry int	eflag;		/* Eco local */
entry int	vflag;		/* Verbose */
#ifdef	DEBUG
entry int	dflag;		/* Debug */
#endif	DEBUG

entry int	telnet_port = TELNET_PORT; /* Porta efetivamente usada */
entry char	telnet_port_given;

/*
 ****** Vari�veis da linha/tela *********************************
 */
int		global_tcp_fd; 	/* fd do TCP */

#ifdef	DEBUG
FILE		*debugfp;	/* FILE do DEBUG */
#endif	DEBUG

TERMIO		ovideo, video;	/* modos do terminal */

/*
 ******	Vari�veis do estado *************************************
 */
#define	OPTSZ	256

/* Todos os estados come�am em "0" (STATE_NO) */

entry char	my_state[OPTSZ];	/* Estado daqui */

entry char	his_state[OPTSZ];	/* Estado dali */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		read_write_loop (int);
int		process_telnet_option (const char *, int);
void		receive_WILL (int);
void		receive_WONT (int);
void		send_DO (int);
void		send_DONT (int);
void		receive_DO (int);
void		receive_DONT (int);
void		send_WILL (int);
void		send_WONT (int);
int		he_should (int);
int		we_should (int);
void		enable (int);
void		disable (int);
int		receive_SB (const char *, int);
int		send_terminal_type (const char *, int);
void		send_window_size (void);
void		send_option (int, int);
const char	*edit_telnet_code (int);
const char	*edit_telnet_option (int);
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
	register int		opt;
	T_BIND			bind;
	INADDR			addr;
	T_CALL			call;
	const char		*str;
	long			serv_addr;
	int			tcp_fd;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "ilevdH")) != EOF)
	{
		switch (opt)
		{
		    case 'i':			/* Sem convers�o de c�digo */
			iflag++;
			break;

		    case 'l':			/* Modo de linha */
			lflag++;
			eflag++;
			break;

		    case 'e':			/* Eco local */
			eflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;
#ifdef	DEBUG
		    case 'd':			/* Debug */
			dflag++;
			break;
#endif	DEBUG
		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	if (argc != 1 && argc != 2)
		help ();

	/*
	 *	Examina a entrada padr�o
	 */
	if (ioctl (0, TCGETS, &ovideo) < 0  ||  isatty (1) == 0)
		error ("$O <stdin> e/ou <stdout> n�o � um terminal");

	/*
	 *	Abre o "endpoint"
	 */
	str = "/dev/itntcp";

	if ((tcp_fd = t_open (str, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", str);

	global_tcp_fd = tcp_fd;

#ifdef	DEBUG
	/*
	 *	Em caso de DEBUG, ...
	 */
	if (dflag && (debugfp = fopen ("debug_file", "w")) == NOFILE)
		error ("$*N�o consegui abrir \"debug_file\"");
#endif	DEBUG

	/*
	 *	Obt�m o endere�o do n� remoto
	 */
	if ((serv_addr = t_node_to_addr (tcp_fd, argv[0], (long *)NULL)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", argv[0]);

	if (vflag)
		printf ("serv_addr dado: %s (%s)\n", t_addr_to_str (serv_addr), argv[0]);

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
		printf ("Port_no do cliente obtido: %d\n", addr.a_port);

	/*
	 *	Obt�m a porta remota, se for o caso
	 */
	if (argv[1] != NOSTR)
	{
		if ((telnet_port = strtol (argv[1], &str, 0)) <= 0)
			error ("$*Porta \"%s\" inv�lida");

		if (telnet_port != TELNET_PORT)
		{
			telnet_port_given++;
			lflag++; eflag++;
		}
	}

	/*
	 *	D� o CONNECT
	 */
	addr.a_port	 = telnet_port;
	addr.a_addr	 = serv_addr;

	call.addr.len	 = sizeof (INADDR);
	call.addr.maxlen = sizeof (INADDR);
	call.addr.buf	 = &addr;

	if (t_connect (tcp_fd, &call, &call) < 0)
	{
		if (errno == TLOOK && t_look (tcp_fd) == T_DISCONNECT)
		{
			error ("A conex�o foi recusada por \"%s\"", argv[0]);
			quit (1);
		}

		error ("$*N�o consegui estabelecer conex�o");
	}

	if (vflag)
		printf ("port_no do servidor obtido: %d\n", addr.a_port);

	/*
	 *	P�e o terminal em RAW com/sem ECHO
	 */
	video = ovideo;

	if (video.t_nline == 0)
		video.t_nline = 24;

	if (video.t_ncol == 0)
		video.t_ncol = 80;

	video.c_oflag &= ~OPOST;
	video.c_lflag &= ~(ISIG|ICANON|ECHO);

	if (eflag)
		video.c_lflag |= ECHO;
#if (0)	/*******************************************************/
#endif	/*******************************************************/

	if (lflag)
		video.c_lflag |= ICANON;

	video.c_cc[VMIN] = 1;

	if (iflag)
	{
		video.c_lflag &= ~CODE;
	   /***	video.c_lflag |= ISO; ***/
	}

	ioctl (0, TCSETNR, &video);

	/*
	 *	Acerta o ECHO
	 */
	if (!telnet_port_given)
	{
		if (eflag)
			send_WILL (NVT_ECHO);
		else
			send_DO (NVT_ECHO);
	}

	/*
	 *	Executa a malha principal
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

	printf ("Conex�o \"telnet\" fechada\n");

	return (0);

}	/* end telnet */

/*
 ****************************************************************
 *	Servi�o de entrada/sa�da regular			*
 ****************************************************************
 */
void
read_write_loop (int tcp_fd)
{
	register int	count, n;
	int		fd_vec[2];
	char		key_area[BLSZ],	tcp_area[BLSZ];
	int		flag, index = -1;
	register char	*key_ptr = key_area, *tcp_ptr;
	char		chr;
	const char	*end_area, *area_ptr;

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
			if (read (0, &chr, sizeof (chr)) == 0)
				chr = video.t_eof;

			*key_ptr++ = chr;

			if   (chr == '\r')
			{
				*key_ptr++ = '\n'; chr = '\n';

				if (video.c_lflag & ECHO)
					putchar ('\n');
			}
			elif (chr == '\n')
			{
				key_ptr[-1] = '\r'; *key_ptr++ = '\n';

				if (video.c_lflag & ECHO)
					{ putchar ('\r'); fflush (stdout); }
			}
			elif (lflag)
			{
				if
				(	chr == video.t_eof ||
					chr == video.t_intr ||
					chr == video.t_quit
				)
					chr = '\n';
			}

			if (!lflag || chr == '\n')
			{
				if (t_snd (tcp_fd, key_area, key_ptr - key_area, T_PUSH) < 0)
					error (NOSTR);

				key_ptr = key_area;
			}

			break;

			/*
			 *	Lembrar que a tela est� RAW,
			 *	portanto pode deixar <cr><nl>
			 */
		    case 1:		/* TCP */
			if ((count = t_nread (tcp_fd)) < 0)
			{
				if (errno == TLOOK && t_look (tcp_fd) == T_ORDREL)
					return;		/* EOF */

				error (NOSTR);
			}

			if (count == 0)	/* Alarme Falso! */
				break;

			if (count > BLSZ)
				count = BLSZ;

			if ((count = t_rcv (tcp_fd, tcp_area, count, &flag)) < 0)
				error (NOSTR);

			if (count == 0)		/* EOF: T�rmino normal */
				return;

			area_ptr = tcp_area; end_area = tcp_area + count;

			for (EVER)
			{
				if (count <= 0)
					break;

				if
				(	telnet_port_given ||
					(tcp_ptr = memchr (area_ptr, IAC, count)) == NOSTR
				)
				{
					if (write (1, area_ptr, count) != count)
						error ("$*Erro de escrita no terminal/v�deo");
					break;
				}

				if ((n = tcp_ptr - area_ptr) > 0) 
				{
					if (write (1, area_ptr, n) != n)
						error ("$*Erro de escrita no terminal/v�deo");

					area_ptr += n; count -= n;
				}

				if (count > 1 && area_ptr[1] == IAC)
				{
					if (write (1, area_ptr, 1) != 1)
						error ("$*Erro de escrita no terminal/v�deo");

					area_ptr += 2; count -= 2; continue;
				}

				/*
				 *	Uma op��o TELNET tem no m�nimo
				 *	3 caracteres: IAC, code, option
				 */
				if (count < 3)
				{
					if (write (1, area_ptr, count) != count)
						error ("$*Erro de escrita no terminal/v�deo");

					break;
				}

				/* Finalmente, uma op��o TELNET */

				n = process_telnet_option (area_ptr, count);
				area_ptr += n; count -= n;

			}	/* end for (EVER) */

			break;

		    default:
			error ("$A chamada ao sistema \"attention\" retornou o �ndice %d inv�lido", index);

		}	/* end switch */

	}	/* end for ever */

}	/* end read_write_loop */

/*
 ****************************************************************
 *	Processa uma op��o TELNET				*
 ****************************************************************
 */
int
process_telnet_option (const char *cp, int count)
{
	int		n = 3, code = cp[1], option = cp[2];

	/*
	 *	N�o pode retornar <= 0
	 */
	if (vflag) printf
	( 	"Recebi: %s %s\r\n",
		edit_telnet_code (code),
		edit_telnet_option (option)
	);

	switch (code)
	{
	    case WILL:
		receive_WILL (option);
		break;

	    case WONT:
		receive_WONT (option);
		break;

	    case DO:
		receive_DO (option);
		break;

	    case DONT:
		receive_DONT (option);
		break;

	    case SUB:
		n = receive_SB (cp, count);
		break;

	    default:
		error ("process_telnet_option: c�digo %02X inv�lido\n", code);
		break;

	}	/* end switch */

	if (n < 3)
		n = 3;

	return (n);

}	/* end process_telnet_option */

/*
 ****************************************************************
 *	Recebi um WILL						*
 ****************************************************************
 */
void
receive_WILL (int option)
{
	register char	*state_ptr = &his_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		if (he_should (option))
			{ *state_ptr = STATE_YES; send_option (DO, option); }
		else
			send_option (DONT, option);
		break;
			
	    case STATE_YES:
		/* Ignore */
		break;

	    case STATE_WANTNO:
		error ("DONT respondido com WILL (op��o %s)", edit_telnet_option (option));
		*state_ptr = STATE_NO;
		break;

	    case STATE_WANTYES:
		*state_ptr = STATE_YES;
#ifdef	WHEN_NEEDED
		send_request (option);
#endif	WHEN_NEEDED
		break;

	    default:
		error ("receive_WILL: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end receive_WILL */

/*
 ****************************************************************
 *	Recebi um WONT						*
 ****************************************************************
 */
void
receive_WONT (int option)
{
	register char	*state_ptr = &his_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		/* Ignore */
		break;

	    case STATE_YES:
		*state_ptr = STATE_NO;
		send_option (DONT, option);
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		*state_ptr = STATE_NO;
		break;

	    default:
		error ("receive_WONT: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end receive_WONT */

/*
 ****************************************************************
 *	Pede para ligar						*
 ****************************************************************
 */
void
send_DO (int option)
{
	register char	*state_ptr = &his_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		*state_ptr = STATE_WANTYES;
		send_option (DO, option);
		break;

	    case STATE_YES:
		error ("Op��o %s j� ligada", edit_telnet_option (option));
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		error ("Op��o %s em processamento", edit_telnet_option (option));
		break;

	    default:
		error ("send_DO: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end send_DO */

#ifdef	WHEN_NEEDED
/*
 ****************************************************************
 *	Pede para desligar					*
 ****************************************************************
 */
void
send_DONT (int option)
{
	register char	*state_ptr = &his_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		error ("Op��o %s j� desligada", edit_telnet_option (option));
		break;

	    case STATE_YES:
		*state_ptr = STATE_WANTNO;
		send_option (DONT, option);
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		error ("Op��o %s em processamento", edit_telnet_option (option));
		break;

	    default:
		error ("send_DONT: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end send_DONT */
#endif	WHEN_NEEDED

/*
 ****************************************************************
 *	Recebi um DO						*
 ****************************************************************
 */
void
receive_DO (int option)
{
	register char	*state_ptr = &my_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		if (we_should (option))
		{
			*state_ptr = STATE_YES;
			send_option (WILL, option);
			enable (option);
		}
		else
		{
			send_option (WONT, option);
		}
		break;
			
	    case STATE_YES:
		/* Ignore */
		break;

	    case STATE_WANTNO:
		error ("WONT respondido com DO (op��o %s)", edit_telnet_option (option));
		*state_ptr = STATE_NO;
		break;

	    case STATE_WANTYES:
		*state_ptr = STATE_YES;
		enable (option);
		break;

	    default:
		error ("receive_DO: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end receive_DO */

/*
 ****************************************************************
 *	Recebi um DONT						*
 ****************************************************************
 */
void
receive_DONT (int option)
{
	register char	*state_ptr = &my_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		/* Ignore */
		break;

	    case STATE_YES:
		disable (option);
		*state_ptr = STATE_NO;
		send_option (WONT, option);
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		*state_ptr = STATE_NO;
		break;

	    default:
		error ("receive_DONT: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end receive_DONT */

/*
 ****************************************************************
 *	Concorda em ligar					*
 ****************************************************************
 */
void
send_WILL (int option)
{
	register char	*state_ptr = &my_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		*state_ptr = STATE_WANTYES;
		send_option (WILL, option);
		break;

	    case STATE_YES:
		error ("Op��o %s j� ligada", edit_telnet_option (option));
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		error ("Op��o %s em processamento", edit_telnet_option (option));
		break;

	    default:
		error ("send_WILL: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end send_WILL */

#ifdef	WHEN_NEEDED
/*
 ****************************************************************
 *	N�o concorda em ligar					*
 ****************************************************************
 */
void
send_WONT (int option)
{
	register char	*state_ptr = &my_state[option];

	switch (*state_ptr)
	{
	    case STATE_NO:
		error ("Op��o %s j� desligada", edit_telnet_option (option));
		break;

	    case STATE_YES:
		*state_ptr = STATE_WANTNO;
		send_option (WONT, option);
		break;
			
	    case STATE_WANTNO:
	    case STATE_WANTYES:
		error ("Op��o %s em processamento", edit_telnet_option (option));
		break;

	    default:
		error ("send_WONT: Estado %d inv�lido (op��o %s)", *state_ptr, edit_telnet_option (option));
		break;

	}	/* end switch */

}	/* end send_WONT */
#endif	WHEN_NEEDED

/*
 ****************************************************************
 *	Concordamos com a sua op��o?				*
 ****************************************************************
 */
int
he_should (int option)
{
	switch (option)
	{
	    case NVT_ECHO:
		if (eflag)
			return (0);
		else
			return (1);
		break;

	    case NVT_SUPRESS_GO_AHEAD:
		return (1);

	    case NVT_TERMINAL_TYPE:
		return (0);

	    case NVT_WINDOW_SIZE:
		return (0);

#if (0)	/*******************************************************/
	    default:
		error ("he_should: Op��o %d desconhecida", option);
		break;
#endif	/*******************************************************/

	}	/* end switch */

	return (0);

}	/* end he_should */

/*
 ****************************************************************
 *	Concordamos com a sua op��o?				*
 ****************************************************************
 */
int
we_should (int option)
{
	switch (option)
	{
	    case NVT_ECHO:
		if (eflag)
			return (1);
		else
			return (0);
		break;

	    case NVT_SUPRESS_GO_AHEAD:
		return (1);

	    case NVT_TERMINAL_TYPE:
		return (1);

	    case NVT_WINDOW_SIZE:
		return (1);

#if (0)	/*******************************************************/
	    default:
		error ("we_should: Op��o %d desconhecida", option);
		break;
#endif	/*******************************************************/

	}	/* end switch */

	return (0);

}	/* end we_should */

/*
 ****************************************************************
 *	Liga a op��o						*
 ****************************************************************
 */
void
enable (int option)
{
	switch (option)
	{
	    case NVT_ECHO:
		video.c_lflag |= ECHO;
		ioctl (0, TCSETNR, &video);
		break;

	    case NVT_SUPRESS_GO_AHEAD:
		break;

	    case NVT_TERMINAL_TYPE:
		break;

	    case NVT_WINDOW_SIZE:
		send_window_size ();
		break;

	    default:
		error ("enable: Op��o %d desconhecida", option);
		break;

	}	/* end switch */

}	/* end enable */

/*
 ****************************************************************
 *	Desliga a op��o						*
 ****************************************************************
 */
void
disable (int option)
{
	switch (option)
	{
	    case NVT_ECHO:
		video.c_lflag &= ~ECHO;
		ioctl (0, TCSETNR, &video);
		break;

	    case NVT_SUPRESS_GO_AHEAD:
		break;

	    case NVT_TERMINAL_TYPE:
		break;

	    case NVT_WINDOW_SIZE:
		break;

	    default:
		error ("disable: Op��o %d desconhecida", option);
		break;

	}	/* end switch */

}	/* end disable */

/*
 ****************************************************************
 *	Recebe um comando SB					*
 ****************************************************************
 */
int
receive_SB (register const char *cp, int count)
{
	int		option = cp[2];

	switch (option)
	{
	    case NVT_TERMINAL_TYPE:
		return (send_terminal_type (cp, count));

	    default:
		error ("receive_SB: Op��o %d desconhecida", option);
		return (3);

	}	/* end switch */

}	/* end he_should */

/*
 ****************************************************************
 *	Envia o tipo do terminal				*
 ****************************************************************
 */
int
send_terminal_type (const char *cp, int count)
{
	register int		n;
	register char		c;
	register const char	*term;
	char			area[4];
	int			tcp_fd = global_tcp_fd;

	if (count < 6)
		return (3);

	if ((c = cp[3]) != 1 /* ==  SEND */)
		error ("Esperava um SEND ao inv�s de %d", c);

	if ((c = cp[4]) != IAC)
		error ("Esperava um IAC ao inv�s de %d", c);

	if ((c = cp[5]) != SE)
		error ("Esperava um SE ao inv�s de %d", c);

	if ((term = getenv ("TERM")) == NOSTR)
		term = "UNKNOWN";

	n = strlen (term);

	area[0] = IAC;
	area[1] = SUB;
	area[2] = NVT_TERMINAL_TYPE;
	area[3] = 0 /* == IS */;

	if (t_snd (tcp_fd, area, 4, 0) != 4)
		error (NOSTR);

	if (t_snd (tcp_fd, term, n, 0) != n)
		error (NOSTR);

	area[0] = IAC;
	area[1] = SE;

	if (t_snd (tcp_fd, area, 2, T_PUSH) != 2)
		error (NOSTR);

	if (vflag) printf
	( 	"Enviei: TERM=%s\r\n",
		term
	);

	return (6);

}	/* end send_terminal_type */

/*
 ****************************************************************
 *	Envia o tamanho da janela				*
 ****************************************************************
 */
void
send_window_size (void)
{
	char			area[9];

	area[0] = IAC;
	area[1] = SUB;
	area[2] = NVT_WINDOW_SIZE;
	area[3] = 0;
	area[4] = video.t_ncol;
	area[5] = 0;
	area[6] = video.t_nline;
	area[7] = IAC;
	area[8] = SE;

	if (t_snd (global_tcp_fd, area, sizeof (area), T_PUSH) != sizeof (area))
		error (NOSTR);

	if (vflag) printf
	( 	"Enviei: WINDOW_SIZE=(%d,%d)\r\n",
		area[4], area[6]
	);

}	/* end send_window_size */

/*
 ****************************************************************
 *	Envia uma op��o						*
 ****************************************************************
 */
void
send_option (int code, int option)
{
	char		area[3];

	area[0] = IAC;
	area[1] = code;
	area[2] = option;

	if (t_snd (global_tcp_fd, area, 3, T_PUSH) != 3)
		error (NOSTR);

	if (vflag) printf
	( 	"Enviei: %s %s\r\n",
		edit_telnet_code (code),
		edit_telnet_option (option)
	);

}	/* end send_option */

/*
 ****************************************************************
 *	Edita um c�digo TELNET					*
 ****************************************************************
 */
typedef struct
{
	int	c_code;		/* C�digo num�rico */
	char	c_name[8];	/* C�digo em ISO */

}	CODE_TABLE;

const CODE_TABLE	code_table[] =
{
	WILL,	"WILL",
	WONT,	"WON'T",
	DO,	"DO",
	DONT,	"DON'T",
	SUB,	"SB",
	0
};

const char *
edit_telnet_code (int code)
{
	register const CODE_TABLE	*cp;
	static char			nm[16];

	for (cp = code_table; cp->c_code != 0; cp++)
	{
		if (cp->c_code == code)
			return (cp->c_name);
	}

	sprintf (nm, "??? (%d, 0x%02X)", code, code);

	return (nm);

}	/* end edit_telnet_code */

/*
 ****************************************************************
 *	Edita uma op��o TELNET					*
 ****************************************************************
 */
typedef struct
{
	int	o_option;	/* C�digo num�rico da op��o */
	char	o_name[20];	/* Op��o em ISO */

}	OPTION_TABLE;

const OPTION_TABLE	option_table[] =
{
	NVT_ECHO,		"ECHO",
	NVT_SUPRESS_GO_AHEAD,	"SUPRESS_GO_AHEAD",	
	NVT_NAOL,		"NAOL (ncol)",
	NVT_NAOP,		"NAOP (nline)",
	NVT_TERMINAL_TYPE,	"TERMINAL_TYPE",
	NVT_WINDOW_SIZE,	"WINDOW_SIZE",
	0
};

const char *
edit_telnet_option (int option)
{
	register const OPTION_TABLE	*cp;
	static char			nm[16];

	for (cp = option_table; cp->o_option != 0; cp++)
	{
		if (cp->o_option == option)
			return (cp->o_name);
	}

	sprintf (nm, "??? (%d, 0x%02X)", option, option);

	return (nm);

}	/* end edit_telnet_option */

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
	int			event;

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
		if (errno == TLOOK)
		{
			event = t_look (global_tcp_fd);
	
			fprintf (stderr, " (%s)", t_strevent (global_tcp_fd, event));
	
			if (event ==  T_DISCONNECT)
				{ fprintf (stderr, "\r\n"); quit (1); }
		}
		elif (errno != 0)
		{
			fprintf (stderr, " (%s)", strerror (errno));
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
		"%s - comunica com um n� remoto utilizando o protocolo TELNET\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-eliv] <n�_remoto> [<porta_remota>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Modo caractere a caractere com eco remoto\n"
		"\t-e: Modo caractere a caractere com eco local\n"
		"\t-l: Modo linha a linha (com eco local)\n"
		"\t-i: N�o converte o c�digo na recep��o\n"
		"\t-v: Verboso\n"
	);

	exit (2);

}	/* end help */
