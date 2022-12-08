/*
 ****************************************************************
 *								*
 *			msg.c					*
 *								*
 *	Defini��o das Mensagens ao Usu�rio			*
 *								*
 *	Vers�o	1.0.0, de 04.11.86				*
 *		3.0.0, de 26.04.97				*
 *								*
 *	Modulo: ED						*
 *		Editores de Texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>

#include "../h/ed.h"
#include "../h/proto.h"
#include "../h/extern.h"

/*
 ******	Mensagens ***********************************************
 */
const char	M_ok[] =	"Ok";
const char	M_nspace[] =	"N�o h� mem�ria para \"%s\"";
const char	M_wrerror[] =	"Erro na escrita";
const char	M_rderror[] =	"Erro na leitura";
const char	M_permission[] = "Permiss�o negada";
const char	M_nfound[] =	"N�o encontrei \"%s\"";
const char	M_directory[] =	"\"%s\" � um diret�rio";
const char	M_iregular[] =	"\"%s\" n�o � um arquivo regular";
const char	M_object[] =	"\"%s\" � um arquivo objeto";
const char	M_empty[] =	"\"%s\" est� vazio";
const char	M_rdonly[] =	"\"%s\" s� tem permiss�o para leitura";
const char	M_exists[] =	"\"%s\" j� existe";
const char	M_saved[] =	"\"%s\" j� est� atualizado";
const char	M_newfile[] =	"\"%s\": arquivo novo";
const char	M_size[] =	"\"%s\": %d linhas, %d caracteres";
