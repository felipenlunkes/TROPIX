main ()
{
	printf ("hu:	%hu\n", 12345);
	printf ("u:	%u\n", 12345);
	printf ("lu:	%lu\n", 12345);
	printf ("Lu:	%Lu\n", 12345);
	printf ("llu:	%llu\n", 12345ll);
	printf ("qu:	%qu\n", 12345ll);
	printf ("llu:	%llu\n", -12345ll);
	printf ("qu:	%qu\n", -12345ll);
	printf ("lld:	%lld\n", -12345ll);
	printf ("qd:	%qd\n", -12345ll);
	printf ("qu:	este valor (%qu) � grande\n", 1234567890123456789ll);
	printf ("llu:	este valor (%llu) � grande\n", 1234567890123456789ll);
	printf ("qd:	este valor (%qd) � grande\n", +1234567890123456789ll);
	printf ("lld:	este valor (%lld) � grande\n", +1234567890123456789ll);
	printf ("qd:	este valor (%qd) � grande\n", -1234567890123456789ll);
	printf ("lld:	este valor (%lld) � grande\n", -1234567890123456789ll);
}
