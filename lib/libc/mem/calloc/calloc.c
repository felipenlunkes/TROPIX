/*
 ****************************************************************
 *								*
 *			calloc.c				*
 *								*
 *	Aloca��o din�mica de mem�ria zerada			*
 *								*
 *	Vers�o	1.0.0, de 27.06.86				*
 *		3.2.3, de 08.12.99				*
 *								*
 *	M�dulo: malloc						*
 *		libc/mem					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

/*
 ****** Defini��o da ARENA **************************************
 */
#define	PGSZ		4096		/* Incremento para "sbrk" */
#define	PGMASK		(PGSZ-1)	/* M�scara para "sbrk" */

#define	BUSY		1		/* O endere�o � sempre par */

#define	IS_BUSY(p)	((p) &  BUSY)

#define	WITH_BUSY(p)	((STORE *)((int)(p) |  BUSY))
#define	WITHOUT_BUSY(p)	((STORE *)((int)(p) & ~BUSY))

#define	SET_BUSY(p)	((p) |=  BUSY)
#define	CLR_BUSY(p)	((p) &= ~BUSY)

typedef	union store	STORE;

union store
{
	int	m_status;		/* O bloco est� ou n�o em uso */
	STORE	*m_ptr;			/* Aponta para o pr�ximo bloco */
};

#define	STORE_SHIFT	2		/* LOG (2) (sizeof (STORE)) */

#define	NOSTORE		(STORE *)NULL

extern	STORE	*_malloc_base;		/* Primeiro elemento da Arena */
extern	STORE	*_malloc_top;		/* �ltimo elemento da Arena */

extern	STORE	*_malloc_search;	/* Ptr para busca */

/*
 ****** Depura��o ***********************************************
 */
#ifdef	DEBUG

#define ASSERT(expr)	if ((expr) == 0)		\
			{				\
				 _malloc_assert (__FILE__, __LINE__); \
			}

extern void	_malloc_assert (const char *, int);

#else

#define ASSERT(expr)

#endif	DEBUG

/*
 ****************************************************************
 *	Aloca��o din�mica de mem�ria zerada			*
 ****************************************************************
 */
void *
calloc (size_t elem_count, size_t elem_sz)
{
	void		*area;
	int		store_count;

	/*
	 *	Aloca e zera a �rea
	 */
	store_count = (elem_count * elem_sz + sizeof (STORE) - 1) >> STORE_SHIFT;

	if ((area = malloc (store_count << STORE_SHIFT)) != NOVOID)
		memsetl (area, 0, store_count);

	return (area);

}	/* end calloc */
