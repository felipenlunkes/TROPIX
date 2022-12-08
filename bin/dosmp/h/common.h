/*
 ****************************************************************
 *								*
 *			common.h				*
 *								*
 *	Defini��es utilizadas em todos os m�dulos		*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.7, de 04.08.97				*
 *								*
 *	M�dulo: DOSMP						*
 *		Utilit�rios Sofisticados			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 *		Inspirado no PLDOS de Norival Ribeiro Figueira	*
 *								*
 ****************************************************************
 */


/*
 ******	Defini��es �teis ****************************************
 */
#define	NULL	0
#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	MIN(a,b) ((a) < (b) ? (a) : (b))

/*
 ******	Tipos �teis *********************************************
 */
typedef unsigned int	bit;

/*
 ******	Defini��es das macros ***********************************
 */
#ifdef	LITTLE_ENDIAN

#define	GET_SHORT(cp)		(*(unsigned short *)(cp))
#define	GET_LONG(cp)		(*(unsigned long *)(cp))
#define	PUT_SHORT(n, cp) 	(*(unsigned short *)(cp) = n)
#define	PUT_LONG(n, cp) 	(*(unsigned long *)(cp) = n)

#else

#define	GET_SHORT(cp)		get_bad_short (cp)
#define	GET_LONG(cp)		get_bad_long (cp)
#define	PUT_SHORT(n, cp) 	put_bad_short (n, cp)
#define	PUT_LONG(n, cp) 	put_bad_long (n, cp)

extern int		get_bad_short (const char *);
extern long		get_bad_long (const char *);
extern void		put_bad_short (int, char *);
extern void		put_bad_long (long, char *);

#endif	LITTLE_ENDIAN

/*
 ******	Par�metros do programa **********************************
 */
extern const char	pgversion[];	/* Vers�o */
extern int		exit_code;	/* C�digo de retorno */
extern const char	*sys_nm;	/* Nome do sistema operacional */
extern const char	**color_vector;	/* Para o vetor de cores */

/*
 ******	Indicadores do programa *********************************
 */
extern int		cflag;		/* Cria uma sistema de arquivos */
extern int		rflag;		/* Read only */
extern int		vflag;		/* Verbose */

/*
 ******	Textos comuns *******************************************
 */
extern const char	options_ifv[];	/* Textos comum em "cmd.c" */
extern const char	somewhere_expand[];
extern const char	num_dev_list[];
extern const char	num_dev_option[];

/*
 ****** Indicadores do comandos	*********************************
 */
extern int		cmd_iflag;	/* Interativo */
extern int		cmd_vflag;	/* Verboso */
extern int		cmd_fflag;	/* For�a */
extern int		cmd_lflag;	/* Longo */
extern int		cmd_dflag;	/* Debug */
extern int		cmd_dotflag;	/* N�o ignora ".old" */
extern int		cmd_cflag;	/* Compara��o */
extern int		cmd_uflag;	/* Atualiza��o */
extern int		cmd_aflag;	/* Todas as entradas */
extern int		cmd_sflag;	/* Somente os totais */

/*
 ****** Vari�veis dos padr�es ***********************************
 */
#define	NPAT	20

extern const char	*inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
extern int		inc_pati;

extern const char	*exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
extern int		exc_pati;

/*
 ****** Vari�veis de entrada/sa�da ******************************
 */
extern char		dev_nm[64];	/* Nome do dispositivo */
extern long		dev_mode;	/* Modo do dispositivo */
extern int		dev_fd;		/* Descritor do dispositivo */
extern int		dev_dev;	/* Major + minor do dispositivo */
extern int		dev_type;	/* Tipo da parti��o */
extern int		dev_ro;		/* Detetada prote��o de escrita */

extern char		vol_nm[];	/* Nome do volume */
extern char		stdin_is_a_tty;	/* Estamos lendo do terminal */

/*
 ******	Estado do sistema de arquivos DOS ***********************
 */
typedef enum
{
	FS_CLOSED = 0,		/* Fechado */
	FS_OPEN,		/* Aberto o dispositivo, mas sem DOS v�lido */
	FS_MOUNT_RO,		/* DOS OK, pronto para leituras  */
	FS_MOUNT_RW		/* DOS OK, pronto para leituras e escritas */

}	FS_STATUS;

extern FS_STATUS	fs_status;	/* Estado atual */

/*
 ******	Quasi-constantes do tempo *******************************
 */
extern time_t		HOJE;		/* In�cio do dia de hoje (GMT) */
extern time_t		AMANHA;		/* In�cio do dia de amanh� (GMT) */
extern time_t		SEMANA;		/* In�cio da semana (GMT) */

/*
 ******	Dados da raiz *******************************************
 */
extern int		root_dev;	/* Dispositivo da raiz */
extern int		root_ino;	/* No. do inode da raiz */

/*
 ****** Vari�veis de "cmd_getopt" *******************************
 */
extern const char	*cmd_nm;	/* Nome do comando em execu��o */
extern const char	*cmd_optarg; 	/* Argumento de uma op��o */
extern int		cmd_optind;	/* Indice do argumento apos as op��es */
extern int		cmd_optinit;	/* Na pr�xima chamada, inicializa */

/*
 ****** Vari�veis de "signal" ***********************************
 */
extern int		received_intr;	/* Veio um <^C> */
extern int		ignore_intr;	/* Diferente de zero, ignora <^C> */

/*
 ******	Outras vari�veis ****************************************
 */
extern int		cwd_cluster;	/* Diret�rio corrente */
extern int		bin_mode;	/* Modo bin�rio ao inv�s ISO */
#define iso_mode (!bin_mode)		/* Modo ISO */
extern int		lfn_mode;	/* == 0 => 8.3 * != 0 => 255 (W 95) */
