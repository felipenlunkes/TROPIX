/*
 ****************************************************************
 *								*
 *			<sys/utsname.h>				*
 *								*
 *	Estrutura de identifica��o do sistema 			*
 *								*
 *	Vers�o	3.0.0, de 29.08.94				*
 *		3.0.0, de 29.08.94				*
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

#define	UTSNAME_H		/* Para definir os prot�tipos */

/*
 ******	A estrutura *********************************************
 */
typedef	struct	utsname	UTSNAME;

struct	utsname
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
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern int	uname (UTSNAME *);
