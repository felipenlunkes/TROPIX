/*
 ****************************************************************
 *								*
 *			link_c.c				*
 *								*
 *	Compara��o remota de �rvores (cliente) 			*
 *								*
 *	Vers�o	2.3.0, de 28.10.91				*
 *		4.2.0, de 02.05.02				*
 *								*
 *	M�dulo: TCMPTO_C/TNET					*
 *		Utilit�rios de comunica��es			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../tnet.h"
#include "../h/tcmpto_c.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
entry LITEM	*local_linklist_first,	/* Come�o da Lista */
		*local_linklist_last;	/* Final da Lista */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		verdir (const char *);

/*
 ****************************************************************
 *	Processa LINKs locais 					*
 ****************************************************************
 */
char *
local_link_proc (const char *file_nm, STAT *sp)
{
	LITEM		*lp;

	/*
	 *	Se tem apenas 1 LINK, nada precisa ser feito
	 */
	if (sp->st_nlink == 1)
		return (NOSTR);

	/*
	 *	Insere na lista
	 */
	if ((lp = malloc (sizeof (LITEM))) == (LITEM *)NULL)
		error ("$N�o obtive mem�ria para item de elo f�sico");

	if ((lp->l_name = strdup (file_nm)) == NOSTR)
		error ("$N�o obtive mem�ria para item de elo f�sico");

	lp->l_dev = sp->st_dev;
	lp->l_ino = sp->st_ino;

	lp->l_next = (LITEM *)NULL;

	if (local_linklist_first == (LITEM *)NULL)
		local_linklist_first = lp;
	else
		local_linklist_last->l_next = lp;

	local_linklist_last = lp;

	/*
	 *	Verifica se um outro nome j� foi visto
	 */
	for (lp = local_linklist_first; lp != local_linklist_last; lp = lp->l_next)
	{
		if (lp->l_dev == sp->st_dev && lp->l_ino == sp->st_ino)
			return (lp->l_name);
	}

	return (NOSTR);

}	/* end local_link_proc */

/*
 ****************************************************************
 *	Remove a lista de LINKs					*
 ****************************************************************
 */
void
delete_local_link_list (void)
{
	LITEM		*lp, *next;

	for (lp = local_linklist_first; lp != (LITEM *)NULL; lp = next)
	{
		free (lp->l_name);

		next = lp->l_next;

		free (lp);
	}

	local_linklist_first = (LITEM *)NULL;
	local_linklist_last  = (LITEM *)NULL;

}	/* end delete_local_link_list */

/*
 ****************************************************************
 *	Remo��o local						*
 ****************************************************************
 */
void
delete_local_file (const char *file_nm)
{
	STAT		s;

	if (lstat (file_nm, &s) < 0)
	{
		msg ("*N�o consegui obter o estado do arquivo em \"%s\"", local_node_nm);
		return;
	}

	if (S_ISDIR (s.st_mode))
	{
		if (rmdir (file_nm) < 0)
			msg ("*N�o consegui remover o diret�rio em \"%s\"", local_node_nm);
	}
	else
	{
		if (unlink (file_nm) < 0)
			msg ("*N�o consegui remover o arquivo em \"%s\"", local_node_nm);
	}

}	/* end delete_local_file */

/*
 ****************************************************************
 *	Link local						*
 ****************************************************************
 */
void
link_local_file (const char *file_nm, const char *link_nm)
{
	if (verdir (file_nm) < 0)
	{
		msg ("N�o consegui criar os diret�rios intermedi�rios do arquivo em \"%s\"", local_node_nm);
		return;
	}

	if (link (link_nm, file_nm) < 0)
	{
		msg ("*N�o consegui criar o elo f�sico \"%s\"", local_node_nm);
		return;
	}

}	/* end link_local_file */

/*
 ****************************************************************
 *	Remo��o remota						*
 ****************************************************************
 */
void
delete_remote_file (const char *file_nm)
{
	char		*rmsg;

	t_snd_msg (R_RM, file_nm);

	if (t_rcv_msg (&rmsg) < 0)
	{
		msg ("N�o consegui remover o arquivo em \"%s\"", remote_node_nm);
		msg (rmsg);
		return;
	}

}	/* end delete_remote_file */

/*
 ****************************************************************
 *	Link remoto						*
 ****************************************************************
 */
void
link_remote_file (const char *file_nm, const char *link_nm)
{
	char		*rmsg;

	t_snd_msg_no_push (R_LINK, file_nm);
	t_snd_msg (R_LINK, link_nm);

	if (t_rcv_msg (&rmsg) < 0)
	{
		msg ("*N�o consegui criar o elo f�sico \"%s\"", remote_node_nm);
		msg (rmsg);
		return;
	}

}	/* end link_remote_file */
