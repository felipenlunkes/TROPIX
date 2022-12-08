/*
 ****************************************************************
 *								*
 *			tabs.h					*
 *								*
 *	Estrutura das tabelas de linhas e de depura��o		*
 *								*
 *	Vers�o	1.0.0, de 28.01.86				*
 *		3.0.0, de 28.02.94				*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Estrutura da tabela de linhas ***************************
 */
#define	NOLNOTB		(LNOTB *)NULL

/*** typedef	struct lnotb	LNOTB; ***/

struct lnotb
{
	LINE	l;			/* Estrutura da Entrada */
	LNOTB	*l_next;		/* Proximo Elemento */
};

/*
 ******	Estrutura da tabela de s�mbolos2 ************************
 */
#define NODBTB		(DBTB *)NULL

/*** typedef struct db	DBTB; ***/

struct db
{
	DBSYM	db;
	DBTB	*d_next;
};
