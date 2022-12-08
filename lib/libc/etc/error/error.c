/*
 ****************************************************************
 *								*
 *			error.c					*
 *								*
 *	Imprime uma mensagem de erro				*
 *								*
 *	Vers�o	3.2.3, de 21.12.99				*
 *		3.2.3, de 14.03.00				*
 *								*
 *	M�dulo: error						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

/*
 ******	Vari�veis globais ***************************************
 */
const char	*error_default_text		= "$Mem�ria esgotada";
entry void	(*error_default_function) (int) = &exit;
entry int	error_default_value		= 1;
entry int	error_standard_count;

/*
 ****************************************************************
 *	Imprime uma mensagem de erro				*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	va_list		args;
	const char	*fmt = format;
	char		err, abrt;
	int		save_errno = errno;

	va_start (args, format);

	if (format == NOSTR)
		fmt = error_default_text;

	if ((abrt = *fmt) == '$')
		fmt++;

	if ((err = *fmt) == '*')
		fmt++;

	if (*fmt == '@')
		{ fmt++; error_standard_count++; }

	fprintf  (stderr, "%s: ", pgname);
	vfprintf (stderr, fmt, args);

	if (err == '*' && save_errno != 0)
		fprintf (stderr, " (%s)", strerror (save_errno));

	putc ('\n', stderr);

	if (abrt == '$')
		error_default_function (error_default_value);

	va_end (args);

}	/* end error */
