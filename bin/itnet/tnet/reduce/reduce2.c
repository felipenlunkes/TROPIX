/*
 ****************************************************************
 *								*
 *			reduce2.c				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.0, de 14.11.90				*
 *		3.0.0, de 14.05.95				*
 *								*
 *	M�dulo: TCMPTO_C/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stat.h>
#include <stdlib.h>
#include <time.h>

#include "../reduce.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry int	outfile_fd;	/* Arquivo de sa�da */

extern int	Bflag;		/* Debug */

#undef	CRC
#ifdef	CRC
extern int	crcflag;	/* N�o gera/confere CRCs */
#endif	CRC

extern long	in_cnt, out_cnt; /* Total de caracteres de entrada/sa�da */

extern int	code_area[8];	/* Cabem sempre 8 c�digos ainda de 16 bits */

entry CRCFILE	outcrcfile;	/* Bloco para STDOUT */

entry CODEFILE	incodefile;	/* Bloco para CODEIN */

entry COLFILE	incolfile;	/* COLFILE da cole��o */

/*
 ****** Par�metros de compress�o ********************************
 */
extern int	MAX_BIT_SZ;	/* O algoritmo funciona no m�ximo com 16 bits */ 

extern int	MAX_BIT_USED;	/* N�mero de bits realmente usados */ 

extern int	MAX_CODE;	/* Nunca pode usar este c�digo */

extern int	CODE_SOURCE;	/* Fonte de novos c�digos */

extern int	bit_sz;		/* Tamanho atual */

extern int	max_code;	/* �ltimo c�digo do tamanho atual */

/*
 ****************************************************************
 *	Expande um arquivo segundo o algoritmo LZW		*
 ****************************************************************
 */
off_t
unreduce (int fd)
{
	register int	K, omega_K, old_omega_K, orig_omega_K;
	register CODETB	*hp, *codetb;
	register char	*sp;
	register CRCFILE *fp1 = &outcrcfile;
	register CODEFILE *fp0 = &incodefile;
	int		CODESZ;
	static int	old_CODESZ = 0;
	static CODETB	*old_codetb;
	char		STACK[7000];

	/*
	 *	Inicializa os par�metros da expans�o
	 */
	CODE_SOURCE = FIRST_CODE;

   /***	MAX_BIT_SZ = ......;	/* Atribu�do em tcpto_s.c */

#ifdef	CRC
   /***	crcflag = ......;	/* Atribu�do em ... */
#endif	CRC

	MAX_CODE = BIT_SZ_TO_CODE (MAX_BIT_SZ);

	MAX_BIT_USED = MIN_BIT_SZ;

	CODESZ = (1 << MAX_BIT_SZ); 

	bit_sz = MIN_BIT_SZ;

	max_code = BIT_SZ_TO_CODE (MIN_BIT_SZ);

	outfile_fd = fd;

	in_cnt = 0;	out_cnt = 0;

	incolfile.i_ptr = incolfile.i_bend;

	outcrcfile.i_ptr = outcrcfile.i_base;

	fp0->c_ptr = fp0->c_bend;	/* Abandona */

	if (Bflag)
	{
		error
		(	"MAX_BIT_SZ = %d, CODESZ = %d, codetbsz = %d", 
			MAX_BIT_SZ, CODESZ, CODESZ * sizeof (CODETB)
		);
	}

	/*
	 *	Aloca mem�ria para a tabela CODE
	 */
	if (CODESZ > old_CODESZ)
	{
		if (old_CODESZ != 0)
			free (old_codetb);

		if ((codetb = malloc (CODESZ * sizeof (CODETB))) == NOCODETB)
			error ("$N�o consegui alocar mem�ria para a tabela CODE");

		old_codetb = codetb;	  old_CODESZ = CODESZ;
	}
	else
	{
		codetb = old_codetb;
	}

	/*
	 *	Realiza a expans�o
	 */
	K = old_omega_K = GETCODE ();

	if (old_omega_K == max_code)
		return (out_cnt);

	PUTCHAR (K);

	sp = STACK;

	while ((omega_K = GETCODE ()) != max_code)
	{
		/*
		 *	Verifica se � o c�digo de controle
		 */
		if (omega_K == CONTROL_CODE)
		{
			fp0->c_ptr = fp0->c_bend;	/* Abandona */

			bit_sz = MIN_BIT_SZ;
			max_code = BIT_SZ_TO_CODE (MIN_BIT_SZ);

			if (Bflag)
			{
				error
				(	"Modificando o c�digo para %2d bits",
					bit_sz
				);
			}

			CODE_SOURCE = FIRST_CODE - 1;

			if ((omega_K = GETCODE ()) == max_code)
				break;
		}

		orig_omega_K = omega_K;

		/*
		 *	Caso especial (KwKwK)
		 */
		if (omega_K >= CODE_SOURCE)
		{
			if (omega_K >= MAX_CODE)
			{
				error
				(	"$ERRO: c�digo inv�lido: "
					"(%d, %d)",
					omega_K, MAX_CODE
				);
			}

			*sp++ = K;
			omega_K = old_omega_K;
		}

		/*
		 *	Decodifica e empilha os caracteres
		 */
		while (omega_K >= FIRST_CODE) 
		{
			hp = &codetb[omega_K];

			*sp++ = hp->h_K;
			omega_K = hp->h_omega;
		}

		K = omega_K;	*sp++ = K;

		/*
		 *	Emite os caracteres da pilha
		 */
		while (sp > STACK)
			PUTCHAR (*--sp);

		/*
		 *	Insere a cadeia omega_K nova na tabela
		 */
		if (CODE_SOURCE < MAX_CODE)
		{
			hp = &codetb[CODE_SOURCE++];

			hp->h_K = K;
			hp->h_omega = old_omega_K;
		}

		old_omega_K = orig_omega_K;

	}	/* end loop GETCODE */

	/*
	 *	Emite o �ltimo bloco (flush)
	 */
	writeblock (0, fp1);

	return (out_cnt);

}	/* end unreduce */

/*
 ****************************************************************
 *	Le um bloco de c�digos 					*
 ****************************************************************
 */
int
readcode (register CODEFILE *fp)
{
	register int	r;

	/*
	 *	Verifica se � a primeira utiliza��o da GETCODE
	 */
	if (fp->c_base == NOCODEP)
		fp->c_base = code_area;

	/*
	 *	Verifica se deve mudar o tamanho do c�digo
	 */
	if (CODE_SOURCE + NC > max_code  &&  bit_sz < MAX_BIT_SZ)
	{
		bit_sz++;

		if (bit_sz > MAX_BIT_USED)
			MAX_BIT_USED = bit_sz;

		max_code = BIT_SZ_TO_CODE (bit_sz);

		if (Bflag)
		{
			error
			(	"Modificando o c�digo para %2d bits",
				bit_sz
			);
		}
	}

	/*
	 *	Le um registro
	 */
	if ((r = fillcode ()) <= 0)
	{
		error ("EOF prematuro do arquivo compactado");
		return (max_code);
	}

	fp->c_ptr = fp->c_base;

	fp->c_bend = fp->c_base + r;

	return (*fp->c_ptr++);

}	/* end readcode */

/*
 ****************************************************************
 *	Confere o CRC e escreve um bloco do arquivo 		*
 ****************************************************************
 */
void
writeblock (unsigned char c, register CRCFILE *fp)
{
	register int	n;

	/*
	 *	Verifica se � a primeira utiliza��o da putc
	 */
	if (fp->i_base == NOSTR)
	{
		/*
		 *	A primeira utiliza��o da putc
		 */
		if ((fp->i_base = malloc (BLSZ + CRCSZ)) == NOSTR)
			error ("$N�o consegui alocar mem�ria para a �rea de sa�da");

		fp->i_bend = fp->i_base + BLSZ;

#ifdef	CRC
		if (!crcflag)
			fp->i_bend += CRCSZ;
#endif	CRC

		fp->i_ptr = fp->i_base;

		n = 0;
	}
	else
	{
		n = fp->i_ptr - fp->i_base;

#ifdef	CRC
		/*
		 *	Verifica o CRC
		 */
		if (!crcflag)
		{
			rn  =  (int)*--fp->i_ptr;
			rn |= ((int)*--fp->i_ptr << 8);

			n -= CRCSZ;

			if (rn != crc16 (fp->i_base, n))
				error ("Erro de CRC aos %d bytes", out_cnt);
		}
#endif	CRC
	}

	/*
	 *   Processa o bloco
	 */
	if (n > 0  &&  write (outfile_fd, fp->i_base, n) != n)
		error ("$*Erro de escrita no disco");

	fp->i_ptr = fp->i_base;

	*fp->i_ptr++ = c;

	out_cnt += n;

}	/* end writeblock */
