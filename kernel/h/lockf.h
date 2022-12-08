/*
 ****************************************************************
 *								*
 *			<sys/lockf.h>				*
 *								*
 *	Tabela de LOCKs de regi�es de arquivos			*
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

#define	LOCKF_H			/* Para definir os prot�tipos */

/*
 ******	Formato da estrutura ************************************
 */
struct lockf
{
	EVENT	k_free;		/* Evento de libera��o do LOCK */
	char	k_reser[3];	/* o EVENT � o primeiro membro da estrutura */

	UPROC	*k_uproc;	/* Processo dono do LOCK */

	off_t	k_begin;	/* In�cio da regi�o */
	off_t	k_end;		/* Final da regi�o */

	LOCKF	*k_next;	/* Pr�ximo LOCK */
};

/*
 ******	Modos de a��o do LOCKF **********************************
 */
typedef enum
{
	F_ULOCK,	/* Libera */
	F_LOCK,		/* Lock com espera */
	F_TLOCK,	/* Lock com retorno de erro */
	F_TEST		/* Apenas consulta */

}	LOCKFMODE;
