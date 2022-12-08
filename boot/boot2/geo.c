/*
 ****************************************************************
 *								*
 *			geo.c					*
 *								*
 *	C�lculos referentes � geometria dos discos		*
 *								*
 *	Vers�o	3.0.0, de 29.09.96				*
 *		3.0.6, de 21.03.97				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1996 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/syscall.h>
#include <sys/bcb.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "h/common.h"
#include "h/ide.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.2.3, de x.99";

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
int		geo_get_parttb_geo (const char *, HDINFO *);
int		geo_get_std_method (const char *, HDINFO *);
int		geo_get_cyl (const PARTTB *);
int		geo_get_sec (int, ulong, const TRIO *);
int		geo_get_heu_method (const char *, HDINFO *);
int		geo_cmp_trio_with_linear (const PARTTB *, const HDINFO *);
long		geo_get_linear_blno (const TRIO *, const HDINFO *);
void		geo_print_size (int index, const PARTTB *pp);
void		help (void);

/*
 ****************************************************************
 *	Programa para tentar obter a geometria 			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, fd, index;
	const char	*file_nm;
	char		block0[512];
	const PARTTB	*pp;
	HDINFO		g;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	L� o arquivo
	 */
	if ((file_nm = argv[0]) == NOSTR)
		help ();

	if ((fd = open (file_nm, O_RDONLY)) < 0)
		error ("$*N�o consegui abrir o arquivo \"%s\"", file_nm);

	if (read (fd, &block0, sizeof (block0)) != sizeof (block0))
		error ("$*Erro na leitura do arquivo \"%s\"", file_nm);

	/*
	 *	Assume o valor m�ximo
	 */
	g.h_head = 255;
	g.h_sect = 63;

	/*
	 *	Imprime as 4 parti��es
	 */
	for
	(	index = 0, pp = (PARTTB *)(block0 + PARTB_OFF);
		index < 4;
		index++, pp++
	)
	{
		geo_print_size (index, pp);
		printf
		(	"%d, %d\n", 
			geo_get_linear_blno (&pp->pt_start, &g),
			geo_get_linear_blno (&pp->pt_end, &g)
		);
	}

	g.h_head = 0;
	g.h_sect = 0;

	/*
	 *	x
	 */
	geo_get_parttb_geo (block0, &g);

	return (exit_code);

}	/* end geo */

/*
 ****************************************************************
 *	Tenta obter a geometria a partir das parti��es		*
 ****************************************************************
 */
int
geo_get_parttb_geo (const char *block0, HDINFO *gp)
{
	daddr_t		CYLSZ;

	/*
	 *	Tenta os dois m�todos
	 */
	if (geo_get_std_method (block0, gp) >= 0)
		goto found;

	if (geo_get_heu_method (block0, gp) >= 0)
		goto found;

	/*
	 *	N�O conseguiu: solu��o alternativa
	 */
#if (0)	/*******************************************************/
		if (disksz > (1 * GBSZ) / BLSZ)
			{ gp->h_head = 255; gp->h_sect = 63; }
		else
#endif	/*******************************************************/
			{ gp->h_head = 64; gp->h_sect = 32; }

	printf
	(	"N�O consegui obter a geometria; "
		"Usando a geometria (%d, %d)\n",
		gp->h_head, gp->h_sect
	);

	/*
	 *	Calcula o n�mero de cilindros
	 */
    found:
	CYLSZ = gp->h_head * gp->h_sect;
#if (0)	/*******************************************************/
	gp->h_cyl = (disksz + CYLSZ - 1) / CYLSZ;
#endif	/*******************************************************/

	printf
	( 	"Usando a geometria (%d, %d)\n",
		gp->h_head, gp->h_sect
	);

	return (0);

}	/* end geo_get_parttb_geo */

/*
 ****************************************************************
 *	M�todo 1: 2 equa��es com duas inc�gnitas		*
 ****************************************************************
 */
int
geo_get_std_method (const char *block0, HDINFO *gp)
{
	int		index;
	const PARTTB	*pp;
	int		CYLSZ;

	/*
	 *	Calcula o tamanho do cilindro
	 */
	for
	(	index = 0, pp = (PARTTB *)(block0 + PARTB_OFF);
		/* abaixo */;
		index++, pp++
	)
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
	for
	(	index = 0, pp = (PARTTB *)(block0 + PARTB_OFF);
		/* abaixo */;
		index++, pp++
	)
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

	printf ("Consegui com o m�todo ortodoxo (%d, %d)\n", gp->h_sect, gp->h_head);

	return (0);

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
geo_get_heu_method (const char *block0, HDINFO *gp)
{
	const PARTTB	*pp;
	int		index;

	/*
	 *	Primeiro procura uma parti��o talvez terminada em cilindro
	 */
	for
	(	index = 0, pp = (PARTTB *)(block0 + PARTB_OFF);
		/* abaixo */;
		index++, pp++
	)
	{
		if (index >= NPART)
			return (-1);

		if (pp->pt_size == 0)
			continue;

		gp->h_sect = (pp->pt_end.sect & 0x3F) - 1 + 1;
		gp->h_head =  pp->pt_end.head + 1;

printf ("Tentando (%d, %d)\n", gp->h_sect, gp->h_head);

		if (geo_cmp_trio_with_linear (pp, gp) >= 0)
			break;
	}

	/*
	 *	Agora confere em todas as parti��es
	 */
	for
	(	index = 0, pp = (PARTTB *)(block0 + PARTB_OFF);
		index < NPART;
		index++, pp++
	)
	{
		if (pp->pt_size == 0)
			continue;

#if (0)	/*******************************************************/
		/* Lembrar os casos de discos com mais de 1024 cilindros */

		if (pp->pt_start.cyl > pp->pt_end.cyl)
			continue;
#endif	/*******************************************************/

		if (geo_cmp_trio_with_linear (pp, gp) < 0)
			return (-1);

	}

	printf ("Consegui com a heur�stica (%d, %d)\n", gp->h_sect, gp->h_head);

	return (0);

}	/* end geo_get_heu_method */

/*
 ****************************************************************
 *  Compara as 2 representa��es levando em conta o truncamento	*
 ****************************************************************
 */
int
geo_cmp_trio_with_linear (const PARTTB *pp, const HDINFO *gp)
{
	char		big;
	daddr_t		diff, offset, last;

	/*
	 *	Verifica se � um disco com poss�velmente mais de 8 GB
	 */
	if (gp->h_head == 255 && gp->h_sect == 63)
		big = 1;
	else
		big = 0;

	/*
	 *	Examina o in�cio da parti��o
	 */
	offset = geo_get_linear_blno (&pp->pt_start, gp);

	if ((diff = pp->pt_offset - offset) != 0)
	{
		if (!big || (diff % (255 * 63) != 0))
			return (-1);
	}

	/*
	 *	Examina o final da parti��o
	 */
	last = geo_get_linear_blno (&pp->pt_end, gp);

	if ((diff = (pp->pt_offset + pp->pt_size - (last + 1))) != 0)
	{
		if (!big || (diff % (255 * 63) != 0))
			return (-1);
	}

	/*
	 *	Conseguiu
	 */
	return (0);

}	/* end geo_cmp_trio_with_linear */

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

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - programa\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-op��es] arg\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-x: op��o\n"
		"\t-y: op��o\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados argumentos\n"
		"\nObs.:\tobserva��o\n"
	);

	exit (2);

}	/* end help */
