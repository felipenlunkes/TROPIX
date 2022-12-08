/*
 ****************************************************************
 *								*
 *			symtab.h				*
 *								*
 *	Definitions for symtab.c and callers, part of bison	*
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


/*
 ****************************************************************
 *	Definitions for symtab.c and callers, part of bison	*
 ****************************************************************
 */
#define	TABSIZE	1009


/*  symbol classes  */

#define SUNKNOWN 0
#define STOKEN	 1
#define SNTERM	 2


typedef
  struct bucket
    {
      struct bucket *link;
      struct bucket *next;
      char *tag;
      char *type_name;
      short value;
      short prec;
      short assoc;
      short user_token_number;
      char class;
    }
  bucket;


extern bucket **symtab;
extern bucket *firstsymbol;

extern bucket	*gensym (void);
extern bucket	*getsym (char *key);
