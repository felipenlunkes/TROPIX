#include <sys/syscall.h>

#include <stdio.h>

main (int argc, const char *argv[])
{
	if (argc != 3)
		error ("$N�o � assim que se usa!");

	if (rename (argv[1], argv[2]) < 0)
		error ("$*Erro na chamada RENAME");
}
