/*
 ****************************************************************
 *								*
 *			<sys/uerror.h>				*
 *								*
 *	C�digo dos erros do usu�rio				*
 *								*
 *	Vers�o	3.0.0, de 05.10.94				*
 *		4.8.0, de 23.10.05				*
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

#define	UERROR_H		/* Para definir os prot�tipos */

/*
 ****************************************************************
 *	C�digos de erros					*
 ****************************************************************
 */
typedef	enum
{
	/* 00: */ NOERR,		/* Erro ZERO */
	/* 01: */ EPERM,		/* N�o � o dono ou superusu�rio */
	/* 02: */ ENOENT,		/* Nome de arquivo desconhecido */
	/* 03: */ ESRCH,		/* N�mero de processo desconhecido */
	/* 04: */ EINTR,		/* Chamada ao sistema interrompida */
	/* 05: */ EIO,			/* Erro de entrada/sa�da */
	/* 06: */ ENXIO,		/* Dispositivo desconhecido ou endere�o fora dos limites */
	/* 07: */ E2BIG,		/* Lista de argumentos longa demais */
	/* 08: */ ENOEXEC,		/* Arquivo n�o-execut�vel */
	/* 09: */ EBADF,		/* Descritor de arquivo inv�lido */
	/* 10: */ ECHILD,		/* O Processo n�o possui filhos */
	/* 11: */ EAGAIN,		/* Recurso n�o dispon�vel, tente mais tarde */
	/* 12: */ ENOMEM,		/* Mem�ria insuficiente */
	/* 13: */ EACCES,		/* Permiss�o negada */
	/* 14: */ EFAULT,		/* Endere�o inv�lido de mem�ria */
	/* 15: */ ENOTBLK,		/* Este dispositivo n�o � de blocos */
	/* 16: */ EBUSY,		/* Recurso ocupado */
	/* 17: */ EEXIST,		/* O arquivo j� existe */
	/* 18: */ EXDEV,		/* Elo atrav�s de sistema de arquivos */
	/* 19: */ ENODEV,		/* Dispositivo inexistente */
	/* 20: */ ENOTDIR,		/* N�o � um diret�rio */
	/* 21: */ EISDIR,		/* � um diret�rio */
	/* 22: */ EINVAL,		/* Argumento ou opera��o inv�lido */
	/* 23: */ ENFILE,		/* Tabela FILE cheia */
	/* 24: */ EMFILE,		/* Arquivos abertos demais */
	/* 25: */ ENOTTY,		/* O dispositivo n�o � de caracteres */
	/* 26: */ ETXTBSY,		/* Texto ocupado */
	/* 27: */ EFBIG,		/* Arquivo excessivamente grande */
	/* 28: */ ENOSPC,		/* Sistema de arquivos cheio */
	/* 29: */ ESPIPE,		/* \"Seek\" em PIPE ou FIFO */
	/* 30: */ EROFS, 		/* Prote��o de escrita */
	/* 31: */ EMLINK,		/* N�mero excessivo de elos f�sicos */
	/* 32: */ EPIPE,		/* PIPE sem leitor */
	/* 33: */ EDOM,			/* Argumento fora dos limites */
	/* 34: */ ERANGE,		/* Resultado fora dos limites */
	/* 35: */ EDEADLK,		/* Foi evitado um \"deadlock\" */
	/* 36: */ ENOLCK,		/* Tabela de \"locks\" cheia */
	/* 37: */ EOLINE,		/* Dispositivo n�o pronto */
	/* 38: */ EPFULL,		/* FIFO Cheio */
	/* 39: */ ENOTFS,		/* Este dispositivo n�o contem um sistema de arquivos */
	/* 40: */ EOLDVER,		/* Referenciando biblioteca compartilhada antiga */
	/* 41: */ ENOTMNT,		/* Dispositivo n�o montado */
	/* 42: */ ETIMEOUT,		/* Tempo de espera esgotado */
	/* 43: */ ENOTREG,		/* N�o � um arquivo regular */
	/* 44: */ EBADFMT,		/* Formato inv�lido */
	/* 45: */ ENOSHLIB,		/* Biblioteca compartilhada n�o carregada */
	/* 46: */ ELOOP,		/* Aninhamento excessivo de elos simb�licos */
	/* 63: */ ENAMETOOLONG = 63,	/* Nome excessivamente comprido */
	/* 66: */ ENOTEMPTY = 66,	/* Diret�rio n�o vazio */
	/* 69: */ EDQUOT = 69,		/* Quota de disco excedida */
	/* 70: */ ESTALE, 		/* Refer�ncia n�o mais v�lida a arquivo remoto */
	/* 71: */ EREMOTE, 		/* N�vel excessivo de refer�ncias remotas em um caminho */

	/* 72: */ TBADNET,		/* Rede n�o inicializada */
	/* 73: */ TUNKNET,		/* Nome/endere�o de rede desconhecido */
	/* 74: */ TBADADDR,		/* Erro no formato do endere�o */
	/* 75: */ TADDRBUSY,		/* Endere�o j� sendo utilizado */
	/* 76: */ TNOADDR,		/* N�o consegui alocar o endere�o */
	/* 77: */ TBADOPT,		/* Informa��es das op��es inv�lidas */
	/* 78: */ TBADDATA,		/* Informa��es do dado inv�lidas */
	/* 79: */ TNODATA,		/* Ainda n�o h� dados dispon�veis */
	/* 80: */ TBADSEQ,		/* N�mero de seq��ncia inv�lido */
	/* 81: */ TBADQLEN,		/* Tamanho de fila inv�lido */
	/* 82: */ TBADFLAG,		/* Indicadores inv�lidos */
	/* 83: */ TNODIS,		/* N�o h� pedido de desconex�o abortiva */
	/* 84: */ TNOREL,		/* N�o h� pedido de desconex�o ordenada */
	/* 85: */ TBUFOVFLW,		/* Mensagem maior do que a �rea dispon�vel */
	/* 86: */ TOUTSTATE,		/* Estado inv�lido */
	/* 87: */ TLOOK,		/* Evento ocorrido exige aten��o */
	/* 88: */ TFLOW,		/* Controle de fluxo impede transmiss�o */
	/* 89: */ TNOUDERR,		/* N�o houve erro no protocolo sem conex�o */
	/* 90: */ TNOTSUPPORT,		/* Fun��o n�o implementada */
	/* 91: */ TNOROUTE,		/* N�o h� rota para o n� destino */
	/* 92: */ TDNSSERVER		/* Erro no servidor de DNS */

}	ERRNO;
