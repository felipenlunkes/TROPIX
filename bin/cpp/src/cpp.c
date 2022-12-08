/*
 ****************************************************************
 *								*
 *			cpp.c					*
 *								*
 *	Pr�processador de fontes em "C"				*
 *								*
 *	Vers�o	2.1.0, de 19.09.88				*
 *		4.6.0, de 27.08.04				*
 *								*
 *	M�dulo: CPP						*
 *		Tradutores					*
 *		Categoria D					*	
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>
#include <sys/kcntl.h>

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../h/cpp.h"
#include "../h/scan.h"
#include "../h/lex.h"
#include "../h/error.h"
#include "../h/symtb.h"

/*
 ****************************************************************
 *	Vari�veis e declara��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.6.0, de 27.08.04";

#define	INCLSZ	40

entry FILE	*fpout;		/* Arquivo a ser Gerado */

const		char *srcname,	/* Nome do Arquivo Fonte */
		*dstname;	/* Nome do Arquivo Destino */

entry int	Cflag,		/* Mant�m os Coment�rios */
		Pflag,		/* N�o coloca controles na sa�da */
		Tflag,		/* Mais diagn�sticos */
		vflag,		/* Modo Verboso */
		dflag;		/* Debug */

const char	*incld[INCLSZ + 1],	/* Diret�rios para procura de includes */
		**incldp = incld + 1;

const char	**color_vector; /* Para as cores dos modos */

/*
 ****************************************************************
 *	Ponto de Entrada					*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	int		opt;

	while ((opt = getopt (argc, argv, "PCvD:U:I:TdMH")) != EOF)
	{
		switch (opt)
		{
		    case 'P':
			Pflag++;
			break;

		    case 'C':
			Cflag++;
			break;

		    case 'v':
			vflag++;
			break;

		    case 'D':
			if (CATEG (optarg) != LETTER)
			{
			    inv_mac:
				fprintf
				(	stderr,
					"Nome de macro inv�lido: \"%s\"\n\n",
					optarg
				);
				help ();
			}
			mkpredef (optarg, S_PREDEF);
			break;

		    case 'U':
			if (CATEG (optarg) != LETTER)
				goto inv_mac;
			mkpreundef (optarg);
			break;

		    case 'I':
			if (incldp >= &incld[INCLSZ])
			{
				fprintf	(stderr, "Excesso de Op��es \"-I\"\n\n");
				help ();
			}
			
			*incldp++ = optarg;
			break;

		    case 'T':			/* LINT */
			Tflag++;
			break;

		    case 'd':
			dflag++;
			break;

		    case 'M':
			exit (0);

		    case 'H':
			help ();

		    default:
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	/*
	 *	Ajusta os ponteiros
	 */
	*incldp++ = "/usr/include";
	*incldp++ = "/usr/xwin/include";
	*incldp++ = "/usr/xwin/include/X11";
	*incldp   = NOSTR;

	argv += optind;

#undef	DEBUG
#ifdef	DEBUG
	/*
	 *	Testa a tabela de s�mbolos
	 */
    {
	SYMTB		*sp, *tst_sp, **hp, **link_place;
	int		n = 0;

	for (hp = &hashtb[0]; hp < &hashtb[HASHSZ]; hp++)
	{
		for (sp = *hp; sp != NOSYMTB; sp = sp->s_link)
		{
			tst_sp = hash (sp->s_name, &link_place);

			if   (tst_sp == NOSYMTB)
				{ error ("S�mbolo \"%s\" n�o est� na SYMTB", sp->s_name); n++; }
			elif (tst_sp != sp)
				{ error ("S�mbolo \"%s\" est� no local errado da SYMTB", sp->s_name); n++; }
			else
				error ("S�mbolo \"%s\" est� no local correto da SYMTB", sp->s_name);
		}
	}

	if (n == 0)
		error ("Tabela de s�mbolos correta");
    }
#endif	DEBUG

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stdout)), (void *)NULL, &color_vector);

	/*
	 *	Prepara o caso de erro
	 */
	error_default_function = quit;

	/*
	 *	Obt�m o arquivo de entada
	 */
	if (*argv == NOSTR)
	{
		error ("Falta especificar o arquivo de <entrada>\n");
		help ();
	}

	srcname = *argv++;

	if (readfile (srcname) < 0)
		exit (1);

	/*
	 *	Prepara o arquivo de sa�da
	 */
	if   (*argv == NOSTR)
		fpout = stdout;
	elif ((fpout = fopen (dstname = *argv++, "w")) == NOFILE)
		error ("$*N�o consegui criar \"%s\"", dstname);

	/*
	 *	Verifica se tem argumentos sup�rfluos
	 */
	if (*argv)
		error ("O argumento sup�rfluo \"%s\" ser� ignorado", *argv);

	/*
	 *	Passa � execu��o
	 */
	signal (SIGINT,  on_signal);
	signal (SIGQUIT, on_signal);

	parsefile ();

	/*
	 *	Se for verboso, ...
	 */
	if (vflag)
	{
		KPSZ		kpsz;

		/* Imprime a tabela de s�mbolos */

		printsymtb ();

		/* Imprime a Mem�ria ocupada */

		kcntl (K_GETPSZ, &kpsz);

		printf
		(
			"Texto = %d, Data = %d, Bss = (%d + %d), "
			"Stack = %d, Total = %d\n",
			(int)&etext - 0x400000,
			(int)&edata - 0x20000000,
			(int)&end - (int)&edata,
			(int)_cbreak - (int)&end,
			kpsz.k_ssize,
			(int)&etext - 0x400000 + (int)_cbreak - 0x20000000 + kpsz.k_ssize
		);
	}

	quit (nerrors);

}	/* end main */

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
		"%s - pr�processador para fontes em \"C\"\n"
		"\n%s\n"
		"\nSintaxe:\n"
		" %s [-PCTv] [-D <def> ...] [-U <id> ...] "
			"[-I <dir> ...] <entrada> [<sa�da>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-P: N�o coloca as linhas de controles na sa�da\n"
		"\t-C: Mant�m os coment�rios na sa�da\n"
		"\t-T: Emite mais diagn�sticos\n"
		"\t-v: Verboso\n"
		"\t-D: Predefine macros "
			"(<def> � da forma \"id\" ou \"id=valor\")\n"
		"\t-U: N�o permite macros com o nome <id>\n"
		"\t-I: Acrescenta <dir> � lista de busca de includes\n"
	);

	exit (2);

}	/* end help */

/*
 ****************************************************************
 *	Abandona o Programa					*
 ****************************************************************
 */
void
quit (int n)
{
	if (n != 0 && fpout != NOFILE && fpout != stdout)
		unlink (dstname);

	exit (n);

}	/* end quit */

/*
 ****************************************************************
 *	Processa Sinais						*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	quit (2);

}	/* end on_signal */
