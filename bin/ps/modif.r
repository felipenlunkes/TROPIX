.bp
.he 'PS (cmd)'TROPIX: Manual de Modifica��es'PS (cmd)'
.fo 'Atualizado em 10.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "ps -"
informa sobre o estado dos processos
.br

.in
.sp 2
.ip "01.12.87  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "07.11.88  2.1.0" 20
Foi consertado o problema do usu�rio n�o superusu�rio
do programa "ps" poder listar e at� cancelar (!) programas
de outros usu�rios.

.sp
A malha pela tabela de processos � agora terminada pelo indicador
"lastproc", n�o necessitando de percorrer a tabela toda.

.ip "09.04.90  2.3.0" 20
Foi feita uma revis�o geral. Ajustado o tamanho d� �rea de leitura
da UPROC do SWAP.

.ip "23.02.91  2.3.1" 20
Foi incorporado na tabela o nome dos "pseudo-terminais".

.ip "06.04.91  2.3.2" 20
Foi feita uma fun��o de leitura de disco "raw" com "count" e "offset"
gen�ricos.

.ip "14.10.91  2.3.3" 20
Foi introduzida a op��o "-lll" para imprimir uma lista de tamanhos.

.sp
A tabela de terminais agora est� ordenada.

.sp
A op��o "-k" envia agora SIGTERM, e  "-kk" SIGKILL.

.ip "20.10.91  2.3.4" 20
Foi generalizado o "ps" para funcionar tamb�m com o TROPIX.

.ip "20.05.96  3.0.0" 20
Foi introduzida a op��o "-llll" para imprimir informa��o sobre SIGALARM.

.ip "27.06.97  3.0.1" 20
Pequena revis�o. Atualizado o "ttyc00" para "t00".

.ip "05.07.98  3.0.2" 20
Desmembrado o tempo em tempo de usu�rio e tempo do sistema.

.ip "16.07.98  3.1.0" 20
Consertado a malha sem fim com nomes de terminais inexistentes.

.ip "24.07.98  3.1.1" 20
Foi introduzida a op��o "-lllll" para imprimir informa��o sobre a STACK do KERNEL.

.ip "09.08.01  4.0.0" 20
Usando "readdir".

.ip "10.08.04  4.6.0" 20
Adaptado para "uproc" apenas.
