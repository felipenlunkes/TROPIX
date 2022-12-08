#include <stdio.h>
#include <stdlib.h>
#include <xti.h>
#include <fcntl.h>

#define	NOSTR	(char *)NULL

entry char	*pgname;	/* Nome do programa */

main (int argc, register char *argv[])
{
	register int	fd;
	T_INFO		info;

	pgname = argv[0];

	/*
	 *	Modo de usar: t
	 *
	 *	T_COTS		1	connection mode
	 *	T_COTS_ORD	2	connection mode com desconex�o ordenada
	 *	T_CLTS		3	connectionless mode
	 */
	argv += 1;
	argc -= 1;

	/*
	 *	Abre o "endpoint" UDP
	 */
	if ((fd = t_open ("/dev/itnudp", O_RDWR, (T_INFO *)NULL)) < 0)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", "/dev/itnudp");
		perror (pgname);
		exit (1);
	}

	/*
	 *	Obt�m as informa��es UDP
	 */
	if (t_getinfo (fd, &info) < 0)
	{
		fprintf (stderr, "N�o consegui obter as informa��es\n");
		perror (pgname);
		exit (1);
	}

	/*
	 *	Imprime as informa��es UDP
	 */
	printf
	(	"\nUDP:\n\n"
		"info.addr = %d\n"
		"info.options = %d\n"
		"info.tsdu = %d\n"
		"info.etsdu = %d\n"
		"info.connect = %d\n"
		"info.discon = %d\n"
		"info.servtype = %d\n",

	 	info.addr,
		info.options,
		info.tsdu,
		info.etsdu,
		info.connect,
		info.discon,
		info.servtype
	);

	t_close (fd);

	/*
	 *	Abre o "endpoint" TCP
	 */
	if ((fd = t_open ("/dev/itntcp", O_RDWR, (T_INFO *)NULL)) < 0)
	{
		fprintf (stderr, "N�o consegui abrir \"%s\"\n", "/dev/itntcp");
		perror (pgname);
		exit (1);
	}

	/*
	 *	Obt�m as informa��es TCP
	 */
	if (t_getinfo (fd, &info) < 0)
	{
		fprintf (stderr, "N�o consegui obter as informa��es\n");
		perror (pgname);
		exit (1);
	}

	/*
	 *	Imprime as informa��es TCP
	 */
	printf
	(	"\nTCP:\n\n"
		"info.addr = %d\n"
		"info.options = %d\n"
		"info.tsdu = %d\n"
		"info.etsdu = %d\n"
		"info.connect = %d\n"
		"info.discon = %d\n"
		"info.servtype = %d\n",

	 	info.addr,
		info.options,
		info.tsdu,
		info.etsdu,
		info.connect,
		info.discon,
		info.servtype
	);

	t_close (fd);

	exit (0);

}	/* end t */
