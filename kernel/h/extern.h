/*
 ****************************************************************
 *								*
 *			extern.h				*
 *								*
 *	Declara��o das v�ri�veis externas			*
 *								*
 *	Vers�o	3.0.0, de 30.08.94				*
 *		4.9.0, de 10.05.07				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */


/*
 ******	Vari�veis externas globais ******************************
 */
extern char		etext;			/* Final do texto */
extern char		end;			/* Final do BSS (Inicio da SYMTB) */
extern int		video_line;		/* Para controlar a tela cheia */
extern char		libt_nm[];		/* Nome da biblioteca "libt.o" */
extern int		nmount;			/* N�mero de dispositivos montados */
extern const char	lowertoupper[];		/* Tabela de convers�o ISO */
extern const char	uppertolower[];		/* Tabela de convers�o ISO */
extern const char	* const sys_errlist[];	/* Lista das mensagens de erro */
extern ulong		pl_mask[];		/* M�scara dos n�veis para interrup��es */
extern int		irq_pl_vec[];		/* N�veis definitivos dos IRQs */
extern char		CSW;			/* C�digo da depura��o (para ASM) */
extern const char	*file_code_name_vec[];	/* C�digos dos tipos de sistema de arquivos */
extern const int	sys_nerr;		/* O n�mero de mensagens de erro */
extern char		*domain_name;		/* Nome do domain */
extern const char	video_8x16_tb[];	/* A Fonte de caracteres 8x16 */
extern int		idle_intr_active;	/* Ativa as "l�mpadas" */

extern char		*dmesg_area;		/* �rea de mensagens */
extern char		*dmesg_ptr;
extern const char	*dmesg_end;

extern int		usb_busy;		/* Para verificar o uso */
extern int		usb_active;		/* Controladoras ativas */

enum SCREEN_SAVER_STATE { SCREEN_SAVER_IDLE, SCREEN_SAVER_ACTIVE };	/* Estado do protetor de tela */

extern enum SCREEN_SAVER_STATE	screen_saver_state;	/* Estado do protetor de tela */

/*
 ******	Vari�veis definidas no m�dulo "boot.s" ******************
 */
extern char		bootcode[];		/* Endere�o do c�digo do BOOT */
extern int		bcodesz;		/* Tamanho do c�digo do BOOT */

/*
 ******	Vari�veis definidas no m�dulo "dispat.c" ****************
 */
extern short		bestpri;		/* Prioridade da cabe�a da "corerdylist" */

/*
 ******	Vari�veis definidas no m�dulo "kinit.c" *****************
 */
extern char		fpu_present;		/* Inicializado no fpu.s */
extern int		tick_utime;		/* Tempo de um tick em microsegundos */
extern int		step_utime_16;		/* Tempo de uma contagem do PIT << 16 */
extern int		PIT_init;		/* Valor inicial do contador do PIT */

/*
 ******	Vari�veis definidas no m�dulo "main.c" ******************
 */
extern char		preemption_flag[];	 /* Habilita troca de proc. em modo SUP */

/*
 ******	Vari�veis definidas no m�dulo "clock.c" *****************
 */
extern int		hz;			/* Contador de interrup��es do rel�gio */
extern time_t		time;			/* Tempo em segundos desde o BIG BANG */
extern time_t		uptime;			/* Tempo em segundos desde o BOOT */
extern int		PIT_val_proc;		/* Valor do PIT pr�ximo ao final do */
						/* processamento da interrup��o do rel�gio */

/*
 ******	Vari�veis definidas no m�dulo "con.c" *******************
 */
extern const char	iso_to_pc_tb[];

/*
 ******	Vari�veis definidas no m�dulo "boot.s" *******************
 */
extern char		init_nm[];		/* Nome do INIT */

/*
 ******	Vari�veis definidas no m�dulo "excep.s" *****************
 */
extern void		syscall_vector ();

/*
 ******	Vari�veis definidas no m�dulo "start.s" *****************
 */
extern void		*end_base_bss;		/* Final da �rea baixa alocada */
extern void		*end_ext_bss;		/* Final da �rea alta alocada */
extern int		phys_mem;		/* Mem�ria f�sica total (KB) */
extern int		cputype;		/* Tipo da CPU */
#ifdef	UPROC_H
extern UPROC		*uproc_0;		/* Endere�o da PPDA do proc 0 */
#endif	UPROC_H

/*
 ******	Vari�veis utilizando defini��es de "bcb.h" **************
 */
#ifdef	BCB_H
extern BCB		bcb;			/* A estrutura herdada do BOOT */
#endif	BCB_H

#if (0)	/*******************************************************/
/*
 ******	Vari�veis utilizando defini��es de "bhead.h" ************
 */
#ifdef	BHEAD_H
extern BHEAD		*bclock;		/* Ponteiro do algoritmo do CLOCK */
#endif	BHEAD_H
#endif	/*******************************************************/

/*
 ******	Vari�veis utilizando defini��es de "disktb.h" ***********
 */
#ifdef	DISKTB_H
extern DISKTB		*disktb;		/* A tabela de discos */
extern DISKTB		*next_disktb;		/* A pr�xima entrada vaga da tabela */
extern DISKTB		*end_disktb;		/* O final da tabela de discos */
#endif	DISKTB_H

/*
 ******	Vari�veis utilizando defini��es de "inode.h" ************
 */
#ifdef	INODE_H
extern INODE		*rootdir;		/* Diretorio da RAIZ Universal */
extern INODE		*iclock;		/* INODE do Algoritmo do CLOCK */
extern	const FSTAB	fstab[];		/* Sistemas de arquivos */
#endif	INODE_H

/*
 ******	Vari�veis utilizando defini��es de "iotab.h" **********
 */
#ifdef	IOTAB_H
extern	const BIOTAB	biotab[];		/* Dispositivo de blocos */
extern	const CIOTAB	ciotab[];		/* Dispositivo de caracteres */
#endif	IOTAB_H

/*
 ******	Vari�veis utilizando defini��es de "ipc.h" ************
 */
#ifdef	IPC_H
extern LOCK		ueventllock;		/* Lista local de eventos */
extern LOCK		ueventglock;		/* Lista global de eventos */
extern LOCK		usemallock;		/* Lista local de sem�foros */
extern LOCK		usemaglock;		/* Lista global de sem�foros */
extern LOCK		regionllock;		/* Lista local de regi�es */
extern LOCK		regionglock;		/* Lista global de regi�es */
extern UEVENTG		*ueventgfreelist;	/* Lista livre de UEVENTG */
extern USEMAG		*usemagfreelist;	/* Lista livre de UEVENTG */
extern REGIONG		*regiongfreelist;	/* Lista livre de REGIONG */
extern int		regiong_list_count;	/* Contador de REGIONG usados */
#endif	IPC_H

/*
 ******	Vari�veis utilizando defini��es de "itnet.h" **********
 */
#ifdef	ITNET_H
extern ITSCB		itscb;			/* O bloco de contr�le */
extern const ETHADDR	ether_broadcast_addr;
extern EVENT		dns_server_table_not_empty_event;
#endif	ITNET_H

/*
 ******	Vari�veis utilizando defini��es de "kcntl.h" ************
 */
#ifdef	KCNTL_H
extern const PARTNM	partnm[];
#endif	KCNTL_H

/*
 ******	Vari�veis utilizando defini��es de "mmu.h" **************
 */
#ifdef	MMU_H
extern mmu_t		*kernel_page_directory;	 /* Diret�rio das tabela de pgs. */
extern mmu_t		*extra_page_table;	 /* Diret�rio das tabela de pgs. */
#endif	MMU_H

extern char		mmu_dirty[];		/* Indica que deve recarregar a MMU */

/*
 ******	Vari�veis utilizando defini��es de "sb.h" ***************
 */
#ifdef	SB_H
extern SB		sb_head;		/* Cabe�a da lista */
#endif	SB_H

/*
 ******	Vari�veis utilizando defini��es de "scb.h" **************
 */
#ifdef	SCB_H
extern SCB		scb;			/* O bloco de contr�le do sistema */
#endif	SCB_H

/*
 ******	Vari�veis utilizando defini��es de "sync.h" *************
 */
#ifdef	SYNC_H
extern LOCK		coremlock;		/* Lock da Tabela da Memoria */
extern LOCK		diskmlock;		/* Lock da Tabela do Disco */
extern EVENT		every_second_event;	/* Evento de segundo em segundo */
extern LOCK		iclocklock;		/* LOCK do algoritmo do CLOCK */
extern LOCK		sblistlock;		/* LOCK para a Lista de SB's */
extern LOCK		updlock;		/* LOCK de Opera��o de Update */
extern LOCK		corerdylist_lock;
extern EVENT		usb_explore_event;	/* Evento de explora��o do USB */
#endif	SYNC_H

/*
 ******	Vari�veis utilizando defini��es de "sysent.h" ***********
 */
#ifdef	SYSENT_H
extern const SYSENT	sysent[];		/* Tabela de chamadas ao sistema */
#endif	SYSENT_H

/*
 ******	Vari�veis utilizando defini��es de "seg.h" **************
 */
#ifdef	SEG_H
extern EXCEP_DC		gdt[];			/* A tabela GDT */
#endif	SEG_H

/*
 ******	Vari�veis utilizando defini��es de "tty.h" **************
 */
#ifdef	TTY_H
extern int		TTYMAXQ;		/* Limite para parar o processo */
extern int		TTYMINQ;		/* Limite para reiniciar o processo */
extern int		TTYPANIC;		/* Limite para abandonar toda a fila */
extern int		TTYCOMMPANIC;		/* Idem, para o modo de comunica��es */

extern LOCK		cfreelock;		/* Lock da Lista livre */
extern CBLK		*cfreelist;		/* Comeco da lista Livre */
extern ushort		chartb[];
extern char		isotoisotb[];		/* Tabelas de convers�o */
extern char		isotoatb[];
extern char		isotou1tb[];
extern char		isotou2tb[];

extern TTY		*kernel_pty_tp;		/* Para enviar mensagens do KERNEL */
#endif	TTY_H

/*
 ******	Vari�veis utilizando defini��es de "uproc.h" **************
 */
#ifdef	UPROC_H
extern UPROC		u;			/* A extens�o da tabela de processos */
extern UPROC		*corerdylist;		/* Cabeca da corerdylist */
extern UPROCV		*uprocfreelist;		/* Lista das Entradas UPROC n�o usadas */
extern LOCK		uprocfreelist_lock;
#endif	UPROC_H

/*
 ******	Vari�veis utilizando defini��es de "utsname.h" **********
 */
#ifdef	UTSNAME_H
extern UTSNAME		uts;			/* A estrutura de identifica��o do sistema */
#endif	UTSNAME_H

/*
 ******	Vari�veis utilizando defini��es de "video.h" ************
 */
#ifdef	VIDEO_H
extern VIDEODATA	*video_data;		/* A tabela de video */
extern VIDEODISPLAY	*curr_video_display;
#endif	VIDEO_H

/*
 ******	Vari�veis utilizando defini��es de "mon.h" **************
 */
#ifdef	MON_H
extern MON		mon;			/* A estrutura de monitora��o */
#endif	MON_H
