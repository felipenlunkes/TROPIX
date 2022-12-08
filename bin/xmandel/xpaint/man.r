.bp
.he 'XPAINT (xwin)'TROPIX: Manual de Refer�ncia'XPAINT (xwin)'
.fo 'Escrito em 17.04.03'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
xpaint - exibe imagens em uma janela X-Window.

.in
.sp
.b SINTAXE
.in 5
xpaint [op��es] <arquivo> ...

.in
.sp
.b DESCRI��O
.in 5
O cliente "xpaint" permite visualizar, em uma janela, imagens nos seguintes
formatos: GIF, JPEG, BMP e XPM (um formato pr�prio do X-Window).
.sp

Os <arquivo>s especificados podem ser regulares ou diret�rios.
No primeiro caso, devem conter as imagens a serem visualizadas.
Sempre que um diret�rio � dado, a sub�rvore por ele enraizada �
percorrida � procura de arquivos que contenham imagens.
.sp

Se o nome de um arquivo possuir a extens�o correspondente ao formato
(".gif", "jpg", ".bmp" ou ".xpm"), o "xpaint" assumir� que a imagem
contida no arquivo possui o formato especificado; caso contr�rio, tentar�
descobrir o formato, analisando o arquivo.
.sp

H� tamb�m a possibilidade de mostrar a seq��ncia em "slideshow",
especificando o intervalo de tempo entre exibi��es consecutivas.
.sp

.in 5
As op��es dispon�veis s�o as seguintes:
.in 8

.ip "-d <display>" 20
especifica o servidor X a contactar. Por omiss�o, assume-se o servidor local.

.ip "-f <fator>" 20
especifica o fator de escala a utilizar. Valores para amplia��o:
"2", "3", ..., "8". Valores para redu��o: "1/2", "1/3", "1/4", ..., "1/8".

.ip "-N" 20
os <arquivo>s, em vez de mencionados como argumentos do programa,
s�o lidos da entrada padr�o.

.ip "-R" 20
dentre os arquivos encontrados, seleciona um aleatoriamente e
usa a imagem nele contida como fundo da janela-m�e (RootWindow).

.ip "-s <tempo>" 20
especifica o intervalo de <tempo> segundos entre exibi��es consecutivas.

.ip "-v" 20
imprime, na janela de texto onde o "xpaint" foi invocado, informa��es sobre
as imagens sendo mostradas.
.ep
.sp
.sp

.in
.b
NAVEGA��O
.r
.in 5
Sempre que v�rios arquivos contendo imagens forem encontrados,
o usu�rio ter� a op��o de navegar pela seq��ncia de imagens,
utilizando as setas e algumas teclas especiais:

.in 8
.ip "Seta para cima" 20
retrocede � imagem anterior

.ip "Seta para baixo" 20
passa � imagem seguinte

.ip "Seta para esquerda" 20
reduz o fator de escala, na seq��ncia "1", "1/2", "1/3", ..., "1/8",
diminuindo a imagem corrente

.ip "Seta para direita" 20
aumenta em uma unidade o fator de escala, ampliando a imagem corrente

.ip "Home" 20
volta � primeira imagem

.ip "End" 20
passa � �ltima imagem

.ip "Esc" 20
encerra a navega��o
.ep
.sp

.in
.b
OBSERVA��ES
.r
.in 5
A altera��o do fator de escala durante a exibi��o de uma imagem �
preservada em exibi��es subseq�entes da mesma imagem.
.sp

Imagens no formato XPM s�o imunes a fatores de escala, s� podendo
ser exibidas em tamanho natural.
.sp

Se o intervalo de tempo entre imagens for especificado (veja op��o "-s"),
ainda assim o usu�rio poder� utilizar as teclas de navega��o. A �nica
diferen�a � que, expirado o tempo mencionado, a transi��o para a imagem
seguinte far-se-� automaticamente.
.sp

.in
.b
VEJA TAMB�M
.r
.in 5
.wo "(xwin): "
X, fvwm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
