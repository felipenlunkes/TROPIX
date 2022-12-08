/*
 ****************************************************************
 *								*
 *			includes.c				*
 *								*
 *	Descobre os arquivos inclu�dos				*
 *								*
 *	Vers�o	1.0.0, de 03.05.97				*
 *		1.0.0, de 03.05.97				*
 *								*
 *	M�dulo: includes					*
 *		Utilit�rios sup�rfluos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include <errno.h>

/*
 ****************************************************************
 *	Nome e vers�o do programa				*
 ****************************************************************
 */
entry const char	pgversion[] = "Vers�o 1.0.0, de 03.05.97";
entry const char	pgoptions[] = "I:uMHNv";

/*
 ****************************************************************
 *	Macros							*
 ****************************************************************
 */
#define	PATHSZ		1024		/* Tamanho m�x. de um caminho */
#define	LINESZ		4096		/* Tamanho m�x. de uma linha */
#define	INCSZ		30		/* # m�x. de diret�rios de busca */
#define	NOCHR		'\0'

/*
 ****************************************************************
 *	Vari�veis						*
 ****************************************************************
 */
entry	char		*search_dir[INCSZ] =
{
	".",
	"/usr/include"
};

entry	char		**usr_include_pos = search_dir + 1;
entry	char		**last_search_dir = search_dir + 1;

entry	int		Nflag,
			vflag,
			uflag;

entry	const char	margin[] = "\t\t\t";

/*
 ****************************************************************
 *	Prot�tipos de Fun��es Locais				*
 ****************************************************************
 */
entry	void		help (int);
entry	int		include (const char *, STAT *, int);
entry	int		add_search_dir (const char *);
entry	int		process_include (const char *, char *, int);
entry	void		canonize (char *);

/*
 ****************************************************************
 *	Programa principal					*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	int		opt;
	char		dir_name[PATHSZ];

	/*
	 *	Analisa as op��es de execu��o.
	 */
	while ((opt = getopt (argc, argv, pgoptions)) != EOF)
	{
		switch (opt)
		{
		    case 'I':
			if (last_search_dir >= &search_dir[INCSZ - 3])
				error ("$Excesso de op��es '-I'");

			*++last_search_dir = (char *)optarg;
			break;

		    case 'u':
			uflag++;
			break;

		    case 'M':
			exit (0);

		    case 'H':
			help (0);

		    case 'N':
			Nflag++;
			break;

		    case 'v':
			vflag++;
			break;

		    default:
			putc ('\n', stderr);
			help (2);

		}	/* end switch (opt) */

	}	/* while ((opt = getopt (...))) */

	argv += optind;
	argc -= optind;

	if (Nflag)
	{
		if (*argv != NOSTR)
			error ("$Com a op��o '-N' n�o podem ser dados argumentos");

		while (fngets (dir_name, sizeof (dir_name) - 1, stdin) != NOSTR)
		{
			if (ftw (dir_name, include) != 0)
				error ("$\"ftw (\"%s\")\" retornou -1", dir_name);
		}
	}
	else if (*argv == NOSTR)
	{
		if (ftw (".", include) != 0)
			error ("$\"ftw (\".\")\" retornou -1");
	}
	else
	{
		while (*argv != NOSTR)
		{
			if (ftw (*argv, include) != 0)
				error ("$\"ftw (\"%s\")\" retornou -1", *argv);
			argv++;
		}
	}

	exit (0);

}	/* end main */

/*
 ****************************************************************
 *	Processa os includes					*
 ****************************************************************
 */
int
include (const char *name, STAT *sp, int type)
{
	char		dir[PATHSZ];
	const char	*np;
	char		*cp, *ep, c, delim;
	FILE		*fp;
	int		lineno, nincludes;
	char		line[LINESZ];

	switch (type)
	{
	    case FTW_D:
		return (0);

	    case FTW_F:
		if
		(	(np = strrchr (name, '.')) == NOSTR ||
			((c = np[1]) != 'c' && c != 'h') || np[2] != NOCHR
		)
			return (0);
		break;

	/** case FTW_NS: **/
	/** case FTW_DNR: **/
	    default:
		error ("*N�o consegui obter o estado de \"%s\"", name);
		return (0);
	}

	if (vflag)
		fprintf (stderr, "=> %s\n", name);

	/*
	 *	� um ".c" ou ".h"
	 */
	if ((np = strrchr (name, '/')) == NOSTR)
	{
		search_dir[0] = ".";
	}
	else
	{
		int	n;

		memcpy (dir, name, n = np - name);
		dir[n] = NOCHR;
		search_dir[0] = dir;
	}

	/*
	 *	Processa o arquivo, procurando #include.
	 */
	if ((fp = fopen (name, "r")) == NOFILE)
	{
		error ("*N�o pude abrir %s", name);
		return (0);
	}

	nincludes = 0;

	for (lineno = 1; fgets (line, sizeof (line) - 2, fp) != NOSTR; lineno++)
	{
		if (line[0] != '#')
			continue;

		for (cp = line + 1; (c = *cp) == ' ' || c == '\t'; cp++)
			/* pulando brancos */;

		if (strncmp (cp, "include", 7) != 0)
			continue;

		for (cp += 7; (c = *cp) == ' ' || c == '\t'; cp++)
			/* pulando brancos */;

		if (c == '<' || c == '"')
		{
			delim = (c == '<') ? '>' : '"';

			for
			(	ep = ++cp;
				(c = *ep) != delim && c != NOCHR;
				ep++
			)
				/* procurando delimitador */;

			if (c != delim)
			{
				error
				(	"Arquivo %s, linha %d: "
					"faltou delimitador",
					name, lineno
				);
			}

			*ep = NOCHR;

			if (process_include (name, cp, nincludes++) < 0)
			{
				error
				(	"Arquivo %s, linha %d: "
					"include \"%s\" n�o encontrado",
					name, lineno, cp
				);
			}
		}
		else
		{
			error
			(	"Arquivo %s, linha %d: erro de sintaxe",
				name, lineno
			);
		}
	}

	if (nincludes)
		putchar ('\n');

	fclose (fp);

	return (0);

}	/* end include */

/*
 ****************************************************************
 *	Localiza um arquivo inclu�do				*
 ****************************************************************
 */
int
process_include (const char *name, char *file, int nincludes)
{
	char		fname [PATHSZ];
	char		**dp;

	for (dp = search_dir; *dp != NOSTR; dp++)
	{
		/*
		 *	Comp�e o nome do arquivo e v� se ele existe.
		 */
		strcpy (fname, *dp);
		strcat (fname, "/");
		strcat (fname, file);

		if (vflag)
			fprintf (stderr, "====> Tentando %s\n", fname);

		if (access (fname, F_OK) >= 0)
			break;			/* Achou! */
	}

	if (nincludes == 0)
	{	/*
		 *	� a primeira vez que esta rotina � chamada para
		 *	o arquivo "name".
		 */
		printf ("\n%s%s", margin, name);
	}

	if (*dp == NOSTR)
		return (-1);

	if (uflag || dp != usr_include_pos)
	{
		canonize (fname);
		printf ("\t\\\n%s%s\t", margin, fname);
	}

	return (0);

}	/* end process_include */

/*
 ****************************************************************
 *	Elimina componentes sup�rfluos em um nome		*
 ****************************************************************
 */
void
canonize (char *fname)
{
	char	*ep, *bp, *cp, *comp, *np;
	int	n;

	ep = strend (fname);
	*ep++ = '/';
	*ep = NOCHR;

	for (bp = cp = fname; cp < ep; /* abaixo */)
	{
		comp = cp;
		while (*cp++ != '/')
			/* procurando '/' */;

		n = cp - comp;

		while (*cp == '/')
			cp++;		/* pulando '/' consecutivos */

		if (strncmp (comp, "./", n) == 0)
			continue;

		if (bp > fname && strncmp (comp, "../", n) == 0)
		{
			if (bp == fname + 1)
				continue;

			for (np = bp - 2; np >= fname && *np != '/'; np--)
				/* procurando '/' ou in�cio */;

			np++;

			if (strncmp (np, "../", bp - np) != 0)
			{
				bp = np;
				continue;
			}
		}

		while (n-- > 0)
			*bp++ = *comp++;
	}

	*--bp = NOCHR;

}	/* end canonize */

/*
 ****************************************************************
 *	Resumo de Utilizacao do Programa			*
 ****************************************************************
 */
void
help (int exitval)
{
	fprintf
	(	stderr,
		"%s - descobre arquivos inclu�dos\n\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-vuN] [-I <dir>] ... [<caminho> ...]\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: modo verboso\n"
		"\t-u: imprime tamb�m os arquivos encontrados "
			"em \"/usr/include\"\n"
		"\t-N: l� os argumentos da entrada padr�o\n"
		"\t-I: acrescenta <dir> � lista de diret�rios a procurar\n"
	);

	exit (exitval);

}	/* end help */
