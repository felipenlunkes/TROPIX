/*
 ****************************************************************
 *								*
 *			do_rm.c					*
 *								*
 *	Remove arquivos						*
 *								*
 *	Vers�o	3.0.0, de 21.11.93				*
 *		3.1.0, de 15.01.99				*
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
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		simple_rm (const char *);
void		do_rm_help (void);

/*
 ****************************************************************
 *	Remove arquivos						*
 ****************************************************************
 */
void
do_rm (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Inicializa��es
	 */
	cmd_iflag = 1;

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
			cmd_iflag = 0;
			break;

		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case 'H':			/* Help */
			do_rm_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_rm_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc == 0)
		{ do_rm_help (); return; }

	/*
	 *	Processa os arquivos
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		simple_rm (*argv);
	}

}	/* end do_rm */

/*
 ****************************************************************
 *	Remove um arquivo					*
 ****************************************************************
 */
void
simple_rm (const char *path)
{
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

#undef	DEBUG
#ifdef	DEBUG
	printf
	(	"simple_rm: entries = %d, clusno = %d\n",
		z.z_lfn_entries, z.z_lfn_clusno
	);

	printf
	(	"simple_rm: blkno = %d, end_blkno = %d, offset = %d\n",
		z.z_lfn_blkno, z.z_lfn_end_blkno, z.z_lfn_offset
	);
#endif	DEBUG

	/*
	 *	Se necess�rio, pede confirma��o do usuario
	 */
	if   (cmd_iflag)
	{
		fprintf
		(	stderr,
			"(%c, %d) %s? (n): ",
			file_type_edit (z.z_mode), GET_LONG (z.z_size), path
		);

		if (askyesno () <= 0)
			return;
	}
	elif (cmd_vflag)
	{
		printf ("%s:\n", path);
	}

	/*
	 *	Verifica se � um arquivo regular
	 */
	if (Z_ISDIR (z.z_mode))
	{
		printf
		(	"%s: O arquivo \"%s\" � um diret�rio\n",
			cmd_nm, path
		);
		return;
	}

	/*
	 *	Verifica se tem o bit "r" ligado
	 */
	if (z.z_mode & Z_RO)
	{
		fprintf
		(	stderr,
			"%s: O arquivo \"%s\" s� permite leituras - "
			"remove? (n): ",
			cmd_nm, path
		);

		if (askyesno () <= 0)
			return;
	}

	/*
	 *	Remove o arquivo
	 */
	if (dos_unlink (&z, 1 /* trunca */) < 0)
		return;

	/*
	 *	Verifica se alterou o nome do volume principal
	 */
	if (Z_ISVOL (z.z_mode))
	{
		vol_nm[0] = '\0';

		dir_walk (vol_search, uni.u_root_cluster);
	}

}	/* end simple_rm */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_rm_help (void)
{
	fprintf
	(	stderr,
		"%s - remove arquivos (regulares ou volumes) DOS\n"
		"\nSintaxe:\n"
		"\t%s [-ifv] <arquivo> ...\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: Pede a confirma��o para cada <arquivo> a remover "
			"(modo normal)\n"
		"\t-f: Remove os <arquivo>s sem pedir confirma��o do usu�rio\n"
		"\t-v: Lista o nome dos <arquivo>s removidos\n"
	);

}	/* end do_rm_help */
