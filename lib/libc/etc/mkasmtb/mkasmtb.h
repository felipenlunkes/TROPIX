/*
 ****************************************************************
 *								*
 *			<mkasmtb.h>				*
 *								*
 *	Estrutura para a gera��o direta de objetos simb�licos	*
 *								*
 *	Vers�o	1.0.0, de 25.04.86				*
 *		3.0.0, de 23.02.95				*
 *								*
 *	M�dulo: mkasmtb.h					*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Modo do m�dulo gerado ***********************************
 */
typedef	enum
{
	RO,		/* Readonly global */
	RW,		/* Read/write global */
	ROL,		/* Readonly local */
	RWL		/* Read/write local */

}	ROW;

/*
 ******	Estrutura para a descri��o de cada entrada **************
 */
typedef	struct
{
	int	o_size;		/* Tamanho do membro */
	int	o_offset;	/* Posi��o do membro na entrada */
	int	o_count;	/* No. de exemplares deste membro */
	char	*o_rel_nm;	/* Nome da vari�vel reloc�vel (NOSTR se abs.) */
	void	*o_rel_addr;	/* Endere�o da vari�vel relocadora */

}	OBJENT;

#define NOOBJENT	(OBJENT *)NULL

/*
 ******	Prot�tipos **********************************************
 */
extern int	mkasmtb (const char *, const char *, const void *, long, ROW, int, const OBJENT *);
