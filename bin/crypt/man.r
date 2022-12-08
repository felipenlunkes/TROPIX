.bp
.he 'CRYPT (man)'TROPIX: Manual de Refer�ncia'CRYPT (man)'
.fo 'Atualizado em 20.04.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "crypt -"
codifica/decodifica arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
crypt [-c] [<entrada> [<sa�da>]]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "crypt" l� o arquivo <entrada>, codifica-o/decodifica-o
de acordo com certa transforma��o,
e coloca a vers�o transformada no arquivo <sa�da>.

.sp
Se <sa�da> n�o for dada, a vers�o transformada � escrita na sa�da padr�o.
Se al�m disto, a <entrada> n�o for dada, o arquivo original
� lido da entrada padr�o.

.sp
A transforma��o � determinada por uma <chave> e uma <complexidade>.
A chave � sempre pedida pelo terminal. A <complexidade> � normalmente
48, a n�o ser que seja dada a op��o "-c", quando ent�o o seu valor
� tamb�m pedido pelo terminal.

.sp
A transforma��o que codifica um certo arquivo � a mesma que o ir�
decodificar posteriormente; a seq��ncia de comandos

.sp
.(l
		crypt original transformado
		crypt transformado
.)l
.sp
ir� escrever o arquivo "original" no terminal (desde naturalmente,
que a mesma <chave> seja dada para os dois comandos).

.in
.sp
.b OBSERVA��ES
.in 5
Quanto maior a <complexidade>, maior ser� o tempo necess�rio para
a transforma��o, o que ir� dificultar a decodifica��o por pessoas
n�o autorizadas.

.sp
Para maior seguran�a, n�o utilize <chave>s com menos de 5 caracteres.

.sp
Se dois ou mais arquivos codificados com a mesma chave forem
concatenados, e este resultado for decodificado, apenas o primeiro
arquivo ser� decodificado corretamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
getpass
.br

.in
.sp
.b
REFER�NCIA
.r
.in 5
Reeds, J.A. & Weinberger, P.J., "File Security and the
Unix System Crypt Command", AT&T Bell Laboratories
Technical Journal, Vol. 63, No. 8, Out. 1984.

.in
.sp
.b ARQUIVOS
.in 5
/dev/tty

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
