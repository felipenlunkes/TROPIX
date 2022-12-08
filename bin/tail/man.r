.bp
.he 'TAIL (cmd)'TROPIX: Manual de Refer�ncia'TAIL (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "tail -"
obt�m a parte final de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
tail [-b <n>[lbc]] [-f] [<arquivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "tail" copia a parte final do <arquivo> dado para a sa�da
padr�o, a partir do local designado.
Se o nome do <arquivo> n�o for dado, ser� lida a entrada padr�o.

.sp
A c�pia come�a normalmente na d�cima linha antes do final do arquivo
(isto �, s�o copiadas as suas �ltimas 10 linhas); veja a op��o "-b".

.sp
As op��es do comando s�o:

.in +3
.ip -b
Inicia a c�pia a <n> linhas ("l"), blocos de 512 bytes ("b") ou
caracteres ("c") antes do final do <arquivo>.

.ip -f
Ap�s copiar a parte final do <arquivo>, entra em uma malha sem fim
tentando, a cada segundo, copiar linhas adicionais do <arquivo>.
Esta op��o s� pode ser usada se o nome do <arquivo> for dado.

.sp
Esta op��o � �til para monitorar o crescimento de um arquivo no qual
um outro processo est� escrevendo.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O comando "tail" trabalha com uma �rea interna de tamanho limitado,
e s�o copiados um m�ximo de 4096 bytes, independente do valor de <n>.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
dd
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
