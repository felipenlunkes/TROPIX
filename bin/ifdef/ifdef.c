/*
 ****************************************************************
 *								*
 *			ifdef.c					*
 *								*
 *	Realiza o pr�processamento apenas de "ifdef"		*
 *								*
 *	Vers�o	2.0.0, de 14.09.88				*
 *		4.2.0, de 08.05.02				*
 *								*
 *	M�dulo: ifdef						*
 *		Utilit�rios Secretos				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stat.h>
#include <ctype.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	LINESZ	512		/* Tamanho da linha */

#define	DEFSZ	20		/* No. m�ximo de definic�es */
#define RESSZ	100		/* No. m�ximo de residuais */

#define elif	else if

entry const char	pgversion[] =  "Vers�o:	4.2.0, de 08.05.02";

entry int		vflag;		/* Verbose */
entry int		rflag;		/* Vari�veis residuais */
entry int		Nflag;		/* Nomes do <stdin> */

/*
 ******	Vari�veis globais ***************************************
 */
entry char		buf[LINESZ];	/* �rea de entrada/sa�da */

entry const char	*dir;		/* O �ltimo argumento � um diret�rio */

entry char		outnm_line[LINESZ]; /* Nomes de sa�da */

entry FILE		*infp, *outfp;	/* Ponteiros dos arquivos de entrada/sa�da */

entry int		defi;		/* No. de "defines" */

entry const char	*defvar[DEFSZ];	/* As vari�veis definidas */

entry int		undefi;		/* No. de "undefs" */

entry const char	*undefvar[DEFSZ]; /* As vari�veis indefinidas */

entry char		stack[100];	/* Stack de "ifdefs", etc ... */

entry char		*stackp = stack; /* Ponteiro do Stack */

entry int		falselevel;	/* No. de Condicionais FALSE aninhadas */

entry char		*resvar[RESSZ];	/* Vari�veis residuais */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		procfile (const char *, const char *);
int		metaline (const char *);
int		vargiven (const char *, char *, int);
void		resvarpr (void);
void		help (void);

/*
 ****************************************************************
 *	Programa de pr�processar "ifdef"			*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	int		opt;
	const char	*cp;
	STAT		s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vrND:U:H")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'r':			/* Vari�veis residuais */
			rflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 'D':			/* Defini��es */
			if (defi >= DEFSZ)
				error ("$No momento somente aceitamos %d defini��es\n",	DEFSZ);

			defvar[defi++] = optarg;
			break;

		    case 'U':			/* Indefini��es */
			if (undefi >= DEFSZ)
				error ("$No momento somente aceitamos %d indefini��es\n", DEFSZ);

			undefvar[undefi++] = optarg;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();
		}

	}

	argv += optind;
	argc -= optind;

	/*
	 *	Verifica se o �ltimo argumento � um diret�rio
	 */
	if (argc != 0 && stat (argv[argc-1], &s) == 0 && S_ISDIR (s.st_mode))
		{ dir = argv[argc-1]; argv[argc-1] = NOSTR; }

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag)
	{
		if (argc != 1 || !dir)
			help ();

		/*
		 *	Le os argumentos do "stdin"
		 */
		while (fngets (buf, sizeof (buf), stdin) != NOSTR)
		{
			if ((cp = strrchr (buf, '/')) == NOSTR)
				cp = buf;
			else
				cp++;

			strcpy (outnm_line, dir);
			strcat (outnm_line, "/");
			strcat (outnm_line, cp);

			procfile (buf, outnm_line);
		}

		resvarpr ();

		exit (0);
	}

	/*
	 *	Foi dado o diret�rio
	 */
	if (dir)
	{
		if (argc < 2)
			help ();

		/*
		 *	Processa os argumentos dados
		 */
		for (/* vazio */; *argv; argv++)
		{
			if ((cp = strrchr (*argv, '/')) == NOSTR)
				cp = *argv;
			else
				cp++;

			strcpy (outnm_line, dir);
			strcat (outnm_line, "/");
			strcat (outnm_line, cp);

			procfile (*argv, outnm_line);
		}

		resvarpr ();

		exit (0);
	}

	/*
	 *	Processa o caso da sa�da padr�o
	 */
	if (argc == 1)
	{
		procfile (argv[0], "*");

		resvarpr ();

		exit (0);
	}

	/*
	 *	Processa o caso de 2 arquivos
	 */
	if (argc == 2)
	{
		procfile (argv[0], argv[1]);

		resvarpr ();

		exit (0);
	}

	help ();

}	/* end ifdef */

/*
 ****************************************************************
 *	Processa um arquivo					*
 ****************************************************************
 */
void
procfile (const char *innm, const char *outnm)
{
	if (vflag)
		fprintf (stderr, "%s:\n", innm);

	if ((infp = fopen (innm, "r")) == NOFILE)
	{
		error ("*N�o consegui abrir \"%s\" (%s)\n", innm);
		return;
	}

	if   (*outnm == '*')
	{
		outfp = stdout;
	}
	elif ((outfp = fopen (outnm, "w")) == NOFILE)
	{
		error ("*N�o consegui abrir \"%s\" (%s)\n", outnm);
		fclose (infp);
		return;
	}

	falselevel = 0; stackp = stack;

	while (fngets (buf, LINESZ, infp) == buf)
	{
		if   (buf[0] == '#')
		{
			if (metaline (innm))
				continue;
		}
		elif (falselevel)
		{
			continue;
		}

		fnputs (buf, outfp);
	}

	if (stackp != stack)
		error ("Faltaram \"endif's\" no arquivo \"%s\"", innm);

	fclose (infp);

	if (*outnm != '*')
		fclose (outfp);

}	/* end procfile */

/*
 ****************************************************************
 *	Analisa a diretiva de pr�processamento			*
 ****************************************************************
 */
int
metaline (const char *innm)
{
	char		*cp, *begin, *End;
	int		c;

	/*
	 *	Retorna:
	 *	  0    => Copia a linha
	 *	  <> 0 => Ignora a linha
	 */
	cp = buf + 1;

	while ((c = *cp) == ' ' || c == '\t')
		cp++;

	if   (strncmp (cp, "define", 6) == 0)
	{
		/*
		 *	"#define"
		 */
		cp += 6;

		while ((c = *cp) == ' ' || c == '\t')
			cp++;

		if ((c = *cp) != '_' && c != '$' && !isalnum (c))
		{
			fprintf
			(	stderr,
				"**** Nome de vari�vel inv�lida\n"
			);
		}

		begin = cp;

		while ((c = *cp) == '_' || c == '$' || isalnum (c))
			cp++;

		End = cp;

		switch (vargiven (begin, End, 0 /* N�o residual */))
		{
		    case -1:	/* Na lista de indefinidos */
			break;

		    case 1:	/* Na lista de definidos */
			break;

		    default:	/* Neutro: n�o est� em nenhuma lista */
			return (falselevel);
		}

		/*
		 *	Elimina a linha seguinte, se � em branco
		 */
		if ((c = getc (infp)) != '\n' && c != EOF)
			ungetc (c, infp);

		return (1);
	}
	elif (strncmp (cp, "undef", 5) == 0)
	{
		/*
		 *	"#undef"
		 */
		cp += 5;

		while ((c = *cp) == ' ' || c == '\t')
			cp++;

		if ((c = *cp) != '_' && c != '$' && !isalnum (c))
		{
			fprintf
			(	stderr,
				"**** Nome de vari�vel inv�lida\n"
			);
		}

		begin = cp;

		while ((c = *cp) == '_' || c == '$' || isalnum (c))
			cp++;

		End = cp;

		switch (vargiven (begin, End, 0 /* N�o residual */))
		{
		    case -1:	/* Na lista de indefinidos */
			break;

		    case 1:	/* Na lista de definidos */
			break;

		    default:	/* Neutro: n�o est� em nenhuma lista */
			return (falselevel);
		}

		/*
		 *	Elimina a linha seguinte, se � em branco
		 */
		if ((c = getc (infp)) != '\n' && c != EOF)
			ungetc (c, infp);

		return (1);
	}
	elif (strncmp (cp, "ifdef", 5) == 0)
	{
		/*
		 *	"#ifdef"
		 */
		cp += 5;

		while ((c = *cp) == ' ' || c == '\t')
			cp++;

		if ((c = *cp) != '_' && c != '$' && !isalnum (c))
		{
			fprintf
			(	stderr,
				"**** Nome de vari�vel inv�lida\n"
			);
		}

		begin = cp;

		while ((c = *cp) == '_' || c == '$' || isalnum (c))
			cp++;

		End = cp;

		switch (vargiven (begin, End, 1 /* Residual */))
		{
		    case -1:	/* Na lista de indefinidos */
			*stackp++ = 'U';
			falselevel++;
			return (1);

		    case 1:	/* Na lista de definidos */
			*stackp++ = 'D';
			return (1);

		    default:	/* Neutro: n�o est� em nenhuma lista */
			*stackp++ = 'N';
			return (falselevel);
		}
	}
	elif (strncmp (cp, "ifndef", 6) == 0)
	{
		/*
		 *	"#ifndef"
		 */
		cp += 6;

		while ((c = *cp) == ' ' || c == '\t')
			cp++;

		if ((c = *cp) != '_' && c != '$' && !isalnum (c))
		{
			fprintf
			(	stderr,
				"**** Nome de vari�vel inv�lida\n"
			);
		}

		begin = cp;

		while ((c = *cp) == '_' || c == '$' || isalnum (c))
			cp++;

		End = cp;

		switch (vargiven (begin, End, 1 /* Residual */))
		{
		    case -1:	/* Na lista de indefinidos */
			*stackp++ = 'D';
			return (1);

		    case 1:	/* Na lista de definidos */
			*stackp++ = 'U';
			falselevel++;
			return (1);

		    default:	/* Neutro: n�o est� em nenhuma lista */
			*stackp++ = 'N';
			return (falselevel);
		}
	}
	elif (strncmp (cp, "if", 2) == 0)
	{
		/*
		 *	"#if"
		 */
		cp += 2;

		while ((c = *cp) == ' ' || c == '\t')
			cp++;

		/*
		 *	Analisa o caso particular "#if (0)"
		 */
		if (strncmp (cp, "(0)", 3) == 0)
		{
			*stackp++ = 'U';
			falselevel++;
			return (1);
		}

		*stackp++ = 'N';
		return (falselevel);
	}
	elif (strncmp (cp, "else", 4) == 0)
	{
		/*
		 *	"#else"
		 */
		if (stackp <= stack)
		{
			fprintf
			(	stderr,
				"\"#else\" sem \"#if...\" no arquivo \"%s\"\n",
				innm
			);
		}

		switch (stackp[-1])
		{
		    case 'U':
			falselevel--;
			stackp[-1] = 'D';
			return (1);

		    case 'D':
			falselevel++;
			stackp[-1] = 'U';
			return (1);

		    default:	/* Neutro */
			return (falselevel);
		}
	}
	elif (strncmp (cp, "elif", 4) == 0)
	{
		/*
		 *	"#elif"
		 */
		if (stackp <= stack)
		{
			fprintf
			(	stderr,
				"\"#elif\" sem \"#if\" no arquivo \"%s\"\n",
				innm
			);
		}

		if (stackp[-1] != 'N')
		{
			fprintf
			(	stderr,
				"\"#elif\" associado a \"#ifdef\" "
				"no arquivo \"%s\"\n",
				innm
			);
		}

		return (falselevel);
	}
	elif (strncmp (cp, "endif", 5) == 0)
	{
		/*
		 *	"#endif"
		 */
		cp += 5;

		if (stackp <= stack)
		{
			fprintf
			(	stderr,
				"Excessivos \"endif's\" no arquivo \"%s\"\n",
				innm
			);
		}

		switch (*--stackp)
		{
		    case 'U':
			falselevel--;
			break;

		    case 'D':
			break;

		    default:	/* Neutro */
			return (falselevel);
		}

		/*
		 *	Elimina a linha seguinte, se � em branco
		 */
		if ((c = getc (infp)) != '\n' && c != EOF)
			ungetc (c, infp);

		return (1);
	}

	/*
	 *	Demais metacomandos
	 */
	return (falselevel);

}	/* end metaline */

/*
 ****************************************************************
 *	Verifica se a vari�vel foi dada				*
 ****************************************************************
 */
int
vargiven (const char *begin, char *End, int flag)
{
	/*
	 *	Flag:
	 *	   0: N�o residual
	 *	   1: Residual
	 *
	 *	Devolve:
	 *	  -1 => Indefinida
	 *	   0 => Vari�vel n�o dada
	 *	  +1 => Definida
	 */
	int		i;
	const char	**cpp;
	char		**rpp;
	char		c;

	c = *End; *End = '\0';

	for (cpp = defvar, i = 0; i < defi; cpp++, i++)
	{
		if (streq (begin, *cpp))
			{ *End = c; return (1); }
	}

	for (cpp = undefvar, i = 0; i < undefi; cpp++, i++)
	{
		if (streq (begin, *cpp))
			{ *End = c; return (-1); }
	}

	/*
	 *	A vari�vel n�o foi dada => � residual
	 */
	if (flag)
	{
		for (rpp = resvar; *rpp; rpp++)
		{
			if (streq (*rpp, begin))
				{ *End = c; return (0); }
		}

		if (rpp >= &resvar[RESSZ - 1])
			error ("$Tabela de vari�veis residuais excedida");

		*rpp = strdup (begin);
	}

	*End = c; return (0);

}	/* end vargiven */

/*
 ****************************************************************
 *	Imprime as vari�veis residuais				*
 ****************************************************************
 */
void
resvarpr (void)
{
	char		* const *rpp;
	int		i;

	if (!rflag)
		return;

	if (**resvar == 0)
	{
		fprintf (stderr, "N�o h� vari�veis residuais");
	}
	else
	{
		fprintf (stderr, "\nVari�veis residuais:");

		for (rpp = resvar, i = 0; *rpp; rpp++, i++)
		{
			if (i % 5 == 0)
				fprintf (stderr, "\n     ");

			fprintf (stderr, " %-14.14s", *rpp);
		}
	}

	fprintf (stderr, "\n");

}	/* end resvarpr */

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
		"%s - realiza pr�processamentos parciais\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-vr] [-D <var>] [-U <var>] <arquivo1> [<arquivo2]\n"
		"\t%s [-vr] [-D <var>] [-U <var>] <arquivo> ... <diret�rio>\n"
		"\t%s [-vr] [-D <var>] [-U <var>] -N <diret�rio>\n",
		pgname, pgversion, pgname, pgname, pgname, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-D: A vari�vel \"var\" deve ser definida\n"
		"\t-U: A vari�vel \"var\" deve ser indefinida\n"
		"\t-v: Verboso\n"
		"\t-r: Imprime uma lista de vari�veis residuais\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
	);

	exit (2);

}	/* end help */
