/*
 ****************************************************************
 *								*
 *			machine.h				*
 *								*
 *	Define machine-dependencies for bison			*
 *								*
 *	Vers�o	3.0.0, de 06.07.93				*
 *		3.0.0, de 06.07.93				*
 *								*
 *	M�dulo: GBISON						*
 *		Gerador de analisadores sint�ticos		*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Baseado em software hom�nimo do GNU		*
 * 								*
 ****************************************************************
 */


/*
 ****************************************************************
 *	Define machine-dependencies for bison			*
 ****************************************************************
 */
#define	MAXSHORT	32767
#define	MINSHORT	-32768

#define	BITS_PER_WORD	32
#define MAXTABLE	32767

#define	WORDSIZE(n)	(((n) + BITS_PER_WORD - 1) / BITS_PER_WORD)
#define	SETBIT(x, i)	((x)[(i)/BITS_PER_WORD] |= (1<<((i) % BITS_PER_WORD)))
#define RESETBIT(x, i)	((x)[(i)/BITS_PER_WORD] &= ~(1<<((i) % BITS_PER_WORD)))
#define BITISSET(x, i)	(((x)[(i)/BITS_PER_WORD] & (1<<((i) % BITS_PER_WORD))) != 0)
