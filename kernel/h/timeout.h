/*
 ****************************************************************
 *								*
 *			<sys/timeout.h>				*
 *								*
 *	Estrutura da Tabela TIMEOUT				*
 *								*
 *	Vers�o	3.0.0, de 07.09.94				*
 *		3.2.3, de 23.10.99				*
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

#define	TIMEOUT_H		/* Para definir os prot�tipos */

/*
 ******	A Entrada ***********************************************
 */
typedef struct timeout	TIMEOUT;

struct timeout
{
	ulong	o_time;		/* Tempo absoluto em "ticks" */
	void	(*o_func) (int); /* Rotina a ser chamada */
	int	o_arg;		/* Argumento */
	TIMEOUT	*o_next;	/* Ponteiro para a pr�xima entrada */
};

#define	NOTIMEOUT (TIMEOUT *)NULL

/*
 ******	A entrada da fila "hash" do timeout *********************
 */
typedef struct
{
	LOCK	o_lock;		/* Spinlock de cada fila */
	ushort	o_count;	/* Contador (para depura��o) */
	TIMEOUT	*o_first;	/* Ponteiro para o in�cio da fila */

}	TIMEOUT_HASH;

#define TIMEOUT_HASH_SZ	64	/* Naturalmente pot�ncia de 2 */
