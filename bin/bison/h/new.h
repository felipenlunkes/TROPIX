/*
 ****************************************************************
 *								*
 *			new.h					*
 *								*
 *	Storage allocation interface for bison			*
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
 *	Storage allocation interface for bison			*
 ****************************************************************
 */
#define	NEW(t)		((t *) mallocate((unsigned) sizeof(t)))
#define	NEW2(n, t)	((t *) mallocate((unsigned) ((n) * sizeof(t))))

#define	FREE(x)		if (x)	\
				 free ((void *) (x))

extern	char *mallocate ();
