.bp
.he 'CURSES (curses)'TROPIX: Manual de Modifica��es'CURSES (curses)'
.fo 'Atualizado em 06.07.89'Vers�o 2.2.1'Pag. %'

.b NOME
.in 5
.wo "Curses -"
Biblioteca para constru��o/manipula��o de janelas em terminais alfanum�ricos.
.br

.in
.sp 2
.ip "01.04.87  2.0.0" 20
VERS�O CORRENTE
.sp

.ip "15.09.88  2.1.1" 20
Nova disposi��o para os fontes.
Os arquivos para inclus�o,
que antes estavam no diret�rio "include"
foram transferidos para o diret�rio "terminfo/h"
e s�o instalados no diret�rio "/usr/include/curses".
Os fontes dos programas "tic" e "tac"
foram colocados no diret�rio de fontes dos comandos.
.sp

.ip "15.09.88  2.1.2" 20
Foram realizadas v�rias modifica��es com o objetivo de reduzir
o tempo de processamento demandado pelas rotinas da biblioteca.
Estas modifica��es envolveram a estrutura "WINDOW"
e portanto implicam na necessidade de recompila��o
de seus aplicativos (como por exemplo: "vi" e "wsdb")
nos m�dulos que incluem o arquivo <curses.h>.

.sp
A partir desta vers�o, a Curses � capaz de utilizar
a capacidade de inserir e remover linhas oferecida pelo
hardware de alguns terminais.

.sp
Foram acrescentadas as seguintes op��es de configura��o para as janelas:
A_REAL, G_SIGRET e R_INPUT.

.sp
Foram acrescentadas as rotinas "getctlch" e "setctlch"
que permitem a um aplicativo obter e/ou alterar os valores
para os caracteres de controle utilizados pelo sistema e pela Curses.

.ip "01.04.87  2.2.0" 20
VERS�O CORRENTE

.ip "06.07.89  2.2.1" 20
A "terminfo" foi alterada para reconhecer todas as vari�veis de descri��o.
.sp
Impacto:
(1) Os programas que utilizam a Curses precisam ser religados.
(2) As novas descri��es de terminais s�o incompat�veis com as anteriores.
(3) Os programas j� religados devem trabalhar com as novas descri��es.
.ep
