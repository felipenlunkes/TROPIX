/*
 ****************************************************************
 *								*
 *			_cleanup.c				*
 *								*
 *	Executa o "atexit" e fecha todos os arquivos		*
 *								*
 *	Vers�o	1.0.0, de 14.10.86				*
 *		3.0.0, de 08.07.95				*
 *								*
 *	M�dulo: _cleanup					*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include	<stdio.h>

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void	_atexit_exec (void);

/*
 ****************************************************************
 *	Executa o "atexit" e fecha todos os arquivos		*
 ****************************************************************
 */
void
_cleanup (void)
{
	register FILE *fp;

	_atexit_exec ();

	for (fp = &_ioblk[0]; fp < &_ioblk[_NFILE]; fp++)
		fclose (fp);

}	/* end _cleanup */
