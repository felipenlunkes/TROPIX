/*
 ****************************************************************
 *								*
 *			do_get.c				*
 *								*
 *	Copia arquivos DOS para o sistema TROPIX		*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 10.06.95				*
 *								*
 *	M�dulo: DOSMP						*
 *		Utilit�rios Sofisticados			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Inspirado no PLDOS de Norival Ribeiro Figueira	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		get_file (const char *);
void		do_get_help (void);

/*
 ****************************************************************
 *	Copia arquivos DOS para o sistema TROPIX		*
 ****************************************************************
 */
void
do_get (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "ifvH")) >= 0)
	{
		switch (opt)
		{
		    case 'i':			/* Interativo */
			cmd_iflag++;
			break;

		    case 'f':			/* For�a */
			cmd_fflag++;
			break;

		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case 'H':			/* Help */
			do_get_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_get_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc == 0)
		{ do_get_help (); return; }

	/*
	 *	Processa os diversos arquivos
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		if   (cmd_iflag)
		{
			fprintf (stderr, "%s? (n): ", *argv);

			if (askyesno () <= 0)
				continue;
		}
		elif (cmd_vflag)
		{
			printf ("%s\n", *argv);
		}

		get_file (*argv);
	}

}	/* end do_get */

/*
 ****************************************************************
 *	Obt�m um arquivo					*
 ****************************************************************
 */
void
get_file (const char *path)
{
	STAT		s;
	int		fd, n;
	const char	*nm;
	char		area[BLSZ];
	DOSFILE		f;
	DOSSTAT		z;

	/*
	 *	Obt�m o estado do arquivo
	 */
	if (dos_stat (path, &z) < 0)
	{
		printf
		(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			cmd_nm, path, strerror (errno)
		);
		return;
	}

	if (!Z_ISREG (z.z_mode))
	{
		printf
		(	"O arquivo \"%s\" n�o � regular\n",
			path
		);
		return;
	}

	if (dos_open (&f, &z) < 0)
		return;

	/*
	 *	Verifica se o arquivo j� existe no TROPIX
	 */
	nm = last_nm (path);

	if (stat (nm, &s) >= 0)
	{
		if (S_ISDIR (s.st_mode))
		{
			printf
			(	"%s: \"%s\" j� existe no %s "
				"e � um diret�rio\n",
				cmd_nm, nm, sys_nm
			);
			return;
		}

		if (!cmd_fflag)
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe no %s. "
				"Apaga/reescreve? (n): ",
				cmd_nm, nm, sys_nm
			);

			if (askyesno () <= 0)
				return;
		}

		if (!S_ISREG (s.st_mode) && unlink (nm) < 0)
		{
			printf
			(	"%s: N�o consigo remover \"%s\" (%s)\n",
				cmd_nm, nm, strerror (errno)
			);
			return;
		}

	}	/* end if (j� existe o nm) */ 

	/*
	 *	Cria o arquivo
	 */
	if ((fd = creat (nm, 0666)) < 0)
	{
		printf
		( 	"%s: N�o consigo criar \"%s\" (%s)\n",
			cmd_nm, nm, strerror (errno)
		);
		return;
	}

	/*
	 *	Percorre os blocos do arquivo
	 */
	while ((n = dos_read (&f, area, BLSZ)) > 0)
	{
		if (write (fd, area, n) != n)
		{
			printf
			(	"%s: Erro na escrita de \"%s\" (%s)\n",
				cmd_nm, nm, strerror (errno)
			);
			close (fd);
			return;
		}
	}

	close (fd);

}	/* end get_file */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_get_help (void)
{
	fprintf
	(	stderr,
		"%s - copia arquivos DOS para o diret�rio corrente "
			"do sistema %s\n"
		"\nSintaxe:\n"
		"\t%s [-ifv] <arquivo> ...\n",
		cmd_nm, sys_nm, cmd_nm
	);

	fprintf (stderr, "\nOp��es:%s", options_ifv);

	fprintf (stderr, somewhere_expand, "DOS");

}	/* end do_get_help */
