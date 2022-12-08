#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

main ()
{
	int	nevents, event_fd, shmem_fd, size;
	int	event0, event1;
	int	*regaddr0;
	int	i;

	nevents = 4;
	size = 4096;
#if (0)	/*******************************************************/
	size = 2 * 4096;
#endif	/*******************************************************/
	i = 0;

	if ((event_fd = open ("eventfile", O_RDWR)) < 0)
	{
		printf ("N�o pude abrir \"eventfile\"\n");
		perror ("send");
		exit (1);
	}

	if ((shmem_fd = open ("shmemfile", O_RDWR)) < 0)
	{
		printf ("N�o pude abrir \"shmemfile\"\n");
		perror ("send");
		exit (1);
	}

	if (eventctl (UE_ALLOC, event_fd, nevents) == -1)
	{
		sleep (2);
		printf ("N�o consegui alocar os eventos\n");
		perror ("send");
		exit (1);
	}

	if ((int)(regaddr0 = shmem (shmem_fd, size)) == -1)
	{
		printf ("s: N�o consegui obter a mem�ria compartilhada (%s)\n", strerror (errno));
		exit (1);
	}

	if ((event0 = eventctl (UE_GET, event_fd, 0)) == -1)
	{
		sleep (2);
		printf ("N�o consegui obter o descritor do evento 0\n");
		exit (1);
	}

	if ((event1 = eventctl (UE_GET, event_fd, 1)) == -1)
	{
		sleep (2);
		printf ("N�o consegui obter o descritor do evento 1\n");
		exit (1);
	}
	sleep (2);
	printf ("Endere�o do in�cio da regi�o 0 = %P\n", regaddr0);
	sleep (2);

	printf ("Escrevendo na regi�o \n");
	sleep (2);

	for (;;)
	{
		*regaddr0 = i;
	
		eventdone (event0);

		printf ("Escreveu %08X na regi�o \n", i);
		sleep (1);
	
		eventwait (event1, ++i);
		sleep (2);
	}

	sleep (1);
	close (event_fd);
	close (shmem_fd);
}
