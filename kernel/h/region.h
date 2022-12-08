/*
 ****************************************************************
 *								*
 *			<sys/region.h>				*
 *								*
 *	Tabelas de regi�es de mem�ria				*
 *								*
 *	Vers�o	3.0.0, de 07.09.94				*
 *		4.6.0, de 22.08.04				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	REGION_H		/* Para definir os prot�tipos */

/*
 ******	Formato das estruturas **********************************
 */
struct	regionl
{
	char	rgl_type;	/* Tipo da regi�o */
	char	rgl_prot;	/* Tipo de prote��o da regi�o */

	pg_t	rgl_vaddr;	/* Endere�o virtual em p�ginas na mem�ria */
	REGIONG	*rgl_regiong;	/* Ponteiro para a regi�o global */
};

struct	regiong
{
	char	rgg_name[16];	/* Nome da regi�o */
	char	rgg_type;	/* Tipo da regi�o */
	char	rgg_flags;	/* Caracter�sticas da regi�o */
	LOCK	rgg_regionlock;	/* SPINLOCK de uso exclusivo da entrada */
	char	rgg_pgtb_sz;	/* Tamanho da tabela de p�ginas da regi�o */

	pg_t	rgg_size;	/* Tamanho da regi�o em p�ginas */
	pg_t	rgg_paddr;	/* Endere�o real em p�ginas na mem�ria */

	pg_t	rgg_pgtb;	/* Tabela de p�ginas da regi�o */
	int	rgg_count;	/* No. de proc. usando esta regi�o (procreg) */
	REGIONG	*rgg_next;	/* Pr�x. reg. assoc. mesmo i-node (shmemreg) */
};

/*
 ******	C�digo das regi�es **************************************
 */
enum
{
	RG_NONE,	/* Regi�o inexistente */
	RG_TEXT,	/* Regi�o de texto compartilhado */
	RG_DATA,	/* Regi�o de data (compart. entre threads) */
	RG_STACK,	/* Regi�o de stack nunca compartilhada */
	RG_PHYS,	/* Regi�o de PHYS */
	RG_SHMEM	/* Regi�o de mem�ria compartilhada */
};

#define RG_NAMES { "NONE", "TEXT", "DATA", "STACK", "PHYS", "SHMEM" }

/*
 ******	Indicadores para as opera��es com regi�es ***************
 */
enum
{
	RG_CLR	   = 1,		/* Regi�o deve ser zerada */
	RG_NOMMU   = 2,		/* N�o carrega/descarrega MMU */

	RG_PHYSDUP = 0,		/* Regi�o deve ser duplicada f�sicamente */
	RG_LOGDUP  = 4		/* Regi�o deve ser duplicada logicamente */
};

/*
 ******	Indicadores para as regi�es globais *********************
 */
enum
{
	RGG_METX   = 0x04	/* Manter c�pia do processo em mem�ria */
};

#define	RGG_FLAG_BITS	"\x03" "METX"

/*
 ******	Indicadores de cria��o de processos *********************
 */
enum { FORK, THREAD };
