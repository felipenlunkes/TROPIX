/*
 ****************************************************************
 *								*
 *			h/extern.h				*
 *								*
 *	Declara��o de vari�veis globais				*
 *								*
 *	Vers�o	1.0.0, de 13.11.86				*
 *		3.0.0, de 26.04.97				*
 *								*
 *	Modulo: ED						*
 *		Editores de Texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Vari�veis globais de "main.c" ***************************
 */
extern const char pgversion[];	/* Vers�o do programa */

extern int	vflag;		/* Verbose */

extern TEXT	Text;		/* Informa��es sobre o Texto em edi��o */
extern BASE	*Root;		/* In�cio da Lista com o Texto em edi��o */
extern BASE	*Current;	/* Posi��o Corrente */
extern AUTO	Search;		/* Express�o Regular p/ Busca */

extern bool	Interactive;	/* Edi��o no terminal */
extern bool	Interruption;	/* Houve uma interrup��o */
extern char	temp_buffer[LSIZE]; /* Buffer temporario para uso geral */

/*
 ******	Vari�veis globais de "msg" ******************************
 */
extern const char	M_ok[];
extern const char	M_nspace[];
extern const char	M_wrerror[];
extern const char	M_rderror[];
extern const char	M_permission[];
extern const char	M_nfound[];
extern const char	M_directory[];
extern const char	M_iregular[];
extern const char	M_object[];
extern const char	M_empty[];
extern const char	M_rdonly[];
extern const char	M_exists[];
extern const char	M_saved[];
extern const char	M_newfile[];
extern const char	M_size[];

/*
 ******	Vari�veis globais de "io" *******************************
 */
extern const char	*M_txtio;	/* Mensagem correspondente a TXTIO */

/*
 ******	Vari�veis globais de "re" *******************************
 */
extern char	*_end_match;	/* Primeiro caracter na linha ap�s a express�o */

/*
 ******	Vari�veis globais de "scan" *****************************
 */
extern char		Line[LSIZE];
extern char		*nextp;
extern const char	*error_msg;	/* Mensagem de Erro */

#ifdef	SCAN_H
extern TOKEN		token;
#endif	SCAN_H
