.bp
.he 'XPOP3 (cmd)'TROPIX: Manual de Refer�ncia'XPOP3 (cmd)'
.fo 'Atualizado em 23.04.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.(l
xpop3 - acessa uma caixa postal remota atrav�s do protocolo POP3
.)l

.in
.sp
.b SINTAXE
.in 5
.(l
xpop3 [-d <d>] [-g <g>] [-f <frente>] [-b <fundo>] [-F <f>]
.)l

.bc	/*************************************/
xpop3 - acessa uma caixa postal remota atrav�s do protocolo POP3

Vers�o: 4.5.0, de 23.03.04

Sintaxe:
	xpop3 [-d <day>] [-g <geometria>] [-f <frente>] [-b <fundo>] [-F <f>]

Op��es:	-d: Conecta-se ao servidor X <display>
	-g: Define a <geometria>
	-f: Define a cor de <frente>
	-b: Define a cor de <fundo>
	-F: Use a fonte <f>
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O programa gr�fico "xpop3" permite o acesso a uma caixa postal remota, atrav�s
do protocolo POP3 (Post Office Protocol, Version 3).  

.in
.sp
.b 'DISPOSI��O DAS JANELAS'
.in 5
O programa "xpop3" cont�m (de cima para baixo) as seguintes janelas:

.in +3
.ip 1. 3
Janela de bot�es: op��es (veja abaixo), conecta, desconecta, recebe, remove
e finaliza��o do programa.

.ip 2. 3
Janela de mensagens: Nesta janela s�o escritas mensagens referentes ao
andamento da comunica��o com o servidor, e pedidas senhas.

.ip 3. 3
Janela da conex�o: cont�m dois componentes:

.in +3
.ip a. 3
Estado da conex�o:
Cor de fundo: desconectado; verde: conectado, em fase de autentica��o;
azul: conectado e autenticado.

.ip b. 3
Barra de progresso das transfer�ncias.

.ep
.in -3

.ip 4. 3
Janela da mensagens: cont�m 4 colunas:

.in +3
.ip a. 3
Bot�es de recebimento: preto: n�o recebe; verde: recebe; azul: recebida.

.ip b. 3
Bot�es de remo��o: preto: n�o remove; laranja: remove; vermelho: removido.

.ip c. 3
Dados da mensagem: �ndice, Endere�o eletr�nico remoto, data, tamanho e assunto.

.ip d. 3
Barra de rolagem vertical.

.ep
.in -3

.ep
.in -3

.in
.sp
.b 'BOT�O DE OP��ES'
.in 5
Este bot�o, o primeiro � esquerda na janela de bot�es, fornece o seguinte "menu"
de op��es:

.in +3
.ip 1. 3
Recebe todas as cartas: seleciona todas as cartas para recebimento.

.ip 2. 3
N�O recebe nenhuma carta: desfaz as sele��es para o recebimento das cartas.

.ip 3. 3
Remove todas as cartas: seleciona todas as cartas para remo��o.

.ip 4. 3
N�O remove nenhuma carta: desfaz as sele��es para a remo��o das cartas.

.ip 5. 3
Cancela a remo��o das cartas: as cartas s� s�o efetivamente removidas quando
o programa "xpop3" termina; atrav�s desta op��o indicamos ao servidor para
desistir da remo��o destas cartas.

.ip 6. 3
Limita o tamanho das cartas: Normalmente, n�o h� limite no tamanho das cartas
a receber/remover. Com esta op��o � poss�vel definir um limite para o tamanho.

.ip 7. 3
Caixa postal local: Indica o nome do usu�rio local, que ser� usado para definir
o nome da caixa postal local.
Repare que alterando o usu�rio local, ser� alterado automaticante o usu�rio
remoto (mas n�o reciprocamente).

.ip 8. 3
Caixa postal remota: Indica o nome da caixa postal remota, contendo o nome do
usu�rio remoto, e o nome do n� remoto aonde ser� contactado o servidor POP3.
O nome do n� remoto pode ser dado na vari�vel XPOP3 do ambiente,
como (por exemplo) na forma:

.sp
.nf
		XPOP3=pop.ig.com.br; export XPOP3
.fi

.ip 9. 3
Vers�o: A vers�o do programa "xpop3".

.ep
.in -3


.in
.sp
.b 'MODO DE USO'
.in 5
Supondo que a vari�vel do ambiente XPOP3 esteja convenientemente definida,
o uso "normal" se d� atrav�s das seguintes etapas:

.in +3
.ip 1. 3
Apertar o bot�o "Conecta".

.ip 2. 3
Dar a senha da caixa postal remota.

.ip 3. 3
Na janela de mensagens estar�o as mensagens novas.

.ip 4. 3
Clicar nas mensagens a receber/remover.

.ip 5. 3
Clicar nos bot�es "Recebe" e "Remove".

.ip 6. 3
Clicar no bot�o "Fim".

.in -3
.ep

.sp
Para acessar outras caixas postais, devemos clicar no bot�o "Desconecta",
usar as op��es do menu "Caixa postal local" e/ou "Caixa postal remota"
e conectar novamente.

.in
.sp
.b 'OP��ES DO COMANDO'
.in 5
.in +3
.ip -d
Conecta-se ao servidor X <d>

.ip -g
Fornece a geometria inicial (em pixeis), no formato <largura>x<altura>.

.ip -f
Use a cor de <frente> dada.

.ip -b
Use a cor de <fundo> dada.

.ip -F
Use a fonte <f> dada.

.bc	/*************************************/
Op��es:	-d: Conecta-se ao servidor X <display>
	-g: Define a <geometria>
	-f: Define a cor de <frente>
	-b: Define a cor de <fundo>
	-F: Use a fonte <f>
.ec	/*************************************/

.ep
.in -3

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
