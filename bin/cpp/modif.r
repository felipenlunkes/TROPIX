.bp
.he 'CPP (cmd)'TROPIX: Manual de Modifica��es'CPP (cmd)'
.fo 'Atualizado em 18.09.01'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "cpp -"
pr�processador para fontes em "C"
.br

.in
.sp 2
.ip "01.08.88  2.0.0" 20
VERS�O CORRENTE
.sp

.ip "09.09.88  2.1.0" 20
Foi consertado o problema da expans�o do nome de um arquivo
a ser inclu�do, quando ele cont�m macros.

.ip "04.10.88  2.1.1" 20
Foi alterado o m�dulo "expr.c" para aceitar constru��es do
tipo '#if $arg == "texto"'.

.ip "12.01.89  2.1.2" 20
Foi consertado o problema do "#elif". Alterado "src/parse.c".

.ip "31.01.89  2.1.2" 20
Agora, antes de um argumento ser substitu�do durante a expans�o da
macro, ele � analisado para ver se ele, por sua vez, � uma macro.
Se o for, ele � trocado pelo corpo da macro. Isto s� ocorre em um
n�vel.

.ip "10.04.89  2.1.3" 20
O pr�processador foi alterado para aceitar identificadores de 31 caracteres.
Al�m disto, agora aceita 1024 identificadores, de acordo com o padr�o ANSI.

.ip "12.04.89  2.1.4" 20
Foi modificado o m�dulo "src/pragma.c" para aceitar o "pragma getenv"
na forma "getenv (var1, var2, ...)".

.ip "20.05.89  2.1.5" 20
Foi consertado o �rro do "tipo inv�lido de macro" para macros
j� indefinidas, quando era usado um identificador come�ando por "_".
Alterado "src/expand.c".

.ip "07.09.89  2.1.6" 20
Foi modificada a defini��o de macros para possibilitar a redefini��o
de macros, desde que o texto seja igual (exceto na quantidade de brancos).
Alterado "src/define.c".

.ip "05.10.89  2.3.0" 20
O programa foi (quase) totalmente reescrito.

.ip "09.10.89  2.3.1" 20
Pequena corre��o quando n�o � dado nenhum argumento ("getchar ()").
Alterado "src/expand.c".

.ip "26.10.89  2.3.2" 20
Foi corrigido o erro do parenteses dentro de cadeia normal ("....(....") ou
cadeia literal ('...(...'). Alterado "/src/expand.c".

.ip "28.01.90  2.3.3" 20
Agora, os coment�rios nos finais das diretivas s�o pulados corretamente.
Alterados "cpp.c", "directive.c", "include.c", "pragma.c", "scan.c".

.sp
Macros n�o encontradas no ambiente s�o utilizadas da op��o "-D",
com uma advert�ncia.
Alterado "pragma.c".

.ip "20.09.90  2.3.4" 20
Alterado "expand.c", para retirar os parenteses de "(getc) (fp)".

.sp
Feita uma revis�o, colocando os prot�tipos.

.ip "14.12.90  2.3.5" 20
Foi introduzida a op��o "-T". Alterado "cpp.h", "cpp.c" e "expr.c".

.sp
Foi introduzido a remo��o de coment�rios dentro de argumentos das macros.
Alterado "expand.c".

.sp
Aumentado a �rea alocada para o corpo da macro. 

.ip "02.02.91  2.3.6" 20
O Algoritmo de "hash" dos s�mbolos foi convertido de colis�es internas
para externas, o que remove o limite do n�mero de
s�mbolos que podem ser armazenados.

.sp
Feita uma revis�o em "src/define.c" na parte de macros
definidas/indefinidas por "-D", "-U", "#pragma" e "#define".

.ip "22.02.91  2.3.7" 20
Consertado o esquecimento de verificar o "\" de continua��o de linha
dentro de uma cadeia no corpo de uma macro.
Alterado "define.c".

.ip "15.04.95  3.0.0" 20
Adaptado para o PC.

.ip "13.07.97  3.0.1" 20
Pequena revis�o.

.ip "24.08.01  4.1.0" 20
Retirado o limite do tamanho dos identificadores.

.ip "18.09.01  4.2.0" 20
Inclu�do e ignorado o pragma "pack".
