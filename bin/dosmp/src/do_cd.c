/*
 ****************************************************************
 *								*
 *			do_cd.c					*
 *								*
 *	Muda de diret�rio corrente				*
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

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_cd_help (void);

/*
 ******	Defini��es globais **************************************
 */
entry int	cwd_cluster;		/* Diret�rio corrente */

/*
 ****************************************************************
 *	Muda de diret�rio corrente				*
 ****************************************************************
 */
void
do_cd (int argc, const char *argv[])
{
	int		opt;
	const char	*dir_nm;
	DOSSTAT		z;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_cd_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_cd_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 1)
		{ do_cd_help (); return; }

	dir_nm = argv[0];

	/*
	 *	Procura o diret�rio
	 */
	if (dos_stat (dir_nm, &z) < 0)
	{
		printf
		(	"%s: N�o achei o diret�rio \"%s\" (%s)\n",
			cmd_nm, dir_nm, strerror (errno)
		);
		return;
	}

	if (!Z_ISDIR (z.z_mode))
	{
		printf
		(	"O arquivo \"%s\" n�o � um diret�rio \n",
			dir_nm
		);
		return;
	}

	cwd_cluster = z.z_cluster;

}	/* end do_cd */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_cd_help (void)
{
	fprintf
	(	stderr,
		"%s - troca de diret�rio corrente DOS\n"
		"\nSintaxe:\n"
		"\t%s <novo_diret�rio>\n",
		cmd_nm, cmd_nm
	);

}	/* end help */
