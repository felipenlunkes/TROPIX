/*
 ****************************************************************
 *								*
 *			fdopen.c				*
 *								*
 *	Abre um arquivo, dado um "fd" j� aberto			*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 08.07.95				*
 *								*
 *	M�dulo: fdopen						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <unistd.h>

#include <sys/uerror.h>

/*
 ****************************************************************
 *	Defini��es e vari�veis globais				*
 ****************************************************************
 */
#define	_EOMEM	(char *)EOF

/*
 ****************************************************************
 *	Abre um arquivo, dado um "fd" j� aberto			*
 ****************************************************************
 */
FILE *
fdopen (register int fd, register const char *tipo)
{
	register FILE	*fp;
	register char	rw;

	rw = (tipo[1] == '+') || (tipo[1] == 'b') && (tipo[2] == '+');

	for (fp = _ioblk; /* vazio */; fp++)
	{
		if (fp >= &_ioblk[_NFILE])
			return (NOFILE);

		if (fp->_flag == 0)
			break;
	}

	if (tipo[0] == 'a')
		lseek (fd, 0, L_END);

	fp->_ptr  = _EOMEM;
	fp->_flag = (rw ? _IORW : (tipo[0] == 'r' ? _IOREAD : _IOWRITE));
	fp->_file = fd;

	return (fp);

}	/*  end fdopen */
