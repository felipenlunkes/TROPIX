/*
 ****************************************************************
 *								*
 *			fsckt1.c				*
 *								*
 *	Verifica um sistema de arquivos				*
 *								*
 *	Vers�o	4.3.0, de 09.07.02				*
 *		4.8.0, de 17.07.05				*
 *								*
 *	M�dulo: fsckt1						*
 *		Utilit�rios Especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/stat.h>
#include <sys/mntent.h>
#include <sys/sb.h>
#include <sys/t1.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <setjmp.h>

#include "../h/fsckt1.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char		pgversion[] =  "Vers�o: 4.8.0, de 17.07.05";

entry int		fflag;		/* == 0: Pergunta; > 0: SIM; < 0: N�O */ 
entry int		pflag;		/* Modo de P�nico */
entry int		vflag;		/* Verbose */

const char		fstab_nm[] = "/etc/fstab";

entry jmp_buf		fs_env;		/* Para o caso de erro */

entry dev_t		root_dev;	/* Dispositivo Raiz */
entry int		dev_is_root;	/* O FS � a Raiz do Sistema */

entry const char	*fs_nm;	/* Nome do FS sendo verificado */
entry dev_t		fs_dev;		/* O Dispositivo */

entry int		read_only;	/* N�o � permitido escrever no FS */

entry int		dev_fd = -1;	/* Descritor para Leitura/Escrita */

entry int		fs_modified;	/* FS foi modificado */

entry CACHE		sb;		/* Superbloco */
entry CACHE		inoblk;		/* Bloco com INODEs */
entry CACHE		fileblk;	/* Bloco de Dados de um Arquivo */

entry char 		*disk_block_map; /* Mapa de blocos alocados no disco */
entry char 		*mem_block_map; /* Mapa de blocos alocados na mem�ria */

entry int 		fs_n_dup_blk;	/* Numero de blocos duplicados (por INODE) */

entry long		fs_file_block_sz; /* Tamanho do Arquivo Sendo Analisado */

entry DUPBLK		*dup_block_tb;	/* Endere�o da tabela */
entry int		dup_block_elem;	/* No. de entradas totais no momento */
entry int		dup_block_sz;	/* No. de entradas ocupadas no momento */

entry INO_HASH		*lost_found_ip;	/* INODE do Diret�rio "lost+found" */

entry long		fs_busy_ino;	/* Numero Total de INODEs ocupados no FS */
entry long		fs_busy_bl;	/* Numero Total de blocos ocupados no FS */

entry INO_HASH		**inode_hash_tb,  **link_place;

/*
 ****************************************************************
 *	Verifica um sistema de arquivos				*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	static int	i = 0;	/* Por causa de "set/longjmp" */
	FILE		*fp;
	STAT		root_s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "synpvH")) != EOF)
	{
		switch (opt)
		{
		    case 's':			/* Diz SIM � todas perguntas */
		    case 'y':
			fflag++;
			break;

		    case 'n':			/* Diz N�O � todas perguntas */
			fflag--;
			break;

		    case 'p':			/* Modo de P�nico */
			pflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			fprintf (stderr, "\n");
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Obt�m os dados da raiz do sistema
	 */
	if (stat ("/", &root_s) < 0)
		error ("$*N�o consegui obter o estado da raiz do sistema");

	root_dev = root_s.st_dev;

	/*
	 *	Prepara "error"
	 */
	error_default_function = next_dev;

	/*
	 *	Se n�o foram dados argumentos, l� o arquivo "/etc/fstab"
	 */
	if (*argv == NOSTR)
	{
		int		code;
		char		dev_nm[32];
		char		dir_nm[32];
		MNTENT		mntent;

		if ((fp = fopen (fstab_nm, "r")) == NOFILE)
			error ("$*N�o consegui abrir \"%s\"", fstab_nm);

		for (EVER)
		{
			setjmp (fs_env);

			if ((code = getmntent (fp, dev_nm, dir_nm, &mntent)) == EOF)
				break;

			if (code == 0)
				continue;

			if ((mntent.me_flags & SB_FSCK) == 0)
				continue;

			if (i++ > 0)
				printf ("\n");

			check (dev_nm);
		}

		fclose (fp);

		exit (0);
	}
	else	/* Nomes dos sistemas de arquivos dados */
	{
		static const char	**argv_static;

		argv_static = argv;	/* Por causa de "long/setjmp" */

		setjmp (fs_env);

		while (*argv_static != NOSTR)
		{
			if (i++ > 0)
				printf ("\n");

			check (*argv_static++);
		}
	}

	return (0);

}	/* end fsckt1 */

/*
 ****************************************************************
 *	Continua com o dispositivo seguinte			*
 ****************************************************************
 */
void
next_dev (int i)
{
	longjmp (fs_env, 1);	/* Vai para o dispositivo seguinte */

}	/* end next_dev */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - verifica a consist�ncia de sistemas de arquivos TROPIX T1\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-synpv] [<dev> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-s: Responde SIM a todas perguntas\n"
		"\t-y: Como acima\n"
		"\t-n: Responde N�O a todas perguntas\n"
		"\t-p: Modo de P�nico\n"
		"\t-v: verboso\n"
	);

	exit (2);

}	/* end help */
