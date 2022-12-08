.bp
.he 'GAR (cmd)'TROPIX: Manual de Modifica��es'GAR (cmd)'
.fo 'Atualizado em 20.07.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "gar -"
cria/atualiza cole��es de arquivos
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "09.11.87  1.0.2" 20
Foi modificada a numera��o dos volumes: agora come�am de 1
(ao inv�s de 0). Esta modifica��o � apenas externa - internamente,
o formato da cole��o n�o foi modificada, come�ando de 0.
Deste modo n�o foi criado nenhum problema de compatibilidade
de cole��es velhas/novas.
.sp
Ao final de um volume, se o volume de continua��o for no mesmo
dispositivo, n�o � mais necess�rio repetir o seu nome (desde que
n�o seja a entrada/sa�da padr�o).

.ip "12.01.88  1.1.0" 20
Foi elaborado o conceito do "garfield", um arquivo que durante
a compara��o � criado com o nome dos arquivos diferentes.
Durante a extra��o, este arquivo � consultado para extrair
apenas os arquivos diferentes.
.sp
A op��o "-d" passou a significar, durante a escrita de uma
cole��o, para n�o entrar em subdiret�rios. 

.ip "15.01.88  1.1.1" 20
Foi alterado o m�dulo "out.c" para que, no caso interativo,
diret�rios n�o desejados retornarem "1" para "ftw",
de modo a n�o percorrer estes diret�rios.

.ip "15.02.88  1.1.2" 20
Foi feita uma pequena corre��o na leitura das linhas
do arquivo "garfield", que estava sendo lido em uma �rea autom�tica.
Foi alterado o m�dulo "aux.c".

.ip "10.07.88  2.0.0" 20
Foi acrescida a op��o ".". No modo normal, agora, arquivos
come�ando por ponto n�o s�o gravados na cole��o.

.ip "12.07.88  2.0.1" 20
Agora, as cole��es s�o abertas com o indicador de "O_LOCK",
para evitar a escrita simultanea de 2 "gars" no mesmo disquete (por exemplo).

.ip "01.12.88  2.1.0" 20
As partes n�o significativas do cabe�alhos de m�dulos objetos
s�o mascaradas, para simplificar a compara��o de objetos.

.ip "17.05.89  2.2.0" 20
Nas leituras/escritas com erro agora s�o escritas as causas com "perror".
Alterado "aux.c".

.ip "19.08.89  2.3.0" 20
Foi corrigido o reconhecimento de padr�es envolvendo ".." para
que mesmo sem a op��o ".", arquivos do tipo "../a/b" e "a/../b"
sejam inclu�dos. 

.sp
Foi inclu�da o novo modo de opera��o "append" ("-a").

.ip "22.12.89  2.3.1" 20
Em caso de cabe�alho de volume inv�lido ou volume de continua��o,
"gar" permite a busca de um arquivo GAR no meio da cole��o.
Alterados "append.c", "aux.c", "gar.c", "in.c" e "tok.c".

.sp
Foi corrigido detalhe da cria��o de um link para um arquivo
quando este link j� existia. Alterado "in.c". 

.ip "02.01.90  2.3.2" 20
Foi otimizado o programa para pular blocos (rotina "inskip")
rapidamente, atrav�s de "seek" ao inv�s de leitura. 
Com isto, os blocos pulados n�o t�m o CRC checado, e por isto
foi alterada a semantica da op��o "-r".
A blocagem de entrada para "-t" pode ser "1" (mais r�pido).
Opera��es que ficaram bem mais r�pidas: "-t",
"-x" (com garfield, padr�es ou interativo) e "-a".
Alterados "aux.c", "gar.c", "gar.h",  "in.c" e "out.c".

.sp
Foi consertada a tabela, para imprimir o UID num�rico
no caso do UID simb�lico n�o puder ser obtido.
Alterado "in.c".

.sp
Foi consertado o n�mero do volume de continua��o, que estava defasado
de um. Alterado "aux.c".

.sp
A op��o "-." faz com que os diret�rios seja gravados.
Alterado "out.c".

.ip "16.04.90  2.3.3" 20
Foi estendido a fun��o de sa�da ("-o") para gerar tamb�m cole��es
no formato TAR. Modificados todos os m�dulos.

.sp
Foi consertada a se��o de cria��o em "in.c", que emitia mensagens de
erro err�neas para cria��o de diret�rios.

.sp
Foi criada a op��o "-q" para a compara��o r�pida de m�dulos objeto.
Modificado "gar.c" e "in.c".

.ip "28.09.90  2.3.4" 20
Foi feita uma revis�o geral, e introduzida a redu��o (op��es "-C" e "-b").

.sp
Foi consertado o problema da emiss�o do "max_code" justamente quando
o tamanho do c�digo aumentava.

.ip "24.10.90  2.3.5" 20
Introduzida a compara��o com atualiza��o (op��o "-u").

.sp
Foi melhorada a aloca��o do arquivo tempor�rio de compacta��o.
Agora escolhe "/tmp/...", "/usr/tmp/..." e "...".

.ip "21.11.90  2.3.6" 20
Foi resolvido o problema da emiss�o de "max_code" justamente quando
o tamanho do c�digo mudava.

.ip "26.11.90  2.3.7" 20
Foi introduzida a op��o "-S", com a cria��o de cole��es incrementais,
atrav�s de "garstamp". 
Alterados "src/gar.c" e "src/out.c".

.sp
Foi alterado o formato de impress�o de diagn�sticos. Agora os diagn�sticos
vem na linha seguinte � linha contendo o nome do arquivo.
Alterados "src/append.c", "src/aux.c", "src/gar.c", "src/in.c",
"src/out.c" e "src/tok.c".

.ip "13.12.90  2.3.8" 20
Novamente, mais uma v�z foi resolvido o problema da emiss�o de "max_code"
justamente quando o tamanho do c�digo mudava, o que tamb�m n�o foi o caso
na vers�o 2.3.6.
Alterados "src/reduce1.c".

.sp
A �rea de c�digos de redu��o foi passada de "short" para "int".

.ip "14.01.91  2.3.9" 20
Foi acrescentada o teste "bit_sz < MAX_BIT_SZ" para certificar-se de que o
limite n�o � passado.

.ip "12.03.91  2.3.10" 20
Foi acrescentado a busca de arquivos no formato TAR no meio de uma cole��o.
Alterados "src/gar.c" e "src/tok.c".

.ip "19.10.91  2.3.11" 20
Foi eliminada a mensagem de "link esp�rio" quando os nomes s�o iguais
(decorrentes de uma opera��o de "append").

.sp
Foi introduzida a op��o "-M".

.ip "22.03.92  2.3.12" 20
Foram introduzidos os padr�es de exclus�o (op��o "-P").

.ip "20.11.92  3.0.00" 20
Agora usando a chamada ao sistema "mkdir".

.ip "21.07.93  3.1.00" 20
Introduzido o novo m�todo de compress�o, a "defla��o".

.ip "21.07.93  3.1.01" 20
Agora, sub�rvores do tipo ".old/..." nem s�o mais caminhadas.

.ip "07.04.94  3.1.02" 20
Consertado pequeno detalhe de cria��o dos diret�rios (colocado "0777").

.ip "07.04.95  3.1.03" 20
???.

.ip "11.07.95  3.1.04" 20
Extendida a op��o "-g" para a sa�da.

.ip "11.03.97  3.1.05" 20
Agora, os diret�rios s�o sempre inclu�dos na cole��o.

.ip "04.05.97  3.1.06" 20
O comando sofreu (mais) uma revis�o.

.ip "09.05.97  3.1.07" 20
Introduzida a lista para atualizar as datas dos diret�rios no final.

.ip "25.05.97  3.1.08" 20
Agora temos a op��o "-F" para dar o dispositivo.

.ip "03.06.97  3.1.09" 20
Pequena corre��o no formato TAR: este formato processa apenas arquivos
regulares.

.ip "04.08.97  3.1.10" 20
Agora, lendo nomes da entrada padr�o ser�o interpretados como �rvores.

.ip "05.04.98  3.1.11" 20
Foram colocados alguns "close" faltando no m�dulo "out.c".

.ip "17.04.98  3.1.11" 20
Introduzidos os c�digos de dispositivo '-2' e '-3', para o ZIP.

.ip "16.07.98  3.1.12" 20
Consertado o esquecimento da cria��o de arquivos novos para "-F".

.ip "12.01.99  3.1.13" 20
Foi introduzida a nova vers�o de "askyesno".

.ip "08.05.02  4.2.0" 20
Introduzido o elo simb�lico e as cores dos nomes dos arquivos.

.ip "19.03.03  4.4.0" 20
Alterado o cabe�alho dos arquivos para poder comportar os
novos tamanhos (32 bits) do DEV e INO.

.ip "14.10.04  4.6.0" 20
O indicador "-f" agora pode ser usado tamb�m para a sa�da.

.ip "17.07.05  4.8.0" 20
Foi atualizada a vers�o TAR (mas ainda n�o conclu�da).

.ip "20.07.06  4.9.0" 20
A op��o "-d" na sa�da passa a significar "n�o incluir diret�rios".
