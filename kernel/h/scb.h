/*
 ****************************************************************
 *								*
 *			<sys/scb.h>				*
 *								*
 *	System Control Block: 					*
 *	    Contem os par�metros atuais do sistema		*
 *								*
 *	Vers�o	3.0.0, de 01.09.94				*
 *		4.8.0, de 08.09.05				*
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

#define	SCB_H			/* Para definir os prot�tipos */

/*
 ******	A estrutura *********************************************
 */
struct	scb
{
	/*
	 *	Informa��es sobre as CPUs
	 */
	long	y_cputype;	/* Tipo da CPU (386, 486 ou 586) */
	int	y_ncpu;		/* No. de CPUs ativas */
	long	y_initpid;	/* Pid do INIT */

	/*
	 *	Tabela de processos
	 */
	UPROCV	*y_uproc;	/* In�cio da tabela */
	UPROCV	*y_lastuproc;	/* �ltima entrada usada */
	UPROCV	*y_enduproc;	/* Final da tabela */
	int	y_nproc;	/* No. de entradas */

	/*
	 *	Tabela de HASH dos processos
	 */
	PHASHTB	*y_phash;	/* In�cio da tabela */
	PHASHTB	*y_endphash;	/* Final da tabela */
	int	y_nphash;	/* No. de entradas */
	int	y_phmask;	/* M�scara para o c�lculo do hash */

	/*
	 *	Tabela de INODEs
	 */
	INODE	*y_inode;	/* Come�o da tabela */
	INODE	*y_endinode;	/* Final da tabela */
	int	y_ninode;	/* No. de entradas */

	/*
	 *	Tabela de HASH dos INODEs
	 */
	IHASHTB	*y_ihash;	/* In�cio da tabela */
	IHASHTB	*y_endihash;	/* Final da tabela */
	int	y_nihash;	/* No. de entradas */

	/*
	 *	Tabela de BUFHEADs e BUFFERs 
	 */
	BHEAD	*y_bhead;	/* In�cio dos BHEADs */
	BHEAD	*y_endbhead;	/* Final  dos BHEADs */
	char	*y_buf0;	/* In�cio do buffers 0 */
	char	*y_endbuf0;	/* Final do buffers 0 */
	char	*y_buf1;	/* In�cio do buffers 1 */
	char	*y_endbuf1;	/* Final do buffers 1 */
	int	y_nbuf;		/* No. de BUFFERs    */

	/*
	 *	Tabela de HASH dos BHEADs
	 */
	BHASHTB	*y_bhash;	/* In�cio da tabela */
	BHASHTB	*y_endbhash;	/* Final da tabela */
	int	y_nbhash;	/* No. de entradas */

	/*
	 *	Tabela de KFILEs
	 */
	KFILE	*y_kfile;	/* Come�o da tabela */
	KFILE	*y_endkfile;	/* Final da tabela */
	int	y_nkfile;	/* No. de entradas */

	/*
	 *	Tabela de CLISTs
	 */
	CBLK	*y_clist;	/* Come�o da tabela */
	CBLK	*y_endclist;	/* Final da tabela */
	int	y_nclist;	/* No. de entradas */

	/*
	 *	Tabela de aloca��o da mem�ria interna & disco (swap)
	 */
	MAP	*y_map;		/* In�cio da MAP */
	MAP	*y_endmap;	/* Final  da MAP */
	int	y_nmap;		/* No. de entradas */

	/*
	 *	Tabela de HASH dos s�mbolos das bibliotecas compartilhadas
	 */
	void	*y_shlib_hash;	/* In�cio da SHLIB_HASH */
	void	*y_end_shlib_hash; /* Final da SHLIB_HASH */
	int	y_n_shlib_hash;	/* No. de entrada da SHLIB_HASH */

	/*
	 *	Tabela de TIMEOUT
	 */
	TIMEOUT	*y_timeout;	/* In�cio da tabela */ 
	TIMEOUT	*y_endtimeout;	/* Final da tabela */
	int	y_ntout;	/* No. de entradas por CPU */

	/*
	 *	Tabela de LOCKF
	 */
	LOCKF	*y_lockf;	/* In�cio da tabela */ 
	LOCKF	*y_endlockf;	/* Final da tabela */
	int	y_nlockf;	/* No. de entradas */

	/*
	 *	Tabela de UEVENTLs
	 */
	UEVENTL	*y_ueventl;	/* Come�o da tabela */
	UEVENTL	*y_endueventl;	/* Final da tabela */
	int	y_nueventl;	/* No. de entradas */

	/*
	 *	Tabela de UEVENTs
	 */
	UEVENTG	*y_ueventg;	/* Come�o da tabela */
	UEVENTG	*y_endueventg;	/* Final da tabela */
	int	y_nueventg;	/* No. de entradas */

	/*
	 *	Tabela de USEMALs
	 */
	USEMAL	*y_usemal;	/* Come�o da tabela */
	USEMAL	*y_endusemal;	/* Final da tabela */
	int	y_nusemal;	/* No. de entradas */

	/*
	 *	Tabela de USEMAGs
	 */
	USEMAG	*y_usemag;	/* Come�o da tabela */
	USEMAG	*y_endusemag;	/* Final da tabela */
	int	y_nusemag;	/* No. de entradas */

	/*
	 *	Tabela de REGIONLs
	 */
	REGIONL	*y_regionl;	/* Come�o da tabela */
	REGIONL	*y_endregionl;	/* Final da tabela */
	int	y_nregionl;	/* No. de entradas */

	/*
	 *	Tabela de REGIONGs
	 */
	REGIONG	*y_regiong;	/* Come�o da tabela */
	REGIONG	*y_endregiong;	/* Final da tabela */
	int	y_nregiong;	/* No. de entradas */

	/*
	 *	Tabela do DOMAIN NAME SYSTEM
	 */
	DNS	*y_dns;		/* Come�o da tabela */
	DNS	*y_end_dns;	/* Final da tabela */
	int	y_n_dns;	/* No. de entradas */

	/*
	 *	Tabela de Roteamento da INTERNET
	 */
	ROUTE	*y_route;	/* Come�o da tabela */
	ROUTE	*y_end_route;	/* Final da tabela */
	int	y_n_route;	/* No. de entradas */

	/*
	 *	Tabela de endere�os ETHERNET
	 */
	ETHER	*y_ether;	/* Come�o da tabela */
	ETHER	*y_end_ether;	/* Final da tabela */
	int	y_n_ether;	/* No. de entradas */
	ETHER	*y_ether_first;	/* Come�o da lista */

	/*
	 *	Tabela de blocos para datagramas da INTERNET
	 */
	ITBLOCK	*y_itblock;	/* Come�o da tabela */
	ITBLOCK	*y_end_itblock;	/* Final da tabela */
	int	y_n_itblock;	/* No. de entradas */

	/*
	 *	ENDPOINTs RAW da INTERNET
	 */
	RAW_EP	*y_raw_ep;	/* Come�o da tabela */
	RAW_EP	*y_end_raw_ep;	/* Final da tabela */
	int	y_n_raw_ep;	/* No. de entradas */

	/*
	 *	ENDPOINTs UDP da INTERNET
	 */
	UDP_EP	*y_udp_ep;	/* Come�o da tabela */
	UDP_EP	*y_end_udp_ep;	/* Final da tabela */
	int	y_n_udp_ep;	/* No. de entradas */

	/*
	 *	ENDPOINTs TCP da INTERNET
	 */
	TCP_EP	*y_tcp_ep;	/* Come�o da tabela */
	TCP_EP	*y_end_tcp_ep;	/* Final da tabela */
	int	y_n_tcp_ep;	/* No. de entradas */

	/*
	 *	Tabela de Pseudo Terminais
	 */
	PTY	*y_pty;		/* Come�o da tabela */
	PTY	*y_end_pty;	/* Final da tabela */
	int	y_npty;		/* No. de entradas */

	/*
	 *	Tabela do EXPORT
	 */
	EXPORT	*y_export;	/* Come�o da tabela */
	EXPORT	*y_end_export;	/* Final da tabela */
	int	y_n_export;	/* No. de entradas */

	/*
	 *	Reserva para novas tabelas
	 */
	int	y_tb_res[8*3];	/* Para cada TB 3 ints */

	/*
	 *	Come�o e final das tabelas
	 */
	void	*y_tb0;		/* In�cio das tabelas 0 */
	void	*y_endtb0;	/* Final  das tabelas 0 */
	void	*y_tb1;		/* In�cio das tabelas 1 */
	void	*y_endtb1;	/* Final  das tabelas 1 */

	/*
	 *	Defini��o dos dispositivos
	 */
	dev_t	y_rootdev;	/* Dispositivo do ROOT */
	dev_t	y_pipedev;	/* Dispositivo do PIPE */
	dev_t	y_swapdev;	/* Dispositivo do SWAP */

	char	y_sh_nm[32];	/* Nome da "sh" */

	/*
	 *	Vari�veis globais do SWAP
	 */
	daddr_t	y_swaplow;	/* Bloco Inicial do SWAP */
	int	y_nswap;	/* Tamanho em Blocos do SWAP */

	/*
	 *	No. de unidades f�sicas
	 */
	int	y_nblkdev;	/* No. de BLK */
	int	y_nchrdev;	/* No. de CHR */

	/*
	 *	Superblocos
	 */
	V7SB	*y_rootsb;	/* In�cio da Lista de SBs */
	int	y_nmount;	/* No. maximo de MOUNTs */

	/*
	 *	Mem�ria f�sica
	 */
	void	*y_endpmem;	/* Final da mem�ria f�sica */

	/*
	 *	Come�o e final da mem�ria para os processos (P�GINAS)
	 */
	pg_t	y_ucore0;	/* In�cio da Mem�ria 0 */
	pg_t	y_enducore0;	/* Final  da Mem�ria 0 */
	pg_t	y_ucore1;	/* In�cio da Mem�ria 1 */
	pg_t	y_enducore1;	/* Final  da Mem�ria 1 */

	/*
	 *	Come�o e final dos discos em mem�ria
	 */
	void	*y_ramd0;	/* In�cio do disco */
	void	*y_endramd0;	/* Final  do disco */
	long	y_ramd0sz;	/* No. de bytes do RAM disk */

	void	*y_ramd1;	/* In�cio do disco */
	void	*y_endramd1;	/* Final  do disco */
	long	y_ramd1sz;	/* No. de bytes do RAM disk */

	/*
	 *	Parametros de tempo
	 */
	int	y_hz;		/* Freq��ncia (ticks por segundo) */

	/*
	 *	Par�metros do SCHEDULER
	 */
	int	y_tslice;	/* Time-slice em ticks do rel�gio */
	int	y_incpri;	/* Incremento da prioridade a cada tick */
	int	y_decpri;	/* Decremento da prioridade a cada tick */
	int	y_ttyinc;	/* Incremento para entrada de TTY */
	int	y_nfactor;	/* Influ�ncia do NICE */
	int	y_reser1[4];

	/*
	 *	Par�metros dos processos do usu�rio
	 */
	int	y_maxppu;	/* No. m�ximo de proc. por usu�rio */
	pg_t	y_maxpsz;	/* Tamanho m�ximo de um Proc. de usu�rio */
	int	y_umask;	/* Mascara de cria��o de arquivos */
	long	y_stksz;	/* Tamanho inicial da stack (bytes) */
	long	y_stkincr;	/* Incremento da stack (bytes) */
	int	y_ncexec;	/* No. max. de chars. do Exec */

	/*
	 *	Outros parametros
	 */
	int	y_pgsz;		/* Tamanho (em bytes) da PG */
	void	*y_idle_pattern; /* Tabela de padr�o para IDLE */
	void	*y_intr_pattern; /* Tabela de padr�o para INTR */
	char	y_preemption_mask[8];	/* Troca de proc. em modo SUP */

	/*
	 *	Par�metros da atualiza��o do "cache" dos dispositivos
	 */
	int	y_sync_time;	/* Per�odo de atualiza��o de SB e INODEs */
	int	y_block_time;	/* Per�odo de atualiza��o de blocos */
	int	y_dirty_time;	/* Tempo limite para atualizar um bloco */
	int	y_max_flush;	/* No. m�ximo de blocos atualizados por ciclo */

	/*
	 *	Tabela de Portas/interrup��es das linhas seriais 
	 */
	ushort	y_sio_port[8];	/* No. das portas */
	char	y_sio_irq[8];	/* No. dos IRQs */

	/*
	 *	Tabela de Portas/interrup��es das sa�das paralelas
	 */
	ushort	y_lp_port[4];	/* No. das portas */
	char	y_lp_irq[4];	/* No. dos IRQs */

	/*
	 *	Tabela de Portas/interrup��es das unidades 3Com 503
	 */
	ushort	y_ed_port[4];	/* No. das portas */
	char	y_ed_irq[4];	/* No. dos IRQs */

	/*
	 *	Estrutura UTSNAME: Informa��es sobre o systema
	 */
	struct	uts
	{
		char	uts_sysname[16];	/* Nome do sistema */
		char	uts_systype[16];	/* Tipo do sistema */
		char	uts_nodename[16];	/* Nome do n� */
		char	uts_version[16];	/* Vers�o */
		char	uts_date[16];		/* Data */
		char	uts_time[16];		/* Tempo */
		char	uts_machine[16];	/* Computador */
		char	uts_customer[16];	/* Nome do cliente */
		char	uts_depto[16];		/* Nome do departamento */
		char	uts_sysserno[16];	/* Numero de s�rie do sistema */
		char	uts_res[4][16];		/* Reservado para uso futuro */

	}	y_uts;

	/*
	 *	Vari�veis diversas
	 */
	char	y_std_boot;		/* Usa o "boot" sem alterar nada */
	char	y_fpu_enabled;		/* Unidade de ponto flutuante ativada */
	char	y_CSW;			/* Para DEBUG */
	char	y_ut_clock;		/* O rel�gio CMOS � UT (GMT) */

	int	y_tzmin;		/* Fuso hor�rio, em minutos */
	int	y_screen_saver_time;	/* Tempo do protetor de tela */
	int	y_DELAY_value;		/* Para 1 micro-segundo */

	char	y_boot_verbose;		/* Escreve informa��es sobre o BOOT */
	char	y_ignore_LEDs;		/* N�o atualiza os LEDs do teclado */
	char	y_keyboard;		/* Tipo do teclado => 0: US, 1: ABNT2 */
	char	y_tagenable;		/* Permite o uso de "tag queueing" */

	char	y_dma_enable;		/* Permite o uso de DMA em dispositivos ATA */
	char	y_n_nfs_daemon;		/* N�mero de "daemon"s do servidor NFS */

	char	y_reser2[2];

	int	y_dmesg_sz;		/* Tamanho da �rea para "dmesg" (printf) */

	/*
	 *	Tabela de controladores USB
	 */
	char	y_usb_enable[16];	/* Habilita/desabilita cada controladora */

	/*
	 *	Semi constantes do sistema
	 */
	off_t	y_SYS_ADDR;		/* Endere�o virtual do in�cio do n�cleo */
	off_t	y_UPROC_ADDR;		/* Endere�o virtual do in�cio da UPROC */

	off_t	y_USER_TEXT_ADDR;	/* Endere�o virtual recomendado para in�cio do texto do usu�rio */
	off_t	y_USER_DATA_ADDR;	/* Endere�o virtual recomendado para in�cio do texto do usu�rio */

	pg_t	y_USIZE;		/* Tamanho (em pgs) da UPROC */

	int	y_NUFILE;		/* No. max. de arq. abertos por processo */

	int	y_NCON;			/* No. de consoles virtuais */
	int	y_NSIO;			/* No. de linhas seriais */

	/*
	 *	Reserva para completar 1536 bytes
	 */
	int	y_etc_res[125];
};
