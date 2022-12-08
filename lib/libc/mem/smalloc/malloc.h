/*
 ****************************************************************
 *								*
 *			<malloc.h>				*
 *								*
 *	Defini��es para a aloca��o din�mica de mem�ria		*
 *								*
 *	Vers�o	1.0.0, de 03.09.86				*
 *		3.0.0, de 06.07.95				*
 *								*
 *	M�dulo: malloc.h					*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1995 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Definic�o de macros *************************************
 */
#define	_LONGROUND(n)	(((n) + 3) & ~3)

#define	smalloc(n)	(_sm_base = _sm_next,				\
			(_sm_next += _LONGROUND (n)) <= _sm_end ?	\
				_sm_base : _smalloc (n))

/*
 ******	Vari�veis Externas **************************************
 */
extern void	*_sm_base, *_sm_next, *_sm_end;

/*
 ******	Prot�tipos das fun��es **********************************
 */
extern void	*_smalloc (int);
extern void	sfree (void);
