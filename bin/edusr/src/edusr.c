/*
 ****************************************************************
 *								*
 *			edusr.c					*
 *								*
 *	Gerenciador de contas					*
 *								*
 *	Vers�o	1.5.0, de 04.06.84				*
 *		3.1.1, de 15.01.99				*
 *								*
 *	M�dulo: edusr						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <time.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "../h/edusr.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
#define	EXPIRC	180		/* Data de expira��o por omiss�o */

const char	pgversion[] =  "Vers�o: 3.1.1, de 15.01.99";

entry int		exit_code = 0;	/* C�digo de retorno */

entry int		vflag;		/* Verbose */

entry const char	no_pwd[] = "-------------"; /* Senha nula */

entry char		root_pwd[] = "-------------"; /* Para o "root" */

entry int		stdin_is_a_tty;	/* N�o zero se interativo */

entry int		hoje;		/* A data de hoje (decimal) */

entry const char	std_shell[] = "/bin/sh"; /* SHELL padr�o */

entry const char	*pwd_file_nm = "/etc/passwd"; /* Nome do arquivo de senhas */

entry const char	*group_file_nm = "/etc/group"; /* Nome do arquivo group */

const char lock_file_nm[] = "/etc/pwd_lock_file"; /* Tranca do arquivo de senhas */

/*
 ******	Valores correntes****************************************
 */
entry int		current_group_id;	/* GID */
entry char		current_group_nm[16];	/* Nome do Grupo */
entry int		current_quota;		/* Cota */
entry int		current_expir_date;	/* Data de expira��o */
entry char		current_home[64];	/* Diret�rio HOME */
entry char		current_shell[64];	/* Interpretador */

/*
 ****************************************************************
 *	Gerenciador de contas					*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;
	const GROUP	*gr;
	const PASSWD	*pw;

	cmd_nm = pgname;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
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
	 *	Verifica se o programa foi instalado corretamente
	 */
	if (geteuid () != 0)
		error ("$Este comando pode ser executado apenas pelo SUPERUSU�RIO");

	/*
	 *	Verifica se h� outro usu�rio de "edusr"
	 */
	if (open (lock_file_nm, O_RDWR|O_LOCK|O_CREAT, 0600) < 0)
		error ("$Arquivo de contas/senhas em uso: tente novamente mais tarde");

	/*
	 *	Procura um grupo corrente razo�vel
	 */
	strcpy (current_group_nm, "???");
	current_group_id  = NIG;

	setgrent ();

	while ((gr = getgrent ()) != NULL)
	{
		strcpy (current_group_nm, gr->gr_name);

		if ((current_group_id = gr->gr_gid) > 0)
			break;
	}

	endgrent ();

	/*
	 *	Procura a senha de "root"
	 */
	if ((pw = getpwnam ("root")) == NOPASSWD)
		error ("N�o encontrei a senha de \"root\"");
	else
		strcpy (root_pwd, pw->pw_passwd);

	/*
	 *	Inicializa��o das outras vari�veis globais
	 */
	stdin_is_a_tty = isatty (fileno (stdin));
	hoje = time ((time_t *)NULL) / NSPD;

	current_quota = 0;
	current_expir_date = 0;
	strcpy (current_shell, std_shell);
	strcpy (current_home, "/home");

	/*
	 *	Procura o diret�rio dos usu�rios
	 */
	if (access (current_home, 2) < 0)
		error ("*N�o achei o diret�rio \"%s\"", current_home);

	exec_cmd (NOSTR);

	return (exit_code);

}	/* end edusr */

/*
 ****************************************************************
 *	Imprime uma mensagem de erro				*
 ****************************************************************
 */
void
error (const char *format, ...)
{
	va_list		args;
	const char	*fmt = format;
	char		err, abrt;

	va_start (args, format);

	if ((abrt = *fmt) == '$')
		fmt++;

	if ((err = *fmt) == '*')
		fmt++;

	fprintf  (stderr, "%s: ", cmd_nm);
	vfprintf (stderr, fmt, args);

	if (err == '*' && errno != 0)
		fprintf (stderr, " (%s)", strerror (errno));

	fprintf (stderr, "\n");

	if (abrt == '$')
		quit ();

	va_end (args);

}	/* end error */

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
		"%s - gerencia as contas/senhas\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nObs.:\tPara um resumo dos comandos, tecle \"?\""
		" ap�s o \"prompt\" de \"%s\"\n",
		pgname
	);

	exit (2);

}	/* end help */
