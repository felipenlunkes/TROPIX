/*
 ****************************************************************
 *								*
 *			defs.h					*
 *								*
 *	Defini��es b�sicas					*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 22.03.95				*
 *								*
 *	M�dulo: defs.h						*
 *		libcurses/terminfo				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Defini��es comuns ***************************************
 */
typedef enum	{ false, true  }	bool;

#define	EVER	;;
#define	elif	else if

#ifndef	NULL
#define		NULL	0
#endif	NULL

#define	NOSTR	(char *)NULL

/*
 ******	Manipula��o de indicadores ******************************
 */
#define	check(f,m)	(((f)&(m)) != 0)	/* Verifica��o */
#define	checkall(f,m)	(((f)&(m)) == (m))	/* Verifica��o */
#define	set(f,m)	((f) |=  (m))		/* Ligando */
#define	reset(f,m)	((f) &= ~(m))		/* Desligando */

/*
 ******	Esta macro deveria ser definida em <stdio.h> ************
 */
#define	remaining(fp)	(((fp)->_bend > (fp)->_ptr) ?	\
				((fp)->_bend - (fp)->_ptr) : 0)
