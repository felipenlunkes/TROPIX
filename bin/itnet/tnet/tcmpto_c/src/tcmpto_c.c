/*
 ****************************************************************
 *								*
 *			tcmpto_c.c				*
 *								*
 *	Compara��o remota de �rvores (cliente) 			*
 *								*
 *	Vers�o	2.3.0, de 28.10.91				*
 *		4.5.0, de 03.06.03				*
 *								*
 *	M�dulo: TCMPTO_C/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
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
#include <string.h>
#include <stat.h>
#include <ftw.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <termio.h>
#include <errno.h>
#include <time.h>
#include <xti.h>

#include "../../tnet.h"
#include "../../reduce.h"
#include "../h/tcmpto_c.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.5.0, de 03.06.03";

#define	TCMPTO_PORT	117

const char	TCMPTO_VERSION[] = "TCMPTO,3.0.5";

/*
 ****** Os diversos (e muitos) indicadores **********************
 */
entry int		fromflag;	/* Caminhada na �rvore REMOTA */
entry int		cpflag;		/* Copie diretamente (sem compara��o) */
entry int		pipeflag;	/* Pipe */

entry int		tflag,		/* copy flags */
			fflag,
			dflag;

entry int		Cflag;		/* Usa compress�o */
entry int		gflag;		/* Gere o "garfield" */
entry int		Lflag;		/* local = N�o entre em diret�rios */
entry int		iflag = 1;	/* Iterativo */
entry int		vflag;		/* verbose flag */
entry int		qflag;		/* Compara��o r�pida de objetos */
entry int		mflag;		/* Copia tamb�m o estado do arquivo */
entry int		dotflag;	/* N�o ignorar ".old" */
entry int		Nflag;		/* Nomes do "stdin" */

entry int		nflag;		/* Foi dado o nome do n� */
entry int		uflag;		/* Foi dado o nome do usu�rio remoto */
entry int		Dflag;		/* Foi dado o diret�rio remoto */

entry int		Zflag;		/* Do not execute Commands */
entry int		Bflag;		/* Debug */

entry const char	**color_vector;	/* Para as cores dos modos */

/*
 ******	Os padr�es **********************************************
 */
entry const char	*inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
entry int		inc_pati;

entry const char	*exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
entry int		exc_pati;

/*
 ****** Vari�veis diversas **************************************
 */
const char		tcp_dev_nm[] = "/dev/itntcp";

entry int		tcp_fd;		/* C�pia do "fd" */

entry int		snd_dis = 0;	/* Disconecta em caso de erro (se != 0) */

entry char		local_node_nm[80]; /* Nome do n� local */

entry const char	*remote_node_nm; /* Nome do n� remoto */

entry const char	*local_user_nm;	/* Nome do usu�rio local */

entry int		local_user_euid; /* Identifica��o efetiva do usu�rio local */

entry const char	*remote_user_nm; /* Nome do usu�rio remoto */

entry const char	*remote_dir_nm;	/* Nome do diret�rio remoto */

entry const char	*local_cwd_nm;	/* Nome do diret�rio corrente local */

#ifdef	REPORTs
entry TERMIO	old_video, video;	/* modos do terminal */
#endif	REPORTs

const char		garfield[] = "garfield";

entry FILE		*tty_fp;		/* Arquivo para "askyesno" */

entry FILE		*gar_fp;		/* Arquivo "garfield" */

entry int		diff_files_cnt;		/* Contador de nr. de Arq. diferentes */

extern int		MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

#ifdef	DEBUG
void			print_op_list (void);
#endif	DEBUG

/*
 ****************************************************************
 *	Compara��o remota de �rvores (cliente) 			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, fd;
	const char	*field;
	const char	**p;
	char		*cp;
	char		*rmsg;
	char		buf[BLSZ];
	INADDR		serv_addr, snd_addr, my_addr;
	T_BIND		bind;
	T_CALL		snd_call, rcv_call;
	SEGFLAGS	segflags;
	char		id[16];
	const char	*str, *bit_sz_str = NOSTR;

	/*
	 *	Verifica logo se a caminhada � na �rvore local ou remota ou pipe
	 */
	str = "tfdCgLFvsqm.Nn:u:D:p:P:MHBZ";

	if   (patmatch (pgname, "*cmpfrom"))
		fromflag++;
	elif (patmatch (pgname, "*cpto"))
		cpflag++;
	elif (patmatch (pgname, "*cpfrom"))
		{ cpflag++; fromflag++; }
	elif (patmatch (pgname, "*pipe"))
		{ pipeflag++; str = "CNn:u:D:MHB"; }

	/*
	 *	tcmpto   [-tfdgLFvm.N] <ENV> <PAD> [<�rvore> ...]
	 *	tcmpfrom [-tfdgLFvm.N] <ENV> <PAD> [<�rvore> ...]
	 *	tcpto    [-LFvm.N] <ENV> <PAD> [<�rvore> ...]
	 *	tcpfrom  [-LFvm.N] <ENV> <PAD> [<�rvore> ...]
	 *	tpipe    [-N] <ENV> [<�rvore> ...]
	 *
	 *	Valores de <ENV>: [-C] [-n <n�>] [-u <usu�rio>] [-D <rdir>]
	 *
	 *	Valores de <PAD>: [-s] [-p <p>] [-P <P>]
	 */
	while ((opt = getopt (argc, argv, str)) != EOF)
	{
		switch (opt)
		{
		    case 't':		/* Copy-to flag */
			tflag++;
			if (fflag || dflag || gflag)
				help ();
			break;

		    case 'f':		/* Copy-from flag */
			fflag++;
			if (tflag || dflag || gflag)
				help ();
			break;

		    case 'd':		/* Data-flag */
			dflag++;
			if (tflag || fflag || gflag)
				help ();
			break;

		    case 'C':		/* Comprime */
			Cflag++;
			break;

		    case 'g':		/* Gera "garfield" */
			gflag++;
			if (fflag || dflag || tflag)
				help ();
			break;

		    case 'L':		/* Local */
			Lflag = 1;
			break;

		    case 'F':		/* Force */
			iflag = 0;
			break;

		    case 'v':		/* Verbose flag */
			vflag++;
			break;

		    case 's':			/* Padr�es = 	*.[cshryv] e */
			put_s_option ();
			break;

		    case 'p':		/* Padr�es de inclus�o */
			put_p_option (optarg, inc_pat, &inc_pati);
			break;

		    case 'P':		/* Padr�es de exclus�o */
			put_p_option (optarg, exc_pat, &exc_pati);
			break;

		    case 'q':		/* Compara��o r�pida de objetos */
			qflag++;
			break;

		    case 'm':		/* Copia o estado do arquivo */
			mflag++;
			break;

		    case '.':		/* N�o ignora ".old" */
			dotflag++;
			break;

		    case 'N':		/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'n':		/* N� */
			nflag++;
			remote_node_nm = optarg;
			break;

		    case 'u':		/* Usu�rio remoto */
			uflag++;
			remote_user_nm = optarg;
			break;

		    case 'D':		/* Diret�rio remoto */
			Dflag++;
			remote_dir_nm = optarg;
			break;

		    case 'M':		/* Stick im memory */
			exit (0);

		    case 'H':		/* Help */
			help ();

		    case 'B':		/* Debug flag */
			Bflag++;
			vflag++;
			break;

		    case 'Z':		/* N�o executa os comandos */
			Zflag++;
			break;

		    default:		/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
	{
		fprintf
		(	stderr,
			"%s: Os argumentos sup�rfluos ser�o ignorados\n",
			pgname
		);

		*argv = NOSTR;
	}

#if (0)	/*******************************************************/
	/*
	 *	Lendo de arquivo deve ser aceito ".old"
	 */
	if (*argv == NOSTR)
		dotflag++;
#endif	/*******************************************************/

	/*
	 *	Abre o "garfield"
	 */
	if (!pipeflag && gflag && (gar_fp = fopen (garfield, "w")) == NOFILE)
		error ("$*N�o consegui abrir \"%s\"", garfield);

	/*
	 *	Abre o terminal para "askyesno"
	 */
	if (!pipeflag && (askyesno_stdin = tty_fp = fopen ("/dev/tty", "r")) == NOFILE)
		error ("$*N�o consegui abrir \"/dev/tty\"");

	askyesno_set (1);	/* Em princ�pio, for�a */

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stdout)), (void *)NULL, &color_vector);

	/*
	 *	Encontra o nome do usu�rio local
	 */
	if ((local_user_nm = getlogin ()) == NOSTR)
		local_user_nm = strdup (getenv ("USER"));

	if (local_user_nm == NOSTR)
		error ("$N�o consegui obter o nome do usu�rio local");

	/*
	 *	Ajusta os sinais
	 */
	if (signal (SIGINT,  SIG_IGN) != SIG_IGN)
		signal (SIGINT, on_signal);

	if (signal (SIGTERM,  SIG_IGN) != SIG_IGN)
		signal (SIGTERM, on_signal);

#ifdef	REPORTs
	/*
	 *	Poe o Terminal sem PAGE na entrada
	 */
	if (!pipeflag && ioctl (fileno (tty_fp), TCGETS, &old_video) >= 0)
	{
		video = old_video;
#if (0)	/*************************************/
		video.c_cc[VPAGE] = 0;
		ioctl (fileno (tty_fp), TCSETNR, &video);
#endif	/*************************************/
	}
#endif	REPORTs

	/*
	 *	O n� destino, usu�rio remoto e o diret�rio remoto
	 *	tamb�m podem ser dados no ambiente
	 */
	if ((cp = (char *)getenv ("TNET")) == NOSTR)
		cp = "";

	if ((cp = strdup (cp)) == NOSTR)
		cp = "";

	for (field = strfield (cp, ','); field != NOSTR; field = strfield (NOSTR, ','))
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
		elif (strncmp (field, "rdir=", 5) == 0)
		{
			if (remote_dir_nm == NOSTR)
				remote_dir_nm = field + 5;
		}
		elif (streq (field, "reduce") || streq (field, "compress"))
		{
			Cflag++;
		}
		elif (*field >= '0'  &&  *field <= '9')
		{
			if (bit_sz_str == NOSTR)
				bit_sz_str = field;
		}
	}

	/*
	 *	Analisa o n�mero de bits
	 */
	if (bit_sz_str != NOSTR)
	{
		if
		(	(MAX_BIT_SZ = strtol (bit_sz_str, &str, 0)) < 9 ||
			MAX_BIT_SZ > 16 ||
			*str != '\0'
		)
		{
			error ("$No. de bits inv�lido: \"%s\"", bit_sz_str);
		}
	}
	else
	{
		MAX_BIT_SZ = DEF_BIT_SZ;
	}

	if (remote_node_nm == NOSTR)
		error ("$Faltou dar o nome do n� destino");

	if (remote_user_nm == NOSTR)
		remote_user_nm = local_user_nm;

	if (remote_dir_nm != NOSTR && streq (remote_dir_nm, "-"))
		remote_dir_nm = NOSTR;

	/*
	 ******	Abre o dispositivo TCP **************************
	 */
	if ((tcp_fd = fd = t_open (tcp_dev_nm, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", tcp_dev_nm);

	if ((snd_addr.a_addr = t_node_to_addr (fd, remote_node_nm, &my_addr.a_addr)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", remote_node_nm);

	snd_addr.a_port = TCMPTO_PORT;

	if ((cp = t_addr_to_node (fd, my_addr.a_addr)) == NOSTR)
		error ("$N�o consegui obter o nome do n� local");

	strcpy (local_node_nm, cp);

	/*
	 *	Executa o "bind" para o ENDPOINT local
	 */
	my_addr.a_port = 0;
	my_addr.a_addr = 0;

	bind.addr.len	 = 0;
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &my_addr;

	bind.qlen = 0;

	if (t_bind (fd, &bind, &bind) < 0)
		error ("$*N�o consegui atribuir endere�o local");

	/*
	 *	Executa o "connect"
	 */
	snd_call.addr.len    = sizeof (INADDR);
	snd_call.addr.buf    = &snd_addr;

	rcv_call.addr.maxlen = sizeof (INADDR);
	rcv_call.addr.buf    = &serv_addr;

	if (t_connect (fd, &snd_call, &rcv_call) < 0)
	{
		if (errno == TLOOK && t_look (fd) == T_DISCONNECT)
			error ("$A conex�o foi recusada");
		else
			error ("$*N�o consegui estabelecer conex�o");
	}

	snd_dis++;	/* De agora adiante, com "^C" desconecta */

	/*
	 *	Recebe o nome do servidor e vers�o do protocolo
	 */
	t_rcv_msg (&rmsg);

	if (!streq (rmsg, TCMPTO_VERSION))
		error ("$Erro de vers�o de servidor: %s :: %s", rmsg, TCMPTO_VERSION);

	/*
	 *	Envia o segmento de flags
	 */
	segflags.seg_type      = ENDIAN_LONG (FFLAGS);
	segflags.seg_flags[0]  = ENDIAN_LONG (fromflag);
	segflags.seg_flags[1]  = ENDIAN_LONG (cpflag);
	segflags.seg_flags[2]  = ENDIAN_LONG (gflag);
	segflags.seg_flags[3]  = ENDIAN_LONG (Lflag);
	segflags.seg_flags[4]  = ENDIAN_LONG (vflag);
	segflags.seg_flags[5]  = ENDIAN_LONG (qflag);
	segflags.seg_flags[6]  = ENDIAN_LONG (mflag);
	segflags.seg_flags[7]  = ENDIAN_LONG (dotflag);
	segflags.seg_flags[8]  = ENDIAN_LONG (Bflag);
	segflags.seg_flags[9]  = ENDIAN_LONG (Cflag);
	segflags.seg_flags[10] = ENDIAN_LONG (MAX_BIT_SZ);

	if (t_snd (fd, &segflags, sizeof (segflags), 0) < 0)
		error (NOSTR);

	/*
	 *	Envia os nomes dos usu�rios local e remoto
	 */
	local_user_euid = ENDIAN_LONG (geteuid ());

	if (t_snd (fd, &local_user_euid, sizeof (local_user_euid), 0) < 0)
		error (NOSTR);

	strscpy (id, local_user_nm, sizeof (id));

	if (t_snd (fd, id, sizeof (id), 0) < 0)
		error (NOSTR);

	strscpy (id, remote_user_nm, sizeof (id));

	if (t_snd (fd, id, sizeof (id), T_PUSH) < 0)
		error (NOSTR);

	/*
	 *	Processa a senha
	 */
	if (t_rcv_msg (&rmsg) != 0)
	{
		sprintf (buf, "Senha para \"%s@%s\": ", remote_user_nm, remote_node_nm);

		t_snd_msg (0, getpass (buf));

		if (t_rcv_msg (&rmsg) < 0)
			{ fprintf (stderr, "%s\n", rmsg); goto rel; }
	}

	/*
	 *	Processa a (segunda) senha do superusu�rio
	 */
	if (t_rcv_msg (&rmsg) != 0)
	{
		sprintf (buf, "Repita a senha para \"%s@%s\": ", remote_user_nm, remote_node_nm);

		t_snd_msg (0, getpass (buf));

		if (t_rcv_msg (&rmsg) < 0)
			{ fprintf (stderr, "%s\n", rmsg); goto rel; }
	}

	/*
	 *	Agora, mant�m apenas os finais dos nomes
	 */
	if ((cp = strchr (local_node_nm, '.')) != NOSTR)
		cp[0] = '\0';

	if ((cp = strchr (remote_node_nm, '.')) != NOSTR)
		cp[0] = '\0';

	/*
	 *	Envia o nome do diret�rio remoto
	 */
	if   (remote_dir_nm == NOSTR)		/* N�o dado */
	{
		t_snd_msg (0, NOSTR);
	}
	elif (remote_dir_nm[0] == '/')		/* /beta */
	{
		t_snd_msg (0, remote_dir_nm);
	}
	else					/* beta */
	{
		if ((local_cwd_nm = getcwd (NOSTR, BLSZ)) == NOSTR)
			error ("$N�o consegui obter o diret�rio corrente");

		strcpy (buf, local_cwd_nm);

		if (!streq (remote_dir_nm, "."))
		{
			strcat (buf, "/");
			strcat (buf, remote_dir_nm);
		}

		t_snd_msg (0, buf);
	}

	/*
	 *	Envia os padr�es
	 */
	if (fromflag)
	{
		for (p = inc_pat; *p != NOSTR; p++)
			t_snd_msg_no_push (0, *p);

		t_snd_msg (-1, NOSTR);

		for (p = exc_pat; *p != NOSTR; p++)
			t_snd_msg_no_push (0, *p);

		t_snd_msg (-1, NOSTR);
	}

	/*
	 *	Ajusta o sinal SIGINT para esperar o final de cada arquivo
	 */
	if (signal (SIGINT,  SIG_IGN) != SIG_IGN)
		signal (SIGINT, on_sigint);

	/*
	 *	Verifica se � "pipe"
	 */
	if (pipeflag)
		{ execute_pipe (argv); goto rel; }

	/*
	 *	Processa as �rvores
	 */
	walk (argv);

	/*
	 *	Emita a mensagem de totais de diferen�as
	 */
	if   (cpflag)
	{
		/* Nenhuma mensagem */
	}
	elif (diff_files_cnt > 1)
	{
		fprintf
		(	stderr,
			"Foram encontrados %d arquivos diferentes em \"%s\"\n",
			diff_files_cnt, remote_node_nm
		); 
	}
	elif (diff_files_cnt == 1)
	{
		fprintf
		(	stderr,
			"Foi encontrado 1 arquivo diferente em \"%s\"\n",
			remote_node_nm
		); 
	}
	else
	{
		fprintf
		(	stderr,
			"N�o foi encontrado nenhum arquivo diferente em \"%s\"\n",
			remote_node_nm
		); 
	}

	/*
	 *	Imprime a lista de opera��es
	 */
	if (Bflag)
		print_op_list ();

#ifdef	REPORTs
	/*
	 *	Poe o Terminal em RAW
	 */
	video.c_lflag &= ~(ICANON|ECHO);
	video.c_cc[VPAGE] = 0;
	video.c_cc[VMIN] = 1;

	ioctl (fileno (tty_fp), TCSETNR, &video);
#endif	REPORTs

	/*
	 *	Copia os arquivos escolhidos
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
	if (t_sndrel (fd) < 0)
		error ("$*N�o consegui terminar a conex�o");

	if (t_rcvrel (fd) < 0)
		error ("$*N�o consegui terminar a conex�o");

	t_close (fd);

	quit (0);

	return (1);

}	/* end tcmpto */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf (stderr, "%s - ", pgname);

	if   (pipeflag)
	{
		fprintf
		(	stderr,
			"escreve arquivos remotos na sa�da padr�o\n"
			"\n%s\n"
			"\nSintaxe:\n"
			"\t%s [-N] <ENV> [<�rvore> ...]\n",
			pgversion, pgname
		);
	}
	elif (!cpflag)
	{
		fprintf
		(	stderr,
			"compara��o/atualiza��o remota de �rvores "
			"(caminhando �rvores %s)\n"
			"\n%s\n"
			"\nSintaxe:\n"
			"\t%s [-tfdgLFvm.N] <ENV> <PAD> [<�rvore> ...]\n",
			fromflag ? "remotas" : "locais", pgversion, pgname
		);
	}
	else	/* cpflag */
	{
		fprintf
		(	stderr,
			"c�pia remota de �rvores (caminhando �rvores %s)\n"
			"\n%s\n"
			"\nSintaxe:\n"
			"\t%s [-LFvm.N] <ENV> <PAD> [<�rvore> ...]\n",
			fromflag ? "remotas" : "locais", pgversion, pgname
		);
	}

	fprintf
	(	stderr,
		"\n\tValores de <ENV>: [-C] [-n <n�>] [-u <usu�rio>] [-D <rdir>]\n"
		"\n\tValores de <PAD>: [-s] [-p \"<p>\"] [-P \"<P>\"]\n"
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-t: Atualiza as <�rvore>s do <n�> remoto\n"
		"\t-f: Atualiza as <�rvore>s locais\n"
		"\t-d: Atualiza as <�rvore>s locais ou do <n�> remoto,\n"
		"\t    dependendo das datas de modifica��o dos arquivos\n"
		"\t-g: Processa o arquivo \"garfield\"\n"
		"\t-L: Modo local: n�o entra em subdiret�rios\n"
		"\t-F: For�a: atualiza/copia sem esperar por uma confirma��o do usu�rio\n"
	);

	fprintf
	(	stderr,
		"\t-v: Verboso: imprime estat�sticas, ...\n"
		"\t-m: Atualiza/copia tamb�m o estado do arquivo\n"
		"\t-.: N�o ignora arquivos \"ocultos\" (da forma \".old\")\n"
		"\t-s: Adiciona os padr�es dos fontes em \"C\"\n"
		"\t-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o\n"
		"\t-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o\n"
	);

	fprintf
	(	stderr,
		"\t-C: Transmite os conte�dos dos arquivos em forma comprimida\n"
		"\t-n: Nome ou endere�o do <n�> remoto\n"
		"\t-u: Nome do usu�rio do <n�> remoto\n"
		"\t-D: Nome para compor o caminho completo das <�rvore>s\n"
		"\t-N: Le os nomes das <�rvore>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados argumentos\n"
		"\nObs.:\tAs op��es \"-t\", \"-f\" e \"-d\" s�o mutuamente exclusivas\n"
	);

	exit (2);

}	/* end help */
