/*
 ****************************************************************
 *								*
 *			<sys/devmajor.h>			*
 *								*
 *    A parte mais significativa dos c�digos dos dispositivos	*
 *								*
 *	Vers�o	3.2.3, de 28.04.00				*
 *		4.8.0, de 05.10.05				*
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

#define	DEVMAJOR_H			/* Para definir os prot�tipos */

/*
 ****** Os c�digos **********************************************
 */
enum
{
	IDE_MAJOR,		/* Dispositivos IDE/ATAPI */
	FD_MAJOR,		/* Disquete */
	SD_MAJOR,		/* Controlador SCSI Adaptec 1542 */
	SC_MAJOR,		/* Controlador SCSI Adaptec 2940 */
	ZIP_MAJOR,		/* Disposito ZIP (porta paralela) */
	MD_MAJOR,		/* Meta-dispositivo para arquivos MS-DOS */
	RAMD_MAJOR,		/* Disco simulado na mem�ria */
	PSEUDO_MAJOR,		/* Disco simulado em um arquivo regular */
	UD_MAJOR,		/* Dispositivos de Massa USB */
	NFS_MAJOR,		/* Dispositivos NFS */

	CON_MAJOR = 16,		/* Console e videos (modo texto) */
	TTY_MAJOR,		/* Dispositivo indireto para o pr�prio terminal */
	MEM_MAJOR,		/* Mem�ria f�sica, do n�cleo, ... */
	SIO_MAJOR,		/* Linhas seriais */
	ITN_MAJOR,		/* Internet */
	PTYC_MAJOR,		/* Pseudo terminais clientes */
	PTYS_MAJOR,		/* Pseudo terminais sevidores */
	SLIP_MAJOR,		/* Linha serial com IP */
	LP_MAJOR,		/* Impressoras paralelas */
	ED_MAJOR,		/* Placa "ethernet" NE2000 */
	PPP_MAJOR,		/* Linha serial com PPP */
	XCON_MAJOR,		/* Console (interface para X-Window) */
	SB_MAJOR,		/* Sound Blaster 16 */
	RTL_MAJOR,		/* Placa "ethernet" RTL 8139 */
	PS2_MAJOR,		/* Camundongo PS2 */
	LIVE_MAJOR,		/* Sound Blaster Live */
	UMS_MAJOR,		/* Camundongo USB */
	ULP_MAJOR,		/* Impressora USB */
};

/*
 ******	O n�mero de dispositivos de cada classe *****************
 */
enum
{
	NSIO = 8		/* No. de linhas seriais */
};

/*
 ******	Outras defini��es ***************************************
 */
enum {	MD_SWAP_MINOR, MD_ROOT_MINOR, MD_HOME_MINOR };
