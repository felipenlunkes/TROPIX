.bp
.he 'CMPOBJ (cmd)'TROPIX: Manual de Refer�ncia'CMPOBJ (cmd)'
.fo 'Atualizado em 23.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "cmpobj -"
compara pares de m�dulos objeto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cmpobj [-q] <m�dulo1> <m�dulo2>
cmpobj [-q] <m�dulo1> [<m�dulo2> ...] <diret�rio>
cmpobj [-q] [-N] <diret�rio>
.)l


.lp
.in
.b DESCRI��O
.in 5
O programa "cmpobj" � uma complementa��o de "cmp" (cmd), para m�dulos objeto.
Ele compara independentemente as diversas se��es dos m�dulos objeto, 
indicando as diferen�as (se houver).

.sp
Em sua primeira forma, o comando "cmpobj" compara <m�dulo1> com
<m�dulo2>.

.sp
Na segunda forma, compara um ou mais <m�dulo>s com
os respectivos m�dulos hom�nimos do <diret�rio> especificado.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes
dos <m�dulo>s, que s�o lidos da entrada padr�o, um por linha.

.sp
O programa "cmpobj" obedece �s conven��es da fun��o "modecolor",
consultando a vari�vel MODECOLOR do ambiente para obter
as cores dos nomes dos arquivos e das mensagens
de erro (veja "modecolor" (libc)).

.sp
As op��es do comando s�o:

.in +3
.ip -q
Compara��o r�pida: Se os tamanhos totais dos <m�dulo>s e
as datas contidas nos cabe�alhos forem iguais, os <m�dulo>s
s�o considerados iguais.
Esta compara��o � muito mais r�pida, e a probabilidade de indicar
uma igualdade falsa � extremamente baixa.

.ip -N
L� os nomes dos <m�dulo>s da entrada padr�o 
(usado para a terceira forma).
Esta op��o � impl�cita se for dado apenas o nome do <diret�rio>.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
modecolor
.br
.wo "(cmd): "
cmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
