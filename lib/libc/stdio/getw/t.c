#include <stdio.h>
#include <errno.h>

main (argc, argv)
char	**argv;
{
	register char	*cp;
	register FILE	*fp;
	register	w;

	if ((fp = fopen (argv[1], "r")) == NOFILE)
	{
		printf
		(	"N�o consegui abrir \"%s\" (%s)\n",
			argv[1], strerror (errno)
		);
		exit (1);
	}

	while ((w = getw (fp)) != EOF)
		putw (w, stdout);

}	/* end t */
