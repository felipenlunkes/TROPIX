/*
 ****************************************************************
 *								*
 *			sym.c					*
 *								*
 *	Manipula��o da Tabela de S�mbolos			*
 *								*
 *	Vers�o	3.2.2, de 27.11.99				*
 *		4.5.0, de 21.10.03				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../h/common.h"
#include "../h/sym.h"
#include "../h/scan.h"
#include "../h/command.h"

#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Vari�veis Globais					*
 ****************************************************************
 */
/*
 ******	N� cabe�a da lista circular de vari�veis ****************
 */
entry	SYM	var_list =
{
	S_UNDEF,	/* s_type */
	{ 0 },		/* s_name */
	0,		/* s_union */
	NOSTR,		/* s_value */
	&var_list,	/* s_next */
	&var_list,	/* s_prev */
	NOSYMP		/* s_hnext */
};

/*
 ******	Ponteiros para diversas entradas importantes ***********
 */
entry	SYM	*home_sp,		/* vari�vel HOME */
		*ps1_sp,		/* vari�vel PS1 */
		*ps2_sp,		/* vari�vel PS2 */
		*current_prompt,	/* prompt corrente */
		*hist_sp,		/* vari�vel HIST */
		*path_sp;		/* Vari�vei PATH */

/*
 ****************************************************************
 *	Prot�tipos de Fun��es					*
 ****************************************************************
 */
int	add_to_environment (SYM *);

/*
 ****************************************************************
 *	Define uma vari�vel, a partir de uma cadeia		*
 ****************************************************************
 */
SYM *
define_variable_from_string (char *str)
{
	char		*pt;
	SYM		*sp;

	if ((pt = strchr (str, '=')) == NOSTR)
		return (NOSYMP);

	*pt = NOCHR;

	sp = define_variable (str, pt + 1, -1 /* n�o altera flags */);

	*pt = '=';

	return (sp);

}	/* end define_variable_from_string */

/*
 ****************************************************************
 *	Define uma vari�vel					*
 ****************************************************************
 */
SYM *
define_variable (const char *name, const char *value, int flags)
{
	SYM		*sp, *vsp;
	char		*str;

	/*
	 *	Insere o nome da vari�vel e verifica se o tipo n�o �
	 *	S_FUNC ou S_PROG.
	 */
	if ((sp = put_sym (name)) == NOSYMP || sp->s_type > S_VAR)
		return (NOSYMP);

	/*
	 *	Verifica se o valor ser� modificado ou n�o.
	 */
	if (value == NOSTR)
		value = "";

	if ((str = strdup (value)) == NOSTR)
	{
		error (NOSTR);
		return (NOSYMP);
	}

	/*
	 *	Se a vari�vel � nova, insere em ordem crescente
	 *	de nomes na lista de vari�veis.
	 */
	if (sp->s_type == S_UNDEF)
	{
		strscpy (var_list.s_name, name, sizeof (var_list.s_name));	/* sentinela */

		for (vsp = var_list.s_next; strcmp (name, vsp->s_name) > 0; vsp = vsp->s_next)
			/* vazio */;

		vsp->s_prev->s_next = sp;
		sp->s_prev	    = vsp->s_prev;
		vsp->s_prev	    = sp;
		sp->s_next	    = vsp;

		sp->s_type = S_VAR;
	}

	/*
	 *	Modifica o valor e os indicadores, se necess�rio.
	 */
	if (flags >= 0)
		sp->s_flags = flags;

	if (sp->s_flags & V_READONLY)
	{
		error
		(	"O valor da vari�vel \"%s\" n�o pode "
			"ser alterado",
			name
		);

		free (str);
		return (sp);
	}

	/*
	 *	Verifica se o novo valor � id�ntico ao antigo.
	 */
	if (sp->s_value != NOSTR && streq (str, sp->s_value))
	{
		free (str);
		return (sp);
	}

	/*
	 *	Libera o valor anterior e atribui o novo.
	 */
	if (sp->s_value != NOSTR)
		free (sp->s_value);

	sp->s_value = str;

	/*
	 *	O valor foi alterado e a vari�vel �
	 *	V_EXPORT: modifica tamb�m o ambiente.
	 */
	if (sp->s_flags & V_EXPORT)
		add_to_environment (sp);

	/*
	 *	Modificar certas vari�veis causa efeitos colaterais.
	 */
	if   (sp == hist_sp)
		set_history_size (atol (str));
	elif (sp == path_sp)
		exec_hash_create (script == 0);

	return (sp);

}	/* end define_variable */

/*
 ****************************************************************
 *	Modifica apenas os indicadores de uma vari�vel		*
 ****************************************************************
 */
int
set_variable_flag (const char *name, int flag)
{
	SYM		*sp;

	/*
	 *	Verifica se o identificador est� definido e se � vari�vel.
	 */
	if ((sp = search_sym (name)) == NOSYMP)
	{
		error ("\"%s\" n�o foi definido", name);
		return (-1);
	}

	if (sp->s_type != S_VAR)
	{
		error ("\"%s\" n�o � uma vari�vel", name);
		return (-1);
	}

	/*
	 *	Altera os identificadorese, se for o caso, modifica o ambiente.
	 */
	if ((sp->s_flags & V_EXPORT) == 0 && (flag & V_EXPORT))
		add_to_environment (sp);

	sp->s_flags |= flag;

	return (0);

}	/* end set_variable_flag */

/*
 ****************************************************************
 *	Acrescenta uma vari�vel ao ambiente			*
 ****************************************************************
 */
int
add_to_environment (SYM *sp)
{
	int		name_len, value_len;
	char		*env;

	/*
	 *	Prepara a cadeia "var=valor".
	 */
	name_len  = strlen ((const char *)sp->s_name);
	value_len = strlen (sp->s_value);

	if ((env = malloc (name_len + value_len + 2)) == NOSTR)
		return (-1);

	memmove (env, (const char *)sp->s_name, name_len);
	env[name_len] = '=';
	memmove (env + name_len + 1, sp->s_value, value_len + 1);

	/*
	 *	Acrescenta ao ambiente.
	 */
	if (putenv (env) < 0)
	{
		error ("*Erro em putenv (\"%s\")", env);
		free (env);
		return (-1);
	}

	return (0);

}	/* end add_to_environment */

/*
 ****************************************************************
 *	Remove uma vari�vel					*
 ****************************************************************
 */
int
delete_variable (const char *name)
{
	SYM		**hp, *sp, *bsp;

	/*
	 *	Localiza o identificador, usando a tabela "hash".
	 */
	hp = &hashtb[strhash (name, strlen (name), hashsz)];

	for (bsp = NOSYMP, sp = *hp; sp != NOSYMP; bsp = sp, sp = sp->s_hnext)
	{
		if (streq (sp->s_name, name))
			goto found;
	}

	error ("Vari�vel \"%s\" n�o definida", name);

	return (-1);

	/*
	 *	Achou: verifica se � uma vari�vel e se pode ser removida.
	 */
    found:
	if (sp->s_type != S_VAR)
	{
		error ("\"%s\" n�o � uma vari�vel", name);
		return (-1);
	}

	if (sp->s_flags & V_PERMANENT)
	{
		error ("A vari�vel \"%s\" n�o pode ser removida", name);
		return (-1);
	}

	/*
	 *	Retira da cadeia hash.
	 */
	if (bsp == NOSYMP)
		*hp          = sp->s_hnext;
	else
		bsp->s_hnext = sp->s_hnext;

	/*
	 *	Retira tamb�m da lista de vari�veis.
	 */
	sp->s_prev->s_next = sp->s_next;
	sp->s_next->s_prev = sp->s_prev;

	/*
	 *	Se for "export", tira tamb�m do ambiente.
	 */
	if (sp->s_flags & V_EXPORT)
	{
		if (delenv (name) < 0)
			error ("Vari�vel \"%s\" n�o retirada do ambiente", name);
	}

	/*
	 *	Libera o espa�o.
	 */
	free (sp->s_value);
	free (sp);

	return (0);

}	/* end delete_variable */

/*
 ****************************************************************
 *	Apenas Busca o Nome do S�mbolo				*
 ****************************************************************
 */
SYM *
search_sym (const char *sym)
{
	SYM		*sp;

	for (sp = hashtb[strhash (sym, strlen (sym), hashsz)]; sp != NOSYMP; sp = sp->s_hnext)
	{
		if (streq (sp->s_name, sym))
			return (sp);
	}

	return (NOSYMP);

}	/* end search_sym */

/*
 ****************************************************************
 *	Busca/Insere um s�mbolo					*
 ****************************************************************
 */
SYM *
put_sym (const char *id)
{
	SYM		**hp;
	SYM		*sp, *bsp;

	/*
	 *	Calcula a posi��o na tabela hash.
	 */
	hp = &hashtb[strhash (id, strlen (id), hashsz)];

	/*
	 *	Busca na cadeia de colis�es.
	 */
	for (bsp = NOSYMP, sp = *hp; sp != NOSYMP; bsp = sp, sp = sp->s_hnext)
	{
		if (streq (sp->s_name, id))
			return (sp);		/* achou */
	}

	/*
	 *	Cria um novo s�mbolo, ao final da cadeia de colis�es.
	 */
	if ((sp = calloc (1, sizeof (SYM))) == NOSYMP)
		return (NOSYMP);

	strscpy (sp->s_name, id, sizeof (sp->s_name));

	if (bsp == NOSYMP)
		*hp          = sp;
	else
		bsp->s_hnext = sp;

/***	sp->s_value = S_UNDEF;	***/
/***	sp->s_type  = S_UNDEF;	***/
/***	sp->s_hnext = NOSYMP;	***/

	return (sp);

}	/* end put_sym */

/*
 ****************************************************************
 *	Mostra as vari�veis					*
 ****************************************************************
 */
void
show_variables (FILE *fp, int mask)
{
	SYM		*sp;
	int		c;

	for (sp = var_list.s_next; sp != &var_list; sp = sp->s_next)
	{
		if (mask > 0 && (sp->s_flags & mask) == 0)
			continue;

		c = (sp->s_flags & V_EXPORT) ? 'e' : '-';
		putc (c, fp);

		c = (sp->s_flags & V_READONLY) ? 'r' : '-';
		putc (c, fp);

		c = (sp->s_flags & V_PERMANENT) ? 'p' : '-';
		putc (c, fp);

		fprintf (fp, "\t%-14.14s\t%s\n", sp->s_name, sp->s_value);
	}

}	/* end show_variables */

#if (0)	/*******************************************************/
/*
 ****************************************************************
 *	Mostra o ambiente da SHELL				*
 ****************************************************************
 */
int
show_environment (FILE *fp)
{
	const char	**cp;

	for (cp = environ; *cp != NOSTR; cp++)
		fprintf (fp, "%s\n", *cp);

	return (0);

}	/* end show_environment */
#endif	/*******************************************************/
