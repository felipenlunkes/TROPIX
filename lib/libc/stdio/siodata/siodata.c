/*
 ****************************************************************
 *								*
 *			siodata.c				*
 *								*
 *	Inicializa��o da Tabela FILE				*
 *								*
 *	Vers�o	1.0.0, de 14.11.86				*
 *		4.4.0, de 02.11.02				*
 *								*
 *	M�dulo: siodata						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>

/*
 ****** Defini��es e Vari�veis Globais **************************
 */
#define _EOMEM  (char *)EOF

/*
 ******	Vari�veis externas **************************************
 */
entry char	_sio1buf[BLSZ],		/* �reas para entrada e saida */
		_sio2buf[BLSZ];

entry int	_stdbuf = 3;		/* Indica qual a �rea n�o usada */

/*
 ****************************************************************
 *	Blocos inicializados da "stdio"				*
 ****************************************************************
 */
entry FILE	_ioblk[_NFILE] =
{
   /*	ptr	base  bend  lend  bsize   flag  	file	*/

    { _EOMEM, NOSTR, NOSTR, NOSTR,   0, _IOREAD,	0 }, /* stdin */
    { _EOMEM, NOSTR, NOSTR, NOSTR,   0, _IOWRITE,	1 }, /* stdout */
    { _EOMEM, NOSTR, NOSTR, NOSTR,   0, _IOWRITE,	2 }  /* stderr */
};
