/*
 ****************************************************************
 *								*
 *			nfs2s_stat.c				*
 *								*
 *	Servidor NFS Vers�o 2: Manipula��o de estados		*
 *								*
 *	Vers�o	4.8.0, de 05.09.05				*
 *		4.8.0, de 05.09.05				*
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
#include "../h/region.h"

#include "../h/mntent.h"
#include "../h/sb.h"
#include "../h/inode.h"
#include "../h/stat.h"
#include "../h/ustat.h"
#include "../h/itnet.h"
#include "../h/nfs.h"
#include "../h/uerror.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Servidor NFS Vers�o 2: Processa o GETATTR		*
 ****************************************************************
 */
void
nfs2_server_getattr (const RPCINFO *info)
{
	const struct arg { FHANDLE file; }		*rp = info->f_area;
	struct reply { RPCPLG prolog; FATTR fattr; }	*reply;
	ITBLOCK		*bp;
	INODE		*ip;
	UDP_EP		uep;

	/*
	 *	Em primeiro lugar, localiza o INODE
	 */
	if ((ip = nfs2_get_handle_inode (&rp->file)) == NOINODE)
		{ nfs_send_status_datagram (info, NFS_ERRNO); return; }

	/*
	 *	Obt�m um ITBLOCK e prepara o RPC com os atributos pedidos
	 */
	bp = nfs_setup_server_datagram_prolog (info, &uep); reply = bp->it_u_area;

	nfs2_get_fattr_attribute (&reply->fattr, ip);

	iput (ip);

	/*
	 *	Envia a mensagem atrav�s do protocolo UDP
	 */
   /***	bp->it_u_area  = reply;	***/
	bp->it_u_count = sizeof (struct reply);

	send_udp_datagram (&uep, bp);

}	/* end nfs2_server_getattr */

/*
 ****************************************************************
 *	Servidor NFS Vers�o 2: Processa o SETATTR		*
 ****************************************************************
 */
void
nfs2_server_setattr (const RPCINFO *info)
{
	const struct arg { FHANDLE file; SATTR sattr; }	*rp = info->f_area;
	struct reply { RPCPLG prolog; FATTR fattr; }	*reply;
	ITBLOCK			*bp;
	INODE			*ip;
	UDP_EP			uep;

	/*
	 *	Em primeiro lugar, localiza o INODE
	 */
	if ((ip = nfs2_get_handle_inode (&rp->file)) == NOINODE)
		{ nfs_send_status_datagram (info, NFS_ERRNO); return; }

	/*
	 *	Em segundo, obt�m a prote��o desejada e a altera
	 */
	if (nfs_owner (ip, info) < 0)
		{ iput (ip); nfs_send_status_datagram (info, NFS_ERRNO); return; }

	if (ip->i_sb->sb_mntent.me_flags & SB_RONLY)
		{ iput (ip); nfs_send_status_datagram (info, EROFS); return; }

	xuntext (ip, 0 /* no lock */);

	if (ip->i_flags & ITEXT)
		{ iput (ip); nfs_send_status_datagram (info, ETXTBSY); return; }

	/*
	 *	Altera os atributos
	 */
	nfs2_put_sattr_attribute (&rp->sattr, ip);

	/*
	 *	Obt�m um ITBLOCK e prepara o RPC com os atributos pedidos
	 */
	bp = nfs_setup_server_datagram_prolog (info, &uep); reply = bp->it_u_area;

	nfs2_get_fattr_attribute (&reply->fattr, ip);

	iput (ip);

	/*
	 *	Envia a mensagem atrav�s do protocolo UDP
	 */
   /***	bp->it_u_area  = reply;	***/
	bp->it_u_count = sizeof (struct reply);

	send_udp_datagram (&uep, bp);

}	/* end nfs2_server_setattr */

/*
 ****************************************************************
 *	Servidor NFS Vers�o 2: Processa o STATFS		*
 ****************************************************************
 */
void
nfs2_server_statfs (const RPCINFO *info)
{
	const struct arg { FHANDLE file; }		*rp = info->f_area;
	struct reply { RPCPLG prolog; STATFS statfs; }	*reply;
	ITBLOCK		*bp;
	SB		*unisp;
	int		code;
	USTAT		us;
	UDP_EP		uep;

	/*
	 *	Procura o Dispositivo na lista de SB's
	 */
	if ((unisp = sbget (rp->file.h_dev)) == NOSB)
		{ nfs_send_status_datagram (info, ENODEV); return; }

	code = unisp->sb_code;

	sbput (unisp);

	(*fstab[code].fs_ustat) (unisp, &us);

	/*
	 *	Obt�m um ITBLOCK e prepara o RPC com o FSTAT
	 */
	bp = nfs_setup_server_datagram_prolog (info, &uep); reply = bp->it_u_area;

	/* Coloca o FSTAT */

	reply->statfs.fs_tsize  = ENDIAN_IMMED (MAX_NFS2_DATA);
	reply->statfs.fs_bsize  = ENDIAN_LONG  (us.f_bsize);
	reply->statfs.fs_blocks = ENDIAN_LONG  (us.f_fsize);
	reply->statfs.fs_bfree  = ENDIAN_LONG  (us.f_tfree);
	reply->statfs.fs_bavail = ENDIAN_LONG  (us.f_tfree);

	/*
	 *	Envia a mensagem atrav�s do protocolo UDP
	 */
   /***	bp->it_u_area  = reply;	***/
	bp->it_u_count = sizeof (struct reply);

	send_udp_datagram (&uep, bp);

}	/* end nfs2_server_statfs */
