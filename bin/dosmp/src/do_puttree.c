/*
 ****************************************************************
 *								*
 *			do_puttree.c				*
 *								*
 *	Copia �rvores TROPIX para o sistema DOS			*
 *								*
 *	Vers�o	3.0.0, de 23.11.93				*
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
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Vari�veis deste comando *********************************
 */
extern int	not_first;	/* J� escreveu o nome de um diret�rio */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		puttree_ftw_function (const char *, STAT *, int);
int		dos_verdir (const char *);
void		do_puttree_help (void);

extern int	cmp_one_file (const char *, int, STAT *, DOSSTAT *);

/*
 ****************************************************************
 *	Copia �rvores TROPIX para o sistema DOS			*
 ****************************************************************
 */
void
do_puttree (int argc, const char *argv[])
{
	char		*tree;
	const char	*str;
	int		opt;
	STAT		old_s;

	/*
	 *	Inicializa��es
	 */
	not_first = 0;

	/*
	 *	Analisa as op��es
	 */
	if (streq (cmd_nm, "cmpputtree"))
		{ str = "ui.sp:P:H"; cmd_cflag++; }
	else
		  str = "ifv.sp:P:H";

	while ((opt = cmd_getopt (argv, str)) >= 0)
	{
		switch (opt)
		{
		    case 'i':			/* Interativo */
			cmd_iflag++;
			break;

		    case 'u':			/* Atualiza��o */
			cmd_uflag++;
			break;

		    case 'f':			/* For�a */
			cmd_fflag++;
			break;

		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case '.':			/* ".old" */
			cmd_dotflag++;
			break;

		    case 's':			/* Padr�es = 	*.[cshryv] e */
			put_s_option ();
			break;

		    case 'p':		/* Padr�es de inclus�o */
			if (put_p_option (cmd_optarg, inc_pat, &inc_pati) < 0)
				{ do_puttree_help (); return; }
			break;

		    case 'P':		/* Padr�es de exclus�o */
			if (put_p_option (cmd_optarg, exc_pat, &exc_pati) < 0)
				{ do_puttree_help (); return; }
			break;

		    case 'H':			/* Help */
			do_puttree_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_puttree_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 1)
		{ do_puttree_help (); return; }

	/*
	 *	Obt�m o estado do diret�rio fonte TROPIX
	 */
	tree = path_can ((char *)argv[0]);

	if (stat (tree, &old_s) < 0)
	{
		printf
		(	"%s: N�o achei o arquivo %s \"%s\" (%s)\n",
			cmd_nm, sys_nm, tree, strerror (errno)
		);
		return;
	}

	if (!S_ISDIR (old_s.st_mode))
	{
		printf
		(	"%s: O arquivo %s \"%s\" n�o � um diret�rio\n",
			cmd_nm, sys_nm, tree
		);
		return;
	}

	/*
	 *	Percorre �rvore TROPIX
	 */
	ftw (tree, puttree_ftw_function);

}	/* end do_puttree */

/*
 ****************************************************************
 *	Obt�m um arquivo					*
 ****************************************************************
 */
int
puttree_ftw_function (const char *path, STAT *sp, int code)
{
	DOSSTAT		z;
	int		fd;
	const char	*nm;

	/*
	 *	Verifica se houve um <^C>
	 */
	if (received_intr)
		return (-1);

	/*
	 *	Obt�m o estado do <destino> DOS
	 */
	if (dos_stat (path, &z) < 0)
		z.z_mode = Z_IFMT;		/* Meio deselegante! */

	nm = last_nm (path);

	/*
	 *	Identifica o <fonte> (a partir de ftw)
	 */
	switch (code)
	{
		/*
		 ******	Diret�rio *******************************
		 */
	    case FTW_D:		/* Diret�rios ".old": pula toda sub�rvore */
		if (!cmd_dotflag)
		{
			if (patmatch (path, ".!.*") || patmatch (path, "*/.!.*"))
				return (1);
		}

		/*
		 *	Verifica se � interativo
		 */
		if   (cmd_cflag)
		{
			if (not_first++)
				printf ("\n");

			printf ("Diret�rio \"%s\":\n", path);
		}
		elif (cmd_iflag)
		{
			if (not_first++)
				printf ("\n");

			fprintf (stderr, "Diret�rio \"%s\"? (n): ", path);

			if (askyesno () <= 0)
				return (1);
		}
		elif (cmd_vflag)
		{
			if (not_first++)
				printf ("\n");

			printf ("Diret�rio \"%s\":\n", path);
		}

		/*
		 *	Verifica se o arquivo j� existe, e � um diret�rio
		 */
		if (Z_ISDIR (z.z_mode))
			return (0);

		/*
		 *	Se n�o for um diret�rio ...
		 */
		if (z.z_mode == Z_IFMT)		/* Meio deselegante! */
		{
			if (cmd_cflag)
			{
				printf
				(	"\t*** N�o achei o diret�rio \"%s\" (%s)\n",
					nm, strerror (errno)
				);

				if (!cmd_uflag)
					return (1);

				if (cmd_iflag)
				{
					fprintf
					(	stderr,
						"\t*** Atualiza no %s? (n): ",
						"DOS"
					);

					if (askyesno () <= 0)
						return (1);
				}
			}
		}
		else	/* Existe, mas n�o � diret�rio */
		{
			if   (cmd_cflag)
			{
				printf
				(	"\t*** O arquivo \"%s\" deveria ser um "
					"diret�rio\n",
					path
				);

				if (!cmd_uflag)
					return (1);

				if (cmd_iflag)
				{
					if (z.z_mode & Z_RO) fprintf
					(	stderr,
						"\t*** O arquivo \"%s\" s� "
						"permite leituras\n", path
					);

					fprintf
					(	stderr,
						"\t*** Atualiza no %s? (n): ",
						"DOS"
					);

					if (askyesno () <= 0)
						return (1);
				}
			}
			elif (!cmd_fflag)
			{
				fprintf
				(	stderr,
					"\t*** O arquivo \"%s\" deveria ser um "
					"diret�rio\n",
					path
				);

				if (z.z_mode & Z_RO) fprintf
				(	stderr,
					"\t*** O arquivo \"%s\" s� "
					"permite leituras\n", path
				);

				fprintf
				(	stderr,
					"\t*** Atualiza no %s? (n): ",
					"DOS"
				);

				if (askyesno () <= 0)
					return (1);
			}

			if (dos_unlink (&z, 1 /* trunca */) < 0)
				return (1);
		}

		/*
		 *	Cria o diret�rio
		 */
		if (dos_verdir (path) < 0)
		{
			printf
			(	"%s: Erro na cria��o dos diret�rios "
				"intermedi�rios de \"%s\" (%s)\n",
				cmd_nm, path, strerror (errno)
			);
			return (1);
		}

		if (dos_mkdir (path) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui criar o diret�rio \"%s\" (%s)\n",
				cmd_nm, path, strerror (errno)
			);
			return (1);
		}

		return (0);

		/*
		 ****** Arquivo normal **************************
		 */
	    case FTW_F:
		if (!pattern_accept (path))
			return (0);

		/*
		 *	Verifica se � interativo
		 */
		if   (cmd_cflag)
		{
			printf ("    %s:\n", nm);
		}
		elif (cmd_iflag)
		{
			fprintf (stderr, "    %s? (n): ", nm);

			if (askyesno () <= 0)
				return (0);
		}
		elif (cmd_vflag)
		{
			printf ("    %s:\n", nm);
		}

		/*
		 *	Deve ser regular
		 */
		if (!S_ISREG (sp->st_mode))
		{
			printf
			(	"\t*** O arquivo %s \"%s\" n�o � regular\n",
				sys_nm, path
			);
			return (0);
		}

		/*
		 *	Examina o nome novo
		 */
		switch (z.z_mode & Z_IFMT)
		{
		    case Z_IFMT:	/* Arquivo ainda n�o existe no DOS */
			if (cmd_cflag)
			{
				printf
				(	"\t*** N�o achei o arquivo (%s)\n",
					strerror (errno)
				);

				if (!cmd_uflag)
					return (0);

				if (cmd_iflag)
				{
					fprintf
					(	stderr,
						"\t*** Atualiza no %s? (n): ",
						"DOS"
					);

					if (askyesno () <= 0)
						return (0);
				}
			}
			break;

		    case Z_DIR:
			printf
			(	"\t*** \"%s\" j� existe e � um diret�rio\n",
				path
			);
			return (0);
	
		    case Z_REG:
			if   (cmd_cflag)
			{
				if ((fd = inopen (sp->st_dev, sp->st_ino)) < 0)
				{
					printf
					( 	"%s: N�o consigo abrir \"%s\" (%s)\n",
						cmd_nm, path, strerror (errno)
					);
					return (0);
				}

				if (cmp_one_file (path, fd, sp, &z) == 0)
					{ close (fd); return (0); }

				close (fd);

				if (!cmd_uflag)
					return (0);

				if (cmd_iflag)
				{
					if (z.z_mode & Z_RO) printf
					(	"\t*** O arquivo \"%s\" s� "
						"permite leituras\n", path
					);

					fprintf
					(	stderr,
						"\t*** Atualiza no %s? (n): ",
						"DOS"
					);

					if (askyesno () <= 0)
						return (0);
				}
			}
			elif (!cmd_fflag)
			{
				fprintf
				(	stderr,
					"\t*** \"%s\" j� existe%s. "
					"Apaga/reescreve? (n): ",
					path,
					(z.z_mode & Z_RO) ? " e s� permite leituras" : ""
				);

				if (askyesno () <= 0)
					return (0);
			}
			goto old_unlink;
	
		    default:
			if (cmd_cflag)
			{
				printf
				(	"\t*** O arquivo %s \"%s\" "
					"j� existe e n�o � regular\n",
					"DOS", path
				);

				if (!cmd_uflag)
					return (0);

				if (cmd_iflag)
				{
					if (z.z_mode & Z_RO) fprintf
					(	stderr,
						"\t*** O arquivo \"%s\" s� "
						"permite leituras\n", path
					);

					fprintf
					(	stderr,
						"\t*** Atualiza no %s? (n): ",
						"DOS"
					);

					if (askyesno () <= 0)
						return (0);
				}
			}

		    old_unlink:
			if (dos_unlink (&z, 1 /* trunca */) < 0)
				return (0);
	
		}	/* end switch (j� existe o arquivo DOS (dst)) */ 
	
		/*
		 *	Copia o cont�udo
		 */
		if (put_one_file (path, 1 /* complete path */) < 0)
		{
			/* As mensagens j� foram dadas */
		}

		return (0);

		/*
		 ******	Arquivo ileg�vel ************************
		 */
	    case FTW_DNR:
	    case FTW_NS:
		if (!pattern_accept (path))
			return (0);

		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado do arquivo %s \"%s\"\n",
			cmd_nm, sys_nm, path
		);

		return (0);

		/*
		 ******	Outros tipos de arquivos ****************
		 */
	    default:
		error
		(	"puttree_ftw_function: Tipo de arquivo inv�lido: %d\n",
			code
		);
		return (0);

	}	/* end switch */

}	/* end puttree_ftw_function */

/*
 ****************************************************************
 *	Cria os diret�rios intermedi�rios DOS faltando		*
 ****************************************************************
 */
int
dos_verdir (const char *filenm)
{
	char		*cp;
	DOSSTAT		z;

	/*
	 *	Percorre o nome dado analisando todos os diret�rios
	 */
	for (cp = (char *)filenm + 1; *cp != '\0'; cp++)
	{
		if (*cp == '/')
		{
			*cp = '\0';

			if (dos_stat (filenm, &z) < 0)
			{
				if (dos_mkdir (filenm) < 0)
					{ *cp = '/'; return (-1); }
			}

			*cp = '/';

		}	/* end if */

	}	/* end for */

	return (0);

}	/* end dos_verdir */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_puttree_help (void)
{
	if (cmd_cflag)
	{
		fprintf
		(	stderr,
			"%s - compara e copia �rvores %s para o sistema DOS\n"
			"\nSintaxe:\n"
			"\t%s [-ui.s] [-p \"<p>\"] [-P \"<P>\"] <�rvore>\n",
			cmd_nm, sys_nm, cmd_nm
		);

		fprintf
		(	stderr,
			"\nOp��es:"
			"\t-u: Atualiza a �rvore DOS\n"
			"\t-i: Pede a confirma��o para cada arquivo a atualizar\n"
		);
	}
	else
	{
		fprintf
		(	stderr,
			"%s - copia �rvores %s para o sistema DOS\n"
			"\nSintaxe:\n"
			"\t%s [-ifv.s] [-p \"<p>\"] [-P \"<P>\"] <�rvore>\n",
			cmd_nm, sys_nm, cmd_nm
		);
		fprintf (stderr, "\nOp��es:%s", options_ifv);
	}

	fprintf
	(	stderr,
		"\t-.: Processa tamb�m arquivos ocultos (\".old\" ...)\n"
		"\t-s: Adiciona os padr�es dos fontes em \"C\"\n"
		"\t-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o\n"
		"\t-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o\n"
	);

	fprintf (stderr, somewhere_expand, sys_nm);

}	/* end do_puttree_help */
