/*
 ****************************************************************
 *								*
 *			<grp.h>					*
 *								*
 *	Formato do arquivo de grupos				*
 *								*
 *	Vers�o	1.0.0, de 28.10.86				*
 *		3.0.0, de 07.07.95				*
 *								*
 *	M�dulo: grp.h						*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1995 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	GRP_H

/*
 ******	Constantes universais ***********************************
 */
#define	NULL	 0
#define	NOGROUP	 (GROUP *)NULL

/*
 ******	Estrutura "GROUP" ***************************************
 */
typedef struct	group	GROUP;

struct	group
{

	char	*gr_name;	/* Nome do Grupo */
	char	*gr_passwd;	/* Senha Encriptada */
	int	gr_gid;		/* No. do Grupo */
	char	**gr_mem;	/* Ponteiro para os membros */
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern GROUP	*getgrent (void);
extern void	setgrent (void);
extern void	endgrent (void);
extern GROUP	*getgrgid (int);
extern GROUP	*getgrnam (const char *);
extern char	*grcache (int);
