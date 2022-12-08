/*
 ****************************************************************
 *								*
 *			lex.h					*
 *								*
 *	Defini��es peculiares ao analisador l�xico		*
 *								*
 *	Vers�o	1.0.0, de 05.08.88				*
 *		4.1.0, de 22.08.01				*
 *								*
 *	M�dulo: CPP						*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Categorias L�xicas					*
 ****************************************************************
 */
#define	INV	0		/* Caractere Inv�lido */
#define	SEPAR	1		/* Separador */
#define	LETTER	2		/* Letra */
#define	DIGIT	3		/* D�gito */
#define	QUOTE	4		/* Aspas */
#define	USYM	5		/* Simbolo Un�rio (de um caractere) */
#define	BSYM	6		/* Simbolo Un�rio ou Duplo */
#define	APOST	7		/* Ap�strofe */

/*
 ****************************************************************
 *	Macros para Obten��o da Categoria & �ndice		*
 ****************************************************************
 */
#define	CATEG(cp)	categ[*(cp)]

#define	CINDEX(cp)	cindex[*(cp)]

extern const char	categ[];	/* Tabela de categorias */

/*
 ****************************************************************
 *	Vetor com S�mbolos Un�rios				*
 ****************************************************************
 */
typedef	struct
{
	MAJOR	u_major;	/* MAJOR do S�mbolo */
	MINOR	u_minor;	/* MINOR do S�mbolo */

}	UNSYM;
