/*
 ****************************************************************
 *								*
 *			ld.c					*
 *								*
 *	Link-editor de m�dulos objeto				*
 *								*
 *	Vers�o	1.0.0, de 08.01.87				*
 *		4.3.0, de 12.07.02				*
 *								*
 *	M�dulo: ld						*
 *		Utilit�rios b�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <a.out.h>

#include "../h/ld.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char		pgversion[] =  "Vers�o:	4.3.0, de 12.07.02";

/*
 ****** Op��es de link-edi��o ***********************************
 */
entry int		rflag,		/* Mantem a reloca��o, n�o define common */
			bflag,		/* Gera uma biblioteca compartilhada */
			nflag,		/* m�dulo executavel reentrante */
			sflag,		/* "Strip" - Remove SYMTB, RT e RD */
			vflag,		/* Verbose */
			mflag,		/* Gera mapa de link-edi��o */
			uflag,		/* lista os n�o referenciados */
			dotflag;	/* Tempor�rias no diret�rio corrente */

/*
 ****** Vari�veis globais ***************************************
 */
entry int		shared_lib_given; /* Foram dadas bibliotecas compartilhadas */

entry const char	*obj_nm = "a.out"; /* Nome do m�dulo final */

entry const char	*entry_nm;	/* Nome do s�mbolo de "Entry-Point" */

entry off_t		TEXT_ORG = -1,	/* Endereco inicial do "TEXT" */
			DATA_ORG = -1,	/* Endereco inicial do "DATA" */
			COMMON_ORG,	/* Endereco inicial do "COMMON" */
			BSS_ORG;	/* Endereco inicial do "BSS" */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void			on_signal (int, ...);
void	 		quit (int);
void			help (void);

/*
 ****************************************************************
 *	Link-editor de m�dulos objeto				*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const char	*str;

	/*
	 *	Analisa a linha de argumentos para o programa
	 *
	 *	ld [-rbsmnvu.] [-o <obj>] [-e <ent>] [-T <tb>] [-D <db>] <m> ... [-l<x> ...]
	 *
	 */
	while ((opt = getopt (argc, argv, "rbsmnvu.o:e:T:D:MH")) != EOF)
	{
		switch (opt)
		{
		    case 'r':			/* Mantenha a reloca��o */
			rflag++;
			break;

		    case 'b':			/* Gera uma biblioteca compartilhada */
			bflag++;
			break;

		    case 's':			/* Sem tabela de s�mbolos */
			sflag++;
			break;

		    case 'm':			/* Imprime o mapa de m�dulos */
			mflag++;
			break;

		    case 'n':			/* Programa reentrante */
			nflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'u':			/* Lista os n�o referenciados */
			uflag++;
			break;

		    case '.':			/* Tempor�rias no diret�rio corrente */
			dotflag++;
			break;

		    case 'o':			/* Nome do objeto gerado */
			obj_nm = optarg;
			break;

		    case 'e':			/* Nome do ponto de entrada */
			entry_nm = optarg;
			break;

		    case 'T':			/* Origem da se��o TEXT */
			TEXT_ORG = strtol (optarg, &str, 0);

			if (*str != '\0')
				error ("@Origem da se��o TEXT \"%s\" inv�lida", optarg);

			break;

		    case 'D':			/* Origem da se��o DATA */
			DATA_ORG = strtol (optarg, &str, 0);

			if (*str != '\0')
				error ("@Origem da se��o DATA \"%s\" inv�lida", optarg);

			break;

		    case 'M':
			exit(0);

		    case 'H':		/* Help */
			help ();

		    default:		/* Erro */
			fprintf (stderr, "\n");
			help ();

		}	/* end switch */

	}	/* end while */

	if (nflag + rflag + bflag > 1)
		error ("@Op��es conflitantes: \"-n\", \"-r\" e \"-b\" s�o mutuamente exclusivas");

	if ((rflag + bflag) && sflag)
		error ("@Op��es conflitantes: \"-r\" ou \"-b\" com \"-s\"");

	if (error_standard_count)
		quit (1);

   /***	argc -= optind; ***/
	argv += optind;

	if (*argv == NOSTR)
		return (0);

	/*
	 *	Programa os sinais INT e QUIT
	 */
	if (signal (SIGINT,  SIG_IGN) != SIG_IGN)
		signal (SIGINT, on_signal);

	if (signal (SIGQUIT, SIG_IGN) != SIG_IGN)
		signal (SIGQUIT, on_signal);

	/*
	 *	Prepara "error"
	 */
	error_default_function = quit;

	/*
	 ******	Executa os diversas passos ******************************
	 */

	/*
	 *	Passo 1: Monta a Tabela Global de S�mbolos
	 */
	pass1 (argv);

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 2: Verifica os m�dulos necess�rios das bibliotecas regulares
	 */
	pass2 ();

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 3: Atribui valores definitivos aos s�mbolos
	 */
	pass3 ();

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 4: Prepara os arquivos para a gera��o
	 */
	pass4 ();

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 5: Gera as diversas se��es
	 */
	pass5 ();

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 6: Verifica os s�mbolos das bibliotecas compartilhadas
	 */
	pass6 ();

	if (error_standard_count)
		quit (1);

	/*
	 *	Passo 7: Coda: Escreve as diversas se��es e o cabe�alho
	 */
	pass7 ();

	if (error_standard_count)
		quit (1);

#ifdef	COLIS�O
	colision_tst ();
#endif	COLIS�O

	return (0);

}	/* end ld */

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
 *	Termina o Programa Anormalmente				*
 ****************************************************************
 */
void
quit (int n)
{
	if (aout_fd >= 0)
		unlink (obj_nm);

   /***	unlink (text_nm); ***/
   /***	unlink (data_nm); ***/

	if (rt_nm)
		unlink (rt_nm);

	if (rd_nm)
		unlink (rd_nm);

	exit (n);

}	/* end quit */

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
		"%s - link-editor de m�dulos objeto\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"  %s [-rbsmnvu.] [-o <obj>] [-e <ent>] "
		"[-T <tb>] [-D <db>] <m> ... [-l<x> ...]\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-r: Mantem a reloca��o, n�o define COMMON\n"
		"\t-b: Gera uma biblioteca compartilhada\n"
		"\t-s: Gera o m�dulo objeto sem tabela de s�mbolos\n"
		"\t-m: Gera um mapa de link-edi��o\n"
		"\t-n: Gera o m�dulo objeto reentrante\n"
		"\t-v: Verboso\n"
		"\t-u: Lista os s�mbolos n�o referenciados\n"
		"\t    Se for dado duas vezes, lista tamb�m os "
			"das bibliotecas\n"
		"\t-.: Usa os arquivos tempor�rios no diret�rio corrente\n"
	);

	fprintf
	(	stderr,
		"\t-o: O nome do m�dulo gerado ser� <obj> ao inv�s de \"a.out\"\n"
		"\t-e: O nome do s�mbolo de entrada ser� <ent> ao inv�s de \"start\"\n"
		"\t-T: O endere�o do in�cio da se��o \"text\" ser� <tb>\n"
		"\t-D: O endere�o do in�cio da se��o \"data\" ser� <db>\n"
		"\nObs.:"
		"\t<m> ... s�o m�dulos objeto\n"
		"\t<x> ... s�o abreviaturas para nomes de bibliotecas\n"
	);

	exit (2);

}	/* end help */
