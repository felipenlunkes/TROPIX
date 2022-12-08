.bp
.he 'XMANDEL (cmd)'TROPIX: Manual de Refer�ncia'XMANDEL (cmd)'
.fo 'Atualizado em 23.04.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.(l
xmandel - desenha as imagens fractais de Mandelbrot
.)l

.in
.sp
.b SINTAXE
.in 5
.(l
xmandel [-g <geo>] [-f <frente>] [-b <fundo>] [-d <video>] [-F <f>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O gerador de imagens fractais de Mandelbrot "xmandel" permite
selecionar e desenhar regi�es do conjunto de Mandelbrot.

.sp
Al�m disto, permite escolher o tamanho da imagem e as suas cores.

.sp
As imagens geradas por "xmandel" podem ser salvas em arquivos no formato GIF.

.in
.sp
.b 'DISPOSI��O DAS JANELAS'
.in 5
O programa "xmandel" cont�m (de cima para baixo) as seguintes janelas:

.in +3
.ip 1. 3
Janela de bot�es: op��es (veja abaixo), gera��o da imagem anterior, gera��o da imagem
corrente, gera��o do arquivo GIF e finaliza��o do programa.

.ip 2. 3
Janela de mensagens: Nesta janela s�o escritas 2 tipos de mensagens:

.in +6
.ip a. 3
Mensagens informativas sobre a imagem (com o fundo regular):
coordenadas do centro da imagem (real, imagin�rio), largura da imagem,
tamanho da imagem (em pixeis) e o n�mero de cores utilizadas.

.sp
Na linha seguinte, s�o dadas as coordenadas do cursor.

.ip b. 3
Mensagens de erro (com o fundo vermelho).

.ep
.in -6

.ip 3. 3
Janela da image: Nesta janela � desenhada a regi�o do conjunto de Mandelbrot selecionada.
A imagem inicial tem as coordenadas [-0.75, 0], largura 4.0 e tamanho 640x480.

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
Tamanho da Imagem.

.ip 2. 3
Gradiente das cores:
Durante a gera��o do conjunto de Mandelbrot, � obtido um n�mero associado a cada
ponto do conjunto, ao qual � associada uma cor.
O gradiente das cores permite indicar a velocidade da varia��o das cores 
em rela��o � varia��o dos n�meros.

.ip 3. 3
Brilho das cores:
Permite variar a intensidade das componentes vermelhas (R), verde (G) e azul (B)
das diversas cores associados aos pontos do conjunto.

.ip 4. 3
Ordem das cores:
Permite permutar a ordem das componentes das cores criadas gerando diferentes
palhetas de cores.

.ip 5. 3
Desenha o vetor de cores:
Permite visualizar a palheta de cores em vigor (escolhida atrav�s das op��es acima).

.ip 6. 3
Gera a Imagem:
Id�ntico ao bot�o "Gera a Imagem".

.ip 7. 3
Gera o Arquivo:
Id�ntico ao bot�o "Gera o Arquivo".

.ip 8. 3
Gera��o LZW:
A alternativa "Port�til" produz um arquivo GIF leg�vel por qualquer utilit�rio
gr�fico.

.sp
A alternativa "compacta" produz um arquivo GIF de tamanho menor, mas que possivelmente
n�o possa ser lido por alguns utilit�rios gr�ficos (em particular "Paintshop").

.ip 9. 3
Vers�o: A vers�o do programa "xmandel".

.ep
.in -3


.in
.sp
.b SELE��O DE UM SUBCONJUNTO DA IMAGEM CORRENTE
.in 5
Para definir uma regi�o da imagem corrente e ampli�-la, usamos o "mouse"
do seguinte modo:

.in +3
.ip 1. 3
Para definir o tamanho da regi�o arrastamos o "mouse" com o bot�o da esquerda
pressionado.

.ip 2. 3
Para posicionar a regi�o, arrastamos o "mouse" com o bot�o da direita pressionado.

.in -3
.ep

.sp
Ap�s escolhida convenientemente a regi�o, podemos gerar a imagem ampliada atrav�s
do bot�o "Gera a Imagem".

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

.ip -F
Use a fonte <f> dada.

.ep
.in -3

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
