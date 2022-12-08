/*
 ****************************************************************
 *								*
 *			realloc.c				*
 *								*
 *	Realoca��o de mem�ria alocada din�micamente		*
 *								*
 *	Vers�o	1.0.0, de 17.07.87				*
 *		3.2.3, de 06.12.99				*
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

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	DEBUG

#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;

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
				return (NOVOID);	\
			}

extern void	_malloc_assert (const char *, int);

#else

#define ASSERT(expr)

#endif	DEBUG

/*
 ****************************************************************
 *	Realoca��o de mem�ria alocada din�micamente		*
 ****************************************************************
 */
void *
realloc (void *area, int byte_count)
{
	STORE		*p, *q, *r, *s, *t;
	int		old_store_count, new_store_count;

	/*
	 *	Verifica se foi dado o endere�o
	 */
	if (area == NOVOID)
		return (malloc (byte_count));

	p = area - sizeof (STORE);

	if (!IS_BUSY (p->m_status))
	{
		fprintf (stderr, "%s (realloc): A �rea N�O est� alocada\n", pgname);
		return (NOVOID);
	}

	old_store_count = WITHOUT_BUSY (p->m_ptr) - p;

	new_store_count = (byte_count + 2 * sizeof (STORE) - 1) >> STORE_SHIFT;

	/*
	 *	Aglutina os blocos seguintes
	 */
	while (q = WITHOUT_BUSY (p->m_ptr), !IS_BUSY (q->m_status))
	{
		ASSERT (q > p && q < _malloc_top);
		p->m_ptr = WITH_BUSY (q->m_ptr);
	}

	/*
	 *	Verifica se o espa�o � suficiente
	 */
	if (q >= (r = p + new_store_count))
	{
		_malloc_search = r;

		ASSERT (r <= _malloc_top);

		if (q > r)
			r->m_ptr = q;

		p->m_ptr = WITH_BUSY (r);

		return (p + 1);
	}

	/*
	 *	N�o foi suficiente a seguir; tenta antes
	 */
	for (t = _malloc_base; (r = WITHOUT_BUSY (t->m_ptr)) != q; /* abaixo */)
	{
		ASSERT (r > t && r < _malloc_top);

		if (IS_BUSY (t->m_status))
			{ t = r; continue; }

		s = (r == p) ? q : r;

		if (s - t >= new_store_count)
		{
			CLR_BUSY (p->m_status);

			memmove (t + 1, p + 1, (old_store_count - 1) << STORE_SHIFT);

			_malloc_search = r = t + new_store_count;

			if (s > r)
				r->m_ptr = s;

			t->m_ptr = WITH_BUSY (r);

			return (t + 1);
		}

		if (IS_BUSY (r->m_status))
			t = r;
		else
			t->m_ptr = r->m_ptr;
	}
		
	/*
	 *	Verifica se por acaso o bloco dado � o �ltimo da arena
	 */
	if (q == (STORE *)_cbreak - 1)
	{
		t = p + new_store_count;

		if (brk ((void *)(((int)(t + 1) + PGMASK) & ~PGMASK)) == -1)
		{
			/* Restaura o tamanho original */

		    ld_old_size:
			r = p + old_store_count;

			if (q > r)
				r->m_ptr = q;

			p->m_ptr = WITH_BUSY (r);

			return (NOVOID);
		}

		_malloc_top = q = (STORE *)_cbreak - 1; 

		_malloc_search = t;

		if (q > t)
			t->m_ptr = q;

		p->m_ptr = WITH_BUSY (t);
		q->m_ptr = WITH_BUSY (_malloc_base);

		return (p + 1);
	}

	/*
	 *	Definitivamente n�o h� espa�o
	 */
	if ((s = malloc (byte_count)) == NOVOID)
		goto ld_old_size;

	/*
	 *	Alocou em uma �rea nova
	 */
	memmove (s, p + 1, (old_store_count - 1) << STORE_SHIFT);

	free (p + 1);
	
	return (s);

}	/* end realloc */
