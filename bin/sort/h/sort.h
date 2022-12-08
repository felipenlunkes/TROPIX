/*
 ****************************************************************
 *								*
 *			sort.h					*
 *								*
 *	Ordena e/ou intercala arquivos				*
 *								*
 *	Vers�o	1.0.0, de 03.10.86				*
 *		3.0.0, de 05.07.97				*
 *								*
 *	M�dulo: sort						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****** Defini��es universais ***********************************
 */
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

/*
 ****** Estrutura da chave **************************************
 */
typedef	struct
{
	int	k_index;	/* No. do campo */
	int	k_begin;	/* In�cio do campo */
	int	k_size;		/* Tamanho do campo */
	char	k_up_down;	/* Ascendente/descendente */
	char	k_code;		/* C�digo de caracteres */

}	KEY;

extern KEY	key_vec[];	/* Vetor contendo as chaves dadas */

/*
 ****** Indicadores *********************************************
 */
extern int	vflag;		/* Verbose */
extern int	mflag;		/* Intercala��o */
extern int	cflag;		/* Verifica se j� est� ordenado */
extern int	tflag;		/* C�digo de caracteres */
extern int	rflag;		/* Ordena��o reversa */

/*
 ****** Vari�veis globais/externas ******************************
 */
extern char	delim;		/* Delimitador entre as chaves */
extern int	numkeys;	/* No. de chaves dadas */
extern FILE	*out_fp;	/* Arquivo de sa�da */

extern const char *pgname;

/*
 ****** Prot�tipos de fun��es ***********************************
 */
extern void	help (void);
extern void	sort (const char *);
extern void	get_keys (const char *);
extern void	set_cmp_function (void);
extern void	merge (const char *[]);

extern int	cmp_fold_up (const char *, const char *);
extern int	cmp_fold_down (const char *, const char *);
extern int	cmp_dic_up (const char *, const char *);
extern int	cmp_dic_down (const char *, const char *);
extern int	cmp_key (const char *, const char *);

extern int	(*compar) (const void *, const void *);
