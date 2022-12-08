/*
 ****************************************************************
 *								*
 *			xpaint.h				*
 *								*
 *	Defini��es Universais					*
 *								*
 *	Vers�o	3.0.0, de 05.04.98				*
 *		4.4.0, de 17.04.03				*
 *								*
 *	M�dulo: cmd/xpaint					*
 *		X Windows - Clientes				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright (c) 2003 TROPIX Technologies Ltd.	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Algumas abreviaturas �teis				*
 ****************************************************************
 */
#define	EVER	;;
#define	elif	else if

/*
 ****************************************************************
 *	Defini��es de Tipos					*
 ****************************************************************
 */
typedef struct image	IMAGE;
typedef struct format	FORMAT;

#define	NOIMAGE		(IMAGE *)0

/*
 ****** Informa��es sobre Formatos de Imagem ********************
 */
#define	EXTSZ	7

struct format
{
	char		f_extension[EXTSZ + 1];

	int		(*f_test) (FILE *);

	XImage		*(*f_load) (FILE *, int, Display *, XStandardColormap *, IMAGE *);
};

/*
 ****** Informa��es sobre uma Imagem ****************************
 */
struct image
{
	const char	*i_name;		/* Nome do arquivo */
	dev_t		i_dev;			/* (dev, ino) */
	ino_t		i_ino;
	size_t		i_file_sz;		/* Tamanho (em bytes) */

	const FORMAT	*i_format;		/* Formato */

	int		i_factor;		/* Fator de Escala */

	int		i_width,		/* Largura x Altura */
			i_height;

	int		i_ncolors;		/* Nr. efetivo de cores */

	const char	*i_comment;		/* Coment�rio */
};

/*
 ****** Estrutura do Mapa de Cores ******************************
 */
#define	CMAPSZ	256
#define	UNDEF	0xFFFFFFFF

typedef struct
{
	uchar	c_red  [CMAPSZ],
		c_green[CMAPSZ],
		c_blue [CMAPSZ];

	ulong	c_pixel[CMAPSZ];

	ulong	c_size;

	int	c_grayscale;

}	COLORMAP;

/*
 ****************************************************************
 *	Vari�veis Globais					*
 ****************************************************************
 */
extern int		vflag;

extern Display		*display;
extern int		screen;
extern int		depth;

/*
 ****************************************************************
 *	Prot�tipos de Fun��es					*
 ****************************************************************
 */
extern	int	is_a_GIF_file (FILE *);
extern	XImage	*load_GIF_file (FILE *, int, Display *, XStandardColormap *, IMAGE *);

extern	int	is_a_new_GIF_file (FILE *);
extern	XImage	*load_new_GIF_file (FILE *, int, Display *, XStandardColormap *, IMAGE *);

extern	int	is_a_BMP_file (FILE *);
extern	XImage	*load_BMP_file (FILE *, int, Display *, XStandardColormap *, IMAGE *);

extern	int	is_a_XPM_file (FILE *);
extern	XImage	*load_XPM_file (FILE *, int, Display *, XStandardColormap *, IMAGE *);

extern  int     is_a_JPG_file (FILE *);
extern  XImage  *load_JPG_file (FILE *, int, Display *, XStandardColormap *, IMAGE *);

extern	void	msg (const char *, ...);

extern	int	add_pixel (ulong);
extern	int	put_pixel (IMAGE *, XImage *, int, int, ulong);
extern	XImage *alloc_image (Display *, IMAGE *, int, int, int *, int *);
