/*
 ****************************************************************
 *								*
 *			getopt.c				*
 *								*
 *	Fornece as op��es de um comando				*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 09.06.95				*
 *								*
 *	M�dulo: DOSMP						*
 *		Utilit�rios Sofisticados			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Inspirado no PLDOS de Norival Ribeiro Figueira	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>

#include "../h/edusr.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry const char	*cmd_optarg;   	/* Argumento de uma op��o */
entry int		cmd_optind;	/* Indice do argumento apos as op��es */
entry int		cmd_optinit;	/* Na pr�xima chamada, inicializa */

/*
 ****************************************************************
 *	Vari�veis locais estaticas				*
 ****************************************************************
 */
static const char *optp;		/* Ponteiro para a Op��o corrente */
static const char **argvv;		/* Ponteiro para o Argumento corrente */

/*
 ****************************************************************
 *	Ponto de entrada da rotina				*
 ****************************************************************
 */
int
cmd_getopt (const char *argv[], const char *optstring)
{
	int		c;
	const char	*cp;

	/*
	 *	(Re-)Inicializa��o
	 */
	if (cmd_optinit)
	{
		argvv = argv; 		optp = "" - 1;
		cmd_optind = 1; 	cmd_optinit = 0;
	}

	cmd_optarg = NOSTR; optp++;

	/*
	 *	Verifica se este argumento tem mais op��es 
	 */
	if (optp[0] == '\0')
	{
		argvv++; optp = argvv[0];

		if (optp == NOSTR || optp[0] != '-')
		{
			cmd_optind = argvv - argv;
			return (EOF);
		}

		if (optp[1] == '\0')
		{
			cmd_optind = argvv - argv;
			return (EOF);
		}

		if (optp[1] == '-')
		{
			cmd_optind = argvv - argv + 1;
			return (EOF);
		}

		optp++;

	}

	c = optp[0];

	/*
	 *	Procura a op��o na lista
	 */
	for (cp = optstring; cp[0] != '\0'; cp++) 
	{
		if (cp[0] == c)
			goto found;
	}

	fprintf (stderr, "%s: Op��o inv�lida: '%c'\n", argv[0], c);

	cmd_optarg = optp; return ('?');

	/*
	 *	A op��o foi encontrada na lista
	 */
    found:
	if (cp[1] != ':')
		return (c);

	/*
	 *	A Op��o tem Argumento
	 */
	argvv++;

	if (optp[1] == '\0' && optp[-1] == '-')
	{
		/*
		 *	Retorna o argumento
		 */
		if ((cmd_optarg = argvv[0]) == NOSTR)
		{
			fprintf
			(	stderr,
				"%s: Faltando o argumento da op��o '%c'\n",
				argv[0],
				c
			);

			cmd_optarg = optp; return ('?');
		}

		return (c);
	}
	else
	{
		/*
		 *	Foram encontrados Caracteres Estranhos
		 *	antes ou depois desta op��o
		 */
		fprintf
		(	stderr,
			"%s: Caracteres estranhos antes ou "
			"ap�s a op��o '%c'\n",
			argv[0],
			c
		);

		cmd_optarg = optp; return ('?');
	}

}	/* end cmd_getopt */
