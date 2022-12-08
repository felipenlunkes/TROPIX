.bp 1
.he 'GETCWD (libc)'TROPIX: Manual de Refer�ncia'GETCWD (libc)'
.fo 'Atualizado em 02.11.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
getcwd - obt�m o nome do diret�rio corrente

.in
.sp
.b SINTAXE
.in 5
.(l
char	*getcwd (char *area, int size);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "getcwd" devolve um ponteiro para uma �rea contendo
o nome completo (caminho) do diret�rio corrente.

.sp
Se "area" for um ponteiro n�o NULO, "getcwd" sup�e que ele aponte
para uma �rea de "size" bytes, e a preenche com o nome do diret�rio corrente.

.sp
Se "area" for um ponteiro NULO, "getcwd" aloca uma �rea de tamanho
"size", utilizando "malloc" (libc), e recai no caso anterior.

.sp
Em ambos casos, o valor de "size" deve ser suficiente para conter o nome do
diret�rio corrente acrescido de um caractere NULO no final.

.in
.sp
.b DIAGN�STICOS
.in 5
A rotina devolve um ponteiro NULO e um c�digo de erro em "errno"
caso n�o consiga alocar mem�ria suficiente ou haja
um erro na leitura dos diret�rios. 

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "getcwd" preenche a �rea de tr�s para frente,
e portanto o ponteiro retornado n�o � o do in�cio da �rea.
Isto significa que se "getcwd" alocou a �rea via "malloc",
este ponteiro N�O pode ser usado para "free" (libc).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chdir
.br
.wo "(libc):"
malloc, free
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
