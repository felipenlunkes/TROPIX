/*
 ****************************************************************
 *								*
 *			login.c					*
 *								*
 *	Post office protocol (servidor)				*
 *								*
 *	Vers�o	1.0.0, de 15.08.98				*
 *								*
 *	M�dulo: POP3_S						*
 *		Utilit�rios de comunica��es			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <xti.h>

#include "../h/pop3_s.h"

/*
 ****************************************************************
 *	Defini��es para manipular contas e senhas		*
 ****************************************************************
 */
entry PASSWD		user_pw;	/* Do usu�rio corrente */

entry char 		no_passwd[] = "-------------";	/* Senha nula */

entry PASSWD	bad_user = {"", "?????????????", "", 100, 100, 0, 0, "", "", "" };

entry const char	*user_nm;		/* Nome do usu�rio */

/*
 ****************************************************************
 *	Processa o comando USER					*
 ****************************************************************
 */
void
do_user (int argc, const char *argv[])
{
	const PASSWD	*pw = &user_pw;

	if (server_state == S_READY)
		{ delete_messages (); put_mbox (); }

	server_state = S_RESET;

	if (argc == 0)
	{
		reply ("-*Faltando o nome do usu�rio");
		return;
	}

	user_nm = argv[0];

	/*
	 *	Volta a ser superusu�rio
	 */
	if (seteuid (0) < 0)
		error ("$*N�o consegui voltar a ser SUPERUSU�RIO");

	if (pw->pw_name != NOSTR)
	{
		error
		(	"Logout para \"%s@%s\"",
			pw->pw_name, client_node_nm
		);
	}

	/*
	 *	Procura a entrada do usu�rio e copia as entradas relevantes
	 */
	if ((pw = getpwnam (user_nm)) == NOPASSWD)
		pw = &bad_user;

	user_pw.pw_name   = strdup (pw->pw_name);
	user_pw.pw_passwd = strdup (pw->pw_passwd);
	user_pw.pw_uid    = pw->pw_uid;
	user_pw.pw_gid    = pw->pw_gid;
	user_pw.pw_dir    = strdup (pw->pw_dir);

	if (user_pw.pw_dir == NOSTR)
		error ("$Mem�ria esgotada");

	pw = &user_pw;		/* Passa a usar a c�pia */

	endpwent ();

	/*
	 *	Verifica se precisa de senha
	 */
	if (streq (pw->pw_passwd, no_passwd))
		{ get_mbox (); return; }

	reply ("+*Necessito de senha para o usu�rio \"%s\"", user_nm);

	server_state = S_USER;

}	/* end do_user */

/*
 ****************************************************************
 *	Processa o comando PASS					*
 ****************************************************************
 */
void
do_pass (int argc, const char *argv[])
{
	const PASSWD	*pw = &user_pw;

	if   (server_state == S_READY)
	{
		reply ("+*N�o necessito de senha");
		return;
	}
	elif (server_state != S_USER)
	{
		reply ("-*Seq��ncia err�nea de comandos");
		return;
	}

	if (argc == 0)
	{
		reply ("-*Faltando a senha");
		return;
	}

	if (!streq (crypt (argv[0], pw->pw_passwd), pw->pw_passwd))
	{
		reply ("-*Senha incorreta");
		return;
	}

	get_mbox ();

}	/* end do_pass */
