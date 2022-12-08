/*
 ****************************************************************
 *								*
 *			zip.c					*
 *								*
 *	Gerenciador de arquivos					*
 *								*
 *	Vers�o	4.5.0, de 24.12.03				*
 *		4.5.0, de 24.12.03				*
 *								*
 *	M�dulo: xfm						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <fcntl.h>

#include <X11/Intrinsic.h>

#include "../h/xfm.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	*dev_nm;

/*
 ******	Dados da janela do ZIP **********************************
 */
const SUBMENU_VEC	zip_vec[] =
{
	"Permite leituras/escritas",				ZIP_RW,
	"Est� protegido para escritas",				ZIP_RO,
	"Est� protegido para escritas com senha", 		ZIP_RO_PASS,
	"Permite leituras/escritas enquanto n�o retirado",	ZIP_RW_Q
};

entry int		zip_in_use = ZIP_RW;	/* padr�es em uso */

entry SUBMENU	zip =
{
	{ NULL },					/* Windata */
	zip_vec,					/* Text vector */

	0,						/* mapped */
	0,						/* line_offset */
	47,						/* strlen ("Todos os arquivos") */
	(sizeof (zip_vec) / sizeof (SUBMENU_VEC)),	/* text_n */
	&zip_in_use,					/* value_in_use */
	-1						/* highlight_line */
};

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		zip_get_passwd (void);
void		zip_change_protection (void);

/*
 ****************************************************************
 *	Verifica se � permitida a remo��o			*
 ****************************************************************
 */
int
permission_zip (const NODE *np)
{
	if (!np->n_mnt_point)
		return (-1);

	return (1);

}	/* end permission_rm */

/*
 ****************************************************************
 *	Processa a prote��o do ZIP				*
 ****************************************************************
 */
void
zip_0 (void)
{
	const MENUDATA	*mp = &menudata[present_menu];
	const WINDATA	*menu_wp = mp->windata;
	const FSTAB	*tp;
	const NODE	*dir_np;
	XWindowChanges	value;
	WINDATA		*wp = &zip.windata;
	int		fd, status;

	/*
	 *	Pr�logo
	 */
	if ((dir_np = mp->menu_node) == NONODE)
		return;

	if ((tp = search_dir_in_fstab (dir_np->n_path)) == NOFSTAB)
		return;

	if ((fd = open (tp->fs_dev_nm, O_RDONLY)) < 0)
		{ draw_error_msg_text ("*N�o consegui abrir \"%s\"", tp->fs_dev_nm); return; }

	if (ioctl (fd, ZIP_IS_ZIP) < 0)
		{ draw_error_msg_text ("O dispositivo \"%s\" N�O � um ZIP", tp->fs_dev_nm); goto bad; }

	if ((status = ioctl (fd, ZIP_GET_PROTECTION)) < 0)
		{ draw_error_msg_text ("*N�o consegui obter a prote��o de \"%s\"", tp->fs_dev_nm); goto bad; }

	switch (status)
	{
	    case 0:
		zip_in_use = ZIP_RW;
		break;

	    case 2:
		zip_in_use = ZIP_RO;
		break;

	    case 3:
		zip_in_use = ZIP_RO_PASS;
		break;

	    case 10:
		zip_in_use = ZIP_RW_Q;
		break;

	    default:
		{ draw_error_msg_text ("Est� com um prote��o inv�lida (%s)", status); goto bad; }
	}

	dev_nm = tp->fs_dev_nm;

	/*
	 *	Prepara o tamanho da janela
	 */
	value.x = wp->x = menu_wp->x + menu_wp->width;
	value.y = wp->y = menu_wp->y + 1 * (wp->font_height + 2 * SHADOW);

	XConfigureWindow (display, wp->win, CWX|CWY, &value);

	XMapRaised (display, wp->win);

	/*
	 *	Ep�logo
	 */
    bad:
	close (fd);


}	/* end zip_0 */

/*
 ****************************************************************
 *	Troca a prote��o					*
 ****************************************************************
 */
void
zip_tst_and_change_protection (void)
{
	int			fd, status;

	/*
	 *	Abre o arquivo
	 */
	if ((fd = open (dev_nm, O_RDONLY)) < 0)
		{ draw_error_msg_text ("*N�o consegui abrir \"%s\"", dev_nm); return; }

	/*
	 *	Obt�m o estado atual de prote��o
	 */
	status = ioctl (fd, ZIP_GET_PROTECTION);

	close (fd);

	if (status < 0)
		{ draw_error_msg_text ("*N�o consegui obter a prote��o de \"%s\"", dev_nm); return; }

	/*
	 *	Verifica se precisa de senha
	 */
	if (status == 3 || zip_in_use == ZIP_RO_PASS)
		zip_get_passwd ();
	else
		zip_change_protection ();

}	/* end zip_tst_and_change_protection */

/*
 ****************************************************************
 *	L� a senha						*
 ****************************************************************
 */
void
zip_get_passwd (void)
{
	const WINDATA	*menu_wp = &zip.windata;
	WINDATA		*wp = &nm_edit;
	KEYDATA		*kp = &keydata;
	int		len = 50;
	XWindowChanges	value;

	/*
	 *	Prepara o tamanho e localiza��o da janela
	 */
	value.width  = wp->width  = 2 * (MENU_BORDER + SHADOW) + len * wp->font_width;
	value.height = wp->height = 2 * (MENU_BORDER + SHADOW) + wp->font_height;

	value.x = menu_wp->x + menu_wp->width;
	value.y = menu_wp->y + menu_wp->height - 3 * (wp->font_height + 2 * SHADOW);

	XConfigureWindow (display, wp->win, CWWidth|CWHeight|CWX|CWY, &value);

	/*
	 *	Prepara a �rea de leitura do nome da senha
	 */
	kp->k_code	 = 'M';
	kp->k_changed	 = 0;
	kp->k_display	 = display;
	kp->k_win	 = wp->win;
	kp->k_gc	 = wp->text_gc;
	kp->k_rev_gc	 = reverse_text_gc;
	kp->k_font_width = wp->font_width;
	kp->k_area	 = edit_area;
	kp->k_count	 = 0;
	kp->k_offset	 = 0;
	kp->k_size	 = sizeof (edit_area);
	kp->k_x		 = MENU_BORDER + SHADOW;
	kp->k_y		 = MENU_BORDER + 1 * (wp->font_height + 2 * SHADOW) - (wp->font_descent + SHADOW);
	kp->k_function	 = zip_change_protection;

	kp->k_area[0] 	 = '\0';

	XMapWindow (display, wp->win);

}	/* end zip_get_passwd */

/*
 ****************************************************************
 *	x			*
 ****************************************************************
 */
void
zip_change_protection (void)
{
	int					fd, status;
	struct	{ int mode; char pwd[80]; }	mode_pwd;

	/*
	 *	Abre o arquivo
	 */
	if ((fd = open (dev_nm, O_RDONLY)) < 0)
		{ draw_error_msg_text ("*N�o consegui abrir \"%s\"", dev_nm); return; }

	/*
	 *	Obt�m o estado atual de prote��o
	 */
	if ((status = ioctl (fd, ZIP_GET_PROTECTION)) < 0)
		{ draw_error_msg_text ("*N�o consegui obter a prote��o de \"%s\"", dev_nm); goto bad; }

	/*
	 *	Verifica se precisa de senha
	 */
	mode_pwd.pwd[0] = '\0';

	if (status == 3 || zip_in_use == ZIP_RO_PASS)
		strcpy (mode_pwd.pwd, edit_area);

	/*
	 *	Atribui o novo estado de prote��o
	 */
	switch (zip_in_use)
	{
	    case ZIP_RO:
		mode_pwd.mode = 2;
		break;

	    case ZIP_RO_PASS:
		mode_pwd.mode = 3;
		break;

	    case ZIP_RW:
	    default:
		mode_pwd.mode = 0;
		break;

	    case ZIP_RW_Q:
		if (status == 0)
		{
			mode_pwd.mode = 2;

			if (ioctl (fd, ZIP_SET_PROTECTION, &mode_pwd) < 0)
			{
				draw_error_msg_text ("*N�o consegui alterar a prote��o de \"%s\"", dev_nm);
				goto bad;
			}

			status = 2;
		}

		if (status != 2)
		{
			draw_error_msg_text ("O disco n�o est� est� protegido para escritas (sem senha)");
			goto bad;
		}

		mode_pwd.mode = 10;
		break;

	}	/* end switch */

	if (ioctl (fd, ZIP_SET_PROTECTION, &mode_pwd) < 0)
		{ draw_error_msg_text ("*N�o consegui alterar a prote��o de \"%s\"", dev_nm); goto bad; }

	if ((status = ioctl (fd, ZIP_GET_PROTECTION)) < 0)
		{ draw_error_msg_text ("*N�o consegui obter a prote��o de \"%s\"", dev_nm); goto bad; }

	if (status != mode_pwd.mode)
		draw_error_msg_text ("N�o consegui alterar a prote��o de \"%s\" (senha inv�lida)", dev_nm);

	/*
	 *	Ep�logo
	 */
    bad:
	close (fd);

}	/* end zip_change_protection */
