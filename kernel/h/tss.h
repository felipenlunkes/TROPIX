/*
 ****************************************************************
 *								*
 *			<sys/tss.h>				*
 *								*
 *	Defini��o da estrutura de TASK				*
 *								*
 *	Vers�o	3.0.0, de 28.08.94				*
 *		3.0.0, de 28.08.94				*
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

#define	DINO_H			/* Para definir os prot�tipos */

/*
 ******	Estrutura "task state segment" **************************
 */
struct tss
{
	long	tss_link;	/* TSS anterior */
	void	*tss_sp0; 	/* Pilha do n�vel 0 */
	long	tss_ss0;	/* Segmento de pilha n�vel 0 */
	void	*tss_sp1; 	/* Pilha do n�vel 1 */
	long	tss_ss1;	/* Segmento de pilha n�vel 1 */
	void	*tss_sp2; 	/* Pilha do n�vel 2 */
	long	tss_ss2;	/* Segmento de pilha n�vel 2 */

	long	tss_cr3; 	/* Diret�rio da tabela de p�ginas */
	void	*tss_pc; 	/* Contador do programa */
	long	tss_sr; 	/* Estado do processador */

	long	tss_r0; 	/* Registros do usu�rio */
	long	tss_r1; 
	long	tss_r2; 
	long	tss_r3; 
	long	tss_sp;
	long	tss_fp;
	long	tss_r4; 
	long	tss_r5; 

	long	tss_es;		/* Registros de segmenta��o */
	long	tss_cs;
	long	tss_ss;
	long	tss_ds;
	long	tss_fs;
	long	tss_gs;
	long	tss_ldt;
	long	tss_iomap;
};
