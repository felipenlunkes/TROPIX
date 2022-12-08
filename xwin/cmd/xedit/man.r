.bp
.he 'XEDIT (xwin)'TROPIX: Manual de Refer�ncia'XEDIT (xwin)'
.fo 'Atualizado em 14.10.01'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "xedit -"
editor de textos simples para o sistema X-Window
.br

.in
.sp
.b SINTAXE
.in 5
.(l
xedit [<arquivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio gr�fico "xedit" edita o <arquivo> de nome dado.
Se o nome do <arquivo> N�O for dado, ele pode ser dado na se��o
de comandos (veja abaixo).

.sp
As janelas do utilit�rio gr�fico "xedit" cont�m as seguintes informa��es:

.in +3
.ip 1. 3
Se��o de comandos:
um conjunto de comandos com os quais podemos sair de "xedit", salvar o arquivo,
ou ler um novo arquivo para a janela de edi��o. O nome do arquivo deve ser
dado/� mostrado ap�s os comandos.

.ip 2. 3
Janela de mensagens:
cont�m as diversas mensagens de "xedit".
.bc	/*************************************/
Adicionalmente, esta janela pode ser usada como scratch pad.
.ec	/*************************************/

.ip 3. 3
Nome do arquivo:
cont�m o nome do arquivo atualmente sendo editado. Este arquivo pode ser
editado com a permiss�o para leitura e escrita ou somente leitura.

.ip 4. 3
Janela de edi��o:
Cont�m o texto que est� sendo editado ou criado.

.ep
.in -3

.sp
A edi��o do texto � realizada usando as 4 setas ou o "mouse" para movimentar o cursor,
as teclas <del> ou <bs> para apagar o caractere antes do cursor, e as demais
teclas para redigir o texto.

.bc	/*************************************/
.in
.sp
.b COMANDOS
.in 7
Quit
.in 5
Sai da se��o atual do xedit. Se alguma altera��o n�o foi salva, xedit mostra
uma mensagem de alerta, permitindo ao usu�rio salvar o arquivo.
.sp
.in 7
Save
.in 5
Salva o arquivo com o nome que est� na caixa de texto ao lado do bot�o Load.
.sp
.in 7
Load
.in 5
L� o arquivo com o nome que est� na caixa de texto ao lado direito do bot�o
Load, e o mostra na janela dde edi��o. Se o arquivo atual foi modificado e
n�o salvo, uma mensagem de alerta vai dizer ao usu�rio para salvar as
altera��es, ou apertar o bot�o Load novamente.
.br
.ec	/*************************************/

.in
.sp
.b OBSERVA��O
.in 5
Na presente vers�o, "xedit" ainda n�o est� possibilitando a utiliza��o
de caracteres acentuados. Para tanto, � necess�rio usar "ed" ou "vi" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ed, vi
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
