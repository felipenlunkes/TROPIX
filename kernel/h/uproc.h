/*
 ****************************************************************
 *								*
 *			<sys/uproc.h>				*
 *								*
 *	Tabela de processos (agora na �rea do usu�rio)		*
 *								*
 *	Vers�o	3.0.0, de 04.10.94				*
 *		4.6.0, de 21.07.04				*
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

#define	UPROC_H			/* Para definir os prot�tipos */

/*
 ******	Os Estados dos Processos ********************************
 */
typedef enum
{
	SNULL,		/* Processo inexistente */
	SSWAPRDY,	/* Pronto no SWAP */
	SCORERDY,	/* Pronto na memoria */
	SSWAPSLP,	/* Esperando no SWAP */
	SCORESLP,	/* Esperando na memoria */
	SRUN,		/* Executando */
	SZOMBIE		/* Estado intermediario de t�rmino */

}	STATE;

/*
 ******	Indicadores do Processo *********************************
 */
#define	SSYS	0x0001		/* Processo do Sistema */
#define	SLOCK	0x0002		/* No momento n�o pode ir para SWAP */
#define	SULOCK	0x0008		/* Lock de usuario na memoria */
#define	SIGWAKE	0x0010		/* Foi acordado violentamente */
#define	STRACE	0x0020		/* Processo em TRACE */
#define	SWAITED	0x0040		/* Informa��o de TRACE j� foi dada */
#define	SIGEXIT 0x0080		/* Envia o sinal "SIGCHLD" quando der exit */
#define	RTPROC	0x0100		/* Processo de Tempo Real */

/*
 ****** Outras constantes ***************************************
 */
#define NSHLIB	4		/* N�mero m�ximo de bibliotecas compartihadas */

#define	PHYSNO	20		/* No. de Segmentos para Phys */

#define	EXCLOSE	1		/* Feche o Arquivo em um Exec */

/*
 ******	Estrutura do vetor de UPROCs ****************************
 */
struct uprocv
{
	UPROCV	*u_next;		/* Ponteiro da pr�pria lista */
	UPROC	*u_uproc;		/* Ponteiro para a UPROC */
};

/*
 ****************************************************************
 *	Entrada da Tabela de Processos				*
 ****************************************************************
 */
struct	uproc
{
	/*
	 *	As variaveis seguintes s�o herdadas na troca de
	 *	contexto e/ou s�o manipuladas por fun��es em "assembly"
	 */
	short		u_cpu;			/* No. da CPU rodando este processo */
	short		u_pri;			/* Prioridade, 0 a 1000 */

	uchar		u_ctxt_sw_type;		/* Usou a troca r�pida de contexto */
	uchar		u_no_user_mmu;		/* O processo n�o referencia a MMU de usu�rio */

	STATE		u_state;		/* Estado do Processo */
	long		u_sig;			/* Sinais pendentes deste Processo */
	mmu_t		*u_mmu_dir;		/* Endere�o do diret�rio de p�ginas */

	int		(*u_dontpanic) ();	/* A ser chamado em caso de BUS ERR */
	FRAME		*u_frame;		/* Frame-pointer do usu�rio */

	ctxt_t		u_ctxt;			/* Contexto para troca de processo */
	jmp_t		u_qjmp;			/* Contexto usado em "syscall" interrompido */

	/*
	 *	Parte regular
	 */
	int		u_flags;		/* Indicadores do Processo */

	uchar		u_mask;			/* CPU's em que o Processo pode rodar */
	LOCK		u_lock;			/* Semaforo da Entrada */
	LOCK		u_childlock;		/* Semaforo da fila de filhos */
	EVENT		u_deadchild;		/* Evento de Termina��o de um filho */

	ushort		u_time;			/* Tempo de residencia (CORE ou SWAP) */
	schar		u_nice;			/* valor do nice (-NBASE a +NBASE) */
	EVENT		u_trace;		/* Evento do estado TRACE */

	long		u_pid;			/* Numero do Processo */
	long		u_pgrp;			/* Numero do lider do grupo de processos */
	long		u_tgrp;			/* Numero do Grupo de Terminais */

	UPROCV		*u_uprocv;		/* Ponteiro de volta para o vetor */

	UPROC		*u_myself;		/* Endere�o virtual da pr�pria UPROC */
	UPROC		*u_parent;		/* Pai do Processo */
	UPROC		*u_child;		/* Ponteiro para a fila de Filhos */
	UPROC		*u_sibling;		/* Ponteiro para a fila de Irmaos */

	UPROC		*u_next;		/* Fila de processos READY, ou ZOMBIE, ... */

	char		u_pgname[16];		/* In�cio do nome do Programa em Execu��o */

	pg_t		u_size;			/* Tamanho do Processo (p�ginas) */

	REGIONL		u_text;			/* Regi�o do TEXT */
	REGIONL		u_data;			/* Regi�o do DATA */
	REGIONL		u_stack;		/* Regi�o da STACK */

	REGIONL		u_shlib_text[NSHLIB];	/* Regi�o TEXT das bibliotecas compartilhadas */
	REGIONL		u_shlib_data[NSHLIB];	/* Regi�o DATA das bibliotecas compartilhadas */

	void		*u_sema;		/* Semaforo ou evento de espera */

	short		u_stype;		/* Tipo do semaforo */
	ushort		u_alarm;		/* Tempo (seg) para enviar o SIGALARM */

	INODE		*u_inode;		/* Ponteiro para o inode de um TEXTO */

	char		u_syncn;		/* No. de Recursos Ocupados */
	char		u_syncmax;		/* No. maximo de Recursos Ocupados */
	short		u_rtpri;		/* Prioridade de Proc. de Tempo Real */

	EVENT		u_attention_event;	/* Evento do ATTENTION */
	schar		u_attention_index;	/* File descriptor index do ATTENTION (at� 127) */

	schar		u_grave_index;		/* �ndice do fd para "grave" */
	char		u_grave_attention_set;	/* Attention armado para "grave" */

	SYNCH		u_synch[NHIST];		/* O Historico do Sincronismo */

	/*
	 *	Parte de comunica��o com o pai do processo
	 */
	void		*u_fa;			/* Endereco de erro */
	void		*u_pc;			/* Endereco de execu��o */
	int	u_rvalue;		/* Codigo de retorno do Wait */

	/*
	 *	Tamanhos deste processo (em paginas)
	 */
	pg_t		u_tsize;		/* Tamanho do texto */
	pg_t		u_dsize;		/* Tamanho do data */
	pg_t		u_ssize;		/* Tamanho da stack */

	/*
	 *	Identifica��o do Usuario
	 */
	ushort		u_euid;			/* Usuario efetivo  */
	ushort		u_egid;			/* Grupo   efetivo */
	ushort		u_ruid;			/* Usuario real */
	ushort		u_rgid;			/* Grupo   real */

	/*
	 *	Valores dados/retornados no syscall
	 */
	int		u_fd;			/* File Descriptor */
	int		u_error;		/* Codigo de Erro de Retorno */

	/*
	 *	Diretorios & Nomes de Arquivos
	 */
	INODE		*u_cdir;		/* Inode do diretorio corrente */
	INODE		*u_rdir;		/* Inode da raiz corrente */
	char		u_name[16];		/* Componente corrente do nome */

	/*
	 *	Registros para PHYS
	 */
	int		u_phn;			/* No. de phys do momento */

	REGIONL		u_phys_region[PHYSNO];	/* As regi�es locais do PHYS */

	/*
	 *	Arquivos Usados por este Processo	
	 */
	KFILE		*u_ofile[NUFILE];	/* Arquivos abertos por este */
	uchar		u_ofilef[NUFILE];	/* processo e seus flags */

	/*
	 *	Estado dos Sinais
	 */
	void		(*u_signal[NSIG+1]) (int, ...);	/* Estado dos sinais */
	void		(*u_sigludium) ();

	/*
	 *	Tempos
	 */ 
	time_t		u_utime;		/* Tempo de sistema deste processo */
	time_t		u_stime;		/* Tempo de usuario deste processo */
	time_t		u_cutime;		/* Soma dos "utime"s dos filhos */
	time_t		u_cstime;		/* Soma dos "stime"s dos filhos */

	/*
	 *	Terminal associado a este processo
	 */
	TTY		*u_tty;			/* Estrutura TTY */
	dev_t		u_ttydev;		/* Codigo do Dispositivo */

	/*
	 *	Estado do processador de ponto flutuante INTEL Pentium
	 */
	char		u_fpu_used;		/* FPU do PC usado neste processo */
	char		u_fpu_lately_used;	/* FPU usado no corrente time-slice */
	long		u_fpstate[55];		/* Estado interno */

	/*
	 *	Outras vari�veis Diversas
	 */
	time_t		u_start;		/* Tempo de cria��o do processo */
	int		u_cmask;		/* Mascara para cria��o de arq. */
	pg_t		u_xargs;		/* Endere�o da �rea de args do exec */
	OFLAG		u_oflag;		/* Modo de abertura de arquivos */
	short		u_reser3;
	KFILE		*u_fileptr;		/* Ponteiro para KFILE (para I/O) */

	/*
	 *	Mem�ria compartilhada
	 */
	REGIONL		*u_regionlptr;		/* Ponteiro p/ 1a. procregion na tab. REGIONL */
	short		u_ueventno;		/* No. de uevents alocados p/ este proc. */
	short		u_usemano;		/* No. de usemas alocados p/ este proc. */
	short		u_shmemno;		/* No. total de shmem aloc. p/ este proc. */
	short		u_shmemnp;		/* No. total de p�ginas aloc. atrav�s de shmem */
	ulong		u_shmemvaddrmask;	/* Endere�os virtuais aloc. p/ shmem */

	/*
	 *	Tempos
	 */
	time_t		u_seqtime;		/* Tempo estimado do processamento sequencial */
	time_t		u_cseqtime;		/* Soma dos seqtime dos filhos */
	time_t		u_partime;		/* Tempo estimado de processamento paralelo */
	time_t		u_cpartime;		/* Maior partime dos filhos */

	/*
	 *	Informa��es da opera��o NFS
	 */
	struct u_nfs
	{
		LOCK		nfs_lock;		/* Tranca para a estrutura */
		EVENT		nfs_event;		/* Espera neste evento */
		signed char	nfs_status;		/* O estado da opera��o */
		char		nfs_error;		/* C�digo de erro */

		int		nfs_xid;		/* A identifica��o do pedido */
		const void	*nfs_sp;		/* O NFSSB */
		void		*nfs_bp;		/* O ITBLOCK */

		const void	*nfs_area;		/* O come�o e final da informa��o */
		const void	*nfs_end_area;

		int		nfs_transmitted;	/* Quantas vezes transmitido */
		time_t		nfs_last_snd_time;
		int		nfs_timeout;

		int		nfs_reser[1];

	}	u_nfs;

}	/* end struct uproc */;

/*
 ******	Tabela Hash *********************************************
 */
struct phashtb
{
	LOCK	h_lock;		/* semaforo da fila */
	char	h_reser[3];
	UPROC	*h_uproc;	/* ponteiro para a fila */
};

/*
 ******	C�lculo da entrada **************************************
 */
#define PHASH(x) (scb.y_phash + ((unsigned)(x) & scb.y_phmask))
