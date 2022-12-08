/*
 ****************************************************************
 *								*
 *			<sys/bcb.h>				*
 *								*
 *	Conjunto de informa��es passado do BOOT para o KERNEL	*
 *								*
 *	Vers�o	3.0.0, de 31.08.94				*
 *		4.9.0, de 20.02.08				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2008 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	BCB_H			/* Para definir os prot�tipos */

#define	BCB_VERSION	5	/* Para conferir entre o "boot2" e o n�cleo */

/*
 ******	Informa��o sobre os discos IDE **************************
 */
typedef struct
{
	int	h_unit;		/* No. do controlador */
	int	h_port;		/* Porta inicial do controlador */
	int	h_target;	/* No. do disco neste controlador */

	char	h_letter;	/* Identifica��o do "target" */
	char	h_is_present;	/* Est� presente */
	char	h_bl_shift;	/* LOG (2) do tamanho do bloco */

	int	h_head;		/* No. de cabe�as  (REAL) */
	int	h_sect;		/* No. de setores  (REAL) */
	int	h_cyl;		/* No. de cilindros (REAL) */

	int	h_multi;	/* No. m�ximo de setores / opera��o */
	int	h_atavalid;	/* Valida��o */
	int	h_piomode;	/* PIO modes */
	int	h_wdmamode;	/* DMA modes */
	int	h_udmamode;	/* UDMA modes */

	int	h_flags;	/* Indicadores (ver abaixo) */

}	HDINFO;

#define NOHDINFO (HDINFO *)0	/* Ponteiro NULO */

/*
 ****** Bloco de informa��es ************************************
 */
struct bcb
{
	int		y_version;	/* No. da vers�o desta estrutura */

	int		y_video_pos;	/* Posi��o do cursor */

	int		y_cputype;	/* Tipo da CPU */
	int		y_cpu_features;	/* Caracter�sticas da CPU */

	int		y_DELAY_value;	/* Para 1 micro-segundo */

	int		y_physmem;	/* Mem�ria total (em KB) */

	int		y_ssize;	/* Tamanho da tabela de s�mbolos */

	const void	*y_disktb;	/* Endere�o da tabela de discos */
	int		y_disktb_sz;	/* Tamanho (em bytes) da tabela de discos */

	int		y_rootdev;	/* Dispositivo RAIZ */

	char		*y_dmesg_area;	/* Mensagens do "boot2" */
	char		*y_dmesg_ptr;
	const char	*y_dmesg_end;

	const void	*y_videodata;	/* Os dados do VIDEO (estrutura VIDEODATA) */

	void		*y_int_10_addr;	/* Endere�o (16 bits) da INT 10 */

	int		y_res[9];	/* Para 96 bytes */
};
