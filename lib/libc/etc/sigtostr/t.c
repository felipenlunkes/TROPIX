
char	number[20];

main ()
{
	int		signum;
	extern char	*gets ();

	for (;;)
	{
		printf ("N�mero do sinal: ");
		if (gets (number) != number)
			exit (0);
		signum = strtol (number, (char **)0, 0);
		printf ("%d: %s\n", signum,  sigtostr (signum));
	}

}
