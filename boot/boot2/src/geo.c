/*
 ****************************************************************
 *								*
 *			geo.c					*
 *								*
 *	C�lculos referentes � geometria dos discos		*
 *								*
 *	Vers�o	3.0.0, de 29.09.96				*
 *		4.9.0, de 25.07.06				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <common.h>
#include <bcb.h>
#include <scsi.h>
#include <pci.h>
#include <ata.h>

#include "../h/common.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#undef	DEBUG

/*
 ****** Prot�tipos de fun��es ***********************************
 */
int		geo_get_std_method (const PARTTB *parttb, HDINFO *);
int		geo_get_cyl (const PARTTB *);
int		geo_get_sec (int, ulong, const TRIO *);
int		geo_get_heu_method (const PARTTB *parttb, HDINFO *);
int		geo_cmp_trio_with_linear (const PARTTB *, const HDINFO *);
int		geo_tst_one_geometry (const PARTTB *, const HDINFO *);
long		geo_get_linear_blno (const TRIO *, const HDINFO *);
int		geo_get_trio_blno (TRIO *, const HDINFO *, daddr_t);

/*
 ****************************************************************
 *	Tenta obter a geometria a partir das parti��es		*
 ****************************************************************
 */
int
geo_get_parttb_geo (const PARTTB *parttb, HDINFO *gp, daddr_t disksz, const char *dev_nm)
{
	daddr_t		CYLSZ;

	/*
	 *	Assume que n�o tem as extens�es da INT 13
	 */
	gp->h_flags &= ~HD_INT13_EXT;

	/*
	 *	Tenta os dois m�todos
	 */
	if (geo_get_std_method (parttb, gp) >= 0)
		goto found;

	if (geo_get_heu_method (parttb, gp) >= 0)
		goto found;

	/*
	 *	N�O conseguiu: solu��o alternativa
	 */
	if (dev_nm[0] == 's')	/* SCSI */
	{
		if (disksz > (1 * GBSZ) / BLSZ)
			{ gp->h_head = 255; gp->h_sect = 63; }
		else
			{ gp->h_head = 64; gp->h_sect = 32; }
	}
	else			/* IDE */
	{
		{ gp->h_head = 255; gp->h_sect = 63; }
	}

	printf
	(	"\e[34m"
		"\nN�O consegui obter a geometria de \"%s\". "
		"Usando a geometria (%d, %d)\n\n"
		"\e[0m",
		dev_nm, gp->h_head, gp->h_sect
	);

	/*
	 *	Calcula o n�mero de cilindros
	 */
    found:
	CYLSZ = gp->h_head * gp->h_sect;
	gp->h_cyl = (disksz + CYLSZ - 1) / CYLSZ;

	return (0);

}	/* end geo_get_parttb_geo */

/*
 ****************************************************************
 *	M�todo 1: 2 equa��es com duas inc�gnitas		*
 ****************************************************************
 */
int
geo_get_std_method (const PARTTB *parttb, HDINFO *gp)
{
	int		index;
	const PARTTB	*pp;
	int		CYLSZ;

	/*
	 *	Calcula o tamanho do cilindro
	 */
	for (index = 0, pp = parttb; /* abaixo */; index++, pp++)
	{
		if (index >= NPART)
			return (-1);

		if (pp->pt_size == 0)
			continue;

		if ((CYLSZ = geo_get_cyl (pp)) > 0)
			break;
	}

	/*
	 *	Calcula o tamanho do setor
	 */
	for (index = 0, pp = parttb; /* abaixo */; index++, pp++)
	{
		if (index >= NPART)
			return (-1);

		if (pp->pt_size == 0)
			continue;

		gp->h_sect = geo_get_sec
		(
			CYLSZ,
			pp->pt_offset,
			&pp->pt_start
		);

		if (gp->h_sect > 0)
			break;

		gp->h_sect = geo_get_sec
		(
			CYLSZ,
			pp->pt_offset + pp->pt_size - 1,
			&pp->pt_end
		);

		if (gp->h_sect > 0)
			break;
	}

	/*
	 *	Calcula o n�mero de cabe�as
	 */
	gp->h_head = CYLSZ / gp->h_sect;

	if (CYLSZ % gp->h_sect)
		return (-1);

	/*
	 *	Agora confere em todas as parti��es
	 */
	return (geo_tst_geometry (parttb, gp));

}	/* end geo_get_std_method */

/*
 ****************************************************************
 *	Calcula o tamanho do cilindro				*
 ****************************************************************
 */
int
geo_get_cyl (const PARTTB *pp)
{
	ulong		start_bno = pp->pt_offset;
	ulong		end_bno = pp->pt_offset + pp->pt_size - 1;
	ulong		big_b_h, small_b_h;
	ulong		big_h_c, small_h_c;
	ulong		above, below, CYLSZ;

	big_b_h = (start_bno - (pp->pt_start.sect & 0x3F) + 1) * pp->pt_end.head;
	small_b_h = (end_bno - (pp->pt_end.sect & 0x3F) + 1) * pp->pt_start.head;

	big_h_c = pp->pt_end.head * (pp->pt_start.cyl | ((pp->pt_start.sect & 0xC0) << 2));
	small_h_c = pp->pt_start.head * (pp->pt_end.cyl | ((pp->pt_end.sect & 0xC0) << 2));

	above = big_b_h - small_b_h;
	below = big_h_c - small_h_c;

	if ((int)above < 0)
		{ above = -above; below = -below; }

	if (above == 0 || below == 0)
		return (-1);

	CYLSZ = above / below;

	if (above % below)
		return (-1);

	return (CYLSZ);

}	/* end geo_get_cyl */

/*
 ****************************************************************
 *	Calcula o n�mero de setores por trilha			*
 ****************************************************************
 */
int
geo_get_sec (int CYLSZ, ulong bno, const TRIO *tp)
{
	ulong		above, below;
	int		NSECT;

	if ((below = tp->head) == 0)
		return (-1);

	above =  (bno - (tp->sect & 0x3F) + 1);
	above -= CYLSZ * (tp->cyl | ((tp->sect & 0xC0) << 2));

	if (above == 0)
		return (-1);

	NSECT = above / below;

	if (above % below)
		return (-1);

	return (NSECT);

}	/* end geo_get_sec */

/*
 ****************************************************************
 *    Heur�stica supondo que a parti��o termine em um cilindro	*
 ****************************************************************
 */
int
geo_get_heu_method (const PARTTB *parttb, HDINFO *gp)
{
	const PARTTB	*pp;
	int		index;

	/*
	 *	Primeiro procura uma parti��o talvez terminada em cilindro
	 */
	for (index = 0, pp = parttb; /* abaixo */; index++, pp++)
	{
		if (index >= NPART)
			return (-1);

		if (pp->pt_size == 0)
			continue;

		gp->h_sect = (pp->pt_end.sect & 0x3F) - 1 + 1;
		gp->h_head =  pp->pt_end.head + 1;

		if (geo_tst_one_geometry (pp, gp) >= 0)
			break;
	}

	/*
	 *	Agora confere em todas as parti��es
	 */
	return (geo_tst_geometry (parttb, gp));

}	/* end geo_get_heu_method */

/*
 ****************************************************************
 *	Confere t�das as parti��es, dada uma geometria		*
 ****************************************************************
 */
int
geo_tst_geometry (const PARTTB *parttb, const HDINFO *gp)
{
	const PARTTB	*pp;
	int		index;

	for (index = 0, pp = parttb; index < NPART; index++, pp++)
	{
		if (pp->pt_size == 0)
			continue;

		if (geo_tst_one_geometry (pp, gp) < 0)
			return (-1);
	}

	return (0);

}	/* end geo_tst_geometry */

/*
 ****************************************************************
 *	Confere uma parti��o, dada uma geometria		*
 ****************************************************************
 */
int
geo_tst_one_geometry (const PARTTB *pp, const HDINFO *gp)
{
	TRIO		trio;

	if (pp->pt_size == 0)
		return (-1);

	if (geo_get_trio_blno (&trio, gp, pp->pt_offset) < 0)
		return (-1);

	if
	(	trio.head != pp->pt_start.head ||
		trio.sect != pp->pt_start.sect ||
		trio.cyl  != pp->pt_start.cyl
	)
	{
#ifdef	DEBUG
		printf
		(	"ERRO: %d (%d, %d, %d) :: (%d, %d, %d)\n",
			pp->pt_offset,
			trio.cyl | (trio.sect & 0xC0) << 2, 
			trio.head,
			trio.sect & 0x3F,
			pp->pt_start.cyl | ((pp->pt_start.sect & 0xC0) << 2),
			pp->pt_start.head,
			pp->pt_start.sect & 0x3F
		);
#endif	DEBUG
		return (-1);
	}

	if (geo_get_trio_blno (&trio, gp, pp->pt_offset + pp->pt_size - 1) < 0)
		return (-1);

	if
	(	trio.head != pp->pt_end.head ||
		trio.sect != pp->pt_end.sect ||
		trio.cyl  != pp->pt_end.cyl
	)
	{
#ifdef	DEBUG
		printf
		(	"ERRO: %d (%d, %d, %d) :: (%d, %d, %d)\n",
			pp->pt_offset + pp->pt_size - 1,
			trio.cyl | (trio.sect & 0xC0) << 2, 
			trio.head,
			trio.sect & 0x3F,
			pp->pt_end.cyl | ((pp->pt_end.sect & 0xC0) << 2),
			pp->pt_end.head,
			pp->pt_end.sect & 0x3F
		);
#endif	DEBUG
		return (-1);
	}

	return (0);

}	/* end geo_tst_one_geometry */

#if (0)	/*******************************************************/
/*
 ****************************************************************
 *	Calcula o bloco linear a partir do trio			*
 ****************************************************************
 */
long
geo_get_linear_blno (const TRIO *tp, const HDINFO *gp)
{
	long		blkno;

	blkno  = gp->h_head * (tp->cyl | ((tp->sect & 0xC0) << 2));
	blkno += tp->head;
	blkno *= gp->h_sect;
	blkno += (tp->sect & 0x3F) - 1;

	return (blkno);

}	/* end geo_get_linear_blno */
#endif	/*******************************************************/

/*
 ****************************************************************
 *	Calcula o trio a partir do bloco linear			*
 ****************************************************************
 */
int
geo_get_trio_blno (TRIO *tp, const HDINFO *gp, daddr_t blkno)
{
	int	head, sect, cyl;

	if (gp->h_head <= 0 || gp->h_sect <= 0)
		return (-1);

	sect   = (blkno % gp->h_sect) + 1;
	blkno /= gp->h_sect;
	head   =  blkno % gp->h_head;
	blkno /= gp->h_head;
	cyl    = CYLMAX (blkno);

	tp->head = head;
	tp->sect = ((cyl & 0x0300) >> 2) | (sect & 0x3F);
	tp->cyl  = cyl;

	return (0);

}	/* end geo_get_linear_blno */

#ifdef	DEBUG
/*
 ****************************************************************
 *	Imprime os valores de uma parti��o			*
 ****************************************************************
 */
void
geo_print_size (int index, const PARTTB *pp)
{
	printf ("%4d:  ", index);

	printf
	(	"%9d %9d  ",
		pp->pt_offset, pp->pt_size
	);

	printf
	(	"(%4d,%3d,%3d) ",
		pp->pt_start.cyl | ((pp->pt_start.sect & 0xC0) << 2),
		pp->pt_start.head,
		pp->pt_start.sect & 0x3F
	);

	printf
	(	"(%4d,%3d,%3d)  ",
		pp->pt_end.cyl | ((pp->pt_end.sect & 0xC0) << 2),
		pp->pt_end.head,
		pp->pt_end.sect & 0x3F
	);

	printf ("\n");

}	/* end geo_print_size */
#endif	DEBUG
