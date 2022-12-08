/*
 ****************************************************************
 *								*
 *			pass1.c					*
 *								*
 *	Passo 1: Monta a Tabela Global de S�mbolos		*
 *								*
 *	Vers�o	1.0.0, de 14.04.87				*
 *		4.3.0, de 05.07.02				*
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
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <a.out.h>

#include "../h/ld.h"

/*
 ****************************************************************
 *	Defini��es locais					*
 ****************************************************************
 */

/*
 ******	Vari�veis globais ***************************************
 */
entry off_t	TEXT_SIZE,	/* Tamanho do "TEXT" */
		DATA_SIZE,	/* Tamanho do "DATA" */
		BSS_SIZE,	/* Tamanho do "BSS" */
		COMMON_SIZE,	/* Tamanho do "COMMON" */
		SYMTB_SIZE;	/* Tamanho da SYMTB */

/*
 ******	Vari�veis das bibliotecas *******************************
 */
const char		* const dir_list[] =
{
		"/lib/lib",		/* Lista de diret�rios de bibliotecas */
		"/usr/lib/lib",
		"/usr/xwin/lib/lib",
		NOSTR
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		analyse_and_proc_file (const char *);
void		reg_lib_get_LIBSYM (const char *lib_nm);
int		ftw_function (const char *mod_nm, STAT *sp, int type);
void		get_shared_library_symbol_table (const char *lib_nm, int fd, const HEADER *hp);

/*
 ****************************************************************
 *	Passo 1: Monta a Tabela Global de S�mbolos		*
 ****************************************************************
 */
void
pass1 (const char *argv[])
{
	/*
	 *	Processa a lista de arquivos
	 */
	for (/* vazio */; *argv != NOSTR; argv++)
	{
		analyse_and_proc_file (*argv);
	}

}	/* end pass1 */

/*
 ****************************************************************
 *	Determina o tipo do arquivo				*
 ****************************************************************
 */
void
analyse_and_proc_file (const char *nm)
{
	int		fd;
	const char	* const *cpp;
	const MODULE	*mp;
	STAT		s;
	HEADER		h;
	char		*lib_nm;

	/*
	 *	Se o nome for do formato "-lxxx", percorre os diret�rios
	 */
	if (nm[0] == '-' && nm[1] == 'l')
	{
		for (cpp = dir_list; /* abaixo */; cpp++)
		{
			if (*cpp == NOSTR)
			{
				error ("*@N�o consegui encontrar \"lib%s\" em nenhum dos diret�rios", nm + 2);
				return;
			}

			lib_nm = alloca (strlen (*cpp) + strlen (nm) + 2);

			strcpy (lib_nm, *cpp); strcat (lib_nm, nm + 2);

			if (stat (lib_nm, &s) >= 0)
				{ nm = lib_nm; break; }
		}
	}
	elif (stat (nm, &s) < 0)
	{
		error ("*@N�o consegui obter o estado de \"%s\"", nm);
		return;
	}

	/*
	 *	Verifica se � uma biblioteca regular
	 */
	if (S_ISDIR (s.st_mode))
	{
		if (bflag) 		/* � para gerar uma biblioteca compartilhada */
		{
			if (ftw (nm, ftw_function) < 0)
				error ("@A fun��o \"ftw\" devolveu um valor negativo");
		}
		else
		{
			reg_lib_get_LIBSYM (nm);
		}

		return;
	}

	/*
	 *	Abre o arquivo (m�dulo regular ou biblioteca compartilhada)
	 */
	if ((fd = inopen (s.st_dev, s.st_ino)) < 0)
		{ error ("*@N�o consegui abrir \"%s\"", nm); return; }

	/*
	 *	Le o cabe�alho e verifica o n�mero m�gico
	 */
	if (read (fd, &h, sizeof (HEADER)) != sizeof (HEADER))
		{ error ("*@Erro na leitura do cabe�alho de \"%s\"", nm); goto bad; }

	if (h.h_machine != 0x486)
		{ error ("@O m�dulo objeto \"%s\" N�O � para a linha INTEL x86", nm); goto bad; }

	switch (h.h_magic)
	{
	    case FMAGIC:
		if (vflag)
			printf ("M�dulo \"%s\"\n", nm);

		mp = put_module (nm, FMAGIC, s.st_dev, s.st_ino, &h);

		install_mod_symbols (mp, fd, &h, 'R' /* M�dulo regular */);

		close (fd);
		return;

	    case SMAGIC:
		if (vflag)
			printf ("Biblioteca compartilhada \"%s\"\n", nm);

		if (bflag)
			{ error ("@Biblioteca compartilhada \"%s\" dada como fonte de outra?", nm); goto bad; }

		put_module (nm, SMAGIC, s.st_dev, s.st_ino, &h);

		shared_lib_given = 1;	/* H� bibliotecas compartilhadas */

		close (fd);
		return;

	    default:
		error ("@O arquivo \"%s\" n�o � um m�dulo objeto", nm);
		break;

	}	/* end switch */

	/*
	 *	Em caso de erro ...
	 */
    bad:
	close (fd);

}	/* end analyse_and_proc_file */

/*
 ****************************************************************
 *  Analisa um m�dulo para compor uma biblioteca compartilhada	*
 ****************************************************************
 */
int
ftw_function (const char *mod_nm, STAT *sp, int type)
{
	HEADER		h;
	const MODULE	*mp;
	int		fd;

	/*
	 *	Diret�rio n�o leg�vel ou n�o p�de dar "stat"
	 */
	if (type == FTW_SL && stat (mod_nm, sp) < 0 || type == FTW_NS || type == FTW_DNR)
		{ error ("*@N�o pude ler/obter o estado de \"%s\"", mod_nm); return (0); }

	/*
	 *	Prepara e verifica se aceita o nome
	 */
	if (patmatch (mod_nm, ".!.*") || patmatch (mod_nm, "*/.!.*"))
	{
		if (type == FTW_D)
			return (1);	/* Pula toda sub�rvore */
		else
			return (0);
	}

	if (!patmatch (mod_nm, "*.o"))
		return (0);

	if (!S_ISREG (sp->st_mode))
		{ error ("@O arquivo \"%s\" n�o � regular", mod_nm); return (0); }

	if (vflag > 1)
		printf ("M�dulo: \"%s\"\n", mod_nm);

	/*
	 *	Abre o m�dulo
	 */
	if ((fd = inopen (sp->st_dev, sp->st_ino)) < 0)
		{ error ("*@N�o consegui abrir o m�dulo \"%s\"", mod_nm); return (0); }

	/*
	 *	Le o cabe�alho do "a.out"
	 */
	if (read (fd, &h, sizeof (HEADER)) != sizeof (HEADER))
	{
		error ("*@N�o consegui ler o cabe�alho do m�dulo \"%s\"", mod_nm);
		close (fd); return (0);
	}

	if (h.h_magic != FMAGIC)
	{
		error ("@O arquivo \"%s\" n�o � um m�dulo objeto", mod_nm);
		close (fd); return (0);
	}

	if (h.h_ssize == NULL)
	{
		error ("@O m�dulo \"%s\" n�o possui tabela de s�mbolos", mod_nm);
		close (fd); return (0);
	}

	/*
	 *	Insere o m�dulo na tabela de m�dulos
	 */
	mp = put_module (mod_nm, FMAGIC, sp->st_dev, sp->st_ino, &h);

	install_mod_symbols (mp, fd, &h, 'R' /* M�dulo regular */);

	close (fd);

	return (0);

}	/* end ftw_function */

/*
 ****************************************************************
 *	Instala os s�mbolos de um M�dulo Objeto			*
 ****************************************************************
 */
void
install_mod_symbols (const MODULE *mp, int fd, const HEADER *hp, int tipo)
{
	SYM		*sp;
	GSYM		*gp;
	void		*image = NOVOID;
	const SYM	*end_image;
	off_t		text_rel, data_rel, bss_rel;

	/*
	 *	Valores de tipo:
	 *		'R' para m�dulo regular
	 *		'L' para membro de biblioteca regular
	 *
	 *	Calcula as constantes de reloca��o para este m�dulo
	 */
	text_rel  = TEXT_SIZE;
	data_rel  = DATA_SIZE - hp->h_tsize;
	bss_rel   = BSS_SIZE  - hp->h_tsize - hp->h_dsize;

	/*
	 *	Le a tabela de s�mbolos
	 */
	if (hp->h_ssize)
	{
		image = alloca (hp->h_ssize);

		lseek (fd, hp->h_tsize + hp->h_dsize, SEEK_CUR);

		if (read (fd, image, hp->h_ssize) != hp->h_ssize)
			{ error ("*@Erro na leitura da tabela de s�mbolos de \"%s\"", mp->m_nm); return; }
	}

	end_image = image + hp->h_ssize;

	/*
	 *	Processa os S�mbolos
	 */
	for (sp = image; sp < end_image; sp = SYM_NEXT_PTR (sp))
	{
		/*
		 *	Reloca o s�mbolo
		 */
		switch (sp->s_type)
		{
		    case EXTERN|TEXT:
			sp->s_value += text_rel;
			break;

		    case EXTERN|DATA:
			sp->s_value += data_rel;
			break;

		    case EXTERN|BSS:
			sp->s_value += bss_rel;
			break;

		    case EXTERN|ABS:
		    case EXTERN|UNDEF:
			break;

		    default:		/* Ignora os outros s�mbolos */
			continue;

		}	/* end switch */

		/*
		 *	Processa as refer�ncias
		 */
		if (IS_UNDEF (sp) || uflag == 1 && tipo == 'L')
			sp->s_flags |= S_REF;

		/*
		 *	Se o s�mbolo n�o aparecera antes, instala-o
		 */
		if ((gp = hash (sp->s_name, sp->s_nm_len)) == NOGSYM)
			{ gp = put_global_symbol (sp, mp); continue; }

		/*
		 *	Processa as refer�ncias
		 */
		if (sp->s_flags & S_REF)
			gp->s.s_flags |= S_REF;

		/*
		 *	Se o s�mbolo j� foi definido anteriormente, ...
		 */
		if (!IS_UNDEF_OR_COMMON (&gp->s))
		{
			if (IS_UNDEF_OR_COMMON (sp))
				continue;

			if (sp->s_type == gp->s.s_type && sp->s_type == (EXTERN|ABS))
			{
				if (sp->s_value == gp->s.s_value)
					continue;
			}

			error
			(	"@S�mbolo \"%s\" redefinido (\"%s\", %s :: \"%s\", %s)",
				sp->s_name,
				mp->m_nm, edit_sym_type (sp),
				get_module_name (gp), edit_sym_type (&gp->s)
			);

			continue;
		}

		/*
		 *	COMMONs devem assumir o maior valor possivel
		 */
		if (IS_UNDEF_OR_COMMON (sp))
		{
			/* Ambos s�o UNDEF/COMMON */

			if (gp->s.s_value < sp->s_value)
				gp->s.s_value = sp->s_value;

			continue;
		}

		/*
		 *	Neste ponto, na tabela temos UNDEF/COMMON, e no m�dulo TEXT/DATA/BSS
		 *
		 *	Evita usar um TEXT para um COMMON
		 */
		if (gp->s.s_value != 0 && sp->s_type == (EXTERN|TEXT))
		{
			error
			(	"@COMMON \"%s\" alocado no TEXT (\"%s\", \"%s\")\n",
				sp->s_name, mp->m_nm, get_module_name (gp)
			);

			continue;
		}

		/*
		 *	Atualiza Tipo & Valor do s�mbolo
		 */
		gp->s.s_type  = sp->s_type;
		gp->s.s_value = sp->s_value;

	}	/* end for pelos s�mbolos do M�dulo */

	if (sp != end_image)
		error ("Defasamento da tabela de s�mbolos do m�dulo \"%s\"", mp->m_nm);

	/*
	 *	Atualiza os tamanhos das se��es do programa
	 */
	TEXT_SIZE += hp->h_tsize;
	DATA_SIZE += hp->h_dsize;
	BSS_SIZE  += hp->h_bsize;

	return;

}	/* end install_mod_symbols */
