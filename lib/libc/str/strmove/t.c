#include <stdio.h>
#include <string.h>

char	buf[125];

main ()
{
	for (;;)
	{
		memset (buf, '?', 125);

		if (gets (buf) != buf)
			return (0);

		if (strmove (buf+1, buf) != buf+1)
			printf ("***** N�o devolveu o endere�o certo!\n");
		printf ("%s\n", buf+1);

		if (strmove (buf, buf+1) != buf)
			printf ("***** N�o devolveu o endere�o certo!\n");
		printf ("%s\n", buf);
	}
}
