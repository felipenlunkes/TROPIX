.bp
.he 'MAKE (cmd)'TROPIX: Manual de Refer�ncia'MAKE (cmd)'
.fo 'Escrito em 13.12.99'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
make - gerencia a manuten��o de grupos de programas
.sp

.in
.sp
.b SINTAXE
.in 5
make [-intvab] [-f <desc>] [-D <macro>=<valor>] <m�dulo>...

.in
.sp
.b DESCRI��O
.in 5
O comando "make" gerencia a manuten��o de sistemas compostos por
v�rios m�dulos.
As rela��es de depend�ncia entre os m�dulos s�o expressas em um
arquivo de descri��o, que cont�m os comandos necess�rios para
reconstituir o sistema em virtude de altera��es produzidas nos
seus m�dulos integrantes.
.sp
.in 5
O comando aceita como argumentos nomes de m�dulos.
Se n�o for dado nenhum nome de m�dulo, ser� criado/atualizado o primeiro
m�dulo do arquivo de descri��o.
Um m�dulo � criado/atualizado se n�o existe ou ent�o depende
de outros m�dulos
que tenham sido modificados desde a �ltima modifica��o do m�dulo em quest�o.
.sp
.in 5
Se o arquivo de descri��o n�o for especificado (op��o "-f"),
procuram-se os arquivos "Makefile" e "makefile"
(nessa ordem), no diret�rio corrente.

.in 5
.sp 2
As Op��es s�o as seguintes:
.in 8

.ip -i 5
Ignore erros em todos os comandos.

.ip -n 5
Liste os comandos que s�o necess�rios para a atualiza��o, mas n�o os execute.

.ip -t 5
Atualize a data de modifica��o dos m�dulos, sem executar os comandos.

.ip -v 5
Explica o motivo das atualiza��es.

.ip -a 5
Apenas lista os alvos definidos no arquivo de descri��o, exceto os da
forma "*.o". Se for duplicada a op��o ("-aa"), todos os alvos s�o
listados, sem exce��o.

.ip -b 5
Provoca a atualiza��o de todos os m�dulos, independentemente das datas.

.ip -f 5
Utilize <desc> como arquivo de descri��o.

.ip -D 5
Defina a macro <macro> com o valor <valor>.
Esta defini��o se sobrep�e a outras defini��es da mesma macro
(por exemplo no arquivo de descri��o e/ou no ambiente).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, touch
.br
.in 5
.wo "(ref): "
make
.br

.in
.sp
.b ARQUIVOS
.in 5
 Makefile - primeira op��o para o arquivo descri��o.
 makefile - segunda op��o para o arquivo descri��o.

.(t
.in
.sp
.b EXEMPLO
.in 7
.sp 1
Exemplo de um arquivo de descri��o:
.sp
.nf
	mod:	mod1.o mod2.o mod3.o
		cc -o mod mod1.o mod2.o mod3.o

	mod1.o:	mod1.h mod1.c
		cc -c mod1.c

	mod2.o: mod2.h mod2.c
		cc -c mod2.c

	mod3.o: mod3.h mod3.c
		cc -c mod3.c
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
