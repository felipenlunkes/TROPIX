/*
 ****************************************************************
 *								*
 *			reduce.h				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.0, de 27.08.90				*
 *		2.3.3, de 12.12.90				*
 *								*
 *	M�dulo: reduce						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#undef	PRINT_CODES			/* Imprime os c�digos */

#define	CRCSZ	2
#define	STDIN	0
#define	STDOUT	1

#define	NOSTR	(char *)NULL
#define	NOCODEP	(int *)NULL
#define	NOPTR	(void *)NULL

#define	EVER	;;
#define	elif	else if

#define	str(x)	# x
#define	xstr(x)	str (x)

typedef unsigned short	ushort;	/* 16 bites sem sinal */

/*
 ****** Par�metros de compress�o ********************************
 */
#define NC		8 	/* Na �rea de c�digos sempre tem 8 c�digos */

#define BIT_SZ_TO_CODE(sz) ((1 << sz) - 1) /* Calcula o c�digo m�ximo */

#define MIN_BIT_SZ	9	/* O algoritmo come�a com 9 bits */ 

#define DEF_BIT_SZ	14	/* Se n�o for dado "-b" */ 

#define	CONTROL_CODE	256	/* C�digo de controle */

#define	FIRST_CODE	257	/* C�digo inicial */

#define TEST_INTERVAL	10000	/* A cada intervalo, examina a performance */

/*
 ****** Estrutura do cabe�alho **********************************
 */
typedef struct
{
	long	h_magic;	/* N�mero m�gico de identifica��o */
	off_t	h_size;		/* Tamanho do arquivo original */
	time_t	h_time;		/* Data da compress�o */
	long	h_reser1[2];	/* Reservado para uso futuro */
	char	h_bits;		/* N�mero m�ximo de bits do c�digo usado */
	char	h_flags;	/* Indicadores */
	ushort	h_crc;		/* CRC do header */

}	R_HEADER;

#define	R_MAGIC 0x12B9B0A0	/* N�mero PI * 100000000 */
#define	R_CRC	0x01		/* Foram gerados os CRCs */

/*
 ****** Estrutura da tabela HASH ********************************
 */
typedef struct
{
	ushort	h_omega;	/* Cadeia prefixo, ... */
	char	h_K;		/* que adicionada com este caracter, ... */
	ushort	h_omega_K;	/* gera este c�digo */

}	HASHTB;

#define NOCODE		0xFFFF	/* O �ltimo c�digo == n�o-cadeia */

#define NOHASHTB (HASHTB *)NULL

/*
 ****** Estrutura da tabela CODE ********************************
 */
typedef struct
{
	ushort	h_omega;	/* Cadeia prefixo, que adicionada com h_K, */
	char	h_K;		/* gera o c�digo de acesso a esta entrada */

}	CODETB;

#define NOCODETB (CODETB *)NULL

/*
 ****** STDIO alternativa ***************************************
 */
typedef struct
{
	char	*i_ptr;		/* ponteiro para o proximo caracter */
	char	*i_base;	/* ponteiro para o inicio do buffer */
	char	*i_bend;	/* fim do buffer normal */

}	CRCFILE;

#define	GETCHAR() 	(fp0->i_ptr < fp0->i_bend ? \
				 *fp0->i_ptr++ : readblock (fp0))

#define	PUTCHAR(c)  	{ if (fp1->i_ptr < fp1->i_bend)	\
				*fp1->i_ptr++ = (c);	\
			else				\
				writeblock ((c), fp1); }

/*
 ****** Entrada/sa�da da CODEIO *********************************
 */
typedef struct
{
	int	*c_ptr;		/* Ponteiro para o proximo c�digo */
	int	*c_base;	/* Ponteiro para o inicio do buffer */
	int	*c_bend;	/* Fim do buffer */

}	CODEFILE;

#define	GETCODE() 	(fp0->c_ptr < fp0->c_bend ? \
				 *fp0->c_ptr++ : readcode (fp0))

#define	PUTCODE(c)  	{ if (fp1->c_ptr < fp1->c_bend)	\
				*fp1->c_ptr++ = (c);	\
			else				\
				writecode ((c), fp1); }

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		reduce (void);
void		unreduce (void);
int		analysis (HASHTB *, int);
int		readblock (CRCFILE *);
void		writeblock (unsigned char, CRCFILE *);
int		getcode (void);
void		putcode (int);
int		readcode (CODEFILE *);
void		writecode (int, CODEFILE *);
void		write_max_code (void);
int		fillcode (void);
void		flushcode (void);
void		printtotal (off_t, off_t, int);
void		printtable (CODETB *, int);
void		getbuserror (int, ...);
char		*editpercent (int);
int		getpercent (long, long);
void		help (void);
