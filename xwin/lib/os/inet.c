/*
 ****************************************************************
 *								*
 *			inet.c					*
 *								*
 *	Miscel�nea de fun��es do BSD				*
 *								*
 *	Vers�o	1.0.0, de 04.03.97				*
 *		1.0.1, de 28.03.98				*
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

#include <stdio.h>
#include <xti.h>
#include "../xtrans/Xtrans.h"

/*
 ****************************************************************
 *	Converte um endere�o BIG-IP em nota��o x.x.x.x		*
 ****************************************************************
 */
char *
inet_ntoa (IPADDR addr)
{
	static char	buf[32];
	char		*cp;

	cp = (char *)&addr;
	sprintf (buf, "%d.%d.%d.%d", cp[0], cp[1], cp[2], cp[3]);

	return (buf);

}	/* end inet_ntoa */

struct hostent *
gethostbyname (const char *name)
{
	static struct hostent	h;

	h.h_addrtype = AF_LOCAL;

	return (NULL);
}
