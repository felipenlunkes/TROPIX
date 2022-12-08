/*
 ****************************************************************
 *								*
 *			region.c				*
 *								*
 *	Fun��es para manuseio de regi�es de mem�ria		*
 *								*
 *	Vers�o	3.0.0, de 20.10.94				*
 *		4.6.0, de 11.08.04				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/cpu.h"
#include "../h/map.h"
#include "../h/inode.h"
#include "../h/bhead.h"
#include "../h/signal.h"
#include "../h/uproc.h"
#include "../h/uerror.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry LOCK	regionglock;		/* Lock para a lista global de regi�es */
entry REGIONG	*regiongfreelist;	/* Ponteiro para a lista livre de REGIONG */
entry int	regiong_list_count;	/* Contador de REGIONG usados */

#undef	REGIONLOG
#ifdef	REGIONLOG
/*
 ****** Protocolo das chamadas a "regiongrow" *******************
 */
typedef struct
{
	long	r_pid;
	int	r_type;
	pg_t	r_old_size;
	pg_t	r_new_size;

}	REGION_LOG;

#define NLOG	200

entry REGION_LOG	region_log[NLOG];
entry REGION_LOG	*region_log_ptr = region_log;

#endif	REGIONLOG

/*
 ****************************************************************
 *	Altera o tamanho de uma regi�o				*
 ****************************************************************
 */
int
regiongrow (REGIONL *rlp, pg_t new_vaddr, pg_t new_size, int opflags)
{
	pg_t		old_size = 0;
	pg_t		old_paddr, new_paddr;
	pg_t		inc;
	REGIONG		*rgp;

	/*
	 *	Pequena consist�ncia
	 */
	if (rlp->rgl_type == 0)
		{ printf ("%g: Tipo da regi�o NULO ?\n"); return (-1); }

	if (rlp->rgl_prot == 0)
		{ printf ("%g: Prote��o da regi�o NULO ?\n"); return (-1); }

	/*
	 *	Se o novo endere�o virtual n�o � dado, n�o muda
	 */
	if (new_vaddr == 0)
		new_vaddr = rlp->rgl_vaddr;

#ifdef	REGIONLOG
	/*
	 *	Guarda o LOG
	 */
	if (region_log_ptr >= &region_log[NLOG])
		region_log_ptr = &region_log[0];

	region_log_ptr->r_pid		= u.u_pid;
	region_log_ptr->r_type		= rlp->rgl_type;
	region_log_ptr->r_old_size	= 0;
	region_log_ptr->r_new_size	= new_size;

	if (rlp->rgl_regiong != NOREGIONG)
		region_log_ptr->r_old_size = rlp->rgl_regiong->rgg_size;

	region_log_ptr++;
#endif	REGIONLOG

	/*
	 ******	Verifica se a regi�o vai desaparecer ************
	 */
	if (new_size <= 0)
	{
		if (new_size < 0)
			printf ("%g: Tamanho %d negativo\n", new_size);

		regionrelease (rlp);
		return (0);
	}

	/*
	 ******	Verifica se o endere�o virtual mudou ************
	 */
	if (new_vaddr != rlp->rgl_vaddr && rlp->rgl_type != RG_STACK && rlp->rgl_vaddr != NOPG)
	{
		char	rgl_type = rlp->rgl_type;
		char	rgl_prot = rlp->rgl_prot;
#ifdef DEBUG
		printf ("regiongrow: Endere�o virtual mudando de %P para %P\n", rlp->rgl_vaddr, new_vaddr);
#endif DEBUG
		regionrelease (rlp);

		rlp->rgl_type = rgl_type;
		rlp->rgl_prot = rgl_prot;
	}

	/*
	 ******	J� que a regi�o n�o existia, cria uma nova ******
	 */
	if ((rgp = rlp->rgl_regiong) == NOREGIONG)
	{
		/*
		 *	Aloca uma entrada na tabela REGIONG
		 */
		if ((rlp->rgl_regiong = rgp = regiongget ()) == NOREGIONG)
			{ printf ("%g: N�o consegui alocar entrada REGIONG\n"); return (-1); }

		/*
		 *	Aloca o espa�o f�sico necess�rio
		 */
		if (rlp->rgl_type == RG_TEXT)	/* TEXT => fim da mem�ria */
			rgp->rgg_paddr = malloce (M_CORE, new_size);
		else
			rgp->rgg_paddr = malloc (M_CORE, new_size);

		if (rgp->rgg_paddr == NOPG)
		{
			printf ("%g: N�o consegui mem�ria para regi�o TEXT nova\n");
			regiongput (rgp); u.u_error = ENOMEM; return (-1);
		}

		if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
		{
			printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");
			mrelease (M_CORE, new_size, rgp->rgg_paddr);
			regiongput (rgp); u.u_error = ENOMEM; return (-1);
		}

		/*
		 *	Resumo das informa��es
		 */
	   /***	rlp->rgl_type		= (dado);			***/
	   /***	rlp->rgl_prot		= (dado);			***/
		rlp->rgl_vaddr		= new_vaddr;
	   /***	rlp->rgl_regiong	= (acima);			***/

	   /***	rgp->rgg_name		= (regiongget);			***/
		rgp->rgg_type		= rlp->rgl_type;
	   /***	rgp->rgg_flags		= (regiongget, zerado);		***/
	   /***	rgp->rgg_regionlock	= (regiongget, zerado);		***/
	   /***	rgp->rgg_pgtb_sz	= (mmu_page_table_alloc);	***/
		rgp->rgg_size		= new_size;
	   /*** rgp->rgg_paddr		= (acima);			***/
	   /*** rgp->rgg_pgtb		= (mmu_page_table_alloc;	***/
		rgp->rgg_count		= 1;
	   /*** rgp->rgg_next		= (regiongget, zerado);		***/

		/*
		 *	Ep�logo
		 */
		if (opflags & RG_CLR)
			pgclr (rgp->rgg_paddr, new_size);

		if ((opflags & RG_NOMMU) == 0)
			mmu_dir_load (rlp);

		return (0);
	}

	/*
	 ******	A regi�o j� existia *****************************
	 *
	 *	Se for compartilhada, n�o posso modificar
	 */
	if (rgp->rgg_count != 1)
	{
		printf ("%g: Regi�o tipo %d com %d usu�rios\n", rgp->rgg_type, rgp->rgg_count);
		return (-1);
	}

	if (rlp->rgl_type != rgp->rgg_type)
	{
		printf
		(	"%g: Tipo da regi�o N�O confere (%s :: %s)\n",
			region_nm_edit (rlp->rgl_type), region_nm_edit (rgp->rgg_type)
		);

		return (-1);
	}

	old_paddr = rgp->rgg_paddr;
	old_size  = rgp->rgg_size;

	/*
	 ******	A regi�o mant�m o tamanho ***********************
	 */
	if ((inc = new_size - old_size) == 0)
	{
		if (opflags & RG_CLR)
			pgclr (old_paddr, old_size);

		return (0);
	}

	/*
	 ******	A regi�o diminui de tamanho *********************
	 */
	if (inc < 0)
	{
		if ((opflags & RG_NOMMU) == 0)
			mmu_dir_unload (rlp);

		if (rgp->rgg_type != RG_STACK)	/* Cresce para CIMA */
		{
			mrelease (M_CORE, -inc, old_paddr + new_size);
		}
		else				/* Cresce para BAIXO */
		{
			mrelease (M_CORE, -inc, old_paddr);

			rgp->rgg_paddr -= inc;
		}

	   /***	rgp->rgg_paddr = ...; ***/

		mmu_page_table_alloc (rlp, new_vaddr, new_size);

		rlp->rgl_vaddr = new_vaddr;
		rgp->rgg_size  = new_size;

		if ((opflags & RG_NOMMU) == 0)
			mmu_dir_load (rlp);

		if (opflags & RG_CLR)
			pgclr (rgp->rgg_paddr, new_size);

		return (0);
	}

	/*
	 ******	A regi�o aumenta de tamanho no lugar ************ 
	 */
	if (rgp->rgg_type != RG_STACK)	/* N�O-STACK: Cresce para CIMA */
	{
		/* Verifica se h� mem�ria disponivel logo depois da regi�o */

		if (mallocp (M_CORE, inc, old_paddr + old_size) != NOPG)
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

		   /***	rgp->rgg_paddr = old_paddr; ***/

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, inc, old_paddr + old_size);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
				pgclr (old_paddr, new_size);
			else
				pgclr (old_paddr + old_size, inc);

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}

		/* Verifica se h� mem�ria dispon�vel logo antes da regi�o */

		if ((new_paddr = mallocp (M_CORE, inc, old_paddr - inc)) != NOPG)
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

			rgp->rgg_paddr = new_paddr;

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, inc, old_paddr - inc);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
			{
				pgclr (new_paddr, new_size);
			}
			else
			{
				pgcpy (new_paddr, old_paddr, old_size);
				pgclr (new_paddr + old_size, inc);
			}

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}
	}
	else				/* STACK: Cresce para BAIXO */
	{
		/* Verifica se h� mem�ria dispon�vel logo antes da regi�o */

		if ((new_paddr = mallocp (M_CORE, inc, old_paddr - inc)) != NOPG)
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

			rgp->rgg_paddr = new_paddr;

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, inc, old_paddr - inc);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
				pgclr (new_paddr, new_size);
			else
				pgclr (new_paddr, inc);

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}

		/* Verifica se h� mem�ria dispon�vel logo depois da regi�o */

		if (mallocp (M_CORE, inc, old_paddr + old_size) != NOPG)
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

		   /***	rgp->rgg_paddr = old_paddr; ***/

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, inc, old_paddr + old_size);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
			{
				pgclr (old_paddr, new_size);
			}
			else
			{
				pgcpy (old_paddr + inc, old_paddr, old_size);
				pgclr (old_paddr, inc);
			}

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}
	}

	/*
	 ******	A regi�o aumenta de tamanho em outro lugar ****** 
	 */
	if ((new_paddr = malloc (M_CORE, new_size)) != NOPG)
	{
		if (rgp->rgg_type != RG_STACK)	/* N�O-STACK: Cresce para CIMA */
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

			rgp->rgg_paddr = new_paddr;

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, new_size, new_paddr);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
			{
				pgclr (new_paddr, new_size);
			}
			else
			{
				pgcpy (new_paddr, old_paddr, old_size);
				pgclr (new_paddr + old_size, inc);
			}

			mrelease (M_CORE, old_size, old_paddr);

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}
		else				/* STACK: Cresce para BAIXO */
		{
			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_unload (rlp);

			rgp->rgg_paddr = new_paddr;

			if (mmu_page_table_alloc (rlp, new_vaddr, new_size) < 0)
			{
				printf ("%g: N�o consegui mem�ria para as tabelas de regi�o nova\n");

				mrelease (M_CORE, new_size, new_paddr);
				{ u.u_error = ENOMEM; return (-1); }
			}

			rlp->rgl_vaddr = new_vaddr;
			rgp->rgg_size  = new_size;

			if (opflags & RG_CLR)
			{
				pgclr (new_paddr, new_size);
			}
			else
			{
				pgcpy (new_paddr + inc, old_paddr, old_size);
				pgclr (new_paddr, inc);
			}

			mrelease (M_CORE, old_size, old_paddr);

			if ((opflags & RG_NOMMU) == 0)
				mmu_dir_load (rlp);

			return (0);
		}
	}

	{ u.u_error = ENOMEM; return (-1); }

}	/* end regiongrow */

/*
 ****************************************************************
 *	Duplica f�sica ou logicamente uma regi�o		*
 ****************************************************************
 */
int
regiondup (const REGIONL *rlp_src, REGIONL *rlp_dst, int opflags)
{
	REGIONG		*rgp_src;

	/*
	 *	A regi�o destino n�o deve existir ainda
	 */
	if (rlp_dst->rgl_regiong != NOREGIONG)
	{
		printf ("%g: Regi�o %s destino j� existente!\n", region_nm_edit (rlp_src->rgl_type));
		print_calls ();

		return (-1);
	}

	/*
	 *	Se a regi�o fonte n�o existe, por defini��o, j� est� duplicada
	 */
	if ((rgp_src = rlp_src->rgl_regiong) == NOREGIONG)
		return (0);

	/*
	 *	Copia os campos comuns
	 */
	rlp_dst->rgl_type  = rlp_src->rgl_type;
	rlp_dst->rgl_prot  = rlp_src->rgl_prot;
	rlp_dst->rgl_vaddr = rlp_src->rgl_vaddr;

	/*
	 *	Verifica se duplica logicamente ou fisicamente
	 */
	if (opflags & RG_LOGDUP)
	{
#ifdef	MSG
		if (CSWT (25))
			printf ("%g: Duplicando logicamente rlp = %P, rgp = %P\n", u.u_pid, rlp_src, rgp_src);
#endif	MSG
		/*
		 *	Duplica logicamente uma regi�o
		 */
		rlp_dst->rgl_regiong = rgp_src;

		SPINLOCK (&rgp_src->rgg_regionlock);
		rgp_src->rgg_count++;
		SPINFREE (&rgp_src->rgg_regionlock);
	}
	else
	{
#ifdef	MSG
		if (CSWT (25))
			printf ("%g: Duplicando fisicamente rlp = %P, rgp = %P\n", u.u_pid, rlp_src, rgp_src);
#endif	MSG
		/*
		 *	Duplica fisicamente uma regi�o
		 */
		if (regiongrow (rlp_dst, 0, rgp_src->rgg_size, RG_NOMMU) < 0)
			{ printf ("%g: Regi�o n�o pode ser duplicada\n"); return (-1); }

		pgcpy (rlp_dst->rgl_regiong->rgg_paddr, rgp_src->rgg_paddr, rgp_src->rgg_size);
	}

	return (0);

}	/* end regiondup */

/*
 ****************************************************************
 *	Libera uma regi�o alocada mas n�o usada			*
 ****************************************************************
 */
void
regionrelease (REGIONL *rlp)
{
	REGIONG		*rgp;

	if ((rgp = rlp->rgl_regiong) == NOREGIONG)
		return;

	mmu_dir_unload (rlp);

	regiongrelease (rgp, 0);

	memclr (rlp, sizeof (REGIONL));

}	/* end regionrelease */

/*
 ****************************************************************
 *	Libera uma regi�o REGIONG				*
 ****************************************************************
 */
int
regiongrelease (REGIONG *rgp, int untext)
{
	/*
	 *	Decrementa o contador (exceto "untext")
	 */
	SPINLOCK (&rgp->rgg_regionlock);

	if (!untext)
		rgp->rgg_count--;

	if (rgp->rgg_count > 0)
	{
		SPINFREE (&rgp->rgg_regionlock);
		return (1);
	}

	SPINFREE (&rgp->rgg_regionlock);

	/*
	 *	Verifica se � para manter na mem�ria
	 */
	if (rgp->rgg_flags & RGG_METX)
		return (1);

	/*
	 *	N�o � para manter na mem�ria: libera a mem�ria alocada
	 */
	if (rgp->rgg_pgtb != NOPG)
		mrelease (M_CORE, rgp->rgg_pgtb_sz, rgp->rgg_pgtb);

	if (rgp->rgg_type != RG_PHYS)
		mrelease (M_CORE, rgp->rgg_size, rgp->rgg_paddr);

	regiongput (rgp);

	return (0);

}	/* end regiongrelease */

/*
 ****************************************************************
 *	Obt�m uma entrada na tabela REGIONG			*
 ****************************************************************
 */
REGIONG *
regiongget (void)
{
	REGIONG		*rgp;

	SPINLOCK (&regionglock);

	if ((rgp = regiongfreelist) == NOREGIONG)
		{ SPINFREE (&regionglock); return (NOREGIONG); }

	regiongfreelist = rgp->rgg_next; rgp->rgg_next = NOREGIONG;

	regiong_list_count++;

	SPINFREE (&regionglock);

	strcpy (rgp->rgg_name, u.u_pgname);

	return (rgp);

}	/* end regiongget */

/*
 ****************************************************************
 *	Libera uma estrutura REGIONG para a regiongfreelist	*
 ****************************************************************
 */
void
regiongput (REGIONG *rgp)
{
	memclr (rgp, sizeof (REGIONG));

	SPINLOCK (&regionglock);

	rgp->rgg_next = regiongfreelist; regiongfreelist = rgp;

	regiong_list_count--;

	SPINFREE (&regionglock);

}	/* end regiongput */

/*
 ****************************************************************
 *	Inicializa a lista de REGIONG				*
 ****************************************************************
 */
void
regionginit (void)
{
	REGIONG		*rp, *np;

   /***	SPINLOCK (&regionglock); ***/

	np = NOREGIONG;

	for (rp = scb.y_endregiong - 1; rp >= scb.y_regiong; rp--)
		{ rp->rgg_next = np; np = rp; }

	regiongfreelist = np;
   /***	regiong_list_count = 0; ***/

   /***	SPINFREE (&regionglock); ***/

}	/* end regionginit */

/*
 ****************************************************************
 *	Edita o nome de uma regi�o				*
 ****************************************************************
 */
const char	region_nm_vec[][12] = RG_NAMES;

const char *
region_nm_edit (int region_type)
{
	if (region_type < RG_NONE || region_type > RG_SHMEM)
		return ("???");
	else
		return (region_nm_vec[region_type]);

}	/* end mmu_region_nm_edit */
