/*
 ****************************************************************
 *								*
 *			<assert.h>				*
 *								*
 *	Emite diagn�sticos para express�es falsas		*
 *								*
 *	Vers�o	2.3.0, de 26.02.90				*
 *		3.0.0, de 08.06.95				*
 *								*
 *	M�dulo: assert.h					*
 *		/usr/include					*
 *		Categoria B					*
 * 								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1995 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��o de macros					*
 ****************************************************************
 */
#undef	assert

#ifdef	NDEBUG

#	define assert(expr)	((void)0)

#else

	extern void	_assert (const char *, const char *, int);

#	define assert(expr) if ((expr) == 0) _assert (#expr, __FILE__, __LINE__)

#endif	NDEBUG
