/*
 ****************************************************************
 *								*
 *			fdisk.c					*
 *								*
 *	Altera a tabela de parti��o de discos	 		*
 *								*
 *	Vers�o	3.0.0, de 22.12.94				*
 *		4.0.0, de 26.07.00				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <common.h>

#include <bcb.h>
#include <disktb.h>
#include <scsi.h>
#include <pci.h>
#include <ata.h>

#include "../h/common.h"
#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****** Vari�veis globais ***************************************
 */
#define	DEBUG
#undef	NO_WRITE

enum		      {	IDE_TYPE, SCSI_TYPE };	/* Tipo do disco */

entry daddr_t		fdisk_parttb_emer_sect;

entry char		fdisk_type;	/* Tipo: IDE ou SCSI */
entry const void	*fdisk_data;	/* Estrutura ATA ou SCSI */
entry const DISKTB	*fdisk_disktb;	/* Entrada do disco "hda" ou "hdb" */
entry const HDINFO	*fdisk_hdinfo;	/* Entrada de par�metros do disco */
entry daddr_t		fdisk_size;	/* Tamanho do disco */
entry daddr_t		fdisk_round;	/* Para arrendondar os endere�os */
entry const char	*fdisk_nm;	/* Nome do disco */

entry int		fdisk_modified;	/* N�O zero se modificada */
entry int		fdisk_debug;	/* Debug ? */
entry int		fdisk_align;	/* Aligned ? */

extern int		sd_target_index; /* Pr�ximo dispositivo SCSI */

/*
 ****** Defini��es e vari�veis da tabela de parti��es ***********
 */
entry char		parttb_orig_block[BLSZ],	/* Os blocos das tabelas de parti��es */
			parttb_emer_block[BLSZ];

entry PARTTB		parttb[NPART];		/* A tabela de parti��es regular */
entry PARTTB		log_parttb[NPART][NLOGPART]; /* Idem, l�gicas */

entry daddr_t		fdisk_log_offset[NPART][NLOGPART]; /* Deslo. das par. l�gicas */

typedef struct
{
	int	f_reg_index;	/* No. da parti��o regular */
	int	f_log_index;	/* No. da parti��o l�gica */
	PARTTB	*f_pp;		/* Ponteiro para a entrada */

}	PARTINFO;

/*
 ******	Tabela "fict�cia" para os discos IDE ou  SCSI ***********
 */
entry HDINFO	generic_hdinfo;	/* Gen�rico */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		fdisk_read_parttb (const DISKTB *);
void		fdisk_print_parttb (int);
void		fdisk_print_parttb_entry (const PARTTB *, int);
void		fdisk_debug_print_parttb_entry (int, const PARTTB *);
void		fdisk_get_cmd (char *);
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
void		fdisk_write_all_logical_chains (void);
void		fdisk_write_logical_chain (int);
daddr_t		fdisk_round_down (daddr_t);
daddr_t		fdisk_round_up (daddr_t);
void		fdisk_print_part_name (PARTINFO *);
void		fdisk_print_sys_types (void);
void		fdisk_help (void);

/*
 ****************************************************************
 *	Imprime e/ou modifica a tabela de parti��es dos discos	*
 ****************************************************************
 */
void
fdisk (void)
{
	const ATA_DEVICE	*adp;
	const SCSI		*sp;
	ATA_DEVICE		**hpp;
	SCSI			**spp;
	char			cmd[] = "c hda";

	/*
	 *	Pequena introdu��o
	 */
	printf ("\nEntrando no editor de tabelas de parti��es \"fdisk\"\n");
	printf ("\nTecle \"?\" para uma lista de comandos\n");

	fdisk_modified = 0; fdisk_align = 1;

	/*
	 *	Procura discos ATA
	 */
	for (hpp = ata_ptr; /* abaixo */; hpp++)
	{
		if ((adp = *hpp) == NOATADEVICE)
			break;

		if (bopen (adp->ad_disktb) < 0)
			continue;

		switch (adp->ad_type)
		{
		    default:
			continue;

		    case ATA_HD:
			break;

		    case ATAPI_ZIP:		/* N�o tem tabela de parti��es */
			if (adp->ad_scsi->scsi_disksz == ZIP_FLOPPY_CAPACITY)
				continue;
			break;

		}	/* end type */

		cmd[4] = adp->ad_dev_nm[2];

		goto found;
	}

	/*
	 *	Procura discos SCSI
	 */
	for (spp = scsi_ptr; /* abaixo */; spp++)
	{
		if ((sp = *spp) == NOSCSI)
		{
			printf ("\nO sistema n�o tem discos IDE nem SCSI\n");
			goto exit;
		}

		if (!sp->scsi_is_present || !sp->scsi_is_disk)
			continue;

		if (sp->scsi_read_only)
			continue;
				
		if (bopen (sp->scsi_disktb) < 0)
			continue;

		cmd[2] = 's';
		cmd[4] = sp->scsi_dev_nm[2];
		break;
	}

	/*
	 *	Come�a com o dispositivo encontrado
	 */
    found:
	fdisk_get_cmd (cmd);
    exit:
	printf ("\nSaindo do editor de tabelas de parti��es\n");

}	/* end fdisk */

/*
 ****************************************************************
 *	Le um comando para alterar a tabela			*
 ****************************************************************
 */
void
fdisk_get_cmd (char *cmd)
{
	char		*cp;
	int		i;
	HDINFO		*gp = &generic_hdinfo;
	PARTTB		*pp;
	PARTINFO	info;
	char		type, bad;
	char		line[80];

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
		 ******	Troca o dispositivo *********************
		 */
	    case 'c':
		if (fdisk_modified)
		{
			printf ("\nA tabela de parti��es foi modificada!\n");

			printf ("\nTroca de dispositivo (sem atualiz�-la)? (n): ");

			if (askyesno (0) <= 0)
				break;
		}

		/*
		 *	Verifica se deu na forma "c sdb"
		 */
		for (cp++; (*cp == ' ' || *cp == '\t'); cp++)
			/* vazio */;

		if (cp[0] != '\0')
			goto examine_dev_nm;

		for (EVER)
		{
			const DISKTB		*dp;

			printf ("\nNome do novo dispositivo: "); gets (line);

			if (line[0] == 'n')
				goto prompt;

			for (cp = line; (*cp == ' ' || *cp == '\t'); cp++)
				/* vazio */;

			if (cp[0] == '\0')
				continue;

		    examine_dev_nm:
			if (cp[1] != 'd' || cp[3] != '\0')
			{
			   invalid_dev:
				printf
				(	"\nNome de dispositivo inv�lido: \"%s\"\n",
					line
				);
				continue;
			}

			if   (cp[0] == 'h')	/* IDE */
			{
				const ATA_DEVICE	*adp;
				ATA_DEVICE		**hpp;

				for (hpp = ata_ptr; /* abaixo */; hpp++)
				{
					if ((adp = *hpp) == NOATADEVICE)
						goto invalid_dev;

					if (cp[2] == adp->ad_dev_nm[2])
						break;
				}

				dp = adp->ad_disktb;

				if (bopen (dp) < 0)
					continue;

				switch (adp->ad_type)
				{
				    default:
					printf ("\nO dispositivo \"%s\" N�O � um disco\n", line);
					continue;

				    case ATA_HD:
					break;

				    case ATAPI_ZIP:		/* N�o tem tabela de parti��es */
					if (adp->ad_scsi->scsi_disksz != ZIP_FLOPPY_CAPACITY)
						break;

					printf
					(	"\nO dispositivo \"%s\" N�O cont�m uma tabela de parti��es\n",
						line
					);
					continue;

				}	/* end switch */

				if (bread (dp, fdisk_parttb_orig_sect, parttb_orig_block, BLSZ) < 0)
					continue;

				if (*(ushort *)(parttb_orig_block + MAGIC_OFF) != 0xAA55)
					printf ("\n*** O bloco 0 N�O cont�m \"0x55AA\"\n");

				memmove (parttb, parttb_orig_block + PARTB_OFF, sizeof (parttb));

				/* Procura a geometria */

			   /***	gp = &generic_hdinfo; ***/

				if (adp->ad_bios_head)
				{
					gp->h_head  = adp->ad_bios_head;
					gp->h_sect  = adp->ad_bios_sect;
					gp->h_cyl   = adp->ad_bios_cyl;
					gp->h_flags = adp->ad_flags;
				}
				else
				{
					geo_get_parttb_geo (parttb, gp, adp->ad_disksz, adp->ad_dev_nm);
				}

				fdisk_type   = IDE_TYPE;
				fdisk_data   = adp;
				fdisk_size   = adp->ad_disksz;
				fdisk_disktb = dp;
				fdisk_hdinfo = gp;
				fdisk_nm     = adp->ad_dev_nm;

				break;
			}
			elif (cp[0] == 's')	/* SCSI */
			{
				const SCSI	*sp;
				SCSI		**spp;

				for (spp = scsi_ptr; /* abaixo */; spp++)
				{
					if ((sp = *spp) == NOSCSI)
						goto invalid_dev;

					if (cp[2] == sp->scsi_dev_nm[2])
						break;
				}

				dp = sp->scsi_disktb;

				if (!sp->scsi_is_present)
				{
					printf
					(	"\nUnidade N�O presente: \"%s\"\n",
						line
					);
					continue;
				}

				if (!sp->scsi_is_disk || sp->scsi_read_only)
				{
					printf
					(	"\nUnidade N�O comporta uma tabela de parti��es: \"%s\"\n",
						line
					);
					continue;
				}

				if (bopen (dp) < 0)
					continue;

				if (bread (dp, fdisk_parttb_orig_sect, parttb_orig_block, BLSZ) < 0)
					continue;

				if (*(ushort *)(parttb_orig_block + MAGIC_OFF) != 0xAA55)
					printf ("\n*** O bloco 0 N�O cont�m \"0x55AA\"\n");

				memmove (parttb, parttb_orig_block + PARTB_OFF, sizeof (parttb));

				/*
				 *	Atribui o esquema de endere�amento
				 */
			   /***	gp = &generic_hdinfo; ***/

				if (sp->scsi_bios_head)
				{
					gp->h_head = sp->scsi_bios_head;
					gp->h_sect = sp->scsi_bios_sect;
					gp->h_cyl  = sp->scsi_bios_cyl;

					if (sp->scsi_int13_ext)
						gp->h_flags |= HD_INT13_EXT;
					else
						gp->h_flags &= ~HD_INT13_EXT;
				}
				else
				{
					geo_get_parttb_geo (parttb, gp, sp->scsi_disksz, sp->scsi_dev_nm);
				}

				fdisk_type   = SCSI_TYPE;
				fdisk_data   = sp;
				fdisk_size   = sp->scsi_disksz;
				fdisk_disktb = dp;
				fdisk_hdinfo = gp;
				fdisk_nm     = sp->scsi_dev_nm;

				break;
			}
			else
			{
				goto invalid_dev;
			}

		}	/* end for (EVER) */

		/*
		 *	L� e confere a tabela de emerg�ncia
		 */
		fdisk_round = gp->h_head * gp->h_sect;

		fdisk_parttb_emer_sect = gp->h_sect - 1;

		if (bread (fdisk_disktb, fdisk_parttb_emer_sect, parttb_emer_block, BLSZ) < 0)
			printf ("\nN�O consegui ler a tabela de parti��es de emerg�ncia\n");

		if (!memeq (parttb, parttb_emer_block + PARTB_OFF, sizeof (parttb)))
		{
			printf
			(	"\e[34m"
				"\n***** A Tabela de parti��es de emerg�ncia est� diferente da regular\n"
				"\e[0m"
			);

			fdisk_modified++;
		}

		if (fdisk_read_parttb (fdisk_disktb) < 0)
			return;

		fdisk_print_parttb (0 /* sem espa�os vagos */);
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

		if (askyesno (0) > 0)
			fdisk_print_sys_types ();

		printf ("\nD� o tipo desejado (hexadecimal): ");

		gets (line);

		if (line[0] == 'n')
			break;

		if ((i = xtol (line)) & ~0xFF)
			{ printf ("\nTipo inv�lido: \"%s\"\n", line); break; }

		if (IS_EXT (pp->pt_type) ^ IS_EXT (i))
		{
			printf ("\nTroca  de tipos inv�lida\n");
			break;
		}

		pp->pt_type = i;

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
			i = fdisk_make_regular_partition ();
			break;

		    case 'e':
			i = fdisk_make_extended_partition ();
			break;

		    case 'l':
			i = fdisk_make_logical_partition ();
			break;

		    default:
			goto case_n;

		}	/* end switch (line[0]) */

		if (i < 0)
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

		if (askyesno (0) <= 0)
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
	    {
		HDINFO		hi;

		if (geo_get_parttb_geo (parttb, &hi, 0, fdisk_nm) < 0)
			{ printf ("\nN�o consegui obter a geometria\n"); break; }

		printf
		(	"\nGeometria = (%d, %d), %sconfere\n",
			hi.h_head, hi.h_sect,
			gp->h_head == hi.h_head && gp->h_sect == hi.h_sect ? "" : "\e[34mN�O\e[0m "
		);

		break;
	    }

#if (0)	/*******************************************************/
		/*
		 ******	Altera a geometria do disco *****************
		 */
	    case 'e':
	    {
		PARTTB			*reg_pp;
		const ATA_DEVICE	*adp = fdisk_data;
		int			cyl_sz, reg_index;

		if (fdisk_type == IDE_TYPE && adp->ad_cyl <= 1024)
		{
			printf
			(	"\nEste disco IDE n�o possui "
				"outras geometrias poss�veis\n"
			);
			break;
		}

		printf
		(	"\nAlterar a geometria pode impedir "
			"o acesso �s parti��es j� existentes do disco!!\n"
			"\nContinua? (n): "
		);

		if (askyesno (0) <= 0)
			break;

	   /***	gp = &generic_hdinfo; ***/

		if (fdisk_type == SCSI_TYPE)
		{
			if   (gp->h_head == 64 && gp->h_sect == 32)
				{ gp->h_head = 255; gp->h_sect = 63; }
			elif (gp->h_head == 255 && gp->h_sect == 63)
				{ gp->h_head = 64; gp->h_sect = 32; }
		}
		else		/* IDE */
		{
			if (fdisk_hdinfo != gp)
			{
				memmove (gp, fdisk_hdinfo, sizeof (HDINFO));
				fdisk_hdinfo = gp;
			}

			gp->h_head <<= 1;
			gp->h_cyl  >>= 1;

			if (gp->h_cyl >= 512)
				goto atualiza;

		    again:
			printf ("\nD� o n�mero de cabe�as: ");

			gets (line);

			if (line[0] == 'n')
			{
				gp->h_head = adp->ad_head; 
				goto atualiza;
			}

			if ((i = atol (line)) == 0 || (unsigned)i > 255)
			{
				printf ("\nN�mero inv�lido de cabe�as: %d\n", i);
				goto again;
			}

			gp->h_head = i;

			printf ("\nD� o n�mero de setores: ");

			gets (line);

			if (line[0] == 'n')
			{
				gp->h_head = adp->ad_head; 
				goto atualiza;
			}

			if ((i = atol (line)) == 0 || (unsigned)i > 63)
			{
				printf ("\nN�mero inv�lido de setores: %d\n", i);
				goto again;
			}

			gp->h_sect = i; 
		}

	    atualiza:
		fdisk_round = cyl_sz = gp->h_head * gp->h_sect;
		gp->h_cyl = (fdisk_size + cyl_sz - 1) / cyl_sz;

		/*
		 *	Atualiza as parti��es prim�rias
		 */
		for
		(	reg_index = 0, reg_pp = &parttb[0];
			reg_index < NPART;
			reg_index++, reg_pp++
		)
		{
			if (reg_pp->pt_size == 0)
				continue;

			fdisk_put_phys_addr
			(	reg_pp,
				reg_pp->pt_offset,
				reg_pp->pt_offset + reg_pp->pt_size
			);
		}

		fdisk_modified++;

		fdisk_print_parttb (0 /* sem espa�os vagos */);
		break;
	    }
#endif	/*******************************************************/

		/*
		 ******	Reescreve a tabela de parti��es *********
		 */
	    case 'w':
		if (fdisk_modified == 0)
			printf ("\nA tabela n�o foi modificada\n");

		printf ("\nReescreve a tabela de parti��es? (n): ");

		if (askyesno (0) <= 0)
			break;

		fdisk_write_all_logical_chains ();

		memmove (parttb_orig_block + PARTB_OFF, parttb, NPART * sizeof (PARTTB));

		*(ushort *)(parttb_orig_block + MAGIC_OFF) = 0xAA55;
#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", fdisk_parttb_orig_sect);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", parttb_orig_block);
#endif	DEBUG
		bwrite (fdisk_disktb, fdisk_parttb_orig_sect, parttb_orig_block, BLSZ);
#endif	NO_WRITE

		memset (parttb_emer_block, 0, BLSZ);

		memmove (parttb_emer_block + PARTB_OFF, parttb, NPART * sizeof (PARTTB));

#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", fdisk_parttb_emer_sect);
#else
#ifdef	DEBUG
		if (fdisk_debug)
			printf ("\nEscrevendo no bloco %d\n", fdisk_parttb_emer_sect);
#endif	DEBUG
		bwrite (fdisk_disktb, fdisk_parttb_emer_sect, parttb_emer_block, BLSZ);
#endif	NO_WRITE

		fdisk_modified = 0;

		get_all_parttb ();	/* Rel� as parti��es */

		break;

		/*
		 ******	Termina sem reescrever a tabela de parti��es **
		 */
	    case 'q':
		if (fdisk_modified == 0)
			return;

		printf ("\nA tabela de parti��es foi modificada!\n");

		printf ("\nTermina a execu��o de \"fdisk\" (sem atualiz�-la)? (n): ");

		if (askyesno (0) > 0)
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
		 ****** Usa a tabela de emerg�ncia **************
		 */
	    case 'e':
		memmove (parttb, parttb_emer_block + PARTB_OFF, sizeof (parttb));

		if (fdisk_read_parttb (fdisk_disktb) < 0)
			return;

		fdisk_print_parttb (0 /* Sem espa�os vagos */);
		break;

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
    prompt:
	printf ("\nfdisk> "); 	cp = gets (line);

	goto execute_cmd;

}	/* end fdisk_get_cmd */

/*
 ****************************************************************
 *	Obt�m as parti��es de um disco				*
 ****************************************************************
 */
int
fdisk_read_parttb (const DISKTB *dev_dp)
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

   /***	memsetl (parttb, 0, sizeof (parttb) / sizeof (long)); ***/
	memsetl (log_parttb, 0, sizeof (log_parttb) / sizeof (long));
   	memsetl (fdisk_log_offset, 0, sizeof (fdisk_log_offset) / sizeof (long));

#if (0)	/*******************************************************/
	if (*(ushort *)(parttb_orig_block + MAGIC_OFF) != 0xAA55)
		printf ("\n*** O bloco 0 N�O cont�m \"0x55AA\"\n");

	/*
	 *	Copia as parti��es regulares
	 */
	memmove (parttb, parttb_orig_block + PARTB_OFF, sizeof (parttb));
#endif	/*******************************************************/

	/*
	 *	Copia as parti��es estendidas
	 */
	for
	(	reg_index = 0, reg_pp = &parttb[0];
		reg_index < NPART;
		reg_index++, reg_pp++
	)
	{
		if (reg_pp->pt_size == 0)
			continue;

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
		for
		(	log_index = 0, log_pp = &log_parttb[reg_index][0];
			/* abaixo */;
			log_index++, log_pp++
		)
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

			if (bread (dev_dp, log_offset, area, BLSZ) < 0)
				return (-1);

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
	printf ("\nDisco \"%s\": ", fdisk_disktb->p_name);
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
	(	"\n IND. -DEV-  A %c --IN�CIO-- ---FINAL-- --BLOCOs--  TAM (MB) TIPO\n\n",
		fdisk_align ? 'D' : ' '
	);

	/*
	 *	Malha pela tabela
	 */
	for
	(	reg_index = 0, seq_index = 1, reg_pp = parttb;
		/* abaixo */;
		reg_index++, reg_pp++
	)
	{
		/*
		 *	Em primeiro lugar, imprime espa�os vagos
		 */
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
					"................... "
				);
				fdisk_print_MB (reg_size, 5);
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

		printf ("%s%d  ", fdisk_disktb->p_name, reg_index + 1);

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

		for
		(	log_index = 0, log_pp = &log_parttb[reg_index][0];
			/* abaixo */;
			log_index++, log_pp++
		)
		{
			/*
			 *	Em primeiro lugar, imprime espa�os vagos
			 */
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
						"................... "
					);
					fdisk_print_MB (log_size, 5);
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
			(	"%s%d%c ", fdisk_disktb->p_name,
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

	fdisk_print_MB (pp->pt_size, 5);

	printf ("  %02X ", pp->pt_type);
	print_part_type_nm (pp->pt_type);

	printf ("\n");

}	/* end fdisk_print_parttb_entry */

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
	const char	*nm = fdisk_disktb->p_name;

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
	for
	(	reg_index = 0, reg_pp = parttb;
		/* abaixo */;
		reg_index++, reg_pp++
	)
	{
		if (reg_index < NPART && reg_pp->pt_size == 0)
			continue;

		if (reg_index >= NPART)
			size = fdisk_size - last_end;
		else
			size = reg_pp->pt_offset - last_end;

		if (size >= min_size)
		{
			fdisk_print_MB (size, 5);

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
				fdisk_print_MB (size, 5);

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

	fdisk_print_MB (total, 5);

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
	daddr_t		begin, end, size;
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

		if (askyesno (1) <= 0)
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
			end = fdisk_size;

			if (fdisk_align && (i = end % fdisk_round))
			{
				printf ("\nAlinha o final com o in�cio do �ltimo cilindro do disco? (n): ");
	
				if (askyesno (0) > 0)
					end -= i;
			}

			break;
		}

		if (pp->pt_size > 0)
			{ end = fdisk_round_down (pp->pt_offset); break; }
	}

	if ((size = end - begin) <= 0 || fdisk_align && size < fdisk_round)
	{
		printf ("\nNesta �rea n�o h� espa�o dispon�vel\n");
		goto ask_begin;
	}

	if (fdisk_good_regular_area (begin, end) >= 0)
	{
		printf ("\nBloco final = %d (", end - 1);
		fdisk_print_MB (end - begin, 0);
		printf (" MB)? (s): ");

		if (askyesno (1) <= 0)
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

		end = begin + (i << (MBSHIFT - BLSHIFT));

		if (end > fdisk_size)
			goto inv_end;

		if ((end = fdisk_round_up (end)) > fdisk_size)
			end = fdisk_size;

		if (fdisk_good_regular_area (begin, end) < 0)
			goto inv_end;
	}

	/*
	 *	Cria a entrada
	 */
	pp = ip->f_pp;

	pp->pt_active	  = 0;			/* Inativa */
	pp->pt_type	  = TROPIX_T1;		/* Tropix T1 */
	pp->pt_offset	  = begin;
	pp->pt_size	  = end - begin;

	fdisk_put_phys_addr (pp, begin, end);

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
	daddr_t		begin, end, size;
	char		line[80];
	daddr_t		logoffset = fdisk_align ? gp->h_sect : 1;
	int		index, found = 0;
	char		last;

	/*
	 *	Verifica se h� mais de uma parti��o estendida
	 */
	for
	(	reg_index = 0, reg_pp = parttb;
		reg_index < NPART;
		reg_index++, reg_pp++
	)
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
	for
	(	reg_index = 0, reg_pp = parttb;
		/* abaixo */;
		reg_index++, reg_pp++
	)
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
					fdisk_disktb->p_name, reg_index + 1
				);
				break;
			}

			printf
			(	"\nNa parti��o estendida \"%s%d\"? (s): ",
				fdisk_disktb->p_name, reg_index + 1
			);

			if (askyesno (1) > 0)
				break;
		}
	}

	/*
	 *	Achou uma parti��o estendida: procura a pr�xima l�gica vaga
	 */
	for
	(	log_index = 0, log_pp = &log_parttb[reg_index][0];
		/* abaixo */;
		log_index++, log_pp++
	)
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
	for
	(	index = -1, pp = &log_parttb[reg_index][-1], last = 0;
		last == 0;
		index++, pp++
	)
	{
		/* Procura uma �rea */

		if (index < 0)			/* Antes da primeira parti��o l�gica */
		{
			if ((pp + 1)->pt_size == 0)
				continue;

			end = (pp + 1)->pt_offset - fdisk_log_offset[reg_index][index + 1];
			end = fdisk_round_down (end);

			goto begin_of_extended;
		}

		begin = fdisk_round_up (pp->pt_offset + pp->pt_size);

		end   = reg_pp->pt_offset + reg_pp->pt_size;

		if (end != fdisk_size)
			end = fdisk_round_down (end);

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
			end = (pp + 1)->pt_offset - fdisk_log_offset[reg_index][index + 1];
			end = fdisk_round_down (end);
		}

		/* Examina o tamanho */

		if ((size = end - begin) >= fdisk_round || !fdisk_align && size > logoffset)
		{
			begin += logoffset;

			printf ("\nBloco inicial = %d? (s): ", begin);

			if (askyesno (1) > 0)
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
	end = reg_pp->pt_offset + reg_pp->pt_size;

	for
	(	index = log_index - 1, pp = &log_parttb[reg_index][index];
		index >= 0;
		index--, pp--
	)
	{
		if (begin <= pp->pt_offset)
			end = pp->pt_offset - fdisk_log_offset[reg_index][index];
	}

	if (end != fdisk_size)
		end = fdisk_round_down (end);

	size = end - begin + logoffset;

	if (size <= logoffset || fdisk_align && size < fdisk_round)
	{
		printf ("\nNesta �rea n�o h� espa�o dispon�vel\n");
		goto ask_begin;
	}

    get_size:
	if (fdisk_good_logical_area (reg_index, begin - logoffset, end) >= 0)
	{
		printf ("\nBloco final = %d (", end - 1);
		fdisk_print_MB (end - begin, 0);
		printf (" MB)? (s): ");

		if (askyesno (1) <= 0)
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

		end = begin + (i << (MBSHIFT - BLSHIFT));

		if (end > fdisk_size)
			goto inv_end;

		if ((end = fdisk_round_up (end)) > fdisk_size)
			end = fdisk_size;

		if (fdisk_good_logical_area (reg_index, begin - logoffset, end) < 0)
			goto inv_end;
	}

	/*
	 *	Cria a entrada
	 */
	log_pp->pt_active = 0;			/* Inativa */
	log_pp->pt_type	  = TROPIX_T1;		/* Tropix T1 */
	log_pp->pt_offset = begin;
	log_pp->pt_size	  = end - begin;

	fdisk_put_phys_addr (log_pp, begin, end);

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
	int		log_index, i;
	daddr_t		begin, end, min_end, max_end;
	char		line[80];

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

	end = max_end;	/* Em princ�pio */

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
	printf ("\nBloco final = %d (", end - 1);
	fdisk_print_MB (end - begin, 0);
	printf (" MB)? (s): ");

	if (askyesno (1) <= 0)
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

		end = begin + (i << (MBSHIFT - BLSHIFT));

		if (end < max_end)
		{
			if (fdisk_round_up (end) < max_end)
				end = fdisk_round_up (end);
			else
				end = max_end;
		}

		if (end < min_end || end > max_end)
			goto inv_end;
	}

	/*
	 *	Altera a entrada
	 */
   /***	reg_pp->pt_active = ...; ***/
   /***	reg_pp->pt_type	  = ...; ***/
   /***	reg_pp->pt_offset = ...; ***/
   	reg_pp->pt_size	  = end - begin;

	fdisk_put_phys_addr (reg_pp, begin, end);

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
	int		i;
	daddr_t		begin, end, min_end, max_end;
	char		line[80];

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

	end = max_end;	/* Em princ�pio */

	/*
	 *	Sugere um final
	 */
	printf ("\nBloco final = %d (", end - 1);
	fdisk_print_MB (end - begin, 0);
	printf (" MB)? (s): ");

	if (askyesno (1) <= 0)
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

		end = begin + (i << (MBSHIFT - BLSHIFT));

		if (end < max_end)
		{
			if (fdisk_round_up (end) < max_end)
				end = fdisk_round_up (end);
			else
				end = max_end;
		}

		if (end < min_end || end > max_end)
			goto inv_end;
	}

	/*
	 *	Altera a entrada
	 */
   /***	log_pp->pt_active = ...; ***/
   /***	log_pp->pt_type	  = ...; ***/
   /***	log_pp->pt_offset = ...; ***/
   	log_pp->pt_size	  = end - begin;

	fdisk_put_phys_addr (log_pp, begin, end);

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
fdisk_good_regular_area (daddr_t begin, daddr_t end)
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
	if (begin > end)
		return (-1);

	/*
	 *	Verifica os valores m�ximos
	 */
	if ((unsigned)begin >= fdisk_size)
		return (-1);

	if ((unsigned)end > fdisk_size)
		return (-1);

	/*
	 *	Verifica se esta �rea pertence a alguma outra parti��o
	 */
	for (reg_pp = &parttb[0]; reg_pp < &parttb[NPART]; reg_pp++)
	{
		if (reg_pp->pt_size == 0)
			continue;

		if (end <= reg_pp->pt_offset)
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
fdisk_good_logical_area (int reg_index, daddr_t begin, daddr_t end)
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
	if (begin > end)
		return (-1);

	/*
	 *	Verifica os valores m�ximos
	 */
	if ((unsigned)begin >= fdisk_size)
		return (-1);

	if ((unsigned)end > fdisk_size)
		return (-1);

	/*
	 *	Tem de estar dentro da parti��o estendida
	 */
	if (begin < reg_pp->pt_offset)
		return (-1);

	if (end > reg_pp->pt_offset + reg_pp->pt_size)
		return (-1);

	/*
	 *	Verifica se esta �rea pertence a alguma outra parti��o l�gica
	 */
	for
	(	log_index = 0, log_pp = &log_parttb[reg_index][0];
		log_index < NLOGPART;
		log_index++, log_pp++
	)
	{
		if (log_pp->pt_size == 0)
			break;

		if (begin >= log_pp->pt_offset + log_pp->pt_size)
			continue;

		if (end <= log_pp->pt_offset - fdisk_log_offset[reg_index][log_index])
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
	for
	(	reg_index = 0, reg_pp = parttb, seq_index = 0;
		reg_index < NPART;
		reg_index++, reg_pp++
	)
	{
		if (reg_pp->pt_size == 0)
			continue;

		if (seq_index++ == given_index)
		{
			ip->f_reg_index = reg_index;
			ip->f_log_index = -1;
			ip->f_pp 	= reg_pp;

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
				ip->f_pp 	= log_pp;

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
	for
	(	reg_index = 0, reg_pp = &parttb[0];
		/* abaixo */;
		reg_index++, reg_pp++
	)
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

	if (askyesno (1) > 0)
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

	for
	(	log_index = 0, log_pp = log_parttb[reg_index];
		log_index < NLOGPART;
		log_index++, log_pp++
	)
	{
		min_offset = 0x7FFFFFFF;	/* Valor m�ximo */
		min_pp	   = NOPARTTB;
		min_index  = 0;

		for
		(	tmp_index = 0, tmp_pp = tmp_log_parttb;
			tmp_index < NLOGPART;
			tmp_index++, tmp_pp++
		)
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
fdisk_write_all_logical_chains (void)
{
	int		reg_index;
	PARTTB		*reg_pp;

	for
	(	reg_index = 0, reg_pp = parttb;
		reg_index < NPART;
		reg_index++, reg_pp++
	)
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

		fdisk_write_logical_chain (reg_index);
	}

}	/* end fdisk_write_all_logical_chains */

/*
 ****************************************************************
 *	Escreve uma cadeia das parti��es l�gicas		*
 ****************************************************************
 */
void
fdisk_write_logical_chain (int reg_index)
{
	const PARTTB	*reg_pp, *log_pp;
	PARTTB		*pp;
	int		log_index;
	daddr_t		begin, end;
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
		{
			printf ("\nEscrevendo no bloco %d\n", reg_pp->pt_offset);
		}
#endif	DEBUG
		bwrite (fdisk_disktb, reg_pp->pt_offset, area, BLSZ);
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
		end   = offset0 + size0;

		fdisk_put_phys_addr (pp, begin, end);

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
		end   = offset1 + size1;

		fdisk_put_phys_addr (pp, begin, end);

	    write:
#ifdef	NO_WRITE
		printf ("\nIa escrever no bloco %d\n", log_addr);
#else
#ifdef	DEBUG
		if (fdisk_debug)
		{
			printf ("\nEscrevendo no bloco %d\n", log_addr);
		}
#endif	DEBUG
		bwrite (fdisk_disktb, log_addr, area, BLSZ);
#endif	NO_WRITE
	}

}	/* end fdisk_write_logical_chain */

/*
 ****************************************************************
 *	Completa a entrada com os endere�os f�sicos		*
 ****************************************************************
 */
void
fdisk_put_phys_addr (PARTTB *pp, daddr_t begin, daddr_t end)
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
	msg_end = --end;

	sector	= end % gp->h_sect + 1;
	end	= end / gp->h_sect;
	head	= end % gp->h_head;
	cylin	= end / gp->h_head;

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
		(	"%s%d", fdisk_disktb->p_name,
			ip->f_reg_index + 1
		);
	}
	else
	{
		printf
		(	"%s%d%c", fdisk_disktb->p_name,
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
		"\tc: Troca de dispositivo (disco)\n"
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
