/*
 ****************************************************************
 *								*
 *			merge.c					*
 *								*
 *	Intercala��o de registros de arquivos j� ordenados	*
 *								*
 *	Vers�o	1.0.0, de 03.10.86				*
 *		3.0.0, de 05.07.97				*
 *								*
 *	M�dulo: sort						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../h/sort.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	LINESZ	1024

#define NFILES	10

/*
 ******	Defini��o de tipos **************************************
 */
typedef struct
{
	char	l_line[LINESZ];	/* Conte�do da linha (deve ser o primeiro) */
	FILE	*l_fp;		/* File pointer do arquivo */

}	LINE;

#define	NOLINE	(LINE *)NULL

/*
 ****************************************************************
 *	Rotina de Merge						*
 ****************************************************************
 */
void
merge (register const char *argv[])
{
	register LINE	**vp, **vpe, *lp;
	LINE		*line_vec[NFILES];
	int		file_cnt = 0;

	/*
	 *	Abre os arquivos e l� a primeira linha de cada um deles
	 */
	for (vp = line_vec; *argv != NOSTR; argv++, *vp++ = lp, file_cnt++)
	{
		if (vp >= &line_vec[NFILES])
		{
			fprintf
			(	stderr,
				"%s: N�mero de arquivos maior que " XSTR (NFILES) "\n",
				pgname
			);
			exit (1);
		}

		if ((lp = malloc (sizeof (LINE))) == NOLINE)
			{ fprintf (stderr, "Mem�ria esgotada\n"); exit (1); }

		if ((lp->l_fp = fopen (*argv, "r")) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, *argv, strerror (errno)
			);
			exit (1);
		}

		if (fngets (lp->l_line, LINESZ, lp->l_fp) == NOSTR)
		{
			fprintf
			(	stderr,
				"%s: O arquivo \"%s\" est� vazio\n",
				pgname, *argv
			);
			exit (1);
		}

	}	/* end for */

	*vp = NOLINE;	/* Marca o final */

	/*
	 *	Ordena as primeiras linhas dos arquivos
	 *	(Repare a ordem dos membros da estrutura)
	 */
	qtsort (line_vec, file_cnt, compar);

	/*
	 *	L� e ordena as linhas restantes dos arquivos
	 */
	for (vp = line_vec; (lp = *vp) != NOLINE; /* abaixo */)
	{
		fnputs (lp->l_line, out_fp);

		if (fngets (lp->l_line, LINESZ, lp->l_fp) == NOSTR)
			{ vp++; continue; }

		for (vpe = vp + 1; *vpe != NOLINE; vpe++)
		{
			if (compar (vpe[-1]->l_line, vpe[0]->l_line) <= 0)
				break;

			lp = vpe[-1];	vpe[-1] = vpe[0];    vpe[0] = lp;
		}
	}

}	/* end merge */
