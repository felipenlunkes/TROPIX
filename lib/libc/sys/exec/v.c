#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

const char	*env[] =
{
	"env1=dddddddddddd",
	"evn2=tttttttttttt",
	"env3=yyyyyyyyyyyy",
	(char *)0
};

const char	*arg[] =
{
	"arg0",
	"arg1",
	"arg2",
	(char *)0
};

main (int argc, register const char *argv[], const char *envp[])
{
	if (argc == 2)
		environ = env;

	execv ("t", arg);

	perror (argv[0]);
}
