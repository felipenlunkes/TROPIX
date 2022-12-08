/*
 ****************************************************************
 *								*
 *			cddir.c					*
 *								*
 *	Tratamento de diret�rios do ISO9660			*
 *								*
 *	Vers�o	4.2.0, de 26.12.01				*
 *		4.8.0, de 02.11.05				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/mntent.h"
#include "../h/sb.h"
#include "../h/kfile.h"
#include "../h/cdfs.h"
#include "../h/sysdirent.h"
#include "../h/inode.h"
#include "../h/stat.h"
#include "../h/bhead.h"
#include "../h/uerror.h"
#include "../h/signal.h"
#include "../h/uproc.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	cd_get_par_ino (INODE *);
int	cd_name_match (const DIRENT *, const CDDIR *dp, const SB *unisp);
int	cd_name_conv (char *dst, const CDDIR *dp, const SB *unisp);

/*
 ****************************************************************
 *	Procura um nome dado no diret�rio			*
 ****************************************************************
 */
int
cd_search_dir (IOREQ *iop, DIRENT *dep, int mission)
{
	INODE		*ip = iop->io_ip;
	dev_t		dev = ip->i_dev;
	BHEAD		*bp = NOBHEAD;
	const CDDIR	*dp, *end_dp;
	daddr_t		blkno, end_blkno;
	ino_t		ino;
	int		len;

	/*
	 *	Recebe e devolve o "ip" trancado
	 *
	 *	Se encontrou a entrada, devolve:
	 *		"dep->d_ino"			     o INO  (caso normal)
	 *		"dep->d_namlen" e "dep->d_name"	     o nome (caso INUMBER)
	 *		"iop->io_offset_low" o in�cio da entrada
	 *		"iop->io_count"	     o tamanho da entrada
	 *
	 *	(exceto para "." e "..")
	 */

	/*
	 *	Verifica se est� procurando por "." ou ".."
	 */
	if ((mission & INUMBER) == 0 && dep->d_name[0] == '.')
	{
		if   (dep->d_name[1] == '\0')
			{ dep->d_ino = ip->i_ino; return (1); }

		if (dep->d_name[1] == '.' && dep->d_name[2] == '\0')
		{
			if (ip->i_par_ino == NOINO)
				cd_get_par_ino (ip);

			dep->d_ino = ip->i_par_ino; return (1);
		}
	}

	/*
	 *	Obt�m os blocos inicial e final.
	 */
	blkno = ip->i_first_block; end_blkno = blkno + BYTOISOBL (ip->i_size);

	blkno--;	/* � Incrementado antes do primeiro uso */

	for (dp = end_dp = NOCDDIR; /* abaixo */; dp = (CDDIR *)((int)dp + len))
	{
		if (dp >= end_dp)
		{
			/* L� um bloco de diret�rio */

			if (bp != NOBHEAD)
				{ block_put (bp); bp = NOBHEAD; }

			if (++blkno >= end_blkno)
				return (0);

			if (blkno < end_blkno - 1)
				bp = breada (dev, ISOBL_TO_BL (blkno), ISOBL_TO_BL (blkno + 1), 0);
			else
				bp = bread (dev, ISOBL_TO_BL (blkno), 0);

			dp = bp->b_addr; end_dp = (CDDIR *)(bp->b_addr + ISO_BLSZ);
		}

		/* Usa as entradas deste bloco */

		if ((len = dp->d_len) == 0)
			{ dp = end_dp; continue; }

		if (mission & INUMBER)		/* Busca dado o INO */
		{
			ino = (blkno << ISO_BLSHIFT) + ((void *)dp - bp->b_addr);

			if (ino == dep->d_ino)
			{
				dep->d_namlen = cd_name_conv (dep->d_name, dp, ip->i_sb);

				block_put (bp); return (1);
			}
		}
		else				/* Busca dado o nome */
		{
			/* Pula "." e ".." */

			if (dp->d_name_len == 1 && dp->d_name[0] <= 1)
				continue;

			if (cd_name_match (dep, dp, ip->i_sb)) 			/* Achou */
			{
				ino = (blkno << ISO_BLSHIFT) + ((void *)dp - bp->b_addr);

				iop->io_offset_low = ino - (ip->i_first_block << ISO_BLSHIFT);
				dep->d_ino	   = ino;
				iop->io_count	   = len;

				/* P�e o nome original */

				dep->d_namlen = cd_name_conv (dep->d_name, dp, ip->i_sb);

				block_put (bp); return (1);
			}
		}

	}	/* end for (percorrendo as entradas) */

}	/* end cd_search_dir */

/*
 ****************************************************************
 *	Fornece entradas do diret�rio para o usu�rio 		*
 ****************************************************************
 */
void
cd_read_dir (IOREQ *iop)
{
	INODE		*ip = iop->io_ip;
	dev_t		dev = ip->i_dev;
	BHEAD		*bp = NOBHEAD;
	const CDDIR	*dp, *end_dp;
	int		len;
	daddr_t		blkno = 0, end_blkno;
	DIRENT		dirent;

	/*
	 *	Obt�m o INO do pai
	 */
	if (ip->i_par_ino == NOINO)
		cd_get_par_ino (ip);

	/*
	 *	Obt�m o bloco final
	 */
	end_blkno = ip->i_first_block + BYTOISOBL (ip->i_size);

	/*
	 *	Malha Principal
	 */
	for (dp = end_dp = NOCDDIR; iop->io_count >= sizeof (DIRENT); dp = (CDDIR *)((int)dp + len))
	{
		if (dp >= end_dp)
		{
			/* L� um bloco de diret�rio */

			if (bp != NOBHEAD)
				{ block_put (bp); bp = NOBHEAD; }

			blkno = ip->i_first_block + (iop->io_offset_low >> ISO_BLSHIFT);

			if (blkno >= end_blkno)
				{ iop->io_eof = 1; break; }

			if (blkno < end_blkno - 1)
				bp = breada (dev, ISOBL_TO_BL (blkno), ISOBL_TO_BL (blkno + 1), 0);
			else
				bp = bread (dev, ISOBL_TO_BL (blkno), 0);

			dp = bp->b_addr + (iop->io_offset_low & ISO_BLMASK);

			end_dp = (CDDIR *)(bp->b_addr + ISO_BLSZ);
		}

		/* Usa as entradas deste bloco */

		if ((len = dp->d_len) == 0)
		{
			iop->io_offset_low = (iop->io_offset_low + ISO_BLSZ) & ~ISO_BLMASK;
			dp = end_dp;
			continue;
		}

	   	dirent.d_offset	= iop->io_offset_low;

		/* Verifica se � "." e ".." */

		if (dp->d_name_len == 1 && dp->d_name[0] <= 1)
		{
			if   (dp->d_name[0] == '\0')
			{
				dirent.d_ino	= ip->i_ino;
				dirent.d_namlen	= 1;
				strcpy (dirent.d_name, ".");
			}
			else	/* dp->d_name[0] == '\1' */
			{
				dirent.d_ino	= ip->i_par_ino;
				dirent.d_namlen	= 2;
				strcpy (dirent.d_name, "..");
			}
		}
		else
		{
			dirent.d_ino	= (blkno << ISO_BLSHIFT) + (iop->io_offset_low & ISO_BLMASK);
			dirent.d_namlen	= cd_name_conv (dirent.d_name, dp, ip->i_sb);

			if (dirent.d_namlen < 0)	/* Diret�rios relocados => -1 */
				continue;
		}

		if (unimove (iop->io_area, &dirent, sizeof (DIRENT), iop->io_cpflag) < 0)
			{ u.u_error = EFAULT; break; }

		/* Avan�a os ponteiros */

		iop->io_area	   += sizeof (DIRENT);
		iop->io_offset_low += len;
		iop->io_count	   -= sizeof (DIRENT);

	}	/* end for (dp = ...) */
	
	/*
	 *	Postludium
	 */
	if (bp != NOBHEAD)
		block_put (bp);

}	/* end cd_read_dir */

/*
 ****************************************************************
 *	Obt�m o n�mero de refer�ncias a este diret�rio		*
 ****************************************************************
 */
void
cd_get_nlink_dir (INODE *ip)
{
	BHEAD		*bp = NOBHEAD;
	dev_t		dev = ip->i_dev;
	const CDDIR	*dp, *end_dp;
	daddr_t		blkno, end_blkno;
	int		len;

	/*
	 *	Come�a com "." e ".."
	 */
	ip->i_nlink = 2;

	/*
	 *	Obt�m os blocos inicial e final
	 */
	blkno = ip->i_first_block; end_blkno = blkno + BYTOISOBL (ip->i_size);

	blkno--;	/* � Incrementado antes do primeiro uso */

	/*
	 *	Malha Principal
	 */
	for (dp = end_dp = NOCDDIR; /* abaixo */; dp = (CDDIR *)((int)dp + len))
	{
		if (dp >= end_dp)
		{
			/* L� um bloco de diret�rio */

			if (bp != NOBHEAD)
				{ block_put (bp); bp = NOBHEAD; }

			if (++blkno >= end_blkno)
				return;

			if (blkno < end_blkno - 1)
				bp = breada (dev, ISOBL_TO_BL (blkno), ISOBL_TO_BL (blkno + 1), 0);
			else
				bp = bread (dev, ISOBL_TO_BL (blkno), 0);

			dp = bp->b_addr; end_dp = (CDDIR *)(bp->b_addr + ISO_BLSZ);

		}

		/* Usa as entradas deste bloco */

		if ((len = dp->d_len) == 0)
			{ dp = end_dp; continue; }

		/* Pula "." e ".." */

		if (dp->d_name_len == 1 && dp->d_name[0] <= 1)
			continue;

		if ((dp->d_flags & ISO_IFMT) == ISO_DIR)
			ip->i_nlink++;

	}	/* end for (percorrendo as entradas) */

}	/* end cd_get_nlink_dir */

/*
 ****************************************************************
 *	Obt�m o INO do diret�rio pai				*
 ****************************************************************
 */
void
cd_get_par_ino (INODE *ip)
{
	SB		*unisp = ip->i_sb;
	dev_t		dev = ip->i_dev;
	CDSB		*sp = unisp->sb_ptr;
	const CDDIR	*dp, *end_dp;
	daddr_t		blkno, end_blkno;
	BHEAD		*bp;
	int		len;
	int		par_first_block, grand_size, grand_first_block;

	/*
	 *	Se for a RAIZ, ...
	 */
	if (ip->i_ino == unisp->sb_root_ino)
		{ ip->i_par_ino = unisp->sb_root_ino; return; }

	/*
	 *	L� o primeiro bloco do diret�rio dado
	 */
	bp = bread (ip->i_dev, ISOBL_TO_BL (ip->i_first_block), 0);

	dp = bp->b_addr; dp = (CDDIR *)((int)dp + dp->d_len);	/* Segunda entrada */

	par_first_block = 0;

	if (sp->s_rock_ridge)
		par_first_block = cd_rr_fields_analysis (dp, unisp, RR_PARENT_MISSION, NOVOID);

	if (par_first_block == 0)
		par_first_block = ISO_GET_LONG (dp->d_first_block) + dp->d_ext_attr_len;

   	block_put (bp);

	if (par_first_block == sp->s_root_first_block)
		{ ip->i_par_ino = unisp->sb_root_ino; return; }

	/*
	 *	L� o primeiro bloco do diret�rio pai
	 */
	bp = bread (ip->i_dev, ISOBL_TO_BL (par_first_block), 0);

	dp = bp->b_addr; dp = (CDDIR *)((int)dp + dp->d_len);	/* Segunda entrada */

	grand_first_block = ISO_GET_LONG (dp->d_first_block) + dp->d_ext_attr_len;
	grand_size	  = ISO_GET_LONG (dp->d_size);

   	block_put (bp);

	/*
	 *	Obt�m os blocos inicial e final do diret�rio av�
	 */
	blkno = grand_first_block; end_blkno = blkno + BYTOISOBL (grand_size);

	blkno--;	/* � Incrementado antes do primeiro uso */

	bp = NOBHEAD;

	/*
	 *	Malha Principal
	 */
	for (dp = end_dp = NOCDDIR; /* abaixo */; dp = (CDDIR *)((int)dp + len))
	{
		if (dp >= end_dp)
		{
			/* L� um bloco de diret�rio */

			if (bp != NOBHEAD)
				{ block_put (bp); bp = NOBHEAD; }

			if (++blkno >= end_blkno)
				return;

			if (blkno < end_blkno - 1)
				bp = breada (dev, ISOBL_TO_BL (blkno), ISOBL_TO_BL (blkno + 1), 0);
			else
				bp = bread (dev, ISOBL_TO_BL (blkno), 0);

			dp = bp->b_addr; end_dp = (CDDIR *)(bp->b_addr + ISO_BLSZ);

		}

		/* Usa as entradas deste bloco */

		if ((len = dp->d_len) == 0)
			{ dp = end_dp; continue; }

		/* Pula "." e ".." */

		if (dp->d_name_len == 1 && dp->d_name[0] <= 1)
			continue;

		if (ISO_GET_LONG (dp->d_first_block) + dp->d_ext_attr_len != par_first_block)
			continue;

		ip->i_par_ino = (blkno << ISO_BLSHIFT) + ((void *)dp - bp->b_addr);

		block_put (bp);

		return;

	}	/* end for (percorrendo as entradas) */

}	/* end cd_get_par_ino */

/*
 ****************************************************************
 *   Verifica se o nome procurado confere com o do diret�rio	*
 ****************************************************************
 */
int
cd_name_match (const DIRENT *dep, const CDDIR *dp, const SB *unisp)
{
	const CDSB	*sp = unisp->sb_ptr;
	char		c, cd_c;
	int		i, len;
	char		*dst;

	/*
	 *	Se for "Rock Ridge", ...
	 */
	if (sp->s_rock_ridge)
	{
		dst = alloca (sizeof (dep->d_name));

		len = cd_rr_fields_analysis (dp, unisp, RR_NAME_MISSION, dst);

		if (len != 0)
		{
			/* Se for um diret�rio relocado, len == -1 */

			if (dep->d_namlen != len)
				return (0);

			if (unisp->sb_mntent.me_flags & SB_CASE)
				return (memeq (dep->d_name, dst, len));
			else
				return (memnocaseeq (dep->d_name, dst, len));
		}

	}	/* end if (rock ridge) */

	/*
	 *	Se for "joliet", ...
	 */
	len = dp->d_name_len;

	if (sp->s_joliet_level)
	{
		len >>= 1;

		dst = alloca (len + 1);

		big_unicode2iso (dst, dp->d_name, len);

		if (dst[len-2] == ';')
			{ len -= 2; dst[len] = '\0'; }

		if (dep->d_namlen != len)
			return (0);

		if (unisp->sb_mntent.me_flags & SB_CASE)
			return (memeq (dep->d_name, dst, len));
		else
			return (memnocaseeq (dep->d_name, dst, len));
	}

	/*
	 *	Os demais
	 */
	for (i = 0; /* abaixo */; i++)
	{
		c = dep->d_name[i];

		if (i >= len)
			return (c == '\0');

		cd_c = dp->d_name[i];

		if (c == '\0')
		{
			if (cd_c == ';')
				return (1);

			if (cd_c == '.' && dp->d_name[i+1] == ';')
				return (1);

			return (0);
		}

		if (cd_c == c)
			continue;

		if (cd_c == '_' && c == '.')
			continue;

		if (unisp->sb_mntent.me_flags & SB_CASE)
			return (0);

		if (lowertoupper[cd_c] != lowertoupper[c])
			return (0);
	}

}	/* end cd_name_match */

/*
 ****************************************************************
 *	Converte decentemente um nome				*
 ****************************************************************
 */
int
cd_name_conv (char *dst, const CDDIR *dp, const SB *unisp)
{
	const CDSB	*sp = unisp->sb_ptr;
	char		c, *cp;
	const char	*src;
	int		len;

	/*
	 *	Se for "Rock Ridge", ...
	 */
	if (sp->s_rock_ridge)
	{
		len = cd_rr_fields_analysis (dp, unisp, RR_NAME_MISSION, dst);

		/* Se for um diret�rio relocado, len == -1 */

		if (len != 0)
			return (len);

	}	/* end if (rock ridge) */

	/*
	 *	Se for "joliet", ...
	 */
	src = dp->d_name; len = dp->d_name_len;

	if (sp->s_joliet_level)
	{
		len >>= 1;

		big_unicode2iso (dst, src, len);

		if (dst[len-2] == ';')
			{ len -= 2; dst[len] = '\0'; }

		return (len);
	}

	/*
	 *	Os demais
	 */
	cp = dst;

	while (len-- > 0)
	{
		if ((c = *src++) == ';')
		{
			if (cp[-1] == '.')
				cp--;
			break;
		}

		*cp++ = c;
#if (0)	/*******************************************************/
		*cp++ = uppertolower[c];
#endif	/*******************************************************/
	}

	*cp = '\0';

	return (cp - dst);

}	/* end cd_name_conv */
