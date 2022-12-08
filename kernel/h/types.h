/*
 ****************************************************************
 *								*
 *			<sys/types.h>				*
 *								*
 *	Defini��o dos tipos fundamentais			*
 *								*
 *	Vers�o	1.0.0, de 22.07.86				*
 *		4.4.0, de 29.10.02				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	TYPES_H		/* Para incluir prot�tipos */

/*
 ******	Defini��es de tamanhos **********************************
 */
#define	SIDSZ		7		/* Tamanho de identificadores curtos */
#define	IDSZ		14		/* Tamanho padr�o de Identificadores */
#define	LIDSZ		31		/* Tamanho de identificadores longos */

/*
 ******	Defini��es de tipos *************************************
 */
typedef	unsigned char	uchar;		/* Char sem sinal */
typedef	signed char	schar;		/* Char com sinal */
typedef	unsigned short	ushort;		/* Short sem sinal */
typedef	unsigned long	ulong;		/* Long sem sinal */
typedef	long       	daddr_t;  	/* Endereco de Blocos de Disco */
typedef	char *     	caddr_t;  	/* Endereco de Memoria */
typedef	int		pg_t;     	/* Endereco de Pagina */
typedef	ulong		ino_t;     	/* No. de Inode */
typedef	long       	time_t;   	/* Tempo em segundos desde 1.1.70 */
typedef	int        	dev_t;    	/* Codigo de Dispositivo */
typedef	ulong       	off_t;    	/* Posi��o de um Arquivo */
typedef	long long      	loff_t;    	/* Posi��o de um Arquivo */
typedef	long		sid_t[2];	/* Identificador curto */
typedef	long		id_t[4];	/* Identificador */
typedef	long		lid_t[8];	/* Identificador longo */
typedef	long		*idp_t;		/* Ponteiro pata um identificador */

/*
 ******	Macros �teis ********************************************
 */
#define	MAJOR(x)	(int)((unsigned)(x) >> 8)
#define	MINOR(x)	(int)((x) & 0xFF)
