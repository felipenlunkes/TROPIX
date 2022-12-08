/*
 ****************************************************************
 *								*
 *			main.c					*
 *								*
 *	M�dulo principal, funcionando em 32 bits		*
 *								*
 *	Vers�o	3.0.0, de 05.07.94				*
 *		3.0.0, de 28.07.94				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"

#include "../h/proto.h"

/*
 ****** Defini��es globais **************************************
 */
#define	LINESZ	16

/*
 ******	Prot�tipos **********************************************
 */
void		dump_hex (const char *area, int count, long addr);

/*
 ****************************************************************
 *	Imprime DUMP da mem�ria					*
 ****************************************************************
 */
void
mem_dump (void)
{
	char		area[32];
	int		i;

	for (EVER)
	{
		printf ("\nD� o endere�o inicial: ");
		gets (area);

		if (area[0] == 'n')	/* EOF */
			return;

		i = strtol (area, (const char **)NULL, 0);

		if (i == -1)		/* EOF */
			return;

		for (EVER)
		{
			dump_hex ((char *)i, BLSZ, i);

			printf ("Continua? (s): ");

			if (askyesno (1) <= 0)
				break;

			i += BLSZ;
		}
	}

}	/* end mem_dump */

/*
 ****************************************************************
 *	Imprime um "dump" em hexadecimal e ISO			*
 ****************************************************************
 */
void
dump_hex (const char *area, int count, long addr)
{
	int		index = 0, i, n;
	const char	*cp;
	char		buf[16];

	/*
	 *	Inicia o dump
	 */
	while (count > 0)
	{
		if (count >= LINESZ)
			n = LINESZ;
		else
			n = count;

		printf ("%P:   ", addr);

		for (i = 0; i < LINESZ; i++)
		{
			if ((i & 1) == 0)
				printf (" ");

			if (i == LINESZ/2)
				printf (" ");

			if (i < n)
				printf ("%02X", area[i]);
			else
				printf ("  ");
		}

		printf ("     ");

		/*
		 *	Escreve caracteres em ascii
		 */
		for (cp = area, i = 0; i < n; cp++, i++)
		{
			if (*cp < 0x20)
				putchar ('.');
			else
				putchar (*cp);
		}

		putchar ('\n');

		/*
		 *	Se o endere�o � multiplo de 128, pula uma linha
		 */
		area  += n;
		addr  += n;
		index += n;
		count -= n;

		if (((index) & 127) == 0)
			gets (buf);

	}	/* end while */

}	/* end dump_hex */
