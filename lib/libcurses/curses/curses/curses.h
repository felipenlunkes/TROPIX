/*
 ****************************************************************
 *								*
 *			curses.h				*
 *								*
 *	Declara��es para o uso de "curses"			*
 *								*
 *	Vers�o 2.0.0, de 10.05.88				*
 *	       3.0.1, de 30.04.97				*
 *								*
 *	M�dulo: curses.h					*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1997 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#define	H_CURSES	/* Para declarar as fun��es */

/*
 ******	Valores retornados pela maioria das fun��es *************
 */
#define	OK	1
#define	ERR	0

/*
 ******	Valores retornados por "wgetch" *************************
 */
#define	EOL		0x91		/* Fim de linha */
#define	EOT		0x90		/* Fim de arquivo */

#define	KEY_END		0x0100		/* End */
#define	KEY_HOME	0x0101		/* Home */
#define	KEY_DOWN	0x0102		/* Desce */
#define	KEY_UP		0x0103		/* Sobe */
#define	KEY_LEFT	0x0104		/* Esquerda */
#define	KEY_RIGHT	0x0105		/* Direita */
#define	KEY_NPAGE	0x0106		/* Pr�x. P�gina */
#define	KEY_PPAGE	0x0107		/* P�gina Anterior */

#define	KEY_F0		0x0200		/* F0 */
#define	KEY_F1		0x0201		/* F1 */
#define	KEY_F2		0x0202		/* F2 */
#define	KEY_F3		0x0203		/* F3 */
#define	KEY_F4		0x0204		/* F4 */
#define	KEY_F5		0x0205		/* F5 */
#define	KEY_F6		0x0206		/* F6 */
#define	KEY_F7		0x0207		/* F7 */
#define	KEY_F8		0x0208		/* F8 */
#define	KEY_F9		0x0209		/* F9 */

/*
 ******	Tipo de cada caractere **********************************
 */
typedef	unsigned short	chtype;

#define	A_CHARTEXT	0x00FF		/* M�scara para o caractere */
#define	A_ATTRIBUTES	0xFF00		/* M�scara para atributos */

/*
 ******	Atributos ********************************************************
 */
#define	A_NORMAL	0x0000
#define	A_STANDOUT	0x0100
#define	A_REVERSE	0x0200
#define	A_BOLD		0x0400
#define	A_DIM		0x0800
#define	A_BLINK		0x1000
#define	A_UNDERLINE	0x2000
#define	A_ALTCHARSET	0x4000

/*
 ******	Caracteres semi gr�ficos ********************************
 */
extern chtype	ACS_ULCORNER,
		ACS_LLCORNER,
		ACS_URCORNER,
		ACS_LRCORNER,
		ACS_RTEE,
		ACS_LTEE,
		ACS_BTEE,
		ACS_TTEE,
		ACS_HLINE,
		ACS_VLINE,
		ACS_PLUS,
		ACS_S1,
		ACS_S9,
		ACS_DIAMOND,
		ACS_CKBOARD,
		ACS_DEGREE,
		ACS_PLMINUS,
		ACS_BULLET,
		ACS_LARROW,
		ACS_RARROW,
		ACS_DARROW,
		ACS_UARROW,
		ACS_BOARD,
		ACS_LANTERN,
		ACS_BLOCK;

/*
 ******	Caracteres de Controle (veja "getctlch" e "setctlch") ***
 */
#define	C_INTR		1	/* Interrup��o */
#define	C_QUIT		2	/* Quit */
#define	C_SWITCH	3	/* */
#define	C_ERASE		4	/* */
#define	C_AERASE	5	/* */
#define	C_WORD		6	/* */
#define	C_KILL		7	/* */
#define	C_RETYPE	8	/* */
#define	C_EOF		9	/* */

/*
 ******	Estrutura "WINDOW" **************************************
 */
typedef	struct	_window	WINDOW;

struct	_window
{
	char	*w_term;	/* Terminal desta janela */

	short	w_curc,		/* Coluna Corrente */
		w_curl;		/* Linha Corrente */

	short	w_minx,		/* Abcissa M�nima no Terminal */
		w_maxc,		/* Coluna M�xima */
		w_miny,		/* Ordenada M�nima no Terminal */
		w_maxl;		/* Linha M�xima */

	chtype	**w_text;	/* Conte�do da Janela */

	char	*w_changed;	/* Vetor de Altera��es */
	short	w_newlines;	/* Novas linhas */

	chtype	w_attr;		/* Atributos Correntes */

	WINDOW	*w_queue;	/* Fila de Prioridade de Visibilidade */

	char	*w_inqueue;	/* Espa�o para contexto da entrada */

	short	w_displine;	/* Linha onde houve deslocamento */
	short	w_dispcount;	/* Contagem do deslocamento */

	void	(*w_move) (int, int); /* Rotina para move */
	long	w_res;		/* Reservado para uso futuro */

	long	w_flags;	/* Veja abaixo */

};

#define	WINDOWSZ	sizeof (WINDOW)
#define	NOWINDOW	(WINDOW *) 0

/*
 ******	Controle interno das janelas ****************************
 */
#define	W_MASK		0xFFFFFFF0
#define	W_NOTHING	0x00000000	/* */
#define	W_SUBWIN	0x00000001	/* Esta � uma Sub-Window */
#define	W_BOX		0x00000002	/* Esta Janela tem um Contorno */
#define	W_WIDE		0x00000004	/* Cobre horizontalmente o v�deo */
#define	W_TOP		0x00000008	/* Totalmente vis�vel */

/*
 ******	Modo de escrita: "waddset" ******************************
 */
#define A_MASK		0xFFFFFF0F
#define	A_WRAP		0x00000010	/* Continua��o na linha seguinte */
#define	A_SCROLL	0x00000020	/* Rolamento Habilitado */
#define	A_PAGE		0x00000040	/* Pagina��o */
#define	A_REAL		0x00000080	/* Mantendo carac. de controle */

/*
 ******	Modo de entrada: "wgetset" ******************************
 */
#define	G_MASK		0xF0FF00FF
#define	G_ECHO		0x00000100	/* Eco na janela correspondente */
#define	G_INSERT	0x00000200	/* Inser��o */
#define	G_EDIT		0x00000400	/* Edi��o por Linha */
#define	G_TOISO		0x00000800	/* Gera��o de caracteres acentuados */
#define	G_TONL		0x00001000	/* Convers�o de <cr> em <nl> */
#define	G_KEYPAD	0x00002000	/* Reconhecimento de teclas especiais */
#define	G_NODELAY	0x00004000	/* Entrada n�o bloqueada */
#define G_ADDNL		0x00008000	/* N�o inserir <nl> */
#define	G_SIGRET	0x01000000	/* Retorna ERR quando a leitura
						� interrompida */
#define	G_IGXONXOFF	0x02000000	/* Ignora caracteres XON e XOFF */

/*
 ******	Modo de atualiza��o do v�deo: "wrefset" *****************
 */
#define	R_MASK		0xFF00FFFF
#define	R_CLEAR		0x00010000	/* Limpe o V�deo no pr�ximo refresh */
#define	R_CURSOR	0x00020000	/* Atualizar Cursor posi��o corrente */
#define	R_INVIS		0x00040000	/* Cursor invis�vel durante atualiz. */
#define	R_WATCH		0x00080000	/* Observa��o do Teclado */
#define	R_FORCE		0x00100000	/* For�a Posicionamento do Cursor */
#define	R_HOLD		0x00200000	/* Aguarde pedido de entrada */
#define	R_INPUT		0x00400000	/* Atualize a janela na entrada */
#define	R_MOVE		0x00800000	/* Executa rotina programada se o cursor
						n�o est� no v�deo */
/*
 ****** Vari�veis externas **************************************
 */
extern	int	LINES;		/* No. Total de Linhas no V�deo */
extern	int	COLS;		/* No. Total de Colunas no V�deo */
extern	WINDOW	*stdwin;	/* Janela Padr�o */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern	int	newterm (const char *, FILE *, FILE *);
extern	int	setterm (int);

extern	int	incurses (const char *);
extern	void	outcurses (void);

extern	WINDOW	*newwin (int, int, int, int);
extern	void	delwin (WINDOW *);

extern	void	touchwin (WINDOW *);
extern	void	untouchwin (WINDOW *);
extern	void	mvwin (WINDOW *, int, int);

extern	int	wbox (WINDOW *, const char *, int, int);
extern	void	wclrbox (WINDOW *);

extern	int	wmove (WINDOW *, int, int);
extern	int	waddch (WINDOW *, chtype);
extern	int	waddstr (WINDOW *, const char *);
extern	int	winsch (WINDOW *, chtype);
extern	int	winsstr (WINDOW *, const char *);
extern	void	winsertln (WINDOW *);
extern	void	wdelch (WINDOW *);
extern	void	wdeleteln (WINDOW *);
extern	void	wscroll (WINDOW *, int);
extern	void	wclrtoeol (WINDOW *);
extern	void	wclrtobot (WINDOW *);
extern	void	werase (WINDOW *);
extern	void	wrefresh (WINDOW *);

extern	int	wgetch (WINDOW *);
extern	int	wgetstr (WINDOW *, char *);

extern	int	wscanw (WINDOW *, const char *, ...);
extern	int	scanw (const char *, ...);
extern	int	wprintw (WINDOW *, const char *, ...);
extern	int	printw (const char *, ...);

extern	void	beep (void);

extern	int	getctlch (int);
extern	void	setctlch (int, int);

extern	void	setswitch (void (*) (int, ...));
extern	void	setmove (WINDOW *, void (*) ());

/*
 ******	Macros **************************************************
 */
#define	wgetyx(w,y,x)	(y) = (w)->w_curl, (x) = (w)->w_curc
#define	winch(w)	(w)->w_text[(w)->w_curl][(w)->w_curc]

/*
 ******	Modo de Escrita *****************************************
 */
#ifdef	_W_ERR_TST

#define	waddset(w,a)	((a) & A_MASK) ? ERR : ((w)->w_flags &= A_MASK), \
						((w)->w_flags |= (a)), OK
#define	waddon(w,a)	((a) & A_MASK) ? ERR : ((w)->w_flags |= (a)), OK
#define	waddoff(w,a)	((a) & A_MASK) ? ERR : ((w)->w_flags &= ~(a)), OK

#else

#define	waddset(w,a)	((w)->w_flags &= A_MASK), ((w)->w_flags |= (a))
#define	waddon(w,a)	((w)->w_flags |= (a))
#define	waddoff(w,a)	((w)->w_flags &= ~(a))

#endif	_W_ERR_TST

/*
 ******	Modo de Entrada *****************************************
 */
#ifdef	_W_ERR_TST

#define	wgetset(w,a)	((a) & G_MASK) ? ERR : ((w)->w_flags &= G_MASK), \
						((w)->w_flags |= (a)), OK
#define	wgeton(w,a)	((a) & G_MASK) ? ERR : ((w)->w_flags |= (a)), OK
#define	wgetoff(w,a)	((a) & G_MASK) ? ERR : ((w)->w_flags &= ~(a)), OK

#else

#define	wgetset(w,a)	((w)->w_flags &= G_MASK), ((w)->w_flags |= (a))
#define	wgeton(w,a)	((w)->w_flags |= (a))
#define	wgetoff(w,a)	((w)->w_flags &= ~(a))

#endif	_W_ERR_TST

/*
 ******	Modo de Atualiza��o *************************************
 */
#ifdef	_W_ERR_TST

#define	wrefset(w,a)	((a) & R_MASK) ? ERR : ((w)->w_flags &= R_MASK), \
						((w)->w_flags |= (a)), OK
#define	wrefon(w,a)	((a) & R_MASK) ? ERR : ((w)->w_flags |= (a)), OK
#define	wrefoff(w,a)	((a) & R_MASK) ? ERR : ((w)->w_flags &= ~(a)), OK

#else

#define	wrefset(w,a)	((w)->w_flags &= R_MASK), ((w)->w_flags |= (a))
#define	wrefon(w,a)	((w)->w_flags |= (a))
#define	wrefoff(w,a)	((w)->w_flags &= ~(a))

#endif	_W_ERR_TST

/*
 ******	Atributos Correntes *************************************
 */
#define	wattrset(w,a)	(w)->w_attr = (a)
#define	wattron(w,a)	(w)->w_attr |= (a)
#define	wattroff(w,a)	(w)->w_attr &= ~(a)

#define	wclear(w)	{	wrefon (w, R_CLEAR);		\
				werase (w);			\
			} 

/*
 ******	Fun��es precedidas por "move" ***************************
 */
#define	mvaddch(y, x, c)	move ((y), (x)), waddch (stdwin, (c))
#define mvaddstr(y, x, s)	move ((y), (x)), waddstr (stdwin, (s))
#define	mvinsch(y, x, c)	move ((y), (x)), winsch (stdwin, (c))
#define mvinsstr(y, x, s)	move ((y), (x)), winsstr (stdwin, (s))
#define	mvinsertln(s, y)	move ((y), (0)), winsertln (stdwin, (s))
#define	mvdelch(y, x, c)	move ((y), (x)), wdelch (stdwin, (c))
#define	mvdeleteln(y)		move ((y), (0)), wdeleteln (stdwin)

#define	mvgetch(y, x, c)	move ((y), (x)), wgetch (stdwin, (c))
#define mvgetstr(y, x, s)	move ((y), (x)), wgetstr (stdwin, (s))
#define	mvinch(y, x, c)		move ((y), (x)), winch (stdwin, (c))

#define	mvwaddch(w, y, x, c)	wmove ((w), (y), (x)), waddch ((w), (c))
#define mvwaddstr(w, y, x, s)	wmove ((w), (y), (x)), waddstr ((w), (s))
#define	mvwinsch(w, y, x, c)	wmove ((w), (y), (x)), winsch ((w), (c))
#define mvwinsstr(w, y, x, s)	wmove ((w), (y), (x)), winsstr ((w), (s))
#define	mvwinsertln(w, s, y)	wmove ((w), (y), (0)), winsertln ((w), (s))
#define	mvwdelch(w, y, x, c)	wmove ((w), (y), (x)), wdelch ((w), (c))
#define	mvwdeleteln(w, y)	wmove ((w), (y), (0)), wdeleteln (w)

#define	mvwgetch(w, y, x, c)	wmove ((w), (y), (x)), wgetch ((w), (c))
#define mvwgetstr(w, y, x, s)	wmove ((w), (y), (x)), wgetstr ((w), (s))

#define mvwinch (w, y, x)	wmove ((w), (y), (x)), winch (w)

/*
 ******	Fun��es para a janela padr�o ****************************
 */
#define	addch(c)	waddch (stdwin, c)
#define addstr(s)	waddstr (stdwin, s)

#define	insch(c)	winsch (stdwin, (c))
#define	insstr(s)	winsstr (stdwin, (s))
#define	insertln(s)	winsertln (stdwin, (s))

#define	delch(c)	wdelch (stdwin, (c))
#define	deleteln()	wdeleteln (stdwin)

#define	clear()		wclear (stdwin)
#define	clrtobot()	wclrtobot (stdwin)
#define	clrtoeol()	wclrtoeol (stdwin)
#define	erase()		werase (stdwin)

#define	getyx(y,x)	wgetyx (stdwin, y, x)
#define	getch()		wgetch (stdwin)
#define	getstr()	wgetstr (stdwin, str)
#define	inch()		winch (stdwin)

#define	move(y, x)	wmove (stdwin, (y), (x))
#define	refresh()	wrefresh (stdwin)
#define	scroll(n)	wscroll (stdwin, (n))

#define	addset(a)	waddset (stdwin, (a))
#define	addon(a)	waddon (stdwin, (a))
#define	addoff(a)	waddoff (stdwin, (a))

#define	attrset(a)	wattrset (stdwin, a)
#define	attron(a)	wattron (stdwin, a)
#define	attroff(a)	wattroff (stdwin, a)

#define	getset(a)	wgetset (stdwin, (a))
#define	geton(a)	wgeton (stdwin, (a))
#define	getoff(a)	wgetoff (stdwin, (a))

#define	refset(a)	wrefset (stdwin, (a))
#define	refon(a)	wrefon (stdwin, (a))
#define	refoff(a)	wrefoff (stdwin, (a))
