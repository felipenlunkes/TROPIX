/*
 ****************************************************************
 *								*
 *			lzw.h					*
 *								*
 *	Cabe�alho para o m�todo LZW				*
 *								*
 *	Vers�o	3.0.0, de 05.06.93				*
 *		3.0.0, de 05.06.93				*
 *								*
 *	M�dulo: GZIP						*
 *		Utilit�rios de compress�o/descompress�o		*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Baseado em software hom�nimo do GNU		*
 * 								*
 ****************************************************************
 */

#define BITS 16

#define INIT_BITS 9              /* Initial number of bits per code */

#define	LZW_MAGIC  "\037\235"   /* Magic header for lzw files, 1F 9D */

#define BIT_MASK    0x1f	/* Mask for 'number of compression bits' */

/* Mask 0x20 is reserved to mean a fourth header byte, and 0x40 is free.
 * It's a pity that old uncompress does not check bit 0x20. That makes
 * extension of the format actually undesirable because old compress
 * would just crash on the new format instead of giving a meaningful
 * error message. It does check the number of bits, but it's more
 * helpful to say "unsupported format, get a new version" than
 * "can only handle 16 bits".
 */

#define BLOCK_MODE  0x80
/* Block compression: if table is full and compression rate is dropping,
 * clear the dictionary.
 */

#define LZW_RESERVED 0x60 /* reserved bits */

#define	CLEAR  256       /* flush the dictionary */
#define FIRST  (CLEAR+1) /* first free entry */

extern int maxbits;      /* max bits per code for LZW */
extern int block_mode;   /* block compress mode -C compatible with 2.0 */

extern void	lzw (int in, int out);
extern void	unlzw (int in, int out);
