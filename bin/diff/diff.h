/*
 ****************************************************************
 *								*
 *			diff.h					*
 *								*
 *	Compara dois arquivos					*
 *								*
 *	Vers�o	2.3.0, de 25.01.90				*
 *		3.0.0, de 24.04.97				*
 *								*
 *	M�dulo: diff						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��es e vari�veis globais				*
 ****************************************************************
 */
#define	elif	else if
#define	EVER	;;
#define	NOSTR	(char *)NULL

/*
 ******	Defini��o de estruturas *********************************
 */
typedef enum
{
	NORMAL,		/* Sa�da normal */
	EDIT,		/* Comandos para o editor */
	REVEDIT,	/* Editor reverso */
	CONTEXT,	/* Context */
	IFDEF		/* #ifdef's */

}	FUNCTION;

typedef struct cand	CAND;

struct cand
{
	int	c_oldlineno;	/* No. da linha do "oldfile" */
	int	c_newlineno;	/* No. da linha do "newfile" */
	CAND	*c_pred;	/* Predecessor */
};

typedef struct pline
{
	int	l_serial;	/* No. serial da parte sem prefixo+sufixo */
	long	l_hash;		/* Valor "hash" da linha */
	char	*l_text;	/* Ponteiro para o texto da linha */

}	PLINE;

/*
 ******	Vari�veis globais ***************************************
 */
extern FUNCTION	function;	/* Modo de funcionamento */

extern int	bflag;		/* Ignore brancos */
extern int	vflag;		/* Verbose */
extern int	tflag;		/* Time */
extern int	dflag;		/* Debug */

extern const char *ifdefname;	/* Nome do ifdef para a fun��o IFDEF */

extern int	context;	/* Tamanho do contexto para a fun��o CONTEXT */

extern int	status;		/* C�digo de retorno do programa */

extern int	anychange;	/* Houve alguma diferen�a entre os arquivos */

/*
 ******	Vari�veis dos arquivos **********************************
 */
extern const char *oldnm,		/* Nome dos arquivos */
		*newnm;

extern STAT	olds, 		/* Estado dos arquivos */
 		news;

extern char	*oldaddr, 	/* Endere�o dos arquivos */
		*newaddr;

extern PLINE	*oldpline,	/* Endere�os dos PLINEs dos arquivos */
		*newpline;

extern int	oldlineno,	/* No. de linhas dos arquivos */
		newlineno;

extern int	prefixsz,	/* Tamanho dos prefixo e sufixo */
		sufixsz;

extern PLINE	*oldshortpline,	/* Endere�os dos PLINEs sem prefixo/sufixo */
		*newshortpline;

extern int	oldshortlineno,	/* No. de linhas dos arquivos sem pref/suf */
		newshortlineno;

extern PLINE	**oldsortvec,	/* Ponteiro para o vetor ordenado */
		**newsortvec;

extern int	*member;	/* Membros equivalentes de newfile */

extern CAND	**klist,	/* Primeira e �ltima entrada da "klist" */
		**lastklist;

extern CAND	*clist;		/* In�cio da "clist" */

extern int	*J;		/* Resultado da correspond�ncia */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	 	diffcmp (void);
char		*copytemp (void);
char		*dirfilenm (const char *, const char *, int);
void 		getprefixsufix (void);
void 		check (void);
void 		output (void);
void 		change (int, int, int, int);
void 		range (int, int, char *);
void 		on_signal (int, ...);
void 		done (void);
int 		min (int, int);
int 		max (int, int);
void 		help (void);

void		readfile (const char *, STAT *, char **);
void 		mkfiledata (char *, PLINE **, int *);
long 		linehash (char *);
void 		printline (char *, int);
void 		sort (PLINE *, int, PLINE ***);
int 		sortcompare (const PLINE *, const PLINE *);
void 		correspondence (void);
void 		fetch (PLINE *, int, int, char *);
void		stonehenge (void);
CAND		*newcand (int, int, CAND *);
void 		compose (void);

void		*diff_malloc (int);
