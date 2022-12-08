/*
 ****************************************************************
 *								*
 *			t_addr_to_str.c				*
 *								*
 *	Formata um endere�o INTERNET				*
 *								*
 *	Vers�o	2.3.0, de 31.08.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_addr_to_str					*
 *		libxti 						*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <xti.h>

/*
 ****************************************************************
 *	Formata um endere�o INTERNET				*
 ****************************************************************
 */
char *
t_addr_to_str (long addr)
{
	register char	*cp = (char *)&addr;
	static char	buf[16];

#ifdef	LITTLE_ENDIAN
	sprintf (buf, "%u.%u.%u.%u", cp[3], cp[2], cp[1], cp[0]);
#else
	sprintf (buf, "%u.%u.%u.%u", cp[0], cp[1], cp[2], cp[3]);
#endif	LITTLE_ENDIAN

	return (buf);

}	/* end t_addr_to_str */
