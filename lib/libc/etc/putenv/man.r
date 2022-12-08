.bp 1
.he 'PUTENV (libc)'TROPIX: Manual de Refer�ncia'PUTENV (libc)'
.fo 'Atualizado em 30.05.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
putenv - modifica ou acrescenta um valor ao ambiente

.in
.sp
.b SINTAXE
.in 5
.(l
int	putenv (const char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "putenv" espera que "str" aponte para uma cadeia da forma
"name=value", e faz com que o valor da vari�vel "name" seja "value",
alterando o valor da vari�vel (caso j� exista) ou criando
uma vari�vel nova.

.sp
Em qualquer caso, a cadeia apontada por "str" ir� fazer parte
do ambiente ("environment"), de tal modo que se a cadeia for alterada, o
ambiente tambem o ser�.

.sp
A �rea utilizada por "str" pode ser liberada quando uma nova cadeia
definindo a mesma vari�vel for dada para "putenv".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso  a fun��o "putenv" retorna ZERO.
Se a cadeia dada n�o estiver no formato correto, ou se a �rea para alocar
ponteiros para as novas vari�veis estiver esgotada, a fun��o retorna -1. 

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "putenv" manipula o ambiente apontado por "environ", e pode ser
utilizada conjuntamente com as fun��o "getenv" e "delenv".
Note, no entanto, que o ambiente apontado por "envp"
(o terceiro argumento do programa que utiliza "putenv")
N�O � modificado.

.sp
 Esta fun��o utiliza "malloc" (ou "realloc") para obter mais espa�o para
os apontadores do ambiente.

.sp
 A fun��o "putenv" n�o p�e as vari�veis em ordem alfab�tica.

.sp
 Aten��o para n�o chamar "putenv" com uma cadeia em uma
�rea autom�tica, que ir� ser liberada quando a fun��o
que chamou "putenv" retornar. 

.sp
 Na presente implementa��o de "putenv", N�O h� limite
no n�mero de cadeias no ambiente.

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (sys):  exec
     (libc): getenv, delenv, malloc
     (fmt):  environ
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
