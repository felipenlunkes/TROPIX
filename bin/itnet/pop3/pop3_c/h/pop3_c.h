/*
 ****************************************************************
 *								*
 *			pop3_c.h				*
 *								*
 *	Post Office Protocol - Version 3 (cliente)		*
 *								*
 *	Vers�o	3.1.0, de 09.10.98				*
 *		3.2.3, de 12.04.00				*
 *								*
 *	M�dulo: POP3_C						*
 *		Utilit�rios de comunica��es			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */


/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	DATASZ	1024

#define	KBSZ	1024
#define	MBSZ	(KBSZ * KBSZ)

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	POP3_PORT	110

/*
 *****	Vari�veis globais ***************************************
 */
extern const char	*pgname;		/* Nome do programa */

extern const char	pgversion[];		/* Vers�o */

extern FILE		*tty_fp;		/* Arquivo para "askyesno" */

extern int		snd_dis;		/* Em caso de erro, desconecta */

extern int		tcp_fd;			/* Descritor do TCP */

extern FILE		*tcp_fp;		/* FILE do TCP */

extern int		aflag;			/* Todas as cartas */
extern int		vflag;			/* Verbose */

extern const char	tcp_dev_nm[];		/* Nome do dispositivo TCP */

extern INADDR		local_tcp_addr;		/* Endere�o local de controle */

extern char		local_node_nm[];	/* Nome do n� local */

extern const char	*remote_node_nm;	/* Nome do n� remoto */

extern const char	*local_user_nm,		/* Nome do usu�rio local e remoto */
			*remote_user_nm;	/* Nome do usu�rio */

extern int		user_uid;		/* UID do usu�rio */

extern int		user_gid;		/* GID do usu�rio */

extern int		received_intr;		/* Veio um <^C> */

extern	char		first_reply_line[];	/* Primeira linha da resposta */

extern int		LINE_SZ;		/* N�mero m�ximo de caracteres por linha */

extern char		mailbox_nm[];
extern char		*mailbox_ptr;

extern const char	status_nm[];

extern FILE		*status_fp;

extern FILE		*uidl_fp;		/* Arquivo dos UIDLs lidos */

extern const char	base_64_tb[];		/* Tabela de convers�o */

extern char		cp_askyesno_force;	/* Para as nossas vers�es de "askyesno" */
extern int		cp_askyesno_force_seen;

extern char		rm_askyesno_force;
extern int		rm_askyesno_force_seen;

/*
 ******	C�digo de retorno do POP3 *******************************
 */
enum { OK, ERR };

#define	OKSZ	4	/* Tamanho de "+OK " */

/*
 ******	Lista de mensagens **************************************
 */
typedef struct mbox	MBOX;

struct mbox
{
	char		*m_nm;		/* Nome do arquivo */
	int		m_ino;		/* No. do inode do arquivo */

	int		m_index;	/* No. da carta ou linha */

	char		m_status;	/* Estado: "U" ou "R" */
	char		m_quoted;	/* Caracteres na forma "=.." */

	char		*m_uidl;	/* Identica��o do POP3 */
	char		*m_from;	/* Remetente */
	char		*m_to;		/* Destinat�rio */
	char		*m_date;	/* Data */
	time_t		m_time;		/* Data j� convertida */
	char		*m_subject;	/* Asssunto */
	int		m_size;		/* Tamanho da carta */

	char		*m_text;	/* Texto da linha/cabe�alho */
	int		m_len;		/* Tamanho do texto */

	MBOX		*m_local;	/* Ponteiro para a carta igual, local */
	MBOX		*m_back;	/* Ponteiro para o antecessor */
	MBOX		*m_forw;	/* Ponteiro para o sucessor */
};

#define	NOMBOX	(MBOX *)NULL

extern MBOX		mbox_list_head;	/* Cabe�a da lista de mensagens */

/*
 ******	Prot�tipos **********************************************
 */
extern void		connect (void);
extern void		do_quit_and_exit (void);
extern void		quit (void);
extern void		on_intr (int, ...);
extern int		cp_askyesno (void);
extern int		rm_askyesno (void);
extern void		error (const char *, ...);
extern void		tcp_abort (int);
extern void		help (void);

extern void		do_login (void);
extern void		decode_stat (void);
extern void		decode_uidl (void);
extern void		decode_list (void);
extern void		update_local_mbox (void);
extern void		delete_msg_in_remote_mbox (void);
extern void		get_message (MBOX *);
extern void		get_top (MBOX *);
extern int		comando (int, const char *, ...);
extern int		get_reply (void);
extern char		*fnrgets (char *, int, FILE *);
extern int		read_and_store_uidl_or_list (void);

extern void		get_mbox (void);
extern char		*scan_address (const char *);
extern char		*scan_date (const MBOX *);
extern time_t		get_date (const char *);
extern char		*strtoupper (char *);
extern int		get_line_info (const char *, MBOX *);
extern int		get_msg_info (MBOX *);
extern char		*edit_size (int);

extern void	 	do_mime_2 (const char *, char *);
