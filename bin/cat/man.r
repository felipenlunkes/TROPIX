.bp
.he 'CAT (cmd)'TROPIX: Manual de Refer�ncia'CAT (cmd)'
.fo 'Atualizado em 24.08.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
cat - concatena e copia arquivos

.in
.sp
.b SINTAXE
.in 5
cat [-nN] [-o <o>] [<arquivo> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "cat" l� um ou mais <arquivo>s sequencialmente e os escreve
na sa�da padr�o. Assim

.sp
.nf
		cat arq
.fi

.sp
imprime o arquivo, e

.sp
.nf
		cat arq1 arq2 >arq3
.fi

.sp
concatena os arquivos "arq1" e "arq2", colocando o resultado em "arq3".

.sp
Um <arquivo> com nome "-" representa a entrada padr�o.

.sp
As op��es do comando s�o:

.in +5
.ip -n 5
Numera as linhas de sa�da sequencialmente a partir de 1.

.ip -o 5
Insere <o> brancos antes do in�cio de cada linha.
Lembre-se no entanto, de que se <o> n�o for m�ltiplo de 8, as tabula��es
podem se modificar.


.ip -N 5
Os nomes dos arquivos de entrada ser�o lidos da entrada padr�o, um por linha.

.in
.lp
.b OBSERVA��O
.in 5
Cuidado com o uso de comandos com a forma

.sp
.nf
		cat arq1 arq2 >arq1
.fi

.sp
porque o conte�do original do arquivo de entrada "arq1" ser� perdido antes de
ser lido.
Portanto, aten��o com os caracteres especiais de expans�o do "sh" (cmd).

.in
.sp
.b "VEJA TAMB�M"
.in 5
(cmd): cp, pr, sh

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
