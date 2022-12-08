#include <sys/kcntl.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

main (int argc, register const char *argv[])
{
	register int	types, i;

	types = kcntl (K_GET_FD_TYPE);

	for (i = 0; i < 2; i++, types >>= 8)
	{
		printf ("/dev/fd%d: ", i);

		switch (types & 0xFF)
		{
		    case 0:
			printf ("Unidade de disquete n�o dispon�vel\n");
			break;

		    case 1:
			printf ("Unidade de 5�, 360 Kb\n");
			break;

		    case 2:
			printf ("Unidade de 5�, 1.2 Mb\n");
			break;

		    case 3:
			printf ("Unidade de 3�, 720 Kb\n");
			break;

		    case 4:
			printf ("Unidade de 3�, 1.44 Mb\n");
			break;

		    default:
			printf ("Unidade desconhecida\n");
			break;
		}
	}

	exit (0);
}

