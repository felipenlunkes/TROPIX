/*
 ****************************************************************
 *								*
 *			as.c					*
 *								*
 *	Programa principal					*
 *								*
 *	Vers�o	1.0.0, de 10.03.86				*
 *		4.8.0, de 18.11.05				*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/kcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <a.out.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/tokens.h"
#include "../h/scan.h"
#include "../h/id_sym_tb.h"
#include "../h/expr.h"
#include "../h/msg.h"
#include "../h/as.h"
#include "../h/proto.h"

/*
 ******	Vers�o do Programa e macros *****************************
 */
const char	pgversion[] =  "Vers�o:	4.8.0, de 18.11.05";

#define	ROUND(x)	(((x) + 3) & ~3)

/*
 ******	Defini��es e variaveis globais **************************
 */
entry long	*lc;		/* Location counter */

entry long	lctext,		/* Location counter, TEXT */
		lcconst,	/* Location counter, CONST */
		lcdata,		/* Location counter, DATA */
		lcbss;		/* Location counter, BSS */

entry long	tsize,		/* Tamanho da se��o TEXT */
		csize,		/* Tamanho da se��o CONST */
		dsize,		/* Tamanho da se��o DATA */
		bsize;		/* Tamanho da se��o BSS */

entry int	pass;		/* Passo atual (1 ou 2) */

entry int	section;	/* Se��o atual */

entry long	opcodeno;	/* Numerador sequencial das opera��es */

entry int	symblk;		/* "Local symbol block" atual */

entry int	aflag,		/* Gera todos os simbolos */
		vflag,		/* Verbose */
		wflag,		/* O "normal" � 16 bits (ao inv�s de 32) */
		eflag,		/* A listagem deve ser "little-endian" */
		lflag;		/* Lista o Programa Fonte */

entry int	seg16;		/* O segmento � de 16 bits (ao inv�s de 32) */

const char	*objname,	/* Nome do arquivo objeto (default: "a.out") */
		*srcname,	/* Nome do arquivo fonte */
		*listname;	/* Nome da listagem */

entry char	*rtname,	/* Nome do temporario de Reloca��o de TEXT */
		*rdname;	/* Nome do temporario de Reloca��o de DATA */

entry FILE	*src,		/* Arquivo Fonte */
		*list,		/* Listagem */
		*aout,		/* a.out */
		*reltext,	/* Reloca��o do text */
		*reldata;	/* Reloca��o do DATA */

entry int	nmsgs;		/* N�mero de Erros Encontrados */

entry long	sectoff;	/* Deslocamento dentro da se��o atual */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		on_sig (int, ...);

/*
 ****************************************************************
 *	Ponto de Entrada do m�dulo AS-INTEL 80386/486/PENTIUM	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	**av;

	if (signal (SIGINT, SIG_IGN) != SIG_IGN)
		signal (SIGINT, on_sig);

	if (signal (SIGQUIT, SIG_IGN) != SIG_IGN)
		signal (SIGQUIT, on_sig);

	if (signal (SIGTERM, SIG_IGN) != SIG_IGN)
		signal (SIGTERM, on_sig);

	/*
	 *	Assume valores por omiss�o.
	 */
	objname  = "a.out";
	listname = "a.l";

	/*
	 *	Analisa a Linha de Argumentos do Programa
	 */
	while ((opt = getopt (argc, argv, "avweo:l:D:MH")) != EOF)
	{
		switch (opt)
		{
		    case 'a':
			aflag++;
			break;

		    case 'v':
			vflag++;
			break;

		    case 'w':
			wflag++;
			break;

		    case 'e':
			eflag++;
			break;

		    case 'o' :
			objname = optarg;
			break;

		    case 'l':
			listname = optarg;
			lflag++;
			break;

		    case 'D':
			make_pre_define (optarg);
			break;

		    case 'M':
			exit (0);

		    case 'H':
			help (0);

		    default:
			fprintf (stderr, "\n");
			help (1);

		}	/* end switch */

	}	/* end while */

	argv += optind;

	if (*argv == NOSTR)
		help (1);

	/*
	 *	Inicializa algumas variaveis para o primeiro passo.
	 */
   /*** lctext	= lcconst = lcdata = lcbss = 0; ***/
	lc	= &lctext;
   /***	symblk	= 0; ***/
	pass	= 1;
	section	= TEXT;
	seg16	= wflag;
   /***	nmsgs	= 0; ***/
   /***	opcodeno = 0; ***/

	/*
	 *	Percorre a lista de arquivos, executando o primeiro passo.
	 */
	for (av = argv; *av != NOSTR; av++)
	{
		srcname = *av;

		if (vflag)
			printf ("%s:\n", srcname);

		/*
		 *	Verifica se objeto ou listagem vao-se sobrepor
		 *	ao fonte.
		 */
		if (streq (listname, srcname))
		{
			fprintf
			(	stderr,
				"%s: Voc� quer gerar a listagem em "
				"cima do programa fonte ???\n",
				pgname
			);
			quit (1);
		}

		if (streq (objname, srcname))
		{
			fprintf
			(	stderr,
				"%s: Voc� quer gerar o programa "
				"objeto em cima do programa fonte ???\n",
				pgname
			);
			quit (1);
		}

		token->l_line = latoken->l_line = 0;

		if ((src = fopen (srcname, "r")) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, srcname, strerror (errno)
			);
			quit (1);
		}

		/*
		 *	Executa o passo 1 e fecha o arquivo.
		 */
		pass1 ();

		fclose (src);
	}

	if_stack_check ();

	if (nmsgs != 0)
	{
		/*
		 *	Havendo erros, n�o passa adiante.
		 */
		fprintf
		(	stderr,
			"%s: %d erro%s durante o primeiro passo - "
			"montagem abortada\n",
			pgname,
			nmsgs,
			nmsgs > 1 ? "s" : ""
		);
		quit (1);
	}

	/*
	 *	Faz o processamento de SDI's.
	 */
	SDIs_metabolism ();

	/*
	 *	Atualiza rotulos e os tamanhos das 4 se��es.
	 */
	tsize = ROUND (lctext  + labelupdate (TEXT,  0));
	csize = ROUND (lcconst + labelupdate (CONST, tsize));
	dsize = ROUND (lcdata  + labelupdate (DATA,  tsize + csize));
	bsize = ROUND (lcbss   + labelupdate (BSS,   tsize + csize + dsize));

	if (vflag)
	{
		fprintf
		(	stderr,
			"%s: Tsize = %d * Dsize = %d * Bsize = %d\n",
			pgname,
			tsize + csize,
			dsize,
			bsize
		);
		sdistat ();
	}

	/*
	 *	Reinicializa as variaveis para o passo 2.
	 */
	lctext  = 0;
	lcconst = tsize;
	lcdata  = tsize + csize;
	lcbss   = tsize + csize + dsize;
	lc      = &lctext;

	symblk  = 0;
	pass    = 2;
	section = TEXT;
	seg16	= wflag;
   	nmsgs = 0;
   	opcodeno = 0;

	/*
	 *	Abre os arquivos de saida e a listagem.
	 */
	if (lflag)
		initlist ();

	initcode ();
	symnumber ();

	/*
	 *	Percorre a lista de arquivos, executando o segundo passo.
	 */
	for (av = argv; *av != NOSTR; av++)
	{
		srcname = *av;

		token->l_line = latoken->l_line = 0;

		if ((src = fopen (srcname, "r")) == NOFILE)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, srcname, strerror (errno)
			);
			quit (1);
		}

		/*
		 *	Executa o passo 2 e fecha o arquivo.
		 */
		pass2 ();

		fclose (src);
	}

	if_stack_check ();

	if (nmsgs != 0)
	{
		/*
		 *	Havendo erros, n�o passa adiante.
		 */
		fprintf
		(	stderr,
			"%s: %d erro%s durante o segundo passo - "
			"montagem abortada\n",
			pgname,
			nmsgs,
			nmsgs > 1 ? "s" : ""
		);
		quit (1);
	}
	
	/*
	 *	Gera o formato final do "a.out".
	 */
	finishcode ();

	/*
	 *	Termina a Listagem.
	 */
	if (lflag)
	{
		listsym ();
		fclose (list);
	}

	/*
	 *	Se for verboso, ...
	 */
	if (vflag)
	{
		KPSZ		kpsz;

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

	return (nmsgs != 0);

}	/* end main */

/*
 ****************************************************************
 *	Processa os "-D sym=val"				*
 ****************************************************************
 */
void
make_pre_define (const char *arg)
{
	MAJOR		major;
	SYMTB		*sp;
	char		*begin_of_statmt, *begin_of_exp;
	EXP		exp;

	/*
	 *	Simula "getline"
	 */
	strcpy (line, arg);

	lineprinted = 0;

	token->l_line++; 	latoken->l_line++;

	nextp = line;

	gettoken ();

	/*
	 *	Inicialmente procura "id"
	 */
	major = gettoken ();

	begin_of_statmt = token->l_begin;

	if (major != ID)
	{
		msg (ERRO, LONGMARK, "Esperava um identificador");
		return;
	}

	sp = putsym (token->l_name, token->l_len, S_DEFINE);

	/*
	 *	Agora analisa a (poss�vel) express�o
	 */
	if (latoken->l_major != EOL)
	{
		if (latoken->l_major != EQ)
		{
			gettoken ();
			msg (ERRO, LONGMARK, "Esperava um \"=\"");
			return;
		}

		gettoken ();	/* Obt�m "==" */
		gettoken ();	/* Obt�m o primeiro token da express�o */

		begin_of_exp = token->l_begin;

		expression (&exp);

		switch (exp.ex_type)
		{
		    case ERR:
			return;

		    case REAL:
			msg
			(	ERRO, MYMARK,
				"Ainda n�o aceitando valores reais",
				NOSTR, begin_of_exp, exp.ex_end
			);
			return;

		    case UNDEF:
			msg
			(	ERRO, MYMARK,
				"Express�o cont�m vari�vel(is) indefinida(s)",
				NOSTR, begin_of_exp, exp.ex_end
			);
			return;

		}	/* end switch (exp.ex_type) */

	}
	else
	{
		exp.ex_type  = ABS;
		exp.ex_value = 1;
		exp.ex_end   = token->l_end;

	}	/* end if (latoken->l_major != EOL) */

	/*
	 *	N�o permite redefini��es
	 */
	if (sp->s.s_type != UNDEF)
	{
		if (sp->s.s_value == exp.ex_value && sp->s.s_type == exp.ex_type)
		{
			msg
			(	ADVR, MYMARK,
				"Redefini��o ignorada",
				NOSTR, begin_of_statmt, exp.ex_end
			);
		}
		else
		{
			msg
			(	ERRO, MYMARK,
				"Redefini��o inv�lida",
				NOSTR, begin_of_statmt, exp.ex_end
			);
		}

		return;

	}	/* end if (sp->s.s_type != UNDEF) */

	/*
	 *	Atribui o valor
	 */
	sp->s.s_type  = exp.ex_type;
	sp->s.s_value = exp.ex_value;

}	/* end make_pre_define */

/*
 ****************************************************************
 *	Recebe os sinais					*
 ****************************************************************
 */
void
on_sig (int signo, ...)
{
	quit (1);

}	/* end on_sig */

/*
 ****************************************************************
 *	Termina o Programa Anormalmente				*
 ****************************************************************
 */
void
quit (int n)
{
	if (pass == 2)
	{
		unlink (rdname);
		unlink (rtname);
		unlink (objname);
	}

	exit (n);

}	/* end quit */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (int n)
{
	fprintf
	(	stderr,
		"%s - Montador para INTEL-80386/486/PENTIUM\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-avwe] [-o <obj>] [-l <lst>] "
			"[-D <def> ...] <fonte> ...\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-a: Inclui tamb�m os s�mbolos locais na tabela\n"
		"\t-v: Verboso\n"
		"\t-w: Monta para um segmento de 16 bits (ao inv�s de 32)\n"
		"\t-e: A listagem deve ser no estilo \"little-endian\"\n"
		"\t-o: O nome do m�dulo objeto gerado deve ser <obj> "
			"(ao inv�s de \"a.out\")\n"
		"\t-l: Gera um arquivo de listagem com o nome <lst>\n"
		"\t-D: Predefine vari�veis "
			"(<def> � da forma \"var\" ou \"var=valor\")\n"
	);

	exit (n);

}	/* end help */
