.bp
.he 'SIZE (cmd)'TROPIX: Manual de Refer�ncia'SIZE (cmd)'
.fo 'Atualizado em 11.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "size -"
imprime tamanhos e caracter�sticas de m�dulos objeto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
size [-dcxaN] [<m�dulo> ...]
.)l

.in
.sp
.b DESCRICAO
.in 5
O comando "size" imprime uma linha para cada <m�dulo> objeto dado,
contendo os tamanhos das suas v�rias se��es,
al�m de algumas outras informa��es.

.sp 
As informa��es dadas s�o as seguintes:

.in +3
.ip MACH 8
Modelo do computador de origem do <m�dulo> objeto
(Por exemplo, "486", indicando um m�dulo objeto nativo para
INTEL 386/486/PENTIUM).

.ip TIPO 8
Tipo do <m�dulo> objeto: "." para normal, "n" para reentrante e
"s" para biblioteca compartilhada.
Para m�dulos reentrantes, s�o indicados ainda, com "t" ou "m"
os indicadores S_ISVTX e S_IMETX do seu estado (ver "chmod" (sys)).

.ip TS 8
Presen�a ("*") ou aus�ncia (".") da tabela de s�mbolos.

.ip RL 8
Presen�a ("*") ou aus�ncia (".") da informa��o de reloca��o.

.ip VER 8
Vers�o das bibliotecas compartilhadas referenciadas por este
<m�dulo> objeto.

.ip FLAG 8
Indicadores (atualmente sem uso).

.ip TEXTO 8
Tamanho ou endere�o inicial do texto (veja a op��o "-s").

.ip DATA 8
Tamanho ou endere�o inicial da �rea de dados inicializados (veja a op��o "-s").

.ip BSS 8
Tamanho da �rea de dados n�o inicializados.

.ip COMMON 8
Soma dos tamanhos das vari�veis "comuns" a outros m�dulos objeto.
Estas vari�veis ser�o apenas alocadas em tempo de "link-edi��o"
(ver "ld" (cmd)), e ficar�o superpostas
a vari�veis hom�mimas de outros m�dulos objeto.
Este valor s� � impresso com a op��o "-c" (ver adiante).

.ip REFTB 8
Tamanho da tabela de referencias externas. Esta tabela � utilizada
na execu��o de m�dulos objetos que referenciam bibliotecas compartilhadas.
Este valor s� � impresso com a op��o "-c" (ver adiante).

.ip TOTAL 8
Soma das se��es TEXTO + DATA + BSS. Repare que N�O inclui COMMON.

.ip -DATA- 8
Data de gera��o do <m�dulo>. Esta � a data contida no cabe�alho
do m�dulo; n�o confundir com alguma das datas do arquivo.
Ela s� � impressa com a op��o "-d" (ver adiante).

.ip NOME 8
Nome do m�dulo.

.ep
.in -3
.sp
.(t
As op��es do comando s�o:

.in +3
.ip -s
Imprime o endere�o inicial (em hexadecimal) das se��es TEXT e DATA ao inv�s dos tamanhos.
.)t

.ip -d
Imprime tamb�m a data de gera��o do <m�dulo> objeto.
.)t

.ip -c
Imprime tamb�m os tamanhos das se��es COMMON e REFTB.

.ip -x
Os tamanhos s�o dados em hexadecimal ao inv�s de decimal.

.ip -a
Emite mensagens de erro para arquivos que n�o s�o m�dulos objeto
(ao inv�s de simplesmente ignor�-los).

.ip -N
L� os nomes dos <m�dulos> de "stdin"

.ep
.in -3
.sp
Se n�o for dado nenhum <m�dulo>, nem a op��o "-N", ser�o
dadas informa��es sobre "a.out".

.in
.sp
.b OBSERVA��ES
.in 5
.bc	/*************************************/
Como o tamanho real da �rea de dados n�o inicializados (BSS) s� � conhecido
ap�s a "link-edi��o", o comando "size" pode dar tamanhos err�neos para m�dulos
n�o execut�veis. Isto ocorre em virtude das vari�veis em "common".
.sp
.ec	/*************************************/

Para obter informa��es sobre m�dulos contidos em bibliotecas, podemos
usar a expans�o proporcionada pelo "sh" (cmd), como por exemplo:
.sp
.nf
		size /lib/libc/id/*.o
.fi
.sp
ou ent�o usar o comando "walk" (cmd) para obter o nome
de todos os m�dulos de uma biblioteca, como por exemplo:
.sp
.nf
		walk -p "*.o" /lib/libc | size -N
.fi

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chmod
.br
.wo "(cmd): "
sh, walk, ld
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
