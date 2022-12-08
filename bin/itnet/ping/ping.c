/*
 ****************************************************************
 *								*
 *			ping.c					*
 *								*
 *	Teste de acesso a um n� remoto				*
 *								*
 *	Vers�o	3.0.0, de 28.12.92				*
 *		3.0.3, de 24.03.98				*
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

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/times.h>
#include <sys/itnet.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <xti.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.2, de 23.08.97";

#define	EVER	;;
#define	elif	else if
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	MIL	1000
#define	MILHAO	(MIL * MIL)

/*
 ******	Defini��es relativas � ordem de bytes da CPU ************
 */
#ifdef	LITTLE_ENDIAN
#define	ENDIAN_LONG(x)	long_endian_cv (x)
#define	ENDIAN_SHORT(x)	short_endian_cv (x)
#else
#define	ENDIAN_LONG(x)	(x)
#define	ENDIAN_SHORT(x)	(x)
#endif	LITTLE_ENDIAN

/*
 ****** Op��es e par�metros *************************************
 */
entry int	sflag;		/* Estat�stica */
entry int	pflag;		/* Pontos */
entry int	vflag;		/* Verbose */

entry const char *remote_node_nm; /* Nome do n� remoto  */

entry char	canonical_node_nm[256]; /* Nome can�nico do n� remoto  */

entry long	remote_addr;	/* Endere�o do n� remoto  */

#define	N_DG_MAX 20		/* No. de datagramas a enviar (m�ximo) */

#define	N_DG	10		/* No. de datagramas a enviar (default) */

entry int	n_dg = N_DG;	/* No. de datagramas a enviar (efetivo) */

entry int	n_dg_snd;	/* No. de datagramas recebidos corretamente */

entry int	n_dg_rcv;	/* No. de datagramas recebidos corretamente */

entry int	pid;		/* No. do identifica��o do DG */

entry char	dg_map[N_DG_MAX + 3];	/* Mapa de datagramas recebidos */

entry ulong	total_time;	/* Acumulador dos tempos (us) */

/*
 ****** Vari�veis globais ***************************************
 */
const char	raw_dev[] = "/dev/itnraw";

int		raw_fd;		/* fd do RAW */

/*
 ****** Estrutura do datagrama enviado **************************
 */
typedef struct
{
	ICMP_H	h;	/* Cabe�alho ICMP */
	MUTM	t;	/* Tempo de envio */

}	DG;

/*
 ****** Tabela com os nomes das mensagem ICMP *******************
 */
const char	*msg_type[] =
{
	/*  0 */	"Echo reply",
	/*  1 */	NOSTR,
	/*  2 */	NOSTR,
	/*  3 */	"Destination unreachable",
	/*  4 */	"Source quence",
	/*  5 */	"Redirect",
	/*  6 */	NOSTR,
	/*  7 */	NOSTR,
	/*  8 */	"Echo",
	/*  9 */	NOSTR,
	/* 10 */	NOSTR,
	/* 11 */	"Time exceeded",
	/* 12 */	"Parameter problem",
	/* 13 */	"Timestamp",
	/* 14 */	"Timestamp reply",
	/* 15 */	"Information request",
	/* 16 */	"Information reply"
};

/*
 ****** Tabela com os nomes dos c�digos ICMP ********************
 */
const char	*msg_DST_UNREACH[] =
{
	/*  0 */	"Net unreachable",
	/*  1 */	"Host unreachable",
	/*  2 */	"Protocol unreachable",
	/*  3 */	"Port unreachable",
	/*  4 */	"Fragmentation needed and DF set",
	/*  5 */	"Source route failed"
};

const char	*msg_REDIRECT[] =
{
	/*  0 */	"Redirect datagrams for the network",
	/*  1 */	"Redirect datagrams for the host",
	/*  2 */	"Redirect datagrams for the type of service and network",
	/*  3 */	"Redirect datagrams for the type of service and host"
};

const char	*msg_TIME_EXCEEDED[] =
{
	/*  0 */	"Time to live exceeded in transit",
	/*  1 */	"Fragment reassembly time exceeded"
};

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		pai (void);
void		filho (void);
void		compute_and_print_time_interval (MUTM *, MUTM *);
void		print_statistics (void);
void		analyse_unexpected_datagrams (DG *, long);
void		alarm_catch (int, ...);
char		*editpercent (int);
int		getpercent (long, long);
void		error (const char *, ...);
void		help (void);

extern int	compute_checksum (const void *, int);

/*
 ****************************************************************
 *	Teste de acesso a um n� remoto				*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	INADDR		addr;
	T_BIND		bind;
	long		pidfilho;
	const char	*n_str = NOSTR, *str;

	/*
	 *	Pequena inicializa��o
	 */
	pid = getpid ();

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "spn:vH")) != EOF)
	{
		switch (opt)
		{
		    case 's':			/* Estat�stica */
			sflag++;
			break;

		    case 'p':			/* Pontos */
			pflag++;
			break;

		    case 'n':			/* No. de datagramas */
			n_str = optarg;
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

	remote_node_nm = argv[0];

	if (!pflag && !sflag)
		n_dg = 1;

	/*
	 *	Examina o n�mero de datagramas dado
	 */
	if (n_str != NOSTR && ((n_dg = strtol (n_str, &str, 0)) < 1 || *str != '\0'))
		error ("$No. de datagramas inv�lido: \"%s\"", n_str);

	if (n_dg > N_DG_MAX)
	{
		error ("No. m�ximo de datagramas: " XSTR (N_DG_MAX));
		n_dg = N_DG_MAX;
	}


	/*
	 *	Abre o "endpoint"
	 */
	if ((raw_fd = t_open (raw_dev, O_RDWR, (T_INFO *)NULL)) < 0)
		error ("$*N�o consegui abrir \"%s\"", raw_dev);

	/*
	 *	Obt�m o endere�o do n� remoto
	 */
	if ((remote_addr = t_node_to_addr (raw_fd, argv[0], (long *)NULL)) == -1)
		error ("$*N�o consegui obter o endere�o de \"%s\"", argv[0]);

#if (0)	/*******************************************************/
	if (vflag)
		error ("remote_addr dado: %08X (%s)", remote_addr, argv[0]);
#endif	/*******************************************************/

	if ((str = t_addr_to_node (raw_fd, remote_addr)) != NOSTR)
		strcpy (canonical_node_nm, str);
	else
		strcpy (canonical_node_nm, argv[0]);

	if (vflag)
	{
		printf ("Enviando %d datagrama(s) para \"%s\" (%s)\n", n_dg,
			canonical_node_nm, t_addr_to_str (remote_addr));
	}

	/*
	 *	Associa um endere�o
	 */
	addr.a_addr  = 0;	/* A consist�ncia do endere�o � feita abaixo */
	addr.a_proto = ICMP_PROTO;

	bind.addr.len	 = sizeof (INADDR);
	bind.addr.maxlen = sizeof (INADDR);
	bind.addr.buf	 = &addr;

	if (t_bind (raw_fd, &bind, &bind) < 0)
		error ("$*Erro no T_BIND");

	/*
	 *	Cria um filho para enviar os datagramas de ECHO
	 *	O pai le os datagrams de ECHO
	 */
	if ((pidfilho = thread ()) < 0)
		error ("$*N�o consegui dar o thread");

	if (pidfilho > 0)
		pai ();
	else
		filho ();

	return (0);

}	/* end ping */

/*
 ****************************************************************
 *	Filho: envia os pedidos de ECHO				*
 ****************************************************************
 */
void
filho (void)
{
	register int	i;
	T_UNITDATA	unitdata;
	DG		dg;
	INADDR		addr;
	int		seq = 0;

	/*
	 *	Repare no uso cuidado das vari�veis globais (thread)
	 *
	 *	Prepara o datagrama ICMP de pedido de echo
	 */
	dg.h.ih_type	 = ICMP_ECHO_REQ;
	dg.h.ih_code	 = 0;
   /***	dg.h.ih_checksum = 0; ***/
	dg.h.u.s.ih_id	 = ENDIAN_SHORT (pid);
   /***	dg.h.u.s.ih_seq  = 0; ***/

	/*
	 *	Manda o datagrama RAW
	 */
	addr.a_addr  = remote_addr;
	addr.a_proto = ICMP_PROTO;

	unitdata.addr.len	= sizeof (addr);
   	unitdata.addr.buf	= &addr;

	unitdata.udata.len	= sizeof (dg);
	unitdata.udata.buf	= &dg;

	for (i = n_dg; i > 0; i--)
	{
		mutime (&dg.t);

		dg.h.u.s.ih_seq  = ENDIAN_SHORT (seq++);
		dg.h.ih_checksum = 0;
		dg.h.ih_checksum = compute_checksum (&dg, sizeof (dg));

		if (t_sndraw (raw_fd, &unitdata) < 0)
		{
			error ("*Erro no SNDRAW");
			_exit (1);
		}

		n_dg_snd++;

		sleep (1);
	}

	_exit (0);

}	/* end filho */

/*
 ****************************************************************
 *	Pai: recebe os pedidos de ECHO				*
 ****************************************************************
 */
void
pai (void)
{
	register int	i;
	T_UNITDATA	unitdata;
	union { DG dg; char big_area[128]; } u;
	int		flag;
	INADDR		rcv_addr;
	MUTM		end_time;
	int		seq;

	/*
	 *	Prepara o alarme para o caso de n�o receber resposta
	 */
	signal (SIGALRM, alarm_catch);
	signal (SIGINT, alarm_catch);

	alarm (20);

	/*
	 *	Prepara a barra
	 */
	if (pflag)
	{
		for (i = n_dg; i > 0; i--)
			dg_map[i] = ' ';

		dg_map[0] = '|'; 	dg_map[n_dg + 1] = '|';

		printf ("\r%s", dg_map); fflush (stdout);
	}

	/*
	 *	Recebe os datagramas RAW
	 */
	unitdata.addr.maxlen	= sizeof (rcv_addr);
	unitdata.addr.buf	= &rcv_addr;

	unitdata.udata.maxlen	= sizeof (u);
	unitdata.udata.buf	= &u;

	for (i = n_dg; i > 0; i--)
	{
		if (t_rcvraw (raw_fd, &unitdata, &flag) < 0)
			error ("$*Erro no RCVRAW");

		mutime (&end_time);

		if   (u.dg.h.ih_type == ICMP_ECHO_REQ)	/* Ping para 0.0.0.0 */
		{
			i++;
			continue;
		}
		elif (u.dg.h.ih_type != ICMP_ECHO_REPLY)
		{
			analyse_unexpected_datagrams (&u.dg, rcv_addr.a_addr);
			i++;
			continue;
		}

		/*
		 *	Verifica se o ECHO REPLY � do n� esperado
		 */
		if (rcv_addr.a_addr != remote_addr)
			{ i++; continue; }

		/*
		 *	Calcula o checksum e outras consist�ncias
		 */
		if (unitdata.udata.len != sizeof (u.dg))
			error ("Datagrama com tamanho errado %d", unitdata.udata.len);

		if (compute_checksum (&u.dg, sizeof (u.dg)) != 0)
			error ("Erro no checksum");

		if (ENDIAN_SHORT (u.dg.h.u.s.ih_id) != pid)
		{
			error
			( 	"Erro no id: %d :: %d",
				ENDIAN_SHORT (u.dg.h.u.s.ih_id), pid
			);
		}

		n_dg_rcv++;

		seq = ENDIAN_SHORT (u.dg.h.u.s.ih_seq);

		if (pflag)
		{
			dg_map[seq + 1] = '*';

			printf ("\r%s", dg_map);

			fflush (stdout);
		}
		else
		{
			printf ("Datagrama %2d, ", seq);
		}

		compute_and_print_time_interval (&u.dg.t, &end_time);

	}

	if (pflag)
		printf ("\n");

	print_statistics ();

}	/* end pai */

/*
 ****************************************************************
 *	Imprime o tempo de transfer�ncia			*
 ****************************************************************
 */
void
compute_and_print_time_interval (register MUTM *begin_time, register MUTM *end_time)
{
	register time_t	TIME, UTIME;
	register ulong	us;

	/*
	 *	Faz a diferen�a de tempos - cuidado com o "carry"
	 */
	TIME = end_time->mu_time - begin_time->mu_time;

	if ((UTIME = end_time->mu_utime - begin_time->mu_utime) < 0)
	{
		TIME  -= 1;		/* Tira um segundo daqui */
		UTIME += MILHAO;	/* E compensa aqui */
	}

	us = TIME * MILHAO + UTIME; total_time += us;

	/*
	 *	Agora imprime
	 */
	if (!pflag)
		printf ("Tempo = %d.%03d ms\n", us / MIL, us % MIL);

}	/* end compute_and_print_time_interval */

/*
 ****************************************************************
 *	Imprime a estat�stica de recebimento			*
 ****************************************************************
 */
void
print_statistics (void)
{
	register ulong	us;

	if (n_dg <= 1)
		return;

	sleep (1);

	printf
	(	"Dos %d datagramas enviados, foram recebidos %d (%s %%)",
		n_dg_snd, n_dg_rcv,  editpercent (getpercent (n_dg_rcv, n_dg_snd))
	);

	/*
	 *	Imprime o tempo m�dio
	 */
	if (n_dg_rcv > 0)
	{
		us = (total_time + (n_dg_rcv >> 1)) / n_dg_rcv;

		printf
		(
			", Tempo m�dio = %d.%03d ms",
			us / MIL, us % MIL
		);
	}

	putchar ('\n');

}	/* end print_statistics */

/*
 ****************************************************************
 *	Foi recebido um datagrama de tipo inesperado		*
 ****************************************************************
 */
void
analyse_unexpected_datagrams (register DG *dp, long rcv_addr)
{
	register const char	*cp;

	/*
	 *	Imprime o tipo
	 */
	if (dp->h.ih_type < (sizeof (msg_type) / sizeof (char *)))
		cp = msg_type[dp->h.ih_type];
	else
		cp = NOSTR;

#define	ADDR_TO_NODE
#ifdef	ADDR_TO_NODE
	if (cp == NOSTR)
	{
		error
		( 	"Recebi um datagrama ICMP (de %s) de tipo desconhecido (%d)",
			t_addr_to_node (raw_fd, rcv_addr), dp->h.ih_type
		);
		return;
	}

	fprintf
	(	stderr,
		"%s: Recebi um datagrama ICMP (de %s): \"%s\"",
		pgname, t_addr_to_node (raw_fd, rcv_addr), cp
	);
#else
	if (cp == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: Recebi um datagrama ICMP (de %s) de tipo desconhecido (%d)\n",
			pgname, t_addr_to_str (rcv_addr), dp->h.ih_type
		);
		return;
	}

	fprintf
	(	stderr,
		"%s: Recebi um datagrama ICMP (de %s): \"%s\"",
		pgname, t_addr_to_str (rcv_addr), cp
	);
#endif	ADDR_TO_NODE

	/*
	 *	Imprime o c�digo
	 */
	cp = NOSTR;

	switch (dp->h.ih_type)
	{
	    case ICMP_DST_UNREACH:
		if (dp->h.ih_code < (sizeof (msg_DST_UNREACH) / sizeof (char *)))
			cp = msg_DST_UNREACH[dp->h.ih_code];
		else
			cp = "*";
		break;

	    case ICMP_REDIRECT:
		if (dp->h.ih_code < (sizeof (msg_REDIRECT) / sizeof (char *)))
			cp = msg_REDIRECT[dp->h.ih_code];
		else
			cp = "*";
		break;

	    case ICMP_TIME_EXCEEDED:
		if (dp->h.ih_code < (sizeof (msg_TIME_EXCEEDED) / sizeof (char *)))
			cp = msg_TIME_EXCEEDED[dp->h.ih_code];
		else
			cp = "*";
		break;

	}	/* end switch */

	if   (cp == NOSTR)
		fprintf (stderr, "\n");
	elif (*cp == '*')
		fprintf (stderr, " (c�digo %d desconhecido)\n", dp->h.ih_code);
	else
		fprintf (stderr, " (%s)\n", cp);

} 	/* end analyse_unexpected_datagrams */

/*
 ****************************************************************
 *	Intercepta o alarme					*
 ****************************************************************
 */
void
alarm_catch (int signo, ...)
{
	if (n_dg <= 1)
		printf ("N�o foi obtida resposta de \"%s\"\n", remote_node_nm);
	else
		{ printf ("\n"); print_statistics (); }

	exit (0);

}	/* end alarm_catch */

/*
 ****************************************************************
 *	Edita uma percentagem					*
 ****************************************************************
 */
char *
editpercent (register int quoc)
{
	static char	buf[8];
	char		*sinal;

	if (quoc < 0)
		{ sinal = "-"; quoc = -quoc; }
	else
		sinal = "";

	sprintf (buf, "%s%d.%02d", sinal, quoc / 100, quoc % 100);

	return (buf);

}	/* end editpercent */

/*
 ****************************************************************
 *	Calcula uma percentagem					*
 ****************************************************************
 */
int
getpercent (register long numer, register long denom)
{
	int		quoc;

	/*
	 *	Tenta evitar overflow
	 */
	if (numer > (0x7FFFFFFF / 10000))
		quoc = numer / (denom / 10000);
	else
		quoc = 10000 * numer / denom;

	return (quoc);

}	/* end percent */

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
			event = t_look (raw_fd);
	
			fprintf (stderr, " (%s)", t_strevent (raw_fd, event));
	
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
		"%s - teste de acesso a um n� remoto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-spv] [-n <n>] <n� remoto>\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Envia um datagrama e mede o tempo\n"
		"\t-s: Envia " XSTR (N_DG) " datagramas e emite uma estat�stica\n"
		"\t-p: Imprime um diagrama de barra\n"
		"\t-n: Envia <n> ao inv�s de " XSTR (N_DG) " datagramas "
			"(m�ximo de " XSTR (N_DG_MAX) " datagramas)\n"
		"\t-v: Verboso\n"
	);

	exit (2);

}	/* end help */
