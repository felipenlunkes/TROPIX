.bp
.he 'PRDISKTB (cmd)'TROPIX: Manual de Refer�ncia'PRDISKTB (cmd)'
.fo 'Atualizado em 14.04.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "prdisktb -"
Imprime a tabela de discos/parti��es
.br

.in
.sp
.b SINTAXE
.in 5
.(l
prdisktb [-av]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "prdisktb" imprime a tabela de discos/parti��es do
n�cleo do sistema operacional TROPIX.

.sp
Esta tabela � constru�da durante o processo de carga do sistema
("boot") e posteriormente alterada/estendida durante o seu funcionamento.
Ela � de vital import�ncia, pois cont�m a vis�o do
sistema relativos a todos os discos e parti��es presentes.

.sp
Normalmente (isto �, sem a op��o "-a"), "prdisktb" imprime os 
seguintes itens a respeito de cada disco/parti��o:

.in +3
.ip NAME 8
Nome do disco/parti��o.
Se for da forma "fd?", "hd?", "sd?" ou "ramd?" refere-se a um disco
(considerado integralmente).
Se contiver um sufixo de um d�gito e (possivelmente)
uma letra, refere-se a uma parti��o de um disco.

.ip A 8
Cont�m um asterisco se a parti��o for ativa, isto �, se ela � vis�vel
durante o est�gio inicial da etapa de carga dos diversos
sistemas operacionais
("boot0").

.ip OFFSET 8
Deslocamento do come�o da parti��o (em rela��o ao in�cio do disco)
em blocos de 512 bytes.

.ip SIZE 8
Tamanho da parti��o/disco em blocos de 512 bytes.

.ip MB 8
Tamanho da parti��o/disco em MB.

.ip DEV 8
N�mero do dispositivo (Major + Minor), como referenciado dentro do
sistema operacional.

.ip U/T 8
N�mero do controlador + n�mero do dispositivo l�gico.
Estes n�meros s�o utilizados para identificar qual o controlador e/ou
disco.

.ip TYPE 8
Tipo da parti��o, com o c�digo num�rico e simb�lico.

.ep
.in -3

.sp
Com a op��o "-a", "prdisktb" substitui alguns dos itens da lista acima
por:

.in +3
.ip HEAD 8
N�mero de cabe�as, segundo a geometria do disco. Esta n�o �
necessariamente a geometria real do disco, mas sim a geometria usada
pela BIOS do PC e na tabela de parti��es contida no disco.

.ip SECT 8
N�mero de setores por trilha, segundo a geometria do disco.
Veja acima.

.ip CYL 8
N�mero de cilindros, segundo a geometria do disco.
Veja acima.

.ip G/L 8
Indicador da presen�a das extens�es da INT 13 da BIOS.
Um "L" (linear) indica a presen�a das extens�es,
um "G" (geometria) a aus�ncia e um branco significa que
n�o foi poss�vel obter informa��es da BIOS relativas a este disco.

.ip BLSZ 8
Tamanho do bloco do dispositivo.

.ip OPEN 8
N�mero de "open"s desta parti��o/disco.

.ip LOCK 8
Indica se houve um "open" de uso exclusivo nesta parti��o/disco.

.ep
.in -3

.sp
As op��es do comando s�o:

.in +3
.ip -a
Imprime informa��es alternativas (veja acima).

.ip -v
Verboso.

.ep
.in -3

.bc	/*************************************/
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
c
.br
.wo "(sys): "
s
.br
.wo "(libc):"
l
.br
.wo "(xti): "
f
.br
.wo "(fmt): "
f
.br
.ec	/*************************************/

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
