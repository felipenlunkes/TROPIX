/*
 ****************************************************************
 *								*
 *			extern.h				*
 *								*
 *	Defini��es externas					*
 *								*
 *	Vers�o	3.0.0, de 28.07.94				*
 *		4.9.0, de 14.04.06				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

/*
 ****** Declara��es externas ************************************
 */
extern int		vflag;			/* Verbose */

extern void		*malloc_mem0;		/* Para malloc */
extern void		*malloc_area_begin;

extern const char	*def_dev_nm;		/* Dispositivo default */
extern const char	*def_pgm_nm;		/* Programa default */
extern const char	*boot1_dev_nm;		/* Sugest�o de boot (de "boot1") */

extern long		video_cor;		/* Cor atual */
#if (0)	/*******************************************************/
extern long		video_pos;		/* Posi��o do cursor */
#endif	/*******************************************************/
extern int		video_line;		/* Para controlar a tela cheia */
extern char		video_mode;		/* Diferente de 0 se SVGA */
extern char		supervga_code;		/* C�digo de erro do SVGA */
extern const char	video_8x16_tb[];		/* A Fonte de caracteres 8x16 */

extern int		time_out;		/* O usu�rio nada teclou */

extern void		*ramd_addr;		/* Endere�o da RAMD */

extern int		global_target_index;	/* Pr�ximo dispositivo SCSI */
extern daddr_t		daddrvec[];		/* Endere�os do arquivo */

extern char		parttb_orig_block[BLSZ];/* Para o bloco 0 do disco */
extern const PARTNM	partnm[];		/* Tabela de tipos de parti��es */

extern int		CPU_speed;
extern int		cpu_index;

extern char		boot1_devcode;		/* Dados herdados do "boot1" */
extern daddr_t		boot1_offset;


#ifdef	BCB_H
extern BCB		bcb;			/* Bloco de informa��es para o KERNEL */
#endif	BCB_H

#ifdef	DISKTB_H
extern DISKTB		disktb[];		/* Tabela atual de parti��es */
extern DISKTB		proto_disktb[];		/* Tabela para os ancestrais */
#endif	DISKTB_H

#ifdef	ATA_H
extern ATA_DEVICE	*ata_ptr[];		/* Cont�m somente as unidades presentes */
extern int		ata_index;		/* �ndice da entrada seguinte */
#endif	ATA_H

#ifdef	SCSI_H
extern SCSI		*scsi_ptr[];		/* Cont�m somente as unidades presentes */
extern int		scsi_index;		/* �ndice da entrada seguinte */
#endif	SCSI_H
