/*
 ****************************************************************
 *								*
 *			common.h				*
 *								*
 *	Defini��es universais					*
 *								*
 *	Vers�o	3.2.2, de 16.09.99				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	elif		else if
#define	EVER		;;

#ifndef	NULL
#define	NULL		0
#endif

#define NOCHR		'\0'

#ifndef	NOSTR
#define	NOSTR		(char *)NULL
#endif	NOSTR

#define	INVSTR		((char *)(-1))
#define	NOSSTR		(char **)NULL

#define	ALLOC_SHIFT	5			/* Incremento para aloca��es */
#define	ALLOC_INC	(1 << ALLOC_SHIFT)
#define	ALLOC_MASK	(ALLOC_INC - 1)

#define	BUFSZ		512			/* Tamanho de buffer */
#define	HISTSZ		20			/* Tamanho do hist�rico */
#define	NPAR		10			/* Nr. par�metros posicionais */
