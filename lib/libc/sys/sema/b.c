#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define ALLOC	0
#define GET	1

main ()
{
	int j;
	int nsemas, fd, semaid, semadescr, initval;
	int cr;

	nsemas = 1;
	semaid = 0;
	initval = 2;

	fd = open ("Makefile", O_RDONLY);
	printf ("fd = %d\n", fd);

	if ((cr = semactl (ALLOC, fd, nsemas)) == -1)
	{
		printf ("N�o consegui alocar os sem�foros\n");
		exit (1);
	}
	printf ("C�digo de retorno na aloca��o = %08X, %d\n", cr, cr);

	if ((cr = semactl (GET, fd, semaid, initval)) == -1)
	{
		printf ("N�o consegui obter o descritor do sem�foro%d\n",
			 semaid);
		exit (1);
	}
	printf ("Descritor do primeiro sem�foro = %08X, %d\n", cr, cr);
	semadescr = cr;

	for (j = 0; j < 5; j++)
	{
		cr = semalock (semadescr);

		printf (" processo %d recebeu o recurso e ainda tinham %d\n",
				getpid (), cr);

/*
		for (i = 0; i <500000; i++);
*/
		sleep (5);

		cr = semafree (semadescr);

		printf (" processo %d liberou o recurso e agora tinham %d\n",
				getpid (), cr);

	}

	close (fd);
}
