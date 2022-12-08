/*
 ****************************************************************
 *								*
 *			malloc.c				*
 *								*
 *	Aloca��o din�mica de mem�ria				*
 *								*
 *	Vers�o	1.0.0, de 17.07.87				*
 *		3.2.3, de 02.12.99				*
 *								*
 *	M�dulo: malloc						*
 *		libc/mem					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

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

entry	STORE	*_malloc_base;		/* Primeiro elemento da Arena */
entry	STORE	*_malloc_top;		/* �ltimo elemento da Arena */

entry	STORE	*_malloc_search;	/* Ptr para busca */

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
 *	Aloca��o din�mica de mem�ria				*
 ****************************************************************
 */
void *
malloc (int byte_count)
{
	STORE		*p, *q, *r;
	int		store_count, cnt;
	char		attached;

	/*
	 *	Calcula o n�mero de STOREs necess�rios
	 *	(leva em conta o pr�prio ponteiro, e arredonda)
	 */
	store_count = (byte_count + 2 * sizeof (STORE) - 1) >> STORE_SHIFT;

	/*
	 *	Verifica se � a primeira vez
	 */
	if (_malloc_base == NOSTORE)
	{
		p = _cbreak;

		if (brk ((void *)(((int)p + ((store_count + 1) << STORE_SHIFT) + PGMASK) & ~PGMASK)) == -1)
			return (NOVOID);

		q = (STORE *)_cbreak - 1; 

		_malloc_base = _malloc_search = p; _malloc_top = q;

		p->m_ptr = q; q->m_ptr = WITH_BUSY (p);
	}

	ASSERT (_malloc_search >= _malloc_base && _malloc_search <= _malloc_top);

	/*
	 *	Executa uma malha at� encontrar um bloco de tamanho adequado
	 */
	for (p = _malloc_search; /* vazio */; /* vazio */)
	{
		for (cnt = 0; /* abaixo */; /* abaixo */)
		{
			if (!IS_BUSY (p->m_status))
			{
				/*
				 *	Aglutina, se for o caso
				 */
				while (q = p->m_ptr, !IS_BUSY (q->m_status))
				{
					ASSERT (q > p && q < _malloc_top);
					p->m_ptr = q->m_ptr;
				}
				/*
				 *	Verifica se o tamanho � suficiente
				 */
				if (q >= (r = p + store_count))
				{
					_malloc_search = r;

					ASSERT (r <= _malloc_top);

					if (q > r)
						r->m_ptr = q;

					p->m_ptr = WITH_BUSY (r);

					return (p + 1);
				}

			}	/* end if (aglutinando) */

			/*
			 *	Tenta o pr�ximo bloco
			 */
			q = p;	p = WITHOUT_BUSY (p->m_ptr);

			if   (p > q)
				{ ASSERT (p <= _malloc_top); }
			elif (q != _malloc_top || p != _malloc_base)
				{ ASSERT (0); }
			elif (cnt++ > 0)
				break;

		}	/* end for (duas voltas) */

		/*
		 *	N�o encontrou um bloco adequado
		 *	Pede mais mem�ria ao KERNEL
		 */
		p = _cbreak; attached = 0; cnt = store_count; r = _malloc_top;

		if (p == r + 1)
			attached++;
		else
			cnt++;

		if (brk ((void *)(((int)p + (cnt << STORE_SHIFT) + PGMASK) & ~PGMASK)) == -1)
			return (NOVOID);

		q = (STORE *)_cbreak - 1; 

		ASSERT (p > r);

		if (attached)
		{
			r->m_ptr = q;
		}
		else
		{
			r->m_ptr = WITH_BUSY (p);
			p->m_ptr = q;
		}

		_malloc_top = q;
		p = _malloc_base;
		q->m_ptr = WITH_BUSY (p);

	}	/* end for (EVER) */

}	/* end malloc */

#ifdef	DEBUG
/*
 ****************************************************************
 *	Imprime uma mensagem de erro				*
 ****************************************************************
 */
void
_malloc_assert (const char *file, int line)
{
	fprintf
	(	stderr,
		"%s (%s, %d): Arena inconsistente\n",
		pgname, file, line
	);

}	/* end _malloc_assert */

#endif	DEBUG
