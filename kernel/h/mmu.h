/*
 ****************************************************************
 *								*
 *			<sys/mmu.h>				*
 *								*
 *	Defini��es da ger�ncia de mem�ria			*
 *								*
 *	Vers�o	3.0.0, de 27.11.94				*
 *		4.6.0, de 11.08.04				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	MMU_H			/* Para definir os prot�tipos */

/*
 ******	Defini��o de tipos **************************************
 */
#define	MMUSZ		(sizeof (mmu_t))
#define	MMUSHIFT	2	/* Log (2) sizeof (mmu_t) */

/*
 ******	Endere�os virtuais das regi�es do usu�rio ***************
 *
 *	Se alterar, N�O ESQUECER de "ctl/common.s"!
 */
#define USER_TEXT_PGA		BYTOPG (	     4 * MBSZ)
#define USER_DATA_PGA		BYTOPG (	   256 * MBSZ)
#define USER_STACK_PGA		BYTOPG (1 * GBSZ + 252 * MBSZ)		/* 1276 MB */

/* 4 MB de intervalo */

#define USER_PHYS_PGA		USER_STACK_PGA + BYTOPG (  4 * MBSZ)	/* 1280 MB */
#define USER_PHYS_PGA_END	USER_PHYS_PGA  + BYTOPG (576 * MBSZ)	/* 1856 MB */

#define USER_SHLIB_PGA		USER_PHYS_PGA_END 			/* 1856 MB */
#define USER_IPC_PGA		USER_SHLIB_PGA + BYTOPG (128 * MBSZ)	/* 1984 MB */
#define USER_END_PGA		USER_IPC_PGA   + BYTOPG ( 16 * MBSZ)    /* 2000 MB */

/* 44 MB de intervalo */

#define	SVGA_ADDR		(unsigned)((2048 - 8) * MBSZ)		/* 2040 MB */
#define	UPROC_ADDR		(unsigned)((2048 - 4) * MBSZ)		/* 2044 MB */

/*
 ****** M�scara de prote��o das p�ginas	*************************
 */
#define	URO	5	/* P�gina de usu�rio RO */
#define	URW	7	/* P�gina de usu�rio RW */

#define	SRO	1	/* P�gina de supervisor RO */
#define	SRW	3	/* P�gina de supervisor RW */
