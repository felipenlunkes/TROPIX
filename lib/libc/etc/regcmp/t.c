#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

/*
 ****************************************************************
 *	Programa de Teste para Expressoes Regulares.		*
 ****************************************************************
 */
main ()
{
	char	exp[80];
	char	line[80];
	char	match[80];
	char	*code = NULL;
	char	*p;

	while (1)
	{
		printf ("\nExpress�o: ");
		if (gets (exp) == NULL)
			break;

		if (streq (exp, "") && code != NULL)
			printf ("Repetindo a express�o regular anterior\n");
		else
			if ((code = regcmp (exp)) == NULL)
			{
				printf ("ERRO\n");
				continue;
			}

		printf ("Linha: ");
		if (gets (line) == NULL)
			break;

		if ((p = regex (code, line, match)) == NULL)
			printf ("Express�o nao encontrada\n");
		else
		{
			printf ("Encontrei: '%s'", match);
			if (*p)
				printf (" antes de: '%s'\n", p);
			else
				printf (" no final da linha\n");

			printf ("_loc1: '%s'\n", _loc1);
		}

	}

	printf ("fim\n");

}	/* end main */
