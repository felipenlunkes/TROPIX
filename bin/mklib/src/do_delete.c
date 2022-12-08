/*
 ****************************************************************
 *								*
 *			do_delete.c				*
 *								*
 *	Remove m�dulos da biblioteca				*
 *								*
 *	Vers�o	1.0.0, de 23.10.86				*
 *		4.0.0, de 20.08.01				*
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
#include <string.h>
#include <a.out.h>

#include "../h/mklib.h"

/*
 ****************************************************************
 *	Remove m�dulos da biblioteca				*
 ****************************************************************
 */
int
do_delete (const char *argv[])
{
	MOD		*mp, *back_mp;
	char		*mod_path, *nm_point;
	const char	*mod_nm, **cpp;
	int		modif = 0;
	int		len, max_len = 0;

	/*
	 *	Se n�o foi dado nenhum nome de m�dulo, ...
	 */
	if (*argv == NOSTR)
		error ("$A remo��o deve ter nomes de <m�dulo>s");

	/*
	 *	Le a sinopse
	 */
	read_sinop_file (0);

	/*
	 *	Prepara o prefixo dos nomes dos m�dulos
	 */
	for (cpp = argv, max_len = 0; *cpp != NOSTR; cpp++)
	{
		if (max_len < (len = strlen (*cpp)))
			max_len = len;
	}

	mod_path = alloca (lib_dir_nm_len + 1 + max_len);

	strcpy (mod_path, lib_dir_nm);		strcat (mod_path, "/");

	nm_point = strend (mod_path);

	/*
	 *	Processa cada um dos argumentos
	 */
	while ((mod_nm = *argv++) != NOSTR)
	{
		strcpy (nm_point, mod_nm);

		/*
		 *	Verifica se o m�dulo est� na biblioteca
		 */
		for
		(	back_mp = NOMOD, mp = mod_first;
			mp != NOMOD;
			back_mp = mp, mp = mp->m_next
		)
		{
			if (streq (mp->m_mod_nm, mod_nm))
				break;
		}

		if (mp == NOMOD)
		{
			error ("N�o achei o m�dulo \"%s\"", mod_nm);
			continue;
		}

		/*
		 *	Consulta o usu�rio
		 */
		if (!fflag)
		{
			fprintf (stderr, "Remove \"%s\"? (n): ", mod_nm);

			if (askyesno () <= 0)
				continue;
		}

		if (unlink (mod_path) < 0)
		{
			error ("*N�o consegui remover \"%s\"", mod_path);
			continue;
		}

		/*
		 *	Remove o m�dulo
		 */
		if (back_mp == NOMOD)
			mod_first = mp->m_next;
		else
			back_mp->m_next = mp->m_next;

		if (vflag)
			printf ("d - %s\n", mod_nm);

		modif++;
	}

	return (modif);		/* > 0 => N�o ordena */

}	/* end delete */
