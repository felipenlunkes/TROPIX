.bp
.he 'AS (cmd)'TROPIX: Manual de Refer�ncia'AS (cmd)'
.fo 'Atualizado em 24.08.01'Vers�o 4.1.0'Pag. %'

.b NOME
.in 5
.wo "as -"
montador para INTEL-80386/486/PENTIUM
.br

.in
.sp
.b SINTAXE
.in 5
.(l
as [-avwe] [-o <obj>] [-l <lst>] [-D <def> ...] <fonte> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "as" � o montador do sistema TROPIX para programas em
linguagem simb�lica dos microprocessadores INTEL-80386/486/PENTIUM.

.sp
Sua finalidade � traduzir programas em linguagem simb�lica
contidos nos arquivos <fonte> ... para o formato de m�dulo
objeto padr�o do TROPIX, que serve de entrada para o
"link-editor" ld (cmd). 

.sp
Nesta vers�o do sistema, n�o h� mais limite no tamanho dos identificadores.

.sp
As op��es do comando s�o:

.in +3

.bc	/*************************************/
		"\t-w: Monta para um segmento de 16 bits (ao inv�s de 32)\n"
		"\t-e: A listagem deve ser no estilo \"little-endian\"\n"
		"\t-o: O nome do m�dulo objeto gerado deve ser <obj> "
			"(ao inv�s de \"a.out\")\n"
		"\t-l: Gera um arquivo de listagem com o nome <lst>\n"
		"\t-D: Predefine vari�veis "
			"(<def> � da forma \"var\" ou \"var=valor\")\n"
.ec	/*************************************/
.ip -a
Inclui tamb�m os s�mbolos (vari�veis e r�tulos) locais na tabela
de s�mbolos no m�dulo objeto gerado.
Normalmente, s�o inclu�dos apenas os s�mbolos globais.

.ip -v
Com esta op��o, o comando "as" emite algumas estat�sticas sobre os
SDIs ("span dependent instructions"). 

.ip -w
Inicia a montagem para um segmento de 16 bits -
normalmente, o montador inicia a montagem para um segmento de 32 bits
(isto pode tamb�m ser alterado atrav�s das pseudo-instru��es
".seg16" e ".seg32").

.ip -e
Caso seja pedida uma listagem (op��o "-l"), os endere�os s�o
impressos no formato "little-endian" ao inv�s de "big-endian".

.ip -o
Gera o m�dulo objeto com o nome <obj> (ao inv�s de "a.out").
Por homogeneidade, recomendamos que este nome termine com a extens�o ".o".

.ip -l
Gera um arquivo de listagem com o nome <lst>.
A listagem cont�m os c�digos e endere�os de instru��es utilizadas
no programa e a tabela de s�mbolos produzida.

.ip -D
Antes de iniciar a montagem, define a vari�vel "var" com o "valor"
dado, ou com "1", se o "valor" n�o for dado.

.ep
.in -3

.in
.sp
.b DIAGN�STICOS
.in 5
As incorre��es s�o classificadas em "erros" e "advert�ncias".
Para cada incorre��o � impressa a linha, com um ponteiro
indicando o local prov�vel da incorre��o, seguida de uma
mensagem de diagn�stico (por hip�tese auto-explicativa).
Erros detetados no passo 1 suprimem a execu��o do passo 2.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ld
.br
.wo "(fmt): "
a.out
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
