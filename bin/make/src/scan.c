/*
 ****************************************************************
 *								*
 *			scan.c					*
 *								*
 *	Analisador L�xico					*
 *								*
 *	Vers�o	3.0.0, de 29.03.96				*
 *		3.2.3, de 10.01.00				*
 *								*
 *	M�dulo: Make: Construtor de Programas			*
 *		Interpretador de Comandos			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/error.h"
#include "../h/sym.h"
#include "../h/scan.h"
#include "../h/categ.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Vari�veis vis�veis externamente				*
 ****************************************************************
 */
entry	TOKEN	token;			/* Estrutura retornada */
entry	char	*makefile_text;		/* O texto do makefile */

/*
 ****************************************************************
 *	Defini��es Locais					*
 ****************************************************************
 */
#define	BUFSZ		(8 * 1024)
#define	NAMESZ		256

#define	RETURN(r)	return (token.t_major = r)

/*
 ******	Argumentos para a rotina "skip_comment" ****************
 */
enum
{
	DONT_ERASE,
	ERASE
};

/*
 ****************************************************************
 *	Vari�veis locais					*
 ****************************************************************
 */
static	char	*next_pos;	/* Ponteiro para o pr�ximo caractere */
static	char	buf[BUFSZ];	/* Buffer auxiliar */

static	char	*current_line;	/* Come�o da linha corrente */
static	int	current_nline;	/* N�mero da linha corrente */

/*
 ****************************************************************
 *	Estrutura da pilha de contextos				*
 ****************************************************************
 */
#define	NOSSTACK	(SSTACK *)NULL

typedef	struct sstack	SSTACK;

struct sstack
{
	char	*ss_next_pos;		/* Salva "next_pos" */
	char	*ss_line;		/* Salva "current_line" */
	int	ss_nline;		/* Salva "current_nline" */

	SSTACK	*ss_next;		/* Pr�xima c�lula */
};

/*
 *****	Pilha de contextos  *************************************
 */
static	SSTACK	*scan_stack,		/* Pilha de contextos */
		*free_stack;		/* Pilha de c�lulas dispon�veis */

/*
 ****************************************************************
 *	Prot�tipos de fun��es locais				*
 ****************************************************************
 */
char	*skip_comment (char *, int);
MAJOR	get_name (char *);
char	*get_macro_name (char *, char *, char *);
char	*begin_expansion (char *);
char	*finish_expansion (void);

/*
 ****************************************************************
 *	L� o makefile						*
 ****************************************************************
 */
int
read_makefile (char *name)
{
	int	fd;
	off_t	size;
	STAT	st;

	/*
	 *	Tenta abrir o arquivo e obter o tamanho.
	 */
	if ((fd = open (name, O_RDONLY)) < 0)
		return (NIL);

	if (fstat (fd, &st) < 0)
	{
		msg ("N�o pude obter o estado de %s", name);
		exit (1);
	}

	if ((size = st.st_size) <= 0)
	{
		msg ("\"%s\" tem tamanho nulo", name);
		exit (1);
	}

	/*
	 *	L� todo o conte�do para a mem�ria.
	 */
	makefile_text = emalloc (size + 2);

	if (read (fd, makefile_text, size) != size)
	{
		msg
		(	"Erro de leitura em \"%s\" (%s)",
			name, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Eis o Makefile !
	 */
	makefile_name		= name;
	makefile_text[size++]	= '\n';
	makefile_text[size]	= NOCHR;

	/*
	 *	Inicializa algumas vari�veis do analisador l�xico.
	 */
	next_pos = current_line = makefile_text;
	current_nline = 1;

	scan_stack  = NOSSTACK;

	return (0);

}	/* end read_makefile */

/*
 ****************************************************************
 *	Obt�m o pr�ximo token					*
 ****************************************************************
 */
MAJOR
get_token (void)
{
	char	*lp, c;
	uchar	categ;

	/*
	 *	Ignora os separadores.
	 */
	lp = next_pos;

again:
	while ((categ = CATEG (chartb[*lp])) == C_SEP)
		lp++;

	if (scan_stack == NOSSTACK)
	{
		token.t_range.r_begin = token.t_range.r_end = lp;
		token.t_range.r_line  = current_line;
		token.t_range.r_nline = current_nline;
	}

	next_pos = lp + 1;

	/*
	 *	Analisa a categoria do caractere.
	 */
	switch (categ)
	{
	    case C_INV:
		err_msg
		(	WARNING, NOMARK,
			"Caractere inv�lido: %02X; ser� ignorado", *lp
		);
		lp++;
		goto again;

	    case C_COM:			/* # */
		lp = skip_comment (lp, DONT_ERASE);
		goto again;

	    case C_LET:			/* letras e _ */
	    case C_DIG:			/* d�gitos */
	    case C_VAL:			/* v�lidos */
	    case C_QUO:			/* " e ' */
		RETURN (get_name (lp));

	    case C_EOT:			/* <nul> */
		if ((lp = finish_expansion ()) == NOSTR)
		{
			next_pos--;
			RETURN (EOT);
		}

		goto again;

	    case C_EOL:			/* <nl> */
		do
		{
			*lp++ = NOCHR;
			++current_nline;

		}	while ((c = *lp) == '\n');

		current_line = lp;

		while (c == '#')
			c = *(lp = skip_comment (lp, DONT_ERASE));

		next_pos = lp;

		if (c == '\t')
		{
			next_pos++;
			RETURN (BOC);
		}

		RETURN (EOL);

	    case C_CL:			/* : */
		RETURN (CL);

	    case C_EQ:			/* = */
		RETURN (EQ);

	    case C_MAC:			/* $ */
		if (*next_pos == '$')
			RETURN (get_name (lp));

		lp = begin_expansion (next_pos);
		goto again;

	    case C_BL:			/* \ */
		if (*next_pos == '\n')
		{
			lp += 2;
			current_line = lp;
			++current_nline;
			goto again;
		}

		RETURN (get_name (lp));

	    case C_SM:			/* ; */
		RETURN (BOC);
	}

	return (EOT);	/* Apenas para fazer o "lint" feliz */

}	/* end get_token */

/*
 ****************************************************************
 *	Obt�m uma cadeia, sem expandir o texto			*
 ****************************************************************
 */
void
get_string (RANGE *rp)
{
	char	delim, *lp;
	uchar	categ;
	int	quoted;
	RANGE	err;

	/*
	 *	Ignora eventuais separadores no in�cio da cadeia.
	 */
	for (lp = next_pos; (categ = CATEG (chartb[*lp])) == C_SEP; lp++)
		/* vazio */;

	rp->r_begin = lp;
	rp->r_line  = current_line;
	rp->r_nline = current_nline;

	delim = NOCHR;		/* para fazer o "lint" feliz */

	/*
	 *	Procura o fim da cadeia (<nl> n�o precedido de \).
	 *	Trata coment�rios, linhas de continua��o, caracteres inv�lidos
	 *	e trechos entre	aspas ou ap�strofos.
	 */
	for (quoted = FALSE; categ != C_EOL; categ = CATEG (chartb[*lp]))
	{
		switch (categ)
		{
		    case C_BL:
			if (lp[1] == '\n')
			{
				if (quoted)
				{
					err.r_line  = current_line;
					err.r_nline = current_nline;
					err.r_end = lp;

					set_mark (&err);

					err_msg
					(	ERROR, GIVENMARK,
						"Faltou fechar %c", delim
					);

					quoted = FALSE;
					*lp++ = delim;
				}
				else
					*lp++ = ' ';

				*lp++ = ' ';

				current_line = lp;
				++current_nline;
			}
			else
			{
				lp++;
			}
			break;

		    case C_QUO:
			err.r_begin = lp;
			quoted = !quoted;
			delim  = *lp++;
			break;

		    case C_INV:
			err_msg
			(	WARNING, NOMARK,
				"Caractere inv�lido: %02X; ser� ignorado", *lp
			);
			*lp++ = ' ';
			break;

		    case C_COM:
			if (quoted)
				lp++;
			else
				lp = skip_comment (lp, ERASE);
			break;

		    default:
			lp++;

		}	/* end switch (categ) */

	}	/* end for (...) */

	next_pos = lp;		/* fica apontando para o <nl> */

	/*
	 *	Ignora eventuais separadores no final da cadeia.
	 */
	while ((categ = CATEG (chartb[*--lp])) == C_SEP)
		/* vazio */;

	rp->r_end = lp++;
	if (lp < next_pos)
		*lp = NOCHR;

	if (quoted)
	{
		err.r_line  = current_line;
		err.r_nline = current_nline;
		err.r_end   = rp->r_end;
		set_mark (&err);
		err_msg (ERROR, GIVENMARK, "Faltou fechar %c", delim);
	}

}	/* end get_string */

/*
 ****************************************************************
 *	Expande uma cadeia					*
 ****************************************************************
 */
char *
expand (char *lp, int *meta)
{
	char	delim, c, *bp;
	uchar	categ, tb;
	int	nsep, quoted, metachar;
	SSTACK	*save_stack;

	save_stack = scan_stack;
	scan_stack = NOSSTACK;

	delim	 = NOCHR;	/* para fazer o "lint" feliz */
	nsep     = 0;
	bp       = buf;
	quoted	 = FALSE;
	metachar = FALSE;

	for (EVER)
	{
		/*
		 *	Enquanto n�o chegar o fim da cadeia dada,
		 *	analisa a categoria do caractere.
		 */
		switch (categ = CATEG (tb = chartb[c = *lp]))
		{
		    case C_SEP:			/* <sp> <ht> <vt> <ff> */
			if (quoted)
				goto insert;

			nsep++;		/* contabiliza os separadores */
			lp++;
			break;

		    case C_QUO:			/* " ' */
			delim  = c;
			quoted = !quoted;
			goto insert;

		    case C_EOT:			/* <nul> */
			if ((lp = finish_expansion ()) == NOSTR)
				goto skip;
			break;

		    case C_MAC:			/* $ */
			if (quoted)
				goto insert;

			if (lp[1] == '$')
			{
				lp++;
				goto insert;
			}

			lp = begin_expansion (lp + 1);
			break;

		    default:
		    insert:
			if (bp >= &buf[BUFSZ - 3])
			{
				err_msg
				(	INTERNAL_ERROR, NOMARK,
					"Buffers subdimensionados: "
					"aumente BUFSZ (> %d)", BUFSZ
				);
			}

			/*
			 *	Se h� separadores, coloca apenas um
			 *	<sp> na cadeia, compactando-os.
			 */
			if (nsep != 0)
			{
				nsep = 0;
				*bp++ = ' ';
			}

			*bp++ = c;	/* Acrescenta o caractere */

			/*
			 *	Verifica se � um metacaractere.
			 */
			if (META (tb))
				metachar++;
			lp++;
			break;

		}	/* end switch (categ) */

	}	/* end for (EVER) */

skip:
	if (quoted)
		*bp++ = delim;	/* O erro j� foi emitido em "get_string" */

	*bp = NOCHR;

	if (meta != NOINT)
		*meta = metachar;

	scan_stack = save_stack;

	return (buf);		/* Retorna um ponteiro para �rea est�tica */

}	/* end expand */

/*
 ****************************************************************
 *	Ignora at� o final da linha				*
 ****************************************************************
 */
void
skip_line (void)
{
	char	*lp, c;

	for (lp = next_pos; (c = *lp) != '\n' && c != NOCHR; lp++)
		/* vazio */;

	next_pos = lp;

}	/* end skip_line */

/*
 ****************************************************************
 *	Pula coment�rios					*
 ****************************************************************
 */
char *
skip_comment (char *lp, int erase)
{
	int	whole_line;

	whole_line = (lp == current_line);

	if (erase)
	{
		while (*lp != '\n')
			*lp++ = ' ';

		if (whole_line)
		{
			*lp++ = ' ';
			current_line = lp;
			++current_nline;
		}
	}
	else
	{
		while (*lp != '\n')
			lp++;

		if (whole_line)
		{
			*lp++ = NOCHR;
			current_line = lp;
			++current_nline;
		}
	}

	return (lp);

}	/* end skip_comment */

/*
 ****************************************************************
 *	Obt�m o nome da macro a expandir			*
 ****************************************************************
 */
char *
get_macro_name (char *lp, char *begin, char *end_name)
{
	int		left_par = 0, len;
	char		*bp, c, *save_lp;
	HASH		*hp;
	SYM		*sp;
	MACRO		*mp;
	RANGE		range, *rp = &range;

	rp->r_begin = save_lp = lp - 1;
	rp->r_line  = current_line;
	rp->r_nline = current_nline;

	if (*lp == '(')
	{
		lp++;
		left_par++;
	}

	/*
	 *	Extrai o nome da macro.
	 */
	for (bp = begin; MCALL (chartb[c = *lp]); /* sem incremento */)
	{
		if (c == '$')
		{
			if (!left_par)
				break;

			rp->r_begin = lp;

			/*
			 *	O nome da macro cont�m a expans�o de
			 *	outra macro.
			 */
			lp = get_macro_name (lp + 1, bp, end_name);

			hp = hash (bp);

			if
			(	(sp = hp->h_sym) == NOSYM ||
				(mp = &sp->s_macro)->m_begin == NOSTR
			)
			{	/*
				 *	N�o estava definida.
				 */
				rp->r_end = lp - 1;
				set_mark (rp);

				err_msg
				(	WARNING, GIVENMARK,
					"Macro \"%s\" n�o foi definida",
					bp
				);
			}
			else
			{	/*
				 *	Substitui o nome pelo corpo da macro.
				 */
				len = strlen (mp->m_begin);

				if (bp + len < end_name)
				{
					memmove (bp, mp->m_begin, len);
					bp += len;
				}
			}
		}
		elif (bp < end_name)
		{
			*bp++ = c;
			lp++;
		}
	}

	/*
	 *	Verifica a termina��o.
	 */
	if (left_par)
	{
		if (*lp == ')')
		{
			lp++;
		}
		else
		{
			rp->r_begin = save_lp;
			rp->r_end = lp - 1;
			set_mark (rp);

			err_msg
			(	ERROR, GIVENMARK,
				"Faltou o \")\" para terminar o nome"
			);
		}
	}

	*bp = NOCHR;		/* Arremata o fim do nome */

	return (lp);

}	/* end get_macro_name */

/*
 ****************************************************************
 *	Come�a a expans�o de macro				*
 ****************************************************************
 */
char *
begin_expansion (char *lp)
{
	int		len;
	char		*bp, macro_name[NAMESZ];
	HASH		*hp;
	SYM		*sp;
	MACRO		*mp;
	SSTACK		*ssp;
	RANGE		range;

	/*
	 *	Obt�m o nome da macro.
	 */
	range.r_begin = lp - 1;
	range.r_line  = current_line;
	range.r_nline = current_nline;

	lp = get_macro_name (lp, macro_name, &macro_name[NAMESZ - 1]);

	range.r_end = lp - 1;
	set_mark (&range);

	bp = strend (macro_name);

	if (bp == macro_name)
	{
		err_msg (ERROR, GIVENMARK, "Chamada de macro inv�lida");
		return (lp);
	}

	/*
	 *	Procura o texto correspondente � macro.
	 */
	hp = hash (macro_name);

	if ((sp = hp->h_sym) == NOSYM)
	{	/*
		 *	N�o encontrou: assume texto nulo.
		 */
		err_msg
		(	WARNING, GIVENMARK,
			"Macro \"%s\" n�o foi definida",
			macro_name
		);

		len = bp - macro_name;
		sp  = emalloc (SYM_FIXED_SZ + len + 1);

		hp->h_sym     = sp;
		sp->s_type    = S_NAME;
		sp->s_namelen = len;

		memmove (sp->s_name, macro_name, len + 1);

		mp = &sp->s_macro;
		mp->m_begin = mp->m_line = nullstr;
		mp->m_nline = 0;

		memset (&sp->s_node, 0, sizeof (DEPEN));

	/***	sp->s_node.d_sibling = NOSYM;	***/
	/***	sp->s_node.d_flags   = 0;	***/
	/***	sp->s_node.d_nline   = 0;	***/

		return (lp);
	}

	if ((mp = &sp->s_macro)->m_begin == NOSTR)
	{	/*
		 *	Encontrou, mas n�o � macro.
		 */
		err_msg
		(	ERROR, GIVENMARK,
			"\"%s\" n�o � um nome de macro",
			sp->s_name
		);
		return (lp);
	}

	/*
	 *	Guarda o contexto atual e passa a procesasr o texto da macro.
	 *	Verifica se h� c�lula dispon�vel na lista livre antes de alocar.
	 */
	if ((ssp = free_stack) == NOSSTACK)
		ssp = emalloc (sizeof (SSTACK));
	else
		free_stack = ssp->ss_next;

	ssp->ss_next_pos = lp;
	ssp->ss_line     = range.r_line;
	ssp->ss_nline	 = range.r_nline;

	if (scan_stack == NOSSTACK)
		token.t_range.r_end = range.r_end;

	ssp->ss_next	= scan_stack;
	scan_stack	= ssp;

	current_line  = mp->m_line;
	current_nline = mp->m_nline;

	return (mp->m_begin);

}	/* end begin_expansion */

/*
 ****************************************************************
 *	Termina a expans�o					*
 ****************************************************************
 */
char *
finish_expansion (void)
{
	SSTACK	*ssp;
	char	*retp;

	if ((ssp = scan_stack) == NOSSTACK)
		return (NOSTR);

	/*
	 *	Restaura o contexto.
	 */
	retp		= ssp->ss_next_pos;
	current_line	= ssp->ss_line;
	current_nline	= ssp->ss_nline;

	/*
	 *	Retira a c�lula da pilha e coloca-a na lista livre,
	 *	em vez de devolver � arena.
	 */
	scan_stack   = ssp->ss_next;
	ssp->ss_next = free_stack;
	free_stack   = ssp;

	return (retp);

}	/* end finish_expansion */

/*
 ****************************************************************
 *	L� um nome						*
 ****************************************************************
 */
MAJOR
get_name (char *lp)
{
	char	*bp, c, *begin;
	uchar	tb;
	int	isid, len;
	HASH	*hp;
	SYM	*sp;

	isid   = TRUE;
	begin  = lp;
	bp     = buf;

	for (EVER)
	{
		switch (CATEG (tb = chartb[c = *lp]))
		{
		    case C_EOT:
			lp = finish_expansion ();
			break;

		    case C_BL:
			if (lp[1] == '\n')
				goto skip;

			isid = FALSE;
			if (bp < &buf[BUFSZ - 1])
				*bp++ = c;
			lp++;
			break;

		    case C_MAC:
			if (lp[1] != '$')
			{
				lp = begin_expansion (lp + 1);
				break;
			}

			lp++;
			/* FALL THROUGH */

		    case C_QUO:
		    case C_VAL:
			isid = FALSE;
			/* FALL THROUGH */

		    case C_LET:
		    case C_DIG:
			if (bp < &buf[BUFSZ - 1])
				*bp++ = c;
			lp++;
			break;

		    default:
			goto skip;

		}	/* end switch (CATEG (...)) */

	}	/* end for (EVER) */

skip:
	*bp = NOCHR;

	if (scan_stack == NOSSTACK)
		token.t_range.r_end = lp - 1;

	hp = hash (buf);

	if ((sp = hp->h_sym) == NOSYM)
	{	/*
		 *	Aloca a estrutura SYM, com espa�o para o nome.
		 */
		len = bp - buf;
		sp  = emalloc (SYM_FIXED_SZ + len + 1);

		hp->h_sym     = sp;
		sp->s_type    = S_NAME;
		sp->s_namelen = len;

		memmove (sp->s_name, buf, len + 1);

		memset (&sp->s_node, 0, sizeof (DEPEN));

		sp->s_macro.m_begin  = NOSTR;
	/***	sp->s_node.d_sibling = NOSYM;	***/
	/***	sp->s_node.d_flags   = 0;	***/
	/***	sp->s_node.d_nline   = 0;	***/
	}

	token.t_sym  = sp;
	sp->s_isid   = isid && CATEG (chartb[buf[0]]) == C_LET;

	next_pos = lp;
	return (NAME);

}	/* end get_name */
