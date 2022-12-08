/*
 ****************************************************************
 *								*
 *			rpc.c					*
 *								*
 *	Fun��es relacionadas com o PORT MAPPER PROTOCOL		*
 *								*
 *	Vers�o	4.8.0, de 04.08.05				*
 *		4.8.0, de 04.08.05				*
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
#include "../h/scb.h"
#include "../h/sync.h"
#include "../h/region.h"

#include <stdarg.h>

#include "../h/itnet.h"
#include "../h/mntent.h"
#include "../h/sb.h"
#include "../h/nfs.h"
#include "../h/uerror.h"
#include "../h/signal.h"
#include "../h/uproc.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ******	Vari�veis da fila de pedidos para RPC/NFS ***************
 */
entry NFSINQ		*nfs_inq, *end_nfs_inq;	/* A tabela */
entry NFSINQ		*nfs_inq_ptr;		/* A pr�xima entrada a usar */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		nfs_wait_for_datagram (NFSINQ *qp);
void		nfs_receive_call_rpc_datagram (RPCINFO *info, const int *ptr);
void		nfs_receive_reply_rpc_datagram (ITBLOCK *bp, RPCINFO *info, const int *ptr);
const int	*nfs_get_auth (RPCINFO *info, const int *ptr);

/*
 ****************************************************************
 *	Acorda o NFS_DAEMON					*
 ****************************************************************
 */
void
wake_up_nfs_daemon (ITBLOCK *bp)
{
	NFSINQ		*qp = nfs_inq_ptr;

	/*
	 *	Acorda sempre o servidor seguinte
	 */
	if (++qp >= end_nfs_inq)
		qp = nfs_inq;

	nfs_inq_ptr = qp;

	SPINLOCK (&qp->nfs_inq_lock);

	if (qp->nfs_inq_first == NOITBLOCK)
		qp->nfs_inq_first = bp;
	else
		qp->nfs_inq_last->it_nfs_forw = bp;

	qp->nfs_inq_last = bp; bp->it_nfs_forw = NOITBLOCK;

	EVENTDONE (&qp->nfs_inq_nempty);

	SPINFREE (&qp->nfs_inq_lock);

}	/* end wake_up_nfs_daemon */

/*
 ****************************************************************
 *	NFS_DAEMON - Processa a fila de entrada RPC/NFS		*
 ****************************************************************
 */
void
execute_nfs_daemon (void)
{
	int		i;
	NFSINQ		*qp;

	/*
	 *	N�o usa endere�os virtuais de usu�rio
	 */
	u.u_no_user_mmu = 1; strcpy (u.u_pgname, "nfs_daemon_0"); set_pgname (u.u_pgname);

	/*
	 *	Obt�m uma �rea para a tabela de servidores
	 */
	if ((nfs_inq = malloc_byte (scb.y_n_nfs_daemon * sizeof (NFSINQ))) == NONFSINQ)
		panic ("N�o consegui mem�ria para a tabela de servidores NFS");

	end_nfs_inq = nfs_inq + scb.y_n_nfs_daemon; nfs_inq_ptr = nfs_inq - 1;

	memclr (nfs_inq, scb.y_n_nfs_daemon * sizeof (NFSINQ));

   /*** nfs_inq[0].p_nfs_index = 0; ***/

	/*
	 *	Cria os processos dos "daemons" (um j� temos)
	 */
	for (i = 1, qp = nfs_inq + 1; i < scb.y_n_nfs_daemon; i++, qp++)
	{
		qp->nfs_index = i;

		if (newproc (THREAD) == 0)
		{
			snprintf (u.u_pgname, sizeof (u.u_pgname), "nfs_daemon_%d", i);

			set_pgname (u.u_pgname);

			nfs_wait_for_datagram (qp);

			/****** sem retorno *****/
		}
	}

	/*
	 *	Este tamb�m trata de datagramas
	 */
	nfs_wait_for_datagram (nfs_inq);

	/****** sem retorno *****/

}	/* end execute_nfs_daemon */

/*
 ****************************************************************
 *	Espera a chegada de um datagrama			*
 ****************************************************************
 */
void
nfs_wait_for_datagram (NFSINQ *qp)
{
	ITBLOCK		*bp;

	for (EVER)
	{
		/*
		 *	� poss�vel, em certos casos, vir um alarme falso!
		 */
		for (EVER)
		{
			EVENTWAIT (&qp->nfs_inq_nempty, PITNETIN);

			SPINLOCK (&qp->nfs_inq_lock);

			if ((bp = qp->nfs_inq_first) != NOITBLOCK)
				break;

			EVENTCLEAR (&qp->nfs_inq_nempty);

			SPINFREE (&qp->nfs_inq_lock);
		}

		/*
		 *	Achou um pedido; retira da fila
		 */
		if ((qp->nfs_inq_first = bp->it_nfs_forw) == NOITBLOCK)
		{
			qp->nfs_inq_last = NOITBLOCK;
			EVENTCLEAR (&qp->nfs_inq_nempty);
		}

		SPINFREE (&qp->nfs_inq_lock);

		if (nfs_receive_rpc_datagram (bp))
			put_it_block (bp);

	}	/* end for (EVER) */

}	/* end nfs_wait_for_datagram */

/*
 ****************************************************************
 *	Recebe um datagrama RPC					*
 ****************************************************************
 */
int
nfs_receive_rpc_datagram (ITBLOCK *bp)
{
	const UT_H	*uhp = bp->it_u_area;
	int		code;
	const int	*ptr;
	RPCINFO		info;

	/*
	 *	Retorna 1 se deve liberar "bp"
	 *
	 *	Informa��es globais
	 */
	info.f_peer_addr = ENDIAN_LONG  (uhp->ph.ph_src_addr);
	info.f_peer_port = ENDIAN_SHORT (uhp->uh.uh_src_port);
	info.f_area	 = bp->it_area;
	info.f_end_area	 = bp->it_area + bp->it_count;

	/*
	 *
	 *	Guarda a identifica��o do pedido
	 */
	u.u_error = NOERR; ptr = info.f_area; info.f_xid = *ptr++;

	/*
	 *	Verifica se � um pedido/resposta
	 */
	switch (code = ENDIAN_LONG (*ptr++))
	{
	    case RPC_CALL:
		nfs_receive_call_rpc_datagram (&info, ptr);
		return (1);

	    case RPC_REPLY:
		nfs_receive_reply_rpc_datagram (bp, &info, ptr);
		return (0);

	    default:
		printf ("%g: Ignorando datagrama de c�digo %d\n", code);
		return (1);
	}

}	/* end nfs_receive_rpc_datagram */

/*
 ****************************************************************
 *	Recebe um datagrama de chamada RPC			*
 ****************************************************************
 */
void
nfs_receive_call_rpc_datagram (RPCINFO *info, const int *ptr)
{
	int		prog;

	/*
	 *	Verifica se a vers�o do RPC � a correta
	 */
	if (ENDIAN_LONG (*ptr++) != RPC_VERS)
	{
		nfs_send_var_rpc_datagram
		(
			info, 5, RPC_REPLY, RPC_MSG_DENIED, RPC_MISMATCH, RPC_VERS, RPC_VERS
		);
		return;
	}

	/*
	 *	Guarda o n�mero do programa, vers�o e fun��o
	 */
	prog		  = ENDIAN_LONG (*ptr++);
	info->f_vers	  = ENDIAN_LONG (*ptr++);
	info->f_proc	  = ENDIAN_LONG (*ptr++);
	info->f_uid	  = SQUASH_ID;
	info->f_gid	  = SQUASH_ID;

	strcpy (info->f_client_nm, "???");

	/*
	 *	Analisa as duas autentica��es
	 */
	ptr		= nfs_get_auth (info, ptr);
	info->f_area	= nfs_get_auth (info, ptr);

	/*
	 *	Verifica o n�mero do programa que se deseja executar
	 */
	switch (prog)
	{
	    case PMAP_PROG:
		nfs_receive_pmap_datagram (info);
		break;

	    case MOUNTPROG:
		nfs2_receive_mntpgm_datagram (info);
		break;

	    case NFS_PROG:
		nfs2_receive_nfs_datagram (info);
		break;

	    default:
		printf ("%g: Recebi um RPC para o programa %d\n", prog);
		nfs_send_var_rpc_datagram
		(
			info, 5, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0, PROG_UNAVAIL
		);
		break;
	}

}	/* end nfs_receive_call_rpc_datagram */

/*
 ****************************************************************
 *	Recebe um pedido de porta (PORT MAPPER)			*
 ****************************************************************
 */
void
nfs_receive_pmap_datagram (const RPCINFO *info)
{
	const struct arg { int prog; int vers; int prot; int port; }	*rp = info->f_area;

	/*
	 *	Verifica se a vers�o do PORT MAPPER � a correta
	 */
	if (info->f_vers != PMAP_VERS)
	{
		printf ("%g: Recebi um PMAP com vers�o %d errada\n", info->f_vers);
		nfs_send_var_rpc_datagram
		(
			info, 7, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0,
			PROG_MISMATCH, PMAP_VERS, PMAP_VERS
		);
		return;
	}

	/*
	 *	Analisa a fun��o pedida ao PORT MAPPER
	 */
	switch (info->f_proc)
	{
	    case PMAPPROC_GETPORT:
		break;

	    case PMAPPROC_NULL:
	    case PMAPPROC_SET:
	    case PMAPPROC_UNSET:
	    case PMAPPROC_DUMP:
	    default:
		printf ("%g: pedido PMAP %d AINDA N�O IMPLEMENTADO\n", info->f_proc);
		nfs_send_var_rpc_datagram
		(
			info, 5, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0, PROC_UNAVAIL
		);
		return;
	}

	/*
	 *	Retira (finalmente) o pedido e procura na tabela
	 */
	switch (ENDIAN_LONG (rp->prog))
	{
	    case MOUNTPROG:
		if (ENDIAN_LONG (rp->vers) == MOUNTVERS && ENDIAN_LONG (rp->prot) == UDP_PROTO)
		{
			nfs_send_var_rpc_datagram
			(
				info, 6, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0, SUCCESS, RPC_PORT
			);
			return;
		}
		break;

	    case NFS_PROG:
		if (ENDIAN_LONG (rp->vers) == NFS_VERS && ENDIAN_LONG (rp->prot) == UDP_PROTO)
		{
			nfs_send_var_rpc_datagram
			(
				info, 6, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0, SUCCESS, RPC_PORT
			);
			return;
		}
		break;
	}

	/*
	 *	Se n�o conhece, ...
	 */
	printf
	(	"%g: Recebendo pedido PMAP para programa %d, vers�o %d, proto %d\n",
		ENDIAN_LONG (rp->prog), ENDIAN_LONG (rp->vers), ENDIAN_LONG (rp->prot)
	);

	nfs_send_var_rpc_datagram
	(
		info, 6, RPC_REPLY, RPC_MSG_ACCEPTED, AUTH_NULL, 0, SUCCESS, 0
	);

}	/* end nfs_receive_pmap_datagram */

/*
 ****************************************************************
 *	Recebe um datagrama de resposta RPC			*
 ****************************************************************
 */
void
nfs_receive_reply_rpc_datagram (ITBLOCK *bp, RPCINFO *info, const int *ptr)
{
	int		index, reply_stat, accept_stat;
	const char	*msg;
	const UPROCV	*uvp;
	const NFSSB	*nfssp;
	UPROC		*up;

	/*
	 *	Verifica se deve fazer de conta que o datagrama foi perdido
	 */
#undef	LOSE
#ifdef	LOSE
	if ((hz & 0x1E) == 0x10)
	{
		printf ("%g: Perdi um datagrama\n");
		put_it_block (bp); return;
	}
#endif	LOSE

	/*
	 *	Obt�m a UPROC do processo esperando
	 */
	if ((index = info->f_xid & XID_PROC_MASK) >= scb.y_nproc)
	{
		printf ("%g: Resposta NFS com �ndice %d do xid %P inv�lido\n", index, info->f_xid);
		put_it_block (bp); return;
	}

	uvp = &scb.y_uproc[index]; up = uvp->u_uproc;

	if (up->u_nfs.nfs_xid != info->f_xid)
	{
		printf ("%g: N�O localizei resposta NFS com xid %P (:: %P)\n", info->f_xid, up->u_nfs.nfs_xid);
		put_it_block (bp); return;
	}

	/*
	 *	Verifica se entrementes deu "timeout"
	 */
	if (TAS (&up->u_nfs.nfs_lock) < 0)
		{ put_it_block (bp); return; }

	nfssp = up->u_nfs.nfs_sp;

	/*
	 *	Vamos ver se a mensagem foi aceita pelo RPC do servidor
	 */
	if ((reply_stat = *ptr++) != RPC_MSG_ACCEPTED)
	{
		switch (*ptr++)
		{
		    case RPC_MISMATCH:
			msg = "RPC_MISMATCH";
			break;

		    case AUTH_ERROR:
			msg = "AUTH_ERROR";
			break;

		    default:
			msg = "???";
			break;
		}

		printf
		(	"%g: A mensagem RPC de xid %P foi recusada por \"%s\" (%s)\n",
			info->f_xid, nfssp->sb_server_nm, msg
		);

		put_it_block (bp);
		up->u_nfs.nfs_error  = ENXIO;
		up->u_nfs.nfs_status = -1;
		EVENTDONE (&up->u_nfs.nfs_event);
		return;
	}

	/*
	 *	Retira a autentica��o
	 */
	ptr = nfs_get_auth (info, ptr);

	/*
	 *	Vamos ver se a mensagem foi aceita pelo programa do servidor
	 */
	if ((accept_stat = *ptr++) != SUCCESS)
	{
		switch (accept_stat)
		{
		    case PROG_UNAVAIL:
			msg = "PROG_UNAVAIL";
			break;

		    case PROG_MISMATCH:
			msg = "PROG_MISMATCH";
			break;

		    case PROC_UNAVAIL:
			msg = "PROC_UNAVAIL";
			break;

		    case GARBAGE_ARGS:
			msg = "GARBAGE_ARGS";
			break;

		    default:
			msg = "???";
			break;
		}
	
		printf
		(	"%g: A mensagem RPC de xid %P foi recusada por \"%s\" (%s)\n",
			info->f_xid, nfssp->sb_server_nm, msg
		);

		put_it_block (bp);
		up->u_nfs.nfs_error  = ENXIO;
		up->u_nfs.nfs_status = -1;
		EVENTDONE (&up->u_nfs.nfs_event);
		return;
	}

	/*
	 *	Agora que a mensagem foi aceita, ...
	 */
	up->u_nfs.nfs_area	= ptr;
	up->u_nfs.nfs_end_area	= info->f_end_area;
	up->u_nfs.nfs_bp	= bp;
	up->u_nfs.nfs_status	= 1;

	EVENTDONE (&up->u_nfs.nfs_event);

}	/* end nfs_receive_reply_rpc_datagram */

/*
 ****************************************************************
 *	Verifica se o cliente deve retransmitir o datagrama	*
 ****************************************************************
 */
void
nfs_retransmit_client_datagram (UPROC *up)
{
	const NFSSB	*nfssp;
	const SB	*sp;

	/*
	 *	Verifica se entrementes recebeu resposta
	 */
	if (TAS (&up->u_nfs.nfs_lock) < 0)
		return;

	if ((nfssp = up->u_nfs.nfs_sp) == NONFSSB)
		{ printf ("%g: Ponteiro para NFSSB NULO\n"); CLEAR (&up->u_nfs.nfs_lock); return; }

	sp = nfssp->sb_sp;

	/*
	 *	Verifica se excedeu o n�mero de retransmiss�es ou retransmite
	 */
	if (sp->sb_mntent.me_flags & SB_HARD || up->u_nfs.nfs_transmitted <= sp->sb_mntent.me_retrans)
	{
		printf
		(	"Retransmitindo para o servidor NFS \"%s\" (%d)\n",
			nfssp->sb_server_nm, up->u_nfs.nfs_transmitted
		);

		up->u_nfs.nfs_status = 0;
	}
	else
	{
		printf ("Retransmiss�es ESGOTADAS para o servidor NFS \"%s\"\n", nfssp->sb_server_nm);

		up->u_nfs.nfs_error = ETIMEOUT; up->u_nfs.nfs_status = -1;
	}

	EVENTDONE (&up->u_nfs.nfs_event);
	return;

}	/* end nfs_retransmit_client_datagram */

/*
 ****************************************************************
 *	Analisa a Autentica��o					*
 ****************************************************************
 */
const int *
nfs_get_auth (RPCINFO *info, const int *ptr)
{
	int		auth;

	/*
	 *	Analisa a Autentica��o
	 */
	switch (auth = ENDIAN_LONG (*ptr++))
	{
	    case AUTH_NULL:
#undef	DEBUG
#ifdef	DEBUG
		printf ("%g: Ignorando autentica��o NULL\n");
#endif	DEBUG
		break;

	    case AUTH_UNIX:
	    {
		int		len, good_len;
		const int	*unix_ptr = ptr;

		if ((good_len = len = ENDIAN_LONG (unix_ptr[2])) > sizeof (info->f_client_nm) - 1)
			good_len = sizeof (info->f_client_nm) - 1;

		memmove (info->f_client_nm, &unix_ptr[3], good_len); info->f_client_nm[good_len] = '\0';

		unix_ptr += 3 + ((len + 3) >> 2);

		info->f_uid = ENDIAN_LONG (unix_ptr[0]);
		info->f_gid = ENDIAN_LONG (unix_ptr[1]);
#ifdef	DEBUG
		{
			int		ngids = ENDIAN_LONG (unix_ptr[2]);

			printf
			(	"%g: node = \"%s\" (%s), uid = %d, gid = %d, ngids = %d\n",
				info->f_client_nm, edit_ipaddr (info->f_peer_addr),
				info->f_uid, info->f_gid, ngids
			);
		}
#endif	DEBUG
		break;
	    }

	    case AUTH_SHORT:
		printf ("%g: Ignorando autentica��o SHORT\n");
		break;

	    case AUTH_DES:
		printf ("%g: Ignorando autentica��o DES\n");
		break;

	    default:
		printf ("%g: Ignorando autentica��o %d desconhecida\n", auth);
		break;
	}

	return (&ptr[1] + (ENDIAN_LONG (ptr[0]) >> 2));

}	/* end nfs_get_auth */

/*
 ****************************************************************
 *	Envia um datagrama RPC de erro				*
 ****************************************************************
 */
void
nfs_send_var_rpc_datagram (const RPCINFO *info, int count, ...)
{
	UDP_EP		uep;
	ITBLOCK		*bp;
	va_list		ap;
	int		*area;

	/*
	 *	Obt�m um ITBLOCK para compor a resposta
	 */
	bp = get_it_block (IT_OUT_DATA);

	area		=
	bp->it_u_area	= (RPCPLG *)(bp->it_frame + RESSZ);	/* >= ETH_H + IP_H + UDP_H */
	bp->it_u_count	= (count + 1) * sizeof (int);

	/*
	 *	Copia o texto da mensagem
	 */
	va_start (ap, count);

	*area++ = info->f_xid;		/* O "xid" */

	while (count-- > 0)
		*area++ = ENDIAN_LONG (va_arg (ap, int));

	va_end (ap);

	/*
	 *	Envia a mensagem atrav�s do protocolo UDP
	 */
	uep.up_snd_addr = info->f_peer_addr;
	uep.up_snd_port = info->f_peer_port;

	uep.up_my_addr  = 0;		/* Calcula o endere�o local */
	uep.up_my_port	= RPC_PORT;

	send_udp_datagram (&uep, bp);

}	/* end nfs_send_var_rpc_datagram */
