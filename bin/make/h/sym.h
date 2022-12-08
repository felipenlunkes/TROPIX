/*
 ****************************************************************
 *								*
 *			sym.h					*
 *								*
 *	Informa��es sobre s�mbolos				*
 *								*
 *	Vers�o	3.0.0, de 29.03.96				*
 *		3.0.1, de 01.05.97				*
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
 ****************************************************************
 *	Lista de nomes						*
 ****************************************************************
 */
struct	nlist
{
	SYM	*n_sym;		/* O nome */
	RANGE	n_range;	/* Posi��o no texto */

	NLIST	*n_next;	/* Pr�ximo nome */
};

/*
 ****************************************************************
 *	Lista de comandos para atualiza��o			*
 ****************************************************************
 */
struct	clist
{
	char	*c_command;	/* Um comando */
	char	*c_line;	/* Linha onde se encontra */
	int	c_nline;	/* N�mero da linha */
	int	c_metachar;	/* H� metacaracteres no comando */

	CLIST	*c_next;	/* Pr�ximo comando */
};

/*
 ****************************************************************
 *	Informa��es sobre depend�ncias				*
 ****************************************************************
 */
struct	depen
{
	int	d_flags;	/* Flags */
	time_t	d_time;		/* Ultima modifica��o (0 = inexistente) */

	NLIST	*d_depen;	/* Lista de Depend�ncias */
	CLIST	*d_command;	/* Lista de comandos para atualiza��o */
	SYM	*d_sibling;	/* Lista circular de alvos irm�os */

	int	d_nline;	/* N�mero da linha onde aparece como alvo */
};

/*
 ****	Bits de "d_flags"  **************************************
 */
#define	D_READY		0x01	/* O n� j� est� atualizado */
#define	D_ERROR		0x02	/* Houve erro na atualiza��o */
#define	D_CYCLE		0x04	/* O n� pertence ao caminho sendo explorado */
#define	D_EXIST		0x08	/* Executa os comandos apenas se n�o existir */
#define	D_VIRTUAL	0x10	/* O alvo � virtual */
#define	D_DEFINED	0x20	/* O alvo foi definido */

/*
 ****************************************************************
 *	Informa��es sobre macros				*
 ****************************************************************
 */
struct	macro
{
	char	*m_begin,	/* In�cio do texto da macro */
		*m_line;	/* In�cio da linha */
	int	m_nline;	/* N�mero da linha */
};

/*
 ****************************************************************
 *	Informa��es sobre s�mbolos				*
 ****************************************************************
 */
/*
 ****	Tipos de s�mbolos  **************************************
 */
typedef enum
{
	S_PUTENV,		/* Palavra reservada ".putenv" */
	S_EXIST,		/* Palavra reservada ".exist" */
	S_VIRTUAL,		/* Palavra reservada ".virtual" */
	S_NAME 			/* Macro ou nome de arquivo */

}	STYPE;

/*
 ****	Estrutura de informa��es sobre s�mbolos   ***************
 */
struct	sym
{
	STYPE	s_type;		/* Tipo (acima) */

	MACRO	s_macro;	/* Informa��es sobre a macro */
	DEPEN	s_node;		/* N� do grafo de depend�ncias */

	int	s_isid;		/* � um identificador */
	int	s_namelen;	/* strlen (s_name) */

	char	s_name[1];	/* In�cio do nome */
};

#define	SYM_FIXED_SZ	((int)(&((NOSYM)->s_name)))

/*
 ****************************************************************
 *	Estrutura da tabela hash				*
 ****************************************************************
 */
#define	HASHSZ	1009		/* Tamanho (deve ser primo) */

struct	hash
{
	SYM	*h_sym;		/* Ponteiro para a estrutura SYM */
};
