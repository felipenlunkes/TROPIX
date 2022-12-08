/*
 ****************************************************************
 *								*
 *			<setjmp.h>				*
 *								*
 *	Desvios n�o locais					*
 *								*
 *	Vers�o	1.0.0, de 20.11.86				*
 *		3.0.0, de 26.06.95				*
 *								*
 *	M�dulo: setjmp.h					*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1995 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��o de tipos					*
 ****************************************************************
 */
typedef int	jmp_buf[13];

/*
 ****************************************************************
 *	Prot�tipos						*
 ****************************************************************
 */
extern int	setjmp (jmp_buf);		/* Prepara o desvio */
extern void	longjmp (jmp_buf, int);		/* Desvia */
