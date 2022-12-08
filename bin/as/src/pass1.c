/*
 ****************************************************************
 *								*
 *			pass1.c					*
 *								*
 *	An�lise sint�tica - primeiro passo			*
 *								*
 *	Vers�o	1.0.0, de 25.03.86				*
 *		4.1.0, de 24.08.01				*
 *								*
 *	Rotinas:						*
 *		pass1     regular1     getsize			*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <a.out.h>

#include "../h/common.h"
#include "../h/tokens.h"
#include "../h/scan.h"
#include "../h/id_sym_tb.h"
#include "../h/expr.h"
#include "../h/opnd.h"
#include "../h/msg.h"
#include "../h/as.h"
#include "../h/op_code.h"
#include "../h/proto.h"

/*
 ****** Vari�veis globais ***************************************
 */
entry SYMTB	*labtb[LABSZ], **labp;	/* Alinhamento dos r�tulos */

extern	int	if_false_level;	/* No. de Condicionais FALSE aninhadas */

/*
 ****************************************************************
 *	An�lise Sint�tica - Primeiro Passo			*
 ****************************************************************
 */
void
pass1 (void)
{
	MAJOR		major;
	SYMTB		*sp;
	OPCODE		*op;
	char		*begin;
	EXP		exp;

	labp = labtb;

	while (getline () >= 0)
	{
		major = gettoken ();

		/*
		 *	Trata r�tulos
		 */
		if (major == ID && latoken->l_major == CL)
		{
			if (if_false_level)
				continue;

			if (labp >= &labtb [LABSZ])
			{
				msg
				(	ERRO, LONGMARK,
					"N�mero excessivo de r�tulos "
					"consecutivos"
				);
				continue;
			}

			sp = putsym (token->l_name, token->l_len, S_DEFINE);

			if   (sp->s.s_type == REG)
			{
				msg
				(	ERRO, LONGMARK,
					"Nome de um registro: "
					"n�o pode ser usado como r�tulo"
				);
				continue;
			}
			elif (sp->s.s_type != UNDEF)
			{
				msg
				(	ERRO, LONGMARK,
					"R�tulo duplicado"
				);
				continue;
			}

			sp->s.s_value = *lc;
			sp->s.s_type = section;
			sp->s.s_flags |= S_LBL;
			symblk++;

			*labp++ = sp;

			gettoken ();
			gettoken ();
		}
		elif (major == LID && latoken->l_major == CL)
		{
			if (if_false_level)
				continue;

			if (labp >= &labtb [LABSZ])
			{
				msg
				(	ERRO, LONGMARK,
					"N�mero excessivo de r�tulos "
					"consecutivos"
				);
				continue;
			}

			sp = putsym (token->l_name, token->l_len, S_DEFINE);

			if (sp->s.s_type != UNDEF)
			{
				msg
				(	ERRO, LONGMARK,
					"S�mbolo duplicado: ser� ignorado"
				);
				continue;
			}

			sp->s.s_value = *lc;
			sp->s.s_type = section;
			sp->s.s_flags |= S_LBL|S_LOCAL;

			*labp++ = sp;

			gettoken ();
			gettoken ();
		}
		elif (major == ID && latoken->l_major == EQ)
		{
			/*
			 *	Analisa atribui��es
			 */
			if (if_false_level)
				continue;

			sp = putsym (token->l_name, token->l_len, S_DEFINE);
			begin = token->l_begin;

			gettoken ();	/* Obtem "==" */
			gettoken ();	/* Obtem o primeiro token da express�o */

			/*
			 *	Analisa a Express�o
			 */
			expression (&exp);

			/*
			 *	N�o permite redefini��es
			 */
			if (sp->s.s_type != UNDEF && exp.ex_type != ERR)
			{
				if (exp.ex_type == REAL)
				{
					if
					(	sp->s.s_type == REAL &&
						sp->s_rval == exp.ex_rval
					)
					{
						msg
						(	ADVR, MYMARK,
							"Redefini��o ignorada",
							NOSTR,
							begin, exp.ex_end
						);
					}
				}
				elif
				(	sp->s.s_value == exp.ex_value &&
					sp->s.s_type  == exp.ex_type
				)
				{
					msg
					(	ADVR, MYMARK,
						"Redefini��o ignorada",
						NOSTR, begin, exp.ex_end
					);
				}
				else
				{
					msg
					(	ERRO, MYMARK,
						"Redefini��o inv�lida",
						NOSTR, begin, exp.ex_end
					);
				}
				continue;
			}

			if (exp.ex_type == UNDEF)
			{
				msg
				(	ERRO, EXPMARK,
					"Express�o cont�m vari�vel(is) indefinida(s)",
					NOSTR, &exp
				);
				sp->s.s_type = ABS;
				sp->s.s_value = 0;
			}
			elif (exp.ex_type == REAL)
			{
				sp->s.s_type = REAL;
				sp->s_rval   = exp.ex_rval;
			}
			elif (exp.ex_type != ERR)
			{
				sp->s.s_type = exp.ex_type;
				sp->s.s_value = exp.ex_value;
			}
			continue;

		}	/* end atribui��o */

		/*
		 *	Acabaram os r�tulos
		 */
		if (token->l_major == EOL)
			continue;

		if (token->l_major != ID)
		{
			msg (ERRO, LONGMARK, "Esperava instru��o ou pseudo");
			continue;
		}

		/*
		 *	Analisa a Instru��o
		 */
		if ((op = op_hash (token->l_name)) == NOOPCODE)
		{
			msg
			(	ERRO, LONGMARK,
				"Instru��o inv�lida"
			);
			continue;
		}

		if (if_false_level && (op->o_flags & NOSKIP) == 0)
			continue;

		opcodeno++;

		switch (op->o_type)
		{
		    /*
		     *	    Instru��es Regulares
		     */
		    case I_REGULAR:
			*lc += regular1 (op);
			break;

		    /*
		     *	    Pseudo-Instru��es
		     */
		    case I_PSEUDO:
			pseudo1 (op->o_group);
			break;

#if (0)	/*************************************/
		    /*
		     *	    Ponto Flutuante
		     */
		    case I_FLOAT:
			*lc += float1 (op);
			break;
#endif	/*************************************/

		    /*
		     *	    Tipo desconhecido
		     */
		    default:
			msg
			(	COMP, LONGMARK,
				"Instru��o de tipo %d desconhecido",
				op->o_type
			);
			break;

		}	/* end  switch (type) */

		/*
		 *	Reinicializa a Tabela Auxiliar para
		 *	Alinhamento de Rotulos e a de Prefixos
		 */
		labp = labtb;

	}	/* end while (getline () >= 0) */

}	/* end pass1 */
