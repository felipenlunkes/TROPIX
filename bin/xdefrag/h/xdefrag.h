/*
 ****************************************************************
 *								*
 *			xdefrag.h				*
 *								*
 *  Melhora a aloca��o dos blocos de um sistema de arquivos T1	*
 *								*
 *	Vers�o	4.3.0, de 09.10.02				*
 *		4.5.0, de 07.09.03				*
 *								*
 *	M�dulo: xdefrag						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Defini��es globais **************************************
 */
#define MAP_SZ(sz)	((((sz) >> 1) + BL4MASK) & ~BL4MASK)

/*
 ****** Vari�veis globais ***************************************
 */
extern int		dev_fd;			/* O descritor */

extern int		rflag;			/* Somente leituras */

extern int		fs_sz;			/* Tamanho do sistema de arquivos */
extern int		busy_bl;		/* No. de blocos ocupados */

extern int		fs_dir_count;		/* N�mero de diret�rios */

extern char		*old_bit_map,		/* Os mapas de bits */
			*new_bit_map;

extern int		before_map_ready,	/* Os mapas de aloca��o ANTES/DEPOIS est�o prontos */
			after_map_ready;

extern signed char	*before_block_map,	/* Os mapas para os blocos */
			*after_block_map;

extern signed char	*before_block_code;	/* Os c�digos ANTES */

enum { METHOD_FILE, METHOD_FILE_AND_HOLE, METHOD_FTW };

extern int		method_in_use;		/* Tipo da defragmenta��o */

#if (0)	/*******************************************************/
enum { SKIP_CTL_BLOCK, SKIP_NO_BLOCK };

extern int		skip_in_use;		/* Blocos a pular */
#endif	/*******************************************************/

extern int		compact_inodes,		/* N�mero de INODEs compactos ou N�O */
			fragmented_inodes;

extern int		percent_action_block,	/* No. de blocos/inodes a trocar */
			percent_action_inode,
			percent_action_dir,
			percent_action_done;

#define	MSGLINES	4

extern char		*msg_text[MSGLINES];

/*
 ****** Tabela dos dispositivos	*********************************
 */
typedef struct
{
	struct disktb	d_disktb;		/* A entrada da DISKTB */
	char		d_fname[16];		/* Nome do sistem de arquivos */
	int		d_state;		/* O sistema est� montado */

}	DEVTB;	

#define	NODEVTB		(DEVTB *)NULL

extern DEVTB		*devtb;			/* A tabela */

extern int		dev_defrag_index;

extern int		NDEV;			/* Uma quasi constante */

enum { FS_NOSTAT, FS_MOUNTED, FS_NOTREADY, FS_RONLY, FS_NOREAD, FS_NOTT1, FS_OK };

#define	FS_STATUS_NM		\
{				\
	"Sem estado      ",	\
	"Est� montado    ",	\
	"N�o pronto      ",	\
	"Apenas leituras ",	\
	"N�o consegui ler",	\
	"N�o � TROPIX T1 ",	\
	"                "	\
}

/*
 ****** Vetor de INODEs	*****************************************
 */
typedef struct
{
	daddr_t		a_old_bno;	/* Endere�o antigo */
	daddr_t		a_new_bno;	/* Endere�o novo */

}	DOUBLE;

typedef struct inovec	INOVEC;
typedef struct inomode	INOMODE;

struct inomode
{
	ulong		i_mode;		/* Modo e tipo do arquivo */
	ushort		i_uid;      	/* Dono  do Arquivo */
	ushort		i_gid;      	/* Grupo do Arquivo */
	int		i_nlink;	/* No. de Ponteiros para este arquivo */
	time_t		i_atime;   	/* Tempo do ultimo acesso */
	time_t		i_mtime;   	/* Tempo da ultima modifica��o */
	time_t		i_ctime;   	/* Tempo da cria��o */

	ino_t		i_new_ino;	/* O novo �ndice */
	INOVEC		*i_inovec;	/* Para a parte principal (abaixo) */
	INOMODE		*i_next;	/* Para a tabela HASH */

};

struct inovec
{
	ino_t		i_ino;
	off_t		i_size;
   /***	off_t		i_high_size;	***/
	int		i_virtual_blkcnt;
	int		i_phys_blkcnt;
	DOUBLE		*i_double;

	char		i_new_blocks;
	char		i_compact;
};

enum { INO_FRAGMENTED, INO_COMPACT };

#define	NODOUBLE	(DOUBLE *)NULL
#define	NOINOVEC	(INOVEC *)NULL
#define	NOINOMODE	(INOMODE *)NULL

extern INOVEC		*inovec;		/* O vetor de INODEs */
extern const INOVEC	*end_inovec;

extern INOMODE		*inomode;		/* O vetor complementar de INODEs */

extern DOUBLE		**block_map;		/* O vetor de BLOCOs */

extern INOMODE		**inode_hash_tb;
#if (0)	/*******************************************************/
extern INOMODE		**old_inode_hash_tb,
			**new_inode_hash_tb;
#endif	/*******************************************************/

/*
 ******	Defini��o de cache de UM elemento ***********************
 */
typedef struct
{
	daddr_t	b_bno;		/* N�mero do Bloco */
	int	b_dirty;	/* Buffer deve ser escrito */
	char	b_area[BL4SZ];	/* Conte�do do Bloco */

}	CACHE;

#define	NOCACHE	(CACHE *)NULL

extern CACHE		inode_cache,		/* Cache de 1 bloco de INODE */
			dir_cache;		/* Cache de 1 bloco de DIR */

extern int		cache_miss, cache_hit;	/* Acertos do CACHE */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void		get_devtb (void);
extern const char	*cv_blocks_to_MB (long bl_cnt);
extern int		xerror (const char *format, ...);
extern int		bread (void *area, daddr_t bno, int count);
extern int		bwrite (const void *area, daddr_t bno, int count);
extern void		draw_before_blocks (void);
extern void		draw_after_blocks (void);
extern void		clear_msg_window (void);
extern void		clear_before_window (void);
extern void		clear_after_window (void);
extern void		clear_percent_window (void);
extern void		do_XFlush (void);
extern int		compute_before_blocks (void);
extern int		alloc_after_blocks (int copy);
extern void		redraw_after_block (daddr_t bno);
extern void		draw_percent_percent (int, int);
extern void		*bget (CACHE *bp, daddr_t bno);
extern void		*bclear (CACHE *bp, daddr_t bno);
extern void		bflush (CACHE *bp);
extern void		draw_msg_win (void);
extern void		examine_device (DEVTB *dp);
extern void		draw_dev_line (const DEVTB *dp, int index);
extern int		method_ftw_compact (void);
extern void		write_all_moved_inodes (void);
extern int		update_inode_addr (ino_t ino, INOVEC *ip);
extern void		update_dir_entries (void);
extern void		update_sb (void);
extern void		draw_action_line (const char *format, ...);
extern void		put_blocks_in_bitmap (const INOVEC *ip);
extern int		compute_no_of_indir_blocks (daddr_t n_blocks);
extern int		method_file_compact (void);
extern void		update_all_inodes (void);
extern char		*editpercent (int quoc);
extern int		getpercent (long numer, long denom);
