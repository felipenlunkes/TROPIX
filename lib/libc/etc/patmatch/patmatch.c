/*
 ****************************************************************
 *								*
 *			patmatch.c				*
 *								*
 *	Comparador de padr�es					*
 *								*
 *	Vers�o	1.1.0, de 14.08.86				*
 *		4.5.0, de 10.10.03				*
 *								*
 *	M�dulo: patmatch					*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>

/*
 ****************************************************************
 *	Comparador de padr�es					*
 ****************************************************************
 */
int
patmatch (register const char *sp /* Cadeia */, register const char *pp /* Padr�o */)
{
	register char	sc,	/* Caracter da Cadeia */
			pc;	/* Caracter do Padr�o */
	int		found,	/* Encontrou o Char. na lista */
			not = 0; /* Foi visto um '!' */
#undef	DEBUG
#ifdef	DEBUG
	printf ("DBG: str = \"%s\", pdr = \"%s\"\n", sp, pp);
#endif	DEBUG

	/*
	 *	O Padr�o pode conter '?', '*', '[....]', '!c', '![....]'.
	 *	O Caracter '\' desfaz a a��o especial dos caracteres
	 *	acima. A Compara��o � do estilo do "sh", mas
	 *	o caracter '/' � reconhecido por '?' e '*'
	 *
	 *	Devolve:
	 *	    1 => A Cadeia foi Reconhecida.
	 *	    0 => N�o foi Reconhecida, ou
	 *		 o Padr�o contem um erro de Sintaxe
	 */

	/*
	 *	Malha Principal de Compara��o
	 */
	for (/* sem inicializa��o */; /* sem teste */; sp++, pp++)
	{
		switch (pc = pp[0])
		{
			/*
			 *	O Padr�o contem um caracter Normal,
			 *	ou outras palavras, 
			 *	diferente de '?', '*', '[', '!' e '\0'
			 */
		    default:
			if (pc == sp[0])
				continue;
			else
				return (0);

			/*
			 *	O Padr�o Acabou
			 */
		    case '\0':
			if (sp[0] == '\0')
				return (1);
			else
				return (0);

			/*
			 *	Simula como se o "coringa" '?' fosse
			 *	igual ao caracter da cadeia
			 */
		    case '?':
			if (sp[0] == '\0')
				return (0);
			continue;

			/*
			 *	Procura Sufixos em comum
			 */
		    case '*':
			if ((++pp)[0] == '\0')
				return (1);

			while (sp[0] != '\0')
			{
				if (patmatch (sp++, pp))
					return (1);
			}

			return (0);

			/*
			 *	Trata o caracter seguinte como normal
			 */
		    case '\\':
			pp++;

			if ((pc = pp[0]) == '\0')
				return (0);

			if ((sc = sp[0]) == '\0' || sc != pc)
				return (0);

			continue;

		    case '!':
			pp++;
			if ((pc = pp[0]) == '\0')
				return (0);

			if (pc != '[')
			{
				/*
				 *	Compara��o inversa
				 */
				if ((sc = sp[0]) == '\0' || sc == pc)
					return (0);

				continue;
			}

			/*
			 *	pp[0] == '['. Prepara para [....] inverso
			 */
			not = 1;

			/* Cai atraves */

		    case '[':
			found = 0;

			if ((sc = sp[0]) == '\0')
				return (0);

			/*
			 *	Analisa a Sequencia '[....]'
			 */
			while ((pc = (++pp)[0]) != '\0')
			{
				switch (pc)
				{
				    default:
					if (pc == sc)
						found = 1;

					continue;

				    case '-':
					if (pp[-1] == '[' || pp[1] == ']')
					{
						if (sc == '-')
							found = 1;
					}
					else
					{
						if (pp[-1] <= sc && sc <= pp[1])
							found = 1;
					}

					continue;

				    case ']':
					if (found != not)
						goto nextchar;
					else
						return (0);

				}	/* end switch [......] */

			}	/* end while [......] */

		}	/* end switch */

		/*
		 *	A seq��ncia [....] terminou inesperadamente,
		 *	ou em todos os casos
		 */
		return (0);

	    nextchar:
		not = 0;

	}	/* end malha principal de compara��o */

}	/* end patmatch */
