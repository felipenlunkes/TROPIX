.bp
.he 'CC (cmd)'TROPIX: Manual de Refer�ncia'CC (cmd)'
.fo 'Atualizado em 28.08.01'Vers�o 4.1.0'Pag. %'

.b NOME
.in 5
.wo "cc -"
Compilador para linguagem "C"
.br

.in
.sp
.b SINTAXE
.in 5
cc [-casumvOSTPEC.] [-D <def>] ...
.in 14
[-U <id>] ... [-I <dir>] ... [-o <obj>] <arquivo> ...

.in
.sp
.b DESCRI��O
.in 5
O comando "cc" � a interface para o sistema de compila��o da linguagem "C" do
TROPIX. O sistema � composto pelas seguintes ferramentas:
pr�processador ("cpp" (cmd)), compilador (do GNU, programa contribu�do),
montador ("as" (cmd)) e "link-editor" (ld (cmd)).
O comando "cc" processa as op��es dadas, e executa as diversas ferramentas
com os argumentos apropriados. 

.sp
Nesta vers�o de "cc", todos os m�dulos execut�veis gerados s�o reentrantes.
Se for necess�rio gerar um m�dulo N�O reentrante, � necess�rio usar "ld" diretamente.

.sp
O comando aceita diversos tipos de <arquivo>s como argumentos:

.in +3
.ip 1. 3
Arquivos cujos nomes terminam com ".c" s�o considerados programas fonte
em "C" e podem ser pr�processados, compilados, montados 
e "link-editados". O processo de compila��o pode ser interrompido
ap�s qualquer uma destas fases, atrav�s de op��es adequadas.
Se a montagem � executada, ent�o � produzido um m�dulo objeto em
um arquivo cujo nome � o do programa fonte com ".c" substitu�do por ".o".
No entanto, o arquivo "*.o" � normalmente apagado se um �nico programa
fonte em "C" � compilado e "link-editado". 

.ip 2. 3
Arquivos cujos nomes terminam com ".s" s�o considerados programas fonte
em linguagem simb�lica ("assembly"), e podem ser montados e "link-editados".
� produzido um m�dulo objeto em um arquivo cujo nome � o do programa fonte
com ".s" substitu�do por ".o". No entanto, o arquivo "*.o"
� normalmente apagado se um �nico programa fonte � montado e "link-editado". 

.ip 3. 3
Arquivos cujos nomes n�o terminam com ".c" nem ".s" s�o considerados
nomes de m�dulos objeto ou bibliotecas, e s�o passados para o "link-editor".

.ep
.in -3

.sp
Se for gerado um m�dulo execut�vel, o seu nome ser�, por omiss�o, "a.out" (veja a op��o "-o").

.sp
Dependendo da vari�vel "CC_SHLIB" do ambiente (ver "enrivon" (fmt)), a
"link-edi��o" � realizada com bibliotecas convencionais ou compartilhadas.
Se o ambiente contiver a vari�vel "CC_SHLIB" com o valor "0", a "link-edi��o"
ser� realizada com as biliotecas convencionais "/lib/libc" e "/lib/libm".
Por outro lado, se o ambiente N�O contiver a vari�vel "CC_SHLIB",
ou a contiver com o valor "1", a "link-edi��o" ser� realizada com a
bilioteca compartilhada "/lib/libt.o". Se a vari�vel "CC_SHLIB" contiver
outro valor, este ser� usado como nome para a biblioteca ser usada.
De qualquer modo, bibliotecas adicionais podem ser dadas no final da lista
de <arquivo>s.

.sp 2
As op��es do comando s�o:

.in +3
.ip -c 9
Suprime a fase de "link-edi��o", e n�o remove os m�dulos objeto produzidos.

.bc	/*************************************/
.ip -n 9
Se for produzido um m�dulo execut�vel, ele deve ser reentrante.
.ec	/*************************************/

.ip -a 9
Gera os m�dulos objeto e o m�dulo execut�vel com as tabelas de s�mbolos
completas (normalmente elas cont�m apenas os s�mbolos globais).

.ip -s 9
Se for produzido um m�dulo execut�vel, ele n�o deve conter a tabela de s�mbolos.

.ip -u 9
Durante a fase de "link-edi��o", lista os s�mbolos n�o referenciados.

.ip -m 9
Durante a fase de "link-edi��o", produz um mapa dos m�dulos carregados.

.bc	/*************************************/
.ip -f 9
Durante a fase de "link-edi��o",
utiliza a biblioteca de ponto flutuante "falsa".
Isto � �til para programas que sabidamente n�o utilizam nenhuma opera��o
de ponto flutuante (seja de entrada/sa�da ou aritm�tica), pois o m�dulo
execut�vel fica da ordem de 5 Kb menor.
� de responsabilidade do usu�rio certificar-se de que o programa
realmente n�o utiliza opera��es de ponto flutuante
(se alguma fun��o da biblioteca "falsa" for chamada, ser� impressa uma
mensagem de erro, e a execu��o � cancelada).

.ip -l 9
Durante a fase de compila��o, lista o programa fonte (sa�da do pr�processador).

.ip -L 9
Durante a fase de montagem, gera o arquivo de listagem do montador com o nome
"*.l". Esta op��o faz tamb�m com que o compilador mantenha
trechos do programa fonte em "C" na sa�da simb�lica. 

.ip -w 9
Durante a fase de compila��o, gera as informa��es adicionais necess�rias 
para utilizar o depurador simb�lico "wsdb" (cmd).
Se for utilizada esta op��o, n�o pode ser utilizada a fase de otimiza��o
(op��o "-O").
.ec	/*************************************/

.ip -v 9
Lista os nomes das fases sendo executadas, al�m de algumas informa��es
adicionais fornecidas por algumas das fases.

.ip -O 9
Executa a fase de otimiza��o do compilador "C". Esta op��o n�o tem efeito
para programas fonte em linguagem simb�lica.
.bc	/*************************************/
Se for utilizada esta op��o, n�o pode ser utilizada a depura��o simb�lica
(op��o "-w").
.ec	/*************************************/

.ip -S 9
Compila os programas fonte em "C" dados, gerando os
programas correspondentes em linguagem simb�lica (com o sufixo ".s").
N�o � realizada nenhuma montagem nem "linkedi��o".

.ip -T 9
Executa apenas o pr�processador e a fase de an�lise sint�tica
do compilador nos programas fonte em "C" dados.
S�o executadas heur�sticas especiais do compilador, com a finalidade
de apontar constru��es suspeitas dos programas em "C",
que normalmente n�o s�o indicadas.
Este modo � semelhante ao utilit�rio "lint" de alguns sistemas UNIX.
N�o � gerado nenhum arquivo.

.ip -P 9
Executa apenas o pr�processador nos programas fonte em "C" dados,
gerando os programas correspondentes (com o sufixo ".i").

.ip -E 9
Executa apenas o pr�processador nos programas fonte em "C" dados,
pondo o resultado na sa�da padr�o.

.ip -C 9
N�o remove os coment�rios durante o pr�processamento; isto �
�til para as op��es "-P" e "-E".

.ip -. 9
Aloca os arquivos tempor�rios no diret�rio corrente
ao inv�s do diret�rio "/tmp".

.bc	/*************************************/
.ip "-p <cpu>" 9
Gera c�digo objeto para a <cpu> dada.
Se esta op��o n�o for dada, esta informa��o � procurada no ambiente (fmt).
Se tamb�m n�o for dada no ambiente, ser� gerado o c�digo objeto
nativo do compilador.
Nesta vers�o, o c�digo nativo � o do MC68010, e podem ser dados
"m10" (MC68010), "m20" (MC68020) ou "m20,m81" (MC68020 e MC68881).
.ec	/*************************************/

.ip '-D <def>' 9
Pr�define macros para a fase de pr�processamento:
<def> � uma defini��o de macro do tipo "identificador" ou
"identificador=valor".
No primeiro caso, a macro � definida com valor "1".
Veja maiores detalhes em "cpp" (cmd).

.ip '-U <id>' 9
N�o permite macros com o nome <id> durante a fase de pr�processamento.
Mesmo que hajam defini��es da macro <id>
no decorrer do texto, elas s�o ignoradas.
Veja maiores detalhes em "cpp" (cmd).

.ip '-I <dir>' 9
Acrescenta <dir> � lista de diret�rios de busca de arquivos "#include"
durante a fase de pr�processamento.
Veja maiores detalhes em "cpp" (cmd).

.ip "-o <obj>" 9
Se <obj> for um diret�rio j� existente, os m�dulos objeto gerados
ser�o nele colocados com o sufixo ".o", e/ou o m�dulo execut�vel gerado
ser� nele colocado com o nome "a.out".
Em caso contr�rio, <obj> ser� usado como o nome do m�dulo objeto
(execut�vel ou n�o) gerado.
Se esta op��o n�o for dada, o nome do m�dulo execut�vel gerado
ser� "a.out".

.ep
.in -3

.in
.sp
.b DIAGN�STICOS
.in 5
Tanto o pr�processador como o compilador emitem diagn�sticos,
que (por hip�tese) s�o auto-explicativos.
O "link-editor" pode emitir diagn�sticos sobre m�dulos objeto n�o encontrados.

.in
.sp
.b OBSERVA��ES
.in 5
Como "cc" usualmente cria arquivos no diret�rio corrente, � necess�rio
executar o comando em um diret�rio no qual podem ser criados arquivos.

.bc	/*************************************/
.sp
Com a utiliza��o da op��o "-f", podem ocorrer colis�es entre s�mbolos
externos dos m�dulos objeto do usu�rio e a biblioteca "falsa".
Neste caso � necess�rio mudar os nomes dos s�mbolos do usu�rio
(ou n�o usar a op��o "-f").
.ec	/*************************************/
 
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cpp, as, ld
.bc	/*************************************/
cpp, as, ld, wsdb
.ec	/*************************************/
.br
.wo "(fmt): "
ambiente
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
Kernighan, B. W., e Ritchie, D. M., "The C programming Language",
Prentice-Hall, 1978. 

.sp
"American National Standard: Programming Language C" (ANSI),
Technical Commitee X3J11.

.in
.sp
.(t
.b ARQUIVOS
.in 5
.nf
     a.out		Sa�da da "link-edi��o" (nome por omiss�o)
     plcc*		Arquivos tempor�rios
     /tmp/plcc*
     /lib/cpp		Pr�processador
     /lib/gcc.486	Compilador "C"
     /bin/as		Montador
     /bin/ld		"Link-editor"
     /lib/crt0.o	"Run time startoff"
     /lib/crt1.o	"Run time startoff"
     /lib/libc		Bibliotecas padr�o
     /lib/libt.o
     /usr/include	Diret�rio padr�o para arquivos de "#include"
.fi
.)t

.in
.sp
.b EXEMPLOS
.in 7
.sp
.nf
		cc -o obj alpha.c beta.c gamma.s
.fi
.in 5
.sp
compila "alpha.c" e "beta.c", monta "gamma.s" e gera um m�dulo execut�vel.
Se "obj" for um diret�rio existente, o m�dulo gerado ser�
"obj/a.out" e em caso contr�rio "obj".

.sp
.nf
		cc -c -o redoma alpha.c beta.c gamma.c delta.c
.fi
.sp
compila "alpha.c", "beta.c", "gamma.c" e "delta.c", colocando
os m�dulos objetos ("alpha.o", ...) no diret�rio "redoma", que j� deve existir.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
