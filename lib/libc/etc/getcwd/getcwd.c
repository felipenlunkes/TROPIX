/*
 ****************************************************************
 *								*
 *			getcwd.c				*
 *								*
 *	Obtem o nome do diret�rio corrente			*
 *								*
 *	Vers�o	1.0.0, de 24.11.86				*
 *		4.8.0, de 02.11.05				*
 *								*
 *	M�dulo: getcwd						*
 *		lib/etc 					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define	EVER	;;

/*
 ****************************************************************
 *	Ponto de Entrada da Rotina				*
 ****************************************************************
 */
char *
getcwd (char *path, int size)
{
	char		*pp;
	ino_t		par_ino;
	STAT		s;
	DIRENT		de;

	/*
	 *	Pequenas inicializa��es
	 */
	errno = NOERR;

	/*
	 *	Aloca a �rea, se necess�rio
	 */
	if (path == NOSTR && (path = malloc (size)) == NOSTR)
		return (NOSTR);

	/*
	 *	Prepara a �rea do caminho
	 */
	pp = path + size; *--pp = '\0';

	/*
	 *	Obt�m o estado do diret�rio corrente, para come�ar
	 */
	if (stat (".", &s) < 0)
		return (NOSTR);

	/*
	 *	Percorre os componentes do caminho
	 */
	while ((par_ino = getdirpar (s.st_dev, s.st_ino, &de)) != 0)	/* Significa "/" */
	{
		if (par_ino == -1)
			{ error ("*Erro em \"getdirpar\""); return (NOSTR); }

		pp -= de.d_namlen; strncpy (pp, de.d_name, de.d_namlen); *--pp = '/';

		s.st_dev = de.d_offset; s.st_ino = par_ino;
	}

	/*
	 *	Terminou (finalmente)
	 */
	if (*pp != '/')
		*--pp = '/';

	return (pp);

}	/* end getcwd */
