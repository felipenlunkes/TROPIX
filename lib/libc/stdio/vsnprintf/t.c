#include <stdarg.h>
#include <stdio.h>

void error (char *function_name, char *format, ...);

main ()
{
	error ("fun��o", "Um argumento:      %d\n",  1);
	error ("fun��o", "Dois argumentos:   %d, %d\n", 1, 2);
	error ("fun��o", "Tres argumentos:   %d, %d, %d\n", 1, 2, 3);
	error ("fun��o", "Quatro argumentos: %d, %d, %d, %d\n", 1, 2, 3, 4);
	error ("fun��o", "Cinco argumentos:  %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
	error ("fun��o", "Seis argumentos:   %d, %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5, 6);
}

void error (char *function_name, char *format, ...)
{
	char		buf[128];

	register va_list args;

	va_start (args, format);

	vsnprintf (buf, 128, format, args);

	fprintf (stderr, "ERROR in \"%s\": %s", function_name, buf);

	va_end (args);
}
