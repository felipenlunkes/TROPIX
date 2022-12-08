/*
 ****************************************************************
 *								*
 *			cc.c					*
 *								*
 *	Driver do compilador "C" do TROPIX			*
 *								*
 *	Vers�o	2.0.0, de 23.02.88				*
 *		4.1.0, de 28.08.01				*
 *								*
 *	M�dulo: cc						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 4.1.0, de 28.08.01";

/*
 ****** Defini��o de macros *************************************
 */
#define	elif		else if
#define	NOCHAR		(char)NULL

#define	MAXFILES	200
#define MAXOPT		200
#define	MAXPARAM	200

/*
 ****** Vari�veis globais ***************************************
 */
entry int		exit_code = 0;	/* C�digo de retorno */

/*
 ****** Indicadores *********************************************
 */
entry int		cflag;		/* Objetos gerados em "*.o" */
entry int		aflag;		/* Tabela de simbolos com locais */
entry int		sflag;		/* Strip: retira a tabela de simbolos */
entry int		uflag;		/* S�mbolos n�o ref. do linkeditor */
entry int		mflag;		/* Tabela de "linkedi��o" */
entry int		wflag;		/* Gera informa��es para "wsdb" */
entry int		vflag;		/* Liga modo verboso */
entry int		Oflag;		/* Otimize codigo */
entry int		Sflag;		/* Resultado da comp. em "*.s" */
entry int		Tflag;		/* Apenas cheque de sintaxe */
entry int		Pflag;		/* Execute apenas o CPP */
entry int		Eflag;		/* Apenas o CPP, resultado no stdout */
entry int		dotflag;	/* Tempor�rias do diret�rio corrente */

#undef	CC+
#ifdef	CC+
entry int		Mflag;		/* Executa apenas o MACPLUS+ */
#endif	CC+

entry int		dflag;		/* Debug codigo */

#if (0)	/*******************************************************/
entry int		fflag;		/* Fake libm */
entry int		nflag;		/* Torna o codigo gerado reent. */
entry int		Lflag;		/* Gera "*.l" do montador */
entry int		lflag;		/* Gera listagem do compilador */
entry int		pflag;		/* CPU dada */
entry int		Xflag;		/* Op��es para o compilador */
entry const char	*Xstr;		/* Cadeia com as op��es para o comp. */
#endif	/*******************************************************/

entry int		dir;		/* Nome dado (-o) � de um diretorio */

/*
 ****** Vari�veis do MAC+ ***************************************
 */
#ifdef	CC+

const char	macpgm[] = "/bin/mac+";	/* Arquivo com o MACPLUS+ */
const char	*macout	= "/tmp/plccm+XXXXXX";	/* Arquivo de saida do MACPLUS+ */
const char	*cppout;		/* Arquivo de saida do CPP */
const char	*macv[MAXOPT];		/* Parametros para MAC+ */
int		nmac;			/* Numero de parametros para MAC+ */

#else

const char	*cppout = "/tmp/plccpXXXXXX";	/* Arquivo de saida do CPP */

#endif	CC+

int	tindex  = 9;			/* Caractere a mudar nos temps */

/*
 ****** Vari�veis do PCC ****************************************
 */
const char	*cin;			/* Arquivo de entrada de C */
const char	*cout;			/* Arquivo de saida de C */
const char	*c2out;			/* Arquivo de saida de C2 */
const char	*as_in;			/* Arquivo fonte do Assembler */
const char	*as_out;		/* Arquivo de saida do Assembler */
const char	*outnm;			/* Arquivo gerado */

const char	prefix[] = "/lib/crt0.o"; /* Prefixo para todos os programas */

const char	*cppinc;		/* Mais um Include para o CPP */
const char	*cppgm  =  "/lib/cpp";	/* Arquivo com o CPP */

const char	*c1pgm  =  "/lib/gcc.486"; /* Arquivo com o C (compilador em si) */
const char	aspgm[] =  "/bin/as";	/* Arquivo com o Assembler */
const char	ldpgm[] =  "/bin/ld";	/* Arquivo com o Linkeditor */

const char	*shlib_name = "-lt.o";	/* Nome da biblioteca compartilhada  */

const char	nullfile[] =  "/dev/null"; /* Arquivo Ignorado */

/*
 ****** Vari�veis diversas **************************************
 */
entry const char	*clist[MAXFILES]; /* Arquivos a serem compilados */
entry int		nc;		/* No. de arquivos a compilar */
entry const char	*llist[MAXFILES]; /* Arquivos a serem linkeditados */
entry int		nl;		/* No. de arquivos a linkeditar */
entry const char	*v[MAXPARAM];	/* Lista de parametros a passar */
entry int		nv;		/* Numero de parametros */
entry int		nobj;		/* Numero de arquivos ".o" recebidos */

entry char		*cppv[MAXOPT];	/* Parametros para CPP */
entry int		ncpp;		/* Numero de parametros para CPP */

entry int		dlen;		/* Comprimento do nome do dir. dado */
entry char		*dnm;		/* Nome do diretorio */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
const char	*setext (const char *, int);
int		getext (const char *);
int		distinct (const char **, const char *);
int		exec (const char *, const char *[]);
const char	*lastid (const char *);
void		unlkfiles (void);
void		sigexit (int, ...);
void		help (void);

/*
 ****************************************************************
 *	Driver do compilador "C" do TROPIX			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	const char	*cp;
	char		*cv;
	int		c;
	int		i;
	STAT		s;
	int		opt;
	const char	*cpuid = NOSTR;
#ifdef	CC+
	int		status;
#endif	CC+

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "casumvOSTPEC.D:U:I:o:dMH")) != EOF)
	{
		switch (opt)
		{
		    case 'c':			/* N�o linkeditar */
			cflag++;
			break;

		    case 'a':			/* s�mbolos locais */
			aflag++;
			break;

		    case 's':			/* strip */
			sflag++;
			break;

		    case 'u':			/* N�o referenciados */
			uflag++;
			break;

		    case 'm':			/* Tabela do "link-editor" */
			mflag++;
			break;

		    case 'v':			/* Passos da compila��o */
			vflag++;
			break;

		    case 'O':			/* Otimiza��o */
			if (wflag)
				help ();
			Oflag++;
			break;

		    case 'S':			/* Gera apenas *.s */
			Sflag++;
			cflag++;
			break;

		    case 'T':			/* Verifica a sintaxe */
			Tflag++;
			Sflag++;
			cflag++;
			break;

		    case 'P':			/* CPP para *.i */
			Pflag++;
			cflag++;
			break;

		    case 'E':			/* CPP para stdout */
			Eflag++;
			cflag++;
			break;

		    case 'C':			/* CPP com coment�rios */
			cppv[ncpp++] = cv = malloc (3);
			*cv++ = '-';
			*cv++ = 'C';
			*cv = NOCHAR;
			break;

		    case '.':			/* Tempor�rios no dir corr */
			dotflag++;
			tindex -= 5;
#ifdef	CC+
			macout += 5;
#else
			cppout += 5;
#endif	CC+
			break;

		    case 'D':			/* Op��es do CPP */
		    case 'U':
		    case 'I':
			if (ncpp >= MAXOPT)
				error ("$Op��es demais para o pr�processador");

			cv = malloc (3);
			cppv[ncpp++] = cv;
			*cv++ = '-';
			*cv++ = opt;
			*cv = NOCHAR;

			cv = malloc (strlen (optarg) + 1);
			cppv[ncpp++] = cv;
			strcpy (cv, optarg);

			break;

		    case 'o':			/* Nome do objeto */
			if ((c = getext (optarg)) == 's' || c == 'c')
			    error ("$Nome do objeto terminado em 'c' ou 's'?");

			outnm = optarg;
			break;

#if (0)	/*******************************************************/
		    case 'p':			/* CPU */
			pflag++;
			cpuid = optarg;
			break;

		    case 'X':			/* Op��es para o compilador */
			Xflag++;
			Xstr = optarg;
			break;

		    case 'w':			/* wsdb */
			if (Oflag)
				help ();
			wflag++;
			break;
#endif	/*******************************************************/

#ifdef	CC+
		    case '+':			/* Somente o MACPLUS+ */
			Mflag++;
			cflag++;
			break;

		    case 'g':			/* Argumento para MACPLUS+ */
			macv[nmac++] = "-g";
			macv[nmac++] = optarg;
			break;
#endif	CC+
		    case 'd':			/* Debug */
			dflag++;
			break;

		    case 'M':
			exit (0);

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch (opt) */

	}	/* end while (getopt () != EOF) */

	/*
	 *	Alguns retoques
	 */
	if (Tflag)
		Oflag = 0;

	/*
	 *	Acerta "argv" e "argc"	
	 */
	argc -= optind;
	argv += optind;

	if (*argv == NOSTR)
		error ("$Nenhum arquivo?\n");

	/*
	 ******	Examina as CPUs e processadores flutuantes ******
	 */
	if (cpuid == NOSTR)
		cpuid = getenv ("CPU");

	if (cpuid == NOSTR)
		cpuid = "";

	/*
	 *	Verifica se "outnm", se dado, � um diret�rio
	 */
	if (outnm)
	{
		if (stat (outnm, &s) == 0)
			dir = ((s.st_mode & S_IFMT) == S_IFDIR);

		if (dir)
		{
			dlen = strlen (outnm) + 1;
			dnm = malloc (dlen + 1);

			strcpy (dnm, outnm);
			dnm[dlen - 1] = '/';
			dnm[dlen] = NOCHAR;
		}
	}

	/*
	 **************	Processa o ambiente  ****************************
	 */
	if ((cp = getenv ("CC_CPP")) != NOSTR)		/* Pr�processador a utilizar */  
		cppgm = cp;

	if ((cp = getenv ("CC_INC")) != NOSTR)		/* Diret�rio de "*.h" */    
		cppinc = cp;

	if ((cp = getenv ("CC_COMP")) != NOSTR)		/* Compilador a utilizar */   
		c1pgm = cp;

	if ((cp = getenv ("CC_SHLIB")) != NOSTR)
	{
		if   (streq (cp, "0"))
			shlib_name = NOSTR;
		elif (streq (cp, "1"))
			shlib_name = "-lt.o";
		else
			shlib_name = cp;
	}

	/*
	 **************	Processa a lista de arquivos ********************
	 */
	for (/* vazio */; cp = *argv; argv++)
	{
		if ((c = getext (cp)) == 'c' || c == 's')
		{
			/*
			 *	Arquivo a ser compilado ou montado
			 */
			if (nc >= MAXFILES)
				error ("$N�mero excessivo de arquivos fontes");

			clist[nc++] = cp;

			if (cflag == 0)
				cp = setext (cp, 'o');
		}

		if (c == 'o')
			nobj++;

		if (cflag)
			continue;

		if (distinct (llist, cp))
		{
			/*
			 *	Arquivo a ser linkeditado
			 */
			if (nl >= MAXFILES)
				error ("$N�mero excessivo de arquivos objeto");

			llist[nl++] = cp;

		}
		else
		{
			error ("$Objeto repetido: \"%s\"", cp);
		}

	}	/* end for (arquivos) */

	/*
	 *	Consistencia do "outnm"	
	 */
	if (outnm  &&  nc > 1  &&  dir == 0  &&  cflag)
	{
		error
		(	"$Mesmo nome (\"%s\") para v�rios arquivos gerados",
			outnm
		);
	}

	if (nc == 0)
		goto linkedition;

#ifdef	CC+
	if (Mflag == 0)
	{
		/*
		 *	Se pedida compila��o completa:
		 *	Cria arquivos temporarios.
		 */
		if ((macout = mktemp (macout)) == NOSTR)
			error ("$N�o obtive o nome do arquivo tempor�rio");

		if (Pflag == 0 && Eflag == 0)
		{
			cppout = cv = strdup (macout);
			cv[tindex] = 'p';

			cout = cv = strdup (macout);
			cv[tindex] = 'c';

			as_out = cv = strdup (macout);
			cv[tindex] = 'a';

			if (Oflag)
			{
				c2out = cv = strdup (macout);
				cv[tindex] = '2';
			}
			else
			{
				c2out = cout;
			}
		}

	}	/* end if (Mflag == 0) */

#else	CC+

	if (Pflag == 0 && Eflag == 0)
	{
		/*
		 *	Se pedida compila��o completa:
		 *	Cria arquivos temporarios.
		 */
		if ((cppout = mktemp (cppout)) == NOSTR)
			error ("$N�o obtive o nome do arquivo tempor�rio");

		cout = cv = strdup (cppout);
		cv[tindex] =   'c';

		as_out = cv = strdup (cppout);
		cv[tindex] =  'a';

		c2out = cout;

	}	/* end if (Pflag == 0 && Eflag == 0) */
#endif	CC+

	/*
	 *	Trata os sinais
	 */
	if (signal (SIGINT, SIG_IGN) != SIG_IGN)
		signal (SIGINT, sigexit);

	if (signal (SIGTERM, SIG_IGN) != SIG_IGN)
		signal (SIGTERM, sigexit);

	/*
	 **************	Compila os arquivos *****************************
	 */
	for (i = 0; i < nc; i++)
	{
		if (nc > 1)
			printf ("%s:\n", clist[i]);

		if (getext (clist[i]) == 's')
		{
			if (Sflag)
				continue;

			as_in = clist[i];

			goto assemble;
		}
		else
		{
			as_in = c2out;
		}

#ifdef	CC+
		status = 0;

		/*
		 *	Execu��o do MACPLUS+
		 */
		if (Mflag)
		{
			if (cflag  &&  outnm  &&  ! dir)
				macout = outnm;
			else
				macout = setext (clist[i], 'm');
		}

		v[1] = "-c";

		for (c = 0, nv = 2; c < nmac; c++, nv++)
			v[nv] = macv[c];

		v[nv++] = "-o";
		v[nv++] = macout;

		if (vflag)
		{
			v[nv++] = "-v";
			puts ("  Macroprocessando");
		}

		v[nv++] = clist[i];
		v[nv++] = NOSTR;

		if ((status = exec (macpgm, v)) != 255 && status != 0)
		{
			cflag++;
			exit_code++;

			if (! Mflag)
				unlink (macout);

			continue;
		}

		if (Mflag)
			continue;
#endif	CC+

		/*
		 *	Prepara��o para execu��o do CPP
		 */
		if (Pflag  &&  Eflag == 0)
		{
			if (cflag  &&  outnm  &&  dir == 0)
				cppout = outnm;
			else
				cppout = setext (clist[i], 'i');
		}

#ifdef	CC+
		if (status == 255)
		{
#endif	CC+
			/*
			 *	Execu��o do CPP
			 */
			if (vflag)
				puts ("  Preprocessando");

			for (nv = 1, c = 0; c < ncpp; c++, nv++)
				v[nv] = cppv[c];

			if (cppinc)
			{
				v[nv++] = "-I";
				v[nv++] = cppinc;
			}

			if (Pflag || Eflag)
				v[nv++] = "-P";

			if (Tflag)
				v[nv++] = "-T";
#ifdef	CC+
			v[nv++] = macout;
#else
			v[nv++] = clist[i];
#endif	CC+
			if (!Eflag)
				v[nv++] = cppout;

			v[nv] = NOSTR;

			if (exec (cppgm, v))
			{
				cflag++;
				exit_code++;

#ifdef	CC+
				unlink (macout);
#endif	CC+
				if (Pflag == 0 && Eflag == 0)
					unlink (cppout);

				continue;
			}

			if (Pflag || Eflag)
				continue;

			/*
			 *	Entrada de C
			 */
			cin = cppout;

#ifdef	CC+
		}	/* end if (status != 0377) */
		else
		{
			if (Pflag || Eflag)
			{
				link (macout, cppout);
				unlink (macout);
			}
			else
			{
				cin = macout;
			}
		}

		unlink (macout);
#endif	CC+

		/*
		 *	Execu��o de C (primeiro passo do compilador)
		 */
		if (vflag)
			puts ("  Compilando");

		nv = 1;

		v[nv++] = "-ftropix";

		if   (Tflag)
		{
			v[nv++] = "-O";
#if (0)	/*************************************/
			v[nv++] = "-fsyntax-only";
#endif	/*************************************/
			v[nv++] = "-W";
			v[nv++] = "-Wunused";
			v[nv++] = "-Wshadow";
			v[nv++] = "-Wswitch";
			v[nv++] = "-Wreturn-type";
		}
		elif (Oflag)
		{
			v[nv++] = "-O";
		}

		v[nv++] = "-o";

		if   (Tflag)
		{
			v[nv++] = nullfile;
		}
		elif (Sflag)
		{
			if (cflag  &&  outnm  &&  dir == 0)
				v[nv++] = outnm;
			else
				v[nv++] = setext (clist[i], 's');
		}
		else
		{
			v[nv++] = cout;
		}

		v[nv++] = cin;

		v[nv] = NOSTR;

		if (exec (c1pgm, v))
		{
			cflag++;
			exit_code++;

			unlink (cin);
			if (v[nv - 2] == cout)
				unlink (cout);

			continue;
		}

		unlink (cin);

		if (Sflag)
			continue;

		/*
		 *	Montagem	
		 */
	    assemble:
		if (vflag)
			puts ("  Montando");

		nv = 1;

		if (aflag)
			v[nv++] = "-a";

		if (vflag)
			v[nv++] = "-v";

		v[nv++] = "-o";

		if (cflag  &&  outnm  &&  dir == 0)
		{
			v[nv++] = outnm;
		}
		else
		{
			v[nv++] = setext (clist[i], 'o');
		}

#if (0)	/*******************************************************/
		if (Lflag)
		{
			v[nv++] = "-l";
			v[nv++] = setext (clist[i], 'l');
		}
#endif	/*******************************************************/

		v[nv++] = as_in;
		v[nv] = NOSTR;

		if (exec (aspgm, v))
		{
			cflag++;
			exit_code++;

			unlink (v[2]);
			if (as_in == c2out)
				unlink (c2out);

			continue;
		}

		if (as_in == c2out)
			unlink (c2out);

	}	/* end for (i = 0; i < nc; i++) */

	/*
	 **************	Ep�logo: LINK EDITION ***************************
	 */
    linkedition:
	if (cflag)
		exit (exit_code);

	if (vflag)
		puts ("Linkeditando");

	nv = 1;

	if (outnm)
	{
		v[1] = "-o";

		if (dir)
		{
			v[2] = cv = malloc (dlen + 6);
			strcpy (cv, dnm);
			strcpy (cv+dlen, "a.out");
		}
		else
		{
			v[2] = outnm;
		}

		nv = 3;
	}

	if (aflag)
		v[nv++] = "-a";

	v[nv++] = "-n";

	if (sflag)
		v[nv++] = "-s";

	if (uflag)
		v[nv++] = "-u";

	if (uflag > 1)
		v[nv++] = "-u";

	if (mflag)
		v[nv++] = "-m";

	if (vflag)
		v[nv++] = "-v";

	if (dotflag)
		v[nv++] = "-.";

#if (0)	/*******************************************************/
	v[nv++] = "-T";
	v[nv++] = "0x400000";

	v[nv++] = "-D";
	v[nv++] = "0x20000000";
#endif	/*******************************************************/

	v[nv++] = prefix;

	for (i = 0; i < nl; /* vazio */)
		v[nv++] = llist[i++];

	if (shlib_name == NOSTR)
		{ v[nv++] = "-lc"; v[nv++] = "-lm"; }
	else
		v[nv++] = shlib_name;

#if (0)	/*******************************************************/
	if (shlib_value != 0)
		v[nv++] = "-lt.o";
	else
		{ v[nv++] = "-lc"; v[nv++] = "-lm"; }
#endif	/*******************************************************/

	v[nv++] = NOSTR;

	exit_code |= exec (ldpgm, v);

	for (i = 0; i < nc; /* vazio */)
		unlink (setext (clist[i++], 'o'));

	return (exit_code);

}	/* end main */

/*
 ****************************************************************
 *	Copia o nome com o diret�rio e extens�o alterada	*
 ****************************************************************
 */
const char *
setext (const char *nm, int c)
{
	char		*cp;
	int		l;

	/*
	 *	Obtem o nome do arquivo
	 */
	nm = lastid (nm);

	l = strlen (nm);

	if (dir)
		l += dlen;

	cp = malloc (l + 1);

	if (dir)
	{
		strcpy (cp, dnm);
		strcat (cp, nm);
	}
	else
	{
		strcpy (cp, nm);
	}

	cp[l - 1] = c;

	return (cp);

}	/* end setext */

/*
 ****************************************************************
 *	Retorna a extens�o do nome de um arquivo		*
 ****************************************************************
 */
int
getext (const char *nm)
{
	char		*cp;

	cp = strend (nm);

	if ((cp -= 2) > nm && *cp++ == '.')
		return (*cp);

	return (NOCHAR);

}	/* end getext */

/*
 ****************************************************************
 *	Verifica se o nome dado esta' entre os da lista dada	*
 ****************************************************************
 */
int
distinct (const char **list, const char *nm)
{
	for (/* vazio */; *list; list++)
	{
		if (streq (nm, *list))
			return (0);
	}

	return (1);

}	/* end distinct */

/*
 ****************************************************************
 *	Executa o um dos passos da compila��o			*
 ****************************************************************
 */
int
exec (const char *nm, const char *argv[])
{
	int		pid;
	int	 	termcode;
	int		status;
	const char	**cp;

	argv[0] = lastid (nm);

	if (dflag != 0)
	{
		printf ("=> (%s)\t", nm);

		for (cp = argv; *cp; cp++) 
			printf ("%s ", *cp);

		printf ("\n");
	}

	if (dflag > 1)
		return (0);

	/*
	 *	Cria um processo filho
	 */
	if ((pid = fork ()) == 0)
	{
		/*
		 *	Este � o processo filho
		 */
		execv (nm, argv);
		error ("$*N�o consegui executar \"%s\"", nm);
	}
	elif (pid < 0)
	{
		error ("N�o consegui criar um processo para \"%s\"", nm);
		return (100);
	}

	/*
	 *	Espera o filho terminar a execu��o
	 */
	while (pid != wait (&status))
		/* vazio */;

	/*
	 *	Verifica se a termina��o foi normal
	 */
	if ((termcode = status & 0xFF) != 0)
	{
		fprintf (stderr, "%s: ", pgname);

		fprintf
		(	stderr,
			"%s na execu��o de \"%s\"",
			sigtostr (termcode & ~0x80),
			nm
		);

		fprintf (stderr, ", pc = %P", _fpc);

		if (termcode == SIGBUS || termcode == SIGADR || termcode == SIGSEGV)
		{
			fprintf (stderr, ", fa = %P", _faddr);
		}
		elif (termcode == SIGILL)
		{
			fprintf (stderr, ", inst = %04X", (int)_faddr & 0xFFFF);
		}

		putc ('\n', stderr);

		if (termcode & 0x80)
		    error ("Core dumped");

		unlkfiles ();

		exit (++exit_code);
	}

	return ((status >> 8) & 0xFF);

}	/* end exec */

/*
 ****************************************************************
 *	Obt�m o �ltimo identificador de um caminho		*
 ****************************************************************
 */
const char *
lastid (const char *path)
{
	const char	*cp;

	if ((cp = strrchr (path, '/')) != NOSTR)
		return (cp + 1);
	else
		return (path);

}	/* end lastid */

/*
 ****************************************************************
 *	Remove os arquivos temporarios				*
 ****************************************************************
 */
void
unlkfiles (void)
{
#ifdef	CC+
	if (getext (macout) == NOCHAR)
		unlink (macout);
#endif	CC+

	if (getext (cppout) == NOCHAR)
		unlink (cppout);

	if (getext (cout) == NOCHAR)
		unlink (cout);

	if (getext (c2out) == NOCHAR)
		unlink (c2out);

	if (getext (as_out) == NOCHAR)
		unlink (as_out);

}	/* end unlkfiles () */

/*
 ****************************************************************
 *	Tratamento de sinais					*
 ****************************************************************
 */
void
sigexit (int signo, ...)
{
	unlkfiles ();

	exit (100);

}	/* end sigexit () */

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
		"%s - Compilador para a linguagem \"C\"\n"
		"\n%s\n"
		"\nSintaxe:\n",
		pgname, pgversion
	);

	fprintf
	(	stderr,
#if (0)	/*******************************************************/
		"\t%s [-casumvOSTPEC%s.] [-D <def>] [-U <id> ] [-I <dir>] [-o <obj>]%s <arq> ...\n",
#endif	/*******************************************************/
		"\t%s [-casumvOSTPEC%s.] [-D <def>] ... [-U <id> ] ...\n"
		"\t\t\t\t\t  [-I <dir>] ... [-o <obj>]%s <arq> ...\n",
		pgname,
#ifdef	CC+
		"M", " [-g def]"	/* lembrar o problema do "M" repetido */
#else
		"", ""
#endif	CC+
	);

	fprintf
	(	stderr,
		"\nOp��es:\n"
		"\t-c: N�o faz a \"link-edi��o\", gerando m�dulos objeto \"*.o\"\n"
		"\t-a: Inclui os s�mbolos locais na tabela de s�mbolos\n"
		"\t-s: Produz um m�dulo execut�vel sem tabela de s�mbolos\n"
		"\t-u: Lista os s�mbolos n�o referenciados\n"
		"\t-m: Produz uma tabela de \"link-edi��o\"\n"
#if (0)	/*******************************************************/
	"\t%s [-cnasumflLwvOSTPEC%s.] [-p <cpu>] [-D <def>] ... "
	"[-U <id> ] ...\n"
	"\t\t\t\t\t  [-I <dir>] ... [-o <obj>]%s <arq> ...\n",
		"\t-L: Gera o \"*.l\" do montador\n"
		"\t-l: Lista a entrada do compilador\n"
		"\t-f: Utiliza a biblioteca de ponto flutuante falsa\n"
		"\t-n: Produz um m�dulo execut�vel reentrante\n"
		"\t-w: Gera informa��es de depura��o para \"wsdb\"\n"
#endif	/*******************************************************/
	);

	fprintf
	(	stderr,
		"\t-v: Imprime informa��es sobre os passos da compila��o\n"
		"\t-O: Compila com a fase de otimiza��o\n"
		"\t-S: N�o executa o montador, gerando arquivos \"*.s\"\n"
		"\t-T: Verifica apenas a sintaxe, sem gerar nenhum arquivo\n"
		"\t-P: Executa apenas o pr�processador, gerando arquivos \"*.i\"\n"
		"\t-E: Executa apenas o pr�processador, pondo a saida em \"stdout\"\n"
		"\t-C: Mantem os coment�rios na sa�da do pr�processador\n"
#ifdef	CC+
		"\t-+: Executa o MACPLUS+, gerando arquivos \"*.m\"\n"
#endif	CC+
		"\t-.: Aloca os arquivos tempor�rios no diret�rio corrente\n"
	);

	fprintf
	(	stderr,
		"\t-D: Predefine uma macro para o pr�processador\n"
		"\t    <def> � da forma \"id\" ou \"id=valor\"\n"
		"\t-U: N�o permite macros com o nome <id>\n"
		"\t-I: Acrescenta <dir> � lista de busca de \"#includes\" do pr�processador\n"
		"\t-o: Define o nome do objeto gerado\n"
#ifdef	CC+
		"\t-g: Define vari�veis globais para o MACPLUS+\n"
#endif	CC+

#if (0)	/*******************************************************/
		"\nObs.\tAs op��es \"-w\" e \"-O\" s�o mutuamente exclusivas\n"
		"\t-p: Gera c�digo objeto para a <cpu> dada\n"
#endif	/*******************************************************/

	);

	exit (2);

}	/* end help */
