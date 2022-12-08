.bp 1
.he 'CMD (fmt)'TROPIX: Manual de Refer�ncia'CMD (fmt)'
.fo 'Atualizado em 28.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "cmd -"
sintaxe da utiliza��o de comandos

.in
.sp
.b SINTAXE
.in 5
<nome> [-<op��o> ...] [<arg> ...]
.sp
.nf
   onde:
.fi

.ip <nome>: 9
nome do comando.

.ip <op��o>: 9
sempre precedida de '-'.
Uma <op��o> pode ser vir acompanhada de um argumento
(por exemplo "-f new.makefile") ou n�o
(por exemplo "-v").
Estes argumentos das op��es n�o devem ser confundidos
com os argumentos dos comandos.

.ip <arg>: 9
argumento do comando. Estes argumentos n�o t�m sintaxe definida, e
variam de comando para comando.

.ep
.in
.sp
.b DESCRI��O
.in 5
Abaixo � dada a sintaxe da utiliza��o dos comandos. 
Recomendamos que todos os comandos sigam esta sintaxe para 
a homogeneidade do sistema TROPIX.
Na constru��o de novos comandos, a fun��o "getopt" (libc)
pode (e deve) ser utilizada para a verifica��o da sintaxe.

.in +3
.ip 1. 3
As op��es devem constar de apenas um caractere.

.ip 2. 3
Todas as op��es devem ser precedidas de '-'.

.ip 3. 3
Op��es sem argumentos podem ser agrupadas ap�s um �nico '-'.

.ip 4. 3
O primeiro argumento de uma op��o deve vir separado da op��o
por brancos.

.ip 5. 3
Argumentos de op��es n�o podem ser opcionais.

.ip 6. 3
Grupos de argumentos de uma op��o devem vir separados por
virgulas, ou brancos e neste caso, entre aspas
(por ex. -p 114,abdc,alpha ou -p "114 abcd alpha").

.ip 7. 3
A cadeia "--" pode ser usada para indicar o final das op��es.

.ip 8. 3
O caractere '-' precedido e seguido de brancos deve apenas
ser utilizado com o significado de entrada ou sa�da padr�o.

.in -3
.ep
.in
.sp
.b
OBSERVA��O
.r
.in 5
No TROPIX procura-se respeitar ao m�ximo estas regras definidas
pela AT&T. Ironicamente, o sistema onde estas regras s�o muito
pouco respeitadas � no pr�prio UNIX da AT&T.
.br

.(t
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
getopt
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
