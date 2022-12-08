/*
 ****************************************************************
 *								*
 *			sort.c					*
 *								*
 *	Ordena e/ou intercala arquivos				*
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

#include <sys/types.h>
#include <sys/syscall.h>

#define	DEBUG
#ifdef	DEBUG
#include <sys/kcntl.h>
#endif	DEBUG

#include <stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#include "../h/sort.h"

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 05.07.97";

#define	BLKMEM	4096

/*
 ****** Indicadores *********************************************
 */
entry int	vflag;		/* Verbose */
entry int	mflag;		/* Intercala��o */
entry int	cflag;		/* Verifica se j� est� ordenado */
entry int	tflag = 'a';	/* C�digo de caracteres */
entry int	rflag;		/* Ordena��o reversa */

/*
 ****** Vari�veis globais ***************************************
 */
entry char	delim = ' ';	/* Delimitador entre as chaves */
entry int	numkeys;	/* No. de chaves dadas */
entry FILE	*out_fp = stdout; /* Arquivo de sa�da */

/*
 ****************************************************************
 *	Ordena e/ou intercala arquivos				*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	const char	*out_nm = NOSTR;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vmcraidfo:t:k:H")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'm':			/* Intercala��o */
			mflag++;
			break;

		    case 'c':			/* J� est� ordenado? */
			cflag++;
			break;

		    case 'r':			/* Ordena��o reversa */
			rflag++;
			break;

		    case 'a':			/* c�digo LEXICOGR�FICO */
			tflag = 'a';
			break;

		    case 'i':			/* c�digo ISO */
			tflag = 'i';
			break;

		    case 'd':			/* c�digo DICION�RIO */
			tflag = 'd';
			break;

		    case 'f':			/* c�digo FOLD */
			tflag = 'f';
			break;

		    case 'o':			/* Nome do arquivo de sa�da */
			out_nm = optarg;
			break;

		    case 't':			/* Delimitador */
			delim = *optarg;
			break;

		    case 'k':			/* Chaves */
			get_keys (optarg);
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Pequena consist�ncia
	 */
	argv += optind;
	argc -= optind;

	if (!mflag && argc > 1)
		help ();

	/*
	 *	Abre o arquivo de sa�da
	 */
	if (out_nm != NOSTR && (out_fp = fopen (out_nm, "w")) == NOFILE)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui criar \"%s\" (%s)\n",
			pgname, out_nm, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Escolhe a rotina de compara��o e atribui em "compar"
	 */
	set_cmp_function ();

	/*
	 *	Se foi dada a op��o "-m" ent�o trata-se de intercala��o
	 */
	if (mflag)
		merge (argv);
	else
		sort (argv[0]);

#ifdef	DEBUG
	/*
	 *	Imprime o total de mem�ria
	 */
	if (vflag)
	{
		KPSZ	kpsz;
	
		kcntl (K_GETPSZ, &kpsz);

		fprintf
		(	stderr,
			"text = %d, data+bss = %d, stack = %d\n",
			kpsz.k_tsize, kpsz.k_dsize, kpsz.k_ssize
		);
	}
#endif	DEBUG

	return (0);

}	/* end main */

/*
 ****************************************************************
 *	Ordena							*
 ****************************************************************
 */
void
sort (const char *file_nm)
{
	register int	c, file_fd;
	register char	*ep, *cp;
	register char	**tp, **te;
	char		*file_area = NOSTR;
	char		**tag_area = NOVOID;
	int		tag_sz;
	off_t		file_sz;
	STAT		s;

	/*
	 *	L� o arquivo (come�a a �rea com um "\n")
	 */
	if (file_nm != NOSTR)
	{
		if ((file_fd = open (file_nm, O_RDONLY)) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, file_nm, strerror (errno)
			);
			exit (1);
		}

		if (fstat (file_fd, &s) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
				pgname, file_nm, strerror (errno)
			);
			exit (1);
		}

		if (!S_ISREG (s.st_mode))
		{
			fprintf (stderr, "%s: \"%s\" n�o � regular\n", pgname, file_nm);
			exit (1);
		}

		file_sz = s.st_size + 1;	/* N�o esquece o "\n" extra */

		if ((file_area = malloc (file_sz)) == NOSTR)
			{ fprintf (stderr, "Mem�ria esgotada\n"); exit (1); }

		file_area[0] = '\n';

		if (s.st_size && read (file_fd, file_area + 1, s.st_size) != s.st_size)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui ler \"%s\" (%s)\n",
				pgname, file_nm, strerror (errno)
			);
			exit (1);
		}
	}
	else		/* PIPE */
	{
		file_sz = 0;	ep = cp = NOSTR;

		while ((c = getchar ()) != EOF)
		{
			if (cp >= ep)
			{
				if ((file_area = realloc (file_area, file_sz + BLKMEM)) == NOSTR)
					{ fprintf (stderr, "Mem�ria esgotada\n"); exit (1); }

				cp = file_area + file_sz;
				ep = cp + BLKMEM;

				if (file_sz == 0) /* N�o esquece o "\n" extra */
					*cp++ = '\n';

				file_sz += BLKMEM;
			}

			*cp++ = c;
		}

		file_sz = cp - file_area;
	}
	
	if (file_sz <= 1)
	{
		fprintf (stderr, "%s: Arquivo de tamanho NULO?\n", pgname);
		exit (1);
	}

	/*
	 *	Cria os "tags"
	 */
	tag_sz = 0;	tp = te = NOVOID;

	for (cp = file_area, ep = cp + file_sz; cp < ep; cp++)
	{
		if (*cp == '\n')
		{
			if (tp >= te)
			{
				if ((tag_area = realloc (tag_area, tag_sz * sizeof (char *) + BLKMEM)) == NOVOID)
					{ fprintf (stderr, "Mem�ria esgotada\n"); exit (1); }
	
				tp = tag_area + tag_sz;
				te = tp + (BLKMEM / sizeof (char *));
	
				tag_sz += (BLKMEM / sizeof (char *));
			}

			*cp = '\0';		*tp++ = cp + 1;
		}
	}

	tp--; 	tag_sz = tp - tag_area; 	/* O �ltimo n�o existe */

	te = tp;	/* Final dos "tags" */

	if (vflag)
		fprintf (stderr, "No. de elementos = %d\n", tag_sz);

	/*
	 *	� apenas para verificar a ordena��o?
	 */
	if (cflag) for (tp = tag_area; /* abaixo */; tp++)
	{
		if (tp >= te - 1)
		{
			fprintf
			(	stderr, file_nm ?
				"O arquivo \"%s\" j� est� ordenado\n" :
				"O arquivo j� est� ordenado\n", file_nm
			);
			exit (0);
		}

		if (compar (tp[0], tp[1]) > 0)
		{
			fprintf
			(	stderr, file_nm ?
				"O arquivo \"%s\" N�O est� ordenado\n" :
				"O arquivo N�O est� ordenado\n", file_nm
			);
			exit (1);
		}
	}

	/*
	 *	Ordena
	 */
	qtsort (tag_area, tag_sz, compar);

	/*
	 *	Escreve o arquivo ordenado
	 */
	for (tp = tag_area; tp < te; tp++)
		fnputs (tp[0], out_fp);

}	/* end sort */

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
		"%s - ordena e/ou intercala arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"    %s [-vcraidf]   [-o <sa�da>] "
		"[-t <d>] [-k \"x:y.zot ... \"] [<entrada>]\n"
		"    %s -m [-vraidf] [-o <sa�da>] "
		"[-t <d>] [-k \"x:y.zot ... \"] <entrada> ...\n",
		pgname, pgversion, pgname, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-v: Verboso\n"
		"\t-m: Intercala��o (\"merge\")\n"
		"\t-c: Verifica se o arquivo j� est� ordenado\n"
		"\t-r: Ordena��o reversa (descendente)\n"
		"\t-a: Tipo de ordena��o LEXICOGR�FICO (tipo por omiss�o)\n"
		"\t-i: Tipo de ordena��o ISO\n"
		"\t-d: Tipo de ordena��o DICION�RIO\n"
		"\t-f: Tipo de ordena��o FOLD (ma�usculas = min�sculas)\n"
	);
	fprintf
	(	stderr,
		"\t-o: Escreve o arquivo ordenado em <sa�da> ao inv�s de \"stdout\"\n"
		"\t-t  Utiliza o caracter <d> ao inv�s do branco como delimitador de campos\n"
		"\t-k: Especifica chaves:\n"
		"\t\t x: No. do campo\n"
		"\t\t y: In�cio da chave dentro do campo\n"
		"\t\t z: Largura da chave\n"
		"\t\t o: Ordem ascendente/descendente (\"a\" ou \"d\")\n"
		"\t\t t: Tipo (\"a\", \"i\", \"d\", ou \"f\"), como acima\n"
		"\nObs.:\tSem op��es: ordem ascendente, tipo LEXICOGR�FICO, sa�da em \"stdout\"\n"
	);

	exit (2);

}	/* end help */
