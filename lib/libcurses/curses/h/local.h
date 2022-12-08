/*
 ****************************************************************
 *								*
 *			local.h					*
 *								*
 *	Declara��es Locais 					*
 *								*
 *	Vers�o	2.0.0, de 16.03.88				*
 *		3.0.0, de 22.03.95				*
 *								*
 *	Modulo: local.h						*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 *	Os seguintes arquivos devem ser incluidos antes deste:
 *
 *		<curses.h>
 */

/*
 ******	Janelas dispon�veis *************************************
 */
#define		_NWINDOWS	20	/* No. Max. de Janelas */

extern	WINDOW	*_windows;		/* Janelas */
