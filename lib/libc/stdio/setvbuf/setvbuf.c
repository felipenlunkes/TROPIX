/*
 ****************************************************************
 *								*
 *			setvbuf.c				*
 *								*
 *	Define a �rea de entrada/sa�da de um arquivo		*
 *								*
 *	Vers�o	1.0.0, de 17.11.86				*
 *		4.4.0, de 02.11.02				*
 *								*
 *	M�dulo: setvbuf						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

/*
 ******	Defini��es globais **************************************
 */
#define	elif	else if
#define	_EOMEM	(char *)EOF

/*
 ******	Defini��o de vari�veis externas *************************
 */
extern char	_sio1buf[], _sio2buf[];
extern int	_stdbuf;

/*
 ****************************************************************
 *	Define a �rea de entrada/sa�da de um arquivo		*
 ****************************************************************
 */
int
setvbuf (FILE *fp, char *buf, int mode, int size)
{
	/*
	 *	O arquivo j� deve estar aberto
	 */
	if (fp->_flag == 0 || size < 0)
		return (EOF);

	if (mode == _IOLBF && (fp->_flag & _IOWRITE) == 0)
		return (EOF);

	/*
	 *	Libera a �rea antiga
	 */
	if (fp->_base != NOSTR)
	{
		if   (fp->_flag & _IOMYBUF)
			free (fp->_base);
		elif (fp->_base == _sio1buf)
			_stdbuf |= 0x1;
		elif (fp->_base == _sio2buf)
			_stdbuf |= 0x2;

		fp->_bend = NOSTR;
		fp->_lend = NOSTR;
	}

	fp->_flag &= ~(_IOMYBUF|_IONOBUF|_IOLNBUF);

	/*
	 *	Se n�o foi dada uma �rea, obt�m uma
	 */
	if (buf == NOSTR && (mode == _IOFBF || mode == _IOLBF))
	{
		if (size <= BLSZ && _stdbuf)
		{
			if (_stdbuf & 0x01)
				{ buf = _sio1buf; _stdbuf &= ~0x01; }
			else
				{ buf = _sio2buf; _stdbuf &= ~0x02; }
		}
		else
		{
			if ((buf = malloc (size)) == NOSTR)
				return (EOF);

			fp->_flag |= _IOMYBUF;
		}
	}

	/*
	 *	De posse de todos os ingredientes, termina o bloco
	 */
	switch (mode)
	{
	    case _IOFBF:
		fp->_base  = buf;
		fp->_bend  = buf + size;
		fp->_bsize = size;
		break;

	    case _IOLBF:
		fp->_flag |= _IOLNBUF;
		fp->_base  = buf;
		fp->_lend  = buf + size;
		fp->_bsize = size;
		break;

	    case _IONOBUF:
		fp->_base = NOSTR;
		fp->_flag |= _IONOBUF;
		fp->_bsize = 1;
		break;

	    default:
		return (EOF);

	}	/*  end switch (mode)  */

	fp->_ptr = _EOMEM;

	return (0);

}	/* end setvbuf */
