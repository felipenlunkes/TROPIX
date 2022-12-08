/*
 ****************************************************************
 *								*
 *			do_create.c				*
 *								*
 *	Cria o arquivo de sinopse				*
 *								*
 *	Vers�o	1.0.0, de 06.10.86				*
 *		4.2.0, de 01.10.01				*
 *								*
 *	M�dulo: MKLIB						*
 *		Utilit�rios Especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stat.h>
#include <ftw.h>
#include <unistd.h>
#include <a.out.h>
#include <errno.h>

#include "../h/mklib.h"

/*
 ****************************************************************
 *	Cria o arquivo de sinopse				*
 ****************************************************************
 */
int
do_create (const char *argv[])
{
	/*
	 *	Pequena consist�ncia
	 */
	if (argv[0] != NOSTR)
		error ("$A cria��o n�o deve ter nomes de <m�dulo>s");

	/*
	 *	Aloca mem�ria para a tabela HASH
	 */
	if ((hash_tb = calloc (HASHSZ, sizeof (SYMTB *))) == (SYMTB **)NULL)
		error (NOSTR);

	/*
	 *	Remove o arquivo de sinopse antigo
	 */
	if (unlink (lib_sinop_nm) < 0 && errno != ENOENT)
		error ("$*N�o consegui remover \"%s\"", lib_sinop_nm);

	/*
	 *	Gera o novo arquivo de sinopse
	 */
	mod_first = mod_last = NOMOD;

	if (ftw (lib_dir_nm, ftw_create_function) < 0)
		error ("A fun��o \"ftw\" devolveu um valor negativo");

	free (hash_tb);

	return (-1);	/* Ordena e escreve a sinopse */

}	/* end do_create */

/*
 ****************************************************************
 *	Insere um m�dulo nas tabelas				*
 ****************************************************************
 */
int
ftw_create_function (const char *mod_path, STAT *sp, int opt)
{
	const char	*mod_nm = mod_path;
	MOD		*mp;

	/*
	 *	Diret�rio n�o leg�vel ou n�o p�de dar "stat"
	 */
	if (opt == FTW_NS || opt == FTW_DNR)
	{
		error ("*N�o pude ler/obter o estado de \"%s\"", mod_nm);
		return (0);
	}

	/*
	 *	Prepara e verifica se aceita o nome
	 */
	if (patmatch (mod_path, ".!.*") || patmatch (mod_path, "*/.!.*"))
	{
		if (opt == FTW_D)
			return (1);	/* Pula toda sub�rvore */
		else
			return (0);
	}

	if (opt != FTW_F)
		return (0);

	if (!S_ISREG (sp->st_mode))
	{
		error ("O arquivo \"%s\" n�o � regular", mod_path);
		return (0);
	}

	if (lib_dir_nm_len == 1 && lib_dir_nm[0] == '.' && mod_nm[0] != '.')
		mod_nm -= 2;

	mod_nm += lib_dir_nm_len + 1;

	/*
	 *	Verifica se o dispositivo do arquivo � o mesmo 
	 *	da raiz da biblioteca
	 */
	if (sp->st_dev != lib_dev)
	{
		error
		(
			"O m�dulo \"%s\" N�O est� no mesmo dispositivo que \"%s\"",
			mod_path, lib_dir_nm
		);
	}

	/*
	 *	Insere o m�dulo na lista
	 */
	if ((mp = malloc (sizeof (MOD))) == NOMOD)
		error (NOSTR);

	if ((mp->m_mod_nm = strdup (mod_nm)) == NOSTR)
		error (NOSTR);

	mp->m_ino = sp->st_ino;

	if (mod_first == NOMOD)
		mod_first = mp;
	else
		mod_last->m_next = mp;

	mp->m_next = NOMOD;
	mod_last   = mp;

	/*
	 *	Insere os s�mbolos
	 */
	if (mod_insert (mod_nm, mp, sp, NOHEADER) < 0)
		return (0);

	return (0);

}	/* end ftw_create_function */

/*
 ****************************************************************
 *	Insere um m�dulo na tabela de m�dulos 			*
 ****************************************************************
 */
int
mod_insert (const char *mod_nm, MOD *mp, const STAT *sp, HEADER *hp)
{
	int		fd;
	HEADER		h;
	SYM		*sym_tb;

	/*
	 *	Abre o arquivo
	 */
	if ((fd = inopen (sp->st_dev, sp->st_ino)) < 0)
	{
		error ("*N�o consegui abrir \"%s\"", mod_nm);
		return (-1);
	}

	/*
	 *	Verifica se o HEADER j� est� dispon�vel
	 */
	if (hp == NOHEADER)
	{
		hp = &h;

		/*
		 *	Verifica se o m�dulo � objeto
		 */
		if (read (fd, hp, sizeof (HEADER)) != sizeof (HEADER))
		{
			error ("*Erro na leitura do cabe�alho de \"%s\"", mod_nm);
			close (fd); 	return (-1);
		}

		if (hp->h_magic != FMAGIC)
		{
			error ("O arquivo \"%s\" n�o � um m�dulo objeto", mod_nm);
			close (fd); 	return (-1);
		}
	}

	/*
	 *	Aloca mem�ria e le a tabela de s�mbolos
	 */
	sym_tb = alloca (hp->h_ssize);

	lseek (fd, sizeof (HEADER) + hp->h_tsize + hp->h_dsize, L_SET);

	if (hp->h_ssize && read (fd, sym_tb, hp->h_ssize) != hp->h_ssize)
	{
		error ("*Erro na leitura da tabela de s�mbolos de \"%s\"", mod_nm);
		close (fd); 	return (-1);
	}

	close (fd);

	/*
	 *	Processa os s�mbolos do arquivo
	 */
	if (vflag)
		printf ("a - %s\n", mod_nm);

	mk_mod_sym
	(
		mod_nm,
		mp,
		sym_tb,
		(SYM *)((int)sym_tb + hp->h_ssize),
		1				/* HASHON */
	);

	return (0);

}	/* end mod_insert */

/*
 ****************************************************************
 *	Processa a Tabela de s�mbolos de um m�dulo		*
 ****************************************************************
 */
int
mk_mod_sym
(
	const char	*mod_nm,
	MOD		*mp,
	SYM		*sym_tb,
	SYM		*end_sym_tb,
	int		hash_flag
)
{
	const SYM	*sp;
	SYMTB		*zp, **link_point;
	SYMTB		*first_sym = NOSYMTB, *last_sym = NOSYMTB;
	char		type;

	/*
	 *	Percorre toda a tabela de s�mbolos
	 */
	mp->m_n_sym = 0;

	for (sp = sym_tb; sp < end_sym_tb; sp = SYM_NEXT_PTR (sp))
	{
		/*
		 *	Analisa o s�mbolo
		 */
		if ((sp->s_type & EXTERN) == 0)
			continue;

		type = sp->s_type & ~EXTERN;

		if (type < TEXT || type > BSS)
			continue;

		/*
		 *	Verifica se a Hash est� ativa: testa duplica��es
		 */
		if (hash_flag)
		{
			if ((zp = hash (sp->s_name, sp->s_nm_len, &link_point)) != NOSYMTB)
			{
				if (vflag)
					fprintf (stderr, "\t");

				error
				(
					"S�mbolo \"%s\" duplicado: "
					"\"%s\" :: \"%s\"",
					sp->s_name,
					mod_nm,
					zp->z_mod->m_mod_nm
				);

				continue;
			}

		}	/* end if (HASH on) */

		/*
		 *	Cria a estrutura do s�mbolo
		 */
		if ((zp = malloc (sizeof (SYMTB))) == NOSYMTB)
			error (NOSTR);

		if (hash_flag)
			{ *link_point = zp; zp->z_link = NOSYMTB; }

		if ((zp->z_sym_nm = strdup (sp->s_name)) == NOSTR)
			error (NOSTR);

		zp->z_sym_len = sp->s_nm_len,
		zp->z_mod     = mp;

		if (first_sym == NOSYMTB)
			first_sym = zp;
		else
			last_sym->z_sym_next = zp;

		last_sym = zp;
		zp->z_sym_next = NOSYMTB;

	   /***	zp->z_link = NOSYMTB; ***/

		mp->m_n_sym++;

	}	/* end percorrendo a tabela de s�mbolos do m�dulo */

	mp->m_sym = first_sym;

	if (sp != end_sym_tb)
		error ("Defasamento na tabela de s�mbolos de \"%s\"", mod_nm);

	return (mp->m_n_sym);

}	/* end mk_mod_sym */
