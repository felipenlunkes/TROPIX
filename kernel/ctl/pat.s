|*
|****************************************************************
|*								*
|*			pat.s					*
|*								*
|*	Defini��es do padr�o de interrup��es			*
|*								*
|*	Vers�o	3.0.0, de 05.09.94				*
|*		3.0.0, de 05.09.94				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

|*
|******	Defini��es do padr�o da interrup��o *********************
|*
CHAR		= '*'

SPACE		= { 0 << 8 } | ' '
COLOR		= { 4 << 8 } | CHAR	|* Vermelho
W		= SPACE

.if 0	/*******************************************************/
W		= { 7 << 8 } | CHAR	|* Branco
.endif	/*******************************************************/

INTR_PAT_LEN	= 8			|* Em caracteres na tela
INTR_PAT_LOC	= COL - 20 - INTR_PAT_LEN |* Offset na �ltima linha

INTR_PAT_SZ	= 16			|* Em bytes
INTR_PAT_SHIFT	= 4			|* Log (2) do acima

INTR_VGA_ADDR	= VGA_ADDR + 2 * { LINE * COL + INTR_PAT_LOC }
