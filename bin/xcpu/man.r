.bp
.he 'XCPU (cmd)'TROPIX: Manual de Refer�ncia'XCPU (cmd)'
.fo 'Atualizado em 21.10.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "xcpu -"
desenha o gr�fico de uso da UCP
.br

.in
.sp
.b SINTAXE
.in 5
.(l
xcpu [-g <geo>] [-f <frente>] [-b <fundo>] [-d <video>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio gr�fico "xcpu" desenha um mapa do uso da Unidade Central de Processamento.

.sp
Cada linha vertical corresponde a um segundo; a sua altura indica o uso da UCP, de
0 a 100 \%. O eixo horizontal corresponde ao tempo, com uma escala em minutos.

.sp
As op��es do comando s�o:

.in +3
.ip "-d <display>" 15
Conecta ao servidor X <display>, ao inv�s do sevidor local.

.ip "-D <desktop>" 15
Inicia no <desktop> dado.

.ip "-g <geometria>" 15
Define o tamanho da janela e a posi��o, no formato "[<dx>x<dy>][+<x>+<y>]";
<dx> e <dy> s�o os tamanhos e <x> e <y> as posi��es (em pixels).

.ip "-f <frente>" 15
Define a cor de frente, no padr�o RGB ou usando os nomes simb�licos do
arquivo "/usr/xwin/conf/rgb.txt".

.ip "-b <fundo>" 15
Define a cor de fundo.

.ip "-v" 15
Verboso.

.ep
.in -3

.sp
Para encerrar o programa, pode-se teclar "q" com o cursor em sua janela.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
