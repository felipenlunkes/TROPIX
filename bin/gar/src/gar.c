/*
 ****************************************************************
 *								*
 *			gar.c					*
 *								*
 *	General Archiver -- utilit�rio para fitas/disquetes	*
 *								*
 *	Vers�o	1.1.0, de 11.01.88				*
 *		4.9.0, de 20.07.06				*
 *								*
 *	M�dulo:	GAR						*
 *		utilit�rios b�sicos				*
 *		Categoria A					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#include "../h/common.h"
#include "../h/gar.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.9.0, de 20.07.06";

const char	headerversion[] =  "19.03.03";

#define	NPAT	20		/* No. maximo de Padr�es */

#define	COL_AREA_RAW	(20 * KBSZ)	/* Tamanho padr�o da �rea de entrada */
#define	COL_AREA_STD	 (4 * KBSZ)	/* Tamanho padr�o da �rea de entrada */

/*
 ****** Indicadores *********************************************
 */
entry FUNC		func  = NOFTN;	/* Fun��o */

entry void		(*function) ();	/* Fun��o a executar para cada bloco */

entry MODIF		modif = NOMODIF; /* Modificador */

entry int		Tflag;		/* Gera o formato TAR */
entry int		Dflag = 1;	/* Comprime (ZIP) */
entry int		nflag;		/* Interativo */
entry int		uflag;		/* Compara��o com atualiza��o */
entry int		rflag;		/* Sempre cheque os CRCs */
entry int		vflag;		/* Verbose */
entry int		dflag;		/* Diret�rio corrente/N�o inclui diret�rios na cole��o */
entry int		fflag;		/* Copia mesmo que j� exista */
entry int		mflag;		/* Restaura dono, grupo e datas */
entry int		gflag;		/* Processa o "garfield" */
entry int		dotflag;	/* N�o ignora ".old" etc ... */
entry int		crcflag;	/* N�o gera CRC na compress�o */
entry int		Gflag;		/* Debug */
entry int		Hflag;		/* Help flag */

entry const char	*inc_pat[NPAT+1];	/* Os Padr�es */
entry int		inc_pati;

entry const char	*exc_pat[NPAT+1]; /* Os Padr�es de exclus�o */
entry int		exc_pati;

entry int		exit_code = 0;	/* C�digo de retorno */

/*
 ******	�rea de Entrada/Saida ***********************************
 */
entry BUF		*b;		/* Continua��o + leitura/escrita da cole��o */

entry int		col_area_sz;	/* Tamanho do buffer em vigor (blocagem) */

entry int		col_area_avail_sz; /* No. de bytes disponiveis no buffer */

entry int		col_is_a_tape;	/* A cole��o � uma fita */

/*
 ****** Vari�veis diversas **************************************
 */
entry KHEAD		khead;		/* Cabe�alho interno */

entry const char	*g_filenm;	/* Nome do Arquivo em Processamento */
entry int		g_filenmput;	/* O Nome do Arquivo ja foi impresso */
entry int		g_nlput;	/* O <nl> j� foi escrito */

entry time_t		date;		/* Data de cria��o da Cole��o GAR */

entry int		vol;		/* No. do Volume GAR */

entry FILE		*ttyfp;		/* Para ler do terminal */

entry TYPE		type;		/* Tipo da Fita */

entry const char	**color_vector;	/* Para as cores dos modos */

/*
 ****** Garfield ************************************************
 */
const char		garfield[] = "garfield";
entry FILE		*gfp;

/*
 ****** Cole��o *************************************************
 */
entry int		device_code = 0; /* C�digo do dispositivo */
const char		*device_nm = NOSTR; /* Nome do Dispositivo */

entry int		colfd;		/* File Descriptor da Cole��o */
entry dev_t		coldev;		/* Dispositivo da Cole��o */
entry ino_t		colino;		/* Inode da Cole��o */

/*
 ******	Cadeias magicas do GAR	*********************************
 */
const char		garvolume[GARMSZ+1]	= "GAR VOLUME  ";
const char		garheader[GARMSZ+1]	= "GAR HEADER  ";
const char		garlink[GARMSZ+1]	= "GAR LINK    ";
const char		gartrailer[GARMSZ+1]	= "GAR TRAILER ";

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void			put_s_option (void);
int			put_p_option (const char *, const char *[], int *);

/*
 ****************************************************************
 *	Ponto de Entrada					*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	int		i, opt;
	const char	*str;
	const char	*bl_str = NOSTR;
	const char	*level_str = NOSTR;
	STAT		dev_s;		/* Bloco para stat */

	/*
	 *	Pequena inicializa��o
	 */
	error_default_function = quit;

	/*
	 *	Analisa as Op��es
	 */
	while ((opt = getopt (argc, argv, "ioaxtceF:TDl:rB:sp:P:nuvdfmg.0123GMH")) != EOF)
	{
		switch (opt)
		{
		    case 'i':			/* Entrada */
			if (func != NOFTN)
				help ();

			func = IN;
			break;

		    case 'o':			/* Saida */
			if (func != NOFTN)
				help ();

			func = OUT;
			break;

		    case 'a':			/* Append */
			if (func != NOFTN)
				help ();

			func = OUT; modif = APPEND;
			break;

		    case 'x':			/* Extra��o */
			if (func != IN)
				help ();

			if (modif != NOMODIF)
				help ();

			modif = CREATE;
			break;

		    case 't':			/* Tabela */
			if (func != IN)
				help ();

			if (modif != NOMODIF)
				help ();

			modif = TAB;
			break;

		    case 'c':			/* Compara��o */
			if (func != IN)
				help ();

			if (modif != NOMODIF)
				help ();

			modif = COMP;
			break;

		    case 'e':			/* Pipe */
			if (func != IN)
				help ();

			if (modif != NOMODIF)
				help ();

			modif = PIPE;
			break;

		    case 'F':			/* Dispositivo da cole��o */
			if (device_code || device_nm)
				help ();

			device_nm = optarg;
			break;

		    case 'T':			/* Gere o formato TAR */
			Tflag++;
			break;

		    case 'D':			/* N�O Comprime */
			Dflag = 0;
			break;

		    case 'l':			/* N�vel de compress�o */
			level_str = optarg;
			break;

		    case 'r':			/* Sempre cheque os CRCs */
			rflag++;
			break;

		    case 'B':			/* Blocagem */
			bl_str = optarg;
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

		    case 'n':			/* Interativo */
			nflag++;
			break;

		    case 'u':			/* Compara��o com atualiza��o */
			if (func != IN)
				help ();

			if (modif == NOMODIF)
				modif = COMP;

			if (modif != COMP)
				help ();

			uflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'd':			/* Diretorio Corrente */
			switch (func)
			{
			    case IN:
				if (modif != CREATE && modif != COMP)
					help ();
				break;

			    case OUT:
				break;

			    default:
				help ();
			}

			dflag = 1;
			break;

		    case 'f':			/* Force */
#if (0)	/*******************************************************/
			if (func != IN)
				help ();

			if (modif != CREATE && modif != COMP)
				help ();
#endif	/*******************************************************/

			fflag++;
			break;

		    case 'm':			/* Restaura dono, etc... */
			if (func != IN)
				help ();

			if (modif != CREATE && modif != COMP)
				help ();
			mflag++;
			break;

		    case 'g':			/* Processa "garfield" */
			if (func == IN && modif != CREATE && modif != COMP)
				help ();

			gflag++;
			break;

		    case '.':			/* N�o ignora ".old" etc ... */
			if (func != OUT)
				help ();

			dotflag++;
			break;

		    case '0':
		    case '1':
		    case '2':
		    case '3':
#if (0)	/****************************************************/
		    case '4':
		    case '5':
		    case '8':
		    case '9':
#endif	/****************************************************/
			if (device_code || device_nm)
				help ();

			device_code = opt;
			break;

		    case 'G':			/* Debug */
			Gflag++;
			break;

		    case 'M':			/* Texto residente */
			exit (0);

		    case 'H':			/* help */
			Hflag++;
			break;

		    default:			/* erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end getopt */

	if (Hflag)
		help ();

	argv += optind;

	/*
	 *	Faz uma consistencia dos Argumentos
	 */
	if (func == NOFTN)
		{ error ("� necess�rio dar \"-i\", \"-o\" ou \"-a\"\n"); help (); }

	if (func == IN && modif == NOMODIF)
	{
		error ("No caso \"-i\" � necess�rio dar \"x\", \"t\", \"c\" ou \"e\"\n");
		help ();
	}

	/*
	 *	Prepara os sinais
	 */
	if (signal (SIGHUP,  SIG_IGN) != SIG_IGN)
		signal (SIGHUP, on_signal);

	if (signal (SIGINT,  SIG_IGN) != SIG_IGN)
		signal (SIGINT, on_signal);

	if (signal (SIGTERM, SIG_IGN) != SIG_IGN)
		signal (SIGTERM, on_signal);

	/*
	 *	Analisa o n�vel de defla��o
	 */
	if (level_str != NOSTR)
	{
		if
		(	(ZIP_LEVEL = strtol (level_str, &str, 0)) < MIN_LEVEL ||
			ZIP_LEVEL > MAX_LEVEL || *str != '\0'
		)
		{
			error ("$N�vel de compress�o ZIP inv�lido: \"%s\"", level_str);
		}
	}
	else
	{
		ZIP_LEVEL = DEF_LEVEL;
	}

	/*
	 *	Prepara o "garfield"
	 */
	if (gflag)
	{
		if (func == OUT)
		{
			if (freopen (garfield, "r", stdin) == NOFILE)
				error ("$*N�o consegui abrir \"%s\"", garfield);
		}
		else
		{
			char *modo = (modif == COMP ? "w" : "r" /* CREATE */);

			if ((gfp = fopen (garfield, modo)) == NOFILE)
				error ("$*N�o consegui abrir \"%s\"", garfield);
		}
	}

	/*
	 *	Prepara a TTY para Interativo
	 */
	if ((ttyfp = fopen ("/dev/tty", "r")) == NOFILE)
		error ("$*N�o consegui abrir \"/dev/tty\"");

	askyesno_stdin = ttyfp;
	askyesno_set (1);

	if (nflag && func == IN && modif != CREATE && modif != COMP)
	{
		error
		(	"O modo interativo s� pode ser usado na\n"
			"\tinclus�o/cria��o/compara��o de arquivos\n"
		);
		help ();
	}

	if (nflag)
		vflag = 0;

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stderr)), (void *)NULL, &color_vector);

	/*
	 *	Prepara o nome do dispositivo
	 */
	switch (device_code)
	{
	    case 0:
		break;

	    case '0':
		device_nm = "/dev/fd0";
		break;

	    case '1':
		device_nm = "/dev/fd1";
		break;

	    case '2':
		device_nm = "/dev/rzip0";
		break;

	    case '3':
		device_nm = "/dev/rzip1";
		break;

	    default:
		error ("$Nesta vers�o, o dispositivo # %c n�o est� definido", device_code);

	}	/* end switch */

	/*
	 *	Analisa o dispositivo
	 */
	if (device_nm != NOSTR)
	{
		/*
		 *	Dispositivo de entrada/sa�da dado
		 */
		int	oflag;

		if   (func == IN)
		{
			oflag = O_RDONLY;
		}
		elif (modif == APPEND)
		{
			oflag = O_RDWR|O_LOCK|O_CREAT;
		}
		else
		{
			oflag = O_WRONLY|O_LOCK|O_CREAT;

			if (!fflag && stat (device_nm, &dev_s) >= 0 && S_ISREG (dev_s.st_mode))
			{
				fprintf
				(	stderr,
					"%s: \"%s\" j� existe. Apaga/reescreve? (n): ",
					pgname, device_nm
				);

				if (askyesno () <= 0)
					exit (0);
			}
		}

		if ((colfd = open (device_nm, oflag, 0644)) < 0)
			error ("$*N�o consegui abrir \"%s\"", device_nm);
	}
	else	/* device_nm == NOSTR */
	{
		/*
		 *	Entrada/sa�da padr�o
		 */
		if (modif == APPEND)
			error ("$N�o podemos usar a entrada/sa�da padr�o para acr�scimos");

		if (func == IN)
			{ device_nm = "<stdin>";  colfd = 0; }
		else
			{ device_nm = "<stdout>"; colfd = 1; }
	}

	if (fstat (colfd, &dev_s) < 0)
		error ("$*N�o consegui obter estado de \"%s\"", device_nm);

	coldev = dev_s.st_dev;
	colino = dev_s.st_ino;

	/*
	 *	Analisa a blocagem
	 */
	if   (bl_str != NOSTR)
	{
		if ((i = strtol (bl_str, &str, 0)) <= 0 || *str)
			error ("$Blocagem inv�lida: \"%s\"", bl_str);

		col_area_sz = i * KBSZ;
	}
	elif (S_ISCHR (dev_s.st_mode))
	{
		col_area_sz = COL_AREA_RAW;
	}
	else
	{
		col_area_sz = COL_AREA_STD;
	}

	/*
	 *	Tenta obter o tamanho do dispositivo
	 */
	get_dev_size (colfd, &dev_s);

#if (0)	/*************************************/
#include <sys/ioctl.h>
	/*
	 *	Heur�stica para obter a blocagem boa
	 */
	if (col_area_sz == NBMAX * BLSZ  &&  func == IN  &&  col_area_sz_given == 0)
	{
		if (ioctl (colfd, MTISATAPE, 0) < 0)
		{
			if   (rflag)
				col_area_sz = NBDEF * BLSZ;
			elif (qflag || nflag || inc_pati > 0 || exc_pati > 0)
				col_area_sz = BLSZ;
			elif (modif == TAB || modif == CREATE && gflag)
				col_area_sz = BLSZ;
			else
				col_area_sz = NBDEF * BLSZ;
		}
	}

	/*
	 *	Verifique se � SU (em virtude do 'm')
	 */
	if (geteuid () != 0 && mflag)
	{
		erro
		(	"O usu�rio n�o � SUPERUSU�RIO: "
			"a op��o \"m\" ser� ignorada"
		);
		mflag = 0;
	}
#endif	/*************************************/

	/*
	 *	Verifique se tem argumentos superfluos
	 */
	if (func == IN  &&  *argv != NOSTR)
		{ error ("Na entrada podem apenas ser dados padr�es\n"); help (); }

	/*
	 *	Aloca a �rea de entrada/sa�da
	 */
	if ((b = malloc (col_area_sz + sizeof (GVOL))) == (BUF *)NULL)
		error ("$N�o obtive mem�ria para a �rea de entrada/sa�da");

	/*
	 *	Chama a Rotina Adequada
	 */
	if   (func == IN)
	{
		in ();
	}
	elif (modif == APPEND)
	{
		append (argv);
	}
	else	/* OUT */
	{
		col_area_avail_sz = col_area_sz;
		volhwrite ();
		out (argv);
	}

	quit (0);

}	/* end gar */

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
 *	Em caso de sinal, ...					*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	quit (1);

}	/* end on_signal */

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
		"%s - utilit�rio para a cria��o/atualiza��o "
			"de cole��es de arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n",
		pgname, pgversion
	);

	if (Hflag > 1) fprintf
	(	stderr,
		"\t%s -i [-xtce] [-F <col>] [-rnvugfmd#] "
		"[-B <n>] <PAD>\n\n"
		"\t%s -o [-Tngv#] [-F <col>] "
		"[-B <n>] <COMP> < <nomes>\n"
		"\t%s -o [-Tnvd.#] [-F <col>] "
		"[-B <n>] <PAD> <COMP> <nome> ...\n\n"
		"\t%s -a [-ngv#] [-F <col>] "
		"[-B <n>] <COMP> < <nomes>\n"
		"\t%s -a [-nvd.#] [-F <col>] "
		"[-B <n>] <PAD> <COMP> <nome> ...\n"
		"\nValores de <PAD>: "
		"[-s] [-p \"<p>\"] [-P \"<P>\"]\n"
		"\nValores de <COMP>: "
		"[-D] [-b <b>] [-l <l>]\n",
		pgname, pgname, pgname, pgname, pgname
	);
	else fprintf
	(	stderr,
		"\t%s -i [-xtce] [-F <col>] [-vugmd#]\n\n"
		"\t%s -o [-v#]   [-F <col>] < <nomes>\n"
		"\t%s -o [-vs#]  [-F <col>] [-p \"<p>\"] <nome> ...\n\n"
		"\t%s -a [-v#]   [-F <col>] < <nomes>\n"
		"\t%s -a [-vs#]  [-F <col>] [-p \"<p>\"] <nome> ...\n",
		pgname, pgname, pgname, pgname, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: Entrada\n"
		"\t-o: Sa�da\n"
		"\t-a: Acr�scimo\n"
		"\t-x: Extra��o\n"
		"\t-t: Tabela de conte�do\n"
		"\t-c: Compara��o\n"
		"\t-e: Escrita dos arquivos na sa�da padr�o\n"
		"\t-F: O dispositivo da cole��o � <col>\n"
		"\t-0: O dispositivo da cole��o � \"/dev/fd0\"\n"
		"\t-1: O dispositivo da cole��o � \"/dev/fd1\"\n"
		"\t-2: O dispositivo da cole��o � \"/dev/rzip0\"\n"
		"\t-3: O dispositivo da cole��o � \"/dev/rzip1\"\n"
		"\t-v: Verboso\n"
		"\t-u: Compara��o com atualiza��o\n"
		"\t-g: Processa \"garfield\"\n"
		"\t-m: Restaura o estado do arquivo\n"
		"\t-d: Diret�rio corrente/N�o inclui diret�rios na cole��o\n"
		"\t-p: Inclui apenas os arquivos contendo os padr�es \"<p>\"\n"
		"\t-s: Utiliza os padr�es para programas fonte em \"C\"\n"
	);
 
	if (Hflag < 2) fprintf
	(	stderr,
		"\nObs.:\tPara uma lista completa das op��es, use \"%s -HH\" ou \"man %s\"\n",
		pgname, pgname
	);
	else fprintf
	(	stderr,
		"\t-T: Gera a cole��o no formato TAR\n"
		"\t-D: N�O comprime os arquivos regulares\n"
		"\t-l: Utiliza o n�vel <l> ao inv�s de "
			XSTR (DEF_LEVEL)  " na compress�o ZIP\n"
		"\t-r: Sempre verifica os CRCs\n"
		"\t-n: Interativo\n"
		"\t-f: For�a\n"
		"\t-B: Blocagem de <n> KB\n"
		"\t-P: Exclui os arquivos contendo os padr�es <P>\n"
		"\t-.: Grava tamb�m \"arquivos ocultos\"\n"
	);

	quit (2);

}	/* end help */
