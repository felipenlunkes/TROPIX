.bp 1
.he 'MODETOSTR (libc)'TROPIX: Manual de Refer�ncia'MODETOSTR (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
modetostr - obt�m a forma simb�lica do modo de um arquivo

.in
.sp
.b SINTAXE
.(l
#include <stdlib.h>

char	*modetostr (long mode);
.)l

.in
.sp
.b DESCRI��O
.in 5
O argumento "mode" � o modo de um arquivo 
tal como obtido de uma chamada
ao sistema "stat" ou "fstat" (ver "stat" (sys)).
A fun��o "modetostr" converte o modo de um arquivo 
de sua forma interna para uma forma simb�lica.

.sp
A fun��o devolve um ponteiro para uma cadeia de 23 caracteres
da forma
.nf

		"R 7654321mtsg rwxrwxrwx".

.fi

.bc	/*************************************/
onde cada caractere (exceto o primeiro) corresponde a um indicador do modo.
.sp
.ec	/*************************************/

O primeiro caractere indica o tipo de arquivo:
"B" para um dispositivo especial de blocos (estruturado),
"C" para um dispositivo especial de caracteres (n�o estruturado),
"D" para um diret�rio, "F" para um "fifo", "R" para um arquivo regular
e "?" para um arquivo de tipo inv�lido.

.sp
O segundo caractere � branco. H� ent�o 11 
caracteres relativos aos atributos, mais um branco
e 9 caracteres com o modo de prote��o do arquivo.
Se o indicador estiver desligado, o caracter assume o valor '-'
ao inv�s do caracter indicado acima.
Para informa��es sobre os diversos indicadores do modo,
veja "chmod" (sys).

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "modetostr" devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso
ele seja necess�rio ap�s a fun��o ser chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chmod, ls
.br
.wo "(sys): "
stat, chmod
.br

.in
.sp
.b EXEMPLO
.r
.in 5
Uma chamada para "modetostr" poder� retornar:
.br
.nf

		"R -------m-s- rwxr-x--x"

.fi
o que significa que se trata de um arquivo regular,
com permiss�o para leitura, escrita e execu��o para o dono,
leitura e execu��o para os usu�rios do mesmo grupo
e de execu��o para os outros usu�rios, e com os atributos "set user ID"
e "salva a imagem do processo na mem�ria, mesmo sem usu�rios".

.in
.sp
.b ESTADO
.in 5
Efetivo.
