/*
 ****************************************************************
 *								*
 *			categ.h					*
 *								*
 *	Defini��es acerca das Categorias L�xicas		*
 *								*
 *	Vers�o	3.2.2, de 16.09.99				*
 *		4.5.0, de 12.11.03				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 *	Formato da entrada da tabela:
 *
 *	     3       1   1     3
 *	+----------+---+---+-------+
 *	|  CATEG   | M | A | INDEX |
 *	+----------+---+---+-------+
 *
 *	CSHIFT = 5
 */

/*
 ****************************************************************
 *	Categorias dos Caracteres				*
 ****************************************************************
 */
#define	INV	0		/* Caractere inv�lido */
#define	QUOTE	1		/* Caracteres de substitui��o */
#define	SEPAR	2		/* Separador */
#define	LETTER	3		/* Letra */
#define	DIGIT	4		/* D�gito */
#define	OTHER	5		/* Outros caracteres v�lidos */
#define	USYM	6		/* Delimitador simples */
#define	BSYM	7		/* Delimitador bin�rio */

/*
 ****************************************************************
 *	Categorias na Tabela					*
 ****************************************************************
 */
#define	I	(INV	<< CSHIFT)
#define	Q	(QUOTE	<< CSHIFT)
#define	S	(SEPAR	<< CSHIFT)
#define	L	(LETTER	<< CSHIFT)
#define	D	(DIGIT	<< CSHIFT)
#define	O	(OTHER  << CSHIFT)
#define	U	(USYM	<< CSHIFT)
#define	B	(BSYM	<< CSHIFT)

#define	M	(1 << (CSHIFT - 1))
#define	A	(1 << (CSHIFT - 2))

/*
 ****************************************************************
 *	Macros para obten��o da Categoria e �ndice		*
 ****************************************************************
 */
#define	CSHIFT		5	

#define	CATEG(t)	((t) >> CSHIFT)

#define	CINDEX(t)	((t) & 0x07)

#define IS_META(t)	((categtb[t]) & M)

#define IS_ACCENT(t)	((categtb[t]) & A)

/*
 ****************************************************************
 *	A tabela de categorias					*
 ****************************************************************
 */
extern	const uchar	categtb[];
