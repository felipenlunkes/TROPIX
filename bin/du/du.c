/*
 ****************************************************************
 *								*
 *			du.c					*
 *								*
 *	Informa sobre o uso de disco				*
 *								*
 *	Vers�o	1.0.0, de 15.06.86				*
 *		4.6.0, de 24.10.04				*
 *								*
 *	M�dulo: du						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/ustat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stat.h>
#include <fcntl.h>
#include <errno.h>

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.6.0, de 24.10.04";

#define	EVER		;;
#define	elif		else if
#define STR(x)		# x
#define XSTR(x)		STR (x)

/*
 ******	Convers�es para KB e MB *********************************
 */
enum {	NPAT = 20 };	/* No. maximo de Padr�es */

#define	BLTOKB_INT(x)	((unsigned)(x) >> (KBSHIFT-BLSHIFT))
#define	BLTOKB_DEC(x)	(((x) & (KBSZ/BLSZ-1)) * (100 / (KBSZ/BLSZ)))


#define	BLTOMB_INT(x)	((unsigned)(x) >> (MBSHIFT-BLSHIFT))
#define	BLTOMB_DEC(x)	((100 * ((unsigned)(x) & (MBSZ/BLSZ - 1))) >> (MBSHIFT-BLSHIFT))

/*
 ******	Os padr�es **********************************************
 */
entry const char	*inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
entry int		inc_pati;

entry const char	*exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
entry int		exc_pati;

/*
 ******	Lista de nomes de um diret�rio **************************
 */
typedef struct	name	NAME;

struct name
{
	char	*i_nm;			/* Nome (somente um nome) */
	int	i_len;			/* Comprimento do nome */
	int	i_ino;			/* Comprimento do nome */
	NAME	*i_next;		/* Ponteiro para o pr�ximo */
};

#define	NONAME (NAME *)NULL

/*
 ******	Item de "link" ******************************************
 */
typedef struct litem	LITEM;

struct litem
{
	dev_t	l_dev;		/* Dispositivo */
	ino_t	l_ino;		/* No. do Inode */
	LITEM	*l_next;	/* o Proximo */
};

entry LITEM	*linklist;	/* Comeco da Lista */

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry int	dotflag;	/* N�o ignora ".old" ... */
entry int	dflag;		/* Para cada subdiret�rio */
entry int	aflag;		/* Para cada arquivo */
entry int	mflag;		/* Em MB */
entry int	vflag;		/* Verbose */
entry int	gflag;		/* Debug */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

entry long	TOTAL;		/* Total geral em BL */
entry int	files;		/* No. de arquivos processados */

entry int	ret;		/* C�digo de retorno */

entry int	blkmask,	/* M�scara do tamanho do bloco */
		blkmask_given;

const char	du_fmt[]   = "%9s  %s\n";
const char	du_title[] = "----%s---  ------NOME------\n";

/*
 ******	Prot�tipos de fun��es ***********************************
 */
long		proc_file (const char *);
long		file_analysis (const char *, int, int, int, int);
int		proc_link (STAT *);
int		getintmask (const char *str);
int		round_file_size_to_BL (const STAT *sp);
void		put_s_option (void);
int		put_p_option (char *, const char *[], int *);
int		pattern_accept (const char *);
char		*edit_sz_value (int);
void		help (void);

/*
 ****************************************************************
 *	Informa sobre o uso de disco				*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es.
	 */
	while ((opt = getopt (argc, argv, "damb:.sp:P:vgNH")) != EOF)
	{
		switch (opt)
		{
		    case 'd':			/* Somente total */
			dflag++;
			break;

		    case 'a':			/* Para cada arquivo */
			aflag++;
			break;

		    case 'm':			/* Em MB */
			mflag++;
			break;

		    case 'b':			/* Tamanho do bloco */
			blkmask = getintmask (optarg);
			blkmask_given++;
			break;

		    case '.':			/* N�o ignora ".old" ... */
			dotflag++;
			break;

		    case 's':			/* Padr�es = 	*.[cshryv] e */
			put_s_option ();
			break;

		    case 'p':		/* Padr�es de inclus�o */
			put_p_option ((char *)optarg, inc_pat, &inc_pati);
			break;

		    case 'P':		/* Padr�es de exclus�o */
			put_p_option ((char *)optarg, exc_pat, &exc_pati);
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'g':			/* Debug */
			gflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			fputc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;

	printf (du_title, mflag ? "MB" : "KB");

	/*
	 *	Analisa as <�rvores>
	 */
	if (*argv == NOSTR) 		/* N�o foram dadas <�rvores> */
	{
		if (Nflag)
		{
			char		*area = alloca (512);

			while (fngets (area, 512, stdin) != NOSTR)
				proc_file (area);
		}
		else
		{
			proc_file (".");
		}
	}
	else				/* Foram dadas <�rvores> */
	{
		if (Nflag)
		{
			char		*area = alloca (512);

			error ("Os argumentos sup�rfluos ser�o ignorados");

			while (fngets (area, 512, stdin) != NOSTR)
				proc_file (area);
		}
		else
		{
			for (/* vazio */; *argv; argv++)
				proc_file (*argv);
		}
	}

	/*
	 *	Se foram dados mais de uma <�rvore>, d� o total geral
	 */
	if (files > 1)
		printf (du_fmt, edit_sz_value (TOTAL), "TOTAL");

	return (ret);

}	/* end du */

/*
 ****************************************************************
 *	Analisa uma <�rvore>					*
 ****************************************************************
 */
long
proc_file (const char *file_nm)
{
	long		total;
	STAT		s;

	if (stat (file_nm, &s) < 0)
	{
		error ("*N�o consegui obter o estado de \"%s\"", file_nm);
		ret++;
		return (0);
	}

	total = file_analysis (file_nm, strlen (file_nm), s.st_dev, s.st_ino,  1 /* Root */);

	printf (du_fmt, edit_sz_value (total), file_nm);

	TOTAL += total; files++;

	return (total);

}	/* end proc_file */

/*
 ****************************************************************
 *	Calcula o total de uma <�rvore>				*
 ****************************************************************
 */
long
file_analysis (const char *file_nm, int file_len, int dev, int ino, int root)
{
	DIR		*dir_fd;
	const DIRENT	*dp;
	long		dir_total = 0;
	char		*memnm;
	STAT		s;
	NAME		name_list, *lp, *ip;

	if (gflag)
		error ("file_analysis (%s, %d)", file_nm, root);

	/*
	 *	Inicialmente, obt�m o estado do arquivo
	 */
	if (instat (dev, ino, &s) < 0)
	{
		error ("*N�o consegui obter o estado de \"%s\"", file_nm);
		ret++;
		return (0);
	}

	/*
	 ******	Arquivo N�O-diret�rio ***********************************
	 */
	if (!S_ISDIR (s.st_mode))
	{
		int		blsize;

		if (!pattern_accept (file_nm))
			return (0);

		if (s.st_nlink > 1 && proc_link (&s))
		{
			if (gflag)
				printf ("L %s\n", file_nm);

			return (0);
		}

		blsize = round_file_size_to_BL (&s);

		if (aflag && !root)
			printf (du_fmt, edit_sz_value (blsize), file_nm);

		return (blsize);
	}

	/*
	 ******	Diret�rio ***********************************************
	 */
	if ((dir_fd = inopendir (s.st_dev, s.st_ino)) == NODIR)
	{
		error ("*N�o consegui abrir o diret�rio \"%s\"", file_nm);
		ret++; return (0);
	}

	/*
	 *	L� o conte�do do diret�rio
	 */
	name_list.i_next = NONAME;

	ip = alloca (sizeof (NAME));

	while ((dp = readdir (dir_fd)) != NODIRENT)
	{
		if (dp->d_name[0] == '.')
		{
			if   (!dotflag)
				continue;
			elif (dp->d_name[1] == '\0')
				continue;
			elif (dp->d_name[1] == '.' && dp->d_name[2] == '\0')
				continue;
		}

		ip->i_nm = alloca (dp->d_namlen + 1);

		strcpy (ip->i_nm, dp->d_name);
		ip->i_len = dp->d_namlen;

		ip->i_ino = dp->d_ino;

		/*
		 *	Completa os campos de NAME
		 */
	   /***	ip->i_nm   = ... ***/	/* Acima */
	   /***	ip->i_s    = ... ***/	/* Acima */
	   /***	ip->i_next = ... ***/	/* Abaixo  */

		/*
		 *	Insere na lista
		 */
		for (lp = &name_list; lp->i_next != NONAME; lp = lp->i_next)
		{
			if (strcmp (ip->i_nm, lp->i_next->i_nm) <= 0)
				break;
		}

		ip->i_next = lp->i_next;
		lp->i_next = ip;

		ip = alloca (sizeof (NAME));	/* J� aloca um seguinte */

	}	/* end lendo o diret�rio */

	closedir (dir_fd);

	/*
	 *	Agora, processa a lista
	 */
	for (ip = name_list.i_next; ip != NONAME; ip = ip->i_next)
	{
		int	len = file_len + ip->i_len + 1;

		memnm = alloca (len + 1);

		if (streq (file_nm, "."))
		{
			strcpy (memnm, ip->i_nm);
			len = ip->i_len;
		}
		else
		{
			strcpy (memnm, file_nm);
			strcat (memnm, "/");
			strcat (memnm, ip->i_nm);
		}

		dir_total += file_analysis (memnm, len, s.st_dev, ip->i_ino, 0 /* Not root */);
	}

	/*
	 *	Terminou de processar o diret�rio
	 *	N�o esquecer de contar o tamanho do pr�prio diret�rio
	 */
	dir_total += round_file_size_to_BL (&s);

	if (dflag && !root)
		printf (du_fmt, edit_sz_value (dir_total), file_nm);

	return (dir_total);

}	/* end file_analysis */

/*
 ****************************************************************
 *	Processa LINKs						*
 ****************************************************************
 */
int
proc_link (STAT *sp)
{
	LITEM		*lp;

	for (lp = linklist; lp != (LITEM *)NULL; lp = lp->l_next)
	{
		if (lp->l_dev == sp->st_dev && lp->l_ino == sp->st_ino)
			return (1);
	}

	if ((lp = malloc (sizeof (LITEM))) == (LITEM *)NULL)
	{
		error (NOSTR);
	}
	else
	{
		lp->l_dev = sp->st_dev;
		lp->l_ino = sp->st_ino;

		lp->l_next = linklist;
		linklist = lp;
	}

	return (0);

}	/* end proc_link */

/*
 ****************************************************************
 *	Converte um n�mero dado					*
 ****************************************************************
 */
int
getintmask (const char *str)
{
	int		n, log, candidate;
	const char	*ptr;

	n = strtol (str, &ptr, 0);

	switch (*ptr)
	{
	    case 'c':
	    case 'C':
		n *= 2 * KBSZ;
		break;

	    case 'k':
	    case 'K':
		n *= KBSZ;
		break;

	    case 'b':
	    case 'B':
		n *= BLSZ;
		break;

	    case '\0':
		break;
		
	    default:
		error ("$Sufixo de n�mero inv�lido: '%c'", *ptr);

	}	/* end switch (*ptr) */

	for (candidate = 1, log = 0; /* abaixo */; candidate <<= 1, log += 1)
	{
		if (candidate == n)
			break;

		if (log >= 31)
			error ("$N�mero \"%s\" (%d) N�O � uma pot�ncia de 2", str, n);
	}

	return (n - 1);

}	/* end getintmask */

/*
 ****************************************************************
 *	Fun��o para obter o tamanho do bloco			*
 ****************************************************************
 */
int
round_file_size_to_BL (const STAT *sp)
{
	static dev_t	cache_dev = NODEV;
	static int	cache_symlink_sz;
	int		size;

	/*
	 *	Em primeiro lugar, obt�m o tamanho do bloco
	 */
	if (!blkmask_given && sp->st_dev != cache_dev)
	{
		USTAT		*up = alloca (sizeof (USTAT));

		if (ustat (sp->st_dev, up) < 0)
		{
			error
			(	"$*N�o consegui obter o estado do sistema de arquivos %d::%d",
				MAJOR (sp->st_dev), MINOR (sp->st_dev)
			);
		}

		cache_dev		= sp->st_dev;
		cache_symlink_sz	= up->f_symlink_sz;

		blkmask			= up->f_bsize - 1;
	}

	/*
	 *	Verifica o tipo de arquivo
	 */
	size = sp->st_size;

	switch (sp->st_mode & S_IFMT)
	{
	    case S_IFREG:
	    case S_IFDIR:
		break;

	    case S_IFLNK:
		if (size < cache_symlink_sz)
			return (0);

		break;

	    default:
		return (0);
	}

	/*
	 *	Agora arredonda
	 */
	return (((size + blkmask) & ~blkmask) >> BLSHIFT);

}	/* end round_file_size_to_BL */

/*
 ****************************************************************
 *	Prepara o texto com o no. de KBs			*
 ****************************************************************
 */
char *
edit_sz_value (int blocos)
{
	static char	area[16];

	if (mflag)
		sprintf (area, "%d.%02d", BLTOMB_INT (blocos), BLTOMB_DEC (blocos));
	else
		sprintf (area, "%d.%02d", BLTOKB_INT (blocos), BLTOKB_DEC (blocos));

	return (area);

}	/* end edit_sz_value */

/*
 ****************************************************************
 *	Executa a op��o "-s" (padr�es de "C")			*
 ****************************************************************
 */
void
put_s_option (void)
{
	put_p_option ("*.[cshryv]", inc_pat, &inc_pati);
	put_p_option ("*[Mm]akefile", inc_pat, &inc_pati);

}	/* end put_s_option */

/*
 ****************************************************************
 *	Executa a op��o "-p" (outros padr�es)			*
 ****************************************************************
 */
int
put_p_option (char *cp, const char *pat_vec[], int *pati_ptr)
{
	char		c;

	for (EVER)
	{
		while ((c = *cp) == ' ' || c == '\t' )
			cp++;

		if (c == '\0')
			return (0);

		if (*pati_ptr >= NPAT)
		{
			printf
			(	"%s: No momento somente aceitamos "
				XSTR (NPAT) " padr�es\n\n",
				pgname
			);
			help ();
		}

		pat_vec[(*pati_ptr)++] = cp++;

		while ((c = *cp) != '\0' && c != ' ' && c != '\t')
			cp++;

		if (c == '\0')
			return (0);

		*cp++ = '\0';

	}	/* end for (EVER) */

}	/* end put_p_option */

/*
 ****************************************************************
 *	Verifica se o nome do arquivo satisfaz um dos padr�es	*
 ****************************************************************
 */
int
pattern_accept (const char *file_nm)
{
	const char	**pp;

	/*
	 *	Agora testa os padr�es de inclus�o
	 */
	if ((pp = inc_pat)[0] != NOSTR)
	{
		for (/* vazio */; /* vazio */; pp++)
		{
			if (*pp == NOSTR)
				return (0);

			if (patmatch (file_nm, *pp))
				break;
		}
	}

	/*
	 *	Finalmente testa os padr�es de exclus�o
	 */
	if ((pp = exc_pat)[0] != NOSTR)
	{
		for (/* vazio */; *pp != NOSTR; pp++)
		{
			if (patmatch (file_nm, *pp))
				return (0);
		}
	}

	return (1);

}	/* end pattern_accept */

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
		"%s - informa sobre o uso de disco\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-dam.sN] [-b <sz>] [-p \"<p>\"] [-P \"<P>\"] [<�rvore> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-d: Informa tamb�m para cada sub�rvore\n"
		"\t-a: Informa tamb�m para cada arquivo\n"
		"\t-m: Escreve os valores em MB (ao inv�s de KB)\n"
		"\t-.: Lista tamb�m arquivos ocultos (\".old\" ...)\n"
		"\t-s: Adiciona os padr�es dos fontes em \"C\"\n"
		"\t-N: L� os nomes das <�rvore>s de \"stdin\"\n"
		"\t-b: Use <sz> como o tamanho do bloco\n"
		"\t-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o\n"
		"\t-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o\n"
		"\nObs.:\tUma <�rvore> pode tamb�m ser um arquivo normal. Se n�o for\n"
		"\tdada nenhuma <�rvore>, nem a op��o \"-N\", ser� considerado \".\".\n"
	);

	exit (2);

}	/* end help */
