/*
 ****************************************************************
 *								*
 *			del.c					*
 *								*
 *	Post Office Protocol - Version 3 (cliente gr�fico)	*
 *								*
 *	Vers�o	4.3.0, de 19.09.02				*
 *		4.4.0, de 25.12.02				*
 *								*
 *	M�dulo: xpop3						*
 *		Utilit�rios especiais				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stat.h>
#include <pwd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <xti.h>

#include "../h/xpop3.h"

/*
 ****************************************************************
 *	Atualiza a caixa postal local				*
 ****************************************************************
 */
void
do_delete (int unused)
{
	MBOX		*mp;
	int		index;
	int		total_del = 0, del = 0;

	/*
	 *	Conta o n�mero de cartas a remover
	 */
	for (index = 0; index < mail_vec_sz; index++)
	{
		mp = mail_vec_tb[index];

		if (mp->m_status != 'N')
			continue;

		if (mp->m_del == DO)
			total_del++;
	}

	if (total_del == 0)
		return;

	draw_percent_percent (0, 100);

	do_XFlush ();

	/*
	 *	Remove-as
	 */
	for (index = 0; index < mail_vec_sz; index++)
	{
		mp = mail_vec_tb[index];

		if (mp->m_status != 'N')
			continue;

		if (mp->m_del != DO)
			continue;

		if (comando (1, "DELE %d", mp->m_no) != OK)
		{
			xerror ("N�o consegui remover a carta %d", mp->m_no);
			continue;
		}

		mp->m_del = DONE;

		/*
		 *	Atualiza a cor da remo��o
		 */
		draw_mail_del_button (mp, mp->m_index - FIRST_LINE);

		/*
		 *	Atualiza a barra de percentagem
		 */
		draw_percent_percent (++del, total_del);

		do_XFlush ();
	}

}	/* end do_delete */

/*
 ****************************************************************
 *	Cancela a remo��o das cartas				*
 ****************************************************************
 */
int
do_reset (void)
{
	if (comando (1, "RSET") != OK)
	{
		xerror ("N�o consegui enviar o comando RSET");
		return (-1);
	}

	return (0);

}	/* end do_reset */
