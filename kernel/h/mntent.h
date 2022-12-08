/*
 ****************************************************************
 *								*
 *			<sys/mntent.h>				*
 *								*
 *	Par�metros de montagem de systemas de arquivos		*
 *								*
 *	Vers�o	4.8.0, de 27.09.05				*
 *		4.8.0, de 27.09.05				*
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

#define	MNTENT_H		/* Para definir os prot�tipos */

/*
 ****** Estrutura com as op��es de montagem *********************
 */
struct mntent
{
	int	me_flags;		/* Indicadores: veja abaixo */
	int	me_uid, me_gid;		/* Usu�rio e Grupo */

	/* V�rios par�metros para NFS */

	long	me_server_addr;		/* Endere�o IP do servidor */
	int	me_rsize;		/* Tamanho de leitura */
	int	me_wsize;		/* Tamanho de escrita */
	int	me_timeout;		/* Tempo para retransmiss�o */
	int	me_retrans;		/* No. de retransmiss�es */
	int	me_port;		/* No. da porta */
	int	me_nfsvers;		/* Vers�o do protocolo NFS */

	int	me_reser[6];		/* Reserva para 64 bytes */
};

/*
 ****** Os valores de "me_flags" ********************************
 */
enum
{
	SB_RONLY	= (1 <<  0),	/* O FS � READONLY */
	SB_USER		= (1 <<  1),	/* Pode ser montado por usu�rios regulares */
	SB_ATIME	= (1 <<  2),	/* Atualiza os tempos de acesso */ 
	SB_DEV		= (1 <<  3),	/* Interpreta os dispositivos */ 
	SB_EXEC		= (1 <<  4),	/* Executa programas */ 
	SB_SUID		= (1 <<  5),	/* Interpreta os indicadores SUID/SGID */ 
	SB_EJECT	= (1 <<  6),	/* Ejeta ap�s a desmontagem */ 
	SB_CASE		= (1 <<  7),	/* A "caixa alta/baixa" importa nos nomes */ 
	SB_ROCK		= (1 <<  8),	/* Usar a extens�o "Rock Ridge", se presente */ 
	SB_JOLIET	= (1 <<  9),	/* Usar a extens�o "Joliet", se presente */ 
	SB_LFN		= (1 << 10),	/* L�/escreve com "long file names" */ 
	SB_HARD		= (1 << 11),	/* Montagem "soft/hard" para NFS */ 

	SB_AUTO		= (1 << 29),	/* Monta com "mount -a" */
	SB_FSCK		= (1 << 30)	/* Verifica o sistema de arquivos */

	/* N�o usar o bit 31 para evitar n�meros negativos */
};

/*
 ****** Os valores de "default" *********************************
 */
enum {	SB_DEFAULT_ON	= (SB_DEV|SB_EXEC|SB_SUID|SB_CASE|SB_ROCK|SB_JOLIET|SB_LFN|SB_AUTO) };

enum {	SB_NOT_KERNEL	= (SB_AUTO|SB_FSCK) };

enum {	SB_RSIZE = 1024, SB_WSIZE = 1024, SB_TIMEOUT = 1, SB_RETRANS = 8, SB_PORT = 2049, SB_NFSVERS = 2 };
