.bp
.he 'CPTREE (cmd)'TROPIX: Manual de Modifica��es'CPTREE (cmd)'
.fo 'Atualizado em 21.12.04'Vers�o 4.7.0'Pag. %'

.b NOME
.in 5
.wo "cptree -"
copia uma �rvore
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "13.05.87  1.0.1" 20
O funcionamento  da op��o "-o" foi alterado de modo a
manter tamb�m a data de cria��o dos arquivos.
.sp

.ip "06.07.87  1.0.2" 20
O percurso da �rvore, originariamente em largura, passou a ser
em profundidade, sendo criada a op��o "-b", para uma poss�vel escolha
do modo de busca anterior.
.ip "" 20
O erro que havia ao copiar a �rvore "/" foi corrigido.
.ip "" 20
Passou a ser poss�vel o n�o percurso de uma determinada
sub�rvore atrav�s da op��o "-i", que pedir� a confirma��o tamb�m 
para diret�rios.
.ip "" 20
Foi alterado o n�mero de bits do modo do arquivo, passando para 24.
.sp

.in
.sp 2
.ip "01.01.88  1.1" 20
VERS�O CORRENTE
.sp

.ip "09.06.88  1.1.1" 20
O erro que havia ao copiar a �rvore "/"
para um diret�rio da pr�pria �rvore "/" foi corrigido.

.ip "14.11.89  2.3.0" 20
O programa sofreu (ou deliciou-se) com uma revis�o global.

.ip "28.01.90  2.3.1" 20
Foi consertado o detalhe da c�pia do diret�rio ".". 

.ip "21.11.92  3.0.0" 20
Agora usando a chamada ao sistema "mkdir".

.ip "17.12.93  3.0.1" 20
Agora usando a chamada "inopen" e "ftw" nova. A op��o "-b" foi substitu�da
pela "-L".

.ip "13.04.97  3.0.2" 20
Introduzida a lista para atualizar as datas dos diret�rios no final.

.ip "03.05.97  3.0.3" 20
Corrigido o erro na composi��o dos nomes destino.

.ip "04.08.97  3.0.4" 20
Introduzido a op��o "-P".

.ip "15.01.99  3.1.0" 20
Foi atualizada a chamada � fun��o "askyesno".

.ip "08.01.01  4.0.0" 20
Foi adicionado o modo "de for�a" de "askyesno".

.ip "26.04.02  4.2.0" 20
Adicionado os elos simb�licos.

.ip "22.09.02  4.6.0" 20
Adicionada a op��o "-l".

.ip "21.12.02  4.7.0" 20
Pequena corre��o na op��o "-l".
