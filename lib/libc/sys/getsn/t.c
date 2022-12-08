#include <sys/syscall.h>

#include <stdio.h>
#include <errno.h>

main ()
{
	int		sn;

	if ((sn = getsn ()) == -1)
	{
		fprintf
		(	stderr,
			"N�o consegui obter o n�mero de s�rie (%s)\n",
			strerror (errno)
		);
		exit (1);
	}

	printf ("N�mero de s�rie = %d\n", sn);
}
