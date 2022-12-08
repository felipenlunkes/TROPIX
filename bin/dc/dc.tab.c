
/*  A Bison parser, made from dc.y with Bison version GNU Bison version 1.21
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	DIGIT	258
#define	LETTER	259
#define	SCALE	260
#define	UMINUS	261

#line 21 "dc.y"

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


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		44
#define	YYFLAG		-32768
#define	YYNTBASE	22

#define YYTRANSLATE(x) ((unsigned)(x) <= 261 ? yytranslate[x] : 27)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    17,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    13,     8,     2,    19,
    20,    11,     9,     2,    10,     2,    12,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    14,
    18,    15,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     7,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     6,     2,    21,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
    16
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     5,     9,    11,    15,    19,    23,    27,    31,
    35,    39,    43,    47,    51,    55,    59,    62,    65,    67,
    70,    72,    75,    77
};

static const short yyrhs[] = {    -1,
    22,    23,    17,     0,    22,     1,    17,     0,    24,     0,
     4,    18,    24,     0,    19,    24,    20,     0,    24,     9,
    24,     0,    24,    10,    24,     0,    24,    11,    24,     0,
    24,    12,    24,     0,    24,    13,    24,     0,    24,     8,
    24,     0,    24,     6,    24,     0,    24,     7,    24,     0,
    24,    14,    24,     0,    24,    15,    24,     0,    10,    24,
     0,    21,    24,     0,     4,     0,    25,    26,     0,     3,
     0,    25,     3,     0,     5,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   154,   155,   156,   160,   162,   170,   172,   174,   176,   178,
   180,   182,   184,   186,   188,   190,   192,   194,   196,   203,
   207,   217,   221,   222
};

static const char * const yytname[] = {   "$","error","$illegal.","DIGIT","LETTER",
"SCALE","'|'","'^'","'&'","'+'","'-'","'*'","'/'","'%'","'<'","'>'","UMINUS",
"'\\n'","'='","'('","')'","'~'","list","stat","expr","number","scale",""
};
#endif

static const short yyr1[] = {     0,
    22,    22,    22,    23,    23,    24,    24,    24,    24,    24,
    24,    24,    24,    24,    24,    24,    24,    24,    24,    24,
    25,    25,    26,    26
};

static const short yyr2[] = {     0,
     0,     3,     3,     1,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     2,     2,     1,     2,
     1,     2,     1,     0
};

static const short yydefact[] = {     1,
     0,     0,    21,    19,     0,     0,     0,     0,     4,    24,
     3,     0,    19,    17,     0,    18,     2,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    22,    23,    20,
     5,     6,    13,    14,    12,     7,     8,     9,    10,    11,
    15,    16,     0,     0
};

static const short yydefgoto[] = {     1,
     8,     9,    10,    30
};

static const short yypact[] = {-32768,
    23,   -13,-32768,   -12,    26,    26,    26,     8,    57,     0,
-32768,    26,-32768,-32768,    42,-32768,-32768,    26,    26,    26,
    26,    26,    26,    26,    26,    26,    26,-32768,-32768,-32768,
    57,-32768,    66,    74,    81,    -3,    -3,-32768,-32768,-32768,
-32768,-32768,    28,-32768
};

static const short yypgoto[] = {-32768,
-32768,    -5,-32768,-32768
};


#define	YYLAST		96


static const short yytable[] = {    14,
    15,    16,    28,    11,    29,    12,    31,    23,    24,    25,
    26,    27,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,     2,    17,     3,     4,    44,     3,    13,
     0,     0,     5,     0,     0,     5,     0,     0,     0,     0,
     0,     6,     0,     7,     6,     0,     7,    18,    19,    20,
    21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
     0,    32,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    20,    21,    22,    23,    24,    25,    26,    27,    21,
    22,    23,    24,    25,    26,    27
};

static const short yycheck[] = {     5,
     6,     7,     3,    17,     5,    18,    12,    11,    12,    13,
    14,    15,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,     0,     1,    17,     3,     4,     0,     3,     4,
    -1,    -1,    10,    -1,    -1,    10,    -1,    -1,    -1,    -1,
    -1,    19,    -1,    21,    19,    -1,    21,     6,     7,     8,
     9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
    -1,    20,     6,     7,     8,     9,    10,    11,    12,    13,
    14,    15,     7,     8,     9,    10,    11,    12,    13,    14,
    15,     8,     9,    10,    11,    12,    13,    14,    15,     9,
    10,    11,    12,    13,    14,    15
};
/*
 ****************************************************************
 *								*
 *			bison.simple.c				*
 *								*
 *	Skeleton output parser for bison			*
 *								*
 *	Vers�o	3.0.0, de 10.07.93				*
 *		3.0.0, de 10.07.93				*
 *								*
 *	M�dulo: GBISON						*
 *		Gerador de analisadores sint�ticos		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Baseado em software hom�nimo do GNU		*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#line 23 "bison.simple"

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

#line 113 "bison.simple"
int
yyparse (void)
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      memmove (yyss, yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      memmove (yyvs, yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      memmove (yyls, yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 157 "dc.y"
{ yyerrok; ;
    break;}
case 4:
#line 161 "dc.y"
{ printf ("\t%d\t(%P)\n", yyvsp[0], yyvsp[0]); ;
    break;}
case 5:
#line 163 "dc.y"
{
			  printf ("\t%d\t(%P)\n", yyvsp[0], yyvsp[0]);
			  regs [yyvsp[-2]] = yyvsp[0];
			  defined [yyvsp[-2]] = 1;
			;
    break;}
case 6:
#line 171 "dc.y"
{ yyval = yyvsp[-1]; ;
    break;}
case 7:
#line 173 "dc.y"
{ yyval = yyvsp[-2] + yyvsp[0]; ;
    break;}
case 8:
#line 175 "dc.y"
{ yyval = yyvsp[-2] - yyvsp[0]; ;
    break;}
case 9:
#line 177 "dc.y"
{ yyval = yyvsp[-2] * yyvsp[0]; ;
    break;}
case 10:
#line 179 "dc.y"
{ yyval = yyvsp[-2] / yyvsp[0]; ;
    break;}
case 11:
#line 181 "dc.y"
{ yyval = yyvsp[-2] % yyvsp[0]; ;
    break;}
case 12:
#line 183 "dc.y"
{ yyval = yyvsp[-2] & yyvsp[0]; ;
    break;}
case 13:
#line 185 "dc.y"
{ yyval = yyvsp[-2] | yyvsp[0]; ;
    break;}
case 14:
#line 187 "dc.y"
{ yyval = yyvsp[-2] ^ yyvsp[0]; ;
    break;}
case 15:
#line 189 "dc.y"
{ yyval = yyvsp[-2] << yyvsp[0]; ;
    break;}
case 16:
#line 191 "dc.y"
{ yyval = yyvsp[-2] >> yyvsp[0]; ;
    break;}
case 17:
#line 193 "dc.y"
{ yyval = -yyvsp[0]; ;
    break;}
case 18:
#line 195 "dc.y"
{ yyval = ~yyvsp[0]; ;
    break;}
case 19:
#line 197 "dc.y"
{
			  if (!defined [yyvsp[0]])
				error ("A vari�vel \"%c\" ainda n�o foi definida", 'a' + yyvsp[0]);

			  yyval = regs[yyvsp[0]];
			;
    break;}
case 20:
#line 204 "dc.y"
{ yyval = yyvsp[-1] * yyvsp[0]; ;
    break;}
case 21:
#line 208 "dc.y"
{ int	c;

			  if   (yyvsp[0] != 0)
				{ yyval = yyvsp[0]; base = 10; }
			  elif ((c = getchar ()) == 'x')
				{ yyval = 0; base = 16; }
			  else
				{ yyval = c - '0'; base = 8; }
			;
    break;}
case 22:
#line 218 "dc.y"
{ yyval = base * yyvsp[-1] + yyvsp[0]; ;
    break;}
case 24:
#line 223 "dc.y"
{ yyval = 1; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 386 "bison.simple"
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 226 "dc.y"


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
