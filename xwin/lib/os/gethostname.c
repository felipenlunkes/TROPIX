/*
 ****************************************************************
 *								*
 *			gethostname.c				*
 *								*
 *	Obt�m o nome da m�quina					*
 *								*
 *	Vers�o	1.0.0, de 18.03.97				*
 *		1.0.2, de 29.04.98				*
 *								*
 *	M�dulo: xc/lib/aux					*
 *		X Windows - Bibliotecas				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright (c) 1998 TROPIX Technologies Ltd.	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/syscall.h>
#include <sys/itnet.h>

#include <string.h>
#include <fcntl.h>
#include <xti.h>

static const char	tcpdevname[] =	"/dev/itntcp";
static unsigned long	myipaddr;
static int		mynamelen;
static char		myname[NETNM_SZ];

/*
 ****************************************************************
 *	Obt�m o nome da m�quina					*
 ****************************************************************
 */
int
gethostname (char *buf, int maxlen)
{
	int	fd;

	if (myipaddr == 0)
	{	/*
		 *	Obt�m o endere�o IP da m�quina.
		 *	Guarda para que, futuramente, n�o precise obter de novo.
		 */
		if ((fd = t_open (tcpdevname, O_RDWR, (T_INFO *)NULL)) < 0)
			return (-1);

		myipaddr = t_node_to_addr (fd, NULL, NULL);
		strcpy (myname, t_addr_to_node (fd, myipaddr));
		mynamelen = strlen (myname) + 1;

		t_close (fd);
	}

	/*
	 *	Copia para o buffer dado.
	 */
	if (maxlen >= mynamelen)
	{
		memmove (buf, myname, mynamelen);
		return (mynamelen - 1);
	}

	maxlen--;
	memmove (buf, myname, maxlen);
	buf[maxlen] = '\0';

	return (maxlen);

}	/* end gethostname */
