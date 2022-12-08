/*
 ****************************************************************
 *								*
 *			<sys/ioctl.h>				*
 *								*
 *	C�digos do IOCTL dos diversos dispositivos		*
 *	(exceto linhas de comunica��es)				*
 *								*
 *	Vers�o	3.0.0, de 15.12.94				*
 *		3.4.5, de 24.12.03				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	IOCTL_H			/* Para definir os prot�tipos */

/*
 ****************************************************************
 *	C�digos Universais (aplic�veis a qualquer dispositivo)	*
 ****************************************************************
 */
#define	U_ATTENTION		(('U' << 8) | 0)
#define	U_UNATTENTION		(('U' << 8) | 1)

/*
 ****************************************************************
 *	C�digos de fita magn�tica				*
 ****************************************************************
 */
#define	MTISATAPE		(('M' << 8) | 0)

/*
 ****************************************************************
 *	C�digos de disco					*
 ****************************************************************
 */
#define	DKISADISK		(('D' << 8) | 0)
#define	DKFORMAT		(('D' << 8) | 1)

#define	FD_GET_TYPE_TB		(('D' << 8) | 2)
#define	FD_PUT_FORMAT_TYPE	(('D' << 8) | 3)

#define	ZIP_GET_PROTECTION	(('D' << 8) | 4)
#define	ZIP_SET_PROTECTION	(('D' << 8) | 5)
#define	ZIP_START_STOP		(('D' << 8) | 6)
#define	ZIP_LOCK_UNLOCK		(('D' << 8) | 7)
#define	ZIP_IS_ZIP		(('D' << 8) | 8)

/*
 ****************************************************************
 *	C�digos do dispositivo "xconsole"			*
 ****************************************************************
 */
#define	XC_BEEP			(('X' << 8) | 0)
#define	XC_SETLEDS		(('X' << 8) | 1)

/*
 ****************************************************************
 *	C�digos do dispositivo "sb"				*
 ****************************************************************
 */
#define	SB_READ_MIXER		(('S' << 8) | 0)
#define	SB_WRITE_MIXER		(('S' << 8) | 1)
#define	SB_GET_MODE		(('S' << 8) | 2)
#define	SB_SET_MODE		(('S' << 8) | 3)
