/*
 ****************************************************************
 *								*
 *			cptree.c				*
 *								*
 *	Copia uma �rvore					*
 *								*
 *	Vers�o	1.0.2, de 06.07.87				*
 *		4.7.0, de 21.12.04				*
 *								*
 *	M�dulo: cptree						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ftw.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.7.0, de 21.12.04";

#define	NPAT	20		/* No. maximo de Padr�es */

#define	NOSTAT	(STAT *)NULL
#define	EVER	;;
#define	elif	else if
#define STR(x)	# x
#define XSTR(x)	STR (x)

/*
 ******	Indicadores *********************************************
 */
entry int	iflag;		/* Interativo */
entry int	fflag;		/* Force */
entry int	vflag;		/* Verbose */
entry int	dflag;		/* Debug */
entry int	mflag;		/* Mant�m o estado do arquivo */
entry int	lflag; 		/* N�o entra em dispositivos montados */
entry int	Lflag; 		/* N�o entra em subdiret�rios */
entry int	eflag;		/* Copia apenas os arquivos n�o existentes */
entry int	dotflag;	/* N�o ignora ".old" ... */

/*
 ******	Vari�veis globais ***************************************
 */
entry dev_t	old_dev;	/* Dispositivo do diret�rio fonte */

entry dev_t	new_dev;	/* Dispositivo do diret�rio destino */
entry ino_t	new_ino;	/* N�-�ndice do diret�rio destino */

entry int	old_dir_sz;	/* Tamanho do nome da �rvore fonte */
entry int	new_dir_sz;	/* Tamanho do nome da �rvore destino */
const char	*old_dir_nm;	/* Nome da �rvore destino */
const char	*new_dir_nm;	/* Nome da �rvore destino */

entry int	old_path_case;	/* Tipo do caminho fonte */
entry int	new_path_case;	/* Tipo do caminho fonte */

entry int	ftw_file_cnt = 0;	/* Para a op��o "-L" */

entry int	nerrors;	/* No. de erros ocorridos */

const char	**color_vector;	/* Para as cores dos modos */

/*
 ******	Os padr�es **********************************************
 */
entry const char *inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
entry int	inc_pati;

entry const char *exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
entry int	exc_pati;

/*
 ******	Estrutura de links **************************************
 */
typedef struct litem	LITEM;

struct litem
{
	const char	*l_name;	/* Nome */
	dev_t		l_dev;		/* Dispositivo */
	ino_t		l_ino;		/* No. do Inode */
	LITEM		*l_next;	/* o Proximo */
};

LITEM	*linklist;		/* Comeco da Lista */

#define	NOLITEM	(LITEM *)NULL

/*
 ******	Estrutura de modos **************************************
 */
typedef struct mode	MODE;

struct mode
{
	const char	*m_name;	/* Nome */
	STAT		m_s;		/* O estado */
	MODE		*m_next;	/* o Proximo */
};

MODE	*modelist;		/* Comeco da Lista */

#define	NOMODE	(MODE *)NULL

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int 		verdir (const char *);
int 		makedir (char *);
void 		copy_status (STAT *, STAT *, const char *);
int 		copy_analysis (const char *, STAT *, int);
void		put_s_option (void);
int		put_p_option (const char *, const char *[], int *);
int		pattern_accept (const char *);
LITEM		*proc_link (STAT *, const char *);
void		add_mode (const STAT *, const char *);
void		proc_mode_list (void);
void 		block_copy (const char *, const char *, STAT *);
char		*path_can (char *);
void		help (void);

/*
 ****************************************************************
 *	Copia uma �rvore					*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		ret, opt;
	STAT		old_s, new_s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "ifvdmlLe.sp:P:H")) != EOF)
	{
		switch (opt)
		{
		    case 'i':			/* Funcionamento interativo */
			iflag++;
			break;

		    case 'f':			/* N�o pede confirma��o */
			fflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'd':			/* Debug */
			dflag++;
			break;

		    case 'm': 			/* Dono/grupo e datas */
			mflag++;
			break;

		    case 'l':			/* N�o entra em dispositivos montados */
			lflag++;
			break;

		    case 'L':			/* N�o entra em subdiret�rios */
			Lflag++;
			break;

		    case 'e': 			/* Arquivos n�o existentes */
			eflag++;
			break;

		    case '.':			/* N�o ignora ".old" ... */
			dotflag++;
			break;

		    case 's':			/* Padr�es = 	*.[cshryv] e */
			put_s_option ();
			break;

		    case 'p':		/* Padr�es de inclus�o */
			put_p_option (optarg, inc_pat, &inc_pati);
			break;

		    case 'P':		/* Padr�es de exclus�o */
			put_p_option (optarg, exc_pat, &exc_pati);
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
	 *	Prepara o terminal
	 */
	if ((iflag || !fflag))
	{
		if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
			error ("$*N�o consegui abrir \"/dev/tty\"");

	   /***	askyesno_stderr = stdout; ***/
		askyesno_set (1);
	}

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stdout)), (void *)NULL, &color_vector);

	/*
	 *	Normaliza os caminhos
	 */
	argv[0] = path_can ((char *)argv[0]);
	argv[1] = path_can ((char *)argv[1]);

	/*
	 *	Obt�m o estado do diret�rio fonte
	 */
	if (stat (argv[0], &old_s) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", argv[0]);

	/*
	 *	Guarda o "dev" da <fonte> para evitar sair do dispositivo original
	 */
	old_dev = old_s.st_dev;

	/*
	 *	Obt�m o estado do diret�rio destino
	 */
	if (stat (argv[1], &new_s) >= 0)
	{
		if (old_s.st_ino == new_s.st_ino && old_s.st_dev == new_s.st_dev)
			error ("$\"%s\" e \"%s\" s�o a mesma �rvore", argv[0], argv[1]);
	}
	else
	{
		if (verdir ((char *)argv[1]) < 0)
			error ("$*Erro na cria��o dos diret�rios intermedi�rios de \"%s\"", argv[1]);

		if (mkdir (argv[1], old_s.st_mode) < 0)
			error ("$*Erro na cria��o do diret�rio \"%s\"", argv[1]);

		if (stat (argv[1], &new_s) < 0)
			error ("$*N�o consegui obter o estado de \"%s\"", argv[1]);

		if (mflag)
			add_mode (&old_s, argv[1]);
	}

	/*
	 *	Guarda o "ino" e "dev" do <destino> para evitar recurs�o
	 */
	new_ino = new_s.st_ino;
	new_dev = new_s.st_dev;

	/*
	 *	Prepara os nomes
	 */
	old_dir_nm = (char *)argv[0]; 	old_dir_sz = strlen (argv[0]);
	new_dir_nm = (char *)argv[1]; 	new_dir_sz = strlen (argv[1]);

	if   (streq (old_dir_nm, "/"))
		old_path_case = 0;
	elif (streq (old_dir_nm, "."))
		old_path_case = 1;
	else	/* Nem "/" nem "." */
		old_path_case = 2;

	if   (streq (new_dir_nm, "/"))
		new_path_case = 0;
	elif (streq (new_dir_nm, "."))
		new_path_case = 1;
	else	/* Nem "/" nem "." */
		new_path_case = 2;

	/*
	 *	Percorre �rvore fonte
	 */
   /***	ftw_file_cnt = 0; ***/

	ret = ftw (argv[0], copy_analysis);

	/*
	 *	Se for o caso, atualiza o modo dos diret�rios
	 */
	if (mflag)
		proc_mode_list ();

	return (ret + nerrors);

}	/* end cptree */

/*
 ****************************************************************
 *	Processa um nome 					*
 ****************************************************************
 */
int
copy_analysis (const char *old_nm, STAT *old_sp, int code)
{
	const char	*nm;
	char		*new_nm;
	LITEM		*lp;
	STAT		new_s;
	static int	not_first = 0;
	const char	*last_name;

	ftw_file_cnt++;

	/*
	 ******	Obt�m o nome do <destino> ***********************
	 */
	nm = old_nm;

	switch (old_path_case)
	{
	    case 0:		/* "/" */
		nm += 1;
		break;

	    case 1:		/* "." */
		/* vazio */;
		break;

	    default:		/* Demais */
		nm += old_dir_sz;

		if (nm[0] == '/')
			nm += 1;

		break;

	}

	new_nm = alloca (new_dir_sz + 1 + strlen (nm) + 1);

	strcpy (new_nm, new_dir_nm);

	if (new_path_case != 0)		/* Exceto "/" */
		strcat (new_nm, "/");

	strcat (new_nm, nm);

	new_nm = path_can (new_nm);

	if (dflag)
	{
		printf ("%s	=>	%s\n", old_nm, new_nm);

		if (dflag > 1)
			return (0);
	}

	/*
	 *	Obt�m o �ltimo nome do caminho fonte
	 */
	if ((last_name = strrchr (old_nm, '/')) == NOSTR)
		last_name = old_nm;
	else
		last_name++;

	/*
	 *	Obt�m o estado do <destino>
	 */
	if ((lstat (new_nm, &new_s)) < 0)
		new_s.st_mode = 0;

	/*
	 *	Identifica o <fonte> (a partir de ftw)
	 */
	switch (code)
	{
		/*
		 ******	Diret�rio *******************************
		 */
	    case FTW_D:
		if (old_sp->st_dev == new_dev && old_sp->st_ino == new_ino)
			return (1);

#if (0)	/*******************************************************/
		if (lflag && old_sp->st_dev != old_dev)
			return (1);
#endif	/*******************************************************/

		if (!dotflag)
		{
			if (patmatch (old_nm, ".!.*") || patmatch (old_nm, "*/.!.*"))
				return (1);
		}

		/*
		 *	Processa a op��o "-L"
		 */
		if (Lflag && ftw_file_cnt > 1)
			return (1);

		/*
		 *	Verifica se � interativo
		 */
		if   (iflag)
		{
			if (not_first++)
				putc ('\n', stdout);

			fprintf
			(	stderr,
				"Diret�rio \"%s\"? (n): ",
				color_vector[S_IFDIR >> 12],
				old_nm,
				color_vector[MC_DEF]
			);

			if (askyesno () <= 0)
				return (1);
		}
		elif (vflag)
		{
			if (not_first++)
				putc ('\n', stdout);

			printf
			(	"Diret�rio \"%s%s%s\":\n",
				color_vector[S_IFDIR >> 12],
				old_nm,
				color_vector[MC_DEF]
			);
		}

		/*
		 *	Verifica se o arquivo j� existe,
		 *	e por acaso � um diret�rio
		 */
		if (S_ISDIR (new_s.st_mode))
		{
			if (mflag)
				add_mode (old_sp, new_nm);

			goto check_lflag;
#if (0)	/*******************************************************/
			return (0);
#endif	/*******************************************************/
		}

		/*
		 *	Se n�o for um diret�rio ...
		 */
		if (new_s.st_mode != 0)
		{
			if (!fflag)
			{
				fprintf
				(	stderr,
					"%s: O arquivo \"%s\" deveria ser um "
					"diret�rio - remove? (n): ",
					pgname, new_nm
				);

				if (askyesno () <= 0)
					{ nerrors++; return (1); }
			}

			if (unlink (new_nm) < 0)
			{
				error ("*N�o consegui remover \"%s\"", new_nm);
				nerrors++;
				return (1);
			}
		}

		/*
		 *	Cria o diret�rio
		 */
		if (mkdir (new_nm, old_sp->st_mode) < 0)
		{
			error ("*N�o consegui criar o diret�rio \"%s\"", new_nm);
			nerrors++;
			return (1);
		}

		if (mflag)
			add_mode (old_sp, new_nm);

	   check_lflag:
		if (lflag && old_sp->st_dev != old_dev)
			return (1);
		else
			return (0);

		/*
		 ****** Arquivo normal **************************
		 */
	    case FTW_F:
		if (new_s.st_mode && eflag || !pattern_accept (old_nm))
			return (0);

	    case_FTW_F:
		if (iflag)
		{
			fprintf
			(	stderr,
				"    %s%s%s? (n): ",
				color_vector[(old_sp->st_mode & S_IFMT) >> 12],
				last_name,
				color_vector[MC_DEF]
			);

			if (askyesno () <= 0)
				return (0);
		}
		elif (vflag)
		{
			printf
			(	"    %s%s%s:\n",
				color_vector[(old_sp->st_mode & S_IFMT) >> 12],
				last_name,
				color_vector[MC_DEF]
			);
		}

		/*
		 *	Examina o nome novo
		 */
		if (new_s.st_mode)
		{
			if (S_ISDIR (new_s.st_mode))
			{
				error ("\"%s\" j� existe e � um diret�rio", new_nm);
				nerrors++;
				return (0);
			}

			if
			(	old_sp->st_dev == new_s.st_dev  &&
				old_sp->st_ino == new_s.st_ino
			)
			{
				error ("\"%s\" j� existe e � o mesmo arquivo do que \"%s\"", new_nm, old_nm);
				nerrors++;
				return (0);
			}

			if (!fflag)
			{
				fprintf
				(	stderr,
					"%s: \"%s\" j� existe. Apaga/reescreve? (n): ",
					pgname, new_nm
				);

				if (askyesno () <= 0)
					return (0);

			}

			if
			(    (old_sp->st_mode & S_IFMT) != (new_s.st_mode & S_IFMT)
			     || !S_ISREG (old_sp->st_mode)
			)
			{
				if (unlink (new_nm) < 0)
				{
					error ("*N�o consegui remover \"%s\"", new_nm);
					nerrors++;
					return (0);
				}
			}

		}	/* end if (j� existe o new_nm) */

		/*
		 *	Verifica se o arquivo � um elo f�sico na �rvore fonte
		 */
		if (old_sp->st_nlink > 1 && (lp = proc_link (old_sp, new_nm)))
		{
			if (link (lp->l_name, new_nm) < 0)
			{
				error
				(	"*N�o consegui criar o elo f�sico de \"%s\" para \"%s\"\n",
					lp->l_name, new_nm
				);
				nerrors++;
			}
			return (0);
		}

		/*
		 *	Copia o conte�do ou n�-�ndice do arquivo
		 */
		block_copy (old_nm, new_nm, old_sp);

		return (0);

		/*
		 ****** Elo simb�lico ***************************
		 */
	    case FTW_SL:
	    {
		STAT		dst_s;

		/*
		 *	Obt�m o estado do arquivo alvo
		 */
		if (stat (old_nm, &dst_s) >= 0)
		{
			if (S_ISDIR (dst_s.st_mode))	/* Diret�rio */
			{
				if (!dotflag)
				{
					if (patmatch (old_nm, ".!.*") || patmatch (old_nm, "*/.!.*"))
						return (0);
				}
			}
			else				/* Outros */
			{
				if (new_s.st_mode && eflag || !pattern_accept (old_nm))
					return (0);
			}
		}

		goto case_FTW_F;
	    }

		/*
		 ******	Arquivo ileg�vel ************************
		 */
	    case FTW_NS:
		if (new_s.st_mode && eflag || !pattern_accept (old_nm))
			return (0);

		if (iflag || vflag)
		{
			printf
			(	"    %s:	"
				"*** N�o consegui obter o estado\n",
				last_name
			);
		}
		else
		{
			error ("*N�o consegui obter o estado de \"%s\"", old_nm);
		}

		nerrors++;
		return (0);

		/*
		 ******	Diret�rio ileg�vel **********************
		 */
	    case FTW_DNR:
		if (dotflag == 0)
		{
			if (old_nm[0]=='.' && old_nm[1]!='.' && old_nm[1]!='\0')
				return (1);

			if (patmatch (old_nm, "*/.!.*"))
				return (1);
		}

		if (iflag || vflag)
		{
			if (not_first++)
				putc ('\n', stdout);

			printf
			(	"Diret�rio \"%s\":	"
				"*** N�o consegui abrir para leitura\n",
				old_nm
			);
		}
		else
		{
			error ("*N�o consegui ler o diret�rio \"%s\"", old_nm);
		}

		nerrors++;
		return (1);

	    default:
		error ("C�digo %d inv�lido da \"ftw\" para \"%s\"", code, old_nm);
		nerrors++;
		return (0);

	}	/* end switch */

}	/* end copy_analysis */

/*
 ****************************************************************
 *	Copia os blocos (ou o n�-�ndice) do arquivo		*
 ****************************************************************
 */
void
block_copy (const char *old_nm, char const *new_nm, STAT *old_sp)
{
	int		fdin, fdout;
	int		count;
	char		area[BL4SZ];

	if (dflag)
		printf ("=> block_copy (%s, %s)\n", old_nm, new_nm);

	/*
	 *	Analisa o tipo do arquivo
	 */
	switch (old_sp->st_mode & S_IFMT)
	{
		/*
		 ****** Arquivo regular: Copia bloco a bloco ****
		 */
	    case S_IFREG:
		if ((fdout = creat (new_nm, old_sp->st_mode)) < 0)
		{
			error ("*N�o consegui criar o arquivo \"%s\"", new_nm);
			nerrors++;
			return;
		}

		if ((fdin = inopen (old_sp->st_dev, old_sp->st_ino)) < 0)
		{
			error ("*N�o consegui abrir o arquivo \"%s\"", old_nm);
			close (fdout);
			nerrors++;
			return;
		}

		while ((count = read (fdin, area, sizeof (area))) > 0)
		{
			if (write (fdout, area, count) != count)
			{
				error ("*Erro de escrita em \"%s\"", new_nm);
				close (fdin);
				close (fdout);
				nerrors++;
				return;
			}
		}

		close (fdin);
		close (fdout);

		if (count < 0)
		{
			error ("*Erro de leitura em \"%s\"", old_nm);
			nerrors++;
			return;
		}

		break;

		/*
		 ****** Arquivo especial: Recria ****************
		 */
	    case S_IFBLK:
	    case S_IFCHR:
	    case S_IFIFO:
		if (mknod (new_nm, old_sp->st_mode, old_sp->st_rdev) < 0)
		{
			error ("*N�o consegui criar \"%s\"", new_nm);
			nerrors++;
			return;
		}

		break;

		/*
		 ****** Elo simb�lico ***************************
		 */
	    case S_IFLNK:
	    {
		char		*symlink_nm;

		symlink_nm = alloca (old_sp->st_size + 1);

		if (readlink (old_nm, symlink_nm, old_sp->st_size + 1) < 0)
		{
			error ("*N�o consegui obter o conte�do do elo simb�lico de \"%s\"", old_nm);
			nerrors++;
			return;
		}

		if (symlink (symlink_nm, new_nm) < 0)
		{
			error ("*N�o consegui criar o elo simb�lico \"%s\"", new_nm);
			nerrors++;
			return;
		}

		return;
	    }

	    default:
		error ("Tipo do arquivo \"%s\" inv�lido", old_nm);
		nerrors++;
		return;

	}	/* end switch */

	/*
	 *	Atualiza o estado
	 */
	if (mflag)
		copy_status (old_sp, NOSTAT, new_nm);

}	/* end block_copy */

/*
 ****************************************************************
 *	Processa LINKs						*
 ****************************************************************
 */
LITEM *
proc_link (STAT *old_spp, const char *new_nm)
{
	LITEM		*lp;
	char		*cp;

	for (lp = linklist; lp != NOLITEM; lp = lp->l_next)
	{
		if (lp->l_dev == old_spp->st_dev && lp->l_ino == old_spp->st_ino)
			return (lp);
	}

	if
	(	(lp = malloc (sizeof (LITEM))) == NOLITEM ||
		(cp = strdup (new_nm)) == NOSTR
	)
	{
		error ("N�o obtive mem�ria para estrutura de elo f�sico");
		nerrors++;
	}
	else
	{
		lp->l_name = cp;
		lp->l_dev  = old_spp->st_dev;
		lp->l_ino  = old_spp->st_ino;

		lp->l_next = linklist;
		linklist = lp;
	}

	return (NOLITEM);

}	/* end proc_link */

/*
 ****************************************************************
 *	Adiciona um MODO na lista				*
 ****************************************************************
 */
void
add_mode (const STAT *sp, const char *nm)
{
	MODE		*mp;
	char		*cp;

	if
	(	(mp = malloc (sizeof (MODE))) == NOMODE ||
		(cp = strdup (nm)) == NOSTR
	)
	{
		error ("N�o obtive mem�ria para item de modo");
		nerrors++;
	}
	else
	{
		mp->m_name = cp;
		memmove (&mp->m_s, sp, sizeof (STAT));

		mp->m_next = modelist;
		modelist = mp;
	}

}	/* end add_mode */

/*
 ****************************************************************
 *	Altera os modos dos diret�rios da lista de modos	*
 ****************************************************************
 */
void
proc_mode_list (void)
{
	MODE		*mp;

	for (mp = modelist; mp != NOMODE; mp = mp->m_next)
		copy_status (&mp->m_s, NOSTAT, mp->m_name);

}	/* end proc_mode_list */

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
put_p_option (const char *cp, const char *pat_vec[], int *pati_ptr)
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
			error ("No momento somente aceitamos " XSTR (NPAT) " padr�es\n");
			help ();
		}

		pat_vec[(*pati_ptr)++] = cp++;

		while ((c = *cp) != '\0' && c != ' ' && c != '\t')
			cp++;

		if (c == '\0')
			return (0);

		*(char *)cp++ = '\0';

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
	 *	Testa em primeiro lugar os pontos
	 */
	if (!dotflag)
	{
		if (patmatch (file_nm, ".!.*") || patmatch (file_nm, "*/.!.*"))
			return (0);
	}

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
 *	Cria os Diret�rios intemedi�rios faltando		*
 ****************************************************************
 */
int
verdir (const char *filenm)
{
	char		*cp;

	/*
	 *	Percorre o nome dado analisando todos os diret�rios
	 */
	for (cp = (char *)(filenm + 1); *cp != '\0'; cp++)
	{
		if (*cp == '/')
		{
			*cp = '\0';

			if (access (filenm, F_OK) < 0)
			{
				if (mkdir (filenm, 0777) < 0)
					{ *cp = '/'; return (-1); }
			}

			*cp = '/';

		}	/* end if */

	}	/* end for */

	return (0);

}	/* end verdir */

/*
 ****************************************************************
 *	Copia o grupo/dono, ...					*
 ****************************************************************
 */
void
copy_status (STAT *old_sp, STAT *new_sp, const char *new_nm)
{
	STAT		s;

	if (new_sp == NOSTAT)
	{
		new_sp = &s;

		if (stat (new_nm, new_sp) < 0)
		{
			error ("*N�o consegui obter o estado de \"%s\"", new_nm);
			nerrors++;
			return;
		}
	}

	if ((old_sp->st_mode & ~S_IFMT) != (new_sp->st_mode & ~S_IFMT))
	{
		if (chmod (new_nm, old_sp->st_mode & ~S_IFMT) < 0)
		{
			error ("*N�o consegui restaurar a prote��o de \"%s\"", new_nm);
			nerrors++;
		}
	}

	if (utime (new_nm, &old_sp->st_atime) < 0)
	{
		error ("*N�o consegui restaurar os tempos de \"%s\"", new_nm);
		nerrors++;
	}

	if (old_sp->st_uid != new_sp->st_uid || old_sp->st_gid != new_sp->st_gid)
	{
		if (chown (new_nm, old_sp->st_uid, old_sp->st_gid) < 0)
		{
			error ("*N�o consegui restaurar o dono/grupo de \"%s\"", new_nm);
			nerrors++;
		}
	}

}	/* end copy_status */

/*
 ****************************************************************
 *	Normaliza um caminho					*
 ****************************************************************
 */
char *
path_can (char *path)
{
	char		*cp;

	for (cp = strend (path) - 1; /* abaixo */; /* abaixo */)
	{
		if (cp <= path)
			break;

		if   (cp[0] == '/')
			{ *cp = '\0'; cp--; }
		elif (cp[0] == '.' && cp[-1] == '/')
			{ *cp = '\0'; cp--; }
		else
			break;
	}

	while (path[0] == '.' && path[1] == '/')
		path += 2;

	return (path);

}	/* end path_can */

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
		"%s - copia uma �rvore\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-ifvmLe.] <PAD> <�rvore fonte> <�rvore destino>\n\n"
		"\tValores de <PAD>: [-s] [-p \"<p>\"] [-P \"<P>\"]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: Pede a confirma��o para cada arquivo a copiar\n"
		"\t-f: Os arquivos destino existentes s�o removidos "
			"silenciosamente\n"
		"\t-v: Lista o nome dos arquivos copiados\n"
		"\t-m: Copia o dono, grupo, prote��o e datas do arquivo\n"
		"\t-l: N�o entra em dispositivos montados\n"
		"\t-L: N�o entra em subdiret�rios\n"
		"\t-e: Copia apenas os arquivos n�o existentes no destino\n"
		"\t-.: Copia tamb�m arquivos ocultos (\".old\" ...)\n"
		"\t-s: Adiciona os padr�es dos fontes em \"C\"\n"
		"\t-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o\n"
		"\t-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o\n"
	);

	exit (2);

}	/* end help */
