/*
 ****************************************************************
 *								*
 *			reduce.h				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.00, de 27.08.90				*
 *		3.1.06, de 04.05.97				*
 *								*
 *	M�dulo: GAR						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
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

#define	NOCODEP	(int *)NULL

/*
 ****** Par�metros de compress�o ********************************
 */
#define NC		8 	/* Na �rea de c�digos sempre tem 8 c�digos */

#define BIT_SZ_TO_CODE(sz) ((1 << sz) - 1) /* Calcula o c�digo m�ximo */

#define MIN_BIT_SZ	9	/* O algoritmo come�a com 9 bits */ 

#define	CONTROL_CODE	256	/* C�digo de controle */

#define	FIRST_CODE	257	/* C�digo inicial */

#define TEST_INTERVAL	10000	/* A cada intervalo, examina a performance */

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

typedef CRCFILE	COLFILE;

#define	GETC(fp) 	(fp->i_ptr < fp->i_bend ? \
				 *fp->i_ptr++ : readcol (fp))

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
 ****** Vari�veis externas **************************************
 */
extern long	in_cnt, out_cnt; /* Total de caracteres de entrada/sa�da */

extern int	in_fd;		/* Descritor do arquivo */

extern FILE	*out_fp;	/* FILE do arquivo */

extern int	code_area[NC];	/* Cabem sempre NC c�digos at� de 16 bits */

/*
 ****** Par�metros de compress�o ********************************
 */
extern int	MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

extern int	MAX_BIT_USED;	/* N�mero de bits realmente usados */ 

extern int	MAX_CODE;	/* Nunca pode usar este c�digo */

extern int	CODE_SOURCE;	/* Fonte de novos c�digos */

extern int	TEST_POINT;	/* Pr�ximo teste de performance */

extern int	bit_sz;		/* Tamanho atual */

extern int	max_code;	/* �ltimo c�digo do tamanho atual */

extern CRCFILE	incrcfile;	/* Bloco para STDIN */

extern CODEFILE	outcodefile;	/* Bloco para CODEOUT */

extern CRCFILE	outcrcfile;	/* Bloco para STDOUT */

extern CODEFILE	incodefile;	/* Bloco para CODEIN */

extern COLFILE	incolfile;	/* COLFILE da cole��o */

extern off_t	col_size;	/* Tamanho do arquivo comprimido na cole��o */ 

extern int	file_block;	/* No. do bloco do arquivo na cole��o */ 

/*
 ****** Prot�tipos de fun��es ***********************************
 */
extern int	analysis (HASHTB *, int);
extern int	readblock (CRCFILE *);
extern void	writeblock (unsigned char, CRCFILE *);
extern int	getcode (void);
extern void	putcode (int);
extern int	readcode (CODEFILE *);
extern void	writecode (int, CODEFILE *);
extern void	write_max_code (void);
extern int	readcol (COLFILE *);
extern int	fillcode (void);
extern void	flushcode (void);
extern void	printtotal (off_t, off_t);
extern void	printtable (CODETB *, int);
extern void	getbuserror (int);
extern void	quit (int);
