.bp 1
.he 'DD (cmd)'TROPIX: Manual de Refer�ncia'DD (cmd)'
.fo 'escrito em 14.10.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
dd - copia e converte arquivos

.in
.sp
.b SINTAXE
.in 5
dd [-v] [<argumento>=<valor>] ...

.in
.sp
.b DESCRI��O
.in 5
O comando "dd" copia o arquivo de entrada
para a sa�da especificada, efetuando
poss�veis convers�es.
Por omiss�o, s�o utilizadas a entrada/sa�da padr�o.

.sp
Se o arquivo de sa�da for regular, e N�O for dado o argumento
"seek", ele ser� truncado antes da c�pia.

.sp
Podemos especificar os tamanhos dos blocos de entrada e de sa�da
para blocar/desblocar arquivos e/ou
aproveitar as vantagens das opera��es de
entrada e sa�da em modo f�sico n�o-estruturado ("raw").

.sp
Este comando, ao contr�rio do usual, utiliza uma sintaxe com
palavras chaves, onde s�o dados grupos, contendo cada um
o nome de um argumento, seguido do caracter "=" e do seu respectivo valor.
Estes grupos podem vir em qualquer ordem.

.sp
As op��es do comando s�o:

.in +3
.ip -v
Verboso: escreve uma estat�stica ao final da execu��o,
contendo o n�mero de blocos completamente/parcialmente lidos/escritos.

.ep
.in -3

.sp
Os argumentos s�o as seguintes:

.in +3
.ip 'if=<arq>' 15
Nome do arquivo de entrada (por omiss�o, a entrada padr�o).

.ip 'of=<arq>' 15
Nome do arquivo de sa�da (por omiss�o, a sa�da padr�o).

.ip 'ibs=<n>' 15
Tamanho do bloco de entrada (por omiss�o 4096).

.ip 'obs=<n>' 15
Tamanho do bloco de sa�da (por omiss�o 4096).

.ip 'bs=<n>' 15
Tamanho do bloco de entrada e de sa�da;
este argumento tem prioridade sobre "ibs" e "obs",
e � �til especialmente quando n�o for especificada nenhuma
convers�o, pois n�o ser�o feitas c�pias entra �reas da mem�ria.

.ip 'cbs=<n>' 15
Tamanho da �rea de convers�o.

.ip 'skip=<n>' 15
Pule os <n> blocos iniciais do arquivo de entrada,
antes de iniciar a c�pia.

.ip 'seek=<n>' 15
Inicie a c�pia, no arquivo de sa�da, a partir do bloco <n>
(numera��o come�ando a partir de 0).

.ip 'count=<n>' 15
Copie apenas <n> blocos da entrada.

.ip 'conv=ascii' 15
Converta o c�digo EBCDIC para ASCII.

.in +5
.ip 'ebcdic' 10
Converta o c�digo ASCII para EBCDIC.

.ip 'ibm' 10
Convers�o, um pouco diferente, de ASCII para EBCDIC.

.ip 'lcase' 10
Converta letras mai�sculas em min�sculas.

.ip 'ucase' 10
Converta letras min�sculas em mai�sculas.

.ip 'swab0' 10
Inverta bytes consecutivos
(converte "abcd" em "badc").

.ip 'swab1' 10
Inverta pares de bytes consecutivos
(converte "abcd" em "cdab").

.ip 'swab2' 10
Realize, para pares de bytes consecutivos, swab0 e swab1 simultaneamente
(converte "abcd" em "dcba").

.ip 'noerror' 10
N�o interrompa o programa se ocorrer algum erro.

.ip 'sync' 10
Complete todo bloco de entrada para o tamanho "ibs".

.ip '..., ...' 10
V�rias op��es de convers�o podem ser separadas por v�rgula.

.in -5
.in -3
.ep

.sp 2
Quando for especificado um n�mero (valor <n>), normalmente espera-se
um valor decimal; no entanto podemos usar
hexadecimal (se o n�mero come�ar com "0x" ou "0X"),
ou octal (se o n�mero come�ar com "0").
Al�m disto, o n�mero pode terminar com
"c" ou "C" para especificar multiplica��o por 2048,
"k" ou "K" para especificar multiplica��o por 1024,
"b" ou "B" para especificar multiplica��o por 512,
"l" ou "L" para especificar multiplica��o por 4 e
"w" ou "W" para especificar multiplica��o por 2.
Lembre-se no entanto, que "b" e "B" s�o tamb�m algarismos hexadecimais!

.sp
O argumento "cbs=<n>" (�rea de convers�o) � usado apenas se for especificada
uma convers�o "ascii", "ebcdic", ou "ibm".
No primeiro caso, s�o colocados "n" bytes na �rea de convers�o
(convertidos para ASCII),
os brancos mais � direita s�o suprimidos, e um caractere <nl> � adicionado
antes de escrever o bloco na sa�da.
Nos outros dois casos, o procedimento � o inverso:
� lida uma linha do arquivo de entrada ASCII
(delimitada por um <nl>) na �rea de convers�o
(convertida para EBCDIC), e a �rea � completada com brancos.

.sp
Ao final, escreve uma estat�stica (veja a op��o "-v", acima).

.in
.sp
.b
OBSERVA��O
.r
.in 5
A convers�o "ibm" � uma variante da convers�o ASCII para EBCDIC,
que apesar de n�o corresponder exatamente ao padr�o, adapta-se
melhor aos casos usuais.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
(cmd): cp, tr

.in
.sp
.b EXEMPLOS
.in 7
.sp
dd if=arq1 of=arq2 conv=ucase
.sp
.in +3
Copia "arq1" para "arq2" convertendo as letras min�sculas para mai�sculas.
.sp 2

.in -3
dd if=/dev/rmt0 of=arq ibs=800 cbs=80 conv=ascii,swab0
.sp
.in +3
A unidade de fita cont�m um arquivo,
cujos registros l�gicos de 80 bytes em EBCDIC est�o blocados em 800 bytes.
Este arquivo ser� lido, os bytes consecutivos ser�o invertidos
e convertidos para ASCII, os brancos no final de cada registro de 80 bytes
ser�o eliminados, e finalmente ser�o acrescentados <nl>.
O arquivo convertido � escrito em "arq".
.in -3

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
