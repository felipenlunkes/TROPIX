/*
 ****************************************************************
 *								*
 *			reduce2.c				*
 *								*
 *	Comprime um arquivo segundo o algoritmo LZW		*
 *								*
 *	Vers�o	2.3.00, de 27.08.90				*
 *		3.1.06, de 04.05.97				*
 *								*
 *	M�dulo: GAR						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
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

#include "../h/common.h"
#include "../h/gar.h"
#include "../h/reduce.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry void	(*function) ();	/* Fun��o a executar para cada bloco */

entry CRCFILE	outcrcfile;	/* Bloco para STDOUT */

entry CODEFILE	incodefile;	/* Bloco para CODEIN */

entry COLFILE	incolfile;	/* COLFILE da cole��o */

entry off_t	col_size;	/* Tamanho do arquivo comprimido na cole��o */ 

entry int	file_block;	/* No. do bloco do arquivo na cole��o */ 

/*
 ****************************************************************
 *	Expande um arquivo segundo o algoritmo LZW		*
 ****************************************************************
 */
off_t
unreduce (void (*f) ())
{
	int		K, omega_K, old_omega_K, orig_omega_K;
	CODETB		*hp, *codetb;
	char		*sp;
	CRCFILE		*fp1 = &outcrcfile;
	CODEFILE	*fp0 = &incodefile;
	int		CODESZ;
#if (0)	/*************************************/
	static int	old_CODESZ = 0;
	static CODETB	*old_codetb;
#endif	/*************************************/
	char		STACK[7000];

	/*
	 *	Inicializa os par�metros da expans�o
	 */
	CODE_SOURCE = FIRST_CODE;

   /***	MAX_BIT_SZ = ......;	/* Atribu�do em in.c */

   /***	crc_flag = ......;	/* Atribu�do em in.c */

	MAX_CODE = BIT_SZ_TO_CODE (MAX_BIT_SZ);

	CODESZ = (1 << MAX_BIT_SZ); 

	bit_sz = MIN_BIT_SZ;

	max_code = BIT_SZ_TO_CODE (MIN_BIT_SZ);

	function = f;

	out_cnt = 0;

	incolfile.i_ptr = incolfile.i_bend;

	col_size = khead.k_size;

	file_block = 0;

	outcrcfile.i_ptr = outcrcfile.i_base;

	fp0->c_ptr = fp0->c_bend;	/* Abandona */

	if (Gflag)
	{
		fprintf
		(	stderr,
			"MAX_BIT_SZ = %d, CODESZ = %d, codetbsz = %d\n", 
			MAX_BIT_SZ, CODESZ, CODESZ * sizeof (CODETB)
		);
	}

	/*
	 *	Aloca mem�ria para a tabela CODE
	 */
	if ((codetb = malloc (CODESZ * sizeof (CODETB))) == NOCODETB)
	{
		msg ("N�o consegui alocar mem�ria para a tabela CODE");
		quit (1);
	}

#if (0)	/*************************************/
	codetb = alloca (CODESZ * sizeof (CODETB));

	codetb[0].h_omega = 0;		/* Aloca a mem�ria na STACK */
#endif	/*************************************/

#if (0)	/*************************************/
	if (CODESZ > old_CODESZ)
	{
		if (old_CODESZ != 0)
			free (old_codetb);

		if ((codetb = malloc (CODESZ * sizeof (CODETB))) == NOCODETB)
		{
			msg ("N�o consegui alocar mem�ria para a tabela CODE");
			quit (1);
		}

		old_codetb = codetb;	  old_CODESZ = CODESZ;
	}
	else
	{
		codetb = old_codetb;
	}
#endif	/*************************************/

	/*
	 *	Realiza a expans�o
	 */
	K = old_omega_K = GETCODE ();

	if (old_omega_K == max_code)
	{
	   	free (codetb);
		return (out_cnt);
	}

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

			if (Gflag)
			{
				fprintf
				(	stderr,
					"Modificando o c�digo para %2d bits\n",
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
				msg
				(	"***** ERRO: c�digo inv�lido: "
					"(%d, %d)\n",
					omega_K, MAX_CODE
				);
				quit (1);
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

   	free (codetb);

	return (out_cnt);

}	/* end unreduce */

/*
 ****************************************************************
 *	Le um bloco de c�digos 					*
 ****************************************************************
 */
int
readcode (CODEFILE *fp)
{
	int		r;

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

		max_code = BIT_SZ_TO_CODE (bit_sz);

		if (Gflag)
		{
			fprintf
			(	stderr,
				"Modificando o c�digo para %2d bits\n",
				bit_sz
			);
		}
	}

	/*
	 *	Le um registro
	 */
	if ((r = fillcode ()) <= 0)
	{
		msg ("EOF prematuro do arquivo compactado");
		return (max_code);
	}

	fp->c_ptr = fp->c_base;

	fp->c_bend = fp->c_base + r;

	return (*fp->c_ptr++);

}	/* end readcode */

/*
 ****************************************************************
 *	Le um bloco da cole��o e confere o CRC			*
 ****************************************************************
 */
int
readcol (COLFILE *fp)
{
	int		cnt;
	char		crc[8];

	/*
	 *	Verifica se � a primeira utiliza��o da GETC
	 */
	if (fp->i_base == NOSTR && (fp->i_base = malloc (BLSZ + CRCSZ)) == NOSTR)
	{
		msg ("N�o consegui alocar mem�ria para a �rea de entrada");
		quit (1);
	}

	/*
	 *	Le um bloco
	 */
	cnt = MIN (col_size, BLSZ);

	bread (fp->i_base, cnt);

	col_size -= cnt;

	bread (crc, sizeof (crc) );

	if (atoi (crc) != crc16 (fp->i_base, cnt) )
	{
		msg ("Erro de crc no bloco %d", file_block);
	}

	file_block++;

   /***	in_cnt += cnt; ***/

	/*
	 *	Prepara os ponteiros
	 */
	fp->i_ptr = fp->i_base;

	fp->i_bend = fp->i_base + cnt;

	return (*fp->i_ptr++);

}	/* end readcol */

/*
 ****************************************************************
 *	Confere o CRC e escreve um bloco do arquivo 		*
 ****************************************************************
 */
void
writeblock (unsigned char c, CRCFILE *fp)
{
	int		n, rn;

	/*
	 *	Verifica se � a primeira utiliza��o da putc
	 */
	if (fp->i_base == NOSTR)
	{
		/*
		 *	A primeira utiliza��o da putc
		 */
		if ((fp->i_base = malloc (BLSZ + CRCSZ)) == NOSTR)
		{
			msg ("N�o consegui alocar mem�ria para a �rea de sa�da");
			quit (1);
		}

		fp->i_bend = fp->i_base + BLSZ;

		if (!crcflag)
			fp->i_bend += CRCSZ;

		fp->i_ptr = fp->i_base;

		n = 0;
	}
	else
	{
		n = fp->i_ptr - fp->i_base;

		/*
		 *	Verifica o CRC
		 */
		if (!crcflag)
		{
			rn  =  (int)*--fp->i_ptr;
			rn |= ((int)*--fp->i_ptr << 8);

			n -= CRCSZ;

			if (rn != crc16 (fp->i_base, n))
				msg ("***** Erro de CRC aos %d bytes\n", out_cnt);
		}

	}

	/*
	 *   Processa o bloco
	 */
	if (n > 0)
		(*function) (fp->i_base, n);

	fp->i_ptr = fp->i_base;

	*fp->i_ptr++ = c;

	out_cnt += n;

}	/* end writeblock */
