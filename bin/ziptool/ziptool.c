/*
 ****************************************************************
 *								*
 *			ziptool.c				*
 *								*
 *	Ferramenta para dispositivos Iomega ZIP			*
 *								*
 *	Vers�o	3.0.0, de 28.01.97				*
 *		4.5.0, de 25.12.03				*
 *								*
 *	M�dulo: ziptool						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/disktb.h>
#include <sys/kcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 4.5.0, de 25.12.03";

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	CODE_V7	 0xA8
#define	CODE_T1	 0xA9
#define	CODE_FAT 0x06

#define	NPART		4	/* N�mero total de parti��es reg. */

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	modeflag;	/* Opera��o a executar */
entry int	vflag;		/* Verbose */

/*
 ****** Uma entrada da tabela de parti��es **********************
 */
typedef struct
{
	char	head;		/* Cabe�a */
	char	sect;		/* Setor */
	char	cyl;		/* Cilindro */

}	TRIO;

typedef struct			/* Tabela de parti��es */
{
	char	pt_active;	/* Entrada ativa se 0x80 */
	TRIO	pt_start;	/* Trio inicial */
	char	pt_type;	/* Tipo do sistema de arquivos */
	TRIO	pt_end;		/* Trio final */
	char	pt_ch_offset[4]; /* Deslocamento (blocos) */
	char	pt_ch_size[4];	/* Tamanho (blocos) */

}	PARTTB;

typedef struct
{
	char	m_boot[446];
	PARTTB	m_parttb[NPART];
	ushort	m_signature;

}	MBR;

#define	pt_offset(pt)	*(long *)(pt->pt_ch_offset)
#define	pt_size(pt)	*(long *)(pt->pt_ch_size)

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		zip_get_status (const char *, int, int);
void		zip_set_status (const char *, int);
void		zip_eject (const char *, int);
void		zip_code (const char *, int, const char *);
void		help (void);

/*
 ****************************************************************
 *	Ferramenta para dispositivos Iomega ZIP			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	int		opt, fd;
	const char	*dev_nm = NOSTR;
	const char	*code_nm = NOSTR;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "rpwqec:23vH")) != EOF)
	{
		switch (opt)
		{
		    case 'r':			/* Read-only */
			if (modeflag)
				help ();

			modeflag = 'r';
			break;

		    case 'p':			/* Read-only com senha */
			if (modeflag)
				help ();

			modeflag = 'p';
			break;

		    case 'w':			/* Read/write */
			if (modeflag)
				help ();

			modeflag = 'w';
			break;

		    case 'q':			/* Read/write enquanto n�o ejetado */
			if (modeflag)
				help ();

			modeflag = 'q';
			break;

		    case 'e':			/* Eject */
			if (modeflag)
				help ();

			modeflag = 'e';
			break;

		    case 'c':			/* C�digo da parti��o */
			if (modeflag)
				help ();

			modeflag = 'c';
			code_nm  = optarg;
			break;

		    case '2':			/* zip0 */
			if (dev_nm != NOSTR)
				help ();

			dev_nm = "/dev/zip0";
			break;

		    case '3':			/* zip1 */
			if (dev_nm != NOSTR)
				help ();

			dev_nm = "/dev/zip1";
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			fputc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	if (modeflag == 0)
		modeflag = 'g';

	/*
	 *	Obtem o dispositivo
	 */
	if (*argv != NOSTR && dev_nm == NOSTR)
		{ dev_nm = *argv; argv++; }

	if (*argv != NOSTR)
		help ();

	if (dev_nm == NOSTR)
		dev_nm = "/dev/zip";

	/*
	 *	Abre o dispositivo
	 */
	if ((fd = open (dev_nm, O_RDONLY)) < 0)
		error ("$*N�o consegui abrir \"%s\"", dev_nm);

	/*
	 *	Executa a fun��o pedida
	 */
	switch (modeflag)
	{
	    case 'g':
		zip_get_status (dev_nm, fd, -1);
		break;

	    case 'r':
	    case 'p':
	    case 'w':
	    case 'q':
		zip_set_status (dev_nm, fd);
		break;

	    case 'e':
		zip_eject (dev_nm, fd);
		break;

	    case 'c':
		zip_code (dev_nm, fd, code_nm);
		break;

	}	/* end switch */

	return (exit_code);

}	/* end ziptool */

/*
 ****************************************************************
 *	Obt�m a prote��o atual					*
 ****************************************************************
 */
void
zip_get_status (const char *dev_nm, int fd, int desired_status)
{
	int			status;
	const char		*msg;

	/*
	 *	Obt�m o estado atual de prote��o
	 */
	if ((status = ioctl (fd, ZIP_GET_PROTECTION)) < 0)
		error ("$*N�o consegui obter a prote��o de \"%s\"", dev_nm);

	/*
	 *	Imprime o estado atual de prote��o
	 */
	switch (status)
	{
	    case 0:
		msg = "permite leituras/escritas";
		break;

	    case 2:
		msg = "est� protegido para escritas";
		break;

	    case 3:
		msg = "est� protegido para escritas com senha";
		break;

	    case 10:
		msg = "permite leituras/escritas enquanto n�o retirado";
		break;

	    default:
		msg = "est� com uma prote��o desconhecida";
		break;
	}

	if (desired_status >= 0 && status != desired_status)
		error ("N�O consegui trocar a prote��o (provavelmente senha incorreta)");

	printf ("O disco do dispositivo \"%s\" %s", dev_nm, msg);

	if (vflag)
		printf (" (%d)", status);

	printf ("\n");

	close (fd);

}	/* end zip_get_status */

/*
 ****************************************************************
 *	Atribui a prote��o atual				*
 ****************************************************************
 */
void
zip_set_status (const char *dev_nm, int fd)
{
	int			status;
	const char		*pwd;
	struct	{ int mode; char pwd[80]; }	mode_pwd;

	/*
	 *	Obt�m o estado atual de prote��o
	 */
	if ((status = ioctl (fd, ZIP_GET_PROTECTION)) < 0)
		error ("$*N�o consegui obter a prote��o de \"%s\"", dev_nm);

	/*
	 *	Verifica se precisa de senha
	 */
	mode_pwd.pwd[0] = '\0';

	if (status == 3 || modeflag == 'p')
	{
		if ((pwd = getpass ("Senha: ")) == NOSTR)
			error ("$*N�o consegui obter a senha");

		strcpy (mode_pwd.pwd, pwd);
	}

	if (modeflag == 'p')
	{
		if ((pwd = getpass ("Repita a senha: ")) == NOSTR)
			error ("$*N�o consegui obter a senha");

		if (!streq (mode_pwd.pwd, pwd))
			error ("$A senha N�O conferiu");
	}

	/*
	 *	Atribui o novo estado de prote��o
	 */
	switch (modeflag)
	{
	    case 'r':
		mode_pwd.mode = 2;
		break;

	    case 'p':
		mode_pwd.mode = 3;
		break;

	    case 'w':
		mode_pwd.mode = 0;
		break;

	    case 'q':
		if (status == 0)
		{
			mode_pwd.mode = 2;

			if (ioctl (fd, ZIP_SET_PROTECTION, &mode_pwd) < 0)
				error ("$*N�o consegui alterar a prote��o de \"%s\"", dev_nm);

			status = 2;
		}

		if (status != 2)
			error ("$O disco n�o est� est� protegido para escritas (sem senha)");

		mode_pwd.mode = 10;
		break;

	    default:
		printf ("est� com uma prote��o desconhecida");

	}	/* end switch */

	if (ioctl (fd, ZIP_SET_PROTECTION, &mode_pwd) < 0)
		error ("$*N�o consegui alterar a prote��o de \"%s\"", dev_nm);

	/*
	 *	Imprime o novo estado
	 */
	zip_get_status (dev_nm, fd, mode_pwd.mode);

	close (fd);

}	/* end zip_set_status */

/*
 ****************************************************************
 *	Retira o disco da unidade				*
 ****************************************************************
 */
void
zip_eject (const char *dev_nm, int fd)
{
	/*
	 *	Libera o disco
	 */
	if (ioctl (fd, ZIP_LOCK_UNLOCK, 0) < 0)
		error ("$*N�o consegui retirar o disco (%s, 1)");

	/*
	 *	Liga o motor
	 */
	if (ioctl (fd, ZIP_START_STOP, 1) < 0)
		error ("$*N�o consegui retirar o disco (%s, 2)");

	/*
	 *	Desliga o motor
	 */
	if (ioctl (fd, ZIP_START_STOP, 2) < 0)
		error ("$*N�o consegui retirar o disco (%s, 3)");

	close (fd);

}	/* end zip_eject */

/*
 ****************************************************************
 *	Consulta/atribui o c�digo da parti��o			*
 ****************************************************************
 */
void
zip_code (const char *dev_nm, int fd, const char *code_nm)
{
	int		n, index, code_value = 0;
	const char	*str;
	DISKTB		*disktb, *end_disktb, *dp;
	PARTTB		*pp;
	off_t		offset;
	char		path[16] = "/dev/";
	char		*cp_point = path + 5;
	STAT		s;
	MBR		mbr;

	/*
	 *	Obt�m o estado do dispositivo
	 */
	if (fstat (fd, &s) < 0)
		error ("$*N�o consegui obter o estado de \"%s\"", dev_nm);

	/*
	 *	Obt�m a tabela de disco
	 */
	if ((n = kcntl (K_GET_DEV_TB, NODEV, NODISKTB)) < 0)
		error ("$*N�o consegui obter o tamanho da tabela de discos");

	dp = disktb = alloca (n * sizeof (DISKTB)); end_disktb = disktb + n;

	if (kcntl (K_GET_DEV_TB, NODEV, disktb) < 0)
		error ("$*N�o consegui obter a tabela de discos");

	/*
	 *	Procura o disposito na tabela
	 */
	for (/* acima */; /* abaixo */; dp++)
	{
		if (dp >= end_disktb)
			error ("$N�o encontrei \"%s\" na tabela de parti��es", dev_nm);

		if (dp->p_name[0] == '*')
			continue;

		if (dp->p_dev == s.st_rdev)
			break;
	}

	offset = dp->p_offset;

	close (fd);

	/*
	 *	Procura a parti��o do disco inteiro
	 */
	if (strlen (dp->p_name) != 4)
		error ("$O nome da parti��o \"%s\" N�O tem 4 caracteres", dp->p_name);

	dp->p_name[3] = '\0';

	strcpy (cp_point, dp->p_name);

	/*
	 *	Abre e l� o MBR do disco
	 */
	if ((fd = open (path, O_RDWR)) < 0)
		error ("$*N�o consegui abrir \"%s\"", path);

	if (read (fd, &mbr, sizeof (mbr)) < 0)
		error ("$*Erro de leitura de \"%s\"", path);

	if (mbr.m_signature != 0xAA55)
		error ("$O MBR de \"%s\" N�O cont�m a assinatura 0xAA55", path);

	/*
	 *	Procura a parti��o atrav�s do deslocamento
	 */
	for (pp = mbr.m_parttb, index = 0; /* abaixo */; pp++, index++)
	{
		if (index >= NPART)
			error ("$N�o encontrei a parti��o correspondente de \"%s\"", dev_nm);

		if (pt_offset (pp) == offset)
			break;
	}

	/*
	 *	Executa a fun��o desejada
	 */
	if   (streq (code_nm, "-"))
	{
		switch (pp->pt_type)
		{
		    case CODE_FAT:
			code_nm = " (FAT)";
			break;

		    case CODE_V7:
			code_nm = " (V7)";
			break;

		    case CODE_T1:
			code_nm = " (T1)";
			break;

		    default:
			code_nm = "";
			break;
		}

		printf ("C�digo da parti��o = 0x%02X%s\n", pp->pt_type, code_nm);
		close (fd);
		exit (0);
	}
	elif (streq (code_nm, "V7"))
	{
		code_value = CODE_V7;
	}
	elif (streq (code_nm, "T1"))
	{
		code_value = CODE_T1;
	}
	elif (streq (code_nm, "FAT"))
	{
		code_value = CODE_FAT;
	}
	elif ((code_value = strtol (code_nm, &str, 0)) & ~0xFF)
	{
		error ("$C�digo \"%s\" inv�lido", code_nm);
	}

	pp->pt_type = code_value;

	lseek (fd, 0, SEEK_SET);

	if (write (fd, &mbr, sizeof (mbr)) != sizeof (mbr))
		error ("$*Erro de escrita de \"%s\"", path);

	close (fd);

}	/* end zip_code */

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
		"%s - ferramenta para dispositivos Iomega ZIP\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-rpwqe] [-c <code>] [-23] [<dev>]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Imprime a prote��o atual\n"
		"\t-r: Altera a prote��o para permitir apenas leituras\n"
		"\t-p: Como acima, mas com senha\n"
		"\t-w: Altera a prote��o para permitir leituras e escritas\n"
		"\t-q: Como acima, mas somente enquanto n�o for retirado\n"
		"\t-e: Retira o dispositivo da unidade\n"
		"\t-c: Consulta/atribui o c�digo de parti��o <code>\n"
		"\t-2: Atribui o valor \"/dev/zip0\" a <dev>\n"
		"\t-3: Atribui o valor \"/dev/zip1\" a <dev>\n"
		"\nObs.:\tSe <dev> n�o for dado, ser� considerado \"/dev/zip\"\n"
	);

	exit (2);

}	/* end help */
