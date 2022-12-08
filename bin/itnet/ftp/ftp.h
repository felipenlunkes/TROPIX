/*
 ****************************************************************
 *								*
 *			ftp.h					*
 *								*
 *	File transfer protocol 					*
 *								*
 *	Vers�o	3.0.0, de 12.10.92				*
 *		3.0.4, de 23.08.97				*
 *								*
 *	M�dulo: FTP						*
 *		Utilit�rios de comunica��es			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */


/*
 ******	C�digos de retorno **************************************
 */
typedef enum
{
	PRELIM = 1,	/* Positivo preliminar */
	COMPLETE,	/* Positivo completo */
	CONTINUE,	/* Positivo intermedi�rio */
	TRANSIENT,	/* Negativo transiente */
	ERROR		/* Negativo completo */

}	REPLY_ENUM;

/*
 ******	C�digos dos tipos ***************************************
 */
typedef enum
{
	TYPE_A = 1,	/* ASCII */
	TYPE_E,		/* EBCDIC */
	TYPE_I,		/* IMAGEM */
	TYPE_L		/* LOCAL */

}	TYPE_ENUM;

/*
 ******	C�digos das formas **************************************
 */
typedef enum
{
	FORM_N = 1,	/* N�o impress�o */
	FORM_T,		/* TELNET */
	FORM_C		/* Controle da impressora (ASA) */

}	FORM_ENUM;

/*
 ******	C�digos das estruturas **********************************
 */
typedef enum
{
	STRU_F = 1,	/* Sem estrutura */
	STRU_R,		/* Estrutura de registro */
	STRU_P		/* Estrutura de p�gina */

}	STRU_ENUM;

/*
 ******	C�digos dos modos ***************************************
 */
typedef enum
{
	MODE_S = 1,	/* Fluxo */
	MODE_B,		/* Bloco */
	MODE_C		/* Comprimido */

}	MODE_ENUM;
