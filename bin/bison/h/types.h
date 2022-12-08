
/*
 ****************************************************************
 *								*
 *			types.h					*
 *								*
 *  Data type for repres. bison's grammar input as it is parsed	*
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
 *  Data type for repres. bison's grammar input as it is parsed	*
 ****************************************************************
 */
typedef
  struct shorts
    {
      struct shorts *next;
      short value;
    }
  shorts;
