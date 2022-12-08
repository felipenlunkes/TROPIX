/*
 ****************************************************************
 *								*
 *			ttyin.c					*
 *								*
 *	Interface geral para terminais (parte II)		*
 *								*
 *	Vers�o	3.0.00, de 15.12.94				*
 *		3.0.11, de 15.06.97				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/sync.h"
#include "../h/scb.h"
#include "../h/region.h"

#include "../h/signal.h"
#include "../h/tty.h"
#include "../h/uproc.h"

#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Macros de convers�es de caracteres			*
 ****************************************************************
 */
#define	DEL		0x7F

#define	isaccent(c)	(chartb[c] & 0x0100)
#define isupper(c)	(chartb[c] & 0x0080)
#define islower(c)	(chartb[c] & 0x0040)
#define	isdigit(c)	('0' <= (c) && (c) <= '9')
#define	isword(c)	(isdigit(c) || chartb[c] & 0x00C0)
#define iscntrl(c)	((c) < ' ' || (c) == DEL)
#define	ischave(c)	(chartb[c] & 0x0020)
#define isparen(c)	(chartb[c] & 0x0010)
#define	isespec(c)	(chartb[c] & 0x0008)

/*
 ****************************************************************
 *	Tabela de acentos					*
 ****************************************************************
 */
typedef struct
{
	ushort	a_fonte;	/* Fonte: pares */
	ushort	a_destino;	/* Destino: resultado da convers�o */

}	ACENTO;

#define	OR(a, b)	((a << 8) | b)

const ACENTO	acento[] =
{
	OR ('~', 'A'),	0xC3,	/* � */
	OR ('~', 'a'),	0xE3,	/* � */
	OR ('~', 'O'),	0xD5,	/* � */
	OR ('~', 'o'),	0xF5,	/* � */
	OR (',', 'C'),	0xC7,	/* � */
	OR (',', 'c'),	0xE7,	/* � */
	OR (',', 'z'),	0xDF,	/* � */
	OR ('\'','A'),	0xC1,	/* � */
	OR ('\'','a'),	0xE1,	/* � */
	OR ('\'','E'),	0xC9,	/* � */
	OR ('\'','e'),	0xE9,	/* � */
	OR ('\'','I'),	0xCD,	/* � */
	OR ('\'','i'),	0xED,	/* � */
	OR ('\'','O'),	0xD3,	/* � */
	OR ('\'','o'),	0xF3,	/* � */
	OR ('\'','U'),	0xDA,	/* � */
	OR ('\'','u'),	0xFA,	/* � */
#if (0)	/*******************************************************/
	OR ('\'','C'),	0xC7,	/* � */
	OR ('\'','c'),	0xE7,	/* � */
	OR ('\'','z'),	0xDF,	/* � */
#endif	/*******************************************************/
	OR ('^', 'A'),	0xC2,	/* � */
	OR ('^', 'a'),	0xE2,	/* � */
	OR ('^', 'E'),	0xCA,	/* � */
	OR ('^', 'e'),	0xEA,	/* � */
	OR ('^', 'I'),	0xCE,	/* � */
	OR ('^', 'i'),	0xEE,	/* � */
	OR ('^', 'O'),	0xD4,	/* � */
	OR ('^', 'o'),	0xF4,	/* � */
	OR ('^', 'U'),	0xDB,	/* � */
	OR ('^', 'u'),	0xFB,	/* � */
	OR ('`', 'A'),	0xC0,	/* � */
	OR ('`', 'a'),	0xE0,	/* � */
	OR ('`', 'E'),	0xC8,	/* � */
	OR ('`', 'e'),	0xE8,	/* � */
	OR ('`', 'I'),	0xCC,	/* � */
	OR ('`', 'i'),	0xEC,	/* � */
	OR ('`', 'O'),	0xD2,	/* � */
	OR ('`', 'o'),	0xF2,	/* � */
	OR ('`', 'U'),	0xD9,	/* � */
	OR ('`', 'u'),	0xF9,	/* � */
	OR (':', 'A'),	0xC4,	/* � */
	OR (':', 'a'),	0xE4,	/* � */
	OR (':', 'E'),	0xCB,	/* � */
	OR (':', 'e'),	0xEB,	/* � */
	OR (':', 'I'),	0xCF,	/* � */
	OR (':', 'i'),	0xEF,	/* � */
	OR (':', 'O'),	0xD6,	/* � */
	OR (':', 'o'),	0xF6,	/* � */
	OR (':', 'U'),	0xDC,	/* � */
	OR (':', 'u'),	0xFC,	/* � */
#if (0)	/*******************************************************/
	OR ('=', 'a'),	0xAA,	/* � */
	OR ('=', 'o'),	0xBA,	/* � */
#endif	/*******************************************************/
	0,		0
};

/*
 ****************************************************************
 *	Processamento do caracter na entrada			*
 ****************************************************************
 */
void
ttyin (register int c, register TTY *tp)
{
	register ushort		iflag, lflag;
	register const ACENTO	*ap;
	int			oc, orc;

	/*
	 *	 Chamado pela Interrup��o
	 */
	lflag = tp->t_lflag;

	/*
	 ******	Entrada modo de COMUNICA��ES ********************
	 */
	if (lflag & ICOMM)
	{
		if (tp->t_inq.c_count > TTYCOMMPANIC)
		{
#ifdef	MSG
			printf
			(	"ttyin: PANIC da clist (comm), \"%s\" (%x)\n",
				tp->t_termio.c_name, tp->t_dev
			);
#endif	MSG
			ttyiflush (tp);
			return;
		}

		SPINLOCK (&tp->t_inq.c_lock);

		if (cput (c, &tp->t_inq) < 0)
		{
			SPINFREE (&tp->t_inq.c_lock);
#ifdef	MSG
			printf
			(	"ttyin: Falta de CBLK (comm), \"%s\" (%x)\n",
				tp->t_termio.c_name, tp->t_dev
			);
#endif	MSG
			ttyiflush (tp);
			return;
		}

		if (tp->t_inq.c_count >= tp->t_min)
		{
			EVENTDONE (&tp->t_inqnempty);

			if (tp->t_attention_set && tp->t_uproc->u_attention_index < 0)
			{
				tp->t_attention_set = 0;
				tp->t_uproc->u_attention_index = tp->t_index; 
				EVENTDONE (&tp->t_uproc->u_attention_event);
			}
		}

		SPINFREE (&tp->t_inq.c_lock);

		return;

	}	/* end entrada COMM */

	/*
	 ******	Entrada modo RAW ou COOKED **********************
	 */
	if (tp->t_inq.c_count > TTYPANIC)
	{
#ifdef	MSG
		printf
		(	"ttyin: PANIC da clist (raw/cooked), \"%s\" (%x)\n",
			tp->t_termio.c_name, tp->t_dev
		);
#endif	MSG
		ttyiflush (tp);
		return;
	}

	/*
	 *	Verifica se deve tirar o 8. bit
	 */
	iflag = tp->t_iflag;

	if (iflag & ISTRIP)
		c &= SETEB;

	/*
	 *	Verifica se foi um SINAL
	 */
	if
	(	(c == tp->t_quit || c == tp->t_intr) &&
		(lflag & ISIG) &&
		(tp->t_state & ESCAPE) == 0
	)
	{
		if ((lflag & NOFLSH) == 0)
		{
			ttyiflush (tp);
			ttyoflush (tp);
		}

		sigtgrp (tp->t_tgrp, c == tp->t_intr ? SIGINT : SIGQUIT);

		if ((lflag & ECHO) == 0)
			return;

		ttyout (  c,  tp);
		ttyout ('\n', tp);

		goto out;
	}

	/*
	 *	Verifica o tipo de entrada
	 */
	if ((lflag & ICANON) == 0)
		goto putq;

	/*
	 *	Entrada COOKED
	 */
	tp->t_lno = 0;

	if (tp->t_state & ESCAPE)
	{
		tp->t_state &= ~ESCAPE;

		if (tp->t_escchar == 0)
		{
			/*
			 *	Tratamento do ESCAPE "\"
			 *	Lembre-se que "ttyecho" � uma macro!
			 */
			if (isupper (c))
			{
				ttyecho (c + ('a' - 'A'), tp);
			}
			else
			{
				ttyecho (c, tp);
			}

			if (isparen (c))
				c = ttyconv ("{(})|!~^`'", c);

			SPINLOCK (&tp->t_inq.c_lock);

			if (cput (c, &tp->t_inq) < 0)
				{ SPINFREE (&tp->t_inq.c_lock); return; }

			SPINFREE (&tp->t_inq.c_lock);

			goto out;
		}
		else
		{
			/*
			 *	Tratamento dos ACENTOS
			 */
			oc = tp->t_escchar;
			tp->t_escchar = 0;

			if   (c == '\\')
			{
				SPINLOCK (&tp->t_inq.c_lock);
				cput (oc, &tp->t_inq);
				SPINFREE (&tp->t_inq.c_lock);

				return;
			}

			orc = OR (oc, c); 

			for (ap = acento; ap->a_fonte; ap++)
			{
				if (ap->a_fonte == orc)
				{
					/*
					 *	Achou o acento dado
					 */
					ttyecho ('\b', tp);
					c = ap->a_destino;
					goto putq;
				} 
			}

			/*
			 *	O acento dado n�o existe
			 */
			SPINLOCK (&tp->t_inq.c_lock);
			cput (oc, &tp->t_inq);
			SPINFREE (&tp->t_inq.c_lock);

			if (isaccent (c))
			{
				tp->t_state |= ESCAPE;
				tp->t_escchar = c;

				goto echo;
			}

			/* continua o fluxo normal */
		}
	}

	/*
	 *	Processa o start/stop pelo ^S, ^Q
	 */
	if (tp->t_state & TTYSTOP)
	{
		/*
		 *	Est� no Stop State
		 */
		if (iflag & IXANY || c == CSTART)
		{
			tp->t_state &= ~TTYSTOP;
			tp->t_lno = 1;
			(*tp->t_oproc) (tp, 0);
		}
		return;

	}
	else
	{
		/*
		 *	N�o est� no Stop State
		 */
		if (iflag & IXON && c == CSTOP)
		{
			tp->t_state |= TTYSTOP;
#ifdef	T_STOP
			(*ciotab[MAJOR(tp->t_dev)].w_stop) (tp);
#endif	T_STOP
			return;
		}

		if ((iflag & (IXON|IXANY)) == IXON && c == CSTART)
			return;
	}

	/*
	 *	Examina os "finais" de linha
	 */
	if (c == '\r')
	{
		if (iflag & IGNCR)
			return;

		if (iflag & ICRNL)
			c = '\n';
	}
	elif (c == '\n' && iflag & INLCR)
	{
		c = '\r';
	}

	if (c == '\n')
	{
		SPINLOCK (&tp->t_inq.c_lock);
		cput (c, &tp->t_inq);
		SPINFREE (&tp->t_inq.c_lock);

		if (lflag & (ECHO|ECHONL))
			ttyout ('\n', tp);

		goto nlc;
	}

	/*
	 *	Examina o EOF
	 */
	if (c == tp->t_eof)
	{
		ttyecho (c, tp);
		ttyecho ('\n', tp);
	    nlc:
		SPINLOCK (&tp->t_inq.c_lock);

		if (cput (DELIM, &tp->t_inq) == 0)
		{
			tp->t_delimcnt++;

			EVENTDONE (&tp->t_inqnempty);

			if (tp->t_attention_set && tp->t_uproc->u_attention_index < 0)
			{
				tp->t_attention_set = 0;
				tp->t_uproc->u_attention_index = tp->t_index; 
				EVENTDONE (&tp->t_uproc->u_attention_event);
			}
		}

		SPINFREE (&tp->t_inq.c_lock);

		goto out;
	}

	/*
	 *	Examina o ESCAPE
	 */
	if (c == '\\' && lflag & XCASE)
		{ tp->t_state |= ESCAPE; goto echo; }

	/*
	 *	Processa os acentos
	 */
	if ((lflag & ISOKEY) == 0 && isaccent (c))
	{
		tp->t_state |= ESCAPE;
		tp->t_escchar = c;
		goto echo;
	}

	/*
	 *	Processa os caracteres de ERASE
	 */
	if (c == tp->t_erase || c == tp->t_aerase)
	{
		if (lflag & ECHOE)
		{
			/*
			 *	Por ex. <bs> ou <del>
			 */
			ttywipe (chop (&tp->t_inq), tp);
		}
		else
		{
			/*
			 *	Por ex. #
			 */
			if (chop (&tp->t_inq) >= 0)
			{
				ttyecho (c, tp);
			}
		}
		goto out;
	}

	/*
	 *	Processa o caracter KILL
	 */
	if (c == tp->t_kill)
	{
		if
		(	(lflag & VIDEO) == 0 ||
			(iscntrl (tp->t_erase) == 0 &&
				iscntrl (tp->t_aerase) == 0)
		)
		{
			/*
			 *	N�o VIDEO ou n�o funciona o <bs>
			 */
			while (chop (&tp->t_inq) >= 0)
				/* vazio */;

			ttyecho (c, tp);

			if (lflag & ECHOK)
				ttyout ('\n', tp);
		}
		else
		{
			/*
			 *	VIDEO, e o <bs> funciona
			 */
			while ((c = chop (&tp->t_inq)) >= 0)
				ttywipe (c, tp);
		}
		goto out;
	}

	/*
	 *	Processa o caracter de RETYPE
	 */
	if (c == tp->t_retype)
	{
		ttyecho (c, tp);
		ttyecho ('\n', tp);
		ttyretype (tp, 1);
		goto out;
	}

	/*
	 *	Apaga Uma Palavra se VIDEO e o <bs> funciona
	 */
	if
	(	c == tp->t_word  &&
		lflag & VIDEO  && 
		(iscntrl (tp->t_aerase) || iscntrl (tp->t_erase))
	)
	{
		ttywipe ((c = chop (&tp->t_inq)), tp);

		if (isword (c))
		{
			c = chop (&tp->t_inq);

			while (isword (c))
			{
				ttywipe (c, tp);
				c = chop (&tp->t_inq);
			}

			if (c >= 0)
			{
				SPINLOCK (&tp->t_inq.c_lock);
				cput (c, &tp->t_inq);
				SPINFREE (&tp->t_inq.c_lock);
			}
		}

		goto out;
	}

	/*
	 *	Processa caracteres Maiusulos
	 */
	if (iflag & IUCLC  &&  isupper (c) )
		c += 'a'-'A';

	/*
	 *	Poe na fila de entrada
	 */
    putq:
	SPINLOCK (&tp->t_inq.c_lock);

	if (cput (c, &tp->t_inq) < 0)
	{
		SPINFREE (&tp->t_inq.c_lock);
#ifdef	MSG
		printf
		(	"ttyin: Falta de CBLK (raw/cooked), \"%s\" (%x)\n",
			tp->t_termio.c_name, tp->t_dev
		);
#endif	MSG
		ttyiflush (tp);
		return;
	}

	/*
	 *	Se for modo RAW, verifica se tem o n�mero suficiente
	 */
	if ((lflag & ICANON) == 0)
	{
		if (tp->t_inq.c_count >= tp->t_min)
		{
			EVENTDONE (&tp->t_inqnempty);

			if (tp->t_attention_set && tp->t_uproc->u_attention_index < 0)
			{
				tp->t_attention_set = 0;
				tp->t_uproc->u_attention_index = tp->t_index; 
				EVENTDONE (&tp->t_uproc->u_attention_event);
			}
		}
	}

	SPINFREE (&tp->t_inq.c_lock);

    echo:
	if (lflag & ECHO)
		ttyout (c, tp);
	else
		return;

    out:
	(*tp->t_oproc) (tp, 0);

}	/* end ttyin */

/*
 ****************************************************************
 *	Processamento do caracter na sa�da			*
 ****************************************************************
 */
void
ttyout (register int c, register TTY *tp)
{
	register ushort	oflag, lflag;

	oflag = tp->t_oflag;

	/*
	 *	Processa o Modo RAW sem maiores Delongas
	 */
	if ((oflag & OPOST) == 0)
	{
		SPINLOCK (&tp->t_outq.c_lock);

		if (cput (c, &tp->t_outq) >= 0)
			EVENTCLEAR (&tp->t_outqempty);

		SPINFREE (&tp->t_outq.c_lock);

		return;
	}

	/*
	 *	Ignora o <bs> se o cursor j� estiver no inicio da linha
	 */
	if (c == '\b' && tp->t_col <= tp->t_wcol)
		return;

	/*
	 *	Processa o <ht>
	 */
	if (c == '\t' && (oflag & TABDLY) == TAB3)
	{
		c = 8;

		do
			ttyout (' ', tp);
		while (--c >= 0 && tp->t_col & 0x07);

		return;
	}

	/*
	 *	Processa o Modo XCASE
	 */
	lflag = tp->t_lflag;

	if ((lflag & (ICANON|ICOMM|XCASE)) == (ICANON|XCASE))
	{
		if   (isupper (c))
		{
			ttyout ('\\', tp);
		}
		elif (ischave (c))
		{
			ttyout ('\\', tp);
			c = ttyconv ("({)}!|^~'`", c);
		}
	}

	/*
	 *	Processa o modo OLCUC
	 */
	if (oflag & OLCUC && islower (c))
		c -= 'a' - 'A';

	/*
	 *	Processa os caracteres n�o visiveis na Tela
	 */
	if (isespec (c) && lflag & CNTRLX)
	{
		ttyout ('^', tp);

		if (c == DEL)
			c = '*';
		else
			c |= 0x40;
	}

	/*
	 *	Processa <nl> e <cr>
	 */
	if   (c == '\n')
	{
		if (oflag & ONLCR)
			ttyout ('\r', tp);
	}
	elif (c == '\r')
	{
		if   (oflag & OCRNL)
			c = '\n';
		elif (oflag & ONOCR && tp->t_col == 0)
			return;
	}

	/*
	 *	Coloca (finalmente) o caracter na fila de saida
	 */
	SPINLOCK (&tp->t_outq.c_lock);

	if (cput (c, &tp->t_outq) < 0)
		{ SPINFREE (&tp->t_outq.c_lock); return; }

	EVENTCLEAR (&tp->t_outqempty);

	SPINFREE (&tp->t_outq.c_lock);

	/*
	 *	Calcula a nova coluna na linha
	 */
	switch (chartb[c] & 0x07)
	{
	    case 0:
		/*
		 *	Normal
		 */
		tp->t_col++;
	   /*** break; ***/

	    case 1:
	    case 7:
		/*
		 *	Caracteres de Controle
		 */
		break;

	    case 2:
		/*
		 *	Backspace <bs>
		 */
		if (tp->t_col != 0)
			tp->t_col--;
		break;

	    case 3:
		/*
		 *	Newline <nl>
		 */
		if ((lflag & ONLRET) == 0)
			break;
		/* continua no <cr> */

	    case 6:
		/*
		 *	Carriage Return <cr>
		 */
		tp->t_col = tp->t_wcol = 0;
		break;

	    case 4:
		/*
		 *	Tabula��o <ht>
		 */
		tp->t_col |= 0x07;
		tp->t_col++;
		break;

	    case 5:
		/*
		 *	Form Feed <ff>
		 */
		tp->t_col = tp->t_wcol = 0;
	   /***	tp->t_lno = 0; ***/
		break;

	}	/* end switch */

}	/* end ttyout */
