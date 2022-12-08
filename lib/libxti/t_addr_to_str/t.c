#include <stdio.h>
#include <fcntl.h>
#include <xti.h>

main (int argc, register char *argv[])
{
	char		*pgname;
	long		addr;

	pgname = argv[0];

	if ((addr = t_str_to_addr (argv[1])) == -1)
	{
		fprintf (stderr, "N�o consegui obter o endere�o de \"%s\"\n", argv[1]);
		exit (1);
	}

	printf ("%s: %s (%P)\n", argv[1], t_addr_to_str (addr), addr);

	exit (0);
}
