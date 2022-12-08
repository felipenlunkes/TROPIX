/*
 ****************************************************************
 *								*
 *			<locale.h>				*
 *								*
 *	Localization						*
 *								*
 *	Vers�o	2.3.0, de 02.03.90				*
 *		3.0.0, de 27.01.98				*
 *								*
 *	M�dulo: locale.h					*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
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
	LC_ALL,		/* Todo o "locale" */
	LC_COLLATE,	/* Fun��es "strcoll" e "strxfrm" */
	LC_CTYPE,	/* Fun��es de an�lise de caracteres */
	LC_MONETARY,	/* Informa��o monet�ria */
	LC_NUMERIC,	/* Ponto decimal (e outros) */
	LC_TIME		/* Fun��o "strftime" */

} 	LC_ENUM;

#define	LC_SIZE	(LC_TIME + 1)

typedef struct lconv
{
	char	*decimal_point;	
	char	*thousands_sep;
	char	*grouping;
	char	*int_curr_symbol;
	char	*currency_symbol;
	char	*mon_decimal_point;
	char	*mon_thousands_sep;
	char	*mon_grouping;
	char	*positive_sign;
	char	*negative_sign;
	char	int_frac_digits;
	char	frac_digits;
	char	p_cs_precedes;
	char	p_sep_by_space;
	char	n_cs_precedes;
	char	n_sep_by_space;
	char	p_sign_posn;
	char	n_sign_posn;

}	LCONV;

/*
 ****************************************************************
 *	Defini��o de macros					*
 ****************************************************************
 */
#define	NULL	0

/*
 ****************************************************************
 *	Vari�veis externas					*
 ****************************************************************
 */
#define	LC_COL	4

extern char	_lc_vector[LC_SIZE][LC_COL];
extern LCONV	_lc_lconv;

/*
 ****************************************************************
 *	Prot�tipos						*
 ****************************************************************
 */
extern const char	*setlocale (int, const char *);
extern const LCONV	*localeconv (void);
