#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

void		func (int i);

int
main ()
{
	error ("Texto simples");

	errno = ENOSPC;
	error ("*@Texto com c�digo de erro simples");

	error_default_text = "Este � o texto padr�o modificado";
	error (NOSTR);

	errno = EINVAL;
	error_default_function = func;
	error_default_value = 2;
	error ("$*A seguir, programando a fun��o");

}

void
func (int i)
{
	error ("Esta � a fun��o chamada (valor = %d), error_count = %d", i, error_standard_count);
	exit (0);
}
