/*
 ****************************************************************
 *								*
 *			gif.c					*
 *								*
 *	Converte a imagem para o formato GIF			*
 *								*
 *	Vers�o	4.5.0, de 31.12.03				*
 *		4.5.0, de 18.01.04				*
 *								*
 *	M�dulo: xmandel						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <X11/Intrinsic.h>

#include "../h/xmandel.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry const char	*file_nm = "/tmp/a.gif";

entry FILE		*file_fp;

#define	putW(c, fp)	putc (c, fp); putc (c >> 8, fp)

/*
 ****** Par�metros de compress�o ********************************
 */
enum
{
	MIN_BIT_SZ =	9,		/* O algoritmo come�a com 9 bits */ 
	MAX_BIT_SZ =	12		/* LZW para GIF somente at� 12 bits */
};

enum {	HASHSZ     =	4919 };		/* Para 12 bits */

enum
{
	CLEAR_CODE =	256,		/* Reinicializa a compress�o */
	EOF_CODE   =	257,		/* Final da Imagem */
	FIRST_CODE =	258		/* C�digo inicial */
};

enum {	TEST_INTERVAL =	10000 };	/* A cada intervalo, examina a performance */

#define BIT_SZ_TO_CODE(sz) ((1 << sz) - 1) /* Calcula o c�digo m�ximo */

/*
 ****** Estrutura da tabela HASH ********************************
 */
typedef struct
{
	ushort	h_omega;		/* Cadeia prefixo, ... */
	char	h_K;			/* que adicionada com este caracter, ... */
	ushort	h_omega_K;		/* gera este c�digo */

}	HASHTB;

enum {	NOCODE	=	0xFFFF };	/* O �ltimo c�digo == n�o-cadeia */

#define NOHASHTB (HASHTB *)NULL

/*
 ******	Vari�veis globais ***************************************
 */
entry int	MAX_CODE;		/* Nunca pode usar este c�digo */

entry int	CODE_SOURCE;		/* Fonte de novos c�digos */

entry int	TEST_POINT;		/* Pr�ximo teste de performance */

entry HASHTB	*hashtb;

entry int	bit_sz;			/* Tamanho atual */

entry int	max_code;		/* �ltimo c�digo do tamanho atual */

extern FILE	*file_fp;

entry int	clear_flg;

entry long	in_cnt, out_cnt;	/* Total de caracteres de entrada/sa�da */

/*
 ******	�rea de sa�da *******************************************
 */
enum {	CODE_AREA_SZ =	255 };		/* Defini��o do GIF */

entry char		code_area[CODE_AREA_SZ];

entry char		*code_area_ptr;
	
entry const char	*end_code_area = &code_area[CODE_AREA_SZ];

entry unsigned int	output_bit_area;

entry int		output_bit_count;

/*
 ******	Defini��es de DEBUG *************************************
 */
#undef	ANALYSIS_DEBUG

#undef	CODE_DEBUG
#ifdef	CODE_DEBUG
entry FILE	*code_fp;
#endif	CODE_DEBUG

#undef	INDEX_DEBUG
#ifdef	INDEX_DEBUG
entry FILE	*index_fp;

entry int	total_index;
#endif	INDEX_DEBUG

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		GETCHAR (void);
void		PUTCODE (int code);
void		analysis (void);
char		*editpercent (int, char *area);
int		getpercent (long, long);

/*
 ****************************************************************
 *	Gera o arquivo GIF					*
 ****************************************************************
 */
void
generate_gif_file (int value)
{
	FILE			*fp;
	const ulong		*mp, *end_mp;
	ulong			pixel;
	char			area[64];
	int			len;
	IMAGE_PARAM		*ip = image_param_ptr;

	/*
	 *	Abre o arquivo
	 */
	if (file_fp != NOFILE)
		fclose (file_fp);

	if ((fp = fopen (file_nm, "w")) == NOFILE)
		{ draw_error_msg_text ("N�o consegui criar \"%s\"\n", file_nm); return; }

	file_fp = fp;

	/*
	 *	Escreve o Primeiro Cabe�alho
	 */
	fprintf (fp, "GIF89a");

	putW (MANDEL_WIDTH, fp);		/* logical screen width */
	putW (MANDEL_HEIGHT, fp);		/* logical screen height */

	putc ((0x80 | (7 << 4) | 7), fp);	/* global color table flag */
						/* color resolution */
						/* sort flag */
						/* sizeof global color table */

	putc (0, fp);				/* back ground color index */
	putc (0, fp);				/* pixel aspect ratio */

	/*
	 *	Escreve o Mapa de cores
	 */
	for (mp = gif_col_vector, end_mp = mp + 256; mp < end_mp; mp++)
	{
		pixel = mp[0];

		putc ((pixel >> 16), fp);
		putc ((pixel >> 8), fp);
		putc ((pixel), fp);
	}

	/*
	 *	Escreve o Segundo Cabe�alho
	 */
	putc (',', fp);				/* Image Separator */

	putW (0, fp);				/* Image Left Position */
	putW (0, fp);				/* Image Top Position */
	putW (MANDEL_WIDTH, fp);		/* Image width */
	putW (MANDEL_HEIGHT, fp);		/* Image height */

	putc (0, fp);				/* Local color table flag */
						/* Interface Flag */
						/* Reserved */
						/* Size of Local Color Table */


	fflush (fp);

	/*
	 *	Gera o LZW da imagem propriamente dita
	 */
	putc (8, fp);				/* LZW Code size */

	reduce ();

	/*
	 *	Coloca um coment�rio
	 */
	putc ('!', fp);				/* Comment Extension */
	putc (0xFE, fp);

	len = snprintf (area, sizeof (area), "[%G, %G, %G]", ip->i_CENTER_X, ip->i_CENTER_Y, ip->i_SIZE_X);

	putc (len, fp); fprintf (fp, "%s", area);

	putc (0, fp);

	/*
	 *	O Final do arquivo GIF
	 */
	putc (';', fp);				/* Trailer */

	/*
	 *	Escreve a mensagem
	 */
	draw_msg_text
	(	"[%G, %G, %G], %dx%d, arquivo \"%s\" com %d bytes",
		ip->i_CENTER_X, ip->i_CENTER_Y, ip->i_SIZE_X,
		MANDEL_WIDTH, MANDEL_HEIGHT,
		file_nm, ftell (fp)
	);

	fclose (fp);

}	/* end generate_gif_file */

/*
 ****************************************************************
 *	Comprime um arquivo segundo o algoritmo LZW		*
 ****************************************************************
 */
void
reduce (void)
{
	int		omega, K, i, bit_shift;
	HASHTB		*hp;

#ifdef	CODE_DEBUG
	code_fp = fopen ("/tmp/o.code", "w");
#endif	CODE_DEBUG

#ifdef	INDEX_DEBUG
	index_fp = fopen ("/tmp/o.index", "w");
#endif	INDEX_DEBUG

	/*
	 *	Inicializa os par�metros para a compress�o
	 */
	CODE_SOURCE	= FIRST_CODE;

	TEST_POINT	= (lzw_mode == LZW_PORTABLE) ? 0 : /* LZW_COMPACT */ TEST_INTERVAL;

	bit_sz		= MIN_BIT_SZ;

	max_code	= BIT_SZ_TO_CODE (MIN_BIT_SZ);

	MAX_CODE	= BIT_SZ_TO_CODE (MAX_BIT_SZ);

	bit_shift	= MAX_BIT_SZ - 8;

	code_area_ptr	= code_area;
	
	output_bit_area	= 0;

	output_bit_count = 0;


	in_cnt		= 0;
	out_cnt		= 0;

	clear_flg	= 0;

	/*
	 *	Aloca mem�ria para a tabela HASH 
	 */
	if (hashtb == NOHASHTB && (hashtb = malloc (HASHSZ * sizeof (HASHTB))) == NOHASHTB)
	{
		draw_error_msg_text ("N�o consegui alocar mem�ria para a tabela HASH");
		return;
	}

	/*
	 *	Inicializa a tabela HASH
	 */
	for (hp = &hashtb[HASHSZ - 1]; hp >= hashtb; hp--)
		hp->h_omega = NOCODE;

	/*
	 *	Realiza a compress�o
	 */
	PUTCODE (CLEAR_CODE);

	omega = GETCHAR ();

	while ((K = GETCHAR ()) >= 0)	/* != EOF */
	{
		/*
		 *	Calcula a primeira tentativa HASH
		 */
		i = (K << bit_shift) ^ omega; hp = &hashtb[i];

		/*
		 *	Achou na tabela
		 */
		if (hp->h_omega == omega && hp->h_K == K)
			{ omega = hp->h_omega_K; continue; }

		/*
		 *	O c�digo ainda n�o se encontra na tabela
		 */
		if (hp->h_omega == NOCODE)
		{
		    not_found:
			PUTCODE (omega);

			if   (CODE_SOURCE <= MAX_CODE)
			{
				hp->h_omega	= omega;
				hp->h_K		= K;
				hp->h_omega_K	= CODE_SOURCE++;
			}
			elif (in_cnt >= TEST_POINT)
			{
				analysis ();
			}

		 	omega = K;

			continue;
		}
	
		/*
		 *	Colis�o (sup�e que a tabela nunca esteja cheia)
		 */
		if (i == 0)
			i = 1;
		else
			i = HASHSZ - i;

		for (EVER)
		{
			if ((int)(hp -= i) < (int)hashtb)
				hp += HASHSZ;

			if (hp->h_omega == omega && hp->h_K == K)
				{ omega = hp->h_omega_K; break; }

			if (hp->h_omega == NOCODE)
				goto not_found;

		}	/* end loop de colis�o */

	}	/* end loop GETCHAR () */

	/*
	 *	Coloca o �ltimo c�digo, final e d� flush
	 */
	PUTCODE (omega);

	if (CODE_SOURCE <= MAX_CODE)
		CODE_SOURCE++;

	PUTCODE (EOF_CODE);

	PUTCODE (-1);

#ifdef	INDEX_DEBUG
	fclose (index_fp);

	fprintf (stderr, "Foram gerados %d �ndices\n", total_index);
#endif	INDEX_DEBUG

}	/* end reduce */

/*
 ****************************************************************
 *	Analisa a performance da compress�o			*
 ****************************************************************
 */
void
analysis (void)
{
	HASHTB		*hp;
	int		comp_factor;
	static int	old_comp_factor = 0;
	static int	old_in_cnt, old_out_cnt;

	/*
	 *	Verifica se esvaziar a tabela ao ficar cheia
	 */
	if (lzw_mode == LZW_PORTABLE)
	{
		for (hp = &hashtb[HASHSZ - 1]; hp >= hashtb; hp--)
			hp->h_omega = NOCODE;

		clear_flg = 1;

		CODE_SOURCE = FIRST_CODE;

		PUTCODE (CLEAR_CODE);

		return;
	}

	/*
	 *	Calcula o novo fator de compress�o
	 */
	TEST_POINT = in_cnt + TEST_INTERVAL;

	comp_factor = getpercent ((in_cnt - old_in_cnt) - (out_cnt - old_out_cnt), in_cnt - old_in_cnt);

	old_in_cnt = in_cnt; old_out_cnt = out_cnt;

#ifdef	ANALYSIS_DEBUG
	{
		char		old_area[8], area[8];
		int		hash_cnt = 0;

		fprintf
		(	stderr,
			"Ponto de an�lise: Entrada = %d bytes, Compress�o = %s %%, anterior = %s %%\n",
			in_cnt, editpercent (comp_factor, area), editpercent (old_comp_factor, old_area)
		);

		for (hp = &hashtb[HASHSZ - 1]; hp >= hashtb; hp--)
		{
			if (hp->h_omega != NOCODE)
				hash_cnt++;
		}

		fprintf
		(	stderr, "HASH = %s ocupada (%d, %d)\n",
			editpercent (getpercent (hash_cnt, HASHSZ), area),
			hash_cnt, HASHSZ
		);
	}
#endif	ANALYSIS_DEBUG

	/*
	 *	Compara os fatores
	 */
	if (comp_factor > old_comp_factor)
	{
		/* Est� melhorando - n�o mexe */

		old_comp_factor = comp_factor;
	}
	else
	{
		/* Piorou - recome�a de MIN_BIT_SZ bits */

		for (hp = &hashtb[HASHSZ - 1]; hp >= hashtb; hp--)
			hp->h_omega = NOCODE;

		old_comp_factor = 0;

		clear_flg = 1;

		CODE_SOURCE = FIRST_CODE;

		PUTCODE (CLEAR_CODE);
	}

}	/* end analysis */

/*
 ****************************************************************
 *	Obt�m um caractere de entrada				*
 ****************************************************************
 */
int
GETCHAR (void)
{
	int		count, index;

	if (in_cnt >= MANDEL_WIDTH * MANDEL_HEIGHT)
		return (EOF);

	count = count_matrix[in_cnt];

	if (count == 0 || count >= 1024)
		index = 0;
	else
		index = (count << color_index_shift) % 255 + 1;

	in_cnt++;

#ifdef	INDEX_DEBUG
	fprintf (index_fp, "index = %d\n", index);

	total_index++;
#endif	INDEX_DEBUG

	return (index);

}	/* end GETCHAR */

/*
 ****************************************************************
 *	Emite um c�digo						*
 ****************************************************************
 */
void
PUTCODE (int code)
{
	FILE		*fp = file_fp;
	int		count;

	/*
	 *	Emite um c�digo
	 */
	if (code >= 0)
	{
		output_bit_area |= (code << output_bit_count);

		output_bit_count += bit_sz;

		while (output_bit_count >= 8)
		{
			*code_area_ptr++ = output_bit_area;

			output_bit_area >>= 8;
			output_bit_count -= 8;

			if (code_area_ptr >= end_code_area)
			{
				putc (CODE_AREA_SZ, fp);

				fwrite (code_area, 1, CODE_AREA_SZ, fp);

				code_area_ptr = code_area;
			}
		}

		/*
		 *	Verifica se est� na hora de aumentar o tamanho do c�digo
		 */
		if ((CODE_SOURCE > max_code  &&  bit_sz < MAX_BIT_SZ) || clear_flg > 0)
		{
#ifdef	ANALYSIS_DEBUG
			fprintf
			(	stderr,
				"Ponto de mudan�a: "
				"code = %d, bit_sz = %d, bit_count = %d, clear_flg = %d\n",
				old_code, bit_sz, bit_count, clear_flg
			);
#endif	ANALYSIS_DEBUG

			if (clear_flg)
				{ bit_sz = MIN_BIT_SZ; clear_flg = 0; }
			else
				bit_sz++;

			max_code = BIT_SZ_TO_CODE (bit_sz);
		}
	}
	else		/* EOF => Emite os bits restantes */
	{
		if (output_bit_count > 0)
		{
			*code_area_ptr++ = output_bit_area;

		   /***	output_bit_area >>= 8;	***/
		   /***	output_bit_count -= 8;	***/

			count = code_area_ptr - code_area;

			putc (count, fp);

			fwrite (code_area, 1, count, fp);
		}

		putc (0, fp);			/* Bloco terminador */
	}

}	/* end PUTCODE */

#ifdef	ANALYSIS_DEBUG
/*
 ****************************************************************
 *	Edita uma percentagem					*
 ****************************************************************
 */
char *
editpercent (int quoc, char *area)
{
	char		*sinal;

	if (quoc < 0)
		{ sinal = "-"; quoc = -quoc; }
	else
		sinal = "";

	sprintf (area, "%s%d.%02d", sinal, quoc / 100, quoc % 100);
	
	return (area);

}	/* end editpercent */
#endif	ANALYSIS_DEBUG

/*
 ****************************************************************
 *	Calcula uma percentagem					*
 ****************************************************************
 */
int
getpercent (long numer, long denom)
{
	int		quoc;

	/*
	 *	Tenta evitar overflow
	 */
	if (numer > (0x7FFFFFFF / 10000))
		quoc = numer / (denom / 10000);
	else
		quoc = 10000 * numer / denom;

	return (quoc);

}	/* end percent */
