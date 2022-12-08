.bp
.he 'ASSERT (libc)'TROPIX: Manual de Refer�ncia'ASSERT (libc)'
.fo 'Atualizado em 08.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "assert -"
verifica o valor de uma express�o e emite diagn�stico
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <assert.h>

void	assert (int expr);
.)l

.in
.sp
.b DESCRI��O
.in 5
A macro "assert" insere testes e mensagens de diagn�sticos no programa para
certificar-se de que o valor de uma express�o � n�o-NULO.
Durante a execu��o, se "expr" for falsa (isto �, seu valor for ZERO),
a macro "assert" imprime uma mensagem de erro da forma

.sp
.(l
	Assertiva falsa: "expr", arquivo "t.c", linha 6
.)l

.sp
onde "expr" � o pr�prio texto da express�o sendo testada,
"t.c" � o nome do arquivo e "6" o n�mero da linha onde
ocorreu o erro.
Em seguida, "assert" chama a fun��o "abort" (libc).

.sp
Se a macro "NDEBUG" estiver definida no programa antes
da inclus�o de <assert.h>, as chamadas de "assert" n�o ser�o expandidas.
Isto � �til para retirar os testes e mensagens de um programa
j� depurado. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
abort
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
