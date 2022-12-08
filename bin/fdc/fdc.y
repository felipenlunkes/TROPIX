/*
 ****************************************************************
 *								*
 *			fdc.y					*
 *								*
 *	Calculador de mesa com aritm�tica flutuante		*
 *								*
 *	Vers�o	3.2.3, de 25.03.00				*
 *		3.2.3, de 25.03.00				*
 *								*
 *	M�dulo: fdc						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.2.3, de 25.03.00";

#define	YYDEBUG		0
#define	YYMAXDEPTH	0

union yystype
{
	double	d;
	int	i;
};

#define	YYSTYPE	union yystype

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

entry double	regs[26];	/* Os 26 registros de "a" a "z" */
entry char	defined[26];	/* Indica quais os registros com valor */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
int		yylex (void);
int		yyparse (void);
void		help (void);

/*
 ****************************************************************
 *	Calculador de mesa com aritm�tica flutuante		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vNH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Executa o calculador 
	 */
	yyparse ();

	return (exit_code);

}	/* end fdc */

/*
 ****************************************************************
 *	Fun��o de erro						*
 ****************************************************************
 */
void
yyerror (const char *fmt)
{
	error (fmt);

}	/* end yyerror */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - calculador de mesa com aritm�tica flutuante\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */

%}

/*
 ****************************************************************
 *	A gram�tica						*
 ****************************************************************
 */
%start	list

%token	<i>	LETTER
%token	<d>	NUMBER

%type	<d>	expr

%left	'+' '-'
%left	'*' '/'
%left	UMINUS

%%

list	:	/* vazio */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;
	
stat	:	expr
			{ printf ("\t%15.8g\n", $1, $1); }
	|	LETTER '=' expr
			{
			  printf ("\t%15.8g\n", $3, $3);
			  regs [$1] = $3;
			  defined [$1] = 1;
			}
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '*' expr
			{ $$ = $1 * $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	LETTER
			{
			  if (!defined [$1])
				error ("A vari�vel \"%c\" ainda n�o foi definida", 'a' + $1);

			  $$ = regs[$1];
			}
	|	NUMBER
	;

%%

/*
 ****************************************************************
 *	O analisador l�xico					*
 ****************************************************************
 */
int
yylex (void)
{
	static char	area[128];
	static char	*area_ptr;
	static char	not_empty;
	int		c;

	if (!not_empty)
	{
		if ((fgets (area, sizeof (area), stdin)) == NOSTR)
			return (EOF);

		not_empty = 1; area_ptr = area;
	}

	while ((c = *area_ptr++) == ' ' || c == '\t')
		/* vazio */;

	if (c >= 'a' && c <= 'z')
		{ yylval.i = c - 'a'; return (LETTER); }

	if (c >= '0' && c <= '9' || c == '.')
	{
		yylval.d = strtod (area_ptr - 1, (const char **)&area_ptr);
		return (NUMBER);

	}

	if (c == '\n')
		not_empty = 0;

	return (c);

}	/* end yylex */
