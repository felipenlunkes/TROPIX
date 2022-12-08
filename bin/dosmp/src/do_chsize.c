/*
 ****************************************************************
 *								*
 *			do_chsize.c				*
 *								*
 *	Altera o tamanho de um sistema de arquivos DOS		*
 *								*
 *	Vers�o	3.0.8, de 24.10.97				*
 *		3.0.8, de 24.10.97				*
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

#include <sys/common.h>
#include <sys/types.h>
#include <sys/kcntl.h>
#include <sys/stat.h>
#include <sys/disktb.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Tabela de dispositivos num�ricos ************************
 */
#define	DOS_SB	"dos_sb"	/* Nome do arquivo */

typedef struct disktb	DISKTB;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		check_file_clusters (void);
void		do_chsize_help (void);

/*
 ****************************************************************
 *	Altera o tamanho de um sistema de arquivos DOS		*
 ****************************************************************
 */
void
do_chsize (int argc, const char *argv[])
{
	UNI		*up = &uni;
	int		opt, fd;
	int		needed_sectors;
	int		free_clusters, needed_clusters;
	int		old_n_clusters, new_n_clusters;
	int		new_size, mb = 0;
	int		cyl_size;
	const char	*size_str = NOSTR, *str;
	DISKTB		ud;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "s:vH")) >= 0)
	{
		switch (opt)
		{
		    case 's':			/* Libera o espa�o pedido */
			size_str = cmd_optarg;
			break;

		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case 'H':			/* Help */
			do_chsize_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_chsize_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 0)
		{ do_chsize_help (); return; }

	/*
	 *	Retira o tamanho a liberar
	 */
	if (size_str && ((mb = strtol (size_str, &str, 0)) <= 0 || *str))
	{
		printf
		(	"%s: Tamanho inv�lido: \"%s\"\n",
			cmd_nm, size_str
		);
		return;
	}

	/*
	 *	Obt�m a entrada da parti��o
	 */
	if (kcntl (K_GET_DEV_TB, dev_dev, &ud) < 0)
	{
		printf
		(	"%s: N�o consegui a entrada da tabela de parti��es de \"%s\"\n",
			cmd_nm, dev_dev
		);
		return;
	}

	cyl_size = ud.p_head * ud.p_sect;

	/*
	 *	Verifica se a parti��o termina em um cilindro
	 */
	if ((ud.p_offset + ud.p_size) % cyl_size != 0)
	{
		printf
		(	"%s: CUIDADO: A parti��o n�o termina no final de um cilindro\n",
			cmd_nm
		);
	}

	/*
	 *	L� a FAT de tr�s para frente, e verifica o tamanho cont�guo
	 */
	free_clusters = check_file_clusters ();

	printf
	(
		"Tamanho atual da parti��o DOS            = %s\n",
		cv_blocks_to_MB (ud.p_size)
	);

	printf
	(
		"Tamanho atual do sistema de arquivos DOS = %s\n",
		cv_blocks_to_MB (up->u_end_fs_blkno)
	);

	printf
	(
		"Espa�o livre dispon�vel ao final         = %s\n",
		cv_blocks_to_MB (free_clusters * up->u_sectors_per_cluster)
	);

	if (mb == 0)	/* Se n�o vai alterar, termina */
		return;

	/*
	 ******	Altera o tamanho do sistema de arquivos *********
	 */
	if (fs_status == FS_MOUNT_RO)
	{
		printf
		(	"\n%s: O sistema de arquivos \"%s\" "
			"est� montado somente para leituras\n",
			cmd_nm, dev_nm
		);
		return;
	}

	/*
	 *	Calcula o n�mero de CLUSTERs necess�rios
	 */
	needed_sectors = (mb << (MBSHIFT-BLSHIFT)) + (cyl_size >> 1);

	needed_clusters = (needed_sectors + up->u_sectors_per_cluster - 1) / up->u_sectors_per_cluster;

	if (free_clusters < needed_clusters)
	{
		printf
		(	"\n%s: Espa�o livre insuficiente\n",
			cmd_nm
		);
		return;
	}

	/*
	 *	Calcula o novo tamanho
	 */
	old_n_clusters = up->u_n_clusters;

	new_n_clusters = up->u_n_clusters - needed_clusters;

	new_size = up->u_end_root_dir_blkno + new_n_clusters * up->u_sectors_per_cluster;

	/*
	 *	Arredonda para cilindros
	 */
	new_size = ((ud.p_offset + new_size + cyl_size - 1) / cyl_size) * cyl_size - ud.p_offset;

	new_n_clusters = (new_size - up->u_end_root_dir_blkno) / up->u_sectors_per_cluster;

	printf
	(
		"\n"
		"Tamanho novo da parti��o DOS             = %s (%d blocos)\n",
		cv_blocks_to_MB (new_size),
		new_size
	);

	printf
	(
		"Tamanho novo do sistema de arquivos DOS  = %s\n",
		cv_blocks_to_MB (new_size)
	);

	printf
	(
		"Tamanho da nova parti��o (a ser criada)  = %s (%d blocos)\n",
		cv_blocks_to_MB (ud.p_size - new_size),
		ud.p_size - new_size
	);

	/*
	 *	Verifica se o usu�rio concorda
	 */
	fprintf (stderr, "\nContinua? (n): ");

	if (askyesno () <= 0)
		return;

	/*
	 *	Salva o Superbloco atual
	 */
	if (access (DOS_SB, F_OK) >= 0)
	{
		fprintf
		(	stderr,
			"\nO arquivo " XSTR (DOS_SB) " j� existe. Reescreve? (n): "
		);

		if (askyesno () <= 0)
			goto change;

	}

	if ((fd = creat (DOS_SB, 0666)) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui criar o arquivo " XSTR (DOS_SB) " (%s)\n",
			cmd_nm, strerror (errno)
		);
		return;
	}

	if (write (fd, &sb, BLSZ) != BLSZ)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui salvar o superbloco do sistema de arquivos DOS (%s)\n",
			cmd_nm, strerror (errno)
		);
		return;
	}

	/*
	 *	Altera o valor
	 */
    change:
	PUT_LONG  (0, sb.s_big_size);
	PUT_SHORT (0, sb.s_little_size);

	if (new_size > 0xFFFF)
		PUT_LONG (new_size, sb.s_big_size);
	else
		PUT_SHORT (new_size, sb.s_little_size);

	/*
	 *	Usa o novo valor
	 */
	if (get_uni_block () < 0)
	{
		fprintf
		(	stderr,
			"%s: ERRO INTERNO - o novo superbloco est� inv�lido\n",
			"%s: Sistema de arquivos N�O alterado\n",
			cmd_nm, cmd_nm
		);
		exit (1);
	}

	/*
	 *	Grava o novo Superbloco
	 */
	up->u_infree -= (old_n_clusters - new_n_clusters);

	bwrite (0, &sb);

	if (up->u_sb_backup)
		bwrite (up->u_sb_backup, &sb);

	update_fat32_info ();

}	/* end do_chsize */

/*
 ****************************************************************
 *	Procuta clusters cont�guos do final para o in�cio	*
 ****************************************************************
 */
int
check_file_clusters (void)
{
	int		index, n = 0;

	/*
	 *	Examina do final para o in�cio
	 */
	get_whole_fat ();

	for (index = uni.u_n_clusters + 2 - 1; index >= 2; index--)
	{
		if (get_fat_value (index) != 0)
			break;

		n++;	/* Encontrou um CLUSTER livre */

	}	/* end for (procurando do final para o in�cio) */

	return (n);

}	/* end check_file_clusters */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_chsize_help (void)
{
	fprintf
	(	stderr,
		"%s - altera o tamanho do sistema de arquivos DOS\n"
		"\nSintaxe:\n"
		"\t%s [-s <n>]\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Sem op��es, informa o espa�o livre dispon�vel no final\n"
		"\t    do sistema de arquivos\n"
		"\t-s: Libera <n> MB do final do sistema de arquivos\n"
	);

}	/* end do_chsize_help */
