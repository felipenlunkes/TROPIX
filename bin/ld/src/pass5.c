/*
 ****************************************************************
 *								*
 *			pass5.c					*
 *								*
 *	Passo 5: Gera as diversas se��es			*
 *								*
 *	Vers�o	1.0.0, de 23.10.86				*
 *		4.3.0, de 10.06.02				*
 *								*
 *	M�dulo: ld						*
 *		Utilit�rios b�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <a.out.h>

#include "../h/ld.h"

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
#define	REF_VEC_INCR	32		/* Incrementos para o vetor de refer�ncias */

/*
 ****** Vari�veis globais ***************************************
 */
entry const char 	*text_nm,	/* Nome do arquivo com as se��es "TEXT" */
			*data_nm,	/* Nome do arquivo com as se��es "DATA" */
			*rt_nm,		/* Nome do arquivo com a RT */
			*rd_nm;		/* Nome do arquivo com a RD */

entry int		aout_fd = -1,	/* Descritor do m�dulo final */
			text_fd,	/* Descritor do arquivo com as se��es "TEXT" */
			data_fd;	/* Descritor do arquivo com as se��es "DATA" */

entry FILE	 	*rt_fp,		/* Descritor do arquivo com a RT */
			*rd_fp;		/* Descritor do arquivo com a RD */

entry off_t		TEXT_REL_SIZE,	/* Tamanho da RT */
			DATA_REL_SIZE;	/* Tamanho da RD */

entry off_t		text_addr,	/* Endereco do "TEXT" do m�dulo atual */
			data_addr,	/* Endereco do "DATA" do m�dulo atual */
			bss_addr;	/* Endereco do "BSS"  do m�dulo atual */

entry off_t		text_rel,	/* Reloca��o para o "TEXT" */
			data_rel,	/* Reloca��o para o "DATA" */
			bss_rel;	/* Reloca��o para o "BSS"  */

entry int		external_reference_cnt; /* No. de s�mbolos externos */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		generate_module_sections (const MODULE *);
void 		relocate
		(	const char *,
			int,
			const char *,
			unsigned,
			off_t,
			unsigned,
			off_t,
			GSYM * const *,
			int,
			int,

			FILE *,
			off_t *,
			off_t *,

			off_t
		);
void		insert_external_reference (GSYM *gp, off_t offset);

/*
 ****************************************************************
 *	Passo 5: Gera as diversas se��es			*
 ****************************************************************
 */
void
pass5 (void)
{
	const MODULE	*mp;

	/*
	 *	Prepara os endere�o inicial
	 */
	text_addr = TEXT_ORG;
	data_addr = DATA_ORG;
	bss_addr  = BSS_ORG;

	if (mflag)
	{
		if (vflag)
			printf ("\n\n");

		/*
		 *	Imprime o Cabe�alho do Mapa
		 */
		printf
		( 	"---- TEXTO ----     "
			"---- DATA -----     "
			"----- BSS -----\n"
			"ENDERE�O  TAMAN     "
			"ENDERE�O  TAMAN     "
			"ENDERE�O  TAMAN     "
			"--- M�DULO ---  "
			"\n\n"
		);

		vflag = 0;
	}

	/*
	 *	Percorre a lista de m�dulos
	 */
	for (mp = modtb_list.m_next; mp != NOMODULE; mp = mp->m_next)
	{
		if (vflag)
			printf ("M�dulo: %s\n", mp->m_nm);

		if (mp->m_type == FMAGIC)
			generate_module_sections (mp);
	}

	/*
	 *	Imprime os totais
	 */
	if (mflag)
	{
		printf
		(	"\nTOTAIS: Text = %d, Data = %d, ",
			TEXT_SIZE, DATA_SIZE
		);
		printf
		(	"Bss = %d, Common = %d\n\n",
			BSS_SIZE, COMMON_SIZE
		);
	}

}	/* end pass5 */

/*
 ****************************************************************
 *	Carrega um m�dulo objeto				*
 ****************************************************************
 */
void
generate_module_sections (const MODULE *mp)
{
	const char	*nm = mp->m_nm;
	SYM		*sp;
	GSYM		**vp, *gp;
	off_t		rt_offset;
	GSYM		**vector_image = (GSYM **)NULL;
	int		vector_size, vector_elem = 0;
	static off_t	text_offset, data_offset;
	int		mod_fd;
	HEADER		h;
	void		*symtb_image = NOSYM;
	const SYM	*end_symtb_image = NOSYM;

	/*
	 *	Abre o m�dulo e le o seu cabe�alho
	 */
	if ((mod_fd = inopen (mp->m_dev, mp->m_ino)) < 0)
		{ error ("*@N�o consegui abrir \"%s\"", nm); return; }

	if (read (mod_fd, &h, sizeof (HEADER)) != sizeof (HEADER))
		{ error ("*@Erro na leitura do cabe�alho de \"%s\"", nm); close (mod_fd); return; }

	if (h.h_magic != FMAGIC)
		{ error ("@O m�dulo \"%s\" N�O � regular", nm); close (mod_fd); return; }

	/*
	 *	Calcula as constantes de reloca��o
	 */
	text_rel  = text_addr;
	data_rel  = data_addr - h.h_tsize;
	bss_rel   = bss_addr  - h.h_tsize - h.h_dsize;

	/*
	 *	Imprime a linha da tabela de m�dulos
	 */
	if (mflag)
	{
		printf
		(	"%P %5d     %P %5d     %P %5d     %s\n",
			text_addr, h.h_tsize,
			data_addr, h.h_dsize,
			bss_addr,  h.h_bsize,
			nm
		);
	}

	/*
	 *	Processa a tabela de s�mbolos
	 */
	if (h.h_ssize != 0)
	{
		/*
		 *	Le a tabela de s�mbolos
		 */
		symtb_image = alloca (h.h_ssize);

		lseek (mod_fd, h.h_tsize + h.h_dsize, SEEK_CUR);

		if (read (mod_fd, symtb_image, h.h_ssize) != h.h_ssize)
		{
			error ("*@Erro na leitura da tabela de s�mbolos de \"%s\"", nm);
			close (mod_fd); return;
		}

		end_symtb_image = symtb_image + h.h_ssize;

		/*
		 *	Aloca e zera uma �rea para o vetor de ponteiros para a SYMTB
		 */
		for (sp = symtb_image; sp < end_symtb_image; sp = SYM_NEXT_PTR (sp))
			vector_elem++;

		vector_size = vector_elem * sizeof (GSYM *);

		vector_image = vp = alloca (vector_size);

		memsetl (vector_image, 0, vector_size / sizeof (long));

		/*
		 *	Processa os S�mbolos
		 */
		for (sp = symtb_image; sp < end_symtb_image; sp = SYM_NEXT_PTR (sp), vp++)
		{
			/*
			 *	Escolhe os s�mbolos significativos
			 */
			switch (sp->s_type)
			{
			    case EXTERN|TEXT:
			    case EXTERN|DATA:
			    case EXTERN|BSS:
			    case EXTERN|ABS:
			    case EXTERN|UNDEF:
				break;

			    default:		/* Ignora os outros s�mbolos */
				continue;

			}	/* end switch */

			/*
			 *	Obt�m a entrada da SYMTB global
			 */
			if ((gp = hash (sp->s_name, sp->s_nm_len)) != NOGSYM)
				{ *vp = gp; continue; }

			error ("@ERRO INTERNO: N�o encontrei \"%s\" na tabela de s�mbolos", sp->s_name);

		}	/* end for */

	}	/* end if (h.h_ssize) */

	/*
	 *	Verifica se h� reloca��o para o TEXT
	 */
	rt_offset = sizeof (HEADER) + h.h_tsize + h.h_dsize + h.h_ssize;

	if (h.h_tsize != 0)
	{
		relocate
		(
			nm,
			mod_fd,
			"TEXT",
			h.h_tsize,
			sizeof (HEADER),
			h.h_rtsize,
			rt_offset,
			vector_image,
			vector_elem,
			text_fd,

			rt_fp,
			&TEXT_REL_SIZE,
			&text_offset,

			0
		);
	}

	/*
	 *	Verifica se h� reloca��o para o DATA
	 */
	if (h.h_dsize != 0)
	{
		relocate
		(
			nm,
			mod_fd,
			"DATA",
			h.h_dsize,
			sizeof (HEADER) + h.h_tsize,
			h.h_rdsize,
			rt_offset + h.h_rtsize,
			vector_image,
			vector_elem,
			data_fd,

			rd_fp,
			&DATA_REL_SIZE,
			&data_offset,

			TEXT_SIZE
		);
	}

	text_addr += h.h_tsize;
	data_addr += h.h_dsize;
	bss_addr  += h.h_bsize;

	/*
	 *	Fecha o arquivo
	 */
	close (mod_fd);

}	/* end generate_module_sections */

/*
 ****************************************************************
 *	Reloca uma Se��o					*
 ****************************************************************
 */
void
relocate
(
	const char	*mod_nm,	/* Nome do m�dulo */
	int		mod_fd,		/* Descritor do m�dulo */
	const char	*sec_nm,	/* Nome da se��o ("TEXT/DATA") */
	unsigned	sec_sz,		/* Tamanho da se��o a relocar */
	off_t		sec_off,	/* Deslocamento da se��o a relocar */
	unsigned	rel_sz,		/* Tamanho da reloca��o dada */
	off_t		rel_off,	/* Deslocamento da se��o de reloca��o */
	GSYM	* const vector[],	/* Endere�o do vetor de ponteiros */
	int		vector_elem,	/* N�mero de elementos do vetor */
	int		fd,		/* Descritor da se��o a gravar */

	FILE		*new_rel_fp,	/* Descritor do arquivo de reloca��o ("-r") */
	off_t		*new_rel_sz,	/* Tamanho da reloca��o gerada ("-r") */
	off_t		*new_rel_off,	/* Novo deslocamento ("-r") */

	off_t		a_out_off	/* Deslocamento do in�cio do objeto ("-h") */
)
{
	char		*sec_image;
	const char	*end_sec_image;
	void		*rel_image;
	const RELOC	*end_rel_image;

	GSYM		*gp;
	RELOC		*rp;
	long		r = 0;
	char		*bp;
	unsigned int	index;
	off_t		offset;
	char		write_rel = (rflag || bflag);

	/*
	 *	Aloca mem�ria e le a se��o indicada
	 */
	sec_image = alloca (sec_sz);

	lseek (mod_fd, sec_off, SEEK_SET);

	if (read (mod_fd, sec_image, sec_sz) != sec_sz)
		{ error ("*@Erro na leitura do %s do m�dulo \"%s\"", sec_nm, mod_nm); return; }

	end_sec_image = sec_image + sec_sz;

	/*
	 *	Verifica se h� reloca��o
	 */
	if (rel_sz != 0)
	{
		/*
		 *	Aloca mem�ria e le a reloca��o
		 */
		rel_image = alloca (rel_sz);

		lseek (mod_fd, rel_off, SEEK_SET);

		if (read (mod_fd, rel_image, rel_sz) != rel_sz)
			{ error ("*@Erro na leitura de R%c do m�dulo \"%s\"", *sec_nm, mod_nm); return; }

		end_rel_image = rel_image + rel_sz;

		/*
		 *	Realiza a Reloca��o
		 */
		for (rp = rel_image; rp < end_rel_image; rp++)
		{
			int		rel_len = rp->r_flags & RSZMASK;
			int		rel_seg = rp->r_flags & RSEGMASK;
			int		rel_code = 0;

			if ((offset = rp->r_pos) >= sec_sz)
			{
				error
				(	"@Posi��o %d de reloca��o inv�lido na "
					"se��o %s do m�dulo \"%s\"",
					offset, sec_nm, mod_nm
				);
				continue;
			}

			bp = sec_image + offset; gp = NOGSYM;

			/*
			 ****** Obtem o valor do elemento a ser relocado ****************
			 */
			switch (rel_len)
			{
			/*** case RBYTE: ***/
			   /***	r = *bp; ***/
			   /***	break; ***/

			    case RWORD:
				r = *((short *)bp);
				break;

			    case RLONG:
				r = *((long *)bp);
				break;

			    default:
				error
				(	"@Tamanho %04X de reloca��o inv�lido na "
					"se��o %s do m�dulo \"%s\"",
					rel_len, sec_nm, mod_nm
				);

			}	/* end switch (rel_len) */

			/*
			 ****** Obtem o novo valor do elemento **************************
			 */
			switch (rel_seg)
			{
			    case RTEXT:
				r += text_rel;
				break;

			    case RDATA:
				r += data_rel;
				break;

			    case RBSS:
				r += bss_rel;
				break;

			    case REXTREL:	/* "call" relativo ==> Muito sutil */
				r -= text_rel;
			    case REXT:
				if
				(	(index = rp->r_symbol) >= vector_elem ||
					(gp = vector[index]) == NOGSYM
				)
				{
					error
					(	"@�ndice %d de reloca��o inv�lido na "
						"se��o %s do m�dulo \"%s\"",
						index, sec_nm, mod_nm
					);
					continue;
				}

				/* Verifica o que fazer se o s�mbolo ainda n�o foi definido */

				if (IS_UNDEF_OR_COMMON (&gp->s))
				{
					rel_code = 1;	/* S�mbolo continua indefinido */

					if (shared_lib_given)
					{
						if (rel_len != RLONG) error
						(
							"@S�mbolo \"%s\" com reloca��o N�O longa na "
							"se��o %s do m�dulo \"%s\"",
							gp->s.s_name, sec_nm, mod_nm
						);

						insert_external_reference
						(	gp,
							a_out_off + *new_rel_off + offset
						);
					}

					break;
				}

				/* O S�mbolo j� foi definido */

				rel_code = 2;	/* S�mbolo definido */

				r += gp->s.s_value;

				break;

			    default:
				error
				(	"@Se��o %04X inv�lida de reloca��o na "
					"se��o %s do m�dulo \"%s\"",
					rel_seg, sec_nm, mod_nm
				);

			}	/* end switch (rel_seg) */

			/*
			 ****** Armazena o novo valor do elemento ***********************
			 */
			switch (rel_len)
			{
			/*** case RBYTE: ***/
			   /***	*bp = r; ***/
			   /***	break; ***/

			    case RWORD:
				*((short *)bp) = r;
				break;

			    case RLONG:
				*((long *)bp) = r;
				break;
			}

			/*
			 ****** Escreve a reloca��o (se for o caso) *********************
			 */
			if (!write_rel)
				continue;

			switch (rel_code)
			{
				/*
				 *	Reloca��o sem s�mbolo: Mant�m no mesmo estilo
				 */
			    case 0:
				break;

				/*
				 *	O s�mbolo continua indefinido: altera o n�mero do s�mbolo
				 */
			    case 1:
				rp->r_symbol = gp->s_index;
				break;

				/*
				 *	O s�mbolo foi definido
				 */
			    case 2:
				if (rel_seg == REXTREL)		/* REXTREL resolvido: N�o h� mais reloca��o */
					continue;

				/* S�mbolo definido: Transforma em reloca��o sem s�mbolo */

				rp->r_flags &= ~RSEGMASK;

				switch (gp->s.s_type)
				{
				    case EXTERN|ABS:		/* ABS resolvido: N�o h� mais reloca��o */
					continue;

				    case EXTERN|TEXT:
					rp->r_flags |= RTEXT;
					break;

				    case EXTERN|DATA:
					rp->r_flags |= RDATA;
					break;

				    case EXTERN|BSS:
					rp->r_flags |= RBSS;
					break;

				    default:
					error
					(	"@Tipo de s�mbolo %04X de reloca��o inv�lido na "
						"se��o %s do m�dulo \"%s\"",
						gp->s.s_type, sec_nm, mod_nm
					);

				}	/* end switch (gp->s.s_type) */

				rp->r_symbol = 0;

			}	/* end switch (rel_code) */

			rp->r_pos += *new_rel_off;

			if (fwrite (rp, sizeof (RELOC), 1, new_rel_fp) != 1)
				error ("*@Erro ao gravar R%c", *sec_nm);

			*new_rel_sz += sizeof (RELOC);

		}	/* end for */

	}	/* end if (rel_sz != 0) */

	/*
	 *	Escreve & libera o espaco reservado para a se��o
	 */
	if (write (fd, sec_image, sec_sz) != sec_sz)
		error ("*@Erro na escrita da se��o \"%s\"", sec_nm);

	*new_rel_off += sec_sz;

}	/* end relocate */

/*
 ****************************************************************
 *	Insere a reloca��o na tabela de refer�ncias externas	*
 ****************************************************************
 */
void
insert_external_reference (GSYM *gp, off_t offset)
{
	if (gp->s_ref_len >= gp->s_ref_sz)
	{
		gp->s_ref_sz += REF_VEC_INCR;

		if ((gp->s_ref_vec = realloc (gp->s_ref_vec, gp->s_ref_sz * sizeof (off_t *))) == NULL)
			error (NOSTR);
	}

	gp->s_ref_vec[gp->s_ref_len++] = offset;

	external_reference_cnt++;

}	/* end insert_external_reference */
