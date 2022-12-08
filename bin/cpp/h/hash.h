/*
 ****************************************************************
 *								*
 *			   hash.h				*
 *								*
 *	Fun��o de HASH						*
 *								*
 *	Vers�o	1.0.0, de 05.08.88				*
 *		4.1.0, de 23.08.01				*
 *								*
 *	M�dulo:	CPP						*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */


/*
 ****************************************************************
 *	Fun��o de Hash						*
 ****************************************************************
 */
SYMTB *
hash (const char *name, SYMTB ***link_place)
{
	SYMTB		*sp, **hp;
	int		len;

	/*
	 *	Verifica se j� tem lista de colis�o
	 */
	if (name == token.l_name)
		len = token.l_nm_len;
	else
		len = strlen (name);

	hp = &hashtb[strhash (name, len, HASHSZ)];

	if ((sp = *hp) == NOSYMTB)
		{ *link_place = hp; return (NOSYMTB); }

	/*
	 *	Percorre a lista de colis�o
	 */
	for (EVER)
	{
		if (streq (sp->s_name, name))
			return (sp);
#ifdef	MK
		ncolision++;
		printf
		(	"HASH: Colis�o de \"%s\" com \"%s\"\n",
			name, sp->s_name
		);
#endif	MK
		if (sp->s_link == NOSYMTB)
			{ *link_place = &sp->s_link; return (NOSYMTB); }

		sp = sp->s_link;
	}

}	/* end hash */
