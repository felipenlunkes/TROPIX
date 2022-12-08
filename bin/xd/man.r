.bp 1
.he 'XD (cmd)'TROPIX: Manual de Refer�ncia'XD (cmd)'
.fo 'escrito em 02.04.02 'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
xd - realiza um "dump" em hexadecimal e ISO (ASCII)

.in
.sp
.b SINTAXE
.in 5
xd [-e] [-s <start>] [-a <ender>] [<arquivo>]

.in
.sp
.b DESCRI��O
.in 5
O comando "xd" realiza um "dump" em hexadecimal e em ISO (ASCII)
de <arquivo>. Se <arquivo> n�o for dado, ser� feito o "dump" da entrada padr�o.

.sp
A listagem produzida cont�m 3 colunas: no lado esquerdo o endere�o
inicial da linha (em hexadecimal), no meio o conte�do (tamb�m em hexadecimal),
e do lado direito o mesmo conte�do em ISO.
Se um caractere n�o tiver representa��o gr�fica, ele � substitu�do
por um ponto (".") na coluna da direita.

.sp
Normalmente, o "dump" � feito do in�cio at� o final do arquivo.

.sp
O comando possui as seguintes op��es:

.in +3
.ip -e 12
Esta op��o deve ser usada se se tratar de um arquivo no c�digo EBCDIC.
Os caracteres s�o convertidos de EBCDIC para ISO (apenas) na coluna da direita.

.ip "-s <start>" 12
Pode ser dado para iniciar o "dump" a partir de <start>.
Este n�mero � interpretado normalmente em decimal; no entanto podemos usar
hexadecimal (se o n�mero come�ar com "0x" ou "0X"),
ou octal (se o n�mero come�ar com "0").

.sp
Al�m disto, o n�mero pode terminar com
"c" ou "C" para especificar multiplica��o por 2048,
"k" ou "K" para especificar multiplica��o por 1024,
"b" ou "B" para especificar multiplica��o por 512,
"l" ou "L" para especificar multiplica��o por 4 e
"w" ou "W" para especificar multiplica��o por 2.

.sp
Lembre-se no entanto, que "b", "B", "c" e "C" s�o tamb�m algarismos hexadecimais!

.ip "-a <ender>" 12
Normalmente, a coluna de endere�os come�a no mesmo endere�o em que foi
pedido o in�cio do "dump".
Com a op��o "-a", a coluna de endere�os come�a de <ender>. 
Este n�mero � interpretado da mesma forma do que <start> (ver acima). 

.ep
.in -3

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
