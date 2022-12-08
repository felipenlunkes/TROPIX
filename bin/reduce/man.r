.bp
.he 'REDUCE (cmd)'TROPIX: Manual de Refer�ncia'REDUCE (cmd)'
.fo 'Escrito em 16.09.90'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Comprime/expande um arquivo segundo o algoritmo LZW:
.sp
.wo "reduce -"
comprime ou expande, de acordo com as op��es
.br
.wo "rcat   -"
apenas expande
.br

.in
.sp
.b SINTAXE
.in 5
.(l
reduce [-b <n>] [-rfv] <original> [<comprimido>]

reduce -u [-ft] <comprimido> [<original>]

rcat <comprimido> [<original>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "reduce" tenta reduzir o tamanho do arquivo <original>,
armazenando uma forma reduzida no arquivo <comprimido>.
Se o nome do arquivo <original> for "-", ele � lido da entrada
padr�o. Se o nome do arquivo <comprimido> n�o for dado, ele � escrito
na sa�da padr�o.

.sp
Um arquivo <comprimido> pode ser restaurado � sua forma original
atrav�s de "rcat" (ou "reduce" com a op��o "-u").
Se o nome do arquivo <comprimido> for "-", ele � lido da entrada
padr�o. Se o nome do arquivo <original> n�o for dado, ele � escrito
na sa�da padr�o.

.sp
O comando "reduce" usa um algoritmo baseado no m�todo de
"Lempel-Ziv-Welch" (LZW), um processo adaptativo de compress�o de dados.
Subcadeias comuns do arquivo <original> s�o substitu�das inicialmente
por c�digos de 9 bits, a partir de 257. Quando � alcan�ado o c�digo 512,
passa-se para 10 bits, e assim sucessivamente, at� o m�ximo de 16 bits.
Periodicamente, o fator de compress�o � avaliado, e se est� decrescendo,
a tabela de subcadeias � esvaziada, recome�ando a codifica��o a partir
de 9 bits. Isto faz com que "reduce" se adapte a arquivos longos,
em que o estilo (isto �, o repert�rio de subcadeias) varia.

.sp
O fator de compress�o obtido depende do tamanho do arquivo <original>, o
n�mero de bits utilizado na codifica��o, e a distribui��o das
subcadeias comuns.
Para programas fontes, s�o t�picos fatores de compress�o de 50 a 66 \%
(isto �, o arquivo <comprimido> tem da metade � ter�a parte do tamanho do
<original>). Para m�dulos objeto, os fatores de compress�o s�o menores,
situando-se em geral na faixa de 30 a 40 \%.

.sp
A redu��o m�xima de tamanho � obtida com a utiliza��o de c�digos de 16
bits. Para isto, no entanto, � necess�ria uma quantidade apreci�vel de mem�ria
(principalmente durante a compress�o).
A quantidade da mem�ria necess�ria para a tabela de compress�o/expans�o
� uma fun��o exponencial do tamanho m�ximo do c�digo -
cada bit a mais exige o dobro de mem�ria.

.(t
Na tabela abaixo damos o tamanho total necess�rio por "reduce",
para alguns valores de tamanho m�ximo do c�digo: 

.sp
.ts
center
allbox;
c|c|c.
Bits	Compress�o	Expans�o
.t&
c|c|c.
 9	 48 Kb	 52 Kb
13	120 Kb	 84 Kb
14	196 Kb	116 Kb
16	656 Kb	308 Kb
.te
.)t

.sp
Repare que se forem gerados c�digos de 16 bits, existe a possibilidade de n�o
ser poss�vel a opera��o de expans�o em um outro computador com menos mem�ria
dispon�vel (veja a op��o "-b").

.sp
Normalmente, s�o adicionadas informa��es de CRC durante o processo de
compress�o, que s�o verificadas durante a expans�o. Isto oferece
uma garantia bem alta de que o arquivo recuperado durante o processo de
expans�o � de fato id�ntico ao original que foi comprimido (veja a op��o "-r").  

.sp
Existe uma possibilidade de o arquivo <comprimido> ficar maior
do que o <original>. Isto ocorre principalmente com arquivos
pequenos (menores do que 256 bytes). Se isto ocorrer, � emitida uma
mensagem de advert�ncia.

.sp
As op��es do comando s�o:

.in +3
.ip -b
Tamanho m�ximo do c�digo (em bits).
Esta op��o deve ser utilizada apenas na compress�o
(o arquivo <comprimido> j� cont�m o tamanho m�ximo a ser utilizado na expans�o).
Este valor deve ser dado na faixa de 9 a 16 bits
(se for omitido, ser� usado um tamanho m�ximo de 14 bits, que � um bom
compromisso entre o fator de compress�o e a mem�ria necess�ria para arquivos
da 30 Kb ou menores).

.ip -r
Gera o arquivo <comprimido> SEM os CRCs. Com isto,
a velocidade de compress�o/expans�o fica aproximadamente
.wo '20 \%'
maior e o arquivo <comprimido> fica da ordem de
.wo '1 \%'
menor. Por outro lado, a seguran�a proporcionada pelos cheques
de CRCs � perdida.  

.ip -f
Normalmente, o usu�rio � consultado para decidir se um arquivo destino
j� existente deve ser reescrito.
A op��o "-f" suprime esta consulta, recriando o arquivo.

.ip -v
Estat�stica.
Imprime os totais de caracteres processados e o fator de compress�o obtido.

.ip -u
Opera��o de expans�o.

.ip -t
Imprime a tabela de cadeias utilizada.

.ep

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se ocorreu qualquer tipo de erro, o c�digo do "exit" � 1;
se durante uma opera��o de compress�o o arquivo teve o seu
tamanho aumentado, o c�digo do "exit" � 2;
em caso contr�rio, o c�digo do "exit" � 0.

.in
.sp
.bc	/*************************************/
.b OBSERVA��O(��ES)
.ec	/*************************************/
.b OBSERVA��O
.in 5
O arquivo <comprimido> cont�m codificado um indicador de final de arquivo.
Isto significa que ele pode residir tamb�m em arquivos especiais (de blocos
ou caracteres), e ser corretamente recuperado.
Ali�s, como o arquivo <comprimido> cont�m normalmente CRCs, comprimir
um arquivo diretamente para um disquete ou fita magn�tica � um modo
conveniente de armazenamento/transporte de arquivos, como no exemplo abaixo:

.sp
.(t
.nf
		reduce alpha /dev/d5a
		rcat /dev/d5a .....
.fi
.)t
.sp

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
.wo "(fmt): "
f
.br
.ec	/*************************************/

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"A Technique for High Performance Data Compression",
Terry A. Welch, "IEEE Computer,"
vol. 17, no. 6 (June 1984), pp. 8-19.

.bc	/*************************************/
.in
.sp
.b EXEMPLOS
.in 7
.sp 2
e
.ec	/*************************************/

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
