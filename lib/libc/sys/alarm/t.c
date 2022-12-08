#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void
q (int signo)
{
	printf ("Veio o Sinal\n");

}	/* end q */

main ()
{
	register i;

	signal (SIGALRM, q);

	i = sleep (3);

	printf ("i = %d\n", i);

	signal (SIGALRM, q);
	alarm (2);

	i = sleep (5);

	printf ("i = %d\n", i);

	signal (SIGALRM, q);
	alarm (6);

	i = sleep (3);

	printf ("i = %d\n", i);

	pause ();

}	/* end t */
