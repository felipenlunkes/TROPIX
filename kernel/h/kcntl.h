/*
 ****************************************************************
 *								*
 *			<sys/kcntl.h>				*
 *								*
 *	Controle do Kernel					*
 *								*
 *	Vers�o	1.0.0, de 02.02.87				*
 *		4.5.0, de 01.10.03				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	KCNTL_H			/* Para definir os prot�tipos */

/*
 ****************************************************************
 *	Comandos do KCNTL					*
 ****************************************************************
 */
typedef enum
{
	K_GETSYMGN = 1,		/* Obtem um SYM dado o nome */
	K_GETSYMGA,		/* Obtem um SYM dado o endereco */
	K_GETDEV,		/* Obtem o dev (MAJOR+MINOR) dado o devname */
	K_GETDEVNM,		/* Obtem o devname dado o dev (MAJOR+MINOR) */
	K_PUTCVTB,		/* Modifica a Tabela de convers�o */
	K_SEMAFREE,		/* Libera o recurso de um processo */
	K_GETPSZ,		/* Obt�m os tamanhos das �reas do processo */
	K_KTRACE,		/* Gera um trace dos recursos usados */
	K_GETMMU,		/* Obtem informa��es da gerencia de mem�ria */
	K_SETPREEMPTION,	/* Habilita preemption no kernel */
	K_ERRTOSTR,		/* Obt�m uma cadeia com o nome do erro */
	K_GET_DEV_TB,		/* Obt�m uma entrada da tabela de discos */
	K_GET_PARTNM,		/* Obt�m o nome de um tipo de parti��o */
	K_GET_FD_TYPE,		/* Obt�m os tipos dos disquetes */
	K_MMU_LIMIT,		/* Obt�m/atribui o limite da MMU */
	K_DEBUG,		/* Obt�m/atribui o valor de DEBUG */
	K_CR0,			/* Obt�m/atribui o valor de "cr0" */
	K_DMESG,		/* Obt�m as mensagens do "boot" */

}	KENUM;

/*
 ******	Estrutura para "K_GETPSZ" *******************************
 */
typedef struct
{
	long	k_tsize;	/* Tamanho do texto do processo (bytes) */
	long	k_dsize;	/* Tamanho do data+bss do processo (bytes) */
	long	k_ssize;	/* Tamanho da pilha do processo (bytes) */
	long	k_res0[5];	/* Reservado para uso futuro */

}	KPSZ;

/*
 ******	Defini��es para "K_KTRACE" ******************************
 */
#define	PROCSWTIME	1	/* Tempo para troca de processo */
#define	CLKINTTIME	2	/* Tempo para atend. int. rel�gio */

/*
 ****** Tabela de tipos de sistemas de arquivos *****************
 */
typedef struct
{
	int	pt_type;	/* Tipo do sistema de arquivos */
	char	*pt_nm;		/* Nome do sistema de arquivos */

}	PARTNM;

#define	PARTNM_MAXSZ	20	/* Nenhum nome tem mais de 20 caracteres */
