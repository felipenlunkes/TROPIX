.bp 1
.he 'SUBST (cmd)'TROPIX: Manual de Refer�ncia'SUBST (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "subst -"
Busca/substitui cadeias em v�rios arquivos
.br

.in
.sp
.b SINTAXE
.in 5
subst [-fsvN] [-d <c>] -p <ab>[:<cd>] ... [<arquivo> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "subst" realiza uma s�rie de buscas e/ou substitui��es
de cadeias de caracteres em um ou mais <arquivo>s.

.sp
Cada busca/substitui��o � definida por uma op��o "-p"
(ver abaixo). Podem ser dadas v�rias destas op��es.
� importante notar que as cadeias de busca/substitui��o N�O s�o
express�es regulares tais como utilizadas no comando "grep" (cmd),
mas apenas seq��ncias de caracteres que s�o procuradas/substitu�das
(literalmente como dadas) nos <arquivo>s.

.sp
O comando lista todas as linhas onde encontrou uma (ou mais) cadeia(s)
de busca, precedidas do nome do <arquivo> e do n�mero da linha
(veja a op��o "-s").
Se tiver sido dada uma cadeia de substitui��o,
a linha ser� impressa ap�s feita a substitui��o.
Uma linha pode ser impressa mais de uma vez, se contiver mais de uma
cadeia de busca.

.sp
As op��es do comando s�o:
.in 8
.ip "-f" 7
Atualiza��o sem consulta.
Normalmente, o usu�rio � consultado para confirmar a atualiza��o dos <arquivo>s
modificados; com esta op��o, os <arquivo>s s�o atualizados sem consulta.

.ip "-s" 7
Modo silencioso.
Imprime apenas o nome de cada arquivo, ao inv�s de
listar as linhas onde foram encontradas as cadeias de busca.

.ip "-v" 7
Verboso.

.ip "-N" 7
L� os nomes dos <arquivo>s da entrada padr�o.
Esta op��o � impl�cita se n�o forem nomes de <arquivo>s.

.ip "-d <c>" 7
Delimitador.
Normalmente o caractere de delimita��o entre as cadeias
da op��o "-p" � o ":" (dois pontos).
Se for usada esta op��o, o delimitador usado passa a ser o caractere <c>.

.ip "-p <ab>[:<cd>]" 7
.sp
Cadeia de busca/substitui��o.
Cada op��o "-p" define uma opera��o a ser feita nos <arquivo>s.

.sp
Opera��o de busca: 
Se a op��o for da forma "-p <ab>", s�o listadas todas as linhas
que cont�m a cadeia <ab>.

.sp
Opera��o de substitui��o:
Se a op��o for da forma "-p <ab>:<cd>", s�o modificadas todas as
linhas que cont�m a cadeia <ab>, substituindo-a por <cd>.

.sp
No caso particular de <cd> ser vazia (mas conservando-se o ":"),
todas as ocorr�ncias da cadeia <ab> s�o eliminadas.

.ep
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
grep, walk
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
