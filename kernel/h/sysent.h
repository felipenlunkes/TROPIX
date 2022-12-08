/*
 ****************************************************************
 *								*
 *			<sys/sysent.h>				*
 *								*
 *	Defini��es da tabela de chamadas ao sistema		*
 *								*
 *	Vers�o	3.0.0, de 11.12.94				*
 *		3.0.0, de 11.12.94				*
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

#define	SYSENT_H		/* Para definir os prot�tipos */

/*
 ******	Defini��o da estrutura **********************************
 */
typedef struct sysent
{
	int	(*s_syscall) (); /* Fun��o executora */
	int	s_narg;		/* No. de argumentos da chamada */

}	SYSENT;
