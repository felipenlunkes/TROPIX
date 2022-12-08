/*
 ****************************************************************
 *								*
 *			tar.h					*
 *								*
 *	Header do formato TAR					*
 *								*
 *	Vers�o	1.0.0, de 09.09.86				*
 *		4.8.0, de 19.07.05				*
 *								*
 *	M�dulo: gar						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */


/*
 ****************************************************************
 *	Estrutura do Header					*
 ****************************************************************
 */
typedef	struct
{
	char	t_name[100];		/* Nome do Arquivo */
	char	t_mode[8];		/* Tipo do arquivo */
	char	t_uid[8];		/* Dono */
	char	t_gid[8];		/* Grupo */
	char	t_size[12];		/* Tamanho */
	char	t_mtime[12];		/* tempo de modifica��o */
	char	t_chksum[8];		/* Checksum */
	char	t_typeflag;		/* Tipo do arquivo */
	char	t_linkname[100];	/* Nome do Link */

	/* Os campos seguintes ainda n�o s�o tratados */

	char	t_magic[6];
	char	t_version[2];
	char	t_uname[32];
	char	t_gname[32];
	char	t_devmajor[8];
	char	t_devminor[8];
	char	t_prefix[155+12];

}	THEAD;

/*
 ****************************************************************
 *	Prot�tipos						*
 ****************************************************************
 */
extern int	tchecksum (THEAD *);
