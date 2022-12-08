/*
 ****************************************************************
 *								*
 *			crc16s.c				*
 *								*
 *	Calcula o CRC de 16 bits, baseado no CCITT		*
 *								*
 *	Vers�o	1.0.0, de 28.08.86				*
 *		3.0.0, de 18.06.95				*
 *								*
 *	M�dulo: crc16s						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 * 								*
 *	Calcula o CRC de 16 bits:				*
 * 								*
 *	O CRC (Cyclic Redundancy Check) � definido como o	*
 * 	resto da divis�o (m�dulo 2) da mensagem em buf		*
 * 	pelo polin�mio x**16 + x**15 + x**2 + 1			*
 *	recomendado pelo CCITT					*
 * 								*
 ****************************************************************
 */
int
crc16s (register unsigned char *buf, register int nbytes)
{
	register unsigned short	crc;
	register unsigned char	b, c;
	extern const short	crcstb[];

	crc = 0;

	while (nbytes-- > 0)
	{
		b = *buf++;

		c = b >> 4;
		crc = crcstb[crc >> 12] ^ ((crc << 4) | c);

		c = b & 0x0F;
		crc = crcstb[crc >> 12] ^ ((crc << 4) | c);
	}

	return (crc);

}	/* end crc16 */
