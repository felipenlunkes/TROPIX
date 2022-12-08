/*
 ****************************************************************
 *								*
 *			tac.c					*
 *								*
 *	Descompila a descri��o instalada de um terminal/v�deo	*
 *								*
 *	Vers�o	2.0.0, de 28.04.87				*
 *		3.0.1, de 12.07.97				*
 *								*
 *	Modulo: tac						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <ctype.h>
#include <errno.h>
#include <curses.h>
#include <terminfo.h>

/*
 ****************************************************************
 *	Vari�veis Locais					*
 ****************************************************************
 */
entry char	pgversion[] =  "Vers�o: 3.0.1, de 12.07.97";

typedef enum	{ false, true }	bool;

entry FILE	*output;		/* fp para a Saida */
entry const char *target;		/* Nome da Saida */

entry int	dflag;			/* Indicador de Depura��o */

/*
 ******	Constantes **********************************************
 */
#define	ESC	0x1B	/* Caractere ISO Escape */
#define	NL	0x0A	/* Caractere ISO New Line */
#define	CR	0x0D	/* Caractere ISO Carriage Return */
#define	HT	0x09	/* Caractere ISO Horizontal Tabulation */
#define	BS	0x08	/* Caractere ISO Back Space */
#define	NP	0x0C	/* Caractere ISO New Page */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	put_string (char *);
void	help (void);

/*
 ****************************************************************
 *	Descompila a descri��o instalada de um terminal/v�deo	*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	register int	i;
	const char	*termname;
	INFO		info;
	CAPHASH		*hp;
	char		*str;
	bool		pstring;

	/*
	 *	Interpreta��o das Op��es e Parametros
	 */
	while ((opt = getopt (argc, argv, "dH")) != EOF)
	{
		switch (opt)
		{
		    case 'd':
			dflag++;
			break;

		    case 'H':
			help ();

		    default:
			putc ('\n', stderr);
			help ();
		}
	}

	argv += optind;
   /***	argc -= optind; ***/

	/*
	 *	Obt�m o nome do Terminal
	 */
	termname = NOSTR;

	if (argv[0] != NOSTR)
		termname = *argv++;

	if (termname == NOSTR || streq (termname, "-")) 
		termname = getenv ("TERM");

	if (termname == NOSTR)
	{
		fprintf
		(	stderr,
			"N�o consegui obter o nome do terminal\n",
			target, strerror (errno)
		);
		exit (1);
	}

	/*
	 *	Abertura do objeto (leg�vel)
	 */
	if (argv[0] != NOSTR)
	{
		target = *argv++;

		if (argv[0] != NOSTR)
			help ();

		if ((output = fopen (target, "w")) == NOFILE)
		{
			fprintf
			(	stderr,
				"N�o consegui abrir \"%s\" (%s)\n",
				target, strerror (errno)
			);
			exit (1);
		}
	}
	else
	{
		target = "stdout";
		output = stdout;
	}

	/*
	 *	Pega Informa��es
	 */
	if (!getinfo (termname, &info))
	{
		fprintf
	 	(	stderr,
			"%s: n�o encontrei informa��es sobre \"%s\"\n",
			pgname, termname
		);
		exit (1);
	}

	/*
	 *	Escrevendo a Se��o Names
	 */
	fputs ("#  Nomes\n", output);
	fputs (info.i_names, output);
	putc (',', output);

	/*
	 *	Escrevendo a Se��o Booleans
	 */
	fputs ("\n#  Capacidades Booleans \n\t", output);

	for (i = 0 ; i < info.i_boolno ; i++)
	{
		if (info.i_booleans[i])
		{
			fputs (capbnames[i], output);
			putc (',', output);
			putc (' ', output);
		}
	}

	/*
	 *	Escrevendo a Se��o Numbers
	 */
	fputs ("\n#  Capacidades Numericas \n\t", output);

	for (i = 0 ; i < info.i_numno ; i++)
	{
		if (info.i_numbers[i] >= 0)
		{
			fprintf (output, "%s#%d, ",
				capnnames[i], info.i_numbers[i]);
		}
	}

	/*
	 *	Escrevendo as Strings
	 */
	fputs ("\n#  Capacidades String \n", output);

	pstring = 0;

	for (i = 0 ; i < info.i_strno ; i++)
	{
		if (info.i_strings[i] != NOSTR)
		{
			/*
			 *	As strings param�tricas s�o descompiladas
			 */
			hp = caphash (capsnames[i]);
#ifdef	DEBUG
			printf
			(	"cap:%s, hp->h_id:%s, hp->h_class:%d, "
				"hp->h_order:%d\n",
				capsnames[i], hp->h_id,
				hp->h_class, hp->h_order
			);
#endif	DEBUG
			if (hp->h_class == C_PSTRING)
				str = parmuncomp (info.i_strings[i]);
			else
				str = info.i_strings[i];

			fprintf (output, "\t%s=", capsnames[i]);
			put_string (str);
			fputs(",\n", output);
		}
	}

	/*
	 *	Encerra Escrita
	 */
	if (ferror (output))
	{
		fprintf
		(	stderr,
			"Erro na escrita de \"%s\" (%s)\n",
			target, strerror (errno)
		);
		exit (1);
	}

	fclose (output);

	return (0);

}	/* end tac */

/*
 ****************************************************************
 *	Escreve uma capacidade String por Extenso		*
 ****************************************************************
 */
void	
put_string (char *string)
{
	register char	*s;

	for (s = string ; *s ; s++)
	{
		if   (isgraph (*s))
		{
			/*
			 *	Caracteres Comuns
			 *	(alguns tem de ser "escapados")
			 */
			switch (*s)
			{
			    case '\\':
			    case '^':
			    case ',':
				putc ('\\', output);
				putc (*s, output);
				break;

			    default:
				putc (*s, output);
			}
		}
		else
		{
			/*
			 *	Caracteres de Controle
			 *	("escapados" ou na forma "^X")
			 */
			switch (*s)
			{
			    case ' ':
				putc ('\\', output);
				putc ('s', output);
				break;

			    case ESC:
				putc ('\\', output);
				putc ('E', output);
				break;

			    case NL:
				putc ('\\', output);
				putc ('n', output);
				break;

			    case CR:
				putc ('\\', output);
				putc ('r', output);
				break;

			    case HT:
				putc ('\\', output);
				putc ('t', output);
				break;

			    case BS:
				putc ('\\', output);
				putc ('b', output);
				break;

			    case NP:
				putc ('\\', output);
				putc ('f', output);
				break;

			    case 0x80:
				putc ('\\', output);
				putc ('0', output);
				break;

			    default:
				if (isascii (*s))
				{
					putc ('^', output);
					putc (*s | 0x40, output);
				}
				else
				{
					fprintf (output, "\\%o", *s);
				}
			}
		}

	}	/* end for string */

}	/* end put_string */

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
		"%s - descompila a descri��o instalada de um terminal/v�deo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [<term> [<fonte>]]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nObs.: Se n�o for dado \"<term>\", ou for dado \"-\", "
		"ser� considerado \"$TERM\"\n"
		"      Se n�o for dado \"<fonte>\", "
		"a descri��o fonte ser� posta em \"stdout\"\n"
	);

	exit (2);

}	/* end help */
