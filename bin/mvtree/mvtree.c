/*
 ****************************************************************
 *								*
 *			mvtree.c				*
 *								*
 *	Move ou troca o nome de uma �rvore/diret�rio		*
 *								*
 *	Vers�o	1.0.0, de 23.09.86				*
 *		4.2.0, de 29.04.02				*
 *								*
 *	M�dulo: mvtree						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 29.04.02";

entry int	vflag;		/* Verbose */
entry int	dflag;		/* Debug */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
int 		cptree (const char *, const char *);
int 		rmtree (const char *);
const char	*compose_name (const char *, const char *);
const char	*last_id (const char *);
const char 	*parent_nm (const char *);
const char	*path_normalize (const char *);
int 		dotdot (const char *);
int		is_ancest (const char *, STAT *, const char *);
void		help (void);

/*
 ****************************************************************
 *	Move ou troca o nome de uma �rvore/diret�rio		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	*oldnm, *newnm;
	STAT		old_s, new_s;
	STAT		old_par_s, new_par_s;
	const char	*dirlastnm;
	const char	*oldparent, *newparent;

	/*
	 *	Verifica se o programa foi instalado corretamente
	 */
	if (geteuid () != 0)
		error ("$O usu�rio efetivo n�o � o SUPERUSU�RIO");

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vdH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'd':			/* Debug */
			dflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argc -= optind;
	argv += optind;

	if (argc != 2)
		help ();

	/*
	 *	Normaliza os caminhos
	 */
	oldnm = path_normalize (argv[0]);
	newnm = path_normalize (argv[1]);

	/*
	 *	Analisa o "old"
	 */
	if ((lstat (oldnm, &old_s)) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", oldnm);

	if (!S_ISDIR (old_s.st_mode))
		error ("$\"%s\" n�o � um diret�rio", oldnm);

	/*
	 *	Analisa o "new"
	 */
	if ((stat (newnm, &new_s)) >= 0)
	{
		if (!S_ISDIR (new_s.st_mode))
			error ("$\"%s\" j� existe e n�o � um diret�rio", newnm);

		newnm = compose_name (newnm, last_id (oldnm));

		if ((lstat (newnm, &new_s)) >= 0)
			error ("$\"%s\" j� existe", newnm);

	}	/* end if */

	/*
	 *	Verifica se o nome composto ficou igual
	 */
	if (streq (oldnm, newnm))
		error ("$<fonte> == <destino> ?");

	/*
	 *	Analisa o �ltimo componente do caminho do <diret�rio fonte>
	 */
	dirlastnm = last_id (oldnm);

	if (streq (dirlastnm, ".")  ||  streq (dirlastnm, ".."))
		error ("$N�o posso trocar o nome de \"%s\"", oldnm);

	/*
	 *	Analisa o pai do <diret�rio fonte>
	 */
	if (stat ((oldparent = parent_nm (oldnm)), &old_par_s) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", oldparent);

	/*
	 *	Analisa o pai do <diret�rio destino>
	 */
	if (stat ((newparent = parent_nm (newnm)), &new_par_s) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", newparent);

	/*
	 *	Analisa as permiss�es de acesso de escrita
	 */
	if (access (oldnm, W_OK) < 0)
		error ("$*N�o tenho permiss�o de escrita em \"%s\"", oldnm);

	if (access (newparent, W_OK) < 0)
		error ("$*N�o tenho permiss�o de escrita em \"%s\"", newparent);

	if (access (oldparent, W_OK) < 0)
		error ("$*N�o tenho permiss�o de escrita em \"%s\"", oldparent);
	
	if (dflag)
		printf ("\"%s\" => \"%s\"\n", oldnm , newnm);

	/*
	 ******	Verifica agora, se deve realmente copiar ********
	 */
	if (new_par_s.st_dev != old_par_s.st_dev)
	{
		if (is_ancest (oldnm, &old_s, newparent))
			exit (1);

		if (dflag)
		{
			printf ("Caso 2: cptree/rmtree\n");

			if (dflag > 1)
				exit (3);
		}

		if (cptree (oldnm, newnm) != 0)
			error ("$Erro na c�pia de \"%s\" para \"%s\"", oldnm, newnm);

		if (rmtree (oldnm) != 0)
			error ("$Erro na remo��o  de \"%s\"", oldnm);

		exit (0);
	}	

	/*
	 ******	N�o precisa copiar: Ignora os sinais ************
	 */
	if (dflag)
	{
		printf ("Caso 1: mesmo dispositivo\n");

		if (dflag > 1)
			exit (3);
	}

	if (new_par_s.st_ino != old_par_s.st_ino)
	{
		if (is_ancest (oldnm, &old_s, newparent))
			exit (1);
	}

	if (rename (oldnm, newnm) < 0)
		error ("$*N�o consegui trocar o nome de \"%s\" para \"%s\"", oldnm, newnm);

	return (0);

}	/* end mvtree */

/*
 ****************************************************************
 *	Copia uma arvore					*
 ****************************************************************
 */
int
cptree (const char *oldnm, const char *newnm)
{
	long		pid;
	int		status;

	if ((pid = fork ()) < 0)
		error ("$*N�o consegui dar \"fork\" para copiar \"%s\"", oldnm);

	if (pid)
	{
		wait (&status);
	}
	else
	{
		execl ("/usr/bin/cptree", "cptree", "-fm.", oldnm, newnm, 0);
		execl ("/bin/cptree", "cptree", "-fm.", oldnm, newnm, 0);

		error ("$*N�o consegui executar \"cptree\" para copiar \"%s\"", oldnm);

	}

	return (status);

}	/* end cptree */

/*
 ****************************************************************
 *	Remove uma arvore					*
 ****************************************************************
 */
int
rmtree (const char *oldnm)
{
	long		pid;
	int		status;

	if ((pid = fork ()) < 0)
		error ("$*N�o consegui dar \"fork\" para remover \"%s\"", oldnm);

	if (pid)
	{
		wait (&status);
	}
	else
	{
		execl ("/usr/bin/rmtree", "cptree", "-f", oldnm, 0);
		execl ("/bin/rmtree", "cptree", "-f", oldnm, 0);

		error ("$*N�o consegui executar \"rmtree\" para remover \"%s\"", oldnm);

	}

	return (status);

}	/* end rmtree */

/*
 ****************************************************************
 *	Normaliza um caminho					*
 ****************************************************************
 */
const char *
path_normalize (const char *nm)
{
	char		*cp;

	for (cp = strend (nm) - 1; cp[0] == '/' && cp > nm; cp--)
		*cp = '\0';

	while (strncmp (nm, "./", 2) == 0)
		nm += 2;

	return (nm);

}	/* end path_normalize */

/*
 ****************************************************************
 *	Comp�e o nome de um arquivo de um diret�rio		*
 ****************************************************************
 */
const char *
compose_name (const char *dirnm, const char *filenm)
{
	char		*cp;
	int		sz;

	sz = strlen (dirnm) + strlen (filenm) + 2;

	if ((cp = malloc (sz)) == NOSTR)
		error (NOSTR);

	strcpy (cp, dirnm);

	if (strcmp (cp, "/"))
		strcat (cp, "/");

	strcat (cp, filenm);

	if (strncmp (cp, "./", 2))
		return (cp);
	else
		return (cp + 2);

}	/* end compose_name */

/*
 ****************************************************************
 *	Obt�m o �ltimo componente de um nome			*
 ****************************************************************
 */
const char *
last_id (const char *pathname)
{
	const char	*cp;

	if (cp = strrchr (pathname, '/'))
		return (cp + 1);
	else
		return (pathname);

} 	/* end last_id */

/*
 ****************************************************************
 *	Obt�m o nome do pai do arquivo				* 
 ****************************************************************
 */
const char *
parent_nm (const char *filenm)
{
	char		*cp;
	const char	*parent;

	if ((parent = strdup (filenm)) == NOSTR)
		error (NOSTR);

	if ((cp = strrchr (parent, '/')) == NOSTR)
		return (".");

	if (cp == parent)
		cp++;

	*cp = '\0';

	return (parent);

}	/* end parent_nm */

/*
 ****************************************************************
 * 	Checa se o diret�rio antigo � ancestral do novo		*	
 ****************************************************************
 */
int
is_ancest (const char *oldnm, STAT *old_s, const char *newparentnm)
{
	char		*path;
	int		pathsz;
	STAT		s, roots;

	if (stat ("/", &roots) < 0)
	{
		error ("*N�o consegui obter o estado de \"/\"");
		return (1);
	}

	s.st_ino = 0;

	pathsz = strlen (newparentnm) + 2;

	if ((path = malloc (pathsz)) == NOSTR)
		error (NOSTR);

	strcpy (path, newparentnm);

	while (s.st_dev != roots.st_dev || s.st_ino != roots.st_ino)
	{
		if (lstat (path, &s) < 0)
		{
			error ("*N�o consegui obter o estado de \"%s\"", path);
			return (1);
		}

		if (dflag)
			printf ("comparando \"%s\" com \"%s\"\n", oldnm, path);

		if (s.st_dev == old_s->st_dev && s.st_ino == old_s->st_ino)
		{
			error ("\"%s\" � ancestral de \"%s\"", oldnm, newparentnm);
			return (1);
		}

		if ((path = realloc (path, (pathsz += 3))) == NOSTR)
			error (NOSTR);

		strcat (path, "/..");

	}	/* end while */

	return (0);

}	/* end is_ancest */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - move (troca o nome) de uma �rvore/diret�rio\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <�rvore1> <�rvore2>\n",
		pgname, pgversion, pgname
	);

	exit (2);

} 	/* end help */
