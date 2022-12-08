/*
 ****************************************************************
 *								*
 *			atexit.c				*
 *								*
 *	Registra fun��es para serem executadas no "exit"	*
 *								*
 *	Vers�o	2.3.0, de 04.03.90				*
 *		3.0.0, de 08.06.95				*
 *								*
 *	M�dulo: atexit						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	TABLESZ		32		/* No. de m�ximas de fun��es */

#define	NOTABLE 	(void (**) (void))NULL

static void	(**atexit_table0) (void), /* Ponteiros da Tabela */
		(**atexit_table1) (void),
		(**atexit_table2) (void);

/*
 ****************************************************************
 *	Registra fun��es para serem executadas no "exit"	*
 ****************************************************************
 */
int
atexit (void (*func) (void))
{
	register void	(**tp) (void);

	if (atexit_table0 == NOTABLE)
	{
		if ((tp = malloc (TABLESZ * sizeof (void (*) ()))) == NOTABLE)
			return (-1);

		atexit_table0 = tp;
		atexit_table1 = tp;
		atexit_table2 = tp + TABLESZ;
	}

	if (atexit_table1 >= atexit_table2)
		return (-1);

	*atexit_table1++ = func;

	return (0);

}	/* end atexit */

/*
 ****************************************************************
 *	Executa as fun��es executadas				*
 ****************************************************************
 */
void
_atexit_exec (void)
{
	register void	(**tp) (void);

	if ((tp = atexit_table1) == NOTABLE)
		return;

	for (tp--; tp >= atexit_table0; tp--)
		(**tp) ();

}	/* end _atexit_exec */
