.bp
.he 'INITAB (fmt)'TROPIX: Manual de Refer�ncia'INITAB (fmt)'
.fo 'Atualizado em 15.07.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "initab -"
tabela de inicializa��o do sistema
.br

.in
.sp
.b DESCRI��O
.in 5
A tabela "initab" � utilizada pelo processo de inicializa��o
"init" (cmd), durante a carga do sistema, para obter informa��o
sobre quais terminais (linhas de comunica��es) devem ser ativados.

.sp
A tabela reside no arquivo "/etc/initab", e pode ser editada
diretamente pelo administrador do sistema atrav�s de "ed" (cmd)
ou "vi" (cmd). A tabela consiste de uma linha para cada terminal;
cada linha � composta de 4 campos separados por ":":

.sp
.nf
			c:ttyn:tipo:local
.fi

.sp
O primeiro campo deve consistir de um �nico caractere, que
deve ser um asterisco ("*") para indicar um terminal ativo, e um branco
para inativo.

.sp
O segundo campo d� o nome do terminal: apenas o �ltimo componente
do caminho (isto �, "tty009" se o nome completo for "/dev/tty009").

.sp
O terceiro campo d� o tipo do terminal.
Este tipo pode ser da forma "term" ou "term,stty,...".
O primeiro item ("term") � inserido no ambiente (fmt) como valor
da vari�vel "TERM". Os demais itens "stty,..." s�o similares
aos argumentos do comando "stty" (cmd): nesta vers�o do sistema
s�o aceitos os itens "iso", "ascii", "user1", "user2", "clocal",
"-clocal" e as velocidades (por exemplo "9.6").

.sp
O quarto campo d� o local onde se encontra o terminal - este campo
n�o � examinado pelo utilit�rio "init" - a sua utiliza��o
se d� pelo utilit�rio "who" (cmd) para informar a localiza��o do terminal.

.sp
O comando "init" reconhece tamb�m uma linha especial da forma

.sp
.nf
			c:PRINT_CHILD_STATUS
.fi
.sp
que indica se devem ou n�o serem impressas mensagens de erro sobre
processos filhos de "init" com termina��o anormal.
As mensagens s�o impressas se o caractere "c" for "*".

.in
.sp
.b OBSERVA��O
.in 5 
A tabela de inicializa��o do sistema N�O cont�m linhas para os pseudo terminais.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ed, vi, who, init, stty
.br
.wo "(libc):"
getinitnam
.br
.wo "(fmt): "
environ
.br

.in
.sp
.(t
.b ARQUIVOS
.in 5
/etc/initab
.)t

.in
.sp
.(t
.b EXEMPLOS
.sp
.nf
	*:console:ebc4020,user1:Laborat�rio Digital (232)
	 :tty005:vt100,iso:Sala E 1035              (298)
	*:tty009:tda,ascii:Sala U 3569              (365)
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
