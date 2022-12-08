/*
 ****************************************************************
 *								*
 *			tbl.h					*
 *								*
 *	Estruturas, constantes e vari�veis			*
 *	relativas �s tabelas.					*
 *								*
 *	Vers�o 2.0.0, de 08.07.87				*
 *	Vers�o 2.2.1, de 04.09.89				*
 *								*
 *	Modulo: SROFF						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	TBL_H

/*
 ****************************************************************
 *	Definicoes de constantes.				*
 ****************************************************************
 */
#define		SEP	0
#define		NCOL	1

/*
 ****************************************************************
 *	Definicoes de tipos.					*
 ****************************************************************
 */
typedef	struct
{
	int	c_larg;
	int	c_esq;
	int	c_ponto;
	int	c_dir;
	int	c_subcol;
	int	c_esp;
	BOOL	c_eflag;

}	COLUNA;

typedef	struct
{
	char	f_fmt;
	TPCHAR	f_tipo;
	int	f_sep;
	int	f_ncol;

}	FORMATO;

typedef	struct
{
	char	*d_elemto;
	int	d_tam;
	int	d_tamesq;
	char	d_ccampo;
	char	d_celemto;
	char	d_clinha;
	FORMATO	*d_fmtp;

}	DADOS;


/*
 ****************************************************************
 *	Variaveis globais.					*
 ****************************************************************
 */
extern	COLUNA	*crtcol;	/* caracteristicas das colunas */
extern	int	numcol;		/* numero de colunas */
extern	int	tbl;		/* estado da tabela */
extern	FORMATO	**fmtpont;	/* ponteiros para vetor de formatos */
extern	int	contfmt;	/* numero de formato atual */
extern	int	maxfmt;		/* numero total de formatos */
extern	DADOS	**dtpont;	/* ponteiros para vetor de dados */
extern	int	contdata;	/* numero de dados atual */
extern	int	maxdata;	/* numero total de dados */
extern	int	inicfmt;	/* inicio dos formatos da ultima subtabela */

extern	BOOL	center;		/* centra a tabela */
extern	BOOL	expand;		/* expande a tabela */
extern	BOOL	box;		/* a tabela fica em uma moldura */
extern	BOOL	doublebox;	/* a tabela fica em uma moldura dupla */
extern	BOOL	allbox;		/* cada elemento da tabela fica em moldura */
extern	char	tab;		/* separador na entrada de dados */
extern	long	lintit;		/* linha do t�tulo para a quebra de p�gina */
extern	BOOL	temtit;		/* h� t�tulo na quebra de p�gina */
extern	BOOL	titul;		/* o t�tulo da quebra de p�gina � sublinhado */
extern	BOOL	titneg;		/* o t�tulo da quebra de p�gina � negrito */

/*
 ****************************************************************
 *	Rotinas globais.					*
 ****************************************************************
 */
char	*identatr ();
