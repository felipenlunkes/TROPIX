/*
 ****************************************************************
 *								*
 *			<sys/select.h>				*
 *								*
 *	Defini��o dos tipos usados pela chamada "select"	*
 *								*
 *	Vers�o	4.2.0, de 08.10.01				*
 *		4.2.0, de 08.10.01				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	SELECT_H			/* Para incluir prot�tipos */

/*
 ******	Defini��es de tamanhos **********************************
 */
#define	FD_SETSIZE	32		/* N�mero m�ximo de descritores */

/*
 ******	Defini��es de tipos *************************************
 */
typedef	int		fd_mask;
typedef	int		fd_set;

/*
 ******	Macros �teis ********************************************
 */
#define	FD_SET(fd, mask_ptr)	(*(mask_ptr) |= (1 << (fd)))
#define	FD_CLR(fd, mask_ptr)	(*(mask_ptr) &= ~(1 << (fd)))
#define	FD_ISSET(fd, mask_ptr)	(*(mask_ptr) & (1 << (fd)))
#define	FD_ZERO(mask_ptr)	(*(mask_ptr) = 0)

/*
 ****** Prot�tipos **********************************************
 */
extern int	select (int, fd_set *, fd_set *, fd_set *, const MUTM *);

