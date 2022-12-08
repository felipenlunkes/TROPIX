/*
 ****************************************************************
 *								*
 *			dc.y					*
 *								*
 *	Calculador de mesa com aritm�tica inteira		*
 *								*
 *	Vers�o	3.2.3, de 24.03.00				*
 *		4.6.0, de 03.11.04				*
 *								*
 *	M�dulo: dc						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
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
const char	pgversion[] =  "Vers�o: 4.6.0, de 03.11.04";

#define	YYDEBUG		0
#define	YYMAXDEPTH	0

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

entry int	regs[26];	/* Os 26 registros de "a" a "z" */
entry char	defined[26];	/* Indica quais os registros com valor */
entry int	base;		/* Base do n�mero sendo examinado */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
int		yylex (void);
int		yyparse (void);
void		help (void);

/*
 ****************************************************************
 *	Calculador de mesa com aritm�tica inteira		*
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

}	/* end dc */

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
		"%s - calculador de mesa com aritm�tica inteira\n"
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

%token DIGIT LETTER SCALE

%left	'|'
%left	'^'
%left	'&'
%left	'+' '-'
%left	'*' '/' '%' '<' '>'
%left	UMINUS

%%

list	:	/* vazio */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;
	
stat	:	expr
			{ printf ("\t%d\t(%P)\n", $1, $1); }
	|	LETTER '=' expr
			{
			  printf ("\t%d\t(%P)\n", $3, $3);
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
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	expr '^' expr
			{ $$ = $1 ^ $3; }
	|	expr '<' expr
			{ $$ = $1 << $3; }
	|	expr '>' expr
			{ $$ = $1 >> $3; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	'~' expr	%prec UMINUS
			{ $$ = ~$2; }
	|	LETTER
			{
			  if (!defined [$1])
				error ("A vari�vel \"%c\" ainda n�o foi definida", 'a' + $1);

			  $$ = regs[$1];
			}
	|	number scale
			{ $$ = $1 * $2; }
	;

number	:	DIGIT
			{ int	c;

			  if   ($1 != 0)
				{ $$ = $1; base = 10; }
			  elif ((c = getchar ()) == 'x')
				{ $$ = 0; base = 16; }
			  else
				{ $$ = c - '0'; base = 8; }
			}
	|	number DIGIT
			{ $$ = base * $1 + $2; }
	;

scale	:	SCALE
	|	/* vazio */
			{ $$ = 1; }
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
	int		c;

	while ((c = getchar ()) == ' ' || c == '\t')
		/* vazio */;

	switch (c)
	{
	    case 'a':
	    case 'b':
	    case 'c':
	    case 'd':
	    case 'e':
	    case 'f':
	    case 'g':
	    case 'h':
	    case 'i':
	    case 'j':
	    case 'k':
	    case 'l':
	    case 'm':
	    case 'n':
	    case 'o':
	    case 'p':
	    case 'q':
	    case 'r':
	    case 's':
	    case 't':
	    case 'u':
	    case 'v':
	    case 'w':
	    case 'x':
	    case 'y':
	    case 'z':
		yylval = c - 'a';
		return (LETTER);

	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		yylval = c - '0';
		return (DIGIT);

	    case 'A':
	    case 'B':
	    case 'C':
	    case 'D':
	    case 'E':
	    case 'F':
		yylval = c - 'A' + 10;
		return (DIGIT);

	    case 'K':
		yylval = 1024;
		return (SCALE);

	    case 'M':
		yylval = 1024 * 1024;
		return (SCALE);

	    case 'G':
		yylval = 1024 * 1024 * 1024;
		return (SCALE);

	    case '>':
		if ((c = getchar ()) != '>')
			ungetc (c, stdin);

		return ('>');

	    case '<':
		if ((c = getchar ()) != '<')
			ungetc (c, stdin);

		return ('<');

	    default:
		return (c);
	}

#if (0)	/*******************************************************/
	while ((c = getchar ()) == ' ' || c == '\t')
		/* vazio */;

	if (c >= 'a' && c <= 'z')
		{ yylval = c - 'a'; return (LETTER); }

	if (c >= '0' && c <= '9')
		{ yylval = c - '0'; return (DIGIT); }

	if (c >= 'A' && c <= 'F')
		{ yylval = c - 'A' + 10; return (DIGIT); }

	if (c == 'K')
		{ yylval = 1024; return (SCALE); }

	if (c == 'M')
		{ yylval = 1024 * 1024; return (SCALE); }

	if (c == 'G')
		{ yylval = 1024 * 1024 * 1024; return (SCALE); }

	if (c == '>')
	{
		if ((c = getchar ()) != '>')
			ungetc (c, stdin);

		return ('>');
	}

	if (c == '<')
	{
		if ((c = getchar ()) != '<')
			ungetc (c, stdin);

		return ('<');
	}

	return (c);
#endif	/*******************************************************/

}	/* end yylex */
