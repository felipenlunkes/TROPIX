#include <sys/syscall.h>

#include <stdio.h>
#include <errno.h>

int
main (int argc, register const char *argv[])
{
	const char	*pgname = argv[0];

	printf ("ATEN��O: VOU DAR BOOT!!!!!!\n");

	if (sync () < 0)
	{
		fprintf
		(
			stderr,
			"%s: N�o consegui dar SYNC (%s)\n",
			pgname, strerror (errno)
		);
	} 

	if (sync () < 0)
	{
		fprintf
		(
			stderr,
			"%s: N�o consegui dar SYNC (%s)\n",
			pgname, strerror (errno)
		);
	} 

	if (boot () < 0)
	{
		fprintf
		(
			stderr,
			"%s: N�o consegui dar BOOT (%s)\n",
			pgname, strerror (errno)
		);
	} 

}
