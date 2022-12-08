/*
 ****************************************************************
 *								*
 *			<sys/bhead.h>				*
 *								*
 *	Cabe�a de bloco de entrada/saida estruturada		*
 *								*
 *	Vers�o	3.0.0, de 06.09.94				*
 *		4.8.0, de 05.12.05				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	BHEAD_H			/* Para definir os prot�tipos */

#ifdef	BOOT
/*
 ******	Estrutura BHEAD para o BOOT2 ****************************
 */
struct	bhead
{
	ushort		b_flags;	/* Os indicadores para a opera��o */
	char		b_done;		/* Evento de opera��o terminada */

	daddr_t		b_blkno;	/* O n�mero do bloco */

	void		*b_addr;	/* A �rea de I/O */
	int		b_base_count;	/* O tamanho da �rea de I/O */
	long		b_residual;	/* Bytes que n�o foram transferidos */

	char		b_cmd_txt[16];	/* O texto do comando SCSI */
	int		b_cmd_len;	/* O tamanho do comando SCSI */

	void		*b_ptr;		/* O dispositivo */
	const DISKTB	*b_disktb;

	int		b_retry_cnt;	/* Tentativas */
};
#else
/*
 ******	Estrutura BHEAD para o KERNEL ***************************
 */
struct	bhead
{
	LOCK		b_lock;		/* Semaforo de buffer ocupado */
	EVENT		b_done;		/* Evento de opera��o terminada */
	ushort		b_flags;	/* Flags: veja abaixo */

	short		b_error;	/* Codigo do Erro (0 se n�o houve) */

	dev_t		b_dev;		/* Major+Minor do Dispositivo meta */
	dev_t		b_phdev;	/* Major+Minor do Dispositivo real */

	daddr_t		b_blkno;	/* No. do Bloco meta */
	daddr_t		b_phblkno;	/* No. do Bloco real */

	ino_t		b_ino;		/* No. do INODE (para NFS) */

	BHEAD		*b_next;	/* Fila Hash de Blocos */

	BHEAD		*b_forw;	/* Filas do Driver */
	BHEAD		*b_back;

	BHEAD		*b_lru_forw;	/* Lista LRU */
	BHEAD		*b_lru_back;

	time_t		b_dirty_time;	/* Tempo da �ltima altera��o */

	void		*b_base_addr;	/* Endereco Virtual do in�cio do bloco */
	void		*b_addr;	/* Endereco Virtual da �rea pedida */

	long		b_base_count;	/* No. de bytes pedidos a transferir */
	long		b_count;	/* No. de bytes dispon�veis */
	long		b_residual;	/* Bytes que n�o foram transferidos */

	ushort		b_cyloff;	/* Offset de Cilindro do Pseudo-disco */
	ushort		b_cylin;	/* No. do Cilindro dentro do Pseudo */

	void		*b_ptr;		/* Ponteiro auxiliar para o "driver" */

	char		b_cmd_txt[15];	/* Comando SCSI */
	char		b_cmd_len;

	const char	*b_dev_nm;	/* Nome da parti��o */

	int		b_retry_cnt;	/* Tentativas */

	int		b_pid;		/* PROVIS�RIO */
};

/*
 ******	Estrutura da tabela "hash" dos buffers ******************
 */
struct	bhashtb
{
	LOCK	h_lock;		/* Spinlock de cada entrada */
	char	h_reser[3];
	BHEAD	*h_bhead;	/* Comeco da Fila de Buffers */
};
#endif

/*
 ****** Indicadores *********************************************
 */
#define	B_WRITE		0x0000	/* Flag de Escrita (n�o-leitura) */
#define	B_READ		0x0001	/* Flag de Leitura */
#define	B_STAT		0x0002	/* Flag de consulta de Status */
#define	B_SWAP		0x0004	/* Entrada/saida de SWAP */
#define	B_ASYNC		0x0020	/* Opera��o assincrona */
#define	B_DIRTY		0x0040	/* S� escreva quando necessitar o bloco */
#define	B_ERROR		0x0100	/* Ocorreu algum de Erro */
#define	B_UP		0x1000	/* Sentido da Leitura do Disco no momento */
#define	B_DMA		0x2000	/* Foi utilizado DMA na transfer�ncia */

#define	B_AUTO		0x0002	/* DMA auto iniciado (para DMA) */
