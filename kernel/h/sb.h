/*
 ****************************************************************
 *								*
 *			<sys/sb.h>				*
 *								*
 *	Formato do superbloco					*
 *								*
 *	Vers�o	3.0.0, de 27.09.94				*
 *		4.8.0, de 29.09.05				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	SB_H			/* Para definir os prot�tipos */

/*
 ****************************************************************
 *	A estrutura do SUPER BLOCO universal			*
 ****************************************************************
 */
struct	sb
{
	char	sb_fname[16];	/* Nome do Sistema de Arquivos */
	char	sb_fpack[16];	/* Nome do Disco */

	char	sb_dev_nm[64];	/* O nome como foi dado na montagem */
	char	sb_dir_nm[64];	/* O diret�rio no qual est� montado */

	MNTENT	sb_mntent;	/* Indicadores de montagem */

	LOCK	sb_mlock;	/* SPINLOCK da estrutura */
	char	sb_sbmod;	/* O SB foi modificado */
	char	sb_mbusy;	/* Opera��o de Mount/Umount em Andamento */

	char	sb_res[13];

	ushort	sb_uid;		/* Dono  para "do_user" */
	ushort	sb_gid;		/* Grupo para "do_user" */

	LOCK	sb_lock;	/* SPINLOCK da estrutura espec�fica */
	LOCK	sb_lock_map;
	LOCK	sb_lock_ino;
	LOCK	sb_lock_blk;

	int	sb_mcount;	/* No. Referencias a Arq. neste Dev */

	INODE	*sb_inode;	/* Local de Montagem deste FS */
	dev_t	sb_dev;		/* Dispositivo referente a este SB */

	SB	*sb_back;	/* Lista de SB's */
	SB	*sb_forw;

	int	sb_code;	/* C�digo do Sistema de arquivos */
	int	sb_sub_code;	/* C�digo do Sistema de arquivos */
	void	*sb_ptr;	/* Ponteiro para o Superbloco espec�fico */

	int	sb_root_ino;	/* No. do INODE para o diret�rio raiz */
};

/*
 ******	Outras defini��es universais ****************************
 */
#define	sbput(sp)	spinfree (&(sp)->sb_mlock)
