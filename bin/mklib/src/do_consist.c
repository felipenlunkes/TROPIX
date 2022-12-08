/*
 ****************************************************************
 *								*
 *			do_consist.c				*
 *								*
 *	Realiza testes de consist�ncia na biblioteca		*
 *								*
 *	Vers�o	1.0.0, de 23.10.86				*
 *		4.2.0, de 01.10.01				*
 *								*
 *	M�dulo: MKLIB						*
 *		Utilit�rios Especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stat.h>
#include <ftw.h>
#include <a.out.h>

#include "../h/mklib.h"

/*
 ****************************************************************
 *	Realiza os testes de consist�ncia 			*
 ****************************************************************
 */
int
do_consistency (const char *argv[])
{
	MOD		*mp, *next_mp;
	SYMTB		*zp, *next_zp;

	/*
	 *	Pequena consist�ncia
	 */
	if (argv[0] != NOSTR)
		error ("$A consist�ncia n�o deve ter nomes de <m�dulo>s");

	/*
	 *	L� o arquivo de sinopse
	 */
	read_sinop_file (0);

	printf
	(	"*** Analisando \"%s\" (%s), %d m�dulos, %d s�mbolos\n\n",
		lib_dir_nm, lib_dev_nm, n_lib_mod, n_lib_sym
	);

	/*
	 ******	Examina a ordena��o dos m�dulos *****************
	 */
	printf ("*** Fase  1: Verificando a ordena��o dos m�dulos\n");

	for (mp = mod_first; mp != NOMOD; mp = next_mp)
	{
		next_mp = mp->m_next;

		if (next_mp != NOMOD && strcmp (mp->m_mod_nm, next_mp->m_mod_nm) > 0)
		{
			printf
			(	"\t\tM�dulos \"%s\" e \"%s\" fora de ordem\n",
				mp->m_mod_nm, next_mp->m_mod_nm
			);
		}
	}

	/*
	 ******	Examina a ordena��o dos s�mbolos ****************
	 */
	printf ("*** Fase  2: Verificando a ordena��o dos s�mbolos\n");

	for (mp = mod_first; mp != NOMOD; mp = mp->m_next)
	{
		for (zp = mp->m_sym; zp != NOSYMTB; zp = next_zp)
		{
			next_zp = zp->z_sym_next;

			if (next_zp != NOSYMTB && strcmp (zp->z_sym_nm, next_zp->z_sym_nm) > 0)
			{
				printf
				(	"\t\tS�mbolos \"%s\" e \"%s\" do m�dulo \"%s\" fora de ordem\n",
					zp->z_sym_nm, next_zp->z_sym_nm, mp->m_mod_nm
				);
			}
		}
	}

	/*
	 ******	Examina os m�dulos da biblioteca ****************
	 */
	printf ("*** Fase  3: Verificando se h� s�mbolos duplicados\n");

	if ((hash_tb = calloc (HASHSZ, sizeof (SYMTB *))) == (SYMTB **)NULL)
		error (NOSTR);

	hash_all_sym ();

	free (hash_tb);

	/*
	 ******	Examina os m�dulos da biblioteca ****************
	 */
	printf ("*** Fase  4: Examinando os s�mbolos de cada m�dulo\n");

	if (ftw (lib_dir_nm, consist_ftw_function) < 0)
		error ("A fun��o \"ftw\" devolveu um valor negativo");

	/*
	 ******	Verifica se n�o sobrou algum m�dulo em ".LIBSYM"
	 */
	printf ("*** Fase  5: Verificando se h� m�dulos esp�rios na sinopse\n");

	for (mp = mod_first; mp != NOMOD; mp = mp->m_next)
	{
		if (mp->m_ino != 0)
		{
			printf
			(	"\t\tO m�dulo \"%s\" da sinopse n�o se encontra "
				"na biblioteca\n", mp->m_mod_nm
			);
		}
	}

	vflag = 0;

	return (0);

}	/* end do_consistency */

/*
 ****************************************************************
 *	Verifica se o Arquivo est� em LIBSYM			*
 ****************************************************************
 */
int
consist_ftw_function (const char *mod_path, STAT *sp, int opt)
{
	const char	*mod_nm = mod_path;
	MOD		*mp, *new_mp;
	int		fd;
	SYM		*sym_tb, *end_sym_tb;
	int		new_n_sym, modif;
	HEADER		h;
	const SYMTB	*zp, *new_zp;

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
		printf ("\t\tO arquivo \"%s\" n�o � regular\n", mod_path);
		return (0);
	}

	if (lib_dir_nm_len == 1 && lib_dir_nm[0] == '.' && mod_nm[0] != '.')
		mod_nm -= 2;

	mod_nm += lib_dir_nm_len + 1;

	if (streq (mod_nm, lib_sym_nm))	/* normalmente ".LIBSYM" */
		return (0);

	if (vflag)
		printf ("%s:\n", mod_nm);

	/*
	 *	Verifica se o nome consta da tabela de m�dulos
	 */
	if ((mp = mod_search (mod_nm)) == NOMOD)
	{
		printf ("\t\tO M�dulo \"%s\" n�o consta da sinopse\n", mod_nm);
		return (0);
	}

	/*
	 *	Verifica se DEV e INO conferem
	 */
	if (mp->m_ino != sp->st_ino)
	{
		printf
		(	"\t\tO n�-�ndice do m�dulo \"%s\" n�o confere: (%d :: %d)\n",
			mod_nm, mp->m_ino, sp->st_ino
		);
		mp->m_ino = 0; 		/* Marca o m�dulo como "apagado" */
		return (0);
	}

	mp->m_ino = 0;	 		/* Marca o m�dulo como "apagado" */

	/*
	 ******	Confere os s�mbolos do m�dulo *******************
	 */
	if ((fd = inopen (sp->st_dev, sp->st_ino)) < 0)
	{
		error ("*N�o consegui abrir \"%s\"", mod_nm);
		return (0);
	}

	/*
	 *	Verifica se o m�dulo � objeto
	 */
	if (read (fd, &h, sizeof (HEADER)) != sizeof (HEADER))
	{
		error ("*Erro na leitura do cabe�alho de \"%s\"", mod_nm);
		close (fd); 	return (0);
	}

	if (h.h_magic != FMAGIC)
	{
		error ("O arquivo \"%s\" n�o � um m�dulo objeto", mod_nm);
		close (fd); 	return (0);
	}

	/*
	 *	Aloca mem�ria e le a tabela de s�mbolos
	 */
	sym_tb = alloca (h.h_ssize);

	lseek (fd, sizeof (HEADER) + h.h_tsize + h.h_dsize, L_SET);

	if (h.h_ssize && read (fd, sym_tb, h.h_ssize) != h.h_ssize)
	{
		error ("*Erro na leitura da tabela de s�mbolos de \"%s\"", mod_nm);
		close (fd);	return (0);
	}

	close (fd);

	/*
	 *	Aloca uma �rea mais do que suficiente para os LIBSYMs
	 */
	end_sym_tb = (SYM *)((int)sym_tb + h.h_ssize),

	new_mp = alloca (sizeof (MOD));

	/*
	 *	Processa a tabela de s�mbolos do novo m�dulo
	 */
	new_n_sym = mk_mod_sym
	(
		mod_nm,
		new_mp,
		sym_tb,
		end_sym_tb,
		0			/* HASHOFF */
	);

	/*
	 *	Confere os tamanhos
	 */
	if (new_mp->m_n_sym != mp->m_n_sym)
	{
		printf
		(	"\t\tO N�mero de s�mbolos da tabela de s�mbolos de "
			"\"%s\" n�o confere (%d :: %d)\n",
			mod_nm, new_mp->m_n_sym, mp->m_n_sym
		);
		return (0);
	}

	/*
	 *	Ordena os s�mbolos
	 */
	sort_mod_sym (new_mp);

	/*
	 *	Confere os s�mbolos
	 */
	for
	(	modif = 0, zp = mp->m_sym, new_zp = new_mp->m_sym;
		zp != NOSYMTB;
		zp = zp->z_sym_next, new_zp = new_zp->z_sym_next
	)
	{
#ifdef	DEBUG
	if (vflag > 1)
		printf (" %s", mp->m_mod_nm);
#endif	DEBUG
		if (strcmp (zp->z_sym_nm, new_zp->z_sym_nm))
		{
#ifdef	DEBUG
			printf (" (ERRO: %s)", new_zp->z_sym_nm);
#endif	DEBUG
			modif++;
		}
	}

	if (modif)
	{
		printf
		(	"\t\t%d s�mbolo(s) da tabela de s�mbolos de "
			"\"%s\" n�o confere(m)\n", modif, mod_nm
		);
		return (0);
	}

#ifdef	DEBUG
	if (vflag > 1)
		printf ("\n");
#endif	DEBUG

	return (0);

}	/* end consist_ftw_function */
