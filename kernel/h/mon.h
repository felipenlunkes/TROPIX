/*
 ****************************************************************
 *								*
 *			<sys/mon.h>				*
 *								*
 *	Bloco de monitora��o					*
 *								*
 *	Vers�o	3.0.0, de 01.12.94				*
 *		4.6.0, de 17.06.04				*
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

#define	MON_H			/* Para definir os prot�tipos */

/*
 ******	A estrutura *********************************************
 */
struct	mon
{
	/*
	 *	Informa��es sobre o uso das CPUs
	 */
	int	y_ticks[NCPU];	/* No. de ticks do rel�gio */
	int	y_stop[NCPU];	/* No. de stops de idle */

	/*
	 *	Informa��es sobre o uso dos discos IDE + SCSI
	 */
	int	y_sasi;		/* No. de ticks do rel�gio */

	/*
	 *	Informa��es sobre ETHERNET
	 */
	int	y_ed;

	/*
	 *	Informa��es sobre o PPP
	 */
	int	y_ppp_in;
	int	y_ppp_out;

	/*
	 *	Informa��es sobre os blocos
	 */
	int	y_block_full_cnt;
	int	y_block_dirty_cnt;

	int	y_block_lru_total;	/* Estat�sticas da LRU */
	int	y_block_lru_hit;
	int	y_block_lru_miss;

	/*
	 *	Informa��es sobre os INODEs
	 */
	int	y_inode_in_use_cnt;
	int	y_inode_dirty_cnt;

	/*
	 *	Informa��es sobre os KFILEs
	 */
	int	y_kfile_in_use_cnt;

	/*
	 *	Informa��es sobre o USB
	 */
	int	y_usb;		/* No. de ticks do rel�gio */

	/*
	 *	Reserva
	 */
	int	y_res[22];	/* Reservado para uso futuro */
};
