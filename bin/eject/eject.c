/*
 ****************************************************************
 *								*
 *			eject.c					*
 *								*
 *	Ejeta o meio remov�vel de um dispositivo		*
 *								*
 *	Vers�o	4.3.0, de 01.10.02				*
 *		4.3.0, de 01.10.02				*
 *								*
 *	M�dulo: eject						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/mntent.h>
#include <sys/sb.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 4.3.0, de 01.10.00";

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

const char	fstab_nm[] = "/etc/fstab";

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Ejeta o meio remov�vel de um dispositivo		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	int		opt, fd;
	const char	*nm = NOSTR;
	FILE		*fp;
	int		uid, code;
	char		dev_nm[32];
	char		dir_nm[32];
	STAT		s;
	MNTENT		mntent;


	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "rpwe23vH")) != EOF)
	{
		switch (opt)
		{
		    case '2':			/* zip0 */
			if (nm != NOSTR)
				help ();

			nm = "/dev/zip0";
			break;

		    case '3':			/* zip1 */
			if (nm != NOSTR)
				help ();

			nm = "/dev/zip1";
			break;

		    case 'v':			/* Verbose */
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
	 *	Obtem o dispositivo
	 */
	if (*argv != NOSTR && nm == NOSTR)
		{ nm = *argv; argv++; }

	if (*argv != NOSTR)
		help ();

	if (nm == NOSTR)
		nm = "/dev/zip";

	/*
	 *	Abre e verifica se � um dispositivo ou diret�rio
	 */
	if (stat (nm, &s) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", nm);

	/*
	 *	Se N�O for superusu�rio ou foi dado um diret�rio, analisa "fstab"
	 */
	if ((uid = getuid ()) != 0 || S_ISDIR (s.st_mode))
	{
		if ((fp = fopen (fstab_nm, "r")) == NOFILE)
			error ("$*N�o consegui abrir \"%s\"", fstab_nm);

		for (EVER)
		{
			if ((code = getmntent (fp, dev_nm, dir_nm, &mntent)) == EOF)
				error ("$N�o achei \"%s\" em \"%s\"", dev_nm, fstab_nm);

			if (code == 0)
				continue;

			if (streq (dev_nm, nm) || streq (dir_nm, nm))
				break;
		}

		fclose (fp);

		if (uid != 0 && (mntent.me_flags & SB_USER) == 0)
			{ errno = EPERM; error ("$*N�o consegui retirar o meio"); }

		nm = dev_nm;
	}

	/*
	 *	Abre o dispositivo
	 */
	if ((fd = open (nm, O_RDONLY)) < 0)
		error ("$*N�o consegui abrir \"%s\"", nm);

	/*
	 *	Libera o meio
	 */
	if (ioctl (fd, ZIP_LOCK_UNLOCK, 0) < 0)
		error ("$*N�o consegui retirar o meio (1)");

	/*
	 *	Liga o motor
	 */
	if (ioctl (fd, ZIP_START_STOP, 1) < 0)
		error ("$*N�o consegui retirar o meio (2)");

	/*
	 *	Desliga o motor
	 */
	if (ioctl (fd, ZIP_START_STOP, 2) < 0)
		error ("$*N�o consegui retirar o meio (3)");

	close (fd);

	return (exit_code);

}	/* end eject */

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
		"%s - ejeta o meio remov�vel de um dispositivo\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-23] [<dispositivo/diret�rio>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-2: O dispositivo ser� \"/dev/zip0\"\n"
		"\t-3: O dispositivo ser� \"/dev/zip1\"\n"
		"\nObs.:\tSe <dev> n�o for dado, ser� considerado \"/dev/zip\"\n"
	);

	exit (2);

}	/* end help */
