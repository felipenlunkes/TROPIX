.bp
.he 'SBWAVE (cmd)'TROPIX: Manual de Refer�ncia'SBWAVE (cmd)'
.fo 'Atualizado em 23.5.98'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "sbwave -"
toca m�sica PCM atrav�s da placa de som SB-16
.br

.in
.sp
.b SINTAXE
.in 5
.(l
sbwave [-vdt] <arquivo> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "sbwave" executa as m�sicas PCM dadas nos <arquivo>s
atrav�s da placa de som "Sound Blaster 16" ou sucessoras
("AWE-32", "AWE-64", ...).

.sp
Os arquivos devem estar no formato "wave"
(como por exemplo os arquivos "*.wav" do padr�o da Microsoft).

.sp
Se a interface gr�fica X-Window estiver ativa, � aberta uma janela
contendo 3 linhas:

.in +3
.ip "Linha 1:" 9
Cont�m o nome do arquivo em execu��o
e as suas caracter�sticas
(isto �, Mono/Stereo, Freq�encia de amostragem, No. de bits de cada
amostra e o Tamanho do arquivo).

.ip "Linha 2:" 9
Nesta linha � desenhada
uma barra crescente acompanhando a execu��o do arquivo.

.ip "Linha 3:" 9
Cont�m os tempos na forma
"mm:ss:cc", onde "mm" representam os minutos, "ss" os segundos e
"cc" cent�simos de segundo, correspondentes � barra da segunda linha.

.ep
.in -3

.sp
As op��es do comando s�o:

.in +3
.ip -v
Fornece algumas informa��es sobre cada uma dos <arquivo>s.

.ip -d
N�o executa, apenas fornece as informa��es
sobre cada um dos <arquivo>s,
no formato da linha 1, acima.

.ip -t
Usa o modo de texto (isto �, N�O gr�fico), mesmo que
a interface gr�fica X-Window esteja ativa.

.ep
.in -3

.sp 2
Se voc� tiver Win95/Win98 instalado em seu computador, voc� pode
obter algumas amostras de arquivos "*.wav", usando o programa
"dosmp" para copiar arquivos do diret�rio "\WINDOWS\MEDIA".
N�o esque�a de usar o modo "bin�rio".

.in
.sp
.b OBSERVA��O
.in 5
Na presente vers�o, o TROPIX somente aceita placas de som com
interface digital (DSP) de 16 bits. Observe, durante a carga
do sistema operacional, qual o modelo da sua placa de som, e se
o TROPIX a reconhece/aceita.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
dosmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
