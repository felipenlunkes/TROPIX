/*
 ****************************************************************
 *								*
 *			h/scan.h				*
 *								*
 *	Defini��es para o uso do Scanner			*
 *								*
 *	Vers�o	1.0.0, de 07.10.86				*
 *		3.0.0, de 26.04.97				*
 *								*
 *	Modulo: VI/EX/ED					*
 *		Editores de Texto				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	SCAN_H

/*
 ****** Leitura de um Caractere *********************************
 */
extern	char	*nextp;

/*
 ****** Tipo Token **********************************************
 */
typedef	struct
{
	char	*t_begin;
	char	*t_end;

}	TOKEN;

/*
 ****** Tipo de Marca��o de Erro ********************************
 */
typedef	enum { NOMARK, SHORTMARK, LONGMARK }	ERR;
