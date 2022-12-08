/*
 ****************************************************************
 *								*
 *			<sys/dirent.h>				*
 *								*
 *   Formato do diret�rio independente de sistema de arquivos	*
 *								*
 *	Vers�o	4.0.0, de 02.07.01				*
 *		4.8.0, de 02.11.05				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	DIRENT_H 		/* Para definir os prot�tipos */

/*
 ******	Defini��es da estrutura *********************************
 */
#define	MAXNAMLEN	255	/* Tamanho m�ximo do nome */

#define	NODIRENT	(DIRENT *)NULL

typedef struct dirent	DIRENT;

struct dirent
{
	off_t	d_offset;		/* No diret�rio original */
	int	d_ino;			/* N�mero do n�-�ndice */
	int	d_namlen;		/* Tamanho do identificador */
	char	d_name[MAXNAMLEN+1];	/* O identificador */
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern int	getdirent (int, DIRENT *, int, int *);
extern ino_t	getdirpar (dev_t dev, ino_t ino, DIRENT *dep);
