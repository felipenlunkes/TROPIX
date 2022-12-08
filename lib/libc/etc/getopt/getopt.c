/*
 ****************************************************************
 *								*
 *			getopt.c				*
 *								*
 *	Fornece as op��es de um comando				*
 *								*
 *	Vers�o	1.0.0, de 17.02.86				*
 *		3.0.0, de 22.06.95				*
 *								*
 *	M�dulo: getopt						*
 *		lib/etc 					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry const char	*optarg;   	/* Argumento de uma op��o */
entry int		optind = 1;	/* Indice do argumento apos as op��es */
entry int		opterr = 1;	/* Escreve mensagem de erro */

/*
 ****************************************************************
 *	Vari�veis locais estaticas				*
 ****************************************************************
 */
static const char *optp;	/* Ponteiro para a Op��o corrente */
static const char **argvv;	/* Ponteiro para o Argumento corrente */

/*
 ****************************************************************
 *	Fornece as op��es de um comando				*
 ****************************************************************
 */
int
getopt (int argc, const char *argv[], const char *optstring)
{
	register int		c;
	register const char	*cp;

	/*
	 *	Primeira chamada
	 */
	if (argvv == (const char **)NULL)
		{ argvv = argv; optp = "" - 1; }

	optarg = (const char *)NULL; optp++;

	/*
	 *	Verifica se este argumento tem mais op��es
	 */
	if (optp[0] == '\0')
	{
		argvv++; optp = argvv[0];

		if (optp == (const char *)NULL || optp[0] != '-')
		{
			optind = argvv - argv;
			argvv = (const char **)NULL;
			return (EOF);
		}

		if (optp[1] == '\0')
		{
			optind = argvv - argv;
			argvv = (const char **)NULL;
			return (EOF);
		}

		if (optp[1] == '-')
		{
			optind = argvv - argv + 1;
			argvv = (const char **)NULL;
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

	if (opterr)
		fprintf (stderr, "%s: Op��o inv�lida: '%c'\n", argv[0], c);

	optarg = optp; return ('?');

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
		if ((optarg = argvv[0]) == (const char *)NULL)
		{
			if (opterr)
			{
				fprintf
				(	stderr,
					"%s: Faltando o argumento da op��o '%c'\n",
					argv[0],
					c
				);
			}

			optarg = optp; return ('?');
		}

		return (c);
	}
	else
	{
		/*
		 *	Foram encontrados Caracteres Estranhos
		 *	antes ou depois desta op��o
		 */
		if (opterr)
		{
			fprintf
			(	stderr,
				"%s: Caracteres estranhos antes ou "
				"ap�s a op��o '%c'\n",
				argv[0],
				c
			);
		}

		optarg = optp; return ('?');
	}

}	/* end getopt */
