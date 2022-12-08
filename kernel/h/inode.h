/*
 ****************************************************************
 *								*
 *			<sys/inode.h>				*
 *								*
 *	Formato do INODE na Mem�ria				*
 *								*
 *	Vers�o	3.0.0, de 06.09.94				*
 *		4.8.0, de 15.01.06				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	INODE_H			/* Para incluir os prot�tipos */

/*
 ******	Formato da Estrutura ************************************
 */
#define	NADDR	19		/* N�mero m�ximo de endere�os */

struct	inode
{
	const struct fstab *i_fsp;	/* Ponteiro para a entrada do sistema de arquivos */

	INODE		*i_lru_forw;	/* Lista LRU */
	INODE		*i_lru_back;

	char		i_union;	/* Conte�do da uni�o, abaixo */
	LOCK		i_lock;		/* Semaforo de exclusividade de uso */
	ushort		i_flags;	/* Indicadores: veja abaixo */

	int		i_count;	/* No. de Referencias  */

	INODE		*i_next;	/* Fila Hash de Inodes */
	SB		*i_sb;		/* Ponteiro para o SB deste dev */

	dev_t		i_dev;		/* Dispositivo de Residencia do Inode */
	ino_t		i_ino;		/* No. do Inode */

	dev_t		i_par_dev;	/* Dispositivo de Residencia do pai do Inode */
	ino_t		i_par_ino;	/* No. do Inode do pai */

	char		*i_nm;		/* Nome da entrada (nem sempre dispon�vel) */

	daddr_t		i_lastr;	/* Ultimo bloco logico lido */

	LOCKF		*i_lockf;	/* Ponteiro para a lista de LOCKFs */

  struct
  {
	/*
	 *	Parte que � copiada de/para o INODE do disco
	 */
	long		i_c_mode;	/* Modo e tipo  do arquivo */
	ushort		i_c_uid;	/* Dono  do Arquivo */
	ushort		i_c_gid;	/* Grupo do Arquivo */
	int		i_c_nlink;	/* No. de Ponteiros para este arquivo */
	off_t		i_c_size;	/* Tamanho do Arquivo */

	time_t		i_c_atime;   	/* Tempo do ultimo acesso */
	time_t		i_c_mtime;   	/* Tempo da ultima modifica��o */
	time_t		i_c_ctime;   	/* Tempo da cria��o */

	dev_t		i_c_rdev;	/* Dispositivo     (BLK e CHR) */
	daddr_t		i_c_addr[NADDR];/* End. dos Blocos (REG, DIR) */

  }	c;

  union
  {
    struct
    {
	/*
	 *	Parte usada quando o INODE � um TEXTO
	 */
	LOCK		i_u_xlock;	/* Semaforo do texto */
	short		i_u_xcount;	/* No. de ref. do texto na memoria & SWAP */

	pg_t		i_u_xdaddr;	/* End. do texto no swap (rel. a swaplow) */
	void		*i_u_xheader;	/* Ponteiro para o cabe�alho */
	pg_t		i_u_xsize;	/* Tamanho do texto em paginas */

	REGIONG		*i_u_xregiong;	/* Ponteiro para a regi�o de texto */

    }	x;

    struct
    {
	/*
	 *	Parte usada quando o INODE � um PIPE
	 */
	char		i_u_attention_set;
	EVENT		i_u_fifopar;
	EVENT		i_u_notempty;
	EVENT		i_u_notfull;

	UPROC		*i_u_uproc;
	pg_t		i_u_pipeaddr;
	int		i_u_fd_index;

    }	p;

	/*
	 *	Parte usada quando o INODE � de EVENTos de usu�rio
	 */
	UEVENTG		*i_u_ueventg;	/* Ponteiro para a lista de UEVENTGs */

	/*
	 *	Parte usada quando o INODE � de SEMAforos de usu�rio
	 */
	USEMAG		*i_u_usemag;	/* Ponteiro para a lista de USEMAGs */

	/*
	 *	Parte usada quando o INODE � de uma regi�o compartilhada
	 */
	REGIONG		*i_u_shmemg;	/* A regi�o da mem�ria compartilhada */

  }	u;

};

/*
 ******	Estrutura da Tabela Hash dos Inodes *********************
 */
struct	ihashtb	
{
	LOCK	h_lock;		/* Sleeplock de cada entrada */
	char	h_reser[3];
	INODE	*h_inode;	/* Comeco da Fila de Inodes */
};

/*
 ******	Macro para o c�lculo do HASH ****************************
 */
#define	IHASH(dev,ino)	(scb.y_ihash + ((unsigned int)(dev ^ ino)) % scb.y_nihash)

/*
 ******	Indicador do campo da uni�o *****************************
 */
enum { IN_NULL, IN_TEXT, IN_PIPE, IN_EVENT, IN_SEMA, IN_SHMEM };

/*
 ******	Defini��es da parte COMUM *******************************
 */
#define	i_mode		c.i_c_mode
#define	i_uid		c.i_c_uid
#define	i_gid		c.i_c_gid
#define	i_nlink		c.i_c_nlink
#define	i_size		c.i_c_size

#define	i_atime		c.i_c_atime
#define	i_mtime		c.i_c_mtime
#define	i_ctime		c.i_c_ctime

#define	i_rdev		c.i_c_rdev
#define	i_addr		c.i_c_addr

/*
 ******	Defini��es do TEXT **************************************
 */
#define	i_xlock		u.x.i_u_xlock
#define	i_xcount	u.x.i_u_xcount

#define	i_xdaddr	u.x.i_u_xdaddr
#define	i_xheader	u.x.i_u_xheader
#define	i_xsize		u.x.i_u_xsize

#define	i_xregiong	u.x.i_u_xregiong

/*
 ******	Defini��es do PIPE **************************************
 */
#define	i_attention_set	u.p.i_u_attention_set
#define	i_notempty	u.p.i_u_notempty
#define	i_notfull	u.p.i_u_notfull
#define	i_pipeaddr	u.p.i_u_pipeaddr
#define	i_fifopar	u.p.i_u_fifopar
#define	i_uproc		u.p.i_u_uproc
#define	i_fd_index	u.p.i_u_fd_index

/*
 ******	Defini��es do EVENT *************************************
 */
#define	i_ueventg	u.i_u_ueventg

/*
 ******	Defini��es do SEMA **************************************
 */
#define	i_usemag	u.i_u_usemag

/*
 ******	Defini��es do SHMEM *************************************
 */
#define	i_shmemg	u.i_u_shmemg

/*
 ****** Indicadores *********************************************
 */
#define	IMOUNT		0x0001	/* H� um FS montado neste INODE */
#define	ICHG		0x0010	/* O inode foi alterado */
#define	ITEXT		0x0020	/* O inode representa um TEXT */
#define	IXSWAP		0x0040	/* O texto j� est� no SWAP */
#define	ILOCK		0x0200	/* Uso Exclusivo do Arquivo */
#define	IXCORE		0x0400	/* O texto j� est� na Mem�ria */
#define	IDIRTY		0x0800	/* O arquivo tem blocos n�o atualizados */

/*
 ******	Modos e tipos *******************************************
 */
#define	IMETX	 0x010000	/* Salva a imagem do texto na mem�ria */
#define	IFMT	 0x00F000	/* Tipo do Arquivo */
#define     IFLNK   0x00A000	/* "Link" simb�lico */
#define     IFREG   0x008000	/* Regular */
#define	    IFDIR   0x004000	/* Diretorio */
#define     IFIFO   0x001000	/* FIFO */
#define     IFBLK   0x006000	/* Bloco */
#define	    IFCHR   0x002000	/* Caracter */
#define	ISUID	 0x000800	/* "Set user  id" na execu��o */
#define	ISGID	 0x000400	/* "Set group id" na execu��o */
#define ISVTX	 0x000200	/* Salva a imagem do texto no SWAP */
#define	IREAD	 0x000100	/* Permiss�o de leitura do dono */
#define	IWRITE	 0x000080	/* Permiss�o de escrita do dono */
#define	IEXEC	 0x000040	/* Permiss�o de execu��o do dono */

#define	IPSHIFT	3		/* Shift para acesso �s outras permiss�es */

/*
 ****** Indicadores para a rotina "iname" ***********************
 */
enum
{
	ISEARCH	= 0x00010000,	/* Procurar o Arquivo */
	LSEARCH = 0x00020000,	/* Procurar o "link" simb�lico */
	ICREATE = 0x00040000,	/* Criar    o Arquivo */
	IDELETE = 0x00080000,	/* Apagar   o Arquivo */

	IGIVEN	= 0x00100000,	/* O INODE j� est� em "io_ip" */
	INUMBER	= 0x00200000,	/* Dado o INO (para "search_dir") */
	INOMNT	= 0x00400000,	/* N�o atravessa montagens (para "iget") */
	INOREAD	= 0x00800000	/* N�o l� o INODE (para "iget") */
};

#define	INAME_LEVEL_MASK	0xFFFF	/* Para retirar o n�vel */

/*
 ******	Defini��o �til ******************************************
 */
#define	IS_DOT_or_DOTDOT(name)			\
						\
	(name[0] == '.' && (name[1] == '\0' ||	\
	(name[1] == '.' &&  name[2] == '\0')))

/*
 ****** Estrutura para uma opera��o de E/S **********************
 */
struct ioreq
{
	int		io_fd;		/* Descritor do arquivo */
	KFILE		*io_fp;		/* Ponteiro para KFILE */
	INODE		*io_ip;		/* Ponteiro para INODE */
	dev_t		io_dev;		/* Dispositivo */
	void		*io_area;	/* Endere�o da �rea */
	int		io_count;	/* N�mero de bytes */

  union
  {
	loff_t		io_loff;	/* Posi��o de Leitura/escrita */
	off_t		io_off[2];

  }	off_u;

	int		io_cpflag;	/* Dire��o da c�pia */
	daddr_t		io_rablock;	/* Bloco a ler antecipadamente */
	int		io_eof;		/* Foi encontrado um EOF */
};

#define io_offset	off_u.io_loff
#define io_offset_low	off_u.io_off[0]
#define io_offset_high	off_u.io_off[1]

/*
 ******	Tabela de sistema de arquivos ***************************
 */
typedef	struct dirent	DIRENT;

struct	fstab
{
	int		fs_code;

	int		(*fs_authen)		(dev_t);
	int		(*fs_mount)		(SB *);
	void		(*fs_ustat)		(const SB *, USTAT *);
	void		(*fs_update)		(const SB *);

	int		(*fs_read_inode)	(INODE *);
	void		(*fs_write_inode)	(INODE *);
	INODE		*(*fs_make_inode)	(IOREQ *, DIRENT *, int);
	void		(*fs_rel_inode_attr)	(INODE *);
	void		(*fs_trunc_inode)	(INODE *);
	void		(*fs_free_inode)	(const INODE *);

	int		(*fs_search_dir)	(IOREQ *, DIRENT *, int);
	void		(*fs_read_dir)		(IOREQ *);
	void		(*fs_write_dir)		(IOREQ *, const DIRENT *, const INODE *, int);
	int		(*fs_empty_dir)		(INODE *);
	INODE		*(*fs_make_dir)		(IOREQ *, DIRENT *, int);
	void		(*fs_clr_dir)		(IOREQ *, const DIRENT *, const INODE *);

	void		(*fs_open)		(INODE *, int);
	void		(*fs_close)		(INODE *);

	void		(*fs_read)		(IOREQ *);
	void		(*fs_write)		(IOREQ *);
	int		(*fs_read_symlink)	(IOREQ *);
	INODE		*(*fs_write_symlink)	(const char *, int, IOREQ *, DIRENT *);

	int		(*fs_ioctl)		(int, int, int, int);

	int		reser[8];		/* Para 32 entradas */
};
