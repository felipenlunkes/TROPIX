/*
 ****************************************************************
 *								*
 *			h/txtio.h				*
 *								*
 *	Defini��es para Entrada e Sa�da de Texto		*
 *								*
 *	Vers�o	1.0.0, de 04.11.86				*
 *		3.0.0, de 26.04.97				*
 *								*
 *	Modulo: VI/EX						*
 *		Editores de Texto				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	TXTIO_H

/*
 ******	Estado do arquivo ***************************************
 */
typedef	enum
{
	IO_OK,		/* E/S sem problemas */
	IO_NSPACE,	/* N�o houve mem�ria suficiente */
	IO_WRERROR,	/* Erro na escrita */
	IO_RDERROR,	/* Erro na leitura */
	IO_PERMISSION,	/* Permiss�o negada */
	IO_NFOUND,	/* Arquivo n�o encontrado */
	IO_DIRECTORY,	/* Arquivo � um diret�rio */
	IO_IREGULAR,	/* Arquivo irregular */
	IO_OBJECT,	/* Arquivo contem um programa objeto */
	IO_EMPTY,	/* Arquivo vazio */
	IO_RDONLY,	/* Arquivo com permiss�o apenas para leitura */
	IO_EXISTS,	/* Arquivo j� existe */
	IO_SAVED	/* O Texto j� foi salvo */

}	TXTIO;
