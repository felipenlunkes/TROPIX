/*
 ****************************************************************
 *								*
 *			<sys/disktb.h>				*
 *								*
 *	Estrutura de uma entrada da tabela de discos		*
 *								*
 *	Vers�o	3.0.0, de 26.07.94				*
 *		4.8.0, de 29.06.05				*
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

#define	DISKTB_H		/* Para definir os prot�tipos */

/*
 ******	Estrutura da entrada ************************************
 */
struct disktb
{
	char	p_name[16];	/* Nome da Parti��o do Disco */

	daddr_t	p_offset;	/* Come�o da parti��o  (blocos) */
	daddr_t	p_size;		/* Tamanho da parti��o (blocos) */

	char	p_type;		/* Tipo do sistema de arquivo */
	char	p_flags;	/* Indicadores: veja abaixo */
	char	p_lock;		/* Uso exclusivo do dispositivo */
	char	p_blshift;	/* LOG (2) do tamanho do bloco */

	dev_t	p_dev;		/* MAJOR + MINOR do dispositivo */

	int	p_unit;		/* No. do controlador */
	int	p_target;	/* No. do dispositivo */

	short	p_head;		/* No. de cabe�as   (BIOS) */
	short	p_sect;		/* No. de setores   (BIOS) */
	ushort	p_cyl;		/* No. de cilindros (BIOS) */
	short	p_nopen;	/* No. de opens */

	SB	*p_sb;		/* Ponteiro para o SuperBloco */

	INODE	*p_inode;	/* Para pseudo dispositivos */

	int	p_reser[2];	/* Para completar 64 bytes */
};

/*
 ****** C�digos das parti��es ***********************************
 */
enum
{
	PAR_DOS_FAT12	= 0x01,
	PAR_DOS_FAT16_S	= 0x04,		/* <  32 MB */
	PAR_DOS_FAT16	= 0x06,		/* >= 32 MB */
	PAR_DOS_FAT16_L	= 0x0E,		/* >= 32 MB, INT13_EXT */
	PAR_DOS_FAT32	= 0x0B,
	PAR_DOS_FAT32_L	= 0x0C,		/* INT13_EXT */
	PAR_DOS_EXT_G	= 0x05,
	PAR_NTFS	= 0x07,
	PAR_DOS_EXT_L	= 0x0F,
	PAR_LINUX_EXT2	= 0x83,
	PAR_TROPIX_V7	= 0xA8,
	PAR_TROPIX_T1	= 0xA9,
	PAR_TROPIX_SWAP	= 0xAF,
	PAR_TROPIX_EXT	= 0xAE
};

/*
 ******	Indicadores *********************************************
 */
#define	DISK_ACTIVE	0x0001	/* Parti��o ativa */
#define	DISK_INT13_EXT	0x0004	/* Aceita as extens�es da INT 13 */
