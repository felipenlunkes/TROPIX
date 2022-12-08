/*
 ****************************************************************
 *								*
 *			visual.h				*
 *								*
 *	Defini��o da estrutura para edi��o visual		*
 *								*
 *	Vers�o	2.0.0, de 13.05.88				*
 *		3.0.0, de 23.03.95				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 *	Os seguintes arquivos devem ser inclu�dos antes deste:
 *
 *		<curses.h>
 *		"../h/defs.h"
 */

#define	H_VISUAL	/* Para declarar as fun��es */

/*
 ******	Estrutura para edi��o visual ****************************
 */
typedef	struct
{
	WINDOW	*v_win,		/* Janela para o texto */
		*v_err;		/* Janela para mensagens de erro */

	BASE	*v_ant,
		*v_pos;

	BASE	*v_first,	/* Primeira linha de texto na janela */
		*v_last;	/* �ltima linha da janela */

	BASE	**v_map;

	short	v_cols,		/* No. de colunas em v_win */
		v_lines;	/* No. de linhas */

	short	v_size;		/* No. de linhas ocupadas em v_win */
	short	v_toleft;	/* v_win deslocada para a esquerda */

	short	v_curl,		/* Posi��o coreente em v_win */
		v_curc;

	BASE	*v_base;	/* Posi��o corrente no texto */

	char	*v_search;	/* Aut�mato para busca de exp. regular */
	char	*v_ssearch;

}	VIEW;

#define	NOVIEW	(VIEW *)0

/*
 ******	Constantes para o modo visual ***************************
 */
#define		VIEW_WIDTH	120	/* Largura da P�gina */

/*
 ******	Modo visual: valores de retorno *************************
 */
#define		VIS_QUIT	(-1)
#define		VIS_QUICK	0
#define		VIS_STAY	1
