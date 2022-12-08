/*
 ****************************************************************
 *								*
 *			cpp.h					*
 *								*
 *	Defini��es globais para o pr�processador		*
 *								*
 *	Vers�o	1.0.0, de 05.08.88				*
 *		4.1.0, de 22.08.01				*
 *								*
 *	M�dulo: CPP						*
 *		Tradutores					*
 *		Categoria D					*	
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Vari�veis Globais					*
 ****************************************************************
 */
extern const char	*srcname,	/* Nome do Arquivo Fonte */
			*dstname;	/* Nome do Arquivo a ser Gerado */

extern FILE		*fpout;		/* Descritor da Sa�da */

extern int		Cflag,		/* Mant�m os Coment�rios */
			Pflag,		/* N�o coloca os n�meros de linha na sa�da */
			Tflag,		/* Mais diagn�sticos (estilo LINT) */
			vflag,		/* Modo Verboso */
			dflag;		/* Debug */

extern const char	*incld[],	/* Diret�rios para Procura */
			**incldp;

/*
 ****************************************************************
 *	Prot�tipos						*
 ****************************************************************
 */
extern const char	*basename (const char *);
extern const char	*expand (const char *, char *);
extern const char	*flagedit (int);
extern const char	*mkname (const char *);
extern const char	*mstrcat (char *, ...);
extern const char	*printline (const char *, int);
extern const char	*searchfile (const char *, char);
extern int		expression (void);
extern int		findarg (void);
extern void		free_args_mem (void);
extern int		getescape (const char *);
extern int		pop (void);
extern int		push (void);
extern int		readfile (const char *);
extern void		stackcheck (void);
extern void		directive (void);
extern void		dodefine (void);
extern void		doinclude (void);
extern void		dopragma (void);
extern void		doundef (void);
extern void		help (void);
extern void		mkpredef (const char *, int);
extern void		mkpreundef (const char *);
extern void		operate (void);
extern void		parsefile (void);
extern void		printexpline (const char *, const char *);
extern void		printsymtb (void);
extern void		putlineno (int);
extern void		putlineout (const char *);
extern void		putoutnl (void);
extern void		quit (int);
extern void		on_signal (int, ...);
extern void		skipcomment (void);
extern void		skipline (void);
