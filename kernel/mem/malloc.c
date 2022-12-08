/*
 ****************************************************************
 *								*
 *			malloc.c				*
 *								*
 *	Gerencia da mem�ria interna e swap			*
 *								*
 *	Vers�o	3.0.0, de 04.10.94				*
 *		4.0.0, de 04.04.01				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/scb.h"
#include "../h/sync.h"

#include "../h/map.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
entry LOCK		map_lock[2];	/* Locks das Tabelas */

#define map_core_lock	map_lock[0]	/* Lock da Tabela da Memoria */
#define map_swap_lock	map_lock[1]	/* Lock da Tabela do Disco */

/* Os Locks acima, e as cabe�as abaixo, s�o para serem indexados pelo "enum" */

#define	map_core_head	scb.y_map[0]	/* Cabe�a da tabela da Mem�ria */
#define	map_swap_head	scb.y_map[1]	/* Cabe�a da tabela da Mem�ria */
#define	map_head	scb.y_map	/* Cabe�a da tabela */
#define	RESER_MAPs	2		/* Os dois acima */

entry LOCK		map_free_lock;	/* Lock da Tabela de Mapas */
entry MAP		*map_free_list;	/* Lista livre das entradas */

entry int		map_busy_count;	/* N�mero de entradas ocupadas */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
MAP		*map_get_free_entry (void);
void		map_put_free_entry (MAP *);

/*
 ****************************************************************
 *	Alloca uma �rea de mem�ria f�sica			*
 ****************************************************************
 */
pg_t
malloc (int map, pg_t size)
{
	LOCK		*lock;
	MAP		*ap, *bp, *head;
	pg_t		area = NOPG;

	/*
	 *	Aloca a Tabela
	 */
	lock = &map_lock[map];
	head = &map_head[map];

	SPINLOCK (lock);

	/*
	 *	Procura uma entrada do tamanho desejado
	 */
	head->a_size = size;

	for (bp = head->a_forw; bp->a_size < size; bp = bp->a_forw)
		/* vazio */;

	if (bp != head)
	{
	 	/*
		 *	Achou uma �rea de tamanho Adequado
		 */
		area = bp->a_area; bp->a_area += size;

		if ((bp->a_size -= size) == 0) 	/* Desaparece uma �rea */
		{
			ap = bp->a_back;

			ap->a_forw = bp->a_forw;
			bp->a_forw->a_back = ap;

			map_put_free_entry (bp);
		}
	}

	/*
	 *	libera a Tabela
	 */
	SPINFREE (lock);

#define	DEBUG
#ifdef	DEBUG
	if (CSWT (38))
		printf ("%g: size = %d KB, addr = %d KB\n", PGTOKB (size), PGTOKB (area - BYTOPG (SYS_ADDR)));
#endif	DEBUG

	return (area);

}	/* end malloc */

/*
 ****************************************************************
 *	Alloca uma �rea (de cima para baixo)			*
 ****************************************************************
 */
pg_t
malloce (int map, pg_t size)
{
	LOCK		*lock;
	MAP		*ap, *bp, *head;
	pg_t		area = NOPG;

	/*
	 *	Aloca a Tabela
	 */
	lock = &map_lock[map];
	head = &map_head[map];

	SPINLOCK (lock);

	/*
	 *	Procura uma entrada do tamanho desejado
	 */
	head->a_size = size;

	for (bp = head->a_back; bp->a_size < size; bp = bp->a_back)
		/* vazio */;

	if (bp != head)
	{
	 	/*
		 *	Achou uma �rea de tamanho Adequado
		 */
		area = bp->a_area + bp->a_size - size;

		if ((bp->a_size -= size) == 0) 	/* Desaparece uma �rea */
		{
			ap = bp->a_back;

			ap->a_forw = bp->a_forw;
			bp->a_forw->a_back = ap;

			map_put_free_entry (bp);
		}
	}

	/*
	 *	libera a Tabela
	 */
	SPINFREE (lock);

#ifdef	DEBUG
	if (CSWT (38))
		printf ("%g: size = %d KB, addr = %d KB\n", PGTOKB (size), PGTOKB (area - BYTOPG (SYS_ADDR)));
#endif	DEBUG

	return (area);

}	/* end malloce */

/*
 ****************************************************************
 *	Alloca uma �rea, em um lugar dado			*
 ****************************************************************
 */
pg_t
mallocp (int map, pg_t size, pg_t area)
{
	LOCK		*lock;
	MAP		*ap, *bp, *head;
	pg_t		end_addr;

	/*
	 *	Aloca a Tabela
	 */
	lock = &map_lock[map];
	head = &map_head[map];

	SPINLOCK (lock);

	/*
	 *	Procura a �nica entrada adequada
	 */
	end_addr = area + size;

	for (bp = head->a_forw; /* abaixo */; bp = bp->a_forw)
	{
		if (bp == head)
			{ SPINFREE (lock); return (NOPG); }

		if (bp->a_area + bp->a_size >= end_addr && bp->a_area <= area)
			break;
	}

	/*
	 *	Achou; faz um teste de consist�ncia
	 */
	if   (bp->a_area == area)
	{
		bp->a_area += size;
	}
	elif (bp->a_area + bp->a_size != end_addr)
	{
		printf ("%g: Foi pedida uma �rea n�o adjacente"); SPINFREE (lock); return (NOPG);
	}

	/*
	 *	Verifica se desaparece uma regi�o
	 */
	if ((bp->a_size -= size) == 0)
	{
		ap = bp->a_back;

		ap->a_forw = bp->a_forw;
		bp->a_forw->a_back = ap;

		map_put_free_entry (bp);
	}

	SPINFREE (lock);

#ifdef	DEBUG
	if (CSWT (38))
		printf ("%g: size = %d KB, addr = %d KB\n", PGTOKB (size), PGTOKB (area - BYTOPG (SYS_ADDR)));
#endif	DEBUG

	return (area);

}	/* end mallocp */

/*
 ****************************************************************
 *	Alloca uma �rea especialmente para DMA de 24 bits	*
 ****************************************************************
 */
pg_t
malloc_dma_24 (pg_t *sz_ptr)
{
	MAP		*head, *ap, *bp, *np;
	pg_t		addr;
	pg_t		size;
	pg_t		max_addr = 0, max_size = 0;
	MAP		*max_bp = (MAP *)NULL;

	/*
	 *	Tenta achar uma regi�o de 64 KB, alinhada em 64 KB,
	 *	nos 16 MB iniciais da mem�ria.
	 *	Se n�o encontrar, tenta achar uma �rea menor.
	 */
#define M64KBSZ		((64 * KBSZ) >> PGSHIFT)
#define M64KBMASK	(M64KBSZ - 1)
#define M16MBLIMIT	(BYUPPG (SYS_ADDR + 16 * MBSZ))

	head = &map_core_head; SPINLOCK (&map_core_lock);

	/*
	 *	Procura uma entrada com as caracter�sticas desejadas
	 */
	for (bp = head->a_forw; bp != head; bp = bp->a_forw)
	{
		if ((addr = bp->a_area) >= M16MBLIMIT)
			break;

		/* Arredonda para 64 KB */

		addr += M64KBMASK; addr &= ~M64KBMASK;

		/* Acha o tamanho realmente us�vel */

		size = bp->a_size - (addr - bp->a_area);

		if (addr + size > M16MBLIMIT)
			size = M16MBLIMIT - addr;

		/* Verifica se a regi�o � melhor do que a anterior */

		if (size > max_size)
			{ max_addr = addr; max_size = size; max_bp = bp; }

		/* Verifica se a regi�o tem 64 KB */

		if (size >= M64KBSZ)
			{ max_size = M64KBSZ; break; }

	}	/* end varrendo a tabela "map" */

	/*
	 *	Verifica se achou uma regi�o adequada
	 */
	addr = max_addr; size = max_size; bp = max_bp;

	if (size == 0)
		{ SPINFREE (&map_core_lock); return (NOPG); }

	/*
	 *	Achou uma regi�o adequada: Faz um teste de consist�ncia
	 */
	if (addr < bp->a_area || addr + size > bp->a_area + bp->a_size)
	{
		SPINFREE (&map_core_lock);

		printf ("%g: Erro: (%P, %d) :: (%P, %d)\n", addr, size, bp->a_area, bp->a_size);
		return (NOPG);
	}

	/*
	 *	Atualiza o mapa de mem�ria
	 */
	if   (addr == bp->a_area)		/* Encosta em baixo */
	{
	 	bp->a_area += size;

		if ((bp->a_size -= size) == 0) 	/* Desaparece uma �rea */
		{
			ap = bp->a_back;

			ap->a_forw = bp->a_forw;
			bp->a_forw->a_back = ap;

			map_put_free_entry (bp);
		}
	}
	elif (addr + size == bp->a_area + bp->a_size) /* Encosta em cima */
	{
		bp->a_size -= size;

		/* Nesta caso, N�O pode desaparecer uma �rea */
	}
	else				/* N�O encosta em cima NEM em baixo */
	{
		/* Verifica se h� espaco para mais uma entrada na tabela */

		if ((np = map_get_free_entry ()) == NOMAP)
			{ SPINFREE (&map_core_lock); printf ("%g: Overflow da coremap"); return (NOPG); }

		np->a_area = addr + size;
		np->a_size = bp->a_area + bp->a_size - np->a_area;

	   /***	bp->a_area = ...; ***/
		bp->a_size = addr - bp->a_area;

		np->a_forw = bp->a_forw;
		np->a_back = bp;

		bp->a_forw = np;
		np->a_forw->a_back = np;

	}	/* end if (diversos encostos) */

	/*
	 *	Ep�logo: libera a tabela
	 */
	SPINFREE (&map_core_lock); *sz_ptr = size; return (addr);

}	/* end malloc_dma_24 */

/*
 ****************************************************************
 *	Libera a �rea						*
 ****************************************************************
 */
void
mrelease (int map, pg_t size, pg_t area)
{
	SCB		*sp = &scb;
	LOCK		*lock;
	MAP		*ap, *bp, *head;
	pg_t		end_addr = area + size;

#ifdef	DEBUG
	if (CSWT (38))
	{
		printf ("%g: size = %d KB, addr = %d KB\n", PGTOKB (size), PGTOKB (area - BYTOPG (SYS_ADDR)));

if (size == 1)
print_calls ();
	}
#endif	DEBUG

	/*
	 *	Aloca a tabela
	 */
	lock = &map_lock[map];
	head = &map_head[map];

	SPINLOCK (lock);

	/*
	 *	Verifica se a �rea a ser liberada n�o � de tamanho nulo
	 */
	if (size == 0)
	{
	    bad:
		SPINFREE (lock);

		printf
		(	"%g: %s error: addr = %P (%d), size = %d\n",
			map == M_CORE ? "Core" : "Swap",
			area, area, size
		);

		return;
	}

	/*
	 *	Verifica se os valores dados est�o dentro dos valores f�sicos
	 */
	if (map == M_CORE)
	{
		if
		(	(area < sp->y_ucore0 || end_addr > sp->y_enducore0) &&
			(area < sp->y_ucore1 || end_addr > sp->y_enducore1)
		)
			goto bad;
	}
	else /*	map == M_SWAP */
	{
		if (area < SWAP_OFFSET || end_addr > sp->y_nswap + SWAP_OFFSET)
			goto bad;
	}

	/*
	 *	Procura a primeira entrada de endere�o maior ou igual ao endere�o dado.
	 *	Se n�o existir, aponta para a a cabe�a da lista
	 */
	head->a_area = area;

	for (bp = head->a_forw; bp->a_area < area; bp = bp->a_forw)
		/* vazio */;

	/*
	 *	Verifica se os dados fornecidos n�o v�o se
	 *	superpor com a entrada anterior ou posterior
	 */
	if ((ap = bp->a_back) != head && ap->a_area + ap->a_size > area)
		goto bad;

	if (bp != head && end_addr > bp->a_area)
		goto bad;

	/*
	 *	Verifica se a �rea encosta embaixo
	 *	Se for o caso junta embaixo
	 */
	if (ap != head && ap->a_area + ap->a_size == area)
	{
		/*
		 *	Encosta em Baixo
		 */
		ap->a_size += size;

		/*
		 *	Verifica se tambem encosta em cima
		 *	Se for o caso junta em cima
		 */
		if (bp != head && end_addr == bp->a_area)
		{
			ap->a_size += bp->a_size;

			ap->a_forw = bp->a_forw;
			bp->a_forw->a_back = ap;

			map_put_free_entry (bp);
		}
	}
	else
	{
		/*
		 *	N�o encosta embaixo; Verifica se encosta em cima
		 */
		if (bp != head && end_addr == bp->a_area)
		{
			/*
			 *	encosta em cima; junta em cima
			 */
			bp->a_area -= size;
			bp->a_size += size;
		}
		else
		{
			/*
			 *	N�o encosta em cima nem embaixo;
			 *	Cria uma entrada nova (abrindo uma nova �rea)
			 */
			if ((bp = map_get_free_entry ()) == NOMAP)
				panic ("mrelease: Overflow da %smap", map == M_CORE ? "Core" : "Swap");

			bp->a_size = size;
			bp->a_area = area;
			bp->a_back = ap;
			bp->a_forw = ap->a_forw;

			bp->a_forw->a_back = bp;
			ap->a_forw = bp;

		}	/* end if encosta em cima */

	}	/* end if encosta embaixo */

	SPINFREE (lock);

}	/* end mrelease */

/*
 ****************************************************************
 *	Libera todas as entradas de um dos mapas		*
 ****************************************************************
 */
void
mrelease_all (int map)
{
	LOCK		*lock;
	MAP		*np, *bp, *head;

	/*
	 *	Aloca a Tabela
	 */
	lock = &map_lock[map];
	head = &map_head[map];

	SPINLOCK (lock);

	/*
	 *	Libera todas as �reas
	 */
	for (bp = head->a_forw; bp != head; bp = np)
	{
		np = bp->a_forw;
		map_put_free_entry (bp);
	}

	head->a_forw = head->a_back = head;

	/*
	 *	libera a Tabela
	 */
	SPINFREE (lock);

}	/* end mrelease_all */

/*
 ****************************************************************
 *	Obt�m uma estrutura MAP					*
 ****************************************************************
 */
MAP *
map_get_free_entry (void)
{
	MAP		*bp;

	SPINLOCK (&map_free_lock);

	if ((bp = map_free_list) != NOMAP)
	{
		map_free_list = bp->a_forw;
		map_busy_count++;
	}

	SPINFREE (&map_free_lock);

	return (bp);

}	/* end map_get_free_entry */

/*
 ****************************************************************
 *	Libera uma estrutura MAP				*
 ****************************************************************
 */
void
map_put_free_entry (MAP *bp)
{
	SPINLOCK (&map_free_lock);

	bp->a_forw = map_free_list;
	map_free_list = bp;
	map_busy_count--;

	SPINFREE (&map_free_lock);

}	/* end map_put_free_entry */

/*
 ****************************************************************
 *	Inicializa a lista de MAPs				*
 ****************************************************************
 */
void
map_init_free_list (void)
{
	MAP	*bp, *np;

	np = NOMAP;

   /***	SPINLOCK (&map_free_lock); ***/

	/* Repare que as duas primeiras entradas s�o as cabe�as */

	for (bp = scb.y_endmap - 1; bp >= scb.y_map + RESER_MAPs; bp--)
		{ bp->a_forw = np; np = bp; }

	map_free_list = np;

	bp = &map_core_head; bp->a_forw = bp->a_back = bp;

	bp = &map_swap_head; bp->a_forw = bp->a_back = bp;

   /***	SPINFREE (&map_free_lock); ***/

}	/* end map_init_free_list */
