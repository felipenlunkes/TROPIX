/*
 ****************************************************************
 *								*
 *			fdisk.c					*
 *								*
 *	Altera a tabela de parti��o de discos			*
 *								*
 *	Vers�o	4.6.0, de 11.09.04				*
 *		4.9.0, de 24.12.07				*
 *								*
 *	M�dulo: fdisk						*
 *		Utilit�rios Sofisticados			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2007 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/syscall.h>
#include <sys/disktb.h>
#include <sys/stat.h>
#include <sys/kcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

#include "../h/common.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char		pgversion[] = "Vers�o: 4.9.0, de 24.12.07";

entry int		exit_code = 0;		/* C�digo de retorno */

entry int		gflag;			/* Tenta obter a geometria da tabela de parti��es */
entry int		vflag;			/* Verbose */

/*
 ****** Vari�veis globais ***************************************
 */
#define	DEBUG
#undef	NO_WRITE

entry const char	*file_nm;		/* Nome do dispositivo/arquivo */

entry const HDINFO	*fdisk_hdinfo;		/* Entrada de par�metros do disco */
entry daddr_t		fdisk_size;		/* Tamanho do disco */
entry daddr_t		fdisk_round;		/* Para arrendondar os endere�os */

enum		      { fdisk_parttb_orig_sect = 0 }; /* Endere�os das tabelas de parti��es */
entry daddr_t		fdisk_parttb_emer_sect;

entry int		fdisk_modified;		/* N�O zero se modificada */
entry int		fdisk_debug;		/* Debug ? */
entry int		fdisk_align = 1;	/* Aligned ? */

/*
 ****** Defini��es e vari�veis da tabela de parti��es ***********
 */
entry char		parttb_orig_block[BLSZ],	/* Os blocos das tabelas de parti��es */
			parttb_emer_block[BLSZ];

entry PARTTB		parttb[NPART];			/* A tabela de parti��es regular */
entry PARTTB		log_parttb[NPART][NLOGPART];	/* Idem, l�gicas */

entry daddr_t		fdisk_log_offset[NPART][NLOGPART]; /* Deslo. das par. l�gicas */

/*
 ******	Tabela "fict�cia" para os discos IDE ou  SCSI ***********
 */
entry HDINFO		generic_hdinfo;		/* Gen�rico */

/*
 ****** Tabela de tipos de sistemas de arquivos *****************
 */
const PARTNM	partnm[] =
{
	0x00,	"",		/* Vazio */
	0x01,	"DOS FAT12",
	0x02,	"XENIX root",
	0x03,	"XENIX usr",
	0x04,	"DOS FAT16 < 32 MB",
	0x05,	"DOS Extended",
	0x06,	"DOS FAT16 >= 32 MB",
	0x07,	"NTFS",
	0x08,	"AIX",
	0x09,	"AIX bootable",
	0x0A,	"OPUS",
	0x0B,	"DOS FAT32",
	0x0C,	"DOS FAT32 (L)",
	0x0E,	"DOS FAT16 (L)",
	0x0F,	"DOS Extended (L)",
	0x40,	"Venix 80286",
	0x4F,	"QNX",
	0x51,	"Novell (?)",
	0x52,	"Microport",
	0x63,	"GNU HURD",
	0x64,	"Novell",
	0x75,	"PC/IX",
	0x80,	"old MINIX",
	0x81,	"LINUX/MINIX",
	0x82,	"LINUX swap",
	0x83,	"LINUX ext",
	0x93,	"Amoeba",
	0x94,	"Amoeba BBT",
	0xA5,	"BSD 4.2",
	0xA8,	"TROPIX V7",
	0xA9,	"TROPIX T1",
	0xAA,	"TROPIX fs3",
	0xAE,	"TROPIX Extended",
	0xAF,	"TROPIX swap",
	0xB7,	"BSDI fs",
	0xB8,	"BSDI swap",
	0xC7,	"Syrinx",
	0xDB,	"CP/M",
	0xE1,	"DOS access",
	0xE3,	"DOS R/O",
	0xF2,	"DOS Secondary",
	0xFF,	"BBT",

	-1,	"???"		/* Final da tabela */
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		fdisk_print_MB (daddr_t size, int width);
void		print_part_type_nm (int type);
int		fdisk_read_parttb (int fd);
void		fdisk_print_parttb (int);
void		fdisk_print_parttb_entry (const PARTTB *, int);
void		fdisk_debug_print_parttb_entry (int, const PARTTB *);
void		fdisk_get_cmd (char *, int fd);
void		fdisk_print_empty_spaces (void);
int		fdisk_make_regular_partition (void);
int		fdisk_make_extended_partition (void);
int		fdisk_make_logical_partition (void);
int		fdisk_make_partition (PARTINFO *);
int		fdisk_change_partition_size (void);
int		fdisk_change_regular_partition_size (const PARTINFO *);
int		fdisk_change_logical_partition_size (const PARTINFO *);
int		fdisk_good_regular_area (daddr_t, daddr_t);
int		fdisk_good_logical_area (int, daddr_t, daddr_t);
PARTTB		*fdisk_get_old_parttb_no (PARTINFO *);
PARTTB		*fdisk_get_new_parttb_no (PARTINFO *);
int		fdisk_check_scsi_addressing (const PARTTB *);
void		fdisk_sort_logical_partitions (int);
void		fdisk_put_phys_addr (PARTTB *, daddr_t, daddr_t);
void		fdisk_write_all_logical_chains (int);
void		fdisk_write_logical_chain (int, int);
daddr_t		fdisk_round_down (daddr_t);
daddr_t		fdisk_round_up (daddr_t);
void		fdisk_print_part_name (PARTINFO *);
void		fdisk_print_sys_types (void);
void		fdisk_help (void);
void		help (void);

/*
 ****************************************************************
 *	Imprime e/ou modifica a tabela de parti��es dos discos	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, fd;
	const DISKTB	*dp;
	const char	*cp;
	HDINFO		*gp;
	STAT		s;
	DISKTB		dt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "gvNH")) != EOF)
	{
		switch (opt)
		{
		    case 'g':			/* Tenta obter a geometria da tabela de parti��es */
			gflag++;
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

	if (argc != 1)
		help ();

	/*
	 *	Abre o dispositivo
	 */
	if ((fd = open (file_nm = argv[0], O_RDWR)) < 0 || fstat (fd, &s) < 0)
		error ("$*N�o consegui abrir \"%s\"", file_nm);

	if ((cp = strrchr (file_nm, '/')) != NOSTR)
		file_nm = cp + 1;

	if (kcntl (K_GET_DEV_TB, s.st_rdev, &dt) < 0)
		dp = NODISKTB;
	else
		dp = &dt;

	/*
	 *	L� o SuperBloco Original
	 */
   /***	llseek (fd, (loff_t)fdisk_parttb_orig_sect << BLSHIFT, NULL, L_SET); ***/

	if (read (fd, parttb_orig_block, BLSZ) != BLSZ)
		error ("$*Erro de leitura");

	if (*(ushort *)(parttb_orig_block + MAGIC_OFF) != 0xAA55)
		printf ("\n*** O bloco da tabela de parti��es N�O cont�m \"0x55AA\"\n");

	memmove (parttb, parttb_orig_block + PARTB_OFF, sizeof (parttb));

	/*
	 *	Atribui o esquema de endere�amento
	 */
	gp = &generic_hdinfo;

	if (dp != NODISKTB)
	{
		if (isdigit (strend (dp->p_name)[-1]))
		{
			printf
			(	"\e[31m"
				"\nCUIDADO: O dispositivo \"%s\" � uma parti��o\n"
				"\e[0m",
				dp->p_name
			);
		}

		fdisk_size = dp->p_size;

		if (dp->p_head != 0 && dp->p_sect != 0)
			{ gp->h_head = dp->p_head; gp->h_sect = dp->p_sect; gp->h_cyl = dp->p_cyl; }

		if (dt.p_flags & DISK_INT13_EXT)
			gp->h_flags |= HD_INT13_EXT;
	}
	else
	{
		fdisk_size = s.st_size >> BLSHIFT;
	}

	if (gflag || gp->h_head == 0 || gp->h_sect == 0)
		geo_get_parttb_geo (parttb, gp, fdisk_size, file_nm, 1);

	if (gp->h_sect != 0)
		fdisk_parttb_emer_sect = gp->h_sect - 1;

#ifdef	DEBUG
	if (fdisk_debug)
		printf ("%d\n", fdisk_parttb_emer_sect);
#endif	DEBUG

	fdisk_hdinfo = gp;

	fdisk_round = gp->h_head * gp->h_sect;

	/*
	 *	Tenta ler a tabela de parti��es de emerg�ncia
	 */
	if (fdisk_parttb_emer_sect)
	{
		llseek (fd, (loff_t)fdisk_parttb_emer_sect << BLSHIFT, NULL, L_SET);

		if (read (fd, parttb_emer_block, BLSZ) != BLSZ)
			error ("$*Erro de leitura");

		if (!memeq (parttb, parttb_emer_block + PARTB_OFF, sizeof (parttb)))
		{
			printf
			(	"\e[34m"
				"\n***** A Tabela de parti��es de emerg�ncia est� diferente da regular\n"
				"\e[0m"
			);

			fdisk_modified++;
		}
	}

	/*
	 *	Processa os comandos
	 */
	if (fdisk_read_parttb (fd) < 0)
		return (1);

	fdisk_get_cmd ("", fd);

	return (exit_code);

}	/* end fdisk */

/*
 ****************************************************************
 *	Le um comando para alterar a tabela			*
 ****************************************************************
 */
void
fdisk_get_cmd (char *cmd, int fd)
{
	char		*cp;
	char		line[80];
	PARTTB		*pp;
	PARTINFO	info;
	HDINFO		*gp = &generic_hdinfo;
	int		index;
	char		type, bad;
	HDINFO		hi;

	/*
	 *	Na primeira vez, recebe o comando
	 */
	cp = cmd;

	/*
	 *	analisa a linha lida
	 */
    execute_cmd:
	for (/* acima ou abaixo */; (*cp == ' ' || *cp == '\t'); cp++)
		/* vazio */;

	if (*cp == '-')
		cp++;

	switch (*cp)
	{
		/*
		 ******	Ajuda ***********************************
		 */
	    case '?':
		fdisk_help ();
		break;

		/*
		 ******	Imprime a tabela ************************
		 */
	    case '\0':
		fdisk_print_parttb (0 /* Sem espa�os vagos */);
		break;

	    case 'p':
		fdisk_print_parttb (1 /* Com espa�os vagos */);
		break;

		/*
		 ******	Troca o estado (ativo/n�o ativo) ********
		 */
	    case 'a':
		if ((pp = fdisk_get_old_parttb_no (&info)) == NOPARTTB)
			break;

		if (pp->pt_active)
		{
			pp->pt_active = 0;
		}
		elif (IS_EXT (pp->pt_type))
		{
			printf ("\nParti��es estendidas N�O podem estar ativas\n");
			break;
		}
		else
		{
			pp->pt_active = 0x80;
		}

		/*
		 *	Verifica se h� problema com cilindros maiores do que 1023
		 */
		if
		(	pp->pt_active && pp->pt_offset + pp->pt_size >= 255 * 63 * 1024 &&
			(gp->h_flags & HD_INT13_EXT) == 0
		)
		{
			printf
			(	"\e[34m"
				"\nCUIDADO: Parti��o ativa terminando em cilindro maior do que 1023\n"
				"\e[0m"
			);
		}

		fdisk_modified++;
		fdisk_print_parttb (0 /* sem espa�os vagos */);

		break;

		/*
		 ******	Imprime os tipos ************************
		 */
	    case 'l':
		fdisk_print_sys_types ();
		break;

		/*
		 ******	Imprime os espa�o vago ******************
		 */
	    case 's':
		fdisk_print_empty_spaces ();
		break;

		/*
		 ******	Troca o tipo ****************************
		 */
	    case 't':
		if ((pp = fdisk_get_old_parttb_no (&info)) == NOPARTTB)
			break;

		printf ("\nImprime os tipos das parti��es? (n): ");

		if (askyesno () > 0)
			fdisk_print_sys_types ();

		printf ("\nD� o tipo desejado (hexadecimal): ");

		gets (line);

		if (line[0] == 'n')
			break;

		if ((index = strtol (line, (const char **)NULL, 16)) & ~0xFF)
			{ printf ("\nTipo inv�lido: \"%s\"\n", line); break; }

		if (IS_EXT (pp->pt_type) ^ IS_EXT (index))
		{
			printf ("\nTroca  de tipos inv�lida\n");
			break;
		}

		pp->pt_type = index;

		/*
		 *	D� recomenda��es sobre parti��es DOS
		 */
		bad = 0;

		if (gp->h_flags & HD_INT13_EXT)		/* H� extens�es */
		{
			if (IS_DOS_G (pp->pt_type))
				bad++;
		}
		else					/* N�o h� extens�es */
		{
			if (IS_DOS_L (pp->pt_type))
				bad++;
		}

		if (bad)
		{
			printf
			(	"\e[34m"
				"\nCUIDADO: Tipo de parti��o DOS FAT16/32 incompat�vel com BIOS\n"
				"\e[0m"
			);
		}

		fdisk_modified++;
		fdisk_print_parttb (0 /* sem espa�os vagos */);
		break;

		/*
		 ******	Cria uma parti��o nova ******************
		 */
	    case 'n':
	    case_n:
		printf
		(	"\nD� o tipo desejado: regular (r), "
			"estendida (e) ou l�gica (l): "
		);

		gets (line);

		if (line[0] == 'n')
			break;

		switch (line[0])
		{
		    case 'r':
			index = fdisk_make_regular_partition ();
			break;

		    case 'e':
			index = fdisk_make_extended_partition ();
			break;

		    case 'l':
			index = fdisk_make_logical_partition ();
			break;

		    default:
			goto case_n;

		}	/* end switch (line[0]) */

		if (index < 0)
			break;

		fdisk_modified++;
		fdisk_print_parttb (0 /* sem espa�os vagos */);
		break;

		/*
		 ******	Remove uma parti��o *********************
		 */
	    case 'd':
		if ((pp = fdisk_get_old_parttb_no (&info)) == NOPARTTB)
			break;

		type = pp->pt_type;

		if
		(	info.f_log_index < 0 && IS_EXT (type) &&
			log_parttb[info.f_reg_index][0].pt_size
		)
		{
			printf
			(	"\nEsta parti��o estendida ainda "
				"cont�m parti��o(�es) l�gica(s)!\n"
			);
		}

		printf ("\nRemove realmente a parti��o \"");
		fdisk_print_part_name (&info);
		printf ("\" (");
		print_part_type_nm (type);
		printf (")? (n): ");

		if (askyesno () <= 0)
			break;

		memset (pp, 0, sizeof (PARTTB));

		if (info.f_log_index >= 0)
			fdisk_sort_logical_partitions (info.f_reg_index);

		fdisk_modified++;
		fdisk_print_parttb (0 /* sem espa�os vagos */);
		break;

		/*
		 ******	Altera o tamanho de uma parti��o ************
		 */
	    case 'm':
		if (fdisk_change_partition_size () >= 0)
			fdisk_modified++;

		fdisk_print_parttb (0 /* sem espa�os vagos */);
		break;

		/*
		 ****** Obt�m a geometria ***********************
		 */
	    case 'g':
		if (geo_get_parttb_geo (parttb, &hi, 0, file_nm, 0) < 0)
			{ printf ("\nN�o consegui obter a geometria\n"); break; }

		printf
		(	"\nGeometria = (%d, %d), %sconfere\n",
			hi.h_head, hi.h_sect,
			gp->h_head == hi.h_head && gp->h_sect == hi.h_sect ? "" : "\e[34mN�O\e[0m "
		);

		break;

		/*
		 ****** Usa a tabela de emerg�ncia **************
		 */
	    case 'e':
		if (fdisk_parttb_emer_sect == 0)
		{
			printf
			(	"\nN�O foi encontrado um local adequado para "
				"a tabela de parti��es de emerg�ncia\n"
			);
			break;
		}

		memmove (parttb, parttb_emer_block + PARTB_OFF, sizeof (parttb));

		if (fdisk_read_parttb (fd) < 0)
			return;

		fdisk_print_parttb (0 /* Sem espa�os vagos */);
		break;

		/*
		 ******	Reescreve a tabela de parti��es *********
		 */
	    case 'w':
		if (fdisk_modified == 0)
			printf ("\nA tabela n�o foi modificada\n");

		printf ("\nReescreve a tabela de parti��es? (n): ");

		if (askyesno () <= 0)
			break;

		fdisk_write_all_logical_chains (fd);

		memmove (parttb_orig_block + PARTB_OFF, parttb, NPART * sizeof (PARTTB));

		*(ushort *)(parttb_orig_block + MAGIC_OFF) = 0xAA55;
#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", fdisk_parttb_orig_sect);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", fdisk_parttb_orig_sect);
#endif	DEBUG
		llseek (fd, (loff_t)fdisk_parttb_orig_sect << BLSHIFT, NULL, L_SET);

		if (write (fd, parttb_orig_block, BLSZ) != BLSZ)
			error ("$*Erro de escrita");
#endif	NO_WRITE

		fdisk_modified = 0;

		if (fdisk_parttb_emer_sect == 0)
		{
			printf
			(	"\nN�O foi encontrado um local adequado para "
				"a tabela de parti��es de emerg�ncia\n"
			);
			break;
		}

		memset (parttb_emer_block, 0, BLSZ);

		memmove (parttb_emer_block + PARTB_OFF, parttb, NPART * sizeof (PARTTB));

#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", fdisk_parttb_emer_sect);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", fdisk_parttb_emer_sect);
#endif	DEBUG
		llseek (fd, (loff_t)fdisk_parttb_emer_sect << BLSHIFT, NULL, L_SET);

		if (write (fd, parttb_emer_block, BLSZ) != BLSZ)
			error ("$*Erro de escrita");
#endif	NO_WRITE

		break;

		/*
		 ******	Termina sem reescrever a tabela de parti��es **
		 */
	    case 'q':
		if (fdisk_modified == 0)
			return;

		printf ("\nA tabela de parti��es regular/emerg�ncia N�O est� atualizada!\n");

		printf ("\nTermina a execu��o de \"fdisk\" (sem atualiz�-las)? (n): ");

		if (askyesno () > 0)
			return;

		break;

		/*
		 ******	Liga/desliga DEBUG **********************
		 */
#ifdef	DEBUG
	    case 'G':
		fdisk_debug ^= 1;
		printf ("\nDepura��o %sLIGADA\n", fdisk_debug ? "" : "DES");
		break;
#endif	DEBUG
		/*
		 ******	Liga/desliga o alinhamento **************
		 */
	    case 'u':
		fdisk_align ^= 1;
		printf ("\nAlinhamento de parti��es %sLIGADO\n", fdisk_align ? "" : "DES");
		break;

		/*
		 ******	Inv�lido ********************************
		 */
	    default:
		printf ("\nComando inv�lido: \"%s\"\n", cp);
		break;

	}	/* end switch (caracter do comando) */

	/*
	 *	Escreve o prompt e le uma linha
	 */
	printf ("\nfdisk> ");

	if ((cp = gets (line)) == NOSTR)
		cp = "q";

	goto execute_cmd;

}	/* end fdisk_get_cmd */

/*
 ****************************************************************
 *	Obt�m as parti��es de um disco				*
 ****************************************************************
 */
int
fdisk_read_parttb (int fd)
{
	int		reg_index, log_index;
	PARTTB		*reg_pp, *log_pp;
	const PARTTB	*pp;
	daddr_t		log_offset, ext_begin, ext_end;
	char		area[BLSZ];

	/*
	 *	A tabela inicial j� foi lida; faltam apenas as parti�es l�gicas
	 */
   /***	fdisk_modified = 0; ***/

	memsetl (log_parttb, 0, sizeof (log_parttb) / sizeof (long));
	memsetl (fdisk_log_offset, 0, sizeof (fdisk_log_offset) / sizeof (long));

	/*
	 *	Copia as parti��es estendidas
	 */
	for (reg_index = 0, reg_pp = &parttb[0]; reg_index < NPART; reg_index++, reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

#if (0)	/*******************************************************/
printf ("Parti��o reg %d: %d, %d\n", reg_index, reg_pp->pt_offset, reg_pp->pt_size);
#endif	/*******************************************************/

		/*
		 *	Temos uma parti��o estendida
		 */
		if (!IS_EXT (reg_pp->pt_type))
			continue;

		ext_begin = reg_pp->pt_offset;
		ext_end   = reg_pp->pt_offset + reg_pp->pt_size;

		log_offset = ext_begin;

		/*
		 *	Percorre a cadeia de parti��es l�gicas
		 */
		for (log_index = 0, log_pp = &log_parttb[reg_index][0]; /* abaixo */; log_index++, log_pp++)
		{
			if (log_offset < ext_begin || log_offset >= ext_end)
			{
				printf
				(	"\n*** A cadeia de parti��es l�gicas "
					"da parti��o estendida %d cont�m "
					"um ponteiro inv�lido: %d\n\n",
					reg_index, log_offset
				);
				break;
			}

			llseek (fd, (loff_t)log_offset << BLSHIFT, NULL, L_SET);

			if (read (fd, area, BLSZ) != BLSZ)
				error ("$*Erro de leitura");

			if (*(ushort *)(area + MAGIC_OFF) != 0xAA55)
			{
				printf
				(	"\n*** O bloco %d da cadeia de "
					"parti��es l�gicas da parti��o "
					"estendida %d N�O cont�m \"0x55AA\"\n\n",
					log_offset, reg_index
				);
				break;
			}

			pp = (PARTTB *)(area + PARTB_OFF);
#ifdef	DEBUG
			if (fdisk_debug)
			{
				printf
				(	"\nParti��o l�gica "
					"(estendida %d, bloco %d):\n\n",
					reg_index, log_offset
				);

				fdisk_debug_print_parttb_entry (0, pp + 0);
				fdisk_debug_print_parttb_entry (1, pp + 1);

				printf ("\n");
			}
#endif	DEBUG
			if (pp[0].pt_size == 0)	/* Primeiro m�todo de EOF */
				break;

			/*
			 *	Verifica se ainda tem espa�o
			 */
			if (log_index >= NLOGPART)
			{
				printf
				(	"\n*** N�mero excessivo de parti��es "
					"l�gicas na parti��o estendida %d\n\n",
					reg_index
				);
				break;
			}

			/*
			 *	Achou uma parti��o l�gica
			 */
			memmove (log_pp, pp, sizeof (PARTTB));

			fdisk_log_offset[reg_index][log_index] = pp[0].pt_offset;

			log_pp->pt_offset += log_offset;

#if (0)	/*******************************************************/
printf ("Parti��o log %d: %d, %d\n", log_index, log_pp->pt_offset, log_pp->pt_size);
#endif	/*******************************************************/
			/*
			 *	Uma parti��o l�gica N�O pode ser EXT
			 */
			if (IS_EXT (log_pp->pt_type))
			{
				printf
				(	"\n*** Tipo inv�lido para parti��o "
					"l�gica: 0x%02X\n\n",
					log_pp->pt_type
				);
			}

			/*
			 *	Procura a parti��o seguinte
			 */
			if (pp[1].pt_size == 0)	/* Segundo m�todo de EOF */
				break;

			log_offset = ext_begin + pp[1].pt_offset;

		}	/* end for (cadeia de parti��es l�gicas) */

	}	/* end for (parti��es estendidas) */

	return (0);

}	/* end fdisk_read_parttb */

/*
 ****************************************************************
 *	Imprime a tabela de parti��es DOS			*
 ****************************************************************
 */
void
fdisk_print_parttb (int empty)
{
	int		reg_index, log_index, seq_index;
	const PARTTB	*reg_pp, *log_pp;
	const HDINFO	*gp = fdisk_hdinfo;
	int		align_value;
	daddr_t		min_size = fdisk_align ? fdisk_round : 4 * gp->h_sect;
	daddr_t		last_reg_end = fdisk_align ? gp->h_sect : 1;
	daddr_t		last_log_end;
	daddr_t		reg_size, log_size;

	/*
	 *	Escreve o n�mero de cabe�as, ...
	 */
	printf ("\nDisco \"%s\": ", file_nm);
	fdisk_print_MB (fdisk_size, 0);
	printf
	(	" MB (%d blocos), geo = (%d, %d, %d, %s)\n",
		fdisk_size, gp->h_cyl, gp->h_head, gp->h_sect,
		(gp->h_flags & HD_INT13_EXT) ? "L" : "G"
	);

	/*
	 *	P�e o cabe�alho
	 */
	printf
	(	"\n IND. -DEV-  A %c --IN�CIO-- ---FINAL-- --BLOCOs--  TAM (MB)  TIPO\n\n",
		fdisk_align ? 'D' : ' '
	);

	/*
	 *	Malha pela tabela
	 */
	for (reg_index = 0, seq_index = 1, reg_pp = parttb; /* abaixo */; reg_index++, reg_pp++)
	{
		/* Em primeiro lugar, imprime espa�os vagos */

		if (empty && (reg_pp->pt_size != 0 || reg_index >= NPART))
		{
			if (reg_index >= NPART)
				reg_size = fdisk_size - last_reg_end;
			else
				reg_size = reg_pp->pt_offset - last_reg_end;

			if (reg_size >= min_size)
			{
				printf
				(	"      ..........."
					"............."
					"............."
					"...... "
				);
				fdisk_print_MB (reg_size, 1);
				printf ("  ............\n");
			}
		}

		if (reg_index >= NPART)
			break;

		if (reg_pp->pt_size == 0)
			continue;

		last_reg_end = reg_pp->pt_offset + reg_pp->pt_size;

		/*
		 *	Agora imprime a parti��o regular
		 */
		printf ("%4d  ", seq_index++);

		printf ("%s%d  ", file_nm, reg_index + 1);

		/*
		 *	Verifica se est� alinhada
		 */
		align_value = ' ';	/* Sup�e que ' ' est� contido em '0' */

		if (fdisk_align)
		{
			daddr_t		begin = reg_pp->pt_offset;

			if (begin != gp->h_sect && begin % fdisk_round)
				align_value |= '1';
		
			if ((begin + reg_pp->pt_size) % fdisk_round)
				align_value |= '2';
		}

		fdisk_print_parttb_entry (reg_pp, align_value);

		/*
		 *	Verifica se � uma parti��o estendida
		 */
		if (!IS_EXT (reg_pp->pt_type))
			continue;

		last_log_end = reg_pp->pt_offset + (fdisk_align ? gp->h_sect : 1);

		for (log_index = 0, log_pp = &log_parttb[reg_index][0]; /* abaixo */; log_index++, log_pp++)
		{
			/* Em primeiro lugar, imprime espa�os vagos */

			if (empty)
			{
				if (log_index >= NLOGPART || log_pp->pt_size == 0)
					log_size = reg_pp->pt_offset + reg_pp->pt_size - last_log_end;
				else
					log_size = log_pp->pt_offset - last_log_end;

				if (log_size >= min_size)
				{
					printf
					(	"      ..........."
						"............."
						"............."
						"...... "
					);
					fdisk_print_MB (log_size, 1);
					printf ("  ............\n");
				}
			}

			if (log_index >= NLOGPART || log_pp->pt_size == 0)
				break;

			last_log_end = log_pp->pt_offset + log_pp->pt_size;

			/*
			 *	Agora Imprime a parti��o l�gica
			 */
			printf ("%4d  ", seq_index++);

			printf
			(	"%s%d%c ", file_nm,
				reg_index + 1, log_index + 'a'
			);

			/*
			 *	Verifica se est� alinhada
			 */
			align_value = ' ';	/* Sup�e que ' ' est� contido em '0' */

			if (fdisk_align)
			{
				daddr_t		begin = log_pp->pt_offset;

				if ((begin + log_pp->pt_size) % fdisk_round)
					align_value |= '2';

				if (begin % gp->h_sect)
					align_value |= '1';

				begin -= gp->h_sect;

				if (begin != gp->h_sect && begin % fdisk_round)
					align_value |= '1';
			}

			fdisk_print_parttb_entry (log_pp, align_value);

		}	/* end malha pelas parti��es l�gicas */

	}	/* end malha pela tabela */

}	/* end fdisk_print_parttb */

/*
 ****************************************************************
 *	Imprime uma entrada da tabela de parti��es DOS		*
 ****************************************************************
 */
void
fdisk_print_parttb_entry (const PARTTB *pp, int align_value)
{
	if   (pp->pt_active == 0x00)
		printf ("   ");
	elif (pp->pt_active == 0x80)
		printf (" * ");
	else
		printf (" %02X", pp->pt_active);

	printf ("%c ", align_value);

	printf
	(	"%10d " "%10d " "%10d ",
		pp->pt_offset,
		pp->pt_offset + pp->pt_size - 1,
		pp->pt_size
	);

	fdisk_print_MB (pp->pt_size, 1);

	printf ("  %02X ", pp->pt_type);
	print_part_type_nm (pp->pt_type);

	printf ("\n");

}	/* end fdisk_print_parttb_entry */

/*
 ****************************************************************
 *	Escreve o tipo de uma parti��o				*
 ****************************************************************
 */
void
print_part_type_nm (int type)
{
	const PARTNM	*pnm;

	for (pnm = partnm; /* abaixo */; pnm++)
	{
		if (pnm->pt_type < 0)
			{ printf ("??? (0x%2X)", type); break; }

		if (pnm->pt_type == type)
			{ printf ("%s", pnm->pt_nm); break; }
	}

}	/* end print_part_type_nm */

#ifdef	DEBUG
/*
 ****************************************************************
 *	Imprime o conte�do de uma entrada de parti��es DOS	*
 ****************************************************************
 */
void
fdisk_debug_print_parttb_entry (int index, const PARTTB *pp)
{
	const PARTNM	*pnm;

	/*
	 *	Procura o tipo na tabela (termina com -1)
	 */
	for (pnm = partnm; pnm->pt_type >= 0; pnm++)
	{
		if (pnm->pt_type == pp->pt_type)
			break;
	}

	printf ("%2d:  ", index + 1);

	if   (pp->pt_active == 0x00)
		printf ("   ");
	elif (pp->pt_active == 0x80)
		printf ("*  ");
	else
		printf ("%02X ", pp->pt_active);

	printf
	(	"%9d %9d  ",
		pp->pt_offset, pp->pt_size
	);

	printf
	(	"(%4d,%2d,%2d) ",
		pp->pt_start.cyl | ((pp->pt_start.sect & 0xC0) << 2),
		pp->pt_start.head,
		pp->pt_start.sect & 0x3F
	);

	printf
	(	"(%4d,%2d,%2d)  ",
		pp->pt_end.cyl | ((pp->pt_end.sect & 0xC0) << 2),
		pp->pt_end.head,
		pp->pt_end.sect & 0x3F
	);

	if (pnm->pt_type >= 0)
		printf ("%s\n", pnm->pt_nm);
	else
		printf ("%02X\n", pp->pt_type);

}	/* end fdisk_debug_print_parttb_entry */
#endif	DEBUG

/*
 ****************************************************************
 *	Imprime os espa�os vagos do disco			*
 ****************************************************************
 */
void
fdisk_print_empty_spaces (void)
{
	int		reg_index, log_index, last_index = -1;
	const PARTTB	*reg_pp, *log_pp;
	const HDINFO	*gp = fdisk_hdinfo;
	daddr_t		min_size = fdisk_align ? fdisk_round : 4 * gp->h_sect;
	daddr_t		last_end = fdisk_align ? gp->h_sect : 1;
	daddr_t		size, total = 0;
	const char	*nm = file_nm;

	printf
	(	
		"\n�reas vagas do disco \"%s\": %d blocos (",
		nm, fdisk_size
	);
	fdisk_print_MB (fdisk_size, 0);
	printf (" MB)\n\n");

	/*
	 *	Percorre as parti��es regulares
	 */
	for (reg_index = 0, reg_pp = parttb; /* abaixo */; reg_index++, reg_pp++)
	{
		if (reg_index < NPART && reg_pp->pt_size == 0)
			continue;

		if (reg_index >= NPART)
			size = fdisk_size - last_end;
		else
			size = reg_pp->pt_offset - last_end;

		if (size >= min_size)
		{
			fdisk_print_MB (size, 1);

			if (last_index < 0)
			{
				if (reg_index >= NPART)
				{
					printf (" MB\tO disco ainda n�o possui parti��es\n");
				}
				else
				{
					printf (" MB\tAntes da parti��o \"%s%d\"\n", nm, reg_index + 1);
				}
			}
			else	/* J� viu no m�nimo um parti��o */
			{
				if (reg_index < NPART)
				{
					printf
					(	" MB\tEntre as parti��es \"%s%d\" e \"%s%d\"\n",
						nm, last_index + 1, nm, reg_index + 1
					);
				}
				else
				{
					printf (" MB\tAp�s a parti��o \"%s%d\"\n", nm, last_index + 1);
				}
			}

			total += size;
		}

		if (reg_index >= NPART)
			break;

		if (IS_EXT (reg_pp->pt_type))
		{
			size = reg_pp->pt_size;

			for
			(	log_index = 0, log_pp = &log_parttb[reg_index][0];
				log_index < NLOGPART;
				log_index++, log_pp++
			)
			{
				if (log_pp->pt_size == 0)
					break;

				size -= (log_pp->pt_size + fdisk_log_offset[reg_index][log_index]);
			}

			if (size >= min_size)
			{
				fdisk_print_MB (size, 1);

				printf (" MB\tNa parti��o estendida \"%s%d\"\n", nm, reg_index + 1);

				total += size;
			}
		}

		last_end   = reg_pp->pt_offset + reg_pp->pt_size;
		last_index = reg_index;

	}	/* end (percorrendo as parti��es regulares */

	/*
	 *	D� o total
	 */
	printf ("\n");

	fdisk_print_MB (total, 1);

	printf (" MB\tTOTAL\n");

}	/* end fdisk_print_empty_spaces */

/*
 ****************************************************************
 *	Cria uma parti��o regular				*
 ****************************************************************
 */
int
fdisk_make_regular_partition (void)
{
	PARTINFO	info;

	/*
	 *	Obt�m uma entrada adequada
	 */
	if (fdisk_get_new_parttb_no (&info) == NOPARTTB)
		return (-1);

	return (fdisk_make_partition (&info));

}	/* end fdisk_make_regular_partition */

/*
 ****************************************************************
 *	Cria uma parti��o estendida				*
 ****************************************************************
 */
int
fdisk_make_extended_partition (void)
{
	PARTTB		*pp;
	PARTINFO	info;
	int		code;
	char		line[32];

	/*
	 *	Procura uma entrada
	 */
	if ((pp = fdisk_get_new_parttb_no (&info)) == NOPARTTB)
		return (-1);

	/*
	 *	Pergunta o tipo de estendida
	 */
    again:
	printf
	(	"\nD� o tipo da parti��o estendida: "
		"DOS (d) ou TROPIX (x): "
	);

	gets (line);

	if (line[0] == 'n')
		return (-1);

	switch (line[0])
	{
	    case 'd':
		if (fdisk_hdinfo->h_flags & HD_INT13_EXT)	/* H� extens�es */
			code = DOS_EXT_L;
		else
			code = DOS_EXT_G;
		break;

	    case 'x':
		code = TROPIX_EXT;
		break;

	    default:
		goto again;

	}	/* end switch */

	/*
	 *	Cria a entrada
	 */
	if (fdisk_make_partition (&info) < 0)
		return (-1);

	pp->pt_type = code;

	/*
	 *	Zera as parti��es l�gicas desta parti��o estendida
	 */
	memsetl
	(	log_parttb[info.f_reg_index],
		0,
		NLOGPART * sizeof (PARTTB) / sizeof (long)
	);

	memsetl (fdisk_log_offset[info.f_reg_index], 0, NLOGPART);

	return (0);

}	/* end fdisk_make_extended_partition */

/*
 ****************************************************************
 *	Cria uma parti��o regular ou estendida			*
 ****************************************************************
 */
int
fdisk_make_partition (PARTINFO *ip)
{
	PARTTB		*pp;
	const HDINFO	*gp = fdisk_hdinfo;
	int		i;
	daddr_t		begin, pend, size;
	char		line[80];

	/*
	 *	Obt�m um come�o
	 */
	for (pp = ip->f_pp - 1; /* abaixo */; pp--)
	{
		if (pp < parttb)
			{ begin = fdisk_align ? gp->h_sect : 1; break; }

		if (pp->pt_size > 0)
			{ begin = fdisk_round_up (pp->pt_offset + pp->pt_size); break; }
	}

	if (fdisk_good_regular_area (begin, begin) >= 0)
	{
		printf ("\nBloco inicial = %d? (s): ", begin);

		if (askyesno () < 0)
			goto ask_begin;
	}
	else
	{
	    ask_begin:
		printf ("\nD� o bloco inicial desejado: ");

		gets (line);

		if (line[0] == 'n')
			return (-1);

		if ((unsigned)(begin = atol (line)) >= fdisk_size)
		{
		    inv_begin:
			printf ("\nBloco inicial inv�lido: \"%s\"\n", line);
			goto ask_begin;
		}

		if (fdisk_align)
		{
			if (begin < gp->h_sect)
				begin = gp->h_sect;
			else
				begin = fdisk_round_up (begin);
		}
		else
		{
			if (begin == 0)
				goto inv_begin;
		}

		if (fdisk_good_regular_area (begin, begin) < 0)
			goto inv_begin;
	}

	/*
	 *	Obt�m um final
	 */
	for (pp = ip->f_pp + 1; /* abaixo */; pp++)
	{
		if (pp >= &parttb[NPART])
		{
			pend = fdisk_size;

			if (fdisk_align && (i = pend % fdisk_round))
			{
				printf ("\nAlinha o final com o in�cio do �ltimo cilindro do disco? (n): ");
	
				if (askyesno () > 0)
					pend -= i;
			}

			break;
		}

		if (pp->pt_size > 0)
			{ pend = fdisk_round_down (pp->pt_offset); break; }
	}

	if ((size = pend - begin) <= 0 || fdisk_align && size < fdisk_round)
	{
		printf ("\nNesta �rea n�o h� espa�o dispon�vel\n");
		goto ask_begin;
	}

	if (fdisk_good_regular_area (begin, pend) >= 0)
	{
		printf ("\nBloco final = %d (", pend - 1);
		fdisk_print_MB (pend - begin, 0);
		printf (" MB)? (s): ");

		if (askyesno () < 0)
			goto ask_end;
	}
	else
	{
	    ask_end:
		printf ("\nD� o tamanho desejado (MB): ");

		gets (line);

		if (line[0] == 'n')
			return (-1);

		if ((unsigned)(i = atol (line)) <= 0)
		{
		    inv_end:
			printf ("\nTamanho inv�lido: \"%s\"\n", line);
			goto ask_end;
		}

		pend = begin + (i << (MBSHIFT - BLSHIFT));

		if (pend > fdisk_size)
			goto inv_end;

		if ((pend = fdisk_round_up (pend)) > fdisk_size)
			pend = fdisk_size;

		if (fdisk_good_regular_area (begin, pend) < 0)
			goto inv_end;
	}

	/*
	 *	Cria a entrada
	 */
	pp = ip->f_pp;

	pp->pt_active	  = 0;			/* Inativa */
	pp->pt_type	  = TROPIX_T1;		/* Tropix T1 */
	pp->pt_offset	  = begin;
	pp->pt_size	  = pend - begin;

	fdisk_put_phys_addr (pp, begin, pend);

	return (0);

}	/* end fdisk_make_partition */

/*
 ****************************************************************
 *	Cria uma parti��o l�gica				*
 ****************************************************************
 */
int
fdisk_make_logical_partition (void)
{
	int		reg_index, log_index, i;
	PARTTB		*reg_pp, *log_pp;
	const PARTTB	*pp;
	const HDINFO	*gp = fdisk_hdinfo;
	daddr_t		begin, pend, size;
	char		line[80];
	daddr_t		logoffset = fdisk_align ? gp->h_sect : 1;
	int		index, found = 0;
	char		last;

	/*
	 *	Verifica se h� mais de uma parti��o estendida
	 */
	for (reg_index = 0, reg_pp = parttb; reg_index < NPART; reg_index++, reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

		if (IS_EXT (reg_pp->pt_type))
			found++;
	}

	if (found == 0)
	{
		printf ("\nEste disco N�O cont�m uma parti��o estendida\n");
		return (-1);
	}

	/*
	 *	Sugere as v�rias parti��es estendidas da tabela
	 */
	for (reg_index = 0, reg_pp = parttb; /* abaixo */; reg_index++, reg_pp++)
	{
		if (reg_index >= NPART)
		{
			printf ("\nN�O h� outras parti��es estendidas\n");
			return (-1);
		}

		if (reg_pp->pt_size == 0)
			continue;

		if (IS_EXT (reg_pp->pt_type))
		{
			if (found == 1)
			{
				printf
				(	"\nParti��o estendida \"%s%d\":\n",
					file_nm, reg_index + 1
				);
				break;
			}

			printf
			(	"\nNa parti��o estendida \"%s%d\"? (s): ",
				file_nm, reg_index + 1
			);

			if (askyesno () >= 0)
				break;
		}
	}

	/*
	 *	Achou uma parti��o estendida: procura a pr�xima l�gica vaga
	 */
	for (log_index = 0, log_pp = &log_parttb[reg_index][0]; /* abaixo */; log_index++, log_pp++)
	{
		if (log_index >= NLOGPART)
		{
			printf
			(	"\nEsta parti��o estendida j� tem "
				"%d parti��es l�gicas\n", NLOGPART
			);
			return (-1);
		}

		if (log_pp->pt_size == 0)
			break;
	}

	/*
	 *	Sugere v�rios come�os
	 *	(sabe-se que h� no m�nimo uma entrada vaga)
	 */
	for (index = -1, pp = &log_parttb[reg_index][-1], last = 0; last == 0; index++, pp++)
	{
		/* Procura uma �rea */

		if (index < 0)			/* Antes da primeira parti��o l�gica */
		{
			if ((pp + 1)->pt_size == 0)
				continue;

			pend = (pp + 1)->pt_offset - fdisk_log_offset[reg_index][index + 1];
			pend = fdisk_round_down (pend);

			goto begin_of_extended;
		}

		begin = fdisk_round_up (pp->pt_offset + pp->pt_size);

		pend   = reg_pp->pt_offset + reg_pp->pt_size;

		if (pend != fdisk_size)
			pend = fdisk_round_down (pend);

		if   (pp->pt_size == 0)		/* Parti��o estendida inteiramente vazia */
		{
			last++;

		    begin_of_extended:
			begin = reg_pp->pt_offset;

			if (fdisk_align)
			{
				if (begin <= gp->h_sect)
					begin = gp->h_sect;
				else
					begin = fdisk_round_up (begin);
			}
		}
		elif ((pp + 1)->pt_size == 0)	/* Ap�s a �ltima parti��o l�gica */
		{
			last++;
		}
		else				/* Entre duas parti��es l�gicas */
		{
			pend = (pp + 1)->pt_offset - fdisk_log_offset[reg_index][index + 1];
			pend = fdisk_round_down (pend);
		}

		/* Examina o tamanho */

		if ((size = pend - begin) >= fdisk_round || !fdisk_align && size > logoffset)
		{
			begin += logoffset;

			printf ("\nBloco inicial = %d? (s): ", begin);

			if (askyesno () >= 0)
				goto get_size;
		}

	}	/* end (sugerindo v�rios come�os) */

	/*
	 *	Se ainda n�o tem um come�o, ...
	 */
    ask_begin:
	printf ("\nD� o bloco inicial desejado: ");

	gets (line);

	if (line[0] == 'n')
		return (-1);

	if ((unsigned)(begin = atol (line)) >= fdisk_size || begin < 2)
	{
	    inv_begin:
		printf ("\nBloco inicial inv�lido: \"%s\"\n", line);
		goto ask_begin;
	}

	if (fdisk_align)
	{
		if (begin < 2 * gp->h_sect)
			begin = 2 * gp->h_sect;
		else
			begin = fdisk_round_up (begin - logoffset) + logoffset;
	}

	if (fdisk_good_logical_area (reg_index, begin - logoffset, begin) < 0)
		goto inv_begin;

	/*
	 *	Obt�m um final
	 */
	pend = reg_pp->pt_offset + reg_pp->pt_size;

	for (index = log_index - 1, pp = &log_parttb[reg_index][index]; index >= 0; index--, pp--)
	{
		if (begin <= pp->pt_offset)
			pend = pp->pt_offset - fdisk_log_offset[reg_index][index];
	}

	if (pend != fdisk_size)
		pend = fdisk_round_down (pend);

	size = pend - begin + logoffset;

	if (size <= logoffset || fdisk_align && size < fdisk_round)
	{
		printf ("\nNesta �rea n�o h� espa�o dispon�vel\n");
		goto ask_begin;
	}

    get_size:
	if (fdisk_good_logical_area (reg_index, begin - logoffset, pend) >= 0)
	{
		printf ("\nBloco final = %d (", pend - 1);
		fdisk_print_MB (pend - begin, 0);
		printf (" MB)? (s): ");

		if (askyesno () < 0)
			goto ask_end;
	}
	else
	{
	    ask_end:
		printf ("\nD� o tamanho desejado (MB): ");

		gets (line);

		if (line[0] == 'n')
			return (-1);

		if ((unsigned)(i = atol (line)) <= 0)
		{
		    inv_end:
			printf ("\nTamanho inv�lido: \"%s\"\n", line);
			goto ask_end;
		}

		pend = begin + (i << (MBSHIFT - BLSHIFT));

		if (pend > fdisk_size)
			goto inv_end;

		if ((pend = fdisk_round_up (pend)) > fdisk_size)
			pend = fdisk_size;

		if (fdisk_good_logical_area (reg_index, begin - logoffset, pend) < 0)
			goto inv_end;
	}

	/*
	 *	Cria a entrada
	 */
	log_pp->pt_active = 0;			/* Inativa */
	log_pp->pt_type	  = TROPIX_T1;		/* Tropix T1 */
	log_pp->pt_offset = begin;
	log_pp->pt_size	  = pend - begin;

	fdisk_put_phys_addr (log_pp, begin, pend);

	fdisk_log_offset[reg_index][log_index] = logoffset;

	fdisk_sort_logical_partitions (reg_index);

	return (0);

}	/* end fdisk_make_logical_partition */

/*
 ****************************************************************
 *	Modifica o tamanho de uma parti��o			*
 ****************************************************************
 */
int
fdisk_change_partition_size (void)
{
	PARTINFO	info;

	/*
	 *	Em primeiro lugar, obt�m uma parti��o
	 */
	if (fdisk_get_old_parttb_no (&info) == NOPARTTB)
		return (-1);

	/*
	 *	Analisa o tipo da parti��o
	 */
	if (info.f_log_index < 0)
		return (fdisk_change_regular_partition_size (&info));
	else
		return (fdisk_change_logical_partition_size (&info));

}	/* end fdisk_change_partition_size */

/*
 ****************************************************************
 *	Modifica o tamanho de uma parti��o regular/estendida	*
 ****************************************************************
 */
int
fdisk_change_regular_partition_size (const PARTINFO *ip)
{
	PARTTB		*pp, *reg_pp, *log_pp;
	int		log_index, size, inc;
	daddr_t		begin, pend, min_end, max_end;
	char		line[80], *line_ptr;

	/*
	 *	Pr�logo
	 */
	reg_pp = ip->f_pp; begin = reg_pp->pt_offset;
	min_end = fdisk_round_up (begin + 1);

	/*
	 *	Se for estendido, examina as parti��es l�gicas
	 */
	if (IS_EXT (reg_pp->pt_type)) for
	(
		log_index = 0, log_pp = &log_parttb[ip->f_reg_index][0];
		log_index < NLOGPART;
		log_index++, log_pp++
	)
	{
		if (log_pp->pt_size == 0)
			break;

		if (log_pp->pt_offset + log_pp->pt_size > min_end)
			min_end = fdisk_round_up (log_pp->pt_offset + log_pp->pt_size);
	}

	/*
	 *	Obt�m o maior final poss�vel
	 */
	for (pp = reg_pp + 1; /* abaixo */; pp++)
	{
		if (pp >= &parttb[NPART])
			{ max_end = fdisk_size; break; }

		if (pp->pt_size > 0)
			{ max_end = fdisk_round_down (pp->pt_offset); break; }
	}

	pend = max_end;	/* Em princ�pio */

	/*
	 *	Imprime os valores limites
	 */
	printf ("\nOs tamanhos v�lidos variam entre ");
	fdisk_print_MB (min_end - begin, 0);
	printf (" MB e ");
	fdisk_print_MB (max_end - begin, 0);
	printf (" MB\n");

	/*
	 *	Sugere um final
	 */
	printf ("\nBloco final = %d (", pend - 1);
	fdisk_print_MB (pend - begin, 0);
	printf (" MB)? (s): ");

	if (askyesno () < 0)
	{
	    ask_end:
		printf ("\nD� o tamanho desejado (MB): ");

		gets (line_ptr = line);

		if (line[0] == 'n')
			return (-1);

		if   (line[0] == '+')
			{ line_ptr++;  inc = 1; }
		elif (line[0] == '-')
			{ line_ptr++;  inc = -1; }
		else
			inc = 0;

		if ((unsigned)(size = atol (line_ptr)) <= 0)
		{
		    inv_end:
			printf ("\nTamanho inv�lido: \"%s\"\n", line);
			goto ask_end;
		}

		size <<= (MBSHIFT - BLSHIFT);

		if   (inc > 0)
			size = reg_pp->pt_size + size;
		elif (inc < 0)
			size = reg_pp->pt_size - size;

		pend = begin + size;

		if (pend < max_end)
		{
			if (fdisk_round_up (pend) < max_end)
				pend = fdisk_round_up (pend);
			else
				pend = max_end;
		}

		if (pend < min_end || pend > max_end)
			goto inv_end;
	}

	/*
	 *	Altera a entrada
	 */
   /***	reg_pp->pt_active = ...; ***/
   /***	reg_pp->pt_type	  = ...; ***/
   /***	reg_pp->pt_offset = ...; ***/
	reg_pp->pt_size	  = pend - begin;

	fdisk_put_phys_addr (reg_pp, begin, pend);

	return (0);

}	/* end fdisk_change_regular_partition_size */

/*
 ****************************************************************
 *	Modifica o tamanho de uma parti��o l�gica		*
 ****************************************************************
 */
int
fdisk_change_logical_partition_size (const PARTINFO *ip)
{
	PARTTB		*pp, *log_pp;
	int		size, inc;
	daddr_t		begin, pend, min_end, max_end;
	char		line[80], *line_ptr;

	/*
	 *	Pr�logo
	 */
	log_pp = ip->f_pp; begin = log_pp->pt_offset;
	min_end = fdisk_round_up (begin + 1);

	/*
	 *	Obt�m o maior final poss�vel
	 */
	pp = log_pp + 1;

	if (ip->f_log_index < NLOGPART - 1 && pp->pt_size != 0)
	{
		max_end = fdisk_round_down
			(pp->pt_offset - fdisk_log_offset[ip->f_reg_index][ip->f_log_index + 1]);
	}
	else for (pp = &parttb[ip->f_reg_index + 1]; /* abaixo */; pp++)
	{
		if (pp >= &parttb[NPART])
			{ max_end = fdisk_size; break; }

		if (pp->pt_size > 0)
			{ max_end = fdisk_round_down (pp->pt_offset); break; }
	}

	pend = max_end;	/* Em princ�pio */

	/*
	 *	Sugere um final
	 */
	printf ("\nBloco final = %d (", pend - 1);
	fdisk_print_MB (pend - begin, 0);
	printf (" MB)? (s): ");

	if (askyesno () < 0)
	{
	    ask_end:
		printf ("\nD� o tamanho desejado (MB): ");

		gets (line_ptr = line);

		if (line[0] == 'n')
			return (-1);

		if   (line[0] == '+')
			{ line_ptr++;  inc = 1; }
		elif (line[0] == '-')
			{ line_ptr++;  inc = -1; }
		else
			inc = 0;

		if ((unsigned)(size = atol (line_ptr)) <= 0)
		{
		    inv_end:
			printf ("\nTamanho inv�lido: \"%s\"\n", line);
			goto ask_end;
		}

		size <<= (MBSHIFT - BLSHIFT);

		if   (inc > 0)
			size = log_pp->pt_size + size;
		elif (inc < 0)
			size = log_pp->pt_size - size;

		pend = begin + size;

		if (pend < max_end)
		{
			if (fdisk_round_up (pend) < max_end)
				pend = fdisk_round_up (pend);
			else
				pend = max_end;
		}

		if (pend < min_end || pend > max_end)
			goto inv_end;
	}

	/*
	 *	Altera a entrada
	 */
   /***	log_pp->pt_active = ...; ***/
   /***	log_pp->pt_type	  = ...; ***/
   /***	log_pp->pt_offset = ...; ***/
	log_pp->pt_size	  = pend - begin;

	fdisk_put_phys_addr (log_pp, begin, pend);

   /***	fdisk_log_offset[reg_index][log_index] = logoffset; ***/

   /***	fdisk_sort_logical_partitions (reg_index); ***/

	return (0);

}	/* end fdisk_change_logical_partition_size */

/*
 ****************************************************************
 *	Verifica se uma �rea de blocos j� est� alocada		*
 ****************************************************************
 */
int
fdisk_good_regular_area (daddr_t begin, daddr_t pend)
{
	const PARTTB	*reg_pp;

	/*
	 *	Retorna:
	 *		 0  se N�O est� em uso
	 *		-1  se est� em uso (ou valores inv�lidos)
	 */

	/*
	 *	Pode acontecer, com parti��es fora de ordem
	 */
	if (begin > pend)
		return (-1);

	/*
	 *	Verifica os valores m�ximos
	 */
	if ((unsigned)begin >= fdisk_size)
		return (-1);

	if ((unsigned)pend > fdisk_size)
		return (-1);

	/*
	 *	Verifica se esta �rea pertence a alguma outra parti��o
	 */
	for (reg_pp = &parttb[0]; reg_pp < &parttb[NPART]; reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

		if (pend <= reg_pp->pt_offset)
			continue;

		if (begin >= reg_pp->pt_offset + reg_pp->pt_size)
			continue;

		return (-1);
	}

	return (0);

}	/* end fdisk_good_regular_area */

/*
 ****************************************************************
 *  A �rea de blocos j� est� alocada em uma parti��o estendida?	*
 ****************************************************************
 */
int
fdisk_good_logical_area (int reg_index, daddr_t begin, daddr_t pend)
{
	PARTTB		*reg_pp = &parttb[reg_index], *log_pp;
	int		log_index;

	/*
	 *	Retorna:
	 *		 0  se N�O est� em uso
	 *		-1  se est� em uso (ou valores inv�lidos)
	 */

	/*
	 *	Pode acontecer, com parti��es fora de ordem
	 */
	if (begin > pend)
		return (-1);

	/*
	 *	Verifica os valores m�ximos
	 */
	if ((unsigned)begin >= fdisk_size)
		return (-1);

	if ((unsigned)pend > fdisk_size)
		return (-1);

	/*
	 *	Tem de estar dentro da parti��o estendida
	 */
	if (begin < reg_pp->pt_offset)
		return (-1);

	if (pend > reg_pp->pt_offset + reg_pp->pt_size)
		return (-1);

	/*
	 *	Verifica se esta �rea pertence a alguma outra parti��o l�gica
	 */
	for (log_index = 0, log_pp = &log_parttb[reg_index][0]; log_index < NLOGPART; log_index++, log_pp++)
	{
		if (log_pp->pt_size == 0)
			break;

		if (begin >= log_pp->pt_offset + log_pp->pt_size)
			continue;

		if (pend <= log_pp->pt_offset - fdisk_log_offset[reg_index][log_index])
			continue;

		return (-1);
	}

	return (0);

}	/* end fdisk_good_logical_area */

/*
 ****************************************************************
 *	Procura uma parti��o j� existente			*
 ****************************************************************
 */
PARTTB *
fdisk_get_old_parttb_no (PARTINFO *ip)
{
	int		reg_index, log_index;
	int		given_index, seq_index;
	PARTTB		*reg_pp, *log_pp;
	char		line[80];

	/*
	 *	Pede uma parti��o
	 */
    again:
	printf ("\n�ndice da parti��o: "); gets (line);

	if (line[0] == 'n')
		return (NOPARTTB);

	if ((given_index = atol (line) - 1) < 0)
	{
		printf ("\nValor inv�lido: \"%d\"\n", given_index + 1);
		goto again;
	}

	/*
	 *	Malha pela tabela
	 */
	for (reg_index = 0, reg_pp = parttb, seq_index = 0; reg_index < NPART; reg_index++, reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

		if (seq_index++ == given_index)
		{
			ip->f_reg_index = reg_index;
			ip->f_log_index = -1;
			ip->f_pp	= reg_pp;

			return (reg_pp);
		}

		/*
		 *	Verifica se � uma parti��o estendida
		 */
		if (!IS_EXT (reg_pp->pt_type))
			continue;

		for
		(	log_index = 0, log_pp = &log_parttb[reg_index][0];
			log_index < NLOGPART;
			log_index++, log_pp++
		)
		{
			if (log_pp->pt_size == 0)
				break;

			if (seq_index++ == given_index)
			{
				ip->f_reg_index = reg_index;
				ip->f_log_index = log_index;
				ip->f_pp	= log_pp;

				return (log_pp);
			}

		}	/* end malha pelas parti��es l�gicas */

	}	/* end malha pelas parti��es regulares */

	printf ("\nA parti��o \"%d\" N�O existe\n", given_index + 1);
	goto again;

}	/* end fdisk_get_old_parttb_no */

/*
 ****************************************************************
 *	Obt�m o n�mero de uma parti��o (regular) nova		*
 ****************************************************************
 */
PARTTB *
fdisk_get_new_parttb_no (PARTINFO *ip)
{
	int		reg_index;
	PARTTB		*reg_pp;
	char		line[80];

	/*
	 *	Sugere uma parti��o
	 */
	for (reg_index = 0, reg_pp = &parttb[0]; /* abaixo */; reg_index++, reg_pp++)
	{
		if (reg_index >= NPART)
		{
			printf
			(	"\nN�o h� mais lugar para parti��es "
				"regulares/estendidas\n"
			);
			return (NOPARTTB);
		}

		if (reg_pp->pt_size == 0)
			break;
	}

	printf ("\nN�mero da parti��o = %d? (s): ", reg_index + 1);

	if (askyesno () >= 0)
	{
	    found:
		ip->f_reg_index = reg_index;
		ip->f_log_index = -1;
		ip->f_pp	= reg_pp;

		return (reg_pp);
	}

	/*
	 *	Pede uma parti��o
	 */
    again:
	printf ("\nN�mero da parti��o desejada: ");

	gets (line);

	if (line[0] == 'n')
		return (NOPARTTB);

	if ((unsigned)(reg_index = atol (line) - 1) >= NPART)
	{
		printf
		(	"\nValor fora dos limites: \"%d\" "
			"(deve ser de 1 a " XSTR (NPART) ")\n",
			reg_index + 1
		);
	}
	else	/* reg_index < NPART */		/* N�O deve existir */
	{
		reg_pp = &parttb[reg_index];

		if (reg_pp->pt_size == 0)
			goto found;

		printf ("\nA parti��o \"%d\" j� est� ocupada\n", reg_index + 1);
	}

	goto again;

}	/* end fdisk_get_new_parttb_no */

/*
 ****************************************************************
 *	Ordena as parti��es l�gicas				*
 ****************************************************************
 */
void
fdisk_sort_logical_partitions (int reg_index)
{
	int		tmp_index, log_index, min_index;
	PARTTB		*tmp_pp, *log_pp, *min_pp;
	daddr_t		min_offset;
	PARTTB		tmp_log_parttb[NLOGPART];
	daddr_t		tmp_log_offset[NLOGPART];

	memmove (tmp_log_parttb, log_parttb[reg_index], sizeof (tmp_log_parttb));
	memsetl (log_parttb[reg_index], 0, sizeof (tmp_log_parttb) / sizeof (long));

	memmove (tmp_log_offset, fdisk_log_offset[reg_index], sizeof (tmp_log_offset));
	memsetl (fdisk_log_offset[reg_index], 0, sizeof (tmp_log_offset) / sizeof (long));

	for (log_index = 0, log_pp = log_parttb[reg_index]; log_index < NLOGPART; log_index++, log_pp++)
	{
		min_offset = 0x7FFFFFFF;	/* Valor m�ximo */
		min_pp	   = NOPARTTB;
		min_index  = 0;

		for (tmp_index = 0, tmp_pp = tmp_log_parttb; tmp_index < NLOGPART; tmp_index++, tmp_pp++)
		{
			if (tmp_pp->pt_size == 0)
				continue;

			if (tmp_pp->pt_offset < min_offset)
			{
				min_index  = tmp_index;
				min_offset = tmp_pp->pt_offset;
				min_pp	   = tmp_pp;
			}

		}	/* end malha procurando o m�nimo */

		if (min_pp == NOPARTTB)
			break;

		memmove (log_pp, min_pp, sizeof (PARTTB));
		fdisk_log_offset[reg_index][log_index] = tmp_log_offset[min_index];

		min_pp->pt_size = 0;	/* Retira da fonte */

	}	/* end malha pelo destino */ 

}	/* end fdisk_sort_logical_partitions */

/*
 ****************************************************************
 *	Escreve todas as cadeias das parti��es l�gicas		*
 ****************************************************************
 */
void
fdisk_write_all_logical_chains (int fd)
{
	int		reg_index;
	PARTTB		*reg_pp;

	for (reg_index = 0, reg_pp = parttb; reg_index < NPART; reg_index++, reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

		fdisk_put_phys_addr
		(	reg_pp,
			reg_pp->pt_offset,
			reg_pp->pt_offset + reg_pp->pt_size
		);

		if (!IS_EXT (reg_pp->pt_type))
			continue;

		fdisk_write_logical_chain (reg_index, fd);
	}

}	/* end fdisk_write_all_logical_chains */

/*
 ****************************************************************
 *	Escreve uma cadeia das parti��es l�gicas		*
 ****************************************************************
 */
void
fdisk_write_logical_chain (int reg_index, int fd)
{
	const PARTTB	*reg_pp, *log_pp;
	PARTTB		*pp;
	int		log_index;
	daddr_t		begin, pend;
	daddr_t		log_addr;
	daddr_t		log_offset0, offset0, size0;
	daddr_t		log_offset1, offset1, size1;
	int		code;
	char		area[BLSZ];

	/*
	 *	Prepara o c�digo
	 */
	code = DOS_EXT_G;

	/*
	 *	Se n�o tem nenhuma parti��o l�gica, ...
	 */
	reg_pp = &parttb[reg_index];
	log_pp = &log_parttb[reg_index][0];

	if (log_pp->pt_size == 0)
	{
		memset (area, 0, sizeof (area));
		*(ushort *)(area + MAGIC_OFF) = 0xAA55;

#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", reg_pp->pt_offset);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", reg_pp->pt_offset);
#endif	DEBUG
		llseek (fd, (loff_t)reg_pp->pt_offset << BLSHIFT, NULL, L_SET);

		if (write (fd, area, BLSZ) != BLSZ)
			error ("$*Erro de escrita");
#endif	NO_WRITE
		return;
	}

	/*
	 *	Pequena consist�ncia
	 */
	if (reg_pp->pt_offset + fdisk_log_offset[reg_index][0] != log_pp->pt_offset)
	{
		printf
		(	"\n*** Inconsist�ncia: ext = %d, off = %d, log = %d\n",
			reg_pp->pt_offset, log_pp->pt_offset,
			fdisk_log_offset[reg_index][0] 
		);
	}

	/*
	 *	Escreve a cadeia
	 */
	for (log_index = 0; log_index < NLOGPART; log_index++, log_pp++)
	{
		if (log_pp->pt_size == 0)
			break;

		memset (area, 0, sizeof (area));
		*(ushort *)(area + MAGIC_OFF) = 0xAA55;

		pp = (PARTTB *)(area + PARTB_OFF);

		/*
		 *	Prepara alguns valores �teis
		 */
		log_offset0 = fdisk_log_offset[reg_index][log_index];
		offset0     = log_pp[0].pt_offset;
		size0       = log_pp[0].pt_size;

		log_offset1 = fdisk_log_offset[reg_index][log_index+1];
		offset1     = log_pp[1].pt_offset;
		size1       = log_pp[1].pt_size;

		log_addr    = offset0 - log_offset0;

		/*
		 *	Completa a primeira entrada
		 */
		memmove (pp, log_pp, sizeof (PARTTB));

	   /***	pp->pt_active = ... ***/
	   /***	pp->pt_type   = ... ***/
		pp->pt_offset = log_offset0;
	   /***	pp->pt_size   =  ... ***/

		begin = offset0;
		pend   = offset0 + size0;

		fdisk_put_phys_addr (pp, begin, pend);

		/*
		 *	Completa a segunda entrada
		 */
		if (log_index >= NLOGPART-1 || size1 == 0)
			goto write;

		pp++;

	   /***	pp->pt_active = 0 ***/
		pp->pt_type   = code;
		pp->pt_offset = offset1 - log_offset1 - reg_pp->pt_offset;
		pp->pt_size   = size1 + log_offset1;

		begin = offset1 - log_offset1;
		pend   = offset1 + size1;

		fdisk_put_phys_addr (pp, begin, pend);

	    write:
#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", log_addr);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", log_addr);
#endif	DEBUG
		llseek (fd, (loff_t)log_addr << BLSHIFT, NULL, L_SET);

		if (write (fd, area, BLSZ) != BLSZ)
			error ("$*Erro de escrita");
#endif	NO_WRITE
	}

}	/* end fdisk_write_logical_chain */

/*
 ****************************************************************
 *	Completa a entrada com os endere�os f�sicos		*
 ****************************************************************
 */
void
fdisk_put_phys_addr (PARTTB *pp, daddr_t begin, daddr_t pend)
{
	const HDINFO	*gp = fdisk_hdinfo;
	int		sector,	head, cylin;
	daddr_t		msg_begin, msg_end;

	/*
	 *	Completa o come�o
	 */
	msg_begin = begin;

	sector	= begin % gp->h_sect + 1;
	begin	= begin / gp->h_sect;
	head	= begin % gp->h_head;
	cylin	= begin / gp->h_head;

	cylin	= CYLMAX (cylin);

	pp->pt_start.head = head;
	pp->pt_start.sect = (sector & 0x3F) | ((cylin >> 2) & 0xC0);
	pp->pt_start.cyl  = cylin;

	/*
	 *	Completa o final
	 */
	msg_end = --pend;

	sector	= pend % gp->h_sect + 1;
	pend	= pend / gp->h_sect;
	head	= pend % gp->h_head;
	cylin	= pend / gp->h_head;

	if (pp->pt_active && (cylin > 1023) && (gp->h_flags & HD_INT13_EXT) == 0)
	{
		printf
		(	"\e[34m"
			"\nCUIDADO: Parti��o ativa come�ando no setor %d termina no cilindro %d (> 1023)\n"
			"\e[0m",
			msg_begin, cylin
		);
	}

	cylin	= CYLMAX (cylin);

	pp->pt_end.head = head;
	pp->pt_end.sect = (sector & 0x3F) | ((cylin >> 2) & 0xC0);
	pp->pt_end.cyl  = cylin;

}	/* end fdisk_put_phys_addr */

/*
 ****************************************************************
 *	Arredonda um n�mero de bloco (para baixo)		*
 ****************************************************************
 */
daddr_t
fdisk_round_down (daddr_t daddr)
{
	if (!fdisk_align)
		return (daddr);

	return (daddr - daddr % fdisk_round);

}	/* end fdisk_round_daddr */

/*
 ****************************************************************
 *	Arredonda um n�mero de bloco (para cima)		*
 ****************************************************************
 */
daddr_t
fdisk_round_up (daddr_t daddr)
{
	if (!fdisk_align)
		return (daddr);

	daddr += (fdisk_round - 1);

	return (daddr - daddr % fdisk_round);

}	/* end fdisk_round_daddr */

/*
 ****************************************************************
 *	Imprime blocos em MB					*
 ****************************************************************
 */
void
fdisk_print_MB (daddr_t size, int width)
{
	size += (MBSZ/BLSZ/(2 * 100));	/* Arredonda 0.005 MB */

	printf
	(	width ? "%6d" : "%d",
		(unsigned)size >> (MBSHIFT-BLSHIFT)
	);

	printf
	(	".%02d",
		(100 * ((unsigned)size & (MBSZ/BLSZ - 1))) >> (MBSHIFT-BLSHIFT)
	);

}	/* end fdisk_print_MB */

/*
 ****************************************************************
 *	Imprime o nome de uma parti��o				*
 ****************************************************************
 */
void
fdisk_print_part_name (PARTINFO *ip)
{
	if (ip->f_log_index < 0)
	{
		printf
		(	"%s%d", file_nm,
			ip->f_reg_index + 1
		);
	}
	else
	{
		printf
		(	"%s%d%c", file_nm,
			ip->f_reg_index + 1, ip->f_log_index + 'a'
		);
	}

}	/* end fdisk_print_part_name */

/*
 ****************************************************************
 *	Imprime todos os tipos conhecidos			*
 ****************************************************************
 */
void
fdisk_print_sys_types (void)
{
	const PARTNM	*pnm;
	int		i;

	printf ("\nTipos de sistemas de arquivos:\n");

	for (pnm = partnm + 1, i = 0; pnm->pt_type >= 0; pnm++, i++)
	{
		if ((i % 3) == 0)
			printf ("\n");
		else
			printf ("    ");

		printf ("%02X %20s", pnm->pt_type, pnm->pt_nm);
	}

	printf ("\n");

}	/* end fdisk_print_sys_types */

/*
 ****************************************************************
 *	Resumo de utiliza��o de "fdisk"				*
 ****************************************************************
 */
void
fdisk_help (void)
{
	printf
	(	"\nEditor de tabelas de parti��es\n"
		"\ncomandos:\n"
		"\t-: Imprime a tabela de parti��es\n"
		"\tp: Idem, com �reas vagas\n"
		"\tn: Cria uma parti��o nova\n"
		"\td: Remove uma parti��o\n"
		"\tm: Altera o tamanho de uma parti��o\n"
		"\ta: Troca o estado (ativo/n�o ativo) da parti��o\n"
		"\tl: Imprime os tipos das parti��es\n"
		"\tt: Troca o tipo da parti��o\n"
		"\ts: Imprime as �reas vagas do disco\n"
		"\tu: Liga/desliga o alinhamento (come�a ligado)\n"
		"\tg: Tenta obter a geometria a partir das parti��es\n"
		"\te: Usa a tabela de parti��es de emerg�ncia\n"
		"\tw: Reescreve (atualiza) a tabela de parti��es no disco\n"
		"\tq: Termina a execu��o do editor de parti��es\n"

		"\nObs.:\tPara qualquer dado pedido, \"n\" cancela o comando\n"
	);

}	/* end fdisk_help */

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
		"%s - imprime e/ou modifica a tabela de parti��es de um disco\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-gv] <dev>\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-g: Tenta obter a geometria da tabela de parti��es\n"
		"\t-v: Verboso\n"
	);

	exit (2);

}	/* end help */
