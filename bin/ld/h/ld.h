/*
 ****************************************************************
 *								*
 *			ld.h					*
 *								*
 *	Defini��es globais					*
 *								*
 *	Vers�o	1.0.0, de 02.10.86				*
 *		4.3.0, de 06.07.02				*
 *								*
 *	M�dulo: ld						*
 *		Utilit�rios b�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****** Defini��es universais ***********************************
 */
#define	EVER	;;
#define	elif	else if
#if (0)	/*******************************************************/
#define	KBSZ	1024		/* No. de bytes de um Kilobyte */
#define	MBSZ	(1024 * KBSZ)	/* No. de bytes de um Megabyte */
#define	GBSZ	(1024 * MBSZ)	/* No. de bytes de um Gigabyte */
#endif	/*******************************************************/

/*
 ****** Defini��es para a tabela de s�mbolos ********************
 */
#define	IS_UNDEF(sp)		((sp)->s_type == (EXTERN|UNDEF) && (sp)->s_value == 0)
#define	IS_COMMON(sp)		((sp)->s_type == (EXTERN|UNDEF) && (sp)->s_value != 0)
#define	IS_UNDEF_OR_COMMON(sp)	((sp)->s_type == (EXTERN|UNDEF))

/*
 ******	Nulos das estruturas ************************************
 */
#define	NOSYM		(SYM *)NULL
#define	NOGSYM		(GSYM *)NULL
#define	NOMODULE	(MODULE *)NULL
#define	NORELOC		(RELOC *)NULL
#define	NOLIBSYM	(LIBSYM *)NULL
#define NOLIBFILES	(LIBFILES *)NULL
#define	NIL		(-1)

/*
 ****** Tamanhos das tabelas ************************************
 */
#define	HASHSZ		1009
#define	BUFSZ		10240

/*
 ****** Arredondamento para o proximo multiplo de "y" ***********
 */
#define	ROUND(x,y)	(((x) + ((y) - 1)) & ~((y) - 1))

/*
 ****** Estrutura da tabela de s�mbolos	*************************
 */
typedef	struct gsym	GSYM;

typedef	struct module	MODULE;

struct gsym
{
	int		s_index;	/* No. de ordem do elemento */
	GSYM		*s_next;	/* Ponteiro para o pr�ximo */
	GSYM		*s_link;	/* Lista de colis�o da HASH */
	const MODULE	*s_mod;		/* M�dulo de defini��o do s�mbolo */

	off_t		*s_ref_vec;	/* Vetor de referencias externas */
	int		s_ref_len;	/* N�mero de entradas ocupadas */
	int		s_ref_sz;	/* N�mero de entradas total */

	SYM		s;		/* Elemento da tabela de s�mbolos */
					/* (deve ser o �ltimo) */ 
};

extern GSYM		**link_place;	/* Ponteiro para a entrada da HASHTB */

extern GSYM		gsym_list,	/* Ponteiros para a lista */
			*gsym_last;

extern int		gsym_index;	/* No. de entradas j� em gsymtb */

extern GSYM		*hashtb[]; 	/* A Tabela Hash */

/*
 ****** Estrutura da tabela de m�dulos **************************
 */
struct module
{
	const char	*m_nm;		/* Nome do m�dulo */
	int		m_type;		/* Tipo do m�dulo */
	dev_t		m_dev;		/* Dispositivo */
	ino_t		m_ino;		/* N�mero do i-node */
	MODULE		*m_next;	/* Ponteiro para a lista */
};

extern MODULE		modtb_list,		/* Tabela de m�dulos */
			*modtb_last; 		/* �ltima entrada da lista */

/*
 ****** Op��es de link-edi��o ***********************************
 */
extern int		rflag,		/* Mantem a reloca��o, n�o define common */
			bflag,		/* Gera uma biblioteca compartilhada */
			nflag,		/* m�dulo final executavel reentrante */
			sflag,		/* "Strip" - Remove SYMTB, RT e RD */
			vflag,		/* Verbose */
			mflag,		/* Gera mapa de link-edi��o */
			uflag,		/* lista os n�o referenciados */
			dotflag;	/* Tempor�rias no diret�rio corrente */

extern int		lflag,		/* H� Tabela de No. de Linhas */
			dflag;		/* H� Tabela de Depura��o */

/*
 ****** Vari�veis globais ***************************************
 */
extern int		shared_lib_given; /* Foram dadas bibliotecas compartilhadas */

extern int	 	external_reference_cnt; /* No. de s�mbolos externos */

extern int		aout_fd,	/* Descritor do m�dulo final */
			text_fd,	/* Descritor do arquivo com as se��es "TEXT" */
			data_fd;	/* Descritor do arquivo com as se��es "DATA" */

extern FILE	 	*rt_fp,		/* Descritor do arquivo com a RT */
			*rd_fp;		/* Descritor do arquivo com a RD */

extern const char	*obj_nm,	/* Nome do m�dulo final */
			*text_nm,	/* Nome do arquivo com as se��es "TEXT" */
			*data_nm,	/* Nome do arquivo com as se��es "DATA" */
			*rt_nm,		/* Nome do arquivo com a RT */
			*rd_nm;		/* Nome do arquivo com a RD */

extern const char	*entry_nm;	/* Nome do ponto de entrada */

extern off_t		TEXT_SIZE,	/* Tamanho do "TEXT" */
			DATA_SIZE,	/* Tamanho do "DATA" */
			BSS_SIZE,	/* Tamanho do "BSS" */
			COMMON_SIZE,	/* Tamanho do "COMMON" */
			SYMTB_SIZE,	/* Tamanho da SYMTB */
			TEXT_REL_SIZE,	/* Tamanho da RT */
			DATA_REL_SIZE;	/* Tamanho da RD */

extern off_t		TEXT_ORG,	/* Endereco inicial do "TEXT" */
			DATA_ORG,	/* Endereco inicial do "DATA" */
			BSS_ORG,	/* Endereco inicial do "BSS" */
			COMMON_ORG;	/* Endereco inicial do "COMMON" */

/*
 ****** Prot�tipos **********************************************
 */
extern void		colision_tst (void);
extern void		defsym (const char *, int, long);
extern GSYM		*hash (const char *, int);
extern void		pass1 (const char *[]);
extern void		pass2 (void);
extern void		pass3 (void);
extern void		pass4 (void);
extern void		pass5 (void);
extern void		pass4 (void);
extern void		pass5 (void);
extern void		pass6 (void);
extern void		pass7 (void);
extern MODULE		*put_module (const char *, int, dev_t, ino_t, const HEADER *);
extern GSYM		*put_global_symbol (const SYM *, const MODULE *);
extern void		relocsym (SYM *);
extern void 		quit (int);
extern void		install_mod_symbols (const MODULE *, int, const HEADER *, int);
extern void		reg_lib_free_mem (void);
extern const char	*edit_sym_type (const SYM *);
extern const char	*get_module_name (const GSYM *gp);
