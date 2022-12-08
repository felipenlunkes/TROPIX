/*
 ****************************************************************
 *								*
 *			askyesno.c				*
 *								*
 *	Obt�m uma resposta afirmativa ou negativa		*
 *								*
 *	Vers�o	2.1.0, de 04.10.88				*
 *		3.0.0, de 08.06.95				*
 *								*
 *	M�dulo: askyesno					*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>

#define	elif	else if
#define	EVER	;;

/*
 ******	Vari�veis globais ***************************************
 */
entry FILE	*askyesno_stdin  = stdin;
entry FILE	*askyesno_stderr = stderr;

static char	askyesno_force = 0;
static int	askyesno_force_seen = 0;

/*
 ****************************************************************
 *	Obt�m uma resposta afirmativa ou negativa		*
 ****************************************************************
 */
int
askyesno (void)
{
	int		c, reply;

	/*
	 *	Se j� foi dado um "S" ou "N", ...
	 */
	if   (askyesno_force_seen > 0)
		{ fprintf (askyesno_stderr, "SIM\n"); return (1); }
	elif (askyesno_force_seen < 0)
		{ fprintf (askyesno_stderr, "N�O\n"); return (-1); }

	/*
	 *	L� um caractere (na realidade uma linha)
	 */
    again:
	fflush (askyesno_stderr);

	while ((c = reply = getc (askyesno_stdin)) == ' ' || c == '\t')
		/* vazio */;

	for (EVER)
	{
		if   (c == EOF)
			{ fprintf (askyesno_stderr, "???\n"); return (0); }
		elif (c == '\n')
			break;

		c = getc (askyesno_stdin);

	}	/* end for (EVER) */

	/*
	 *	Analisa o caractere lido
	 */
	switch (reply)
	{
	    case '\n':
		return (0);

	    case 's':
	    case 'y':
		return (1);

	    case 'n':
		return (-1);

	    case 'S':
	    case 'Y':
		if (askyesno_force)
			askyesno_force_seen = 1;

		return (1);

	    case 'N':
		if (askyesno_force)
			askyesno_force_seen = -1;

		return (-1);

	    default:
		fprintf (askyesno_stderr, "Sim ou N�o: ");
		goto again;

	}	/* end switch */

}	/* end askyesno */

/*
 ****************************************************************
 *	Modifica o estado da fun��o "askyesno"			*
 ****************************************************************
 */
int
askyesno_set (int op)
{
	askyesno_force	     = op;
	askyesno_force_seen = 0;

}	/* end askyesno_set */
