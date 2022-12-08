.bp
.he 'ECHO (cmd)'TROPIX: Manual de Refer�ncia'ECHO (cmd)'
.fo 'Atualizado em 20.09.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "echo -"
ecoa os argumentos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
echo [-nl1234567] [<argumento> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "echo" escreve os seus <argumento>s na sa�da padr�o.

.sp
Sem op��es, � escrita apenas uma linha, com os <argumento>s
separados por um <sp> e a linha terminada por um <nl>.

.sp
Se for dada a op��o "-n", n�o � escrito o <nl> no final da linha.

.sp
Se for dada a op��o "-l", os <argumento>s s�o escritos na forma de um por linha.

.sp
Se for dada uma das op��es "-1", "-2", "-3", "-4", "-5", "-6" ou "-7"
escreve a linha com a cor de n�mero dado (veja a tabela de cores em "modecolor" (libc)).

.sp
O comando "echo" � �til para produzir diagn�sticos em arquivos de comandos
para o "sh" (cmd), e tamb�m para enviar dados conhecidos para um "pipe".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
sh
.br
.wo "(libc): "
modecolor
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
