/*
 ****************************************************************
 *								*
 *			ls.c					*
 *								*
 *	Lista caracter�sticas de  arquivos e			*
 *	conte�dos de diret�rios					*
 *								*
 *	Vers�o	1.0.0, de 19.06.87				*
 *		4.9.0, de 26.04.07				*
 *								*
 *	M�dulo: ls						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2007 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 4.9.0, de 26.04.07";

#define	elif	else if

entry int	exitcode = 0;		/* C�digo de retorno do programa */

const char	**color_vector;		/* Para as cores dos modos */

static char	global_area[32];	/* Para v�rias edi��es */

/*
 ******	Indicadores *********************************************
 */
entry int	lflag;		/* Longo */
entry int	flag3;		/* 3 datas */
entry int	dflag;		/* Diret�rio */
entry int	iflag;		/* Inode */
entry int	tflag;		/* time */
entry int	aflag;		/* "." e ".." */
entry int	Rflag;		/* Subdiret�rios */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

/*
 ******	Quasi-constantes do tempo *******************************
 */
entry time_t	HOJE;		/* In�cio do dia de hoje (GMT) */
entry time_t	AMANHA;		/* In�cio do dia de amanh� (GMT) */
entry time_t	SEMANA;		/* In�cio da semana (GMT) */

/*
 ******	Bloco de informa��es de cada arquivo ********************
 */
typedef struct	info	INFO;

struct	info
{
	const char	*i_nm;		/* Nome de arquivo ou diret�rio */
	STAT		i_s;		/* Estado do arquivo */
	INFO		*i_next;	/* Pr�ximo elemento da lista */
};

#define	NOINFO	(INFO *)NULL

entry INFO	filelist,		/* Cabe�a da lista de arquivos */
		dirlist;		/* Cabe�a da lista de diret�rios */

entry INFO	*dirptr = NOINFO;	/* Ponteiro para o diret�rio sendo listado */

/*
 ******	Prot�tipo de fun��es ************************************
 */
void		help (void);
void 		proc_file (const char *);
void 		list_insert (INFO *, INFO *);
void 		show_list (INFO *, int);
void 		show_file (INFO *, int, int, int, int, int);
void 		put_time (time_t);
const char	*edit_uid (int uid);
const char	*edit_gid (int gid);
const char	*edit_decimal_number (int number);
const char	*edit_dev_number (const INFO *ip);
const char	*compose_name (const char *, const char *);
int 		dir_read (INFO *);
const char	*last_id (const char *);
INFO		*infodup (INFO *);

/*
 ****************************************************************
 * Lista caracter�sticas de arquivos e conte�dos de diret�rios	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	time_t		difuso;
	int		longname = 1;
	int		first_dir = 0;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "lL3ditaRNMH")) != EOF)
	{
		switch (opt)
		{
		    case 'l':			/* Longo */
			lflag++;
			break;

		    case 'L':			/* Muito longo */
			lflag += 2;
			break;

		    case '3':			/* 3 datas */
			flag3++;
			break;

		    case 'd':			/* Diret�rio */
			dflag++;
			break;

		    case 'i':			/* Inode */
			iflag++;
			break;

		    case 't':			/* time */
			tflag++;
			break;

		    case 'a':			/* "." e ".." */
			aflag++;
			break;

		    case 'R':			/* Subdiret�rios */
			Rflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'M':			/* Sticky */
			exit (0);

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Pequena consist�ncia
	 */
	if ((lflag ? 1 : 0) + flag3 > 1 || (aflag || dflag) + Rflag > 1)
		help ();

	/*
	 *	Prepara as datas para o c�lculo de HOJE e dias da SEMANA
	 */
	time (&HOJE);				/* Agora GMT */

	difuso = gettzmin () * 60;

	HOJE += difuso;				/* Agora local */

	HOJE =  HOJE / (3600 * 24) * (3600 * 24);

	HOJE -= difuso;				/* Zero hora GMT ajustada */

	AMANHA = HOJE + (3600 * 24);		/* Zero hora de amanh� */

	SEMANA = HOJE - (3600 * 24 * 7);	/* Zero hora h� uma semana */

#undef	DEBUG
#ifdef	DEBUG
	printf ("HOJE =		%s", btime (&HOJE));
	printf ("AMANH� =	%s", btime (&AMANHA));
	printf ("SEMANA =	%s", btime (&SEMANA));
#endif	DEBUG

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stdout)), (void *)NULL, &color_vector);

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
		error ("Os argumentos sup�rfluos ser�o ignorados");

	/*
	 *	Procura os argumentos
	 */
	if   (Nflag) 		/* L� do "stdin" */
	{
		char		*area, *file_nm;
		int		len;

		area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			len = strlen (area);
			file_nm = alloca (len + 1);
			strcpy (file_nm, area);

			proc_file (file_nm);
		}
	}
	elif (*argv == NOSTR) 	/* N�o foram dados argumentos nem "-N": considera "." */
	{
		proc_file (".");
	}
	else 			/* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
			proc_file (*argv);
	}

#ifdef	DEBUG
{	INFO		*ip;

	for (ip = filelist.i_next; ip; ip = ip->i_next)
		printf ("%s\n", ip->i_nm); 	

	printf ("\n"); 	

	for (ip = dirlist.i_next; ip; ip = ip->i_next)
		printf ("%s\n", ip->i_nm); 	
}
#endif	DEBUG

	/*
	 *	Lista os arquivos
	 */
	if (argc > 1 || Nflag || Rflag)
		longname = 0;

	if (filelist.i_next)
		first_dir++;

	show_list (&filelist, 1 /* longname */);

	/*
	 *	Lista os diret�rios; repare que "dir_read" estende "dirlist"
	 */
	for (dirptr = dirlist.i_next; dirptr != NOINFO; dirptr = dirptr->i_next)
	{
		if (longname == 0)
		{
			if (first_dir++)
				printf ("\n");

			printf ("\"%s\":\n", dirptr->i_nm);
		}

		dir_read (dirptr);

		show_list (&filelist, longname);

	}	/* end for */

	return (exitcode);

}	/* end ls */

/*
 ****************************************************************
 *	Processa um nome					*
 ****************************************************************
 */
void
proc_file (const char *filenm)
{
	INFO		*ip;

	if ((ip = malloc (sizeof (INFO))) == NOINFO)
		error (NOSTR);

	if (lstat (filenm, &ip->i_s) < 0)
	{
		error ("*N�o consegui obter o estado de \"%s\"", filenm);
		free (ip);
		exitcode++;
		return;
	}

	ip->i_nm = filenm;

	if (!dflag  &&  S_ISDIR (ip->i_s.st_mode))
		list_insert (&dirlist, ip);
	else
		list_insert (&filelist, ip);

}	/* end proc_file */

/*
 ****************************************************************
 *	Insere no ponto correto da lista			*
 ****************************************************************
 */
void
list_insert (INFO *list, INFO *member)
{
	INFO		*ip;
	time_t		timeval;
	const char	*nm;

	if   (list == &dirlist)
	{
		/*
		 *	Se for um diret�rio, insere alfabeticamente,
		 *	mas depois do diret�rio atual
		 */
		if ((ip = dirptr) == NOINFO)
			ip = list;

		nm = member->i_nm;

		for (/* vazio */; ip->i_next != NOINFO; ip = ip->i_next)
		{
#define	FOLD
#ifdef	FOLD
			if (strttcmp (nm, ip->i_next->i_nm, cmpfoldtb, cmpafoldtb) <= 0)
#else
			if (strcmp (nm, ip->i_next->i_nm) <= 0)
#endif	FOLD
				break;
		}
	}
	elif (tflag)
	{
		/*
		 *	Insere pelo tempo de modifica��o
		 */
		timeval = member->i_s.st_mtime;

		for (ip = list; ip->i_next != NOINFO; ip = ip->i_next)
		{
			if (timeval >= ip->i_next->i_s.st_mtime)
				break;
		}
	}
	else
	{
		/*
		 *	Insere alfabeticamente
		 */
		nm = member->i_nm;
	
		for (ip = list; ip->i_next != NOINFO; ip = ip->i_next)
		{
#ifdef	FOLD
			if (strttcmp (nm, ip->i_next->i_nm, cmpfoldtb, cmpafoldtb) <= 0)
#else
			if (strcmp (nm, ip->i_next->i_nm) <= 0)
#endif	FOLD
				break;
		}
	}

	member->i_next = ip->i_next;
	ip->i_next = member;

}	/* end list_insert */

/*
 ****************************************************************
 *	Lista as informa��es de uma LISTA			*
 ****************************************************************
 */
void
show_list (INFO *list, int longname)
{
	INFO		*ip, *nextip;
	int		nlink_len, max_nlink_len = -1;
	int		uid_len, max_uid_len = -1;
	int		gid_len, max_gid_len = -1;
	int		size_len, max_size_len = -1;

	if (flag3  &&  list->i_next != NOINFO)
	{
		if (iflag)
			printf ("           ");

		printf
		(	"    "
			"------ CRIA��O -----  "
			"---- MODIFICA��O ---  "
			"------ ACESSO ------\n"
		);
	}

	/*
	 *	Procura o m�ximo das v�rias colunas
	 */
	if (lflag) for (ip = list->i_next; ip != NOINFO; ip = ip->i_next)
	{
		if ((nlink_len = strlen (edit_decimal_number (ip->i_s.st_nlink))) > max_nlink_len)
			max_nlink_len = nlink_len;

		if ((uid_len = strlen (edit_uid (ip->i_s.st_uid))) > max_uid_len)
			max_uid_len = uid_len;

		if ((gid_len = strlen (edit_gid (ip->i_s.st_gid))) > max_gid_len)
			max_gid_len = gid_len;

		if (S_ISBLK (ip->i_s.st_mode) || S_ISCHR (ip->i_s.st_mode))
			size_len = strlen (edit_dev_number (ip));
		else
			size_len = strlen (edit_decimal_number (ip->i_s.st_size));

		if (size_len > max_size_len)
			max_size_len = size_len;
	}

	/*
	 *	Imprime
	 */
	for (ip = list->i_next; ip != NOINFO; ip = nextip)
	{
		show_file (ip, longname, max_nlink_len, max_uid_len, max_gid_len, max_size_len);

		nextip = ip->i_next; free (ip);
	}

	list->i_next = NOINFO;		/* Esvazia a LISTA */

}	/* end show_list */

/*
 ****************************************************************
 *	Lista as informa��es de um ARQUIVO			*
 ****************************************************************
 */
void
show_file (INFO *ip, int longname, int max_nlink_len, int max_uid_len, int max_gid_len, int max_size_len)
{
	char		*modestr;

	modestr = modetostr (ip->i_s.st_mode);

	if (iflag)
		printf ("%10u ", ip->i_s.st_ino);

	if (lflag)
	{
		printf ("%c ", modestr[0]);

		if (lflag > 1)
			printf ("%s", modestr + 2);
		else
			printf ("%s", modestr + 14);

		printf (" %*d", max_nlink_len, ip->i_s.st_nlink);

		printf (" %-*s", max_uid_len, edit_uid (ip->i_s.st_uid));
		printf (" %-*s", max_gid_len, edit_gid (ip->i_s.st_gid));

		if (S_ISBLK (ip->i_s.st_mode) || S_ISCHR (ip->i_s.st_mode))
			printf (" %*s", max_size_len, edit_dev_number (ip));
		else
			printf (" %*u", max_size_len, ip->i_s.st_size);

		put_time (ip->i_s.st_mtime);

		printf ("  ");
	}
	elif (flag3)
	{
		printf ("%c ", modestr[0]);

		put_time (ip->i_s.st_ctime);
		put_time (ip->i_s.st_mtime);
		put_time (ip->i_s.st_atime);

		printf ("  ");
	}

	printf
	(	"%s%s",
		color_vector[(ip->i_s.st_mode & S_IFMT) >> 12],
		longname ? ip->i_nm : last_id (ip->i_nm)
	);

	if (lflag && S_ISLNK (ip->i_s.st_mode))
	{
		char		*link_nm;
		STAT		dst_s;

		link_nm = alloca (ip->i_s.st_size + 1);

		printf ("%s => ", color_vector[MC_DEF]);

		if (readlink (ip->i_nm, link_nm, ip->i_s.st_size + 1) >= 0)
			printf ("%s", link_nm);

		if (stat (ip->i_nm, &dst_s) < 0)
			printf ("\e[34m (!)\e[0m");
	}

	printf ("%s\n", color_vector[MC_DEF]);

}	/* end show_file */

/*
 ****************************************************************
 *	Le um diret�rio						*
 ****************************************************************
 */
int
dir_read (INFO *dirip)
{
	INFO		*ip;
	DIR		*dir_fd;
	const DIRENT	*dp;
	const char	*filenm;

	/*
	 *	Abre o diret�rio
	 */
	if ((dir_fd = inopendir (dirip->i_s.st_dev, dirip->i_s.st_ino)) == NODIR)
	{
		error ("*N�o consegui abrir \"%s\"", dirip->i_nm);
		return (0);
	}

	/*
	 *	Le o diret�rio
	 */
	while ((dp = readdir (dir_fd)) != NODIRENT)
	{
		if (!aflag && dp->d_name[0] == '.')
		{
			if   (dp->d_name[1] == '\0')
				continue;
			elif (dp->d_name[1] == '.' && dp->d_name[2] == '\0')
				continue;
		}

		if ((ip = malloc (sizeof (INFO))) == NOINFO)
			error (NOSTR);

		filenm = compose_name (dirip->i_nm, dp->d_name);

		if (instat (dirip->i_s.st_dev, dp->d_ino, &ip->i_s) < 0)
		{
			error ("*N�o consegui obter o estado de \"%s\"", filenm);
			free (ip);
			exitcode++;
			continue;
		}

		ip->i_nm = filenm;

		list_insert (&filelist, ip);

		if (Rflag  &&  S_ISDIR (ip->i_s.st_mode))
			list_insert (&dirlist, infodup (ip));

	}	/* end while (fread) */

	closedir (dir_fd);

	return (0);

}	/* end dir_read */

/*
 ****************************************************************
 *	Copia uma estrutura "INFO"				*
 ****************************************************************
 */
INFO *
infodup (INFO *ip)
{
	INFO		*ipcpy;

	if ((ipcpy = malloc (sizeof (INFO))) == NOINFO)
		error (NOSTR);

	*ipcpy = *ip;

	return (ipcpy);

}	/* end infodup */

/*
 ****************************************************************
 *	Imprime uma DATA					*
 ****************************************************************
 */
void
put_time (time_t timeval)
{
	char		*tp;

	tp = btime (&timeval);

	printf ("  %-8.8s ", tp);		/* hora */

	if (timeval < SEMANA || timeval >= AMANHA)
		printf ("%4.4s %-6.6s", tp+20, tp+13);
	else if (timeval >= HOJE)
		printf ("HOJE %-6.6s", tp+13);
	else
		printf (" %-10.10s", tp+9);

}	/* end put_time */

/*
 ****************************************************************
 *	Edita um UID						*
 ****************************************************************
 */
const char *
edit_uid (int uid)
{
	const char	*str;

	if ((str = pwcache (uid)) != NOSTR)
		snprintf (global_area, sizeof (global_area), "<%s>", str);
	else
		snprintf (global_area, sizeof (global_area), "<%d>", uid);

	return (global_area);

}	/* end edit_uid */

/*
 ****************************************************************
 *	Edita um GID						*
 ****************************************************************
 */
const char *
edit_gid (int gid)
{
	const char	*str;

	if ((str = grcache (gid)) != NOSTR)
		snprintf (global_area, sizeof (global_area), "<%s>", str);
	else
		snprintf (global_area, sizeof (global_area), "<%d>", gid);

	return (global_area);

}	/* end edit_gid */

/*
 ****************************************************************
 *	Edita um n�mero decimal					*
 ****************************************************************
 */
const char *
edit_decimal_number (int number)
{
	snprintf (global_area, sizeof (global_area), "%u", number);

	return (global_area);

}	/* end edit_decimal_number */

/*
 ****************************************************************
 *	Edita um dispositivo					*
 ****************************************************************
 */
const char *
edit_dev_number (const INFO *ip)
{
	sprintf
	(	global_area, "%d/%d",		/* Ou "%3d/%-3d" */
		MAJOR (ip->i_s.st_rdev),
		MINOR (ip->i_s.st_rdev)
	);

	return (global_area);

}	/* end edit_dev_number */

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

	if (*(strend (cp) - 1) != '/')
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
	char		*cp;

	if (cp = strrchr (pathname, '/'))
		return (cp + 1);
	else
		return (pathname);

} 	/* end last_id */

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
		"%s - lista caracter�sticas de arquivos e "
			"conte�dos de diret�rios\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-lL3ditaRN] [<nome> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Simples: apenas o nome do arquivo\n"
		"\t-l: Longo: tipo, modo, n�mero de elos f�sicos, dono, grupo, "
			"tamanho e data de modifica��o\n"
		"\t-L: Muito longo: como o longo, com o modo completo\n"
		"\t-3: 3 datas: tipo, datas de cria��o, �ltima modifica��o e "
			"�ltimo acesso\n"
		"\t-d: Caracter�sticas do diret�rio, e n�o de seu conte�do\n"
		"\t-i: Inclui o n�mero do n�-�ndice\n"
	);

	fprintf
	(	stderr,
		"\t-t: Ordena os arquivos pela data da �ltima modifica��o\n"
		"\t-a: Lista tamb�m \".\" e \"..\"\n"
		"\t-R: Lista subdiret�rios recursivamente\n"
		"\t-N: L� os <nome>s de \"stdin\"\n"

		"\nObs.:\tSe n�o for dado nenhum <nome> nem a op��o \"-N\", "
			"� listado o diret�rio corrente\n"
	);

	exit (2);

}	/* end help */
