.bp
.he 'XCOREMAP (cmd)'TROPIX: Manual de Refer�ncia'XCOREMAP (cmd)'
.fo 'Atualizado em 14.04.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "xcoremap -"
desenha um mapa de aloca��o da mem�ria
.br

.in
.sp
.b SINTAXE
.in 5
.(l
xcoremap [-d <display>] [-g <geometria>] [-f <frente>]
					[-b <fundo>] [<per�odo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando gr�fico "xcoremap" desenha um mapa de aloca��o da mem�ria interna
do computador.

.sp
O mapa � atualizado cada <per�odo> segundos (1 segundo se o <per�odo>
n�o for dado).

.sp
O mapa cont�m uma coluna � esquerda com o endere�o da mem�ria (em KB)
correspondente ao primeiro quadrado do mapa na linha.
Abaixo do mapa, temos uma linha informando
o n�mero de bytes correspondentes a cada
quadrado do mapa, a mem�ria total dispon�vel para programas do
usu�rio, a parte usada e a percentagem.

.sp
Os significados dos quadrados s�o:

.in +3
.ip Cinza: 10
Regi�es livres da mem�ria.

.ip Vermelho: 10
O texto do n�cleo do TROPIX.

.ip Laranja: 10
As tabelas alocadas pelo n�cleo do TROPIX.

.ip Azul: 10
Programas alocados na mem�ria. Normalmente, os textos
ficam no final da mem�ria e a regi�o de dados e a pilha no come�o.

.ip Verde: 10
Mem�ria alocada para a simula��o dos discos
em mem�ria (dispositivos "/dev/ramd0" e "/dev/ramd1").

.ep
.in -3

.sp
As op��es do comando s�o:

.in +3
.ip "-d <display>" 15
Conecta ao servidor X <display>, ao inv�s do sevidor local.

.ip "-g <geometria>" 15
Define o tamanho da janela e a posi��o, no formato "[<dx>x<dy>][+<x>+<y>]";
<dx> e <dy> s�o os tamanhos e <x> e <y> as posi��es (em pixels).

.ip "-f <frente>" 15
Define a cor de frente, no padr�o RGB ou usando os nomes simb�licos do
arquivo "/usr/xwin/conf/rgb.txt".

.ip "-b <fundo>" 15
Define a cor de fundo.

.ep
.in -3

.sp
Para encerrar o programa, pode-se teclar "q" com o cursor em sua janela.

.in
.sp
.b ESTADO
.in 5
Efetivo.
