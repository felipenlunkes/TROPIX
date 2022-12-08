/*
 ****************************************************************
 *								*
 *			<sys/shlib.h>				*
 *								*
 *	Estrutura da tabela de bibliotecas compartilhadas	*
 *								*
 *	Vers�o	3.2.3, de 02.12.99				*
 *		4.3.0, de 12.06.02				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	SHLIB_H			/* Para definir os prot�tipos */

/*
 ******	Tabela de bibliotecas compartilhadas ********************
 */
typedef struct
{
	char	sh_name[16];	/* Nome da biblioteca */
	time_t	sh_time;	/* Data da biblioteca */

	ushort	sh_dep_mask;	/* Depend�ncias desta biblioteca */
	ushort	sh_hash_seq;	/* Ordem na inser��o HASH */

	long	sh_tsize;	/* Tamanho do TEXT */
	long	sh_dsize;	/* Tamanho do DATA */
	long	sh_bsize;	/* Tamanho do BSS */
	long	sh_ssize;	/* Tamanho da SYMTB */

	pg_t	sh_tvaddr;	/* Endere�o virtual do TEXT */
	pg_t	sh_dvaddr;	/* Endere�o virtual do DATA */

	ulong	sh_vaddr_mask;	/* Indica as p�ginas virtuais usadas */

	REGIONG	*sh_region;	/* Regi�o global do TEXT + DATA */

	/* Estat�sticas */

	int	sh_sym_count;	/* No. de s�mbolos */
	int	sh_hash_col;	/* Colis�es HASH */

}	SHLIB;

#define NSHLIB	4	/* N�mero m�ximo de bibliotecas compartihadas */

#define NOSHLIB	(SHLIB *)NULL

extern SHLIB	shlib_tb[];

/*
 ******	Prot�tipos de fun��es ***********************************
 */
enum { SHLIB_LOAD, SHLIB_UNLOAD, SHLIB_TABLE };	/* As opera��es */

extern int	shlib (int op, ...);
