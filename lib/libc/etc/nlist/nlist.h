/*
 ****************************************************************
 *								*
 *			<nlist.h>				*
 *								*
 *	Estrutura usada pela rotina "nlist.c"			*
 *								*
 *	Vers�o	1.0.0, de 20.11.86				*
 *		4.0.0, de 22.08.01				*
 *								*
 *	M�dulo: nlist.h						*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Defini��o da estrutura **********************************
 */
typedef struct nlist
{
	const char	*n_name;	/* Nome do S�mbolo */
	long		n_value;	/* Seu valor */
	int		n_type;		/* Seu tipo */

}	NLIST;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern int	nlist (const char *, NLIST *);
