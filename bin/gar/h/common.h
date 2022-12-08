/*
 ****************************************************************
 *								*
 *			common.h				*
 *								*
 *	Defini��es universais					*
 *								*
 *	Vers�o	1.1.0, de 11.01.88				*
 *		4.2.0, de 27.04.02				*
 *								*
 *	M�dulo: GAR						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��es universais					*
 ****************************************************************
 */
#define	EVER	;;
#define	elif	else if
#define NOVOID	(void *)NULL
#define	NOPTR	(void *)NULL

#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	STDIN	0
#define STDOUT	1

#define	MIN(a,b)	((a) < (b) ? (a) : (b))

typedef unsigned short	ushort;	/* 16 bites sem sinal */

/*
 ******	Indicadores *********************************************
 */
extern int		Tflag;		/* Gera o formato TAR */
extern int		Dflag;		/* N�O Comprime */
extern int		nflag;		/* Interativo */
extern int		uflag;		/* Compara��o com atualiza��o */
extern int		rflag;		/* Sempre cheque os CRCs */
extern int		vflag;		/* Verbose */
extern int		dflag;		/* Diretorio Corrente */
extern int		fflag;		/* Copia mesmo que j� exista */
extern int		mflag;		/* Restaura dono, grupo e datas */
extern int		gflag;		/* Processa o "garfield" */
extern int		dotflag;	/* N�o ignora ".old" etc ... */
extern int		crcflag;	/* N�o gera CRC na compress�o */
extern int		Gflag;		/* Debug */

/*
 ******	Declara��es da defla��o *********************************
 */
#define DEF_LEVEL	5	/* N�vel de compacta��o normal (ZIP) */
#define MIN_LEVEL	1	/* N�vel de compacta��o m�nimo (ZIP) */
#define MAX_LEVEL	9	/* N�vel de compacta��o m�ximo (ZIP) */

extern int		ZIP_LEVEL;	/* Os n�veis podem ser de 1..9 */

/*
 ****** Vari�veis externas **************************************
 */
extern const char	headerversion[]; /* Vers�o do programa */

extern int		exit_code;	/* C�digo de retorno */

extern int		file_block;	/* No. do bloco do arquivo na cole��o */ 

/*
 ******	Buffer de Entrada/Saida *********************************
 */
extern int		col_area_sz;		/* Tamanho do buffer em vigor (blocagem) */

extern int		col_area_avail_sz;	/* No. de bytes disponiveis no buffer */

extern int		col_is_a_tape;		/* A cole��o � uma fita */

/*
 ****** Vari�veis diversas **************************************
 */
extern const char	*g_filenm;	/* Nome do Arquivo em Processamento */
extern int		g_filenmput;	/* O Nome do Arquivo ja foi impresso */
extern int		g_nlput;	/* O <nl> j� foi escrito */

extern time_t		date;		/* Data de cria��o da Cole��o GAR */

extern int		vol;		/* No. do Volume GAR */

extern FILE		*ttyfp;		/* Para ler do terminal */

extern const char	**color_vector;	/* Para as cores dos modos */

/*
 ****** Garfield ************************************************
 */
extern const char	garfield[];
extern FILE		*gfp;

/*
 ****** Garstamp ************************************************
 */
extern const char	garstamp[];
extern time_t		garstamp_time;

/*
 ****** Cole��o *************************************************
 */
extern int		device_code;	/* C�digo do dispositivo */
extern const char	*device_nm; 	/* Nome do Dispositivo */

extern int		colfd;		/* File Descriptor da Cole��o */
extern dev_t		coldev;		/* Dispositivo da Cole��o */
extern ino_t		colino;		/* Inode da Cole��o */

extern char		*reduce_nm0,	/* Nomes do arquivo tempor�rio */
			*reduce_nm1,
			*reduce_nm2;

extern long		totalbytes;	/* No. Total de Bytes lidos/escritos */

extern off_t		col_offset;	/* Tamanho da cole��o */

extern off_t		col_max_offset;	/* Tamanho m�ximo da cole��o */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void		(*function) (void *, int);

extern off_t		deflate (int, FILE *);
extern off_t		inflate (void (*) (), int);
extern void		msg (char *, ...);
extern off_t		reduce (int, FILE *);
extern off_t		unreduce (void (*) ());
extern char		*editpercent (int);
extern int		getpercent (long, long);
extern void		bread (void *, int);
extern void		bwrite (const void *, int);
extern void		on_signal (int, ...);
extern const char	*edit_BY_to_KB (ulong bytes);

#ifdef	STAT_H
extern void		get_dev_size (int, STAT *sp);
extern void		print_file_nm (const char *, const STAT *, const char *, FILE *);
#endif	STAT_H

