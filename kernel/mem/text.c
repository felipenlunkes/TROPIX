/*
 ****************************************************************
 *								*
 *			text.c					*
 *								*
 *	Fun��es de manipula��o dos TEXTs			*
 *								*
 *	Vers�o	3.0.0, de 26.11.94				*
 *		4.3.0, de 22.06.02				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/map.h"
#include "../h/inode.h"
#include "../h/bhead.h"
#include "../h/a.out.h"
#include "../h/mmu.h"
#include "../h/signal.h"
#include "../h/uproc.h"
#include "../h/uerror.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Aloca um TEXT						*
 ****************************************************************
 */
int
xalloc (INODE *ip)
{
	REGIONL		*rlp = &u.u_text;
	REGIONG		*rgp = NOREGIONG;
	HEADER		*hp = ip->i_xheader;
	int		byte_size = hp->h_tsize + hp->h_dsize;

	/*
	 *	Recebe e devolve o "ip" LOCKED
	 */
   	rlp->rgl_regiong = NOREGIONG;
   /***	rlp->rgl_vaddr	 = taddr; ***/
	rlp->rgl_prot	 = URO;
	rlp->rgl_type 	 = RG_TEXT;

	u.u_inode = ip;

	/*
	 *	Analisa o INODE
	 */
	if ((ip->i_flags & ITEXT) == 0)		/* � um TEXT novo */
	{
		if (ip->i_union != IN_NULL)
			printf ("%g: Campo \"union\" %d n�o NULO\n", ip->i_union);

		ip->i_xsize    = BYUPPG (byte_size);
	   /***	ip->i_xdaddr   = 0; ***/
		ip->i_xcount   = 0;
		ip->i_xregiong = NOREGIONG;

		ip->i_flags |= ITEXT;	/* IXSWAP e IXCORE off */
		ip->i_union  = IN_TEXT;

		iinc (ip);

		if ((ip->i_mode & IMETX) == 0)
		{
			if ((ip->i_xdaddr = malloc (M_SWAP, PGTOBL (ip->i_xsize))) == NOPG)
			{
#if (0)	/*******************************************************/
				printf ("%g: N�o consegui obter �rea de SWAP para \"%s\"\n", u.u_name);
#endif	/*******************************************************/
			}
		}
	}

	/*
	 *	Verifica se j� h� uma regi�o (mem�ria) alocada
	 */
	if ((rgp = ip->i_xregiong) == NOREGIONG)
	{
		if (regiongrow (rlp, 0, ip->i_xsize, 0) < 0)
			{ u.u_error = ENOMEM; return (-1); }

		rgp = rlp->rgl_regiong;

		strcpy (rgp->rgg_name, u.u_name);
	   /***	rgp->rgg_type	 = ...; ***/
		rgp->rgg_flags	 = (ip->i_mode & IMETX) ? RGG_METX : 0;
	   /***	rgp->rgg_size	 = ...; ***/
	   /***	rgp->rgg_paddr	 = ...; ***/
	   /***	rgp->rgg_pgtb	 = ...; ***/
	   /***	rgp->rgg_count   = 1; ***/

		ip->i_xregiong	 = rgp;
	}
	else		/* J� tem mem�ria alocada */
	{
		rlp->rgl_regiong = rgp;

		SPINLOCK (&rgp->rgg_regionlock);
		rgp->rgg_count++;
		SPINFREE (&rgp->rgg_regionlock);

		mmu_dir_load (rlp);
	}


	/*
	 *	Verifica se o TEXT j� est� residente na mem�ria
	 */
	if   (ip->i_flags & IXCORE)		/* J� est� na mem�ria */
	{
		/* Nada precisa ser feito */
	}
	elif (ip->i_flags & IXSWAP)		/* Le do SWAP */
	{
		swap (ip->i_xdaddr, rgp->rgg_paddr, ip->i_xsize, B_READ);
	}
	else					/* Le do INODE */
	{
		IOREQ		io;

	   /***	io.io_fd	 = ...;	***/
	   /***	io.io_fp	 = ...;	***/
		io.io_ip	 = ip;
	   /***	io.io_dev	 = ...;	***/
		io.io_area	 = (void *)PGTOBY (rgp->rgg_paddr);
		io.io_count	 = byte_size;
		io.io_offset_low = sizeof (HEADER);
		io.io_cpflag	 = SS;
	   /***	io.io_rablock	 = ...;	***/

		(*ip->i_fsp->fs_read) (&io);

		/*
		 *	Processa (se for o caso) as refer�ncias externas
		 */
		if (hp->h_refsize != 0)
		{
			void		*vp;
			int		mask;

			if ((vp = malloc_byte (hp->h_refsize)) == NOVOID)
				{ u.u_error = ENOMEM; return (-1); }

		   /***	io.io_fd	 = ...;	***/
		   /***	io.io_fp	 = ...;	***/
		   /***	io.io_ip	 = ip;	***/
		   /***	io.io_dev	 = ...;	***/
			io.io_area	 = vp;
			io.io_count	 = hp->h_refsize;
			io.io_offset_low = sizeof (HEADER) + byte_size + hp->h_ssize;
			io.io_cpflag	 = SS;
		   /***	io.io_rablock	 = ...;	***/

			(*ip->i_fsp->fs_read) (&io);

			mask = shlib_extref_resolve
			(
				(void *)PGTOBY (rgp->rgg_paddr), byte_size,
				vp, hp->h_refsize
			);

			if (mask < 0)
				{ u.u_error = ENOEXEC; free_byte (vp); return (-1); }

			hp->h_flags = mask;

			free_byte (vp);
		}
	}

	ip->i_flags |= IXCORE;
	ip->i_xcount++;

#if (0)	/*******************************************************/
	if (ip->i_xcount != rgp->rgg_count)
	{
		printf
		(	"%g: Contadores \"i_xcount\" e \"rgg_count\": (%d :: %d)\n",
			ip->i_xcount, rgp->rgg_count
		);
	}
#endif	/*******************************************************/

	return (0);

}	/* end xalloc */

/*
 ****************************************************************
 *	Libera um TEXT						*
 ****************************************************************
 */
int
xrelease (INODE *ip)
{
	REGIONG		*rgp;

	/*
	 *	C�digo de retorno:
	 *
	 *		 1: Deixou de ser TEXT
	 *		 0: Continua sendo TEXT
	 *		-1: N�o era TEXT
	 */
	if (ip->i_union != IN_TEXT)
		printf ("%g: Campo \"union\" n�o TEXT\n");

	if ((ip->i_flags & ITEXT) == 0)
		{ printf ("%g: O INODE n�o � de um TEXT\n"); return (-1); }

	if ((rgp = ip->i_xregiong) == NOREGIONG)
		{ printf ("%g: Ponteiro \"i_xregiong\" NULO\n"); return (-1); }

	/*
	 *	Verifica se era o �ltimo usu�rio e/ou deve salvar o TEXT
	 */
	if (--ip->i_xcount > 0 || ip->i_mode & (ISVTX|IMETX))
	{
		if (rgp->rgg_count == 1 && (ip->i_mode & IMETX) == 0)
		{
			if ((ip->i_flags & IXSWAP) == 0 && ip->i_xdaddr != NOPG)
			{
				swap (ip->i_xdaddr, rgp->rgg_paddr, ip->i_xsize, B_WRITE);

				ip->i_flags |= IXSWAP;
			}

			ip->i_xregiong	 = NOREGIONG;
			ip->i_flags	&= ~IXCORE;
		}

		regionrelease (&u.u_text);	/* Decrementa "rgg_count" */
#ifdef	MSG
		if (CSWT (25))
		{
			printf
			(	"%g: INO = %d, i_count = %d, i_xcount = %d, rgg_count = %d\n",
				ip->i_ino, ip->i_count, ip->i_xcount, rgp->rgg_count
			);
		}
#endif	MSG
		return (0);
	}

	/*
	 *	Era o �ltimo usu�rio e n�o deve salvar o TEXT nem
	 *	na mem�ria nem no SWAP: O INODE deixa de ser TEXT
	 */
	if (rgp->rgg_count != 1)
		printf ("%g: Inconsist�ncia de \"rgg_count\": (%d :: 1)\n", rgp->rgg_count);

	if (ip->i_xdaddr)
		mrelease (M_SWAP, PGTOBL (ip->i_xsize), ip->i_xdaddr);

	regionrelease (&u.u_text);	/* Decrementa "rgg_count" */

	ip->i_xregiong	 = NOREGIONG;
	ip->i_flags	&= ~(ITEXT|IXSWAP|IXCORE);
	ip->i_union	 = IN_NULL;

	free_byte (ip->i_xheader);

	memclr (&ip->u, sizeof (ip->u));

#ifdef	MSG
	if (CSWT (25))
	{
		printf
		(	"%g: INO = %d, i_count = %d, i_xcount = %d, rgg_count = %d\n",
			ip->i_ino, ip->i_count, ip->i_xcount, rgp->rgg_count
		);
	}
#endif	MSG

	return (1);

}	/* end xrelease */

/*
 ****************************************************************
 *	O INODE deixa de ser TEXT				*
 ****************************************************************
 */
int
xuntext (INODE *ip, int lockflag)
{
	REGIONG		*rgp;

	/*
	 *	Processamento do LOCK:
	 *	se lockflag =
	 *	  0 Supoe que ip j� esteja locked,
	 *	    e se for um TEXT, i_count > 1.
	 *	  1 Supoe que ip n�o esteja locked,
	 *	    e d� o lock/unlock.
	 *
	 *	Retorna:
	 *	  0 se o inode n�o � um TEXT,
	 *	    ou era e foi liberado.
	 *	 -1 se o INODE � um TEXT e n�o
	 *	    pode ser liberado
	 */

	if (lockflag)
		SLEEPLOCK (&ip->i_lock, PSCHED);

	if ((ip->i_flags & ITEXT) == 0)
	{
		if (lockflag)
			SLEEPFREE (&ip->i_lock);

		return (0);
	}

	/*
	 *	Verifica se h� usu�rios deste TEXT
	 */
	if (ip->i_xcount != 0)
	{
		if (lockflag)
			SLEEPFREE (&ip->i_lock);

		return (-1);
	}

	/*
	 *	Libera a regi�o TEXT
	 */
	if ((rgp = ip->i_xregiong) != NOREGIONG)
	{
		if (rgp->rgg_count != 0)
			printf ("%g: Inconsist�ncia de \"rgg_count\": (%d :: 0)\n", rgp->rgg_count);

	   /***	ip->i_xregiong  = NOREGIONG; ***/

		rgp->rgg_flags &= ~RGG_METX;

		regiongrelease (rgp, 1 /* untext */);
	}

	/*
	 *	Libera o TEXT no SWAP
	 */
	if (ip->i_xdaddr)
		mrelease (M_SWAP, PGTOBL (ip->i_xsize), ip->i_xdaddr);

	/*
	 *	Libera a entrada Text do INODE
	 */
	memclr (&ip->u, sizeof (ip->u));
	ip->i_flags &= ~(ITEXT|IXSWAP|IXCORE);

	/*
	 *	Decrementa as referencias
	 */
	if (lockflag)
		iput (ip);
	else
		idec (ip);

	return (0);

}	/* end xuntext */

/*
 ****************************************************************
 *	Tenta desalocar todos os TEXTs de um Dispositivo	*
 ****************************************************************
 */
int
xumount (dev_t dev)
{
	INODE		*ip;
	int		count = 0;

	/*
	 *	Retorna:
	 *	   0: N�o   tem mais nenhum TEXT no Dispositivo.
	 *	  -i: Ainda tem "i" TEXTs no Dispositivo
	 */
	for (ip = scb.y_inode; ip < scb.y_endinode; ip++)
	{
		if (ip->i_mode == 0)
			continue;

		if ((ip->i_flags & ITEXT) && ip->i_dev == dev)
		{
			if (xuntext (ip, 1 /* lock */) < 0)
				count--;
		}
	}

	return (count);

}	/* end xumount */
