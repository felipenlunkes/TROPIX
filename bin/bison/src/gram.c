/*
 ****************************************************************
 *								*
 *			gram.c					*
 *								*
 *	Allocate input grammar variables for bison		*
 *								*
 *	Vers�o	3.0.0, de 06.07.93				*
 *		3.0.0, de 06.07.93				*
 *								*
 *	M�dulo: GBISON						*
 *		Gerador de analisadores sint�ticos		*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Baseado em software hom�nimo do GNU		*
 * 								*
 ****************************************************************
 */

/* comments for these variables are in gram.h  */

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
int nitems;
int nrules;
int nsyms;
int ntokens;
int nvars;

short *ritem;
short *rlhs;
short *rrhs;
short *rprec;
short *rprecsym;
short *sprec;
short *rassoc;
short *sassoc;
short *token_translations;
short *rline;

int start_symbol;

int translations;

int max_user_token_number;

int semantic_parser;

int pure_parser;

int error_token_number;
