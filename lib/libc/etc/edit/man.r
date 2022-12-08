.bp 1
.he 'EDIT (libc)'TROPIX: Manual de Refer�ncia'EDIT (libc)'
.fo 'Atualizado em 13.09.99'Vers�o 3.2.2'Pag. %'

.b NOME
.in 5
edit - edi��o interativa de uma cadeia de caracteres

.in
.sp
.b SINTAXE
.in 5
.(l
int edit (const char *prompt, const char *old, char *new)
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "edit" permite a edi��o visual 
de uma cadeia de caracteres
atrav�s de um subconjunto dos comandos
do editor visual de textos "vi".

.sp
A cadeia dada pelo argumento "prompt"
� utilizada como uma mensagem que precede
a cadeia em edi��o no terminal e pode ser usada
para indicar que est� ocorrendo uma edi��o da cadeia a seguir.

.sp
O argumento "old" aponta para a cadeia dada, que ir� ser editada.
Esta edi��o � realizada em uma c�pia da cadeia, de tal modo
que a cadeia dada n�o � alterada.

.sp
A cadeia resultante da edi��o
� armazenada na �rea apontada pelo argumento "new"
(que se sup�e conter o tamanho necess�rio).

.in
.sp
.b
INTERA��O COM O USU�RIO
.r
.in 5
A rotina "edit" inicia a opera��o
mostrando a cadeia em edi��o no terminal ap�s
a cadeia de "prompt". 
O cursor � colocado sobre
o primeiro caractere da cadeia, que passa a ser
o caractere corrente.

.sp
Os comandos s�o formados por um ou dois caracteres.
Estes caracteres n�o s�o ecoados,
mas o efeito do comando � percebido instantaneamente
pelo usu�rio atrav�s do movimento do cursor
e/ou da altera��o da cadeia no terminal.

.sp 2
.b
Movimento do caractere corrente:
.r

.sp
Os comandos de movimento fazem o cursor 
se mover sobre a cadeia,
alterando o caractere corrente.
Est�o dispon�veis os seguintes comandos de movimento:

.in 10

.ip 0 11
Coloca o cursor sobre o
primeiro caractere da cadeia.

.ip $ 11
Coloca o cursor sobre o
�ltimo caractere da cadeia.

.ip '<sp>, l ou <seta para a direita>' 11
.sp
Coloca o cursor sobre o
caractere seguinte da cadeia.

.ip '<bs> ou h ou <seta para a esquerda>' 11
.sp
Coloca o cursor sobre o
caractere anterior da cadeia.

.ip 'w' 11
Coloca o cursor sobre o
primeiro caractere
da pr�xima palavra da cadeia.

.ip "e" 11
Coloca o cursor sobre o
�ltimo caractere
de uma palavra da cadeia.

.ip 'b' 11
Coloca o cursor sobre o
primeiro caractere de uma palavra anterior
da cadeia.

.ep

.in 5
.sp 2
.b
Inser��o de caracteres:
.r
.sp
Os comandos de inser��o permitem acrescentar
novos caracteres � cadeia.
H� dois comandos b�sicos para inser��o de caracteres:
"i" (insert) que insere antes da posi��o do cursor
e "a" (append) que insere ap�s a posi��o do cursor.
Durante a inser��o a cadeia � mantida atualizada no terminal.
Os caracteres <bs> e <del> removem o �ltimo caractere inserido.
O caractere <^U> remove todo o texto inserido.
O caractere <esc> encerra a inser��o.

.sp 2
.b
Operadores:
.r
.sp
Utilizamos operadores para manipular grupos de caracteres cont�guos.
Os operadores s�o usados em conjun��o com os comandos para movimento,
que especificam o escopo da opera��o
(da posi��o do cursor at� o caractere indicado pelo comando de movimento).
Est�o dispon�veis na vers�o atual dois operadores:
"d" (delete) para remo��o e
"c" (change) para substitui��o (remo��o e inser��o).

.sp 2
.b
Outros Comandos:
.r
.sp
Existem alguns outros comandos:

.in 10
.ip "q" 8
O comando "q" (quit) encerra a edi��o da cadeia.

.ip 'r' 8
O comando "r" (replace) substitui o caractere corrente pelo
caractere teclado em seguida.

.ip "U" 8
O comando "U" (undo) retorna a cadeia ao seu estado original.

.ip <^R> 8
O comando <^R> (retype) mostra novamente a cadeia em edi��o.

.ep

.sp 2
.(t
.in 5
.b
Sin�nimos:
.r
.sp
Existem alguns sin�nimos usando apenas um caractere
para os comandos utilizados com maior frequ�ncia e que
requerem dois caracteres para serem executados.
A tabela abaixo relaciona todos estes sin�nimos
e seus respectivos significados:

.sp
.nf
	+----------+-----------+------------------------------+
	| Comando  | Sin�nimo  |        Significado           |
	+----------+-----------+------------------------------+
	|   $a     |    A      | adiciona no final da linha   |
	+----------+-----------+------------------------------+
	|   c$     |    C      | muda at� o final da linha    |
	+----------+-----------+------------------------------+
	|   d$     |    D      | apaga at� o final da linha   |
	+----------+-----------+------------------------------+
	|   0i     |    I      | insere no in�cio da linha    |
	+----------+-----------+------------------------------+
	|   dl     |    x      | apaga o carac. do cursor     |
	+----------+-----------+------------------------------+
	|   dh     |    X      | apaga o carac. antes do cur. |
	+----------+-----------+------------------------------+
	|   cl     |    s      | substitui a partir do cursor |
	+----------+-----------+------------------------------+
	|    q     |   <cr>    | termina a edi��o             |
	+----------+-----------+------------------------------+

.fi
.)t

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a rotina devolve 0 (zero).
Em caso de erro, a rotina devolve -1 (menos um).

.in
.sp
.b DIAGN�STICOS
.in 5
As seguintes situa��es causam erro:
incapacidade para adquirir mem�ria via "malloc" (libc) e
entrada padr�o e/ou saida padr�o n�o s�o terminais.

.in
.sp
.b OBSERVA��ES
.in 5
A rotina "edit" espera que o terminal
tenha capacidade de executar as fun��es
normalmente associadas aos caracteres <bs>, <ht>, <cr> e <nl>
quando estes forem enviados.
A rotina "edit" tamb�m sup�e que o terminal
apaga o caractere sobre o cursor antes de escrever
um novo caractere enviado.

.sp
Nesta vers�o da fun��o, os caracteres de contr�le descritos acima,
<bs>, <del>, <^U> e <^R> s�o fixos, isto �,
n�o podem ser mudados atrav�s de um "ioctl" (ver "termio" (fmt)),
ou atrav�s do comando "stty" (cmd).

.sp
A cadeia em edi��o pode ter at� 255 caracteres.

.sp
A rotina "edit" trabalha com a linha do terminal em modo "raw" e sem "echo".

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi
.br
.wo "(sys): "
ioctl
.)t

.in
.sp
.(t
.b EXEMPLO
.in 7
char	line[256], newline[256];
.sp
.in 14
.wo '. . .'
.in 7
.sp
if (edit ("Editando: ", line, newline) == 0)
.in 14
.br
{	/* Ok */
}
.in 7
.br
else
.in 14
.br
{	/* Erro */	}
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
