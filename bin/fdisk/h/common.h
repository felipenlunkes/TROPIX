/*
 ****************************************************************
 *								*
 *			common.h				*
 *								*
 *	Altera a tabela de parti��o de discos	 		*
 *								*
 *	Vers�o	4.6.0, de 11.09.04				*
 *		4.6.0, de 11.09.04				*
 *								*
 *	M�dulo: fdisk						*
 *		Utilit�rios Sofisticados			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 *								*
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

extern int	exit_code;	/* C�digo de retorno */

extern int	vflag;		/* Verbose */

/*
 ******	Defini��es �teis para a tabela de parti��es *************
 */
#define	NPART	 4		/* N�mero total de parti��es reg. */
#define	NLOGPART ('z'-'a'+ 1)	/* N�mero m�ximo de parti��es l�gicas */

#define PARTB_OFF (512 - 2 - 4 * 16)	/* In�cio da tabela no setor */

#define MAGIC_OFF (512 - 2)	/* Endere�o do "0xAA55" */

/*
 ******	C�digos de algumas parti��es ****************************
 */
#define	DOS_EXT_G	0x05	/* C�digo da parti��o estendida DOS (Geo) */
#define	DOS_EXT_L	0x0F	/* C�digo da parti��o estendida DOS (Linear) */
#define	TROPIX_EXT	0xAE	/* C�digo da parti��o estendida TROPIX */

#define	TROPIX_V7	0xA8	/* C�digo da parti��o TROPIX V7 */
#define	TROPIX_T1	0xA9	/* C�digo da parti��o TROPIX T1 */

#define	DOS_FAT16_G	0x06	/* C�digo da parti��o FAT16 DOS (Geo) */
#define	DOS_FAT16_L	0x0E	/* C�digo da parti��o FAT16 DOS (Linear) */

#define	DOS_FAT32_G	0x0B	/* C�digo da parti��o FAT32 DOS (Geo) */
#define	DOS_FAT32_L	0x0C	/* C�digo da parti��o FAT32 DOS (Linear) */

#define	IS_EXT(t)	(t == DOS_EXT_G || t == DOS_EXT_L || t == TROPIX_EXT)
#define	IS_DOS_L(t)	(t == DOS_EXT_L || t == DOS_FAT16_L || t == DOS_FAT32_L)
#define	IS_DOS_G(t)	(t == DOS_EXT_G || t == DOS_FAT16_G || t == DOS_FAT32_G)

/*
 ******	Informa��o sobre os discos IDE **************************
 */
typedef struct
{
	int	h_head;		/* No. de cabe�as  (REAL) */
	int	h_sect;		/* No. de setores  (REAL) */
	int	h_cyl;		/* No. de cilindros (REAL) */

	int	h_flags;	/* Indicadores (ver abaixo) */

}	HDINFO;

#define NOHDINFO (HDINFO *)0	/* Ponteiro NULO */

#define HD_INT13_EXT	0x04 	/* O disco aceita as extens�es da INT 13 */

/*
 ****** Uma entrada da tabela de parti��es **********************
 */
typedef struct
{
	char	head;		/* Cabe�a */
	char	sect;		/* Setor */
	char	cyl;		/* Cilindro */

}	TRIO;

typedef struct			/* Tabela de parti��es */
{
	char	pt_active;	/* Entrada ativa se 0x80 */
	TRIO	pt_start;	/* Trio inicial */
	char	pt_type;	/* Tipo do sistema de arquivos */
	TRIO	pt_end;		/* Trio final */
	long	pt_offset;	/* Deslocamento (blocos) */
	long	pt_size;	/* Tamanho (blocos) */

}	PARTTB;

#define	NOTRIO	 (TRIO *)0	/* Ponteiro NULO */
#define NOPARTTB (PARTTB *)0	/* Ponteiro NULO */

#define	CYLMAX(c)	((c) > 1023 ? 1023 : (c))

typedef struct
{
	int	f_reg_index;	/* No. da parti��o regular */
	int	f_log_index;	/* No. da parti��o l�gica */
	PARTTB	*f_pp;		/* Ponteiro para a entrada */

}	PARTINFO;

enum	{ IDE_TYPE, SCSI_TYPE };	/* Tipo do disco */

extern char		fdisk_type;	/* Tipo: IDE ou SCSI */
extern const void	*fdisk_data;	/* Estrutura ATA ou SCSI */
extern const DISKTB	*fdisk_disktb;	/* Entrada do disco "hda" ou "hdb" */
extern const HDINFO	*fdisk_hdinfo;	/* Entrada de par�metros do disco */
extern daddr_t		fdisk_size;	/* Tamanho do disco */
extern daddr_t		fdisk_round;	/* Para arrendondar os endere�os */

extern int		fdisk_modified;	/* N�O zero se modificada */
extern int		fdisk_debug;	/* Debug ? */
extern int		fdisk_align;	/* Aligned ? */

/*
 ****** Defini��es e vari�veis da tabela de parti��es ***********
 */
#if (0)	/*******************************************************/
extern PARTTB	parttb[NPART];		/* A tabela de parti��es regular */
extern PARTTB	log_parttb[NPART][NLOGPART]; /* Idem, l�gicas */

extern daddr_t	fdisk_log_offset[NPART][NLOGPART]; /* Deslo. das par. l�gicas */
#endif	/*******************************************************/

/*
 ******	Tabela "fict�cia" para os discos IDE ou  SCSI ***********
 */
extern HDINFO	generic_hdinfo;	/* Gen�rico */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		geo_get_parttb_geo (const PARTTB *, HDINFO *gp, daddr_t disksz, const char *dev_nm, int);
