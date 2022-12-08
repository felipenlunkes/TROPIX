/*
 ****************************************************************
 *								*
 *			tcmpto_s.h				*
 *								*
 *	Compara��o remota de �rvores (servidor)			*
 *								*
 *	Vers�o	2.3.0, de 28.10.91				*
 *		4.2.0, de 02.05.02				*
 *								*
 *	M�dulo: TCMPTO_S/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	DEBUG			/* Gera ou n�o o c�digo de depura��o */

#define	NPAT	20		/* No. maximo de Padr�es */

/*
 ****** Macros �teis ********************************************
 */
#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define MIN(a,b) (a < b ? a : b)

/*
 ****** Os diversos (e muitos) indicadores **********************
 */
extern int		fromflag;	/* Caminhada na �rvore REMOTA */
extern int		cpflag;		/* Copie diretamente (sem compara��o) */

extern int		Cflag;		/* Usando compress�o */
extern int		gflag;		/* Gere o "garfield" */
extern int		Lflag;		/* local = N�o entre em diret�rios */
extern int		vflag;		/* verbose flag */
extern int		qflag;		/* Compara��o r�pida de objetos */
extern int		mflag;		/* Copia tamb�m o estado do arquivo */
extern int		dotflag;	/* N�o ignorar ".old" */

extern int		Bflag;		/* Debug */

/*
 ****** Estruturas **********************************************
 */
typedef struct litem	LITEM;

struct litem
{
	char		*l_name;	/* Nome do Link */
	int		l_nm_offset;	/* Deslocamento do nome para base */
	dev_t		l_dev;		/* Dispositivo */
	ino_t		l_ino;		/* No. do Inode */
	LITEM		*l_next;	/* o Proximo */
};

extern LITEM		*remote_linklist_first,	/* Come�o da Lista */
			*remote_linklist_last;	/* Final da Lista */

/*
 ****** Vari�veis globais ***************************************
 */
extern int		tcp_fd;			/* Descritor do TCP */

extern const char	*pgname;		/* Nome do programa */

extern int		snd_dis;		/* Disconecta em caso de erro (se != 0) */

extern const char 	garfield[];		/* Nome do arquivo "garfield" */

extern char		file_prefix_nm[];	/* Prefixo para os arquivos */

extern char		*file_prefix_ptr;	/* Ponteiro para o '\0' */

extern int		file_nm_offset;		/* Para obter o nome da BASE */

extern int		global_log_fd;		/* Para "error" */
extern FILE		*global_log_fp;

/*
 ******	Os padr�es **********************************************
 */
extern const char	*inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
extern int		inc_pati;

extern const char	*exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
extern int		exc_pati;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
extern void		t_snd_msg (int, const char *);
extern void		t_snd_msg_no_push (int, const char *);
extern int		t_rcv_msg (char **);
extern void		error (const char *, ...);
extern void		msg (const char *, ...);
extern void		on_signal (int, ...);
extern void		tcp_abort (int);
extern void		quit (int);

extern void		walk (void);
extern int		name_analysis (const char *, STAT *, int);
extern int		file_cmp (const char *, STAT *, int);

extern void		stat_endian_cv (STAT *, const STAT *);

extern char		*remote_link_proc (const char *, STAT *);
extern void		delete_remote_link_list (void);

extern void		copy_from (const char *);
extern void		copy_to (const char *);
extern int		verdir (const char *);

extern void		execute_op_list (void);
extern void 		execute_cmp_list (void);
extern void		delete_remote_file (const char *);
extern void		link_remote_file (const char *, const char *);
extern char		*file_nm_conversion (char *, const char *);

extern void		put_s_option (void);
extern int		put_p_option (const char *, const char *[], int *);
extern int		pattern_accept (const char *);

#ifdef	A_OUT_H
extern void		header_endian_cv (HEADER *hp);
#endif	A_OUT_H
