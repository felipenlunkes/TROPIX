/*
 ****************************************************************
 *								*
 *			<sys/xti.h>				*
 *								*
 *	Definic�es para a utiliza��o da interface XTI		*
 *								*
 *	Vers�o	2.3.12, de 05.08.91				*
 *		4.9.00, de 22.08.06				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	XTI_H		/* Para incluir os prot�tipos */

/*
 ****************************************************************
 *	Algumas defini��es gerais				*
 ****************************************************************
 */
#define	NULL		0
#define	T_NULL		0
#define	T_YES		1
#define	T_NO		0
#define	T_UNUSED	-1
#define	T_ABSREQ	0x8000

/*
 ******	Macros de defini��es de algumas fun��es/vari�veis *******
 */
#define	t_close		close
#define	t_error		perror
#define	t_errno		errno

#define	TSYSERR		(-3)	/* Nunca ocorre */

/*
 ******	Estado da conex�o ***************************************
 */
typedef enum
{
	T_UNINIT,	/* N�o inicializado */
	T_UNBND,	/* "unbound" */
	T_IDLE,		/* Inerte */
	T_OUTCON,	/* Enviando pedido de conex�o */
	T_INCON,	/* Recebendo pedido de conex�o */
	T_DATAXFER,	/* Transferindo dados */
	T_OUTREL,	/* Enviando pedido de desconex�o */
	T_INREL		/* Recebendo pedido de desconex�o */

}	T_STATE;

/*
 ******	Eventos *************************************************
 */
#define	T_LISTEN	0x0001	/* Recep��o de um pedido de conex�o */
#define T_CONNECT	0x0002	/* Recep��o da confirma��o de conex�o */
#define	T_DATA		0x0004	/* Recep��o de mensagem */
#define	T_EXDATA	0x0008	/* Recep��o de mensagem expedita */
#define	T_DISCONNECT	0x0010	/* Recep��o de um pedido de desconex�o */
#define	T_UDERR		0x0040	/* Erro em datagrama */
#define	T_ORDREL	0x0080	/* Indica��o de desconex�o ordenada */
#define	T_GODATA	0x0100	/* � poss�vel enviar mensagem */
#define	T_GOEXDATA	0x0200	/* � poss�vel enviar mensagem expedita */
#define	T_TIMEOUT	0x0400	/* O tempo foi excedido */

/*
 ******	Defini��es de flags *************************************
 */
#define	T_MORE		0x0001	/* A mensagem continua */
#define	T_EXPEDITED	0x0002	/* Mensagem expedita */
#define	T_NEGOTIATE	0x0004	/* Especificar op��es */
#define	T_CHECK		0x0008	/* Verificar op��es */
#define	T_DEFAULT	0x0010	/* Utilizar os defaults nas op��es */
#define	T_SUCCESS	0x0020	/* Sucesso */
#define	T_FAILURE	0x0040	/* Erro */
#define	T_PUSH		0x0100	/* PUSH do TCP */
#define	T_URGENT	0x0200	/* Segmento urgente do TCP */
#define	T_NO_CHECKSUM	0x0400	/* Datagrama UDP recebido sem "checksum" */

/*
 ******	Informa��o utilizada pelos protocolos *******************
 */
typedef struct	t_info
{
	long	addr;		/* Tamanho do endere�o utilizado */
	long 	options;	/* Tamanho das op��es utilizadas */
	long	tsdu;		/* Tamanho m�ximo da mensagem */
	long	etsdu;		/* Tamanho m�ximo da mensagem urgente */
	long	connect;	/* Max.de dados para primitivas de conex�o */
	long	discon;		/* Max.de dados para primitivas de desconex�o */
	long	servtype;	/* Modo de comunica��o */

}	T_INFO;

/*
 ******	Modos de comunica��o definidos **************************
 */
#define	T_COTS		1	/* connection mode */
#define	T_COTS_ORD	2	/* connection mode com desconex�o ordenada */
#define	T_CLTS		3	/* connectionless mode */

/*
 ******	Estrutura do endere�o ***********************************
 */
typedef struct	inaddr		/* Estrutura contendo um endere�o */
{
    long	   a_addr;	/* Endere�o na rede */
    unsigned short a_family;	/* Fam�lia de protocolos */
    unsigned short a_port;	/* "port" */

}	INADDR;

#define	a_proto	a_port		/* Para uso do protocolo RAW */

/*
 ******	Estrutura utilizada por diversas fun��es ****************
 */
typedef struct	netbuf
{
	int	maxlen;		/* Tamanho de buf */
	int	len;		/* N�mero de bytes em buf */
	void	*buf;		/* Dados */

}	NETBUF;

/*
 ******	Estrutura utilizada pela fun��o "bind" ******************
 */
typedef struct	t_bind
{
	NETBUF	addr;		/* Endere�o ("port") */
	int	qlen;		/* Tamanho da fila */

}	T_BIND;

/*
 ******	Estrutura para a ger�ncia de op��es *********************
 */
typedef struct	t_optmgmt
{
	NETBUF	opt;		/* Op��es */
	long	flags;		/* Flags */

}	T_OPTMGMT;

typedef struct	secoptions
{
	short	security;	/* Security field */
	short	compartment;	/* Compartment */
	short	handling;	/* Handling retrictions */
	long	tcc;		/* Transmission control code */

}	SECOPTIONS;

typedef struct	tcp_options
{
	short	precedence;	/* Precedence */
	long	timeout;	/* Abort timeout for TCP in miliseconds */
	long	max_seg_size;	/* Maximum segment size */
	long	max_wait;	/* Tempo m�ximo de sil�ncio desconectado */
	long	max_silence;	/* Tempo m�ximo de sil�ncio conectado */
	long	window_size;	/* Tamanho da janela de entrada */
	long	max_client_conn;/* N�mero m�ximo de conex�es por cliente */
	long	reser[1];	/* Reservado para uso futuro */
	SECOPTIONS secopt;	/* Security options for TCP */

}	TCP_OPTIONS;

/*
 ******	Estrutura de desconex�o *********************************
 */
typedef struct	t_discon
{
	NETBUF	udata;		/* Mensagem */
	int	reason;		/* Motivo da desconex�o */
	int	sequence;	/* N�mero da sequ�ncia */

}	T_DISCON;

/*
 ******	Estrutura utilizada pela fun��o "connect" ***************
 */
typedef struct	t_call
{
	NETBUF	addr;		/* Endere�o */
	NETBUF	opt;		/* Op��es */
	NETBUF	udata;		/* Mensagem */
	int	sequence;	/* N�mero da seq��ncia */

}	T_CALL;

/*
 ******	Estrutura utilizada pela fun��o "sndudata" **************
 */
typedef struct	t_unitdata
{
	NETBUF	addr;		/* Endere�o */
	NETBUF	opt;		/* Op��es */
	NETBUF	udata;		/* Mensagem */

}	T_UNITDATA;

/*
 ******	Estrutura de erro de UNITDATA ***************************
 */
typedef struct	t_uderr
{
	NETBUF	addr;		/* Endere�o */
	NETBUF	opt;		/* Op��es */
	long	error;		/* C�digo do erro */

}	T_UDERROR;

/*
 ******	Tipos de estruturas para "t_alloc" **********************
 */
typedef enum
{
	T_BIND_STR = 1,	/* Estrutura "t_bind" */
	T_OPTMGMT_STR,	/* Estrutura "t_optmgmt" */
	T_CALL_STR,	/* Estrutura "t_call" */
	T_DIS_STR,	/* Estrutura "t_discon" */
	T_UNITDATA_STR,	/* Estrutura "t_unitdata" */
	T_UDERROR_STR,	/* Estrutura "t_uderr" */
	T_INFO_STR	/* Estrutura "t_info" */

}	T_ALLOC_ENUM;

/*
 ******	Campos da estrutura para "t_alloc" **********************
 */
#define	T_ADDR		0x01	/* Endere�o */
#define	T_OPT		0x02	/* Op��es */
#define	T_UDATA		0x04	/* Dados */
#define	T_ALL		0x07	/* Todos acima */

/*
 ****** Prot�tipos **********************************************
 */
extern int	close (int);
extern void	perror (const char *);
extern int	errno;

extern int	t_accept (int, int, const T_CALL *);
extern void	*t_alloc (int, T_ALLOC_ENUM, int);
extern int	t_bind (int, const T_BIND *, T_BIND *);
extern int	t_connect (int, const T_CALL *, T_CALL *);
extern int	t_push (int);
extern int	t_free (const void *, T_ALLOC_ENUM);
extern int	t_getinfo (int, T_INFO *);
extern int	t_getstate (int);
extern int	t_listen (int, T_CALL *);
extern int	t_look (int);
extern int	t_nread (int);
extern int	t_open (const char *, int, T_INFO *);
extern int	t_optmgmt (int, const T_OPTMGMT *, T_OPTMGMT *);
extern int	t_rcv (int, void *, int, int *);
extern int	t_rcvconnect (int, T_CALL *);
extern int	t_rcvdis (int, T_DISCON *);
extern int	t_rcvrel (int);
extern int	t_rcvudata (int, T_UNITDATA *, int *);
extern int	t_rcvuderr (int, T_UDERROR *);
extern int	t_snd (int, const void *, int, int);
extern int	t_snddis (int, const T_CALL *);
extern int	t_sndrel (int);
extern int	t_sndudata (int, const T_UNITDATA *);
extern char	*t_strevent (int, int);
extern int	t_sync (int);
extern int	t_unbind (int);

extern char	*t_addr_to_name (int, long);
extern char	*t_addr_to_node (int, long);
extern char	*t_addr_to_str (long);
extern char	*t_mail_to_node (int, const char *, int, int *);
extern long	t_node_to_addr (int, const char *, long *);
extern long	t_str_to_addr (const char *);
extern int	t_getaddr (int, INADDR *);
extern int	t_rcvraw (int, T_UNITDATA *, int *);
extern int	t_sndraw (int, const T_UNITDATA *);
