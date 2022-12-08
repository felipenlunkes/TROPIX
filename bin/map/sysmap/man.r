.bp
.he 'SYSMAP (cmd)'TROPIX: Manual de Refer�ncia'SYSMAP (cmd)'
.fo 'Atualizado em 23.01.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "sysmap -"
desenha um mapa de uso de alguns recursos do sistema
.br

.in
.sp
.b SINTAXE
.in 5
.(l
sysmap [-v] [-d <display>] [-D <desktop>] [-g <geometria>]
					[-f <frente>] [-b <fundo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio gr�fico "sysmap" desenha um mapa do uso de alguns recursos do sistema.
Para cada recurso � desenhada uma barra representando a percentagem de seu uso.

.sp
Os recursos s�o:

.in +3
.ip "1. CPU:" 11
A utiliza��o da CPU durante o �ltimo segundo.

.ip "2. HD/SD:" 11
A utiliza��o dos discos r�gidos durante o �ltimo segundo.

.ip "3. CPU:" 11
A utiliza��o da mem�ria.

.ip "4. ETHER:" 11
A utiliza��o do dispositivo de "ethernet" ("/dev/ed?" e "/dev/fed?") durante o �ltimo segundo.

.ip "5. PPPIN:" 11
A utiliza��o da dispositivo de entrada de pacotes PPP ("/dev/ppp???") durante o �ltimo segundo.

.ip "6. PPPOUT:" 11
A utiliza��o da dispositivo de sa�da de pacotes PPP ("/dev/ppp???") durante o �ltimo segundo.

.ip "7. DIRTY:" 11
Porcentual de �reas do "cache" de dispositivos estruturados
ainda N�O atualizados.

.ip "8. HIT:" 11
Porcentual de acerto do "cache" de dispositivos estruturados durante o �ltimo minuto.

.ip "9. INODE:" 11
Porcentual de uso da tabela de INODEs (n�s-�ndice) de arquivos.

.ep
.in -3

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
