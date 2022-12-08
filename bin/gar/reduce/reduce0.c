/*
 ****************************************************************
 *								*
 *			reduce0.c				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.00, de 27.08.90				*
 *		3.1.06, de 04.05.97				*
 *								*
 *	M�dulo: GAR						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <signal.h>
#include <string.h>

#include "../h/reduce.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry long	in_cnt, out_cnt; /* Total de caracteres de entrada/sa�da */

entry int	in_fd;		/* Descritor do arquivo */

entry FILE	*out_fp;	/* FILE do arquivo */

entry int	code_area[NC];	/* Cabem sempre NC c�digos at� de 16 bits */

/*
 ****** Par�metros de compress�o ********************************
 */
entry int	MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

entry int	MAX_BIT_USED;	/* N�mero de bits realmente usados */ 

entry int	MAX_CODE;	/* Nunca pode usar este c�digo */

entry int	CODE_SOURCE;	/* Fonte de novos c�digos */

entry int	TEST_POINT;	/* Pr�ximo teste de performance */

entry int	bit_sz;		/* Tamanho atual */

entry int	max_code;	/* �ltimo c�digo do tamanho atual */

/*
 ****************************************************************
 *	Edita uma percentagem					*
 ****************************************************************
 */
char *
editpercent (int quoc)
{
	static char	buf[8];
	char		*sinal;

	if (quoc < 0)
		{ sinal = "-"; quoc = -quoc; }
	else
		sinal = "";


	sprintf (buf, "%s%d.%02d", sinal, quoc / 100, quoc % 100);
	
	return (buf);

}	/* end editpercent */

/*
 ****************************************************************
 *	Calcula uma percentagem					*
 ****************************************************************
 */
int
getpercent (long numer, long denom)
{
	int		quoc;

	/*
	 *	Tenta evitar overflow
	 */
	if (numer > (0x7FFFFFFF / 10000))
		quoc = numer / (denom / 10000);
	else
		quoc = 10000 * numer / denom;

	return (quoc);

}	/* end percent */
