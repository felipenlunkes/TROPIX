.bp
.he 'CMPTREE (cmd)'TROPIX: Manual de Modifica��es'CMPTREE (cmd)'
.fo 'Atualizado em 28.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "cmptree -"
compara �rvores
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

.ip "09.07.87  1.0.2" 20
O percurso da �rvore, originariamente em largura, passou a ser
em profundidade, sendo criada a op��o "-b", para uma poss�vel escolha
do modo de busca anterior.
.ip "" 20
O erro que havia ao copiar a �rvore "/" foi corrigido.
.ip "" 20
Foi alterado o n�mero de bits do modo do arquivo, passando para 24.
.sp

.in
.sp 2
.ip "01.01.88  1.1" 20
VERS�O CORRENTE
.sp

.ip "04.03.88  1.1.1" 20
As sub�rvores da �rvore origem, cujo diret�rio raiz n�o existir
na �rvore destino e n�o for criado durante a execu��o (op��es "-u" e "-i"), 
n�o ser�o mais percorridas.
.sp

.ip "09.06.88  1.1.2" 20
O erro que havia ao copiar a �rvore "/"
para um diret�rio da pr�pria �rvore "/" foi corrigido.
.sp
Foi alterado o funcionamento para detectar quando
uma sub�rvore fonte � a raiz da �rvore destino.

.ip "24.11.89  2.3.0" 20
O programa sofreu (ou deliciou-se) com uma revis�o global.

.ip "28.01.90  2.3.1" 20
Foi consertado o detalhe da compara��o do diret�rio ".". 

.ip "19.11.91  2.3.2" 20
Quando fonte e destino s�o vazios, estava se esquecendo de fechar os arquivos.

.sp
Foi consertado o erro de compara��o de m�dulos-objeto
com cabe�alhos inv�lidos.

.ip "21.11.92  3.0.0" 20
Agora usando a chamada ao sistema "mkdir".

.ip "17.12.93  3.0.1" 20
Agora usando a chamada "inopen" e "ftw" nova. A op��o "-b" foi substitu�da
pela "-L".

.ip "02.02.96  3.0.2" 20
Revis�o para o PC. Introduzido o "garfield".

.ip "03.06.96  3.0.3" 20
Trocada a op��o "-i" por "-f".

.ip "14.04.97  3.0.4" 20
Introduzida a lista para atualizar as datas dos diret�rios no final.

.ip "03.05.97  3.0.5" 20
Corrigido o erro na gera��o dos nomes destino.

.ip "04.08.97  3.0.6" 20
Introduzido a op��o "-P".

.ip "10.01.99  3.1.0" 20
Atualizado para a nova vers�o de "askyesno".

.ip "24.01.00  3.2.3" 20
Introduzida a tabela de compara��o de m�dulos objetos.

.ip "29.03.00  ....." 20
Feita uma revis�o no c�digo de retorno.

.ip "05.08.01  4.0.0" 20
Acrescentada a possibilidade da remo��o do arquivo fonte quando o destino n�o existe.

.ip "26.04.02  4.2.0" 20
Acrescentados os elos simb�licos.

.ip "06.06.02  4.3.0" 20
Acrescentada a compara��o das tabelas de refer�ncias externas.

.ip "28.10.03  4.5.0" 20
Acrescentada a op��o "-d".
