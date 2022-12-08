/*
 ****************************************************************
 *								*
 *			tty.c					*
 *								*
 *	Driver indireto para o pr�prio terminal			*
 *								*
 *	Vers�o	1.0.00, de 22.01.86				*
 *		3.0.27, de 07.01.98				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/kfile.h"
#include "../h/inode.h"
#include "../h/tty.h"
#include "../h/iotab.h"
#include "../h/uerror.h"
#include "../h/signal.h"
#include "../h/uproc.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Fun��o de "open"					*
 ****************************************************************
 */
void
teopen (dev_t dev, OFLAG oflag)
{
	if (u.u_tty == NOTTY)
		{ u.u_error = ENXIO; return; }

	(*ciotab[MAJOR (u.u_ttydev)].w_open) (u.u_ttydev, oflag);

}	/* end teopen */

/*
 ****************************************************************
 *	Fun��o de "close"					*
 ****************************************************************
 */
void
teclose (dev_t dev, int flag)
{
	(*ciotab[MAJOR (u.u_ttydev)].w_close) (u.u_ttydev, 1);

}	/* end teclose */

/*
 ****************************************************************
 *	Fun��o de leitura					*
 ****************************************************************
 */
void
teread (IOREQ *iop)
{
	iop->io_dev = u.u_ttydev;

	(*ciotab[MAJOR (u.u_ttydev)].w_read) (iop);

}	/* end teread */

/*
 ****************************************************************
 *	Fun��o de escrita					*
 ****************************************************************
 */
void
tewrite (IOREQ *iop)
{
	iop->io_dev = u.u_ttydev;

	(*ciotab[MAJOR (u.u_ttydev)].w_write) (iop);

}	/* end tewrite */

/*
 ****************************************************************
 *	Fun��o de controle					*
 ****************************************************************
 */
int
tectl (dev_t dev, int cmd, int arg, int flag)
{
	return (*ciotab[MAJOR (u.u_ttydev)].w_ioctl) (u.u_ttydev, cmd, arg, flag);

}	/* end tectl */
