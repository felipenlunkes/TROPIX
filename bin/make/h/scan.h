/*
 ****************************************************************
 *								*
 *			scan.h					*
 *								*
 *	Defini��es utilizadas pelo Analisador L�xico.		*
 *								*
 *	Vers�o	3.0.0, de 29.03.96				*
 *								*
 *	M�dulo: Make: Construtor de Programas			*
 *		Interpretador de Comandos			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

#ifdef	MAJOR
#undef	MAJOR
#endif	MAJOR

/*
 ****************************************************************
 *	Majors dos tokens 					*
 ****************************************************************
 */
typedef	enum
{
	NAME,		/* Nome de macro ou de arquivo */
	CL,		/* : */
	EQ,		/* = */
	BOC,		/* Seq��ncia <nl><ht> */
	EOL,		/* Final da linha: <nl> n�o seguido de <ht> */
	EOT		/* Final do texto: <nul> */

}	MAJOR;

/*
 ****************************************************************
 *	Estrutura preenchida pelo analisador l�xico		*
 ****************************************************************
 */
struct	token
{
	MAJOR	t_major;	/* Major do Token */
	RANGE	t_range;	/* Localiza��o do token no texto */
	SYM	*t_sym;		/* Ponteiro para a estrutura SYM */
};
