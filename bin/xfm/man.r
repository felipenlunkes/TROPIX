.bp
.he 'XFM (cmd)'TROPIX: Manual de Refer�ncia'XFM (cmd)'
.fo 'Atualizado em 23.09.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.(l
xfm - gerenciador gr�fico de arquivos
.)l

.in
.sp
.b SINTAXE
.in 5
.(l
xfm [-g <geo>] [-f <frente>] [-b <fundo>] [-d <video>]
						[-M <m>] [-F <f>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O gerenciador gr�fico de arquivos "xfm" permite a visualiza��o completa da �rvore
do sistema de arquivos e nela efetuar algumas opera��es, tais como c�pias, compara��es, edi��es, ...

.in
.sp
.b 'DISPOSI��O DAS JANELAS'
.in 5
O programa "xfm" cont�m (de cima para baixo) as seguintes janelas:

.in +3
.ip 1. 3
Janela de bot�es: op��es (veja abaixo), aloca��o de mem�ria din�mica, atualiza��o
da �rvore, releitura da �rvore e finaliza��o do programa.

.ip 2. 3
Janela de mensagens: Nesta janela s�o escritas 3 tipos de mensagens:

.in +6
.ip a. 3
Mensagens informativas (com o fundo regular).

.ip b. 3
Mensagens de �rro (com o fundo vermelho).

.ip c. 3
Mensagens consultando o usu�rio (com o fundo vermelho).
O usu�rio deve ent�o clicar em "SIM" ou "N�O".

.ep
.in -6

.ip 3. 3
Janela da �rvore (� esquerda): Nesta janela � desenhada a �rvore que representa
o completo sistema de arquivos, por�m apenas os diret�rios (os outros arquivos,
isto �, os conte�dos dos diret�rios s�o mostrados na janela do diret�rio (veja abaixo)).

.sp
Cada diret�rio � representado por dois �cones: um bot�o (azul se o diret�rio contiver
filhos, ou vermelho em caso contr�rio) e o �cone amarelo de uma "pasta", seguido
do nome do diret�rio.

.sp
Se o diret�rio corresponder a um ponto de montagem (de acordo
com o arquivo "/etc/fstab" (veja "fstab" (fmt))), o �cone cont�m um pequeno ponto
vermelho.

.sp
Diret�rios "irm�os", isto �, filhos do mesmo diret�rio "pai" s�o dispostos verticalmente
com a mesma indenta��o. � medida em que se aprofunda na �rvore, os diret�rios v�o
sendo indentados para a direita.

.sp
Quando "xfm" inicia, somente s�o mostrados os filhos de "/". Para desenhar os filhos de
um diret�rio, basta clicar no seu bot�o (desde que ele seja azul). Se o bot�o for clicado
mais uma vez, os filhos (e todos os seus descendentes) s�o removidos da janela.

.sp
Clicando no pr�prio �cone do diret�rio, o seu cont�udo � mostrado na janela do
diret�rio (veja abaixo).

.ip 4. 3
Janela do diret�rio (� direita): Nesta janela � desenhado o conte�do do diret�rio
que foi clicado na janela da �rvore (veja acima).

.sp
Cada linha corresponde a uma entrada do diret�rio; a primeira linha � a do pai do
diret�rio mostrado.

.sp
Cada linha cont�m:

.in +6
.ip a. 3
Bot�o de sele��o:
Se este bot�o estiver azul, o arquivo correspondente est� selecionado para
opera��es de c�pia, compara��o, movimenta��o (troca de nome ou mudan�a de diret�rio)
e remo��o. Em caso contr�rio (cor normal de fundo), o arquivo n�o est� selecionado.

.sp
O bot�o esquerdo do "mouse" seleciona/deseleciona um arquivo. Para selecionar v�rios
arquivos, o bot�o deve ser arrastado pressionado.
Repare que � poss�vel selecionar um conjunto de arquivos, por�m n�o mais do que um diret�rio.

.ip b. 3
�cone do tipo do arquivo:
O �cone tenta dar uma id�ia do tipo do arquivo:
para diret�rios, o �cone amarelo de uma "pasta" (como na janela da �rvore);
para arquivos regulares, uma "roda dentada" se for um m�dulo execut�vel ou
uma "folha de papel" em caso contr�rio;
para dispositivos especiais (de blocos ou caracteres) a imagem de "uma unidade
de disquete"; para elos simb�licos dois elos entrela�ados (um azul e outro vermelho).

.ip c. 3
Letra indicativa do tipo do arquivo:

.sp
.in +2
.wo 'R  '
Arquivo regular
.br
.wo 'B  '
Dispositivo especial de blocos
.br
.wo 'C  '
Dispositivo especial de caracteres
.br
.wo 'L  '
Elo simb�lico
.br
.wo 'D  '
Diret�rio
.br
.wo 'F  '
"Fifo"
.br
.wo '?  '
Arquivo de tipo inv�lido
.br
.in -2

.ip d. 3
Prote��o do arquivo: ele tem a forma

.nf

			"rwxrwxrwx"

.fi

onde s�o dados os 9  caracteres relativos � prote��o
do arquivo. Se algum indicador estiver desligado, o caracter
assume o valor '-' ao inv�s do caracter indicado acima.

.sp
Se, na op��o "Modo dos arquivos" (veja abaixo)
foi selecionado o "modo completo",
ser�o dados 4 indicadores adicionais, na forma:

.nf

			"mtsg rwxrwxrwx"

.fi

Para maiores detalhes, veja "ls" (cmd).


.ip e. 3
N�mero de elos f�sicos do arquivo.

.ip f. 3
Dono e grupo do arquivo.

.ip g. 3
Tamanho do arquivo (ou �ndices do dispositivo).

.ip h. 3
Data da �ltima modifica��o do arquivo.

.ip i. 3
Nome do arquivo (com a cor de acordo com a vari�vel MODECOLOR do ambiente,
veja "modecolor" (libc)).

.ep
.in -6

.ip 5. 3
Janela do nome do diret�rio: Esta janela fica acima da janela do diret�rio e cont�m
o nome do diret�rio cujo conte�do est� mostrado na janela abaixo.

.ip 6. 3
Janelas das barras de rolamento das janelas da �rvore e do diret�rio: Cont�m barras
de rolamento "tradicionais", com a adi��o de um bot�o adicional (segundo de baixo
para cima), com a mesma fun��o do bot�o superior.

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
Padr�es: permite selecionar, de acordo com o nome, os arquivos a serem processados
pelas opera��es de c�pias/compara��es.

.sp
A alternativa "Apenas os fontes" restringe as opera��es aos arquivos relevantes
� compila��o de programas na linguagem "C", isto �, �queles cujos nomes
satisfazem os padr�es "*[Mm]akefile" e "*.[cshryv]" (veja "patmatch" (libc)).

.bc	/*************************************/
.ip 1. 3
Padr�es: permite incluir/excluir arquivos para as opera��es de c�pias/compara��es
de acordo com o nome do arquivo.

.sp
A alternativa "Apenas os fontes" restringe as opera��es aos arquivos relevantes
� compila��o de programas na linguagem "C", isto �, �queles cujos nomes
satisfazem os padr�es "*[Mm]akefile" e "*.[cshryv]" (veja "patmatch" (libc)).
.ec	/*************************************/

.ip 2. 3
Arquivos ocultos: inclui (alternativa "Processa") ou N�O (alternativa "Ignora")
arquivos cujos nomes come�am por "." nas opera��es de c�pias/compara��es.


.bc	/*************************************/
.ip 2. 3
Arquivos ocultos: assim como acima, permite incluir/excluir arquivos para as
opera��es de c�pias/compara��es de acordo com o nome do arquivo.

.sp
A alternativa "Ignora" exclui do processamento os arquivos cujos nomes come�am
por ".".
.ec	/*************************************/

.ip 3. 3
Largura das janelas: permite (alternativa "Estende") ou N�O (alternativa "N�o estende")
o aumento autom�tico da largura das janelas da �rvore e do diret�rio.

.ip 4. 3
Modo dos arquivos: resumido (alternativa "Resumido") ou completo (alternativa "Completo"); 
veja acima, em "Prote��o do arquivo".

.ip 5. 3
Vers�o: A vers�o do programa "xfm".

.ep
.in -3


.in
.sp
.b MENUS
.in 5
Para as diversas opera��es de c�pias, compara��es, ... temos os seguintes menus:

.in +3
.ip 1. 3
Menu da �rvore: este menu � ativado clicando o bot�o da direita no �cone do diret�rio desejado da
janela da �rvore.

.sp
Neste menu s�o oferecidas as seguintes opera��es: "ziptool", "mount", "umount", "eject",
"df", "du", "rm", "cp", "cmp", "mv", "sh" e "mkdir".

.sp
Estas opera��es funcionam de modo an�logo aos comandos hom�nimos do TROPIX, tendo como
argumento o nome o nome do diret�rio.

.sp
Em particular, os arquivos fontes das opera��es
"cp", "cmp" e "mv" s�o os integrantes do conjunto selecionado na janela do diret�rio
(veja abaixo).

.ip 2. 3
Menu de um arquivo: este menu � ativado clicando o bot�o da direita no �cone do arquivo desejado da
janela do diret�rio.

.sp
Neste menu s�o oferecidas as seguintes opera��es: "rm", "rename", "sh", "show",
"vi", "xedit", "xpaint" e "mkdir".

.sp
Estas opera��es funcionam de modo an�logo aos comandos hom�nimos do TROPIX, tendo como
argumento o nome do arquivo/diret�rio.

.ip 3. 3
Menu de um conjunto de arquivos: este menu � ativado clicando o bot�o da direita em qualquer
um dos bot�es da janela do diret�rio.

.sp
Neste menu s�o oferecidas as seguintes opera��es: "rm", "rename", "sh", "show",
"vi", "xedit", "xpaint" e "mkdir".

.sp
Estas opera��es funcionam de modo an�logo aos comandos hom�nimos do TROPIX, tendo como
argumento os nomes dos arquivos do conjunto.

.sp
O conjunto de arquivos � selecionado de um dos seguintes modos:

.in +3
.ip 1. 3
Arquivo individual: clica-se com o bot�o esquerdo diretamente no bot�o do arquivo (ou diret�rio)
a selecionar.

.ip 2. 3
Seq��ncia de arquivos: clica-se com o bot�o esquerdo no bot�o do primeiro arquivo da seq��ncia, e
mantendo-se o bot�o pressinado, arrasta-se o "mouse" at� o �ltimo arquivo da seq��ncia, onde
soltamos o bot�o.

.sp
Repetindo esta opera��o, podemos selecionar v�rias seq��ncias de arquivos.
Se esta mesma opera��o for efetuada em arquivos previamente selecionados, o efeito ser�
exclu�-las do conjunto de arquivos selecionados.

.ep

.sp
Repare que podemos selecionar um ou mais arquivos, mas apenas um diret�rio.

.sp
A sele��o de um conjunto de arquivos � usada tamb�m para especificar os arquivos fontes
das opera��es de "cp", "cmp" e "mv" do menu da �rvore.

.in -3

.ep
.in -3

.sp
Para algumas das opera��es � pedida uma confirma��o da opera��o a ser efetuada.

.in
.sp
.b 'OP��ES DO COMANDO'
.in 5
.in +3
.ip -g
Fornece a geometria inicial (em pixeis), no formato <largura>x<altura>.

.ip -f
Use a cor de <frente> dada.

.ip -b
Use a cor de <fundo> dada.

.ip -d
Conecte-se ao <v�deo> dado.

.ip -M
Use a fonte <m> dada para as janelas dos bot�es.

.ip -F
Use a fonte <f> dada para as demais janelas.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ziptool, mount, umount, eject, df, du, rm, cp, cmp,
.in 13
mv, sh, mkdir, rename, show, vi, xedit, xpaint
.br
.in 5
.wo "(libc):"
modecolor, patmatch
.br
.wo "(fmt): "
fstab
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
