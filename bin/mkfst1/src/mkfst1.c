/*
 ****************************************************************
 *								*
 *			mkfst1.c				*
 *								*
 *	Gera um sistema de arquivos TROPIX T1			*
 *								*
 *	Vers�o	4.3.0, de 04.07.02				*
 *		4.6.0, de 22.09.04				*
 *								*
 *	M�dulo: mkfst1						*
 *		Utilit�rios especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/syscall.h>
#include <sys/t1.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stat.h>
#include <unistd.h>

#include "../h/mkfst1.h"

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] = "Vers�o 4.6.0, de 22.09.04";

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	rflag;		/* Cria um arquivo regular */
entry int	fflag;		/* For�a: n�o pede confirma��o */
entry int	vflag;		/* Verbose */

entry const char *fs_nm;	/* Nome do Dispositivo */

entry int	fs_fd;		/* Descritor para leitura e escrita do FS */

entry T1SB	sb;		/* Superbloco */
entry char	bitmap[BL4SZ];	/* �rea para o Mapa de bits */

entry time_t	now_time;	/* Tempo de Cria��o */

/*
 ****************************************************************
 *	Gera um sistema de arquivos TROPIX T1			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	T1SB		*sp;
	daddr_t		fs_sz;
	const char	*boot1_nm;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "rfvH")) != EOF)
	{
		switch (opt)
		{
		    case 'r':			/* Cria o arquivo regular */
			rflag++;
			break;

		    case 'f':			/* For�a */
			fflag++;
			break;

		    case 'v':			/* Verboso */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Analisa o nome do dispositivo
	 */
	get_dev (*argv++);

	sp = &sb;

	if (sp->s_magic == T1_SBMAGIC)
	{
		if (vflag)
		{
			printf
			(	"O dispositivo \"%s\" "
				"j� cont�m um sistema de arquivos:\n\n",
				fs_nm
			);

			fs_sz = sp->s_fs_sz;

			printf
			(	"Tamanho do sistema:       %d (%s)\n"
				"Nome do volume:           \"%s\"\n"
				"Nome do dispositivo:      \"%s\"\n",
				fs_sz,
				cv_blocks_to_KB_MB_or_GB (fs_sz),
				sp->s_fname, sp->s_fpack
			);
		}
	}
	else		/* O No. m�gico n�o confere */
	{
		if (vflag) printf
		(	"O dispositivo \"%s\" ainda N�O cont�m "
			"um sistema de arquivos TROPIX T1\n\n",
			fs_nm
		);

		sp->s_fs_sz = 0;
		memset (sp->s_fname, '\0', sizeof (sp->s_fname));
		memset (sp->s_fpack, '\0', sizeof (sp->s_fpack));
	}

	/*
	 *	Analisa as op��es do programa
	 */
	analyse_arguments (argv);

	/*
	 *	Obt�m o nome do BOOT1
	 */
	boot1_nm = get_boot1_nm ();

	/*
	 *	Imprime os argumentos e pede confirma��o
	 */
	if (vflag)
		printf ("\nNovos argumentos:\n\n");

	if (fflag == 0)
	{
		printf
		(	"Dispositivo:              \"%s\"\n",
			fs_nm
		);
		printf
		( 	"Tipo da parti��o:         \"%s\"\n",
			fs_partnm
		);
		printf
		( 	"Arquivo de BOOT1:         \"%s\"\n",
			boot1_nm != NOSTR ? boot1_nm : "???"
		);
		fs_sz	= sp->s_fs_sz;

		printf
		(	"Tamanho do sistema:       %d (%s)\n"
			"Nome do volume:           \"%s\"\n"
			"Nome do dispositivo:      \"%s\"\n",
			fs_sz,
			cv_blocks_to_KB_MB_or_GB (fs_sz),
			sp->s_fname, sp->s_fpack
		);
	}

	if (fflag == 0)
	{
		fprintf
		(	stderr,
			"\n�ltima chance antes de escrever em \"%s\". "
			"Continua? (n): ",
			fs_nm
		);

		if (askyesno () <= 0)
			exit (0);
	}

	memset (sp->s_reser, 0, sizeof (sp->s_reser));

	/*
	 *	Tenta ler o �ltimo bloco do sistema.
	 *	Isto garantir� que o sistema cabe no dispositivo
	 */
	llseek (fs_fd, (loff_t)(sp->s_fs_sz - 1) << BL4SHIFT, NULL, L_SET);

	if (read (fs_fd, &bitmap, BL4SZ) != BL4SZ)
		error ("$O sistema de arquivos n�o cabe no dispositivo");

	/*
	 *	Obtem o tempo do sistema
	 */
	time (&now_time);

	/*
	 *	Escreve o BOOT1
	 */
	if (boot1_nm != NOSTR)
		write_boot_block (boot1_nm);

	/*
	 *	Gera os mapas de bits
	 */
	make_empty_bitmaps ();

	/*
	 *	Gera os diret�rios RAIZ e "LOST+FOUND"
	 */
	make_root_and_lost_dir ();

	/*
	 *	Finaliza a Gera��o
	 */
	fs_write (T1_SBNO, sp);

	fs_write (T1_BMNO, bitmap);

	fs_write (inode_bno, inode_block);

	fs_write (root_dir_bno, root_dir_image);

	fs_write (lost_dir_bno, lost_dir_image);

#if (0)	/*******************************************************/
	if (S_ISREG (dev_s.st_mode) && sync () < 0)
		error ("CUIDADO: N�O consegui atualizar os blocos do arquivo");
#endif	/*******************************************************/

	if (vflag)
		printf ("Fim do Programa\n");

	return (exit_code);

}	/* end main */

/*
 ****************************************************************
 *	Converte blocos em KB, MB ou GB				*
 ****************************************************************
 */
char *
cv_blocks_to_KB_MB_or_GB (long bl_cnt)
{
	static char	area[32];

	bl_cnt <<= (BL4SHIFT - BLSHIFT);	/* PROVIS�RIO */

	if   (bl_cnt < (10*MBSZ/BLSZ))		/* Menor do que 10 MB */
	{
		bl_cnt += (KBSZ/BLSZ/2);	/* Arredonda 0.5 KB */

		sprintf
		(	area,
			"%d KB",
			(unsigned)bl_cnt >> (KBSHIFT-BLSHIFT)
		);
	}
	elif (bl_cnt < (GBSZ/BLSZ))		/* De 10 MB at� 1024 MB */
	{
		bl_cnt += (MBSZ/BLSZ/(2 * 100)); /* Arredonda 0.005 MB */

		sprintf
		(	area,
			"%d.%02d MB",
			(unsigned)bl_cnt >> (MBSHIFT-BLSHIFT),
			(100 * ((unsigned)bl_cnt & (MBSZ/BLSZ - 1)))
					>> (MBSHIFT-BLSHIFT)
		);
	}
	else	/* 1024 MB ou acima */
	{
		bl_cnt += (GBSZ/BLSZ/(2 * 100)); /* Arredonda 0.005 GB */

		sprintf
		(	area,
			"%d.%02d GB",
			(unsigned)bl_cnt >> (GBSHIFT-BLSHIFT),
			(100 * ((unsigned)bl_cnt & (GBSZ/BLSZ - 1)))
					>> (GBSHIFT-BLSHIFT)
		);
	}

	return (area);

}	/* end cv_blocks_to_KB_MB_or_GB */

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
		"%s - gera um sistema de arquivos TROPIX T1\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-rfv] <dev> [<fs> [<vn> [<pn>]]]\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-r:        Se <dev> n�o existir, cria um arquivo regular\n"
		"\t-f:        Escreve no dispositivo sem confirma��o do usu�rio\n"
		"\t-v:        Verboso\n"
		"\nArgumentos:\n"
		"\t<dev>:     Nome do Dispositivo/Arquivo regular\n"
		"\t<fs>:      Tamanho do sistema de arquivos (normalmente em blocos\n"
		"\t           de 512 bytes); com o sufixo \"k\" ou \"K\" em KB, com o\n"
		"\t           sufixo \"m\" ou \"M\" em MB\n"
		"\t<vn>:      Nome do volume\n"
		"\t<pn>:      Nome do dispositivo f�sico\n"
		"\nObs.:\tArgumentos dados como \"-\" recebem um valor \"padr�o\". "
		"Argumentos\n\tn�o dados ou dados como \".\" s�o herdados do "
			"sistema anterior.\n"
	);

	exit (2);

}	/* end help */
