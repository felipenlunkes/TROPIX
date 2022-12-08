/*
 ****************************************************************
 *								*
 *			coremap.c				*
 *								*
 *	Imprime um mapa de aloca��o da mem�ria			*
 *								*
 *	Vers�o	1.0.0, de 04.07.86				*
 *		3.2.3, de 02.11.99				*
 *								*
 *	M�dulo: coremap						*
 *		Utilit�rios especiais				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/scb.h>
#include <sys/region.h>

#include <sys/kfile.h>
#include <sys/map.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <termio.h>
#include <terminfo.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.2.3, de 02.11.99";

#define	elif	else if
#define	EVER	;;

/*
 ******	Defini��es do video *************************************
 */
#define	GRAIN		256		/* Gr�o (deve ser fra��o de KB) */

#define	PERCENT(a, b)	((100 * (a)) / (b))

#define	ROUNDDIV(a, d)	(((a) + (d) - (1)) / (d))

#ifdef	ICA
#define	BYTOKB(b)	((b) / KBSZ)
#define	KBTOBY(b)	((b) * KBSZ)
#endif	ICA

/*
 ****** Vari�veis diversas **************************************
 */
entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

entry int	periodo = 1;	/* Per�odo da atualiza��o da tela */

entry INFO	info;		/* Informa��es sobre o Terminal */

entry TERMIO	old_termio, new_termio;	/* Controle de pagina��o do terminal */

entry char	*tela;		/* O gr�fico na tela */

entry int	MAXLINE;	/* Nr. de linhas */
entry int	MAXCOL;		/* Nr. de Caracteres por linha */

entry int	MAXCHAR;	/* Nr. Max. de caracteres da tela */

entry int	old_addr = -2;	/* Endereco anterior da tela */

/*
 ******	Par�metros da mem�ria ***********************************
 */
entry int	END_KERMEM;	/* Fim da Memoria Kernel */

entry int	BEGIN_USRMEM;	/* Inicio da Memoria User */

entry int	END_USRMEM;	/* Final do usu�rio */

entry int	END_PHYSMEM;	/* Tamanho da mem. fisica em bytes */

entry int	ALPHA;		/* Nr. de KB por linha da tela */

entry int	DELTA;		/* Nr. de BYTES por caracter da tela */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		putregion (int, int, int);
void		display_char (int, char);
void		on_signal (int, ...);
void		quit (int);
void		setparam (int, int);
void		help (void);

/*
 ****************************************************************
 *	Imprime um mapa de aloca��o da mem�ria			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	TERMIO		*tp;
	const MAP	*mp;
	int		opt;
	int		addr;
	const char	*str;
	int		used, unused, old_unused = -1;
	int		last_end, total_user_bytes;
	SCB		scb;
	MAP		*kernel_coremap, *copy_coremap;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
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
	 *	Verifica se o <per�odo> foi especificado
	 */
	if (argc > 1)
		help ();

	if (argc == 1)
	{
		if ((periodo = strtol (argv[0], &str, 0)) <= 0 || *str)
		{
			fprintf (stderr, "%s: per�odo inv�lido: \"%s\"\n", pgname, argv[0]);
			exit (1);
		}
	}

	/*
	 *	Obtem as caracter�sticas do terminal
	 */
	if (getinfo (NOSTR, &info) == 0)
		exit (1);

	if (info.i_strings[s_clear] == NOSTR)
	{
		fprintf (stderr, "%s: N�o sei como limpar a tela\n", pgname);
		exit (1);
	}

	if (info.i_strings[s_cup] == NOSTR)
	{
		fprintf (stderr, "%s: N�o sei como endere�ar a tela\n", pgname);
		exit (1);
	}

#undef	DEBUG
#ifdef	DEBUG
	printf
	(	"clear = \"%s\", cup = \"%s\"\n",
		info.i_strings[s_cup], info.i_strings[s_clear]
	);
#endif	DEBUG

	/*
	 *	Obt�m o SCB
	 */
	if ((int)getscb (&scb) == -1)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o SCB (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

#ifdef	ICA
	total_user_bytes = PGTOBY (scb.y_enducore - scb.y_ucore);
#elif	PC
	total_user_bytes = PGTOBY (scb.y_enducore1 - scb.y_ucore1);
#endif	ICA/PC

	/*
	 *	Mapeia a tabela da mem�ria
	 */
	if ((int)(kernel_coremap = phys (scb.y_map, scb.y_nmap * sizeof (MAP), O_KERNEL|O_RDONLY)) == -1)
	{
		fprintf
		(	stderr,
			"%s: N�o foi poss�vel mapear a tabela de mem�ria (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Aloca mem�ria para a c�pia instant�nea da tabela de mem�ria
	 */
	if ((copy_coremap = malloc (scb.y_nmap * sizeof (MAP))) == (MAP *)NULL)
	{
		fprintf (stderr, "%s: N�o consegui mem�ria para a c�pia da tabela\n", pgname);
		exit (1);
	}

	/*
	 *	Tira o "PAGING" do Terminal
	 */
	ioctl (1, TCGETS, &old_termio);
	new_termio = old_termio;
	new_termio.c_cc[VPAGE] = 0;
	ioctl (1, TCSETNR, &new_termio);

	/*
	 *	Calcula o n�mero de linhas e colunas
	 */
	tp = &new_termio;

	if (tp->t_nline == 0)
		tp->t_nline = 24;

	if (tp->t_ncol == 0)
		tp->t_ncol = 80;

	MAXLINE = tp->t_nline - 2;
	MAXCOL  = tp->t_ncol  - 8;

	MAXCHAR = MAXLINE * MAXCOL;  

#ifdef	DEBUG
	printf
	(	"MAXLINE = %d, MAXCOL = %d, MAXCHAR = %d\n",
		MAXLINE, MAXCOL, MAXCHAR
	);
#endif	DEBUG

	/*
	 *	Calcula os parametros globais da memoria
	 */
#ifdef	ICA
	setparam (PGTOBY (scb.y_endpmem), 0);

	END_KERMEM   = PGTOBY (scb.y_endkernel) / DELTA;
	BEGIN_USRMEM = PGTOBY (scb.y_ucore) / DELTA;
	END_USRMEM  = PGTOBY (scb.y_enducore) / DELTA;
#elif	PC
	setparam ((int)scb.y_endpmem - (int)SYS_ADDR, 0);

	END_KERMEM   = (PGTOBY (scb.y_ucore1) - (int)SYS_ADDR) / DELTA;
	BEGIN_USRMEM = (PGTOBY (scb.y_ucore1) - (int)SYS_ADDR) / DELTA;
	END_USRMEM  = (PGTOBY (scb.y_enducore1) - (int)SYS_ADDR) / DELTA;
#endif	ICA/PC

#ifdef	DEBUG
	printf
	(	"END_KERMEM = %d, BEGIN_USRMEM = %d, END_USRMEM = %d\n",
		END_KERMEM, BEGIN_USRMEM, END_USRMEM
	);
	sleep (5);
#endif	DEBUG

	/*
	 *	Aloca mem�ria para a tela
	 */
	if ((tela = malloc (MAXCHAR * sizeof (char))) == NOSTR)
	{
		fprintf (stderr, "%s: N�o consegui mem�ria para a tela\n", pgname);
		exit (1);
	}

	memset (tela, '\0', MAXCHAR);

	/*
	 *	Prepara os sinais
	 */
	signal (SIGINT, on_signal);
	signal (SIGTERM, on_signal);

	/*
	 *	Coloca a coluna de endere�os	
	 */
	fputs (info.i_strings[s_clear], stdout);

	for (addr = 0; addr < BYTOKB (END_PHYSMEM); addr += ALPHA)
		printf ("%5d\n", addr);

	/*
	 *	Preenche a �rea do kernel com '+'
	 */
	for (addr = 0; addr < END_KERMEM; addr++)
		display_char (addr, '+');

	/*
	 *	Preenche a �rea entre o fim do kernel e o come�o
	 *	da mem�ria user com 'o'
	 */
	for (/* vazio */; addr < BEGIN_USRMEM; addr++)
		display_char (addr, 'o');

	/*
	 *	Preenche a �rea do RAMD com '+'
	 */
#ifdef	ICA
	for (addr = PGTOBY (scb.y_ramd) / DELTA; addr < PGTOBY (scb.y_endramd) / DELTA; addr++)
		display_char (addr, '+');
#elif	PC
	for
	(	addr = ((int)scb.y_ramd0 - (int)SYS_ADDR) / DELTA;
		addr < ((int)scb.y_endramd0 - (int)SYS_ADDR) / DELTA;
		addr++
	)
	{
		display_char (addr, '+');
	}

	for
	(	addr = ((int)scb.y_ramd1 - (int)SYS_ADDR) / DELTA;
		addr < ((int)scb.y_endramd1 - (int)SYS_ADDR) / DELTA;
		addr++
	)
	{
		display_char (addr, '+');
	}
#endif	ICA/PC

	/*
	 *	Malha fazendo o gr�fico na tela
	 */
	for (EVER)
	{
		unsigned	CORE_DIFF;
		MAP		*head;

		/*
		 *	Tira o instant�neo da tabela
		 */
		memmove (copy_coremap, kernel_coremap, scb.y_nmap * sizeof (MAP));

		CORE_DIFF = (int)copy_coremap - (int)scb.y_map;

		head = copy_coremap;	/* A cabe�a � a primeira entrada */

		/*
		 *	Inicializa��o
		 */
#ifdef	ICA
		last_end = PGTOBY (scb.y_ucore); 
#elif	PC
		last_end = PGTOBY (scb.y_ucore1) - (int)SYS_ADDR; 
#endif	ICA/PC
		addr = BEGIN_USRMEM;
		unused = 0;

		/*
		 *	Desenha as regi�es
		 */
		for
		(	mp = (MAP *)((int)head->a_forw + CORE_DIFF);
			mp != head;
			mp = (MAP *)((int)mp->a_forw + CORE_DIFF)
		)
		{
			long		a_size = PGTOBY (mp->a_size);
			long		a_area = PGTOBY (mp->a_area);
#ifdef	PC
			a_area -= (int)SYS_ADDR;
#endif	PC
			unused += a_size;

			putregion (last_end, a_area, a_size);

			last_end = a_area + a_size;
		}

		/*
		 *	Completa as por��es restantes com '*'
		 */
		for (addr = last_end / DELTA; addr < END_USRMEM; addr++)
			display_char (addr, '*');
	
		/*
		 *	Verifica se mudou o total
		 */
		if (unused != old_unused)
		{
			used = total_user_bytes - unused;

			fputs (parmexec (info.i_strings[s_cup], MAXLINE+1, (MAXCOL>>1) - 30), stdout);

			printf
			(	"COREMAP: [* = %d] total (usu�rio): %d KB, usado: %d KB (%d %%)\r",
				DELTA,
				BYTOKB (total_user_bytes),
				BYTOKB (used),
				PERCENT (used, total_user_bytes)
			);

			old_unused = unused;
		}
		else
		{
			fputs (parmexec (info.i_strings[s_cup], MAXLINE+1, 0), stdout);
		}

		/*
		 *	Espera o per�odo
		 */
		fflush (stdout);
		sleep (periodo);

	}	/* end for (EVER) */

}	/* end coremap */

/*
 ****************************************************************
 *	Imprime uma regi�o na tela				*
 ****************************************************************
 */
void
putregion (int last_end, int begin, int sz)
{
	int		i;
	int		addr;

	/*
	 *	P�e o buraco da tabela (mem�ria alocada)
	 */
	for (i = begin - last_end, addr = last_end / DELTA; i > 0; i -= DELTA)
		display_char (addr++, '*');

	/*
	 *	P�e a entrada da tabela (mem�ria livre)
	 */
	for (/* vazio */; sz >= DELTA; sz -= DELTA)
		display_char (addr++, '.');

}	/* end putregion */

/*
 ****************************************************************
 *	Coloca um  caractere no gr�fico 			*
 ****************************************************************
 */
void
display_char (int addr, char ch)
{
	if (tela[addr] == ch)
		return;

	tela[addr] = ch;

	if (old_addr != addr - 1 || addr % MAXCOL == 0)
	{
		fputs
		(	parmexec
			(	info.i_strings[s_cup],
				addr / MAXCOL,
				6 + addr % MAXCOL
			),
			stdout
		);
	}

	old_addr = addr; putchar (ch);

}	/* end display_char */

/*
 ****************************************************************
 *	Prepara os parametros da tela				*
 ****************************************************************
 */
void
setparam (int maxmem, int pr)
{
	int		n, nchars, graos, nlinhas;

	END_PHYSMEM = maxmem;

	if (END_PHYSMEM % KBSZ)
	{
		fprintf
		(	stderr,
			"%s: A mem�ria (%d Bytes) n�o � m�ltipla de KBSZ?\n",
			pgname, END_PHYSMEM
		);
	}

	/*
	 *	Calcula o no. total de gr�os
	 */
	graos = END_PHYSMEM / GRAIN;

	/*
	 *	Calcula o no. de gr�os por char
	 */
	n = ROUNDDIV (graos, MAXCHAR);

	/*
	 *	Calcula o no. total de chars
	 */
	nchars = ROUNDDIV (graos, n);

	/*
	 *	Calcula o no. total de linhas
	 */
	nlinhas = ROUNDDIV (nchars, MAXCOL);

	/*
	 *	Calcula DELTA, em bytes/char
	 */
	DELTA = n * GRAIN;

	/*
	 *	Calcula ALPHA, em KB/linha
	 */
	ALPHA = DELTA * MAXCOL / KBSZ;

	/*
	 *	Para imprimir a tabela	
	 */
	if (pr)
	{
		printf
		(	"%d\t\t%d\t\t%d		%d		%d\n",
			BYTOKB (END_PHYSMEM),
			ALPHA,
			DELTA,
			nlinhas,
			nchars
		);
	}

}	/* end setparam */

/*
 ****************************************************************
 *	Em caso de sinais, ...					*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	quit (1);

}	/* end on_signal */

/*
 ****************************************************************
 *	Encerramento do Programa				*
 ****************************************************************
 */
void
quit (int signo)
{
	fputs (parmexec (info.i_strings[s_cup], MAXLINE+1, 0), stdout);
	fflush (stdout);

	ioctl (1, TCSETAW, &old_termio);
	putchar ('\n');
	exit (exit_code);

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
		"%s - imprime um mapa de aloca��o da mem�ria\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [<per�odo>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nArgs:\t<per�odo>: Per�odo entre atualiza��es "
		"(normalmente 1 segundo)\n"
	);

	exit (2);

}	/* end help */
