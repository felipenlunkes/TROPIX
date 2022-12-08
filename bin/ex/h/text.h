/*
 ****************************************************************
 *								*
 *			text.h					*
 *								*
 *	Texto em edi��o						*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 23.03.95				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	H_TEXT		/* Para declarar as fun��es */

/*
 ******	Lista circular de linhas mantidas por ED ****************
 */
typedef	struct	base	BASE;

struct	base
{
	BASE	*ant;		/* & base anterior */
	BASE	*pos;		/* & base posterior */
	char	*ch;		/* & cadeia de caracteres da linha */
};

#define	NOBASE	(BASE *)0
#define	NOBASEP	(BASE **)0

/*
 ******	Manipula��es b�sicas na lista ***************************
 */
#define	ISFIRST(b)	(b == Text->t_root->pos)
#define	ISLAST(b)	(b == Text->t_root->ant)

#define	NEWFIRST(b)	Text->t_root->pos = (b), (b)->ant = Text->t_root
#define	NEWLAST(b)	Text->t_root->ant = (b), (b)->pos = Text->t_root

#define	FIRST()		(Text->t_root->pos)
#define	LAST()		(Text->t_root->ant)

#define	POS(b)		(b->pos)
#define	ANT(b)		(b->ant)

#define	FLINK(a,b)	a->pos = b, b->ant = a

#define	LINK(a,f,l)	f->ant = a, l->pos = a->pos, a->pos = f, l->pos->ant = l

#define	UNLINK(f,l)	f->ant->pos = l->pos, l->pos->ant = f->ant

/*
 ******	Tipo tamanho ********************************************
 */
typedef	struct
{
	int	s_nc;		/* No. de caracteres */
	int	s_nl;		/* No. de linhas */

}	SIZE;

#define	NOSIZE	(SIZE *)0

/*
 ******	Caracteristicas do texto em edi��o **********************
 */
#undef	TEXT

typedef	struct
{
	BASE	*t_root;
	SIZE	t_size;
	int	t_flags;		/* Veja flags abaixo */
	char	*t_name;

}	TEXT;

#define	NOTEXT	(TEXT *)0

/*
 ******	Valores para "t_flag" ***********************************
 */
#define   T_CHANGED	0x01	/* O Texto j� foi alterado */
#define   T_RDONLY	0x02	/* O Texto � apenas para leitura */
#define   T_EDITION	0x04	/* Comando de Edi��o */
#define   T_NEW		0x08	/* Iniciando edi��o */

/*
 ******	Valores retornados pelas fun��es de E/S *****************
 */
typedef	enum
{
	IO_OK,		/* E/S sem problemas */
	IO_NSPACE,	/* Nao houve memoria suficiente */
	IO_WRERROR,	/* Erro na escrita */
	IO_RDERROR,	/* Erro na leitura */
	IO_PERMISSION,	/* Permiss�o negada */
	IO_NFOUND,	/* Arquivo n�o encontrado */
	IO_DIRECTORY,	/* Arquivo � um diretorio */
	IO_IREGULAR,	/* Arquivo irregular */
	IO_OBJECT,	/* Arquivo contem um programa objeto */
	IO_EMPTY,	/* Arquivo vazio */
	IO_RDONLY,	/* Arquivo com permiss�o apenas para leitura */
	IO_EXISTS,	/* Arquivo j� existe */
	IO_SAVED	/* O Texto j� foi salvo */

}	TXTIO;
