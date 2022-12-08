/*
 ****************************************************************
 *								*
 *			lex.h					*
 *								*
 *	Defini��es e estruturas usadas pelo scanner		*
 *								*
 *	Vers�o	1.0.0, de 14.02.86				*
 *		3.0.0, de 26.02.94				*
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
 ******	Categorias l�xicas **************************************
 */
#define	INV	0		/* Caractere Invalido */
#define	SEPAR	1		/* Separador */
#define	LETTER	2		/* Letra */
#define	DIGIT	3		/* Digito */
#define	APOST	4		/* Apostrofo */
#define	QUOTE	5		/* Aspas */
#define	USYM	6		/* Simbolo Unario (de um caractere) */
#define	BSYM	7		/* Simbolo Unario ou Duplo */

/*
 ******	Macros para obten��o da categoria & �ndice **************
 */
#define	CATEG(t)	(categtb[*(t)])

#define	CINDEX(t)	(indextb[*(t)])

/*
 ******	Vetor de s�mbolos un�rios *******************************
 */
typedef	struct
{
	MAJOR	u_major;	/* major do delimitador */
	MINOR	u_minor;	/* minor do delimitador */

}	UNSYM;

/*
 ******	Defini��es globais **************************************
 */
extern const char	categtb[];	/* Tabela de categorias dos catacteres */
extern const char	indextb[];	/* Tabela de �ndices dos caracteres */
extern const UNSYM	unsym[];	/* Vetor de Simbolos Unarios */

