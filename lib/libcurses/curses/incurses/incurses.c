/*
 ****************************************************************
 *								*
 *			incurses.c				*
 *								*
 *	Entra em  modo "curses"					*
 *								*
 *	Vers�o	2.0.0, de 17.04.88				*
 *		3.0.0, de 04.03.95				*
 *								*
 *	M�dulo: incurses					*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termio.h>
#include <errno.h>
#include <curses.h>
#include <terminfo.h>

#include "../../terminfo/h/defs.h"

#include "../h/term.h"
#include "../h/local.h"

/*
 ****************************************************************
 *	Defini��es Locais					*
 ****************************************************************
 */
#define	XON		0x11		/* <^Q> */
#define	XOFF		0x13		/* <^S> */

static const char *pgname = "";	/* Nome do programa deste processo */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
static void	getsignals (int, ...);

/*
 ****************************************************************
 *	Entra em  modo "curses"					*
 ****************************************************************
 */
int
incurses (const char *name)
{
	register int 	td, ch;

	/*
	 *	Pr�logo
	 */
	if (_windows == NOWINDOW && (_windows = malloc (_NWINDOWS * sizeof (WINDOW))) == NOWINDOW)
		return (ERR);

	/*
	 *	Guarda sempre o �ltimo nome dado
	 */
	if (name != NOSTR)
		pgname = name;

	/*
	 *	Estabelece o terminal corrente
	 */
	if (_curterm == NOTERM)
	{
		/*
		 *	Primeiro terminal aberto
		 */
		if ((td = newterm (NOSTR, stdout, stdin)) < 0)
			return (ERR);

		getsignals (0);

		setterm (td);

		/*
		 *	Cadeia de incializa��o
		 */
		if (_curterm->t_info.i_strings[s_is1] != NOSTR)
		{
			fputs
			(	_curterm->t_info.i_strings[s_is1],
				_curterm->t_outfp
			);
		}
	}

	/*
	 *	Configura��o da Comunica��o:
	 *
	 *	Protocolo XON/XOFF a cargo do sistema, entrada e
	 *	sa�da n�o processadas, sem echo e sem pagina��o
	 */
	_curterm->t_termio.c_lflag &= ~(ECHO|ICANON);
	_curterm->t_termio.c_oflag &= ~OPOST;
	_curterm->t_termio.t_page = 0;

	if (ioctl (fileno (_curterm->t_infp), TCSETNR, &_curterm->t_termio) < 0)
	{
		fprintf
		(	stderr,
			"%s (curses): N�o consegui alterar "
			"o modo do terminal (%s)\n",
			pgname, strerror (errno)
		);
		return (ERR);
	}

	/*
	 *	Retornando a Curses
	 */
	if (check (_curterm->t_flags, T_OUT))
	{
		/*
		 *	Cadeia de incializa��o
		 */
		if (_curterm->t_info.i_strings[s_is2] != NOSTR)
		{
			fputs
			(	_curterm->t_info.i_strings[s_is2],
				_curterm->t_outfp
			);
		}

		/*
		 *	Posiciona o cursor na �ltima linha
		 */
		fputs
		(
			parmexec
			(	_curterm->t_info.i_strings[s_cup],
				LINES - 1,
				0
			),
			_curterm->t_outfp
		);

		fputs ("\nTecle para continuar", _curterm->t_outfp);
		fflush (_curterm->t_outfp);

		do
		{
			ch = getc (_curterm->t_infp);
		}
		while (ch == XON || ch == XOFF);
	}

	/*
	 *	Padr�o inicial para Flags:
	 */
	_curterm->t_flags |= T_CLEAR;

	return (OK);

}	/* end incurses */

/*
 ****************************************************************
 *	Tratamento de Sinais					*
 ****************************************************************
 */
static void
getsignals (int sig, ...)
{
	void		(*getint) (int, ...), (*getquit) (int, ...);

	switch (sig)
	{
		/*
		 *	Estabelece intercepta��o
		 */
	    case 0:
		if ((getint = signal (SIGINT, getsignals)) != SIG_DFL)
			signal (SIGINT, getint);

		if ((getquit = signal (SIGQUIT, getsignals)) != SIG_DFL)
			signal (SIGQUIT, getquit);
		break;

	    case SIGINT:
		outcurses ();
		fprintf (stderr, "%s: Interrup��o (SIGINT)\n", pgname);
		exit (1);

	    case SIGQUIT:
		outcurses ();
		fprintf (stderr, "%s: Interrup��o (SIGQUIT)\n", pgname);
		abort ();
		exit (1);
	}

}	/* end getsignals */
