/*
 ****************************************************************
 *								*
 *			_writebuf.c				*
 *								*
 *	Escreve a �rea usada pela stdio				*
 *								*
 *	Vers�o	1.0.0, de 14.11.86				*
 *		4.4.0, de 02.11.02				*
 *								*
 *	M�dulo: putc						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

/*
 ******	Defini��es e Vari�veis Globais **************************
 */
#define NOSTR	(char *)NULL
#define	elif	else if
#define	_EOMEM	(char *)EOF

/*
 ******	Defini��o de vari�veis externas	*************************
 */
extern char	_sio1buf[], _sio2buf[];
extern int	_stdbuf;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void	_error (const char *);

/*
 ****************************************************************
 *	Escreve a �rea usada pela stdio				*
 ****************************************************************
 */
int
_writebuf (int c, FILE *fp)
{
	static char	nowrtbuf[_NFILE]; 
	int		n, rn;

	/*
	 *	Para o modo de linha, testa o seu final
	 */
	if (fp->_ptr < fp->_lend  &&  c != '\n')
		return (*fp->_ptr++ = c);

	/*
	 *	Verifica se o arquivo � de atualiza��o
	 */
	if (fp->_flag & _IORW)
		fp->_flag |= _IOWRITE;

	/*
	 *	Verifica se o arquivo � de escrita
	 */
	if ((fp->_flag & (_IOWRITE|_IOREAD)) != _IOWRITE)
		_error ("Escrevendo em arquivo de entrada\n");

	/*
	 *	Verifica se o arquivo � na realidade uma cadeia
	 */
	if (fp->_flag & _IOSTRG)
		{ fp->_flag |= _IOERR; return (EOF); }

	/*
	 *	Verifica se � a primeira utiliza��o da "putc"
	 */
	if (fp->_base == NOSTR)
	{
		if   (fp->_flag & _IONOBUF)
		{
		    noarea:
			fp->_base  = &nowrtbuf[fileno (fp)];
			fp->_bend  = fp->_base;
			fp->_bsize = 1;
			fp->_flag |= _IONOBUF;
		}
		elif (isatty (fileno (fp)))
		{
			fp->_bsize = BLSZ;

			if   (_stdbuf & 0x01)
				{ fp->_base = _sio1buf; _stdbuf &= ~0x01;  }
			elif (_stdbuf & 0x02)
				{ fp->_base = _sio2buf; _stdbuf &= ~0x02;  }
			elif ((fp->_base = malloc (fp->_bsize)) != NOSTR)
				fp->_flag |= _IOMYBUF;
			else
				goto noarea;

			fp->_flag |= _IOLNBUF;
			fp->_lend  = fp->_base + fp->_bsize;
		}
		else
		{
			fp->_bsize = BUFSIZ;

			if ((fp->_base = malloc (fp->_bsize)) != NOSTR)
				fp->_flag |= _IOMYBUF;
			else
				goto noarea;

			fp->_bend = fp->_base + fp->_bsize;

		}

		fp->_ptr = fp->_base;

	}	/* end if (fp->_base == NOSTR) */

	/*
	 *	Calcula o numero de bytes a escrever
	 */
	if (fp->_ptr == _EOMEM)
		fp->_ptr = fp->_base;

	n = fp->_ptr - fp->_base;

	/*
	 *   Escreve no arquivo
	 */
	if   (fp->_flag & _IONOBUF)		/* Arquivo sem �rea */
	{
		n = 1; rn = write (fileno (fp), (char *)&c, 1);
	}
	elif (fp->_flag & _IOLNBUF)		/* Arquivo com �rea de linha */
	{
		if (c == '\n' && fp->_ptr < fp->_lend)
		{
			/* '\n' foi escrito e o �rea n�o est� cheia */

			*fp->_ptr = c;
			rn = write (fileno (fp), fp->_base, ++n);
			fp->_ptr = fp->_base;
		}
		else
		{
			/* �rea cheia ou "c" � o primeiro caractere escrito */

			if (n > 0)
				rn = write (fileno (fp), fp->_base, n);
			else
				rn = 0;

			fp->_ptr = fp->_base;

			if (c == '\n' && rn == n)
			{
				/* c == '\n' com �rea cheia ser� escrito agora */

				n = 1; rn = write (fileno (fp), &c, n);
			}
			else
 			{
				/* c qualquer foi escrito ou c == '\n' foi	*/
				/* escrito com �rea cheia e houve erro no write */

				*fp->_ptr++ = c;
			}
		}
	}
	else					/* Arquivo com �rea normal */
	{
		if (n > 0)
			rn = write (fileno (fp), fp->_base, n);
		else
			rn = 0;

		fp->_ptr = fp->_base; *fp->_ptr++ = c;
	}

	/*
	 *    Erro na escrita
	 */
	if (rn != n)
		{ fp->_flag |= _IOERR; return (EOF); }

	return (c);

}	/* end _writebuf */
