/*
 ****************************************************************
 *								*
 *			<sys/kfile.h>				*
 *								*
 *	Estrutura de uma entrada da tabela KFILE		*
 *								*
 *	Vers�o	3.0.0, de 07.09.94				*
 *		3.1.6, de 13.01.99				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	KFILE_H			/* Para definir os prot�tipos */

/*
 ******	Formato da entrada **************************************
 */
struct	kfile
{
	LOCK	f_lock;		/* Spinlock para a entrada */
	char	f_union;	/* Indica o campo da uni�o */
	OFLAG	f_flags;	/* Indicadores: veja abaixo */

	int	f_count;	/* No. de Refer�ncias */

	INODE	*f_inode;	/* Ponteiro para o INODE */

  union
  {
	loff_t	f_loff;		/* Posi��o de Leitura/escrita */
	off_t	f_off[2];

  }	off_u;

  union
  {
    struct
    {
	/* Parte usada para o ENDPOINT */

	void	*f_u_endpoint;	/* Endpoint (TCP/UDP/IP) */

    }	t;

    struct
    {
	/* Parte usada para EVENTos de usu�rio */

	int	f_u_ueventlno;	/* No. de ueventl's associados a este file */
	int	f_u_ueventloff;	/* Offset na tabela de UEVENTL do conjunto */

    }	e;

    struct
    {
	/* Parte usada para SERMAforos de usu�rio */

	int	f_u_usemalno;	/* No. de usemal's associados a este file */
	int	f_u_usemaloff;	/* Offset na tabela de USEMAL do conjunto */

    }	s;

    struct
    {
	/* Parte usada para SHMEM (mem�ria compartilhada) */

	REGIONL	f_u_shmem_region; /* Regi�o da mem�ria compartilhada */

    }	m;

  }	u;

};

/*
 ******	Indicador do campo da uni�o *****************************
 */
enum { KF_NULL, KF_ITNET, KF_EVENT, KF_SEMA, KF_SHMEM };

/*
 ******	Macros �teis ********************************************
 */
#define	f_offset_low	off_u.f_off[0]
#define	f_offset_high	off_u.f_off[1]

#define	f_offset	off_u.f_loff

/*
 ******	Defini��es da ITNET *************************************
 */
#define	f_endpoint	u.t.f_u_endpoint

/*
 ******	Defini��es de EVENT *************************************
 */
#define	f_ueventlno	u.e.f_u_ueventlno
#define	f_ueventloff	u.e.f_u_ueventloff

/*
 ******	Defini��es de SEMA **************************************
 */
#define	f_usemalno	u.s.f_u_usemalno
#define	f_usemaloff	u.s.f_u_usemaloff

/*
 ******	Defini��es de SHMEM *************************************
 */
#define f_shmem_region	u.m.f_u_shmem_region

/*
 ******	Indicadores *********************************************
 */
#define	O_READ		0x0001		/* Leitura */
#define	O_WRITE		0x0002		/* Escrita */
#define	O_RW		0x0003		/* Leitura e Escrita */ 
#define	O_NDELAY	0x0004		/* N�o espere em Leitura/escrita */ 
#define	O_APPEND	0x0008		/* Escreva no final */ 
#define	O_FORMAT	0x0010		/* Formata��o */ 

#define	O_CREAT		0x0100		/* Crie o Arquivo se n�o existe */ 
#define	O_TRUNC		0x0200		/* Trunque o Arquivo */ 
#define	O_EXCL		0x0400		/* Erro no open se j� existe */

/*
 ******	Parte Interna do Kernel *********************************
 */
#define	O_PHYS		0x0000		/* Mapeamento Fisico */
#define	O_KERNEL	0x1000		/* Mapeamento do Kernel */

#define	O_LOCK		0x4000		/* Open com Uso Exclusivo */
#define	O_PIPE		0x8000		/* � um Pipe ou Fifo */

/*
 ******	Indicadores do FCNTL ************************************
 */
#define	F_DUPFD	0	/* Duplica o descritor */
#define	F_GETFD	1	/* Obtem indicadores do descritor */
#define	F_SETFD	2	/* Atribui indicadores do descritor */
#define	F_GETFL	3	/* Obtem indicadores do arquivo */
#define	F_SETFL	4	/* Atribui indicadores do arquivo */

/*
 ******	Indicadores para a rotina "fopen" ***********************
 */
typedef	enum
{
	FOPEN,		/* Open normal */
	FCTRUNC,	/* Cria��o Truncando */
	FCNEW		/* Cria��o de Arquivo Novo */

}	FOFLAG;
