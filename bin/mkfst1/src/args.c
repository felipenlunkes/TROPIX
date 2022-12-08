/*
 ****************************************************************
 *								*
 *			args.c					*
 *								*
 *	Analisa profundamente as op��es do programa		*
 *								*
 *	Vers�o	4.3.0, de 04.07.02				*
 *		4.6.0, de 22.09.02				*
 *								*
 *	M�dulo: mkfst1						*
 *		Utilit�rios especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/scb.h>
#include <sys/sync.h>
#include <sys/mntent.h>
#include <sys/sb.h>
#include <sys/syscall.h>
#include <sys/disktb.h>
#include <sys/t1.h>
#include <sys/ioctl.h>
#include <sys/kcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <a.out.h>
#include <stat.h>
#include <fcntl.h>
#include <ustat.h>

#include "../h/mkfst1.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry DISKTB	dev_disktb;	/* Entrada da tabela de parti��es */

entry STAT	dev_s;		/* O estado do dispositivo/arquivo */

entry char	fs_partnm[32];	/* Nome da parti��o */

entry SB	*sb_list;	/* Lista de SBs (ordem normal) */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		remove_regular_file (int flag);
void		create_SB_list (void);
const SB	*search_SB_list (const char *dev_nm);

/*
 ****************************************************************
 *	Analisa o dispositivo					*
 ****************************************************************
 */
void
get_dev (const char *dev_nm)
{
	USTAT		u;
	int		len;
	char		*cwd, *path;

	/*
	 *	Obt�m o estado do dispositivo
	 */
	if (stat (fs_nm = dev_nm, &dev_s) < 0)
	{
		if (!rflag)
			error ("$*N�o consegui obter o estado de \"%s\"", dev_nm);

		if ((fs_fd = open (dev_nm, O_CREAT|O_RDWR, 0666)) < 0)
			error ("$*N�o consegui criar o arquivo \"%s\"", dev_nm);

		if (fstat (fs_fd, &dev_s) < 0)
			error ("$*N�o consegui obter o estado de \"%s\"", dev_nm);

		error_default_function = remove_regular_file;

		fs_clear (T1_SBNO);
	}
	else
	{
		if ((fs_fd = open (dev_nm, O_RDWR)) < 0)
			error ("$*N�o consegui abrir \"%s\"", dev_nm);

		switch (dev_s.st_mode & S_IFMT)
		{
		    case S_IFREG:
			create_SB_list ();

			/* Se n�o for um caminho absoluto, expande */

			if (dev_nm[0] != '/')
			{
				if ((cwd = getcwd (NOSTR, 128)) == NOSTR)
					error ("$*N�O consegui obter o nome do diret�rio corrente");

				len = strlen (cwd) + 1 + strlen (dev_nm) + 1; path = alloca (len);

				sprintf (path, "%s/%s", cwd, dev_nm); dev_nm = path;
			}

			if (search_SB_list (dev_nm) != NOSB)
				error ("$O arquivo \"%s\" est� montado", dev_nm);

			break;

		    case S_IFBLK:
		    case S_IFCHR:
			if (ustat (dev_s.st_rdev, &u) >= 0)
				error ("$O dispositivo \"%s\" est� montado", dev_nm);

			if (kcntl (K_GET_DEV_TB, dev_s.st_rdev, &dev_disktb) < 0)
				error ("CUIDADO: N�o consegui obter a tabela de \"%s\"", dev_nm);

			break;

		    default:
			error
			(	"$O arquivo \"%s\" � do tipo \"%c\" inv�lido",
				dev_nm, modetostr (dev_s.st_mode)[0]
			);
		}

#if (0)	/*******************************************************/
		if (ioctl (fs_fd, DKISADISK) < 0)
			error ("$O dispositivo \"%s\" N�O � disco", dev_nm);
#endif	/*******************************************************/
	}

	fs_read (T1_SBNO, &sb);

}	/* end get_dev */

/*
 ****************************************************************
 *	Analisa os argumentos					*
 ****************************************************************
 */
void
analyse_arguments (const char *argv[])
{
	DISKTB		*pp = &dev_disktb;
	T1SB		*sp = &sb;
	char		old;
	daddr_t		fs_sz;
	int		nargs = 0;
	const char	*arg, *str;

	/*
	 *	obt�m o nome do tipo da parti��o do disco
	 */
	if (pp->p_name[0] != '\0')
		kcntl (K_GET_PARTNM, pp->p_type, fs_partnm);

	/*
	 *	Verifica se o dispositivo j� tinha um sistema de arquivos
	 */
	if (old = (sp->s_magic == T1_SBMAGIC))
		fs_sz = sp->s_fs_sz << (BL4SHIFT - BLSHIFT);
	elif (S_ISREG (dev_s.st_mode))
		fs_sz = dev_s.st_size >> BLSHIFT;
	else
		fs_sz = 0;

	/*
	 ******	1: Analisa o tamanho do sistema de arquivos *************
	 */
	if ((arg = *argv) != NOSTR)
		argv++;

	if   (arg == NOSTR || streq (arg, "."))
	{
		if (!old && pp->p_name[0] != '\0')
			{ fs_sz = pp->p_size; nargs++; }
	}
	elif (streq (arg, "-"))
	{
		if (pp->p_name[0] != '\0')
			{ fs_sz = pp->p_size; nargs++; }
	}
	else	/* Dado o n�mero de blocos */
	{
		if ((fs_sz = strtol (arg, &str, 0)) <= 0)
			error ("$Tamanho inv�lido: \"%s\"", arg);

		if   (*str == 'k' || *str == 'K')
			{ fs_sz <<= (KBSHIFT - BLSHIFT); str++; }
		elif (*str == 'm' || *str == 'M')
			{ fs_sz <<= (MBSHIFT - BLSHIFT); str++; }

		if (*str != '\0')
			error ("$Tamanho inv�lido: \"%s\"", arg);

		if (pp->p_name[0] != '\0' && fs_sz > pp->p_size)
			error ("$Tamanho excessivo: \"%s\"", arg);

	   	nargs++;
	}

	if (fs_sz == 0)
		error ("$N�o consegui obter o tamanho do sistema de arquivos");

	fs_sz &= ~(BL4SZ / BLSZ - 1);

	/* Exige que tenha, no minimo, 10 de 4 KB blocos!!! */

	if ((fs_sz >>= (BL4SHIFT - BLSHIFT)) < 10)
		error ("$Tamanho insuficiente: %d blocos", fs_sz);

	if ((fs_sz & T1_ZONE_MASK) <= T1_BMNO)
		fs_sz &= ~T1_ZONE_MASK;

	if (S_ISREG (dev_s.st_mode) && dev_s.st_size < (fs_sz << BL4SHIFT))
		fs_clear (fs_sz - 1);

	sp->s_fs_sz = fs_sz;

	/*
	 ******	2: Verifica se foi dado o nome do volume ****************
	 */
	if ((arg = *argv) != NOSTR)
		argv++;

	if   (arg == NOSTR || streq (arg, "."))
	{
		if (!old)
			{ strcpy (sp->s_fname, "???"); nargs++; }
	}
	elif (streq (arg, "-"))
	{
		strcpy (sp->s_fname, "???"); nargs++;
	}
	else	/* Dado um valor */
	{
		strscpy (sp->s_fname, arg, sizeof (sp->s_fname)); nargs++;
	}

	/*
	 ******	3: Verifica se foi dado o nome do dispositivo f�sico ****
	 */
	if ((arg = *argv) != NOSTR)
		argv++;

	if   (arg == NOSTR || streq (arg, "."))
	{
		if (!old && pp->p_name[0] != '\0')
			strcpy (sp->s_fpack, pp->p_name);
	}
	elif (streq (arg, "-"))
	{
		if (pp->p_name[0] != '\0')
			strcpy (sp->s_fpack, pp->p_name);
	}
	else	/* Dado um valor */
	{
		strscpy (sp->s_fpack, arg, sizeof (sp->s_fpack));
	}

	nargs++;	/* N�o � t�o importante */

	/*
	 ******	Ep�logo *************************************************
	 *
	 *	Se n�o havia um sistema gerado, todos os argumentos devem ser especificados
	 */
	if (*argv != NOSTR)
		error ("CUIDADO: Argumentos sup�rfluos\n");

	if (!old && nargs < 3)
	{
		error ("O dispositivo \"%s\" ainda N�O cont�m um sistema de arquivos", fs_nm);
		error ("$Nem todos os argumentos foram especificados/obtidos");
	}

	sp->s_magic = T1_SBMAGIC;

	sp->s_bl_sz = BL4SZ;

	sp->s_busy_bl  = T1_BMNO;
	sp->s_busy_ino = 0;

}	/* end analyse_arguments */

/*
 ****************************************************************
 *	Remove o arquivo regular criado				*
 ****************************************************************
 */
void
remove_regular_file (int flag)
{
	unlink (fs_nm); exit (1);

}	/* end remove_regular_file */

/*
 ****************************************************************
 *	Prepara a lista de SBs (na ordem normal)		*
 ****************************************************************
 */
void
create_SB_list (void)
{
	int		len;
	SYM		*sym_p;
	const SB	*phys_sp, *next_phys_sp;
	SB		*sp, *last_sp = NOSB;
	SCB		scb;

	/*
	 *	Obtem o "system control block"
	 */
	if ((int)getscb (&scb) == -1)
		error ("$*N�o consegui obter o SCB");

	/*
	 *	Obt�m o endere�o da estrutura "sb_head"
	 */
	len = strlen ("_sb_head"); sym_p = alloca (SYM_SIZEOF (len));

	sym_p->s_nm_len = len; strcpy (sym_p->s_name, "_sb_head");

	if (kcntl (K_GETSYMGN, len, sym_p) < 0)
		error ("$*N�o consegui obter o endere�o de \"_sb_head\"");

	/*
	 *	Mapeia a cabe�a da fila
	 */
	phys_sp = phys ((void *)sym_p->s_value, sizeof (SB), O_KERNEL|O_RDONLY);

	if ((int)phys_sp == -1)
		error ("$*N�o consegui mapear SBHEAD");

	next_phys_sp = phys_sp->sb_forw;

	phys (phys_sp, 0, 0);

	/*
	 *	Percorre a Lista de SBs e cria uma c�pia
	 */
	while (next_phys_sp != (SB *)sym_p->s_value)
	{
		phys_sp = phys (next_phys_sp, sizeof (SB), O_KERNEL|O_RDONLY);

		if ((int)phys_sp == -1)
			error ("$*N�o consegui mapear um SB");

		if ((sp = malloc (sizeof (SB))) == NOSB)
			error (NOSTR);

		memmove (sp, phys_sp, sizeof (SB));

		if (sb_list == NOSB)
			sb_list = sp;
		else
			last_sp->sb_forw = sp;

		last_sp = sp; sp->sb_forw = NOSB;
			
		next_phys_sp = phys_sp->sb_forw;

		if ((int)phys (phys_sp, 0, 0) == -1)
			error ("*N�o consegui desmapear um SB");
	}

#ifdef	DEBUG
	/*
	 *	Imprime a lista
	 */
	for (sp = sb_list; sp != NOSB; sp = sp->sb_forw)
		printf ("\"%s\" => \"%s\"\n", sp->sb_dev_nm, sp->sb_dir_nm);
#endif	DEBUG

}	/* end create_SB_list */

/*
 ****************************************************************
 *	Procura na lista de SBs					*
 ****************************************************************
 */
const SB *
search_SB_list (const char *dev_nm)
{
	const SB	*sp;

	for (sp = sb_list; sp != NOSB; sp = sp->sb_forw)
	{
		if (streq (sp->sb_dev_nm, dev_nm))
			return (sp);
	}

	return (NOSB);

}	/* end search_SB_list */

