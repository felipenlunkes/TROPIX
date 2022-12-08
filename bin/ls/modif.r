.bp
.he 'LS (CMD)'TROPIX: Manual de Modifica��es'LS (CMD)'
.fo 'Atualizado em 26.04.07'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "ls -"
lista caracter�sticas de arquivos e diret�rios
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "22.06.87  1.0.1" 20
Foi adaptado para mostrar os 8 novos bites do modo.
Agora s�o tamb�m mostrados os bites "m" (mant�m o texto na mem�ria),
e os provis�riamente chamados de 1, 2, 3, 4, 5, 6 e 7, mas ainda
com funcionalidade indefinida. Para tanto a op��o "-l" foi alterada,
assim como foi criada a op��o "-L". Agora a op��o "-l" mostra apenas
os bites de prote��o dos arquivos listados. A nova op��o "-L" mostra
al�m da prote��o os bites do modo dos arquivos listados.

.in
.sp 2
.ip "01.01.88  1.1.0" 20
VERS�O CORRENTE

.ip "25.02.90  2.3.0" 20
Foi realizada uma revis�o global, e inserindo a nova op��o "-R".

.ip "17.09.90  2.3.1" 20
Ordena os diret�rios alfabeticamente (na op��o "-R").

.ip "13.12.93  3.0.0" 20
Usando agora as chamadas "inopen" e "instat".

.sp
Usando "strerror" ao inv�s de "perror".

.ip "03.03.95  3.0.1" 20
Adapta��o para o PC

.ip "22.05.97  3.0.2" 20
Mais uma revis�o.

.ip "10.02.99  3.1.7" 20
Inseridas as cores.

.ip "07.08.01  4.0.0" 20
Usando "readdir".

.ip "17.04.02  4.2.0" 20
Adicionados os elos simb�licos e as cores brilhantes.

.ip "06.09.02  4.3.0" 20
Colocado o c�lculo da largura dos campos, para ficar mais estreito.

.ip "27.03.03  4.4.0" 20
Consertado o problema do "-N".

.ip "02.10.03  4.5.0" 20
Usando a compara��o FOLD.

.ip "18.10.03" 20
Desfeito o c�lculo da largura dos campos.

.ip "18.09.05  4.8.0" 20
Recolocado o c�lculo da largura dos campos, para ficar mais estreito
(que indecis�o!).

.ip "26.04.07  4.9.0" 20
O Tamanho agora � impresso como "sem sinal".
