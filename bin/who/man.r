.bp
.he 'WHO (cmd)'TROPIX: Manual de Refer�ncia'WHO (cmd)'
.fo 'Atualizado em 14.07.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "who -"
informa quem est� no sistema
.br

.in
.sp
.b SINTAXE
.in 5
.(l
who [-i] [<arquivo>]
who am I
who am i
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "who", em sua primeira forma, imprime uma linha para cada usu�rio
corrente do sistema, contendo: o nome do usu�rio,
nome do seu terminal (linha de comunica��es), data/hora quando entrou
em sess�o, estado do terminal e local/telefone onde ele est� localizado.
Se for uma sess�o remota, ao inv�s do local/telefone � indicado o
nome do n� remoto entre parenteses.

.sp
O estado de um terminal indica se ele est� habilitado a receber mensagens
de outros usu�rios ou n�o (veja "to", "write", "mesg" (cmd)).
Um "+" indica que est� habilitado e um "-" indica que n�o est�
(um superusu�rio pode enviar mensagens para qualquer terminal,
habilitado ou n�o).

.sp
Na forma "who am I" (ou "who am i"), imprime apenas uma linha,
referente ao pr�prio usu�rio que est� utilizando o comando.

.sp
Se for dado um <arquivo>, ao inv�s de imprimir informa��es sobre os
usu�rios correntes (obtidas do arquivo "/etc/utmp"), o comando "who" imprime as
informa��es obtidas deste <arquivo> dado. O formato do <arquivo>
deve ser o mesmo de "/etc/utmp" - pode ser dado (por exemplo)
"/usr/adm/wtmp", que cont�m um hist�rico das entradas/sa�das em/de sess�o.

.sp
As op��es do comando s�o:

.in +3
.ip -i
Imprime tamb�m o tempo inativo de cada terminal.
Este tempo cont�m o n�mero de horas e minutos transcorridos desde a
�ltima atividade no terminal. Um ponto (".") indica que houve
atividade durante o �ltimo minuto, e portanto � "corrente".
Se n�o houve atividade nas �ltimas 24 horas, isto � indicado por "OLD".
Esta op��o pode ser usada apenas por superusu�rios.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login, to, write, mesg, rlogin, telnet
.br

.in
.sp
.b ARQUIVOS
.in 5
.(l
/etc/utmp
/etc/initab
/usr/adm/wtmp
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
