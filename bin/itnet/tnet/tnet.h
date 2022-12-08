/*
 ****************************************************************
 *								*
 *			<tnet.h>				*
 *								*
 *	Formato do segmento de comunica��o da TNET		*
 *								*
 *	Vers�o	2.3.0, de 23.10.91				*
 *		3.0.5, de 05.08.97				*
 *								*
 *	M�dulo: TCMPTO_C/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Algumas constantes universais				*
 ****************************************************************
 */
#define	IN_CALLs		/* Usa as chamadas especiais */

#define	MIN_COMPRESS_SZ	100

#define	SEGCRCSZ	(BLSZ/2)

/*
 ******	Verifica se as macro vari�veis est�o definidas **********
 */
#if	!defined (BIG_ENDIAN) && !defined (LITTLE_ENDIAN)
#error	"Uma das macrovari�veis \"BIG/LITTLE_ENDIAN\" deve estar definida"
#endif	BIG_ENDIAN/LITTLE_ENDIAN

/*
 ******	Defini��es relativas � ordem de bytes da CPU ************
 */
#ifdef	LITTLE_ENDIAN
#define	ENDIAN_LONG(x)	long_endian_cv (x)
#define	ENDIAN_SHORT(x)	short_endian_cv (x)
#else
#define	ENDIAN_LONG(x)	(x)
#define	ENDIAN_SHORT(x)	(x)
#endif	LITTLE_ENDIAN

/*
 ****************************************************************
 *	C�digos dos diversos tipos de SEGMENTOS			*
 ****************************************************************
 */
typedef enum
{
	FQUIT = -1,	/* Reservado pelo protocolo de segmentos */

	FFLAGS = 1,	/* Flags iniciais do programa para o parceiro */
	FEOF,		/* Final do programa */
	FMSG,		/* Mensagem para o parceiro */
	FNAME,		/* Nome de um arquivo */
	FSTAT,		/* Estado de um arquivo */
	FCMP,		/* Envie os CRCs */
	FCRC,		/* Segmento de CRCs */
	FBLOCK,		/* Bloco de um arquivo */
	FLINK		/* Informa��es de LINK */

}	SEG_TYPE;

/*
 ****** Segmento contendo uma mensagem **************************
 */
typedef struct
{
	int	m_type;			/* Tipo */
	int	m_code;			/* C�digo */
	int	m_len;			/* Tamanho */

}	MSG;

/*
 ****** Segmento do tipo "FFLAGS" *********************************
 */
typedef struct
{
	int	seg_type;		/* Tipo */
	int	seg_flags[16];		/* Flags */

}	SEGFLAGS;

/*
 ****** Estrutura das opera��es *********************************
 */
typedef enum
{
	CP = 0,			/* C�pia de sentido ainda indefinido */
	CPTO,			/* C�pia para o n� remoto */
	CPFROM,			/* C�pia para o n� local */

	L_LINK,			/* Opera��o de LINK local */
	R_LINK,			/* Opera��o de LINK remoto */

	L_RM,			/* Opera��o de remo��o local */
	R_RM,			/* Opera��o de remo��o remota */

	L_RM_LINK,		/* Opera��o de remo��o e LINK locais */
	L_RM_CPFROM,		/* Opera��o de remo��o e c�pia locais */
	R_RM_LINK,		/* Opera��o de remo��o e LINK remotos */
	R_RM_CPTO,		/* Opera��o de remo��o e c�pia remotos */

	F_PROCESS,		/* Arquivo aceito (-i) */
	F_PASS			/* Arquivo n�o aceito (-i) */

}	OP_NM;

#define OP_STR { "CP", "CPTO", "CPFROM", "L_LINK", "R_LINK", "L_RM", "R_RM" }
