/*
 ****************************************************************
 *								*
 *			<sys/seg.h>				*
 *								*
 *	Defini��es relativas � segmenta��o do 486		*
 *								*
 *	Vers�o	3.0.0, de 20.08.94				*
 *		3.0.0, de 10.01.95				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	SEG_H			/* Para incluir os prot�tipos */

/*
 ****** Seletores ***********************************************
 */
#define	KERNEL_CS	(1 * 8 + 0)
#define	KERNEL_DS	(2 * 8 + 0)

#define	USER_CS		(3 * 8 + 3)
#define	USER_DS		(4 * 8 + 3)

#define	KERNEL_TSS	(5 * 8 + 0)
#define	SYS_CALL	(6 * 8 + 3)

#define SEL_PL(s)	((s) & 0x03)	/* Prioridade do seletor */

/*
 ******	Descritor de segmento de exce��o ou call gate ***********
 */
struct excep_dc
{
	bit	ed_low_offset : 16;	/* Parte baixa do deslocamento */
	bit	ed_selector : 16;	/* No. do seletor */
	bit	ed_args : 5;		/* No. de palavras a copiar */
	bit	ed_reser0 : 3;
	bit	ed_type : 5;		/* Tipo do segmento */
	bit	ed_dpl : 2;		/* Prioridade do segmento */
	bit	ed_present : 1;		/* Segmento presente */
	bit	ed_high_offset : 16;	/* Parte alta do deslocamento */
};
