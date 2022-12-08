/*
 ****************************************************************
 *								*
 *			   op_hash.h				*
 *								*
 *	Fun��o de HASH dos operadores				*
 *								*
 *	Vers�o	3.0.0, de 25.02.94				*
 *		3.0.0, de 25.02.94				*
 *								*
 *	Rotinas:						*
 *		op_hash						*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Referencias/defini��es externas				*
 ****************************************************************
 */
entry OPCODE	**op_link_place; /* Ponteiro para encadeamento */

/*
 ****************************************************************
 *	Fun��o de HASH para operadores				*
 ****************************************************************
 */
OPCODE *
op_hash (const char *name)
{
	OPCODE		*op;

	/*
	 *	Verifica se j� tem lista de colis�o
	 */
	op_link_place = &op_hash_tb[strhash (name, strlen (name), op_hash_sz)];
#ifdef	MK
	ncolision = 0;
#endif	MK
	if ((op = *op_link_place) == NOOPCODE)
		return (NOOPCODE);

	/*
	 *	Percorre a lista de colis�o
	 */
	for (EVER)
	{
		if (streq (op->o_name, name))
			return (op);
#ifdef	MK
		ncolision++;
#endif	MK
		if (op->o_link == NOOPCODE)
			{ op_link_place = &op->o_link; return (NOOPCODE); }
		else
			op = op->o_link;
	}

}	/* end op_hash */
