/*
 ****************************************************************
 *								*
 *			ftp_c.c					*
 *								*
 *	File transfer protocol (cliente)			*
 *								*
 *	Vers�o	3.0.0, de 12.10.92				*
 *		4.0.0, de 11.08.01				*
 *								*
 *	M�dulo: FTP_C						*
 *		Utilit�rios de comunica��es			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <setjmp.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <xti.h>

#include "ftp_c.h"
#include "../ftp.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.0.0, de 11.08.01";

const char	tcp_dev_nm[] = "/dev/itntcp";

entry int	vflag;		/* Verbose */
entry int	nflag;		/* Sem login */
entry int	sflag = 1;	/* Envia o port a cada opera��o */

entry jmp_buf	prompt_point;	/* Para o jump remoto */

entry int	received_intr;	/* Veio um <^C> */

entry char	local_node_nm[80]; /* Nome do n� local */

entry const char *remote_node_nm; /* Nome do <n� remoto> */

entry const char *remote_user_nm; /* Nome do usu�rio remoto */

entry INADDR	local_cntl_addr; /* Endere�o local de controle */

entry int	cntl_fd;	/* Descritor da linha de controle */

entry FILE	*cntl_fp;	/* FILE da linha de controle */

entry int	snd_dis;	/* Em caso de erro, desconecta */

entry int	data_fd = -1;	/* FD da linha de dados	*/

/*
 ******	Caracter�sticas da transfer�ncia ************************
 */
entry int	type;		/* Tipo do c�digo */
entry int	stru;		/* Tipo da estrutura */
entry int	mode;		/* Modo de transfer�ncia */
entry int	form;		/* Forma  */

/*
 ****************************************************************
 *	File transfer protocol (cliente)			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	*field;
	char		*str;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vnH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'n':			/* Sem login */
			nflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	ftp [-vn] [<n� remoto>]
	 *
	 *	O <n� remoto> pode tamb�m ser dado no ambiente
	 */
	argv += optind;
	argc -= optind;

	if (argc > 1)
		help ();

	remote_node_nm = argv[0];

	/*
	 *	Abre o terminal para "askyesno"
	 */
	if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
		error ("$*N�o consegui abrir \"/dev/tty\"");

	askyesno_stderr = stdout;

	/*
	 *	Examina o ambiente procurando o n� destino e o usu�rio remoto
	 */
	if ((str = (char *)getenv ("FTP")) == NOSTR)
		str = "";

	if ((str = strdup (str)) == NOSTR)
		str = "";

	for (field = strfield (str, ','); field != NOSTR; field = strfield (NOSTR, ','))
	{
		if   (strncmp (field, "node=", 5) == 0)
		{
			if (remote_node_nm == NOSTR)
				remote_node_nm = field + 5;
		}
		elif (strncmp (field, "user=", 5) == 0)
		{
			if (remote_user_nm == NOSTR)
				remote_user_nm = field + 5;
		}
	}

	if (remote_node_nm == NOSTR)
		{ error ("N�o foi dado o <n� remoto>\n"); help (); }

	/*
	 *	Defini��es b�sicas para o FTP
	 */
	type = TYPE_A;
	form = FORM_N;
	mode = MODE_S;
	stru = STRU_F;

	/*
	 *	Conecta com o servidor
	 */
	do_connect ();

	/*
	 *	Realiza o "login"
	 */
	if (!nflag)
		do_login (0, (const char **)NULL, (CMDTB *)NULL);

	/*
	 *	Prepara o retorno para o caso <^C> (ainda n�o usado)
	 */
	setjmp (prompt_point);

	signal (SIGINT, on_intr);

	/*
	 *	Executa os comandos
	 */
	exec_cmd ();	/* N�o retorna */

	return (1);

}	/* end ftp */

/*
 ****************************************************************
 *	Rotina de conex�o com o servidor remoto			*
 ****************************************************************
 */
void
do_connect (void)
{
	INADDR		serv_addr, remote_addr, bind_addr;
	T_BIND		bind;
	T_CALL		snd_call, rcv_call;
	const char	*cp;

	/*
	 *	Abre o dispositivo TCP de contr�le
	 */
	if ((cntl_fd = t_open (tcp_dev_nm, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", tcp_dev_nm);

	/*
	 *	Obt�m o endere�o n� remoto
	 */
	if ((remote_addr.a_addr = t_node_to_addr (cntl_fd, remote_node_nm, &local_cntl_addr.a_addr)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", remote_node_nm);

	remote_addr.a_port = FTP_CNTL_PORT;

	/*
	 *	Obt�m o nome do n� local
	 */
	if ((cp = t_addr_to_node (cntl_fd, local_cntl_addr.a_addr)) == NOSTR)
		error ("$N�o consegui obter o nome do n� local");

	strcpy (local_node_nm, cp);

	/*
	 *	Prepara a utiliza��o da "stdio" com a comunica��o de controle
	 */
	if ((cntl_fp = fdopen (cntl_fd, "r")) == NOFILE)
		error ("$*N�o consegui obter o FILE da comunica��o de controle");

	/*
	 *	Associa um endere�o local
	 */
	bind_addr.a_addr = 0;

	bind.addr.len	 = 0;
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &bind_addr;

	bind.qlen	 = 0;

	if (t_bind (cntl_fd, &bind, &bind) < 0)
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

	if (t_connect (cntl_fd, &snd_call, &rcv_call) < 0)
	{
		if (errno == TLOOK && t_look (cntl_fd) == T_DISCONNECT)
		{
			error ("A conex�o foi recusada por \"%s\"", remote_node_nm);
			exit (1);
		}

		error ("$*N�o consegui estabelecer conex�o");
	}

	snd_dis++;	/* De agora adiante, erros desconectam */

	if (vflag)
		printf ("Conectado a \"%s\"\n", remote_node_nm);

	/*
	 *	Recebe a confirma��o do servidor
	 */
	if (get_reply () != COMPLETE)
		do_quit (0, (const char **)NULL, (CMDTB *)NULL);

}	/* end do_connect */

/*
 ****************************************************************
 *	Identificador de Comandos				*
 ****************************************************************
 */
void
exec_cmd (void)
{
	const CMDTB	*tp;
	char		*cp;
	char		line[BLSZ];
	int		argc;
	const char	*argv[10];

	/*
	 *	L� e processa os comandos
	 */
    prompt:
	for (EVER)
	{
		received_intr = 0;

		printf ("ftp> "); 	fflush (stdout);

		if (gets (line) == NOSTR)
		{
			if (errno == EINTR)
				continue;

			do_quit (0, (const char **)NULL, (CMDTB *)NULL);
		}

		for (cp = line; cp[0] == ' ' || cp[0] == '\t'; cp++)
			/* vazio */;

		if (cp[0] == '\0')
			continue;

		if (cp[0] == '!')
			{ exec_local_cmd (cp + 1); continue; }

		cp = strtok (cp, " \t");

		/*
		 *	Procura o comando na tabela
		 */
 		for (tp = cmdtab; /* teste abaixo */; tp++)
		{
			if (tp->c_name == NOSTR)
			{
				printf ("Comando \"%s\" desconhecido\n", cp);
				goto prompt;
			}

			if (streq (cp, tp->c_name))
				break;
		}

		if (tp->c_function == NOFUNC)
		{
			printf ("Comando \"%s\" ainda n�o implementado\n", cp);
			goto prompt;
		}

		/*
		 *	Retira os argumentos e realiza a fun��o
		 */
		for (argc = 0; (cp = strtok (NOSTR, " \t")) != NOSTR; argc++)
			argv[argc] = cp;

		(*tp->c_function) (argc, argv, tp);
		
	}	/* end for (EVER) */

}	/* end exec_cmd */

/*
 ****************************************************************
 *	Executa um comando local				*
 ****************************************************************
 */
void
exec_local_cmd (const char *line)
{
	const char	*cp, *dir;
	char		path[128];

	/*
	 *	Pula os brancos iniciais
	 */
	for (cp = line; cp[0] == ' ' || cp[0] == '\t'; cp++)
		/* vazio */;

	if (cp[0] == '\0')
		return;

	/*
	 *	Analisa especialmente o comando "cd"
	 */
	if (cp[0] == 'c' && cp[1] == 'd' && (cp[2] == ' ' || cp[2] == '\t' || cp[2] == '\0'))
	{
		for (cp += 2; /* abaixo */; cp++)
		{
			if (*cp == ' ' || *cp == '\t')
				continue;

			if (*cp == '\0')
				dir = getenv ("HOME");
			else
				dir = env_var_scan (path, cp);

			break;
		}

		if (dir == NOSTR)
			dir = ".";

		if (chdir (dir) < 0)
			error ("*Diret�rio inv�lido: \"%s\"", path);

		return;

	}	/* end if (linha � "cd ...") */

	/*
	 *	Outros comandos
	 */
	system (line);

}	/* end exec_local_cmd */

/*
 ****************************************************************
 *	Substitui vari�veis "$..." do ambiente em um caminho	*
 ****************************************************************
 */
const char *
env_var_scan (char *output_path, const char *input_path)
{
	const char	*path, *env;
	int		slash_missing = 0;

	output_path[0] = '\0';

	for
	(	path = strfield ((char *)input_path, '/');
		path != NOSTR;
		path = strfield (NOSTR, '/')
	)
	{
		if (slash_missing)
			strcat (output_path, "/");
		else
			slash_missing++;

		if (path[0] == '$' && (env = getenv (path + 1)) != NOSTR)
			strcat (output_path, env);
		else
			strcat (output_path, path);
	}

	return (output_path);

}	/* end env_var_scan */

/*
 ****************************************************************
 *	Tratamento de interrup��es ("sa�da elegante")		*
 ****************************************************************
 */
void
on_intr (int signo, ...)
{
	signal (SIGINT, on_intr);

	printf ("A interrup��o de comandos ainda n�o est� implementada\n");

	received_intr++;

#ifdef	PROCESS_INTERRUPT
	if (data_fd >= 0)
	{
		t_snddis (data_fd, (T_CALL *)NULL);
		t_close (data_fd);
		data_fd = -1;
	}

	if (data_fp != NOFILE)
	{
		fclose (data_fp);
		data_fp = NOFILE;
	}

	if (file_fp != NOFILE)
	{
		fclose (file_fp);
		file_fp = NOFILE;
	}

	if (file_fd >= 0)
	{
		close (file_fd);
		file_fd = -1;
	}

	if (dir_fp != NOFILE)
	{
		fclose (dir_fp);
		dir_fp = NOFILE;
	}

	if (tmp_fp != NOFILE)
	{
		fclose (tmp_fp);
		tmp_fp = NOFILE;
	}

	if (tmp_nm != NOSTR)
	{
		unlink (tmp_nm);
		tmp_nm = NOSTR;
	}

	longjmp (prompt_point, 1);
#endif	PROCESS_INTERRUPT

}	/* end on_intr */

/*
 ****************************************************************
 *	Imprime uma mensagem de erro (cliente)			*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	va_list		args;
	const char	*fmt = format;
	char		err, abrt;
	int		event, save_errno = errno;

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
			event = t_look (cntl_fd);
	
			fprintf (stderr, " (%s)", t_strevent (cntl_fd, event));
	
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
	{
		t_snddis (cntl_fd, (T_CALL *)NULL);

		if (data_fd >= 0)
			t_snddis (data_fd, (T_CALL *)NULL);
	}

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
		"%s - programa de c�pia remota de arquivos da INTERNET\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-vn] <n�_remoto>\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: Verboso\n"
		"\t-n: N�o executa automaticamente a seq��ncia de \"login\"\n"
	);

	exit (2);

}	/* end help */
