.bp
.he 'MODETOSTR (LIBC)'TROPIX: Manual de Modifica��es'MODETOSTR (LIBC)'
.fo 'Atualizado em 22.6.87'Vers�o 1.0'Pag. %'

.b NOME
.in 5
.wo "modetostr -"
obt�m a forma simb�lica de modo um arquivo.
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "22.06.87  1.0.1" 20
Foi adaptado para mostrar os 8 novos bites do modo.
Agora s�o tamb�m mostrados os bites "m" (mant�m o texto na mem�ria),
e os provis�riamente chamados de 1, 2, 3, 4, 5, 6 e 7, mas ainda
com funcionalidade indefinida. A cadeia de caracteres cujo ponteiro
� retornado agora tem 23 caracteres. Eles s�o o tipo de arquivo(1),
os atributos(11) e o modo de prote��o(9), separados por espa�os
em branco.

.in
.sp 2
.ip "01.01.88  1.1" 20
VERS�O CORRENTE
.sp
