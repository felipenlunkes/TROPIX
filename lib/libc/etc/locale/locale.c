/*
 ****************************************************************
 *								*
 *			locale.c				*
 *								*
 *	Ger�ncia de localiza��o da "libc"			*
 *								*
 *	Vers�o	3.0.0, de 27.01.98				*
 *		3.0.0, de 29.01.98				*
 *								*
 *	M�dulo: locale						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

/*
 ****************************************************************
 *	Atribui a localidade					*
 ****************************************************************
 */
const char *
setlocale (int category, register const char *locale)
{
	/*
	 *	Verifica se est� questionando
	 */
	if (locale == NOSTR)
	{
		switch (category)
		{
		    case LC_ALL:	/* Todo o "locale" */
			if (_lc_vector[LC_ALL][0] == CHAR_MAX)
				return (NOSTR);
		    case LC_COLLATE:	/* Fun��es "strcoll" e "strxfrm" */
		    case LC_CTYPE:	/* Fun��es de an�lise de caracteres */
		    case LC_MONETARY:	/* Informa��o monet�ria */
		    case LC_NUMERIC:	/* Ponto decimal (e outros) */
		    case LC_TIME:	/* Fun��o "strftime" */
			return (_lc_vector[category]);

		    default:
			return (NOSTR);

		}	/* end switch */
	}

	/*
	 *	Examina a cadeia "locale"
	 */
	if (*locale == '\0' || streq (locale, "C"))
		locale = "P";

	if (!streq (locale, "P") && !streq (locale, "E"))
		return (NOSTR);

	/*
	 *	Atribui o "locale"
	 */
	switch (category)
	{
	    case LC_ALL:	/* Todo o "locale" */
		for (category = LC_ALL; category <= LC_TIME; category++)
			strcpy (_lc_vector[category], locale);
		break;

	    case LC_COLLATE:	/* Fun��es "strcoll" e "strxfrm" */
	    case LC_CTYPE:	/* Fun��es de an�lise de caracteres */
	    case LC_MONETARY:	/* Informa��o monet�ria */
	    case LC_NUMERIC:	/* Ponto decimal (e outros) */
	    case LC_TIME:	/* Fun��o "strftime" */
		strcpy (_lc_vector[category], locale);

		/* Verifica se todos est�o iguais */

		for (category = LC_ALL + 1; /* abaixo */; category++)
		{
			if (category > LC_TIME)
			{
				strcpy (_lc_vector[LC_ALL], locale);
				break;
			}

			if (!streq (_lc_vector[category], locale))
			{
				_lc_vector[LC_ALL][0] = CHAR_MAX;
				break;
			}
		}

		break;

	}	/* end switch */

	return (locale);

}	/* end setlocale */

/*
 ****************************************************************
 *	Retorna a localidade num�rica				*
 ****************************************************************
 */
const LCONV *
localeconv (void)
{
	return (&_lc_lconv);

}	/* end localeconv */
