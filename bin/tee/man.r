.bp
.he 'TEE (cmd)'TROPIX: Manual de Refer�ncia'TEE (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "tee -"
copia a entrada padr�o para
arquivos e a saida padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
tee [-ai] [<arquivo> ...]
.)l

.in
.sp
.b DESCRICAO
.in 5
O comando "tee"  copia a entrada padr�o para os diversos <arquivo>s
dados e a saida padr�o.

.sp
As op��es do comando s�o:

.in +3
.ip -a
Adiciona o conte�do da entrada padr�o ao final dos <arquivo>s
ao inv�s de reescreve-los.

.ip -i
Ignora interrup��es.

.in -3
.ep
.sp

.in
.sp
.b EXEMPLOS
.in 7
O comando "tee" � normalmente conectado atrav�s de "pipes",
como no exemplo
.sp
.nf
		grep include *.c | tee inc_file 
.fi
.sp
Para examinar-se um "pipe" interno, podemos usar o arquivo "/dev/tty":
.sp
.nf
	walk -p "*.c" . | tee /dev/tty | grep -N include >inc_file
.fi

.in
.sp
.b OBSERVA��ES
.in 5
Deve-se lembrar que os "pipes" usam �reas de entrada/sa�da ("buffers")
normais (isto �, N�O �reas de linha), e portanto,
a sa�da na tela � feita apenas quando a �rea
� completado (ao inv�s de escrever linha a linha).

.sp
Se n�o for dado nenhum <arquivo>, o comando simplesmente
copia a entrada padr�o na sa�da padr�o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(sys): "
pipe
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
