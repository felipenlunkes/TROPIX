/*
 ****************************************************************
 *								*
 *			chkalloc.c				*
 *								*
 *	Analisa a arena da aloca��o din�mica			*
 *								*
 *	Vers�o	1.0.0, de 17.07.87				*
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

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
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
#define ASSERT(expr)	if ((expr) == 0)		\
			{				\
				 _malloc_assert (__FILE__, __LINE__); \
				return_code = -1;	\
			}

extern void	_malloc_assert (const char *, int);

/*
 ****************************************************************
 *	Analisa a arena da aloca��o din�mica			*
 ****************************************************************
 */
int
chkalloc (void)
{
	STORE		*p;
	int		search_found = 0;
	int		return_code = 0;

	/*
	 *	Percorre a arena
	 */
	for (p = _malloc_base; WITHOUT_BUSY (p->m_ptr) > p; p = WITHOUT_BUSY (p->m_ptr))
	{
		if (p == _malloc_search)
			search_found++;
	}

	/*
	 *	Verifica o cont�udo dos ponteiros
	 */
	ASSERT (p == _malloc_top);

	ASSERT (WITHOUT_BUSY (_malloc_top->m_ptr) == _malloc_base);

	ASSERT (search_found == 1 || _malloc_search == p);

	return (return_code);

}	/* end chkalloc */
