/*
 ****************************************************************
 *								*
 *			print.c					*
 *								*
 *	Print information on generated parser, for bison	*
 *								*
 *	Vers�o	3.0.0, de 06.07.93				*
 *		3.0.0, de 06.07.93				*
 *								*
 *	M�dulo: GBISON						*
 *		Gerador de analisadores sint�ticos		*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Baseado em software hom�nimo do GNU		*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <string.h>

#include "../h/common.h"
#include "../h/machine.h"
#include "../h/new.h"
#include "../h/files.h"
#include "../h/gram.h"
#include "../h/state.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
extern char **tags;
extern int nstates;
extern short *accessing_symbol;
extern core **state_table;
extern shifts **shift_table;
extern errs **err_table;
extern reductions **reduction_table;
extern char *consistent;
extern char any_conflicts;
extern char *conflicts;
extern int final_state;

extern void conflict_log();
extern void verbose_conflict_log();
extern void print_reductions();

void print_token();
void print_state();
void print_core();
void print_actions();
void print_grammar();

void
terse (void)
{
  if (any_conflicts)
    {
      conflict_log();
    }
}


void
verbose (void)
{
  int i;

  if (any_conflicts)
    verbose_conflict_log();

  print_grammar();

  for (i = 0; i < nstates; i++)
    {
      print_state(i);
    }
}


#if (0)	/*************************************/
void
print_token (int extnum, int token)
{
  fprintf(foutput, " type %d is %s\n", extnum, tags[token]);
}
#endif	/*************************************/


void
print_state (int state)
{
  fprintf(foutput, "\n\nstate %d\n\n", state);
  print_core(state);
  print_actions(state);
}


void
print_core (int state)
{
  int i;
  int k;
  int rule;
  core *statep;
  short *sp;
  short *sp1;

  statep = state_table[state];
  k = statep->nitems;

  if (k == 0) return;

  for (i = 0; i < k; i++)
    {
      sp1 = sp = ritem + statep->items[i];

      while (*sp > 0)
	sp++;

      rule = -(*sp);
      fprintf(foutput, "    %s  ->  ", tags[rlhs[rule]]);

      for (sp = ritem + rrhs[rule]; sp < sp1; sp++)
	{
	  fprintf(foutput, "%s ", tags[*sp]);
	}

      putc('.', foutput);

      while (*sp > 0)
	{
	  fprintf(foutput, " %s", tags[*sp]);
	  sp++;
	}

      fprintf (foutput, "   (rule %d)", rule);
      putc('\n', foutput);
    }

  putc('\n', foutput);
}


void
print_actions (int state)
{
  int i;
  int k;
  int state1;
  int symbol;
  shifts *shiftp;
  errs *errp;
  reductions *redp;
  int rule;

  shiftp = shift_table[state];
  redp = reduction_table[state];
  errp = err_table[state];

  if (!shiftp && !redp)
    {
      if (final_state == state)
	fprintf(foutput, "    $default\taccept\n");
      else
	fprintf(foutput, "    NO ACTIONS\n");
      return;
    }

  if (shiftp)
    {
      k = shiftp->nshifts;

      for (i = 0; i < k; i++)
	{
	  if (! shiftp->shifts[i]) continue;
	  state1 = shiftp->shifts[i];
	  symbol = accessing_symbol[state1];
	  /* The following line used to be turned off.  */
	  if (ISVAR(symbol)) break;
          if (symbol==0)      /* I.e. strcmp(tags[symbol],"$")==0 */
            fprintf(foutput, "    $   \tgo to state %d\n", state1);
          else
            fprintf(foutput, "    %-4s\tshift, and go to state %d\n",
                    tags[symbol], state1);
	}

      if (i > 0)
	putc('\n', foutput);
    }
  else
    {
      i = 0;
      k = 0;
    }

  if (errp)
    {
      int j, nerrs;

      nerrs = errp->nerrs;

      for (j = 0; j < nerrs; j++)
	{
	  if (! errp->errs[j]) continue;
	  symbol = errp->errs[j];
	  fprintf(foutput, "    %-4s\terror (nonassociative)\n", tags[symbol]);
	}

      if (j > 0)
	putc('\n', foutput);
    }

  if (consistent[state] && redp)
    {
      rule = redp->rules[0];
      symbol = rlhs[rule];
      fprintf(foutput, "    $default\treduce using rule %d (%s)\n\n",
     	        rule, tags[symbol]);
    }
  else if (redp)
    {
      print_reductions(state);
    }

  if (i < k)
    {
      for (; i < k; i++)
	{
	  if (! shiftp->shifts[i]) continue;
	  state1 = shiftp->shifts[i];
	  symbol = accessing_symbol[state1];
	  fprintf(foutput, "    %-4s\tgo to state %d\n", tags[symbol], state1);
	}

      putc('\n', foutput);
    }
}

#define END_TEST(end) \
  if (column + strlen(buffer) > (end))					 \
    { fprintf (foutput, "%s\n   ", buffer); column = 3; buffer[0] = 0; } \
  else

void
print_grammar (void)
{
  int i, j;
  short* rule;
  char buffer[90];
  int column = 0;

  /* rule # : LHS -> RHS */
  fputs("\nGrammar\n", foutput);
  for (i = 1; i <= nrules; i++)
    /* Don't print rules disabled in reduce_grammar_tables.  */
    if (rlhs[i] >= 0)
      {
	fprintf(foutput, "rule %-4d %s ->", i, tags[rlhs[i]]);
	rule = &ritem[rrhs[i]];
	if (*rule > 0)
	  while (*rule > 0)
	    fprintf(foutput, " %s", tags[*rule++]);
	else
	  fputs ("		/* empty */", foutput);
	putc('\n', foutput);
      }

  /* TERMINAL (type #) : rule #s terminal is on RHS */
  fputs("\nTerminals, with rules where they appear\n\n", foutput);
  fprintf(foutput, "%s (-1)\n", tags[0]);
  if (translations)
    {
      for (i = 0; i <= max_user_token_number; i++)
	if (token_translations[i] != 2)
	  {
	    buffer[0] = 0;
	    column = strlen (tags[token_translations[i]]);
	    fprintf(foutput, "%s", tags[token_translations[i]]);
	    END_TEST (50);
	    sprintf (buffer, " (%d)", i);

	    for (j = 1; j <= nrules; j++)
	      {
		for (rule = &ritem[rrhs[j]]; *rule > 0; rule++)
		  if (*rule == token_translations[i])
		    {
		      END_TEST (65);
		      sprintf (buffer + strlen(buffer), " %d", j);
		      break;
		    }
	      }
	    fprintf (foutput, "%s\n", buffer);
	  }
    }
  else
    for (i = 1; i < ntokens; i++)
      {
	buffer[0] = 0;
	column = strlen (tags[i]);
	fprintf(foutput, "%s", tags[i]);
	END_TEST (50);
	sprintf (buffer, " (%d)", i);

	for (j = 1; j <= nrules; j++)
	  {
	    for (rule = &ritem[rrhs[j]]; *rule > 0; rule++)
	      if (*rule == i)
		{
		  END_TEST (65);
		  sprintf (buffer + strlen(buffer), " %d", j);
		  break;
		}
	  }
	fprintf (foutput, "%s\n", buffer);
      }

  fputs("\nNonterminals, with rules where they appear\n\n", foutput);
  for (i = ntokens; i <= nsyms - 1; i++)
    {
      int left_count = 0, right_count = 0;

      for (j = 1; j <= nrules; j++)
	{
	  if (rlhs[j] == i)
	    left_count++;
	  for (rule = &ritem[rrhs[j]]; *rule > 0; rule++)
	    if (*rule == i)
	      {
		right_count++;
		break;
	      }
	}

      buffer[0] = 0;
      fprintf(foutput, "%s", tags[i]);
      column = strlen (tags[i]);
      sprintf (buffer, " (%d)", i);
      END_TEST (0);

      if (left_count > 0)
	{
	  END_TEST (50);
	  sprintf (buffer + strlen(buffer), " on left:");

	  for (j = 1; j <= nrules; j++)
	    {
	      END_TEST (65);
	      if (rlhs[j] == i)
		sprintf (buffer + strlen(buffer), " %d", j);
	    }
	}

      if (right_count > 0)
	{
	  if (left_count > 0)
	    sprintf (buffer + strlen(buffer), ",");
	  END_TEST (50);
	  sprintf (buffer + strlen(buffer), " on right:");
	  for (j = 1; j <= nrules; j++)
	    {
	      for (rule = &ritem[rrhs[j]]; *rule > 0; rule++)
		if (*rule == i)
		  {
		    END_TEST (65);
		    sprintf (buffer + strlen(buffer), " %d", j);
		    break;
		  }
	    }
	}
      fprintf (foutput, "%s\n", buffer);
    }
}
