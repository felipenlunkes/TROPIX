/*
 ****************************************************************
 *								*
 *			<ftw.h>					*
 *								*
 *	Caminha em uma �rvore do sistema de arquivos		*
 *								*
 *	Vers�o	1.0.0, de 16.07.86				*
 *		4.2.0, de 08.04.02				*
 *								*
 *	M�dulo: ftw.h						*
 *		/usr/include 					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��o de tipos					*
 ****************************************************************
 */
typedef enum
{
	FTW_F = 5,	/* Arquivo */ 
	FTW_D,		/* Diret�rio */
	FTW_NS,		/* N�o foi poss�vel obter o estado */
	FTW_DNR,	/* N�o foi poss�vel abrir o diret�rio */
	FTW_SL		/* Elo simb�lico */

}	FTW_ENUM;

/*
 ****************************************************************
 *	Prot�tipos das fun��es					*
 ****************************************************************
 */
extern int	ftw (const char *, int (*) (const char *, STAT *, int));
