/*
 ****************************************************************
 *								*
 *			ext2read.c				*
 *								*
 *	Leitura e escrita de arquivos				*
 *								*
 *	Vers�o	4.4.0, de 23.10.02				*
 *		4.7.0, de 11.12.04				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/iotab.h"
#include "../h/kfile.h"
#include "../h/inode.h"
#include "../h/bhead.h"
#include "../h/mntent.h"
#include "../h/sb.h"
#include "../h/ext2.h"
#include "../h/uerror.h"
#include "../h/signal.h"
#include "../h/uproc.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Open de INODEs						*
 ****************************************************************
 */
void
ext2_open (INODE *ip, int oflag)
{
	/*
	 *	Recebe e devolve o INODE locked
	 */
	if (ip->i_flags & ILOCK || (oflag & O_LOCK) && ip->i_count != 1)
		{ u.u_error = EBUSY; return; }

	if (oflag & O_LOCK)
		ip->i_flags |= ILOCK;

}	/* end ext2_open */

/*
 ****************************************************************
 *	Close de INODEs						*
 ****************************************************************
 */
void
ext2_close (INODE *ip)
{
	/*
	 *	Recebe o INODE locked e devolve free
	 */
	if (ip->i_count == 1)
	{
		/* O "close" final do INODE */

		if ((ip->i_mode & IFMT) == IFIFO)
			ip->i_mode |= IREAD|IWRITE;

		ip->i_flags &= ~ILOCK;
	}

	iput (ip);

}	/* end ext2_close */

/*
 ****************************************************************
 *	Leitura de um INODE					*
 ****************************************************************
 */
void
ext2_read (IOREQ *iop)
{
	INODE		*ip = iop->io_ip;
	EXT2SB		*ext2sp = ip->i_sb->sb_ptr;
	dev_t		dev = ip->i_dev;
	BHEAD		*bp;
	daddr_t		lbn, pbn, rabn;
	off_t		range;
	int		offset, count;

	/*
	 *	Prepara algumas vari�veis
	 */
	if (ip->i_sb->sb_mntent.me_flags & SB_ATIME)
		{ ip->i_atime = time; inode_dirty_inc (ip); }

	/*
	 *	Trata-se de arquivo regular ou diret�rio
	 */
	do
	{
		lbn	= iop->io_offset_low >> ext2sp->s_BLOCK_SHIFT;
		offset	= iop->io_offset_low &  ext2sp->s_BLOCK_MASK;
		count	= MIN (ext2sp->s_BLOCK_SZ - offset, iop->io_count);

		/*
		 *	Calcula os blocos f�sicos e "readahead"
		 */
		if ((range = ip->i_size - iop->io_offset_low) <= 0)
			return;

		if (count > range)
			count = range;

		pbn = ext2_block_map (ip, lbn, B_READ, &rabn);

		if (u.u_error)
			return;

		/*
		 *	Le um bloco
		 */
		if (pbn < 0)			/* BLOCO dentro do arquivo, mas nunca foi escrito */
		{
			bp = block_free_get (ext2sp->s_BLOCK_SZ);
			memclr (bp->b_addr, ext2sp->s_BLOCK_SZ);
			bp->b_residual = 0;
		}
		elif (ip->i_lastr + 1 == lbn)	/* A leitura est� sendo feita sequencialmente */
		{
			bp = breada (dev, EXT2_BLOCKtoBL (pbn), EXT2_BLOCKtoBL (rabn), 0);
#ifdef	MSG
			if (CSWT (4))
				printf ("%g: Readahead: dev = %v, bn = %d, ra = %d\n", dev, pbn, rabn);
#endif	MSG
		}
		else				/* Leitura normal */
		{
			bp = bread (dev, EXT2_BLOCKtoBL (pbn), 0);
		}

#ifdef	MSG
		if (CSWT (13))
		{
			if (bp->b_residual != 0)
				printf ("%g: Residual = %d\n", bp->b_residual);
		}
#endif	MSG

		/*
		 *	Move a Informa��o para a area desejada
		 */
		ip->i_lastr = lbn;

		count = MIN (count, ext2sp->s_BLOCK_SZ - bp->b_residual);

		if (unimove (iop->io_area, bp->b_addr + offset, count, iop->io_cpflag) < 0)
			{ u.u_error = EFAULT; block_put (bp); return; }

		iop->io_area       += count;
		iop->io_offset_low += count;
		iop->io_count      -= count;

		block_put (bp);
	}
	while (u.u_error == NOERR && iop->io_count > 0 && count > 0);

}	/* end ext2_read */

/*
 ****************************************************************
 *	Escrita de um INODE					*
 ****************************************************************
 */
void
ext2_write (IOREQ *iop)
{
	INODE		*ip = iop->io_ip;
	EXT2SB		*ext2sp = ip->i_sb->sb_ptr;
	dev_t		dev = ip->i_dev;
	BHEAD		*bp;
	daddr_t		lbn, pbn, rabn;
	int		offset, count;

	/*
	 *	Atualiza o tempo de modifica��o do INODE
	 */
	ip->i_mtime = time; inode_dirty_inc (ip);

	/*
	 *	Trata-se de arquivo regular ou diret�rio
	 */
	do
	{
		lbn	= iop->io_offset_low >> ext2sp->s_BLOCK_SHIFT;
		offset	= iop->io_offset_low &  ext2sp->s_BLOCK_MASK;
		count	= MIN (ext2sp->s_BLOCK_SZ - offset, iop->io_count);

		/*
		 *	Calcula o Endere�o F�sico
		 *	Retorna em caso de BLOCO inv�lido
		 */
		if ((pbn = ext2_block_map (ip, lbn, B_WRITE, &rabn)) <= NODADDR)
			return;

		/*
		 *	Obt�m o Bloco para escrever
		 */
		if   (count == BL4SZ) /* && offset == 0 */
			bp = block_get (dev, EXT2_BLOCKtoBL (pbn), 0);
		elif (rabn == (daddr_t)-1)      /* Bloco acabou de ser alocado */
                        { bp = bread (dev, EXT2_BLOCKtoBL (pbn), 0); memclr (bp->b_addr, ext2sp->s_BLOCK_SZ); }
		else
			bp = bread (dev, EXT2_BLOCKtoBL (pbn), 0);

		/*
		 *	Coloca a informa��o no buffer e o escreve
		 */
		if (unimove (bp->b_addr + offset, iop->io_area, count, iop->io_cpflag) < 0)
			{ u.u_error = EFAULT; block_put (bp); return; }

		iop->io_area       += count;
		iop->io_offset_low += count;
		iop->io_count      -= count;

		if (u.u_error != NOERR)
			block_put (bp);
		else
			bdwrite (bp);

		/*
		 *	Atualiza o tamanho do arquivo
		 */
		if (ip->i_size < iop->io_offset_low)
			ip->i_size = iop->io_offset_low;

	}
	while (u.u_error == NOERR && iop->io_count > 0);

}	/* end ext2_write */

/*
 ****************************************************************
 *	Rotina de "read" de um elo simb�lico 			*
 ****************************************************************
 */
int
ext2_read_symlink (IOREQ *iop)
{
	INODE		*ip = iop->io_ip;
	EXT2SB		*ext2sp;
	BHEAD		*bp;
	int		count;
	char		nulo[4];

	/*
	 *	Prepara algumas vari�veis
	 *
	 *	Repare que "ip->i_size" N�O inclui o NULO
	 */
	if (ip->i_sb->sb_mntent.me_flags & SB_ATIME)
		{ ip->i_atime = time; inode_dirty_inc (ip); }

	count = MIN (iop->io_count, ip->i_size);

	/*
	 *	Verifica se est� nos endere�os ou em um bloco
	 */
	if (ip->i_size < EXT2_NADDR * sizeof (daddr_t))
	{
		/* Est� nos endere�os */

		if (unimove (iop->io_area, ip->i_addr, count, iop->io_cpflag) < 0)
			u.u_error = EFAULT;
	}
	else
	{
		/* Est� em um bloco */

		ext2sp = ip->i_sb->sb_ptr;

		bp = bread (ip->i_dev, EXT2_BLOCKtoBL (ip->i_addr[0]), 0);

		if (bp->b_flags & B_ERROR)
			{ block_put (bp); return (-1); }

		if (unimove (iop->io_area, bp->b_addr, count, iop->io_cpflag) < 0)
			u.u_error = EFAULT;

		block_put (bp);
	}

	/*
	 *	Ep�logo
	 */
	if (iop->io_count > count)
	{
		nulo[0] = '\0';

		if (unimove (iop->io_area + count, nulo, 1, iop->io_cpflag) < 0)
			u.u_error = EFAULT;
	}

	return (count);

}	/* end ext2_read_symlink */

/*
 ****************************************************************
 *	Rotina de "write" de um elo simb�lico 			*
 ****************************************************************
 */
INODE *
ext2_write_symlink (const char *old_path, int old_count, IOREQ *iop, DIRENT *dep)
{
	EXT2SB		*ext2sp = iop->io_ip->i_sb->sb_ptr;
	INODE		*ip;

	/*
	 *	Verifica o tamanho do conte�do: desconta o NULO
	 */
	if (--old_count > ext2sp->s_BLOCK_SZ)
		{ iput (iop->io_ip); u.u_error = E2BIG; return (NOINODE); }

	/*
	 *	Cria o arquivo
	 */
	if ((ip = ext2_make_inode (iop, dep, IFLNK)) == NOINODE)
		return (NOINODE);

	ip->i_mode |= 0777;	/* T�das as permiss�es */

	/*
	 *	Verifica se h� espa�o nos endere�os do INODE
	 */
	if (old_count <= EXT2_NADDR * sizeof (daddr_t))		/* H� espa�o */
	{
		if (unimove (ip->i_addr, old_path, old_count, US) < 0)
			{ u.u_error = EFAULT; iput (ip); return (NOINODE); }

		ip->i_size = old_count;
	}
	else							/* N�O h� espa�o */
	{
		iop->io_ip	   = ip;
		iop->io_area	   = (char *)old_path;
		iop->io_count	   = old_count;
		iop->io_offset_low = 0;
		iop->io_cpflag	   = US;

		ext2_write (iop);
	}

	return (ip);

}	/* end ext2_write_symlink */
