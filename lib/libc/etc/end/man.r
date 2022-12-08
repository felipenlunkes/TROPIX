.bp 1
.he 'END (libc)'TROPIX: Manual de Refer�ncia'END (libc)'
.fo 'Atualizado em 20.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Finais do programa:
.sp
.wo "end   -"
final do programa
.br
.wo "etext -"
final do texto
.br
.wo "edata -"
final da �rea de dados
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

extern char	end;
extern char	etext;
extern char	edata;
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas vari�veis possibilitam a um programa saber o endere�o
final (e portanto o tamanho) de cada uma de suas se��es.

.sp
O endere�o de "etext" (e N�O
o seu conte�do) d� o final do texto, o endere�o de "edata"
o final da �rea de dados inicializados,
e o endere�o de "end" o final do programa (que � o final 
da �rea de dados n�o inicializados - "bss").

.in
.sp
.b OBSERVA��ES
.in 5
Repare que em um programa reentrante (compilado ou "link-editado"
com a op��o "-n"), o final do texto n�o coincide com o
come�o da �rea de dados.

.sp
Diversas rotinas de aloca��o de mem�ria (tais como "brk", "sbrk" (sys),
"malloc", "smalloc" (libc), etc...) modificam o final do programa,
desatualizando o valor do endere�o de "end".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cc, ld
.br
.wo "(sys): "
brk
.br
.wo "(libc):"
malloc
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
