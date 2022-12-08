/*
 ****************************************************************
 *								*
 *			<sys/a.out.h>				*
 *								*
 *	Estrutura de m�dulos objeto				*
 *								*
 *	Vers�o	1.0.0, de 05.03.86				*
 *		4.3.0, de 13.07.02				*
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

#define	A_OUT_H			/* Para definir os prot�tipos */

/*
 ****************************************************************
 *	Estrutura do cabe�alho de um programa objeto 		*
 ****************************************************************
 */
#define	FMAGIC		0407	/* M�dulo regular */
#define	NMAGIC		0410	/* M�dulo reentrante */
#define	SMAGIC		0415	/* Biblioteca compartilhada */

typedef	struct
{
	ushort	h_machine;	/* Computador de Destino */
	ushort	h_magic;	/* Numero Magico */
	ushort	h_version;	/* No. da Vers�o */
	ushort	h_flags;	/* Indicadores (ver abaixo) */
	time_t	h_time;		/* Data e Hora da Gera��o */
	long	h_serial;	/* Numero de Serie */
	long	h_res1[2];	/* Reservado */
	long	h_tstart;	/* Endereco do Inicio do Text */
	long	h_dstart;	/* Endereco do Inicio do Data */
	long	h_entry;	/* Ponto de Entrada do Programa */
	long	h_tsize;	/* Tamanho do Text */
	long	h_dsize;	/* Tamanho do Data */
	long	h_bsize;	/* Tamanho do Bss */
	long	h_ssize;	/* Tamanho da Tabela de S�mbolos */
	long	h_rtsize;	/* Tamanho da Reloca��o para Text */
	long	h_rdsize;	/* Tamanho da Reloca��o para Data */
	long	h_lnosize;	/* Tamanho de Linhas */
	long	h_dbsize;	/* Tamanho da Tabela do "wsdb" */
	long	h_modsize;	/* Tamanho da Tabela de m�dulos */
	long	h_refsize;	/* Tamanho da Tabela de Refer�ncias */
	long	h_res2[1];	/* Reservado */

}	HEADER;

#define	NOHEADER (HEADER *)0

/*
 ****************************************************************
 *	Indicadores de "h_flags"				*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Elemento da tabela de s�mbolos				*
 ****************************************************************
 */
typedef struct
{
	long	s_value;		/* Valor */
	char	s_type;			/* Tipo do s�mbolo (ver abaixo) */
	char	s_flags;		/* Indicadores (ver baixo) */
	ushort	s_nm_len;		/* Tamanho do identificador */
	char	s_name[4];		/* Identificador de at� 64 KB */

}	SYM;

#define	SYM_SIZEOF(len)		(sizeof (SYM) + ((len) & ~3))
#define	SYM_NEXT_PTR(sp)	(SYM *)((int)(sp) + SYM_SIZEOF ((sp)->s_nm_len))
#define	SYM_NM_SZ(len)		(((len) + 4) & ~3)

/*
 ****************************************************************
 *	Tipos dos s�mbolos 					*
 ****************************************************************
 */
#ifndef	UNDEF
#define UNDEF	0		/* Indefinido */
#endif	UNDEF

#define	ABS	0x01		/* Absoluto (constantes) */
#define	TEXT	0x02		/* Text */
#define	DATA	0x03		/* Data */
#define	BSS	0x04		/* Bss */
#define	CONST	0x05		/* Const */
#define	REG	0x06		/* Registrador */

#define	SFILE	0x0A		/* Nome de arquivo */

#define EXTERN	0x20		/* Externo */

/*
 ****************************************************************
 *	Indicadores de "s_flags"				*
 ****************************************************************
 */
#define	S_EXTERN	0x80		/* S�mbolo global */
#define	S_LBL		0x40	 	/* O s�mbolo � um r�tulo */
#define	S_LOCAL		0x20		/* S�mbolo local */
#define	S_REF		0x10		/* S�mbolo foi referenciado */

/*
 ****************************************************************
 *	Estrutura de reloca��o					*
 ****************************************************************
 */
typedef	struct
{
	ushort	r_flags;	/* Indicadores (ver abaixo) */
	short	r_symbol;	/* Numero do S�mbolo na Tabela */
	long	r_pos;		/* Pos. Relativa ao Inicio da Se��o */

}	RELOC;

/*
 ******	Segmentos ***********************************************
 */
#define RSEGMASK	0x000F

#define RTEXT		0x0001
#define	RDATA		0x0002
#define	RBSS		0x0003
#define	REXT		0x0004
#define	REXTREL		0x0005

/*
 ******	Tamanhos ************************************************
 */
#define RSZMASK		0x00F0
#define RSZSHIFT	4

#define	RBYTE		0x0010
#define	RWORD		0x0020
#define	RLONG		0x0040

/*
 ****************************************************************
 *	Estrutura da tabela de refer�ncias externas		*
 ****************************************************************
 */
typedef struct
{
	ushort	r_ref_len;		/* No. de refer�ncias */
	ushort	r_nm_len;		/* Tamanho do identificador */
	char	r_name[4];		/* Identificador de at� 64 KB */

}	EXTREF;

#define	EXTREF_SIZEOF(len)		(sizeof (EXTREF) + ((len) & ~3))
#define	EXTREF_REFPTR(erp)		((void *)erp + EXTREF_SIZEOF (erp->r_nm_len))

/*
 ****************************************************************
 *	Estrutura da tabela de linhas				*
 ****************************************************************
 */
typedef struct
{
	long	ll_line;	/* Nr. da linha */
	long	ll_addr;	/* Endere�o do c�digo ou nome do m�dulo */

}	LINE;
