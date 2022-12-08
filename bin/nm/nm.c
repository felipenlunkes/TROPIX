/*
 ****************************************************************
 *								*
 *			nm.c					*
 *								*
 *	Imprime a tabela de s�mbolos de m�dulos objeto		*
 *								*
 *	Vers�o	2.0.0, de 09.05.88				*
 *		4.2.0, de 08.05.02				*
 *								*
 *	M�dulo: nm						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stat.h>
#include <a.out.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 08.05.02";

#define	elif	else if

entry int	exit_code = 0;	/* C�digo de retorno */

/*
 ******	Indicadores *********************************************
 */
entry int	gflag;		/* Lista somente as vari�veis globais */

entry int	uflag;		/* Lista as vari�veis indefinidas */
entry int	tflag;		/* Lista TEXT */
entry int	dflag;		/* Lista DATA */
entry int	bflag;		/* Lista BSS */
entry int	cflag;		/* Lista COMMON */
entry int	aflag;		/* Lista ABS */
entry int	rflag;		/* Lista REG */
entry int	fflag;		/* Lista somente nomes dos m�dulos */

entry int	flag_sum;	/* N�mero de regi�es acima a listar */

entry int	oflag;		/* Mostra o nome do m�dulo */
entry int	nflag; 		/* Ordena numericamente */
entry int	sflag = +1;	/* Ord. decres. (-1), n�o (0), cres. (+1) */

entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */
entry int	szflag;		/* Imprime o tamanho do campo */

/*
 ****** Vari�veis globais ***************************************
 */
entry SYM	**symtb_vec;	/* ponteiros para os elementos de tbsimb */

#define NOSYM (SYM *)NULL

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		mod_proc (const char *);
int		mod_open (const char *, HEADER *);
int		table_read (const char *, int, HEADER *);
int		symbol_type (SYM *);
int		sym_compare (SYM *, SYM *);
void		table_print (const char *, int, HEADER *);
void		help (void);

/*
 ****************************************************************
 *	Imprime a tabela de s�mbolos de m�dulos objeto		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, num;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "gutdbcarfonepvNH")) != EOF)
	{
		switch (opt)
		{
		    case 'g':			/* Vari�veis globais */
			gflag++;
			break;

		    case 'u':			/* Vari�veis indefinidas */
			uflag++;
			break;

		    case 't':			/* Vari�veis do texto */
			tflag++;
			break;

		    case 'd':			/* Vari�veis do data */
			dflag++;
			break;

		    case 'b':			/* Vari�veis do bss */
			bflag++;
			break;

		    case 'c':			/* COMMON */
			cflag++;
			break;

		    case 'a':			/* ABS */
			aflag++;
			break;

		    case 'r':			/* REG */
			rflag++;
			break;

		    case 'f':			/* Nomes de m�dulos */
			fflag++;
			break;

		    case 'o':			/* Lista o nome do m�dulo */
			oflag++;
			break;

		    case 'n':			/* Ordenar num�ricamente */
			nflag++;
			break;

		    case 'e':			/* Ordena��o decrescente */
			sflag = -1;
			break;

		    case 'p':			/* N�o ordena */
			sflag = 0;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

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
	flag_sum = uflag + tflag + dflag + bflag + cflag + aflag + rflag + fflag;

	if (flag_sum == 0)
	{
		uflag++; tflag++; dflag++; bflag++;
		cflag++; aflag++; rflag++; fflag++;

		flag_sum = 8;
	}

	if (nflag && sflag == 0)
	{
		error ("Op��es conflitantes\n");
		help ();
	}

	/*
	 *	Analisa o size flag
	 */
	if (nflag && sflag == 1 && flag_sum == 1 && tflag + dflag + bflag)
		szflag++;

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag)
	{
		if (*argv != NOSTR)
		{
			error ("Os argumentos sup�rfluos ser�o ignorados");
			*argv = NOSTR;
		}
	}
	else
	{
		if (*argv == NOSTR)
		{
			mod_proc ("a.out");

			exit (exit_code);
		}
	}

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR) 		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		for (num = 0; fngets (area, 1024, stdin) != NOSTR; num++)
		{
			if (!oflag)
			{
				if (num != 0)
					printf ("\n");
				
				printf ("%s:\n", area);
			}
	
			mod_proc (area);
		}
	}
	else				/* Foram dados argumentos */
	{
		for (num = 0; *argv; argv++, num++)
		{
			if (argc > 1  &&  !oflag)
			{
				if (num != 0)
					printf ("\n");
				
				printf ("%s:\n", *argv);
			}
	
			mod_proc (*argv);
		}
	}

	return (exit_code);

}	/* end nm */

/*
 ****************************************************************
 *	Processa um m�dulo					*
 ****************************************************************
 */
void
mod_proc (const char *mod_nm)
{
	int		mod_fd, n_sym;
	HEADER		h;

	/*
	 *	Verifica se consegue abrir o m�dulo
	 */
	if ((mod_fd = mod_open (mod_nm, &h)) < 0)
		{ exit_code++; return; }

	/*
	 *	Imprime os s�mbolos do m�dulo
	 */
	if ((n_sym = table_read (mod_nm, mod_fd, &h)) < 0)
		exit_code++;
	else
		table_print (mod_nm, n_sym, &h);

	close (mod_fd);

}	/* end prodmod */

/*
 ****************************************************************
 *	Abre o m�dulo						*
 ****************************************************************
 */
int
mod_open (const char *mod_nm, HEADER *hp)
{	
	int		mod_fd, sz;
	STAT		s;

	/*
	 *	Abre o m�dulo
	 */
	if ((mod_fd = open (mod_nm, O_RDONLY)) < 0 || fstat (mod_fd, &s) < 0)
	{
		error ("*N�o consegui abrir \"%s\"", mod_nm);
		return (-1);
	}

	/*
	 *	Verifica se � um arquivo regular
 	 */
	if (!S_ISREG (s.st_mode))
	{
		error ("\"%s\" n�o � um arquivo regular", mod_nm);
		close (mod_fd); return (-1);
	}

	/*
	 *	L� o header do m�dulo e verifica se � um m�dulo objeto
 	 */
	if ((sz = read (mod_fd, hp, sizeof (HEADER))) < 0)
	{
		error ("*Erro de leitura no cabe�alho de \"%s\"", mod_nm);
		close (mod_fd); return (-1);
	}

	if
	(	sz != sizeof (HEADER) ||
		hp->h_magic != FMAGIC  &&  hp->h_magic != NMAGIC  &&  hp->h_magic != SMAGIC
	)
	{
		error ("\"%s\" n�o � um m�dulo objeto", mod_nm);
		close (mod_fd); return (-1);
	}

	/*
	 *	Verifica se possui tabela de s�mbolos
	 */
	if (hp->h_ssize == 0)
	{
		error ("\"%s\" n�o possui tabela de s�mbolos", mod_nm);
		close (mod_fd); return (-1);
	}

	return (mod_fd);

}	/* end mod_open */	

/*
 ****************************************************************
 *	L� a tabela de s�mbolos					*
 ****************************************************************
 */
int
table_read (const char *mod_nm, int mod_fd, HEADER *hp)
{
	SYM		*sp, *end_symtb;
	int		symtb_sz = 0, n_sym = 0;
	static SYM	*symtb;

	/*
	 *	Libera �rea utilizada anteriormente
	 */
	if (symtb != NOSYM)
		free (symtb);

	if (symtb_vec != (SYM **)NULL)
		free (symtb_vec);

	/*
	 *	L� a tabela
	 */
	if ((symtb = malloc (hp->h_ssize)) == NOSYM)
	{
		error ("N�o h� mem�ria suficiente para a tabela de s�mbolos de \"%s\"", mod_nm);
		return (-1);
	}

	lseek (mod_fd, hp->h_tsize + hp->h_dsize, L_CUR);

	if (read (mod_fd, symtb, hp->h_ssize) != hp->h_ssize)
	{
		error ("Erro de leitura em \"%s\"", mod_nm);
		return (-1);
	}

	/*
	 *	Conta o n�mero de entradas
	 */
	for
	(	sp = symtb, end_symtb = (SYM *)((int)symtb + hp->h_ssize);
		sp < end_symtb;
		sp = SYM_NEXT_PTR (sp)
	)
	{
		symtb_sz++;
	}

	if (sp != end_symtb)
		error ("Erro de fase na tabela de s�mbolos de \"%s\"", mod_nm);

	/*
	 *	Aloca o vetor de ponteiros
	 */
	if ((symtb_vec = malloc (symtb_sz * sizeof (SYM *))) == (SYM **)NULL)
	{
		error ("N�o h� mem�ria suficiente para a tabela de s�mbolos de \"%s\"", mod_nm);
		return (-1);
	}

	/*
	 *	Cria o vetor de ponteiros
	 */
	for
	(	sp = symtb, end_symtb = (SYM *)((int)symtb + hp->h_ssize);
		sp < end_symtb;
		sp = SYM_NEXT_PTR (sp)
	)
	{
		int		type;

		if ((type = symbol_type (sp)) < 0)
			continue;

		sp->s_type = type;

		symtb_vec[n_sym++] = sp;
	}

	return (n_sym);

}	/* end table_read */

/*
 ****************************************************************
 *	Identifica o tipo do s�mbolo				*
 ****************************************************************
 */
int
symbol_type (SYM *sp)
{
	/*
	 *	Identifica tipos incompat�veis com as op��es
	 */
	if (gflag  &&  (sp->s_type & EXTERN) == 0)
		return (-1);

	/*
	 *	Classifica o tipo
	 */
	switch (sp->s_type)
	{
	    case UNDEF:
		if (sp->s_value != 0)
		{
			if (cflag)
				return ('c');
		}
		else
		{
			if (uflag)
				return ('u');
		}
		break;

	    case UNDEF|EXTERN:
		if (sp->s_value != 0)
		{
			if (cflag)
				return ('C');
		}
		else
		{
			if (uflag)
				return ('U');
		}
		break;

	    case ABS:
		if (aflag)
			return ('a');
		break;

	    case ABS|EXTERN:
		if (aflag)
			return ('A');
		break;

	    case REG:
		if (rflag)
			return ('r');
		break;

	    case REG|EXTERN:
		if (rflag)
			return ('R');
		break;

	    case TEXT:
		if (tflag)
			return ('t');
		break;

	    case TEXT|EXTERN:
		if (tflag)
			return ('T');
		break;

	    case DATA:
		if (dflag)
			return ('d');
		break;

	    case DATA|EXTERN:
		if (dflag)
			return ('D');
		break;

	    case BSS:
		if (bflag)
			return ('b');
		break;

	    case BSS|EXTERN:
		if (bflag)
			return ('B');
		break;

	    case SFILE:
	    case SFILE|EXTERN:
		if (fflag)
			return ('F');
		break;

	    default:
		return ('?');

	} 	/* end switch (sp->s_type) */

	return (-1);

}	/* end symbol_type */

/*
 ****************************************************************
 *	Fun��o de compara��o alfab�tica crescente		*
 ****************************************************************
 */
int
sym_compare_alpha_up (const void *vp1, const void *vp2)
{
	const SYM	*sp1 = vp1, *sp2 = vp2;

#define	FOLD
#ifdef	FOLD
	return (strttcmp (sp1->s_name, sp2->s_name, cmpfoldtb, cmpafoldtb));
#else
	return (strcmp (sp1->s_name, sp2->s_name));
#endif	FOLD

}	/* end sym_compare_alpha_up */

/*
 ****************************************************************
 *	Fun��o de compara��o alfab�tica decrescente		*
 ****************************************************************
 */
int
sym_compare_alpha_down (const void *vp1, const void *vp2)
{
	const SYM	*sp1 = vp1, *sp2 = vp2;

#ifdef	FOLD
	return (strttcmp (sp2->s_name, sp1->s_name, cmpfoldtb, cmpafoldtb));
#else
	return (strcmp (sp2->s_name, sp1->s_name));
#endif	FOLD

}	/* end sym_compare_alpha_down */

/*
 ****************************************************************
 *	Fun��o de compara��o num�rica crescente			*
 ****************************************************************
 */
int
sym_compare_num_up (const void *vp1, const void *vp2)
{
	const SYM	*sp1 = vp1, *sp2 = vp2;
	int		diff;

	if ((diff = sp1->s_value - sp2->s_value) != 0)
		return (diff);

#ifdef	FOLD
	return (strttcmp (sp1->s_name, sp2->s_name, cmpfoldtb, cmpafoldtb));
#else
	return (strcmp (sp1->s_name, sp2->s_name));
#endif	FOLD

}	/* end sym_compare_num_up */

/*
 ****************************************************************
 *	Fun��o de compara��o num�rica decrescente		*
 ****************************************************************
 */
int
sym_compare_num_down (const void *vp1, const void *vp2)
{
	const SYM	*sp1 = vp1, *sp2 = vp2;
	int		diff;

	if ((diff = sp2->s_value - sp1->s_value) != 0)
		return (diff);

#ifdef	FOLD
	return (strttcmp (sp2->s_name, sp1->s_name, cmpfoldtb, cmpafoldtb));
#else
	return (strcmp (sp2->s_name, sp1->s_name));
#endif	FOLD

}	/* end sym_compare_num_down */

/*
 ****************************************************************
 *	Lista os s�mbolos					*
 ****************************************************************
 */
void
table_print (const char *mod_nm, int n_sym, HEADER *hp)
{
	int	i, sz;
	SYM	*sp;
	SYM	**spp;

	/*
	 *	Ordena os s�mbolos
	 */
	if   (sflag > 0)	/* Crescente */
	{
		if (nflag)
			qtsort (symtb_vec, n_sym, sym_compare_num_up);
		else
			qtsort (symtb_vec, n_sym, sym_compare_alpha_up);
	}
	elif (sflag < 0)	/* Decrescente */
	{
		if (nflag)
			qtsort (symtb_vec, n_sym, sym_compare_num_down);
		else
			qtsort (symtb_vec, n_sym, sym_compare_alpha_down);
	}

	/*
	 *	Percorre os s�mbolos, listando-os
	 */
	for
	(	i = n_sym, spp = symtb_vec;
		i > 0;
		i--, spp++
	)
	{
		/*
		 *	Imprime o nome do s�mbolo
		 */
		sp = *spp;

		if (oflag)
			printf ("%s:\t", mod_nm);

		if (!uflag || flag_sum != 1)
		{
			if (sp->s_type == 'u'  ||  sp->s_type == 'U')
				printf ("         ");
			else
				printf ("%P", sp->s_value);
		}

		/*
		 *	Se for ordena��o num�rica crescente,
		 *	imprime o tamanho do elemento
		 */
		if (szflag)
		{
			if (i > 1)
			{
				sz = spp[1]->s_value - sp->s_value;
			}
			else
			{
				int		End = 0;

				switch (sp->s_type)
				{
				    case 't':
				    case 'T':
					End = hp->h_tsize;
					break;

				    case 'd':
				    case 'D':
					End = hp->h_dsize + hp->h_tsize;
					break;

				    case 'b':
				    case 'B':
					End = hp->h_bsize +
					      hp->h_dsize + hp->h_tsize;
					break;
				}

				sz = End - sp->s_value;
			}

			/*
			 *	Um teste levemente arbitr�rio
			 */
			if (sz < 0  ||  sz > 0x100000)
				printf ("        ");
			else
				printf (" %6d ", sz);
		}

		/*
		 *	Imprime o tipo e o nome do s�mbolo
		 */
		printf ("  %c  %s\n", sp->s_type, sp->s_name);
	}

}	/* end table_print */

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
		"%s - imprime a tabela de s�mbolos de m�dulos objeto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-gutdbcarfonepN] [<m�dulo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Sem nenhuma das op��es \"-utdbcarf\", "
			"imprime todos os s�mbolos\n"
		"\t-g: Imprime somente os s�mbolos globais\n"

		"\t-u: Imprime os s�mbolos indefinidos\n"
		"\t-t: Imprime os s�mbolos do TEXT\n"
		"\t-d: Imprime os s�mbolos do DATA\n"
		"\t-b: Imprime os s�mbolos do BSS\n"
		"\t-c: Imprime os s�mbolos do COMMON\n"
		"\t-a: Imprime os s�mbolos absolutos\n"
		"\t-r: Imprime os nomes de registros\n"
		"\t-f: Imprime os nomes de m�dulos\n"

		"\t-o: Imprime o nome do <m�dulo> para cada s�mbolo\n"
		"\t-n: Ordena os s�mbolos numericamente pelo valor\n"
		"\t    (normalmente os s�mbolos s�o ordenados pelo nome)\n"
		"\t-e: Ordena decrescentemente\n"
		"\t-p: N�o ordena os s�mbolos\n"
		"\t-N: L� os nomes dos <m�dulo>s de \"stdin\"\n"

	);

	exit (2);

}	/* end help */
