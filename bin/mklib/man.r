.bp
.he 'MKLIB (cmd)'TROPIX: Manual de Refer�ncia'MKLIB (cmd)'
.fo 'Atualizado em 21.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
mklib - cria/atualiza bibliotecas de m�dulos objeto

.in
.sp
.b SINTAXE
.in 5
.(l
mklib [-rudtkfv] [-cm] [<biblioteca>] [<m�dulo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "mklib" � um utilit�rio de cria��o/manuten��o de bibliotecas de
m�dulos objeto, como por exemplo a "libc" - biblioteca de fun��es b�sicas
usadas por programas escritos na linguagem "C".

.sp
No sistema operacional TROPIX, uma biblioteca consiste de uma �rvore
de m�dulos objeto, em que a raiz cont�m o "arquivo de sinopse" da
biblioteca. Este arquivo, que � de texto, cont�m os nomes dos m�dulos
da biblioteca, com os respectivos s�mbolos externos definidos.
Isto � necess�rio para o bom funcionamento do  "link-editor" "ld" (cmd)
- mais detalhes s�o dados nas OBSERVA��ES abaixo e em "lib" (fmt").

.sp
Sem op��es, o comando "mklib" espera como argumento somente o nome
da <biblioteca> (que � identificada pelo diret�rio raiz da �rvore),
e constr�i o arquivo de sinopse a partir dos m�dulos presentes na
�rvore. Uma poss�vel sinopse antiga � removida.

.sp
As op��es do comando s�o:

.in +3
.ip -r
Substitui ou inclui os <m�dulo>s da/na <biblioteca>, atualizando o arquivo
de sinopse. Os nomes dos <m�dulo>s devem ser dados relativos � raiz
da <biblioteca>, mas os <m�dulo>s propriamente ditos
devem estar no diret�rio corrente.

.sp
Por exemplo, para substituir/incluir o m�dulo "/lib/libc/etc/ftw.o"
da biblioteca "/lib/libc" deve ser dado o comando

.sp
.nf
			mklib -r /lib/libc etc/ftw.o
.fi

.sp
mas o m�dulo "ftw.o" deve estar no diret�rio corrente.

.ip -u
Esta op��o � semelhante � "-r", mas ao inv�s de dar uma lista de
m�dulos, as substitui��es s�o feitas a partir de todos os m�dulos do
diret�rio corrente cujos nomes terminam por ".o".

.sp
A substitui��o � realizada apenas se um m�dulo com o mesmo nome
j� se encontra na <biblioteca> (isto �, n�o s�o feitas inclus�es)
e a data de modifica��o do
m�dulo do diret�rio corrente for mais recente. 

.sp
Repare que se a <biblioteca> tiver dois (ou mais) m�dulos hom�nimos
(em subdiret�rios distintos) ser� considerado o primeiro encontrado
no arquivo de sinopse.

.ip -d
Remove da <biblioteca> os <m�dulo>s dados.

.ip -t
Imprime na sa�da padr�o uma tabela dos m�dulos da <biblioteca>,
juntamente com seus s�mbolos.
Se forem dados nomes de <m�dulo>s, s� s�o impressas informa��es sobre eles.
Em conjunto com a op��o "-v",
produz uma listagem mais detalhada de cada m�dulo.

.ip -k
Realiza uma verifica��o de consist�ncia do arquivo de sinopse da <biblioteca>.
Se hover alguma inconsist�ncia, � necess�rio recriar a sinopse
(usando "mklib" sem op��es).

.ip -f
Normalmente o usu�rio � consultado para confirmar cada
atualiza��o ou remo��o a ser feita. Com a op��o "-f" estas opera��es
s�o feitas sem consulta.

.ip -v
Descreve detalhes das opera��es realizadas.
No caso da op��o "-t", s�o impressas mais informa��es sobre os m�dulos.

.ip -c
Esta op��o � uma abrevia��o para a <biblioteca> "/lib/libc".

.ip -m
Esta op��o � uma abrevia��o para a <biblioteca> "/lib/libm".

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
O arquivo de sinopse tem o nome de ".LIBSYM". Assim, por exemplo,
a sinopse da biblioteca "/lib/libc" � "/lib/libc/.LIBSYM".

.sp
Embora o comando "mklib" n�o exija que os nomes dos m�dulos
terminem em ".o" (exceto com a op��o "-u"), � recomend�vel que
isto seja o caso, por quest�es de intera��o com outros comandos.

.sp
Os m�dulos objeto podem ficar distribu�dos livremente pela �rvore
da biblioteca. Nesta vers�o do sistema, n�o h� mais limites no n�mero
de subdiret�rios (altura da �rvore) nem nos tamanhos dos m�dulos/s�mbolos.

.bc	/*************************************/
H� no entanto, uma limita��o da altura da �rvore,
imposta pelo tamanho do caminho do m�dulo (relativo � biblioteca),
que � (nesta vers�o) de 29 caracteres. Assim, por exemplo, o m�dulo
da "libc" "/lib/libc/etc/ftw.o" � permitido, pois "etc/ftw.o" tem 9
caracteres, mas "/lib/libc/alpha/beta/gamma/delta/etc/ftw.o" n�o �,
pois "alpha/beta/gamma/delta/etc/ftw.o" tem 32 caracteres.
.ec	/*************************************/

.sp
M�dulos cujo caminho cont�m um componente que come�a por "." n�o
s�o considerados por "mklib" (tal como "/lib/libc/.old/ftw.o" ou
"/lib/libc/old/.ftw.o"). Esta caracter�stica pode ser usada
para "tornar invis�veis" m�dulos provis�rios ou antigos.

.sp
O comando "mklib" mant�m ordenado o arquivo de sinopse. Isto �
importante para que o comando "ld" crie os m�dulos execut�veis
com os m�dulos sempre na mesma ordem, independentemente se
m�dulos foram inseridos, removidos ou substitu�dos na biblioteca.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ld
.br
.wo "(fmt): "
lib
.br

.in
.sp
.b ARQUIVOS
.in 5
<biblioteca>/.LIBSYM

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
