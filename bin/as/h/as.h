/*
 ****************************************************************
 *								*
 *			as.h					*
 *								*
 *	Vari�veis globais do montador				*
 *								*
 *	Vers�o	1.0.00, de 05.03.86				*
 *		3.0.12, de 07.08.97				*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

extern long	*lc;		/* Location counter */

extern long	lctext,		/* Location counter, TEXT */
		lcconst,	/* Location counter, CONST */
		lcdata,		/* Location counter, DATA */
		lcbss;		/* Location counter, BSS */

extern long	tsize,		/* Tamanho da se��o TEXT */
		csize,		/* Tamanho da se��o CONST */
		dsize,		/* Tamanho da se��o DATA */
		bsize;		/* Tamanho da se��o BSS */

extern int	pass;		/* Passo atual (1 ou 2) */

extern int	section;	/* Se��o atual */

extern long	opcodeno;	/* Numerador sequencial das opera��es */

extern int	symblk;		/* "Local symbol block" atual */

extern int	aflag,		/* Gera todos os simbolos */
		vflag,		/* Verbose */
		wflag,		/* O "normal" � 16 bits (ao inv�s de 32) */
		eflag,		/* A listagem deve ser "little-endian" */
		lflag;		/* Lista o Programa Fonte */

extern int	seg16;		/* O segmento � de 16 bits (ao inv�s de 32) */

extern const char *objname,	/* Nome do arquivo objeto (default: "a.out") */
		*srcname,	/* Nome do arquivo fonte */
		*listname;	/* Nome da listagem */

extern char 	*rtname,	/* Nome do temporario de Reloca��o de TEXT */
		*rdname;	/* Nome do temporario de Reloca��o de DATA */

extern FILE	*src,		/* Arquivo Fonte */
		*list,		/* Listagem */
		*aout,		/* a.out */
		*reltext,	/* Reloca��o do text */
		*reldata;	/* Reloca��o do DATA */

extern int	nmsgs;		/* N�mero de Erros Encontrados */

extern long	sectoff;	/* Deslocamento dentro da se��o atual */

extern char	*nextp;		/* Ponteiro do analisar l�xico */
