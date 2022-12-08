/*
 ****************************************************************
 *								*
 *			tcmpto_s.c				*
 *								*
 *	Compara��o remota de �rvores (servidor)			*
 *								*
 *	Vers�o	2.3.0, de 29.10.91				*
 *		4.5.0, de 03.06.03				*
 *								*
 *	M�dulo: TCMPTO_S/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <xti.h>

#include "../h/tcmpto_s.h"
#include "../../tnet.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	TCMPTO_PORT	137

const char	TCMPTO_VERSION[] = "TCMPTO,3.0.5";

/*
 ****** Os diversos (e muitos) indicadores **********************
 */
entry int		fromflag;	/* Caminhada na �rvore REMOTA */
entry int		cpflag;		/* Copie diretamente (sem compara��o) */

entry int		pflag;		/* Senha necess�ria */
entry int		vflag;		/* verbose flag */

entry int		Cflag;		/* Usando compress�o */
entry int		gflag;		/* Gere o "garfield" */
entry int		Lflag;		/* local = N�o entre em diret�rios */
entry int		qflag;		/* Compara��o r�pida de objetos */
entry int		mflag;		/* Copia tamb�m o estado do arquivo */
entry int		dotflag;	/* N�o ignorar ".old" */

entry int		Bflag;		/* Debug */

entry int		tcp_fd;		/* C�pia do "fd" */

entry int		snd_dis = 0;	/* Disconecta em caso de erro (se != 0) */

entry int		global_log_fd;	/* Para "error" */
entry FILE		*global_log_fp;

/*
 ****** Estruturas deste m�dulo *********************************
 */
entry char		local_user_nm[16];

entry char		remote_user_nm[16];

entry int		local_user_uid;

entry int		local_user_gid;

entry int		remote_user_euid;

entry char		file_prefix_nm[2*BLSZ];		/* Prefixo para os arquivos */

entry char		*file_prefix_ptr;		/* Ponteiro para o '\0' */

entry PASSWD		no_user  = {"", "?????????????", "", 1 }; /* Inexistente */

const char		no_pwd[]  =	"-------------";	/* Senha nula */

#undef	RETYPE
#ifdef	RETYPE
const char		superuser[] = "<superuser>";		/* Nome do Retype */
#endif	RETYPE

extern int		MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

/*
 ******	Os padr�es **********************************************
 */
entry const char	*inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */

entry const char	*exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */

/*
 ****************************************************************
 *	Compara��o remota de �rvores (servidor)			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	**p;
	const PASSWD	*pwd;
	INADDR		client_addr, serv_addr[2];
	INADDR		tcp_addr[2];
	T_BIND		bind;
	T_CALL		call;
	int		sequence, listen_fd;
	int		listen_port;
	SEGFLAGS	segflags;
	char		*rmsg;

	/*
	 *	Prepara vari�veis de "error" ainda como superusu�rio
	 */
	if ((global_log_fd = open ("/var/adm/itnetlog", O_WRONLY|O_APPEND)) >= 0)
	{
		if ((global_log_fp = fdopen (global_log_fd, "w")) == NOFILE)
			global_log_fd = -1;
	}

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "pvMB")) != EOF)
	{
		switch (opt)
		{
		    case 'p':			/* Senha necess�ria */
			pflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'M':			/* Stick in memory */
			exit (0);

		    case 'B':			/* debug flag */
			Bflag++;
			vflag++;
			break;

		    default:			/* Erro */
			error ("Op��o inv�lida: '%c'", opt);
			break;

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Nos seguintes sinais, desconecta a linha
	 */
	signal (SIGINT,  on_signal);
	signal (SIGTERM, on_signal);

	/*
	 *	tcmpto_s [-v] <listen_port> <listen_fd> <client_addr> <client_port> <sequence>
	 */
#ifdef	DEBUG
	if (Bflag) error
	(	"%s: %s <%s> <%s> <%s> <%s> <%s>",
		pgname, vflag ? "-v" : "",
		argv[0], argv[1], argv[2], argv[3], argv[4]
	);
#endif	DEBUG

	if (argc != 5) error
	(	"$%s: N�mero inv�lido de argumentos: %d",
		pgname, argc
	);

	listen_port	   = atoi (argv[0]);
	listen_fd	   = atoi (argv[1]);
	client_addr.a_addr = t_str_to_addr (argv[2]);
	client_addr.a_port = atoi (argv[3]);
	sequence	   = atoi (argv[4]);

	if ((tcp_fd = t_open ("/dev/itntcp", O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir o dispositivo");

	/*
	 *	Vou realizar o "bind"
	 */
	serv_addr[0].a_port = listen_port;	/* Usa o TNET_PORT */
	serv_addr[1].a_addr = client_addr.a_addr;
	serv_addr[1].a_port = client_addr.a_port;

	bind.addr.maxlen = 0;
	bind.addr.len	 = 2 * sizeof (INADDR);
	bind.addr.buf	 = serv_addr;

	bind.qlen	 = 0;

	if (t_bind (tcp_fd, &bind, (T_BIND *)NULL) < 0)
		error ("$*N�o consegui atribuir endere�o");

	/*
	 *	Vou realizar o "accept"
	 */
	call.opt.len = 0;
	call.udata.len = 0;
	call.sequence = sequence;

	call.addr.len = sizeof (INADDR);
	call.addr.maxlen = sizeof (INADDR);
	call.addr.buf = &client_addr;

#ifdef	DEBUG
	if (Bflag) error
	(	"Vou dar accept para (%s, %d)",
		t_addr_to_str (client_addr.a_addr), client_addr.a_port
	);
#endif	DEBUG

	if (t_accept (listen_fd, tcp_fd, &call) < 0)
		error ("$*Erro no t_accept");

	/*
	 *	Agora n�o precisa mais do "listen_fd"
	 */
	t_close (listen_fd);

	snd_dis++;	/* Aborta em caso de erro fatal */

	/*
	 *	Envia o nome do servidor e o no. do protocolo
	 */
	t_snd_msg (0, TCMPTO_VERSION);

	/*
	 *	Recebe o segmento de flags
	 */
	if (t_rcv (tcp_fd, &segflags, sizeof (segflags), (int *)NULL) != sizeof (segflags))
		error (NOSTR);

	if (ENDIAN_LONG (segflags.seg_type) != FFLAGS)
		error ("$Esperava um segmento FFLAGS");

	fromflag    = ENDIAN_LONG (segflags.seg_flags[0]);
	cpflag      = ENDIAN_LONG (segflags.seg_flags[1]);
	gflag	    = ENDIAN_LONG (segflags.seg_flags[2]);
	Lflag	    = ENDIAN_LONG (segflags.seg_flags[3]);
	vflag	   += ENDIAN_LONG (segflags.seg_flags[4]);
	qflag	    = ENDIAN_LONG (segflags.seg_flags[5]);
	mflag	    = ENDIAN_LONG (segflags.seg_flags[6]);
	dotflag	    = ENDIAN_LONG (segflags.seg_flags[7]);
	Bflag	   += ENDIAN_LONG (segflags.seg_flags[8]);
	Cflag	    = ENDIAN_LONG (segflags.seg_flags[9]);
	MAX_BIT_SZ  = ENDIAN_LONG (segflags.seg_flags[10]);

	/*
	 *	Recebe os nomes dos usu�rios local e remoto
	 */
	if (t_rcv (tcp_fd, &remote_user_euid, sizeof (remote_user_euid), (int *)NULL) < 0)
		error (NOSTR);

#ifdef	LITTLE_ENDIAN
	remote_user_euid = ENDIAN_LONG (remote_user_euid);
#endif	LITTLE_ENDIAN

	if (t_rcv (tcp_fd, remote_user_nm, sizeof (remote_user_nm), (int *)NULL) < 0)
		error (NOSTR);

	if (t_rcv (tcp_fd, local_user_nm, sizeof (local_user_nm), (int *)NULL) < 0)
		error (NOSTR);

	/*
	 *	Decide se vai ou n�o pedir a senha do usu�rio
	 */
	if ((pwd = getpwnam (local_user_nm)) == NOPASSWD)
		pwd = &no_user;
	else
		strcpy (file_prefix_nm, pwd->pw_dir);

	local_user_uid = pwd->pw_uid;
	local_user_gid = pwd->pw_gid;

#if (0)	/*******************************************************/
	if (!ideq (local_user_nm, remote_user_nm) && !streq (pwd->pw_passwd, no_pwd))
		passwd_needed++;
#endif	/*******************************************************/

#if (0)	/*************************************/
	if (pwd->pw_uid == 0 && remote_user_euid != 0)
		passwd_needed++;
#endif	/*************************************/

	/*
	 *	Processa a senha do usu�rio
	 */
	if (t_getaddr (tcp_fd, tcp_addr) < 0)
		error ("$*N�o consegui obter os endere�os TCP");

	if
	(	!pflag || streq (pwd->pw_passwd, no_pwd)
#define	LOCAL_NETWORK_NOPWD
#ifdef	LOCAL_NETWORK_NOPWD
		|| (tcp_addr[0].a_addr & 0xFFFFFF00) == (tcp_addr[1].a_addr & 0xFFFFFF00)
#if (0)	/*******************************************************/
		|| (client_addr.a_addr & 0xFFFF0000) == 0xC0A80000	/* 192.168..... */
#endif	/*******************************************************/
#endif	LOCAL_NETWORK_NOPWD
	)
	{
		t_snd_msg (0, NOSTR);
	}
	else
	{
		t_snd_msg (1, NOSTR);

		t_rcv_msg (&rmsg);

		if (!streq (crypt (rmsg, pwd->pw_passwd), pwd->pw_passwd))
			{ t_snd_msg (-1, "Senha incorreta"); goto rel; }
		else
			t_snd_msg (0, NOSTR);
	}

	/*
	 *	Processa a (segunda) senha do superusu�rio
	 */
#ifdef	RETYPE
	if (pwd->pw_uid != 0 || remote_user_euid == 0)
	{
		t_snd_msg (0, NOSTR);
	}
	else
	{
		if ((pwd = getpwnam (superuser)) == NOPASSWD)
		{
			error ("N�o encontrei a senha do SUPERUSU�RIO");
			t_snd_msg (0, NOSTR);
		}
		else
		{
			t_snd_msg (1, NOSTR);

			t_rcv_msg (&rmsg);

			if (!streq (crypt (rmsg, pwd->pw_passwd), pwd->pw_passwd))
				{ t_snd_msg (-1, "Senha incorreta"); goto rel; }
			else
				t_snd_msg (0, NOSTR);
		}
	}
#else
	t_snd_msg (0, NOSTR);
#endif	RETYPE

	/*
	 *	Recebe o diret�rio prefixo dos nomes dos arquivo
	 */
	t_rcv_msg (&rmsg);

	if (rmsg != NOSTR)
		strcpy (file_prefix_nm, rmsg);

#if (0)	/*************************************/
	strcat (file_prefix_nm, "/");
#endif	/*************************************/

	file_prefix_ptr = strend (file_prefix_nm);

	/*
	 *	Recebe e guarda os padr�es
	 */
	if (fromflag)
	{
		for (p = inc_pat; /* vazio */; /* vazio */)
		{
			if (t_rcv_msg (&rmsg) < 0)
				break;

			*p++ = strdup (rmsg);

		}	/* end for (EVER) */

		for (p = exc_pat; /* vazio */; /* vazio */)
		{
			if (t_rcv_msg (&rmsg) < 0)
				break;

			*p++ = strdup (rmsg);

		}	/* end for (EVER) */

	}	/* end if (fromflag) */

	/*
	 *	Processa as <�rvores>
	 */
	setgid (local_user_gid);
	setuid (local_user_uid);

	error
	(	"Login para \"%s@%s\"",
		local_user_nm,
		t_addr_to_str (client_addr.a_addr)
	);

	walk ();

	/*
	 *	Executa as atualiza��es
	 */
	execute_op_list ();

	/*
	 *	Realiza as compara��es
	 */
	execute_cmp_list ();

	/*
	 *	Termina graciosamente
	 */
    rel:
	error
	(	"Logout para \"%s\"",
		local_user_nm
	);

	if (t_sndrel (tcp_fd) < 0)
		error ("$*N�o consegui terminar conex�o");

	if (t_rcvrel (tcp_fd) < 0)
		error ("$*N�o consegui terminar conex�o");

	t_close (tcp_fd);

	return (0);

}	/* end tcmpto_s */
