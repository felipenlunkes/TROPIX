/*
 ****************************************************************
 *								*
 *			extern.h				*
 *								*
 *	Declara��es de vari�veis globais			*
 *								*
 *	Vers�o	3.0.0, de 29.03.96				*
 *		3.2.3, de 13.12.99				*
 *								*
 *	M�dulo: Make: Construtor de Programas			*
 *		Interpretador de Comandos			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

/*
 ****	Em src/make.c   *****************************************
 */
extern	const char	pgversion[];	/* Vers�o do programa */

extern	char		*makefile_name;	/* Nome do arquivo de descri��o */
extern	char		*shell;		/* Nome da "shell" a ser utilizada */

extern	int		touch,		/* D� "touch" no m�dulo e n�o executa
					   os comandos */
			nostop,		/* Prossegue, mesmo em caso de erro */
			execcmd,	/* Executa os comandos */
			why,		/* Explica o motivo das atualiza��es */
			listonly,	/* Apenas lista os alvos */
			build;		/* Refaz tudo, independentemente das datas */

extern	void		(*sigint) (int, ...),	/* Tratamento de sinais */
			(*sigquit) (int, ...),
			(*sigterm) (int, ...);

/*
 ****	Em tbl/mkhashtb.c   *************************************
 */
extern	HASH		hashtb[];	/* A tabela hash */
extern	char		nullstr[];	/* A cadeia nula "" */

extern	MACRO		*at_macro,	/* Entrada da macro $@ */
			*star_macro,	/* Entrada da macro $* */
			*ask_macro,	/* Entrada da macro $? */
			*minor_macro;	/* Entrada da macro $< */

/*
 ****	Em src/scan.c   *****************************************
 */
extern	TOKEN		token;		/* �ltimo token obtido */
extern	char		*makefile_text;	/* Texto do makefile */

/*
 ****	Em src/error.c   ****************************************
 */
extern	int		nwarnings,	/* N�mero de advert�ncias */
			nerrors;	/* N�mero de erros */
