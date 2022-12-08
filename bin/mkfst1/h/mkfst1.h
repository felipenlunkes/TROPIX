/*
 ****************************************************************
 *								*
 *			mkfst1.h				*
 *								*
 *	Defini��es universais					*
 *								*
 *	Vers�o	4.3.0, de 04.07.02				*
 *		4.3.0, de 04.07.02				*
 *								*
 *	M�dulo: mkfst1						*
 *		Utilit�rios especiais				*
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
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

/*
 ******	Defini��es relativas ao sistema de arquivos *************
 */
#define	PMODE	0755

/*
 ******	Vari�veis externas **************************************
 */
extern const char	pgversion[];	/* Vers�o do programa */

extern int		exit_code;	/* C�digo de retorno */

extern int		rflag;		/* Cria o arquivo regular */
extern int		fflag;		/* Forca: n�o pede confirma��o */
extern int		vflag;		/* Verbose */

extern const char	*fs_nm;		/* Nome do Dispositivo */
extern char		fs_partnm[];	/* Nome da parti��o */

extern int		fs_fd;		/* Descritor para leitura e escritas do FS */

extern T1SB		sb;		/* Superbloco */
extern char		bitmap[BL4SZ];	/* �rea para o Mapa de bits */

#ifdef	DISKTB_H
extern  DISKTB		dev_disktb;	/* Entrada da tabela de parti��es */
#endif	DISKTB_H

#ifdef	STAT_H
extern STAT		dev_s;		/* O estado do dispositivo/arquivo */
#endif	STAT_H

extern time_t		now_time;	/* Tempo de Cria��o */

extern daddr_t		root_dir_bno;

extern daddr_t		inode_bno;	/* No. do bloco dos INODEs */

extern T1DINO		inode_block[T1_INOinBL4];

extern char		root_dir_image[BL4SZ];

extern char		lost_dir_image[BL4SZ];
extern daddr_t		lost_dir_bno;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
extern void		analyse_arguments (const char *[]);
extern char		*cv_blocks_to_KB_MB_or_GB (daddr_t);
extern void		make_empty_bitmaps (void);
extern void		fs_read (daddr_t, void *);
extern void		fs_write (daddr_t, const void *);
extern void		fs_clear (daddr_t);
extern void		get_dev (const char *);
extern const char	*get_boot1_nm (void);
extern void		make_root_and_lost_dir (void);
extern daddr_t		get_empty_block (int type);
extern T1DINO		*ialloc (void);
extern void		help (void);
extern void		write_boot_block (const char *);
