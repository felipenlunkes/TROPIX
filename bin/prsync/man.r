.bp
.he 'PRSYNC (cmd)'TROPIX: Manual de Refer�ncia'PRSYNC (cmd)'
.fo 'Atualizado em 26.10.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "prsync -"
imprime o estado da sincroniza��o dos processos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
prsync [<pid> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "prsync" imprime informa��es sobre o sincronismo dos
diversos processos. Se forem dados <pid>s de processos, somente
ser�o dadas informa��es sobre estes processos; em caso contr�rio
ser�o dadas informa��es sobre todos processos.

.sp
As informa��es dadas s�o as seguintes:

.in +3
.ip PID 10
Identifica��o do processo.

.ip TIPO 10
Tipo do sem�foro pelo qual o processo est� esperando:
SLEEP: recurso �nico; SEMA: recursos m�ltiplos; EVENT: ocorr�ncia de um
evento; (em branco): o processo n�o est� esperando por nenhum
sem�foro (isto �, est� sendo executado ou pronto para executar).

.ip ENDERE�O  10
Endere�o do sem�foro (em hexadecimal).

.ip MAX 10
N�mero m�ximo de recursos j� alocados simultaneamente pelo processo.

.ip TABELA 10
Nome da tabela e n�mero da entrada contendo o sem�foro.

.ip ENTRADA 10
Nome simb�lico do sem�foro. Se este nome n�o puder ser obtido,
� dado o deslocamento do sem�foro dentro da entrada da tabela.

.ip CMD 10
Comando em execu��o referente ao processo, com os respectivos argumentos.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ps
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
