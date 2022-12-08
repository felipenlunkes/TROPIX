.bp 1
.he 'NLIST (libc)'TROPIX: Manual de Refer�ncia'NLIST (libc)'
.fo 'Atualizado em 22.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
nlist - obt�m entradas da tabela de s�mbolos de um mod. objeto

.in
.lp
.b SINTAXE
.in 5
.(l
#include  <nlist.h>  

int	nlist (const char *mod, NLIST *nl);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "nlist" consulta a tabela de s�mbolos do
m�dulo objeto "mod" e completa as informa��es
do vetor de estruturas NLIST apontado por "nl".

.sp
Para cada estrutura do vetor,
"nlist" preenche o tipo e o valor do s�mbolo dado.
Se o s�mbolo n�o for encontrado na tabela,
o tipo e valor s�o zerados.

.sp
O vetor deve ser terminado por uma estrutura contendo um ponteiro
"n_name" NULO.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Normalmente, a rotina retorna ZERO. Nos seguintes casos, ela
devolve um valor negativo: n�o conseguiu abrir o m�dulo objeto "mod";
"mod" n�o � um m�dulo objeto; "mod" n�o possui a
tabela de s�mbolos. 

.in
.sp
.b OBSERVA��O
.in 5
Para se obter informa��es sobre certos s�mbolos do n�cleo do TROPIX,
pode ser mais eficiente utilizar a chamada ao sistema "kcntl" ou "getscb"
(sys). 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
knctl, getscb
.br
.wo "(cmd): "
nm
.br
.wo "(fmt): "
a.out.h
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
