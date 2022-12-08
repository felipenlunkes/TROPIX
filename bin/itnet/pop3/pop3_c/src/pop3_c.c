/*
 ****************************************************************
 *								*
 *			pop3_c.c				*
 *								*
 *	Post Office Protocol - Version 3 (cliente)		*
 *								*
 *	Vers�o	3.1.0, de 09.10.98				*
 *		4.5.0, de 16.10.03				*
 *								*
 *	M�dulo: POP3_C						*
 *		Utilit�rios de comunica��es			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <pwd.h>
#include <termio.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <xti.h>

#include "../h/pop3_c.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char		pgversion[] =  "Vers�o:	4.5.0, de 16.10.03";

const char		tcp_dev_nm[] = "/dev/itntcp";

entry int		aflag;			/* Todas as cartas */
entry int		vflag;			/* Verbose */

entry int		received_intr;		/* Veio um <^C> */

entry char		local_node_nm[80];	/* Nome do n� local */

entry const char	*remote_node_nm;	/* Nome do <n� remoto> */

entry const char	*local_user_nm,		/* Nome do usu�rio local e remoto */
			*remote_user_nm;	/* Nome do usu�rio */

entry int		user_uid;		/* UID do usu�rio */

entry int		user_gid;		/* GID do usu�rio */

entry INADDR		local_tcp_addr;		/* Endere�o local de controle */

entry int		tcp_fd;			/* Descritor da linha de controle */

entry FILE		*tcp_fp;		/* FILE da linha de controle */

entry FILE		*tty_fp;		/* Arquivo para "askyesno" */

entry int		snd_dis;		/* Em caso de erro, desconecta */

entry int		LINE_SZ;		/* N�mero m�ximo de caracteres por linha */

entry char		cp_askyesno_force;	/* Para as nossas vers�es de "askyesno" */
entry int		cp_askyesno_force_seen;

entry char		rm_askyesno_force;
entry int		rm_askyesno_force_seen;

/*
 ****************************************************************
 *	Post Office Protocol - Version 3 (cliente)		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int			opt, status;
	const char		*env, *remote_user_nm_str = NOSTR;
	char			*env_cp, *str;
	char			uidl = 0;
	TERMIO			termio;
	const PASSWD		*pw;
	char			line[16];

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "r:avH")) != EOF)
	{
		switch (opt)
		{
		    case 'r':			/* Caixa postal remota */
			remote_user_nm_str = optarg;
			break;

		    case 'a':			/* Todas as cartas */
			aflag++;
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

	/*
	 *	pop3 [-rfv] [usu�rio@][<n�_remoto>]
	 *
	 *	O <usu�rio> e <n�_remoto> podem tamb�m serem dados no ambiente
	 */
	argv += optind;
	argc -= optind;

	if (argc > 1)
		help ();

#ifdef	ON_INTR
	/*
	 *	Prepara o retorno para o caso <^C>
	 */
	signal (SIGINT, on_intr);
#endif	ON_INTR

	/*
	 *	Abre o terminal para "askyesno"
	 */
	if ((tty_fp = fopen ("/dev/tty", "r")) == NOFILE)
		error ("$*N�o consegui abrir \"/dev/tty\"");

	/*
	 *	Obt�m o TERMIO do v�deo
	 */
	if (ioctl (fileno (tty_fp), TCGETS, &termio) < 0)
		error ("$*N�o consegui obter o TERMIO de \"/dev/tty\"");

	/*
	 *	Obt�m o n�mero de linhas e colunas
	 */
	if (termio.t_nline == 0)
		termio.t_nline = 24;

	if (termio.t_ncol == 0)
		termio.t_ncol = 80;

	LINE_SZ = termio.t_ncol;

	/*
	 *	Retira o nome do usu�rio/n� da linha de comando
	 */
	if   (argv[0] == NOSTR)
	{
	   /***	remote_user_nm = NOSTR; ***/
	   /***	remote_node_nm = NOSTR; ***/
	}
	elif ((str = strchr (argv[0], '@')) == NOSTR)
	{
	   /***	remote_user_nm = NOSTR; ***/
		remote_node_nm = argv[0];
	}
	else
	{
		*str++ = '\0';

	   	remote_user_nm = argv[0];

		if (str[0] != '\0')
			remote_node_nm	= str;
	}

	/*
	 *	Complementa o nome do usu�rio/n� do ambiente
	 */
	if ((remote_user_nm == NOSTR || remote_node_nm == NOSTR) && (env = getenv ("POP3")) != NOSTR)
	{
		env_cp = alloca (strlen (env) + 1); strcpy (env_cp, env);

		if ((str = strchr (env_cp, '@')) == NOSTR)
		{
			if (remote_node_nm == NOSTR)
				remote_node_nm = env_cp;
		}
		else
		{
			*str++ = '\0';
	
			if (remote_user_nm == NOSTR)
				remote_user_nm = env_cp;

			if (remote_node_nm == NOSTR && str[0] != '\0')
				remote_node_nm = str;
		}
	}

	if (remote_user_nm_str != NOSTR)
		remote_user_nm = remote_user_nm_str;
	
	if (remote_node_nm == NOSTR)
		{ error ("N�o foi dado o <n�_remoto>\n"); help (); }

	/*
	 *	�ltime chance de obter o nome/UID do usu�rio
	 */
	if (local_user_nm == NOSTR)
		local_user_nm = getenv ("USER");

	if (local_user_nm == NOSTR)
		local_user_nm = getlogin ();

	if (local_user_nm == NOSTR)
		local_user_nm = (getpwuid (getuid ()))->pw_name;

	if ((pw = getpwnam (local_user_nm)) == NOPASSWD)
		error ("$N�o consegui obter o UID do usu�rio \"%s\"", local_user_nm);

	if (remote_user_nm == NOSTR)
		remote_user_nm = local_user_nm;

	user_uid = pw->pw_uid;
	user_gid = pw->pw_gid;

	/*
	 *	Conecta com o servidor
	 */
	connect ();

	if (get_reply () != OK)
		quit ();

	read_and_store_uidl_or_list ();

	/*
	 *	Obt�m as mensagens j� presentes do usu�rio
	 */
	get_mbox ();

	/*
	 *	Espera o final da leitura dos UIDls
	 */
	if (wait (&status) < 0)
		error ("$*Erro na chamada a \"wait\"");

	/*
	 *	Agora l� as cartas recebidas
	 */
	rewind (uidl_fp);  

	if (fngets (line, sizeof (line), uidl_fp) == NOSTR)  
		error ("$*Erro na leitura do arquivo tempor�rio");

	uidl = strtol (line, &env, 0);

	if   (uidl < 0)
		do_quit_and_exit ();
	elif (uidl > 0)
		decode_uidl ();
	else
		decode_list ();

	/*
	 *	Atualiza a caixa postal local
	 */
	update_local_mbox ();

	/*
	 *	Se for o caso, remove as cartas do servidor
	 */
	if (aflag)
		delete_msg_in_remote_mbox ();

	/*
	 *	Terminou ...
	 */
	do_quit_and_exit ();

	return (1);

}	/* end pop3 */

/*
 ****************************************************************
 *	Rotina de conex�o com o servidor remoto			*
 ****************************************************************
 */
void
connect (void)
{
	INADDR		serv_addr, remote_addr, bind_addr;
	T_BIND		bind;
	T_CALL		snd_call, rcv_call;
	const char	*cp;

	/*
	 *	Abre o dispositivo TCP de contr�le
	 */
	if ((tcp_fd = t_open (tcp_dev_nm, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", tcp_dev_nm);

	/*
	 *	Obt�m o endere�o n� remoto
	 */
	if ((remote_addr.a_addr = t_node_to_addr (tcp_fd, remote_node_nm, &local_tcp_addr.a_addr)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", remote_node_nm);

	remote_addr.a_port = POP3_PORT;

	/*
	 *	Obt�m o nome do n� local
	 */
	if ((cp = t_addr_to_node (tcp_fd, local_tcp_addr.a_addr)) == NOSTR)
		error ("$N�o consegui obter o nome do n� local");

	strcpy (local_node_nm, cp);

	/*
	 *	Prepara a utiliza��o da "stdio" com a comunica��o de controle
	 */
	if ((tcp_fp = fdopen (tcp_fd, "r")) == NOFILE)
		error ("$*N�o consegui obter o FILE da comunica��o de controle");

	/*
	 *	Associa um endere�o local
	 */
	bind_addr.a_addr = 0;

	bind.addr.len	 = 0;
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &bind_addr;

	bind.qlen	 = 0;

	if (t_bind (tcp_fd, &bind, &bind) < 0)
		error ("$*N�o consegui associar um endere�o local\n");

	if (vflag > 1)
		printf ("Port_no de controle obtido: %d\n", ((INADDR *)bind.addr.buf)->a_port);

	/*
	 *	Executa o "connect"
	 */
	snd_call.addr.len    = sizeof (INADDR);
	snd_call.addr.buf    = &remote_addr;

	rcv_call.addr.maxlen = sizeof (INADDR);
	rcv_call.addr.buf    = &serv_addr;

	if (t_connect (tcp_fd, &snd_call, &rcv_call) < 0)
	{
		if (errno == TLOOK && t_look (tcp_fd) == T_DISCONNECT)
		{
			error ("A conex�o foi recusada por \"%s\"", remote_node_nm);
			exit (1);
		}

		error ("$*N�o consegui estabelecer conex�o");
	}

	snd_dis++;	/* De agora adiante, erros desconectam */

	if (vflag)
		printf ("Conectado a \"%s\"\n", remote_node_nm);

}	/* end connect */

/*
 ****************************************************************
 *	Executa o comando "QUIT" e termina			*
 ****************************************************************
 */
void
do_quit_and_exit (void)
{
	if (status_fp != NOFILE)
		fclose (status_fp);

	comando (1, "QUIT");
	quit ();

}	/* end do_quit_and_exit */

/*
 ****************************************************************
 *	Termina o programa graciosamente			*
 ****************************************************************
 */
void
quit (void)
{
	if (t_sndrel (tcp_fd) < 0)
		error ("$*Erro no SNDREL");

	if (t_rcvrel (tcp_fd) < 0)
		error ("$*Erro no RCVREL");

	t_close (tcp_fd);

 	exit (0);

}	/* end quit */

#ifdef	ON_INTR
/*
 ****************************************************************
 *	Tratamento de interrup��es				*
 ****************************************************************
 */
void
on_intr (int signo, ...)
{
	signal (SIGINT, SIG_IGN);

	received_intr++;

}	/* end on_intr */
#endif	ON_INTR

/*
 ****************************************************************
 *    Obt�m uma resposta afirmativa ou negativa para a c�pia	*
 ****************************************************************
 */
int
cp_askyesno (void)
{
	int		c, reply;

	/*
	 *	Se j� foi dado um "S" ou "N", ...
	 */
	if   (cp_askyesno_force_seen > 0)
		{ fprintf (stderr, "SIM\n"); return (1); }
	elif (cp_askyesno_force_seen < 0)
		{ fprintf (stderr, "N�O\n"); return (-1); }

	/*
	 *	L� um caractere (na realidade uma linha)
	 */
    again:
	fflush (stderr);

	while ((c = reply = getc (tty_fp)) == ' ' || c == '\t')
		/* vazio */;

	for (EVER)
	{
		if   (c == EOF)
			{ fprintf (stderr, "???\n"); return (0); }
		elif (c == '\n')
			break;

		c = getc (tty_fp);

	}	/* end for (EVER) */

	/*
	 *	Analisa o caractere lido
	 */
	switch (reply)
	{
	    case '\n':
		return (0);

	    case 's':
	    case 'y':
		return (1);

	    case 'n':
		return (-1);

	    case 'S':
	    case 'Y':
		if (cp_askyesno_force)
			cp_askyesno_force_seen = 1;

		return (1);

	    case 'N':
		if (cp_askyesno_force)
			cp_askyesno_force_seen = -1;

		return (-1);

	    default:
		fprintf (stderr, "Sim ou N�o: ");
		goto again;

	}	/* end switch */

}	/* end cp_askyesno */

/*
 ****************************************************************
 *    Obt�m uma resposta afirmativa ou negativa para a remo��o	*
 ****************************************************************
 */
int
rm_askyesno (void)
{
	int		c, reply;

	/*
	 *	Se j� foi dado um "S" ou "N", ...
	 */
	if   (rm_askyesno_force_seen > 0)
		{ fprintf (stderr, "SIM\n"); return (1); }
	elif (rm_askyesno_force_seen < 0)
		{ fprintf (stderr, "N�O\n"); return (-1); }

	/*
	 *	L� um caractere (na realidade uma linha)
	 */
    again:
	fflush (stderr);

	while ((c = reply = getc (tty_fp)) == ' ' || c == '\t')
		/* vazio */;

	for (EVER)
	{
		if   (c == EOF)
			{ fprintf (stderr, "???\n"); return (0); }
		elif (c == '\n')
			break;

		c = getc (tty_fp);

	}	/* end for (EVER) */

	/*
	 *	Analisa o caractere lido
	 */
	switch (reply)
	{
	    case '\n':
		return (0);

	    case 's':
	    case 'y':
		return (1);

	    case 'n':
		return (-1);

	    case 'S':
	    case 'Y':
		if (rm_askyesno_force)
			rm_askyesno_force_seen = 1;

		return (1);

	    case 'N':
		if (rm_askyesno_force)
			rm_askyesno_force_seen = -1;

		return (-1);

	    default:
		fprintf (stderr, "Sim ou N�o: ");
		goto again;

	}	/* end switch */

}	/* end rm_askyesno */

/*
 ****************************************************************
 *	Imprime uma mensagem de erro (cliente)			*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	va_list	args;
	const char	*fmt = format;
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
				{ putc ('\n', stderr); exit (1); }
		}
		elif (save_errno != 0)
		{
			fprintf (stderr, " (%s)", strerror (save_errno));
		}
	}

	putc ('\n', stderr);

	if (abrt == '$')
		tcp_abort (1);

	va_end (args);

}	/* end error */

/*
 ****************************************************************
 *	Encerra as atividades (desconectando o TCP)		*
 ****************************************************************
 */
void
tcp_abort (int n)
{
	if (snd_dis)
		t_snddis (tcp_fd, (T_CALL *)NULL);

	exit (n);

}	/* end tcp_abort */

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
		"%s - acessa uma caixa postal remota atrav�s do protocolo POP3\n"
		"\n%s\n"
		"\nSintaxe:\n"
	 	"\t%s [-av] [-r <caixa postal remota>] [<usu�rio>@][<n�_remoto>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-r: Nome da caixa postal remota\n"
		"\t-a: Oferece todas as cartas da caixa postal remota para a remo��o\n"
		"\t-v: Verboso\n"
	);

	exit (2);

}	/* end help */
