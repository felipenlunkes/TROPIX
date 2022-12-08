.bp
.he 'GETSET (curses)'TROPIX: Manual de Refer�ncia'GETSET (curses)'
.fo 'Atualizado em 29.09.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Controla o modo de entrada de texto do teclado:
.sp
.wo "wgetset -"
estabelece o modo
.br
.wo "wgeton  -"
habilita algumas op��es do modo
.br
.wo "wgetoff -"
desabilita algumas op��es do modo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wgetset (WINDOW *janela, int modo);
void wgeton (WINDOW *janela, int op��es);
void wgetoff (WINDOW *janela, int op��es);
.)l

.in
.sp
.b DESCRI��O
.in 5
As macros "wgetset", "wgeton" e "wgetoff"
controlam o modo de entrada de texto do teclado
de cada janela.

.sp
A macro "wgetset" estabelece o modo de entrada,
enquanto que as macros "wgeton" e "wgetoff"
habilitam e desabilitam, respectivamente,  algumas de suas op��es.

.sp
A entrada de texto de "curses" reproduz os servi�os realizados
pela interface de terminais do TROPIX
e oferece outras facilidades.
O modo de entrada dos caracteres teclados
� estabelecido habilitando ou desabilitando suas op��es
de acordo com os seguintes indicadores:

.in +3
.ip "G_ECHO:" 11
Eco. Os caracteres teclados s�o escritos em uma janela
e, conseq�entemente, s�o ecoados no v�deo do terminal.

.ip "G_INSERT:" 11
Inser��o.
Quando a entrada de caracteres � ecoada, os caracteres podem ser inseridos
ou podem substituir os caracteres j� existentes na janela.
Este indicador habilita a inser��o.
Com a op��o de inser��o
os caracteres lidos s�o ecoados atrav�s da rotina "winsch",
enquanto que sem esta op��o atrav�s da rotina "waddch".
Al�m disso, na entrada de texto com inser��o
a posi��o onde o pr�ximo caractere ser� inserido
� indicada por um espa�o extra apontado pelo cursor.

.ip "G_EDIT:" 11
Edi��o por linha.
A entrada de caracteres pelo teclado normalmente � editada linha a linha.
Isto significa que os caracteres em uma linha
s� se tornam dispon�veis ap�s o t�rmino desta (com um <nl> ou outro terminador)
e que, enquanto isto n�o ocorre,
o usu�rio pode acrescentar ou remover caracteres em qualquer posi��o da linha
(veja a se��o "INTERA��O COM O USU�RIO").
Quando a entrada n�o � editada
os caracteres s�o recebidos � medida em que s�o teclados.
A edi��o da entrada sempre � realizada com eco.

.ip "G_TOISO:" 11
Gera��o de caracteres acentuados.
Se o teclado do terminal n�o for capaz de gerar caracteres acentuados
e a entrada for editada,
determinados pares de caracteres s�o convertidos
nos caracteres acentuados correspondentes.
Os pares definidos s�o "," seguido de "c" ou "C" (significando "�" ou "�"),
":" seguido de vogal (significando a vogal com trema),
"=" seguido de "a" ou "o"  (significando � ou �)
e os acentos "'", "`", "^" e "~" seguidos de vogal
(significando a vogal com o acento).
Para evitar a convers�o de um par de caracteres,
basta teclar "\" entre eles (por ex: "'\a" para gerar "'a").
Usando este indicador o programa pode determinar se haver�
a convers�o de pares de caracteres em caracteres acentuados
independentemente do teclado poder ger�-los ou n�o.

.ip "G_TONL:" 11
Convers�o do caractere <cr> no caractere <nl>.

.ip "G_KEYPAD:" 11
Reconhecimento de teclas especiais.
Se esta op��o est� habilitada
as seq��ncias de caracteres correspondentes �s teclas especiais
s�o convertidas em constantes simb�licas.
Este mecanismo elimina a necessidade
de realiza��o de um processamento dependente 
do tipo do terminal em que o programa est� sendo executado.
O reconhecimento de teclas especiais abrange na vers�o corrente
as seguintes constantes simb�licas:
"KEY_HOME",
"KEY_DOWN",
"KEY_UP",
"KEY_LEFT",
"KEY_RIGHT" e
"KEY_F0" a "KEY_F9".
Estas constantes est�o definidas no arquivo para inclus�o "<curses.h>".

.ip "G_NODELAY:" 11
Entrada de texto n�o bloqueada.
O comportamento da rotina "wgetch" quando n�o h� caracteres teclados
depende desta op��o;
normalmente ela fica bloqueada esperando o teclado,
com esta op��o ela retorna imediatamente a constante inteira "ERR".

.ip "G_SIGRET:" 11
Retorno imediato quando a leitura � interrompida por algum sinal.
Normalmente a recep��o de um sinal n�o afeta a leitura
de caracteres do teclado; com esta op��o a rotina "wgetch"
retorna o valor "ERR" imediatamente ap�s a recep��o do sinal.

.in -3
.ep
.in 5
.sp
Estes indicadores podem ser combinados atrav�s do operador "|"
("ou" bit a bit).

.sp
Em sua configura��o inicial a entrada de texto de todas as janelas
� ecoada, editada por linha e converte <cr> em <nl>.

.sp
.in 0
.b
INTERA��O COM O USU�RIO
.r
.in 5
Nesta se��o est�o descritos todos os caracteres
que t�m significado especial para a entrada de teclado da "curses".
Alguns destes caracteres s�o usados para edi��o por linha
e os outros para gerar sinais para o programa.
O nome que acompanha a explica��o de cada caractere
� o nome atrav�s do qual ele pode ser alterado pelo comando "stty" (cmd).

.sp
O modo de entrada editada proporciona ao usu�rio algumas facilidades
para corrigir erros de digita��o em uma linha ainda n�o terminada.
A edi��o � comandada pelos caracteres de edi��o (descritos abaixo);
os outros caracteres s�o simplesmente inseridos ou escritos
na posi��o apontada pelo cursor.

.sp
Os caracteres de edi��o n�o s�o ecoados,
mas seus efeitos s�o percebidos instantaneamente pelo usu�rio
atrav�s do movimento do cursor
e/ou da altera��o da linha no v�deo do terminal.
Um caractere de edi��o perde seu significado
quando precedido do caractere <^V>.
Os caracteres de edi��o s�o apresentados a seguir:

.in +3
.ip "\"erase\":" 10
Este caractere remove o caractere imediatamente � esquerda do cursor.

.ip "\"aerase\":" 10
Este caractere � uma alternativa ao caractere "erase".

.ip "\"word\":" 10
Este caractere remove a palavra imediatamente � esquerda do cursor.
Uma palavra � definida como uma sequ�ncia de caracteres
que n�o contenha <sp> nem <ht>.

.ip "\"kill\":" 10
Este caractere remove toda a linha teclada at� o momento.

.ip "\"retype\":" 10
Este caractere reescreve a janela corrente no terminal.
Ele � util quando processos executando em "background"
enviam mensagens ao v�deo que interferem na apresenta��o da linha em edi��o.

.ip "\"eol\":" 10
Caractere alternativo para indicar fim de linha.
Este caractere n�o � ecoado.
Retorna a constante predefinida "EOL".

.ip "\"eof\":" 10
Mais um
caractere alternativo para indicar fim de linha.
Este caractere, no entanto, � ecoado.
Retorna a constante predefinida "EOT".

.ip "\"switch\":" 10
Este caractere causa uma chamada a uma rotina
previamente definida pelo programador.
Ao final da execu��o desta rotina, a edi��o prossegue normalmente.
O caractere "switch" pode ser usado para indicar que o usu�rio
deseja interagir com outra janela.

.ep
.in -3

.sp
Os caracteres a seguir geram sinais.
A cada tipo de sinal est� associado uma a��o padr�o sobre o programa,
entretanto, atrav�s da chamada ao sistema "signal" (sys),
um sinal pode ser ignorado ou interceptado.

.in +3
.ip "\"intr\":" 10
Este caractere gera um sinal de interrup��o
("SIGINT").
Normalmente, o programa termina  ao
receber  este  sinal.
                    
.ip "\"quit\":" 10
Este  caractere  gera  um   sinal   de   "quit"
("SIGQUIT").
Normalmente,  o programa termina com a
grava��o  da  imagem  do  processo   no   disco
("core-dump")  ao  receber este sinal.

.in -3
.ep
.in
.sp
.b OBSERVA��ES
.in 5
Por sua pr�pria natureza,
os sinais s�o considerados eventos ou elementos para intera��o
com o programa como um todo.
Consequentemente os sinais s�o sempre gerados
quando seus caracteres correspondentes s�o teclados
e o comportamento do programa ao receb�-los
(padr�o, ignoramento ou intercepta��o)
n�o pode ser definido de forma independente para cada janela.

.sp
A prepara��o para a recep��o dos sinais (via "signal" (sys))
deve ser feita antes do in�cio das atividades de "curses"
(veja "incurses" (curses)).

.sp
O controle  de "start/stop" da sa�da
� realizado automaticamente pelo n�cleo do sistema.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):   "
stty
.br
.wo "(sys):   "
ioctl
.br
.wo "(curses):"
waddch, wgetch, winsch, waddset, wattrset, wrefset
.br
.wo "(fmt):   "
termio
.br

.in
.sp
.b EXEMPLOS
.in 5
A chamada a seguir reestabelece a configura��o inicial de entrada
na janela padr�o:
.sp
.in 10
wgetset (stdwin, G_ECHO|G_TONL|G_EDIT);


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
