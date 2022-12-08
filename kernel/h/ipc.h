/*
 ****************************************************************
 *								*
 *			<sys/ipc.h>				*
 *								*
 *	Tabelas de eventos e sem�foros do usu�rio		*
 *								*
 *	Vers�o	3.0.0, de 07.09.94				*
 *		3.0.0, de 07.09.94				*
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

#define	IPC_H			/* Para definir os prot�tipos */

/*
 ******	Formato das estruturas **********************************
 */
struct	ueventl
{
	UEVENTG	*uel_uevent;	/* Ponteiro para o evento global */
};

struct	ueventg
{
	EVENT	ueg_event;	/* Evento propriamente dito */
	char	ueg_reser;
	short	ueg_eventid;	/* Identifica��o do evento */
	long	ueg_count;	/* Contador de ocorr�ncias */
	UEVENTG	*ueg_next;	/* Pr�ximo evento associado */
};

struct	usemal
{
	USEMAG	*usl_usema;	/* Ponteiro para o sem�foro global */
	short	usl_count;	/* Contador de recursos alocados */
	short	usl_reser;
};

struct	usemag
{
	SEMA	usg_sema;	/* Sem�foro propriamente dito */
	short	usg_semaid;	/* Identifica��o do sem�foro */
	short	usg_reser;
	USEMAG	*usg_next;	/* Pr�ximo sem�foro associado */
};

/*
 ******	Modos de a��o do "ueventctl" e "usemactl" ***************
 */
typedef enum
{
	UE_ALLOC,	/* Aloca UEVENTLs */
	UE_GET		/* Obt�m o descritor de um UEVENTL*/

}	UEVENTCTLFUNC;

typedef enum
{
	US_ALLOC,	/* Aloca USEMALs */
	US_GET,		/* Obt�m o descritor de um USEMAL */
	US_AVAIL,	/* No. de recursos ainda dispon�veis */
	US_WAIT		/* No. de threads/procs esperando pelo sem. */

}	USEMACTLFUNC;
