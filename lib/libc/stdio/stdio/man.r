.bp 1
.he 'STDIO (libc)'TROPIX: Manual de Refer�ncia'STDIO (libc)'
.fo 'Atualizado em 11.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
stdio - pacote padr�o de fun��es de E/S para o usu�rio

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

FILE	*stdin, *stdout, *stderr;
.)l

.in
.sp
.b DESCRI��O
.in 5
A "stdio" constitui um pacote eficiente de fun��es de entrada/sa�da
gerenciando �reas intermedi�rias para serem usadas a n�vel de usu�rio.

.sp
As macros "getc" e "putc" l�em/escrevem caracteres rapidamente.
As macros "getchar" e "putchar", e as fun��es "fgetc", "fgets", "fngets",
"fprintf", "fputc", "fread", "fscanf", "fwrite", "gets", "getw",
"printf", "puts", "putw", e "scanf" s�o todas baseadas em "getc" e "putc";
elas podem todas serem usadas no mesmo arquivo aberto.

.sp
Um arquivo utilizando as facilidades deste pacote � identificado
por um ponteiro para uma estrutura do tipo FILE.
A fun��o "fopen" cria certos dados para o arquivo e devolve
um ponteiro para identifica-lo em t�das  as transa��es seguintes.

.sp
Normalmente, existem 3 arquivos abertos com ponteiros constantes
definidos em <stdio.h>, e associados com os 3 arquivos padr�o:
.sp
.nf
	"stdin"		arquivo padr�o de entrada
	"stdout"	arquivo padr�o de sa�da
	"stderr"	arquivo padr�o de mensagens de erro
.fi
.sp
Um ponteiro NULO ("NOFILE") identifica um ponteiro inexistente.

.sp
A constante inteira EOF (-1) � devolvida em condi��o de
fim-de-arquivo ou erro pela maioria das fun��es inteiras que
trata dos arquivos (veja maiores detalhes nas descri��es
individuais).

.sp
A constante inteira "BUFSIZ" define o tamanho das �rea de entrada/sa�da
usadas pela implementa��o em particular.

.sp
Qualquer programa que utiliza este pacote necessita incluir
o arquivo <stdio.h>. As fun��es e constantes relativas a
este pacote est�o declaradas neste arquivo, e n�o necessitam
de declara��es adicionais. As constantes e as seguintes
fun��es s�o implementadas como macros, e n�o podem ser
redeclaradas: "getc", "getchar", "putc", "putchar", "ferror",
"feof", "clearerr" e "fileno".

.sp
Arquivos de sa�da possuem normalmente �reas de entrada/sa�da regulares
se est�o associados a um arquivo em disco e �reas de entrada/sa�da de
linha se est�o associados a um terminal.

As fun��es "setbuf" e "setvbuf" podem ser usadas para mudar
esta estrat�gia de �reas de entrada/sa�da (inclusive N�O usar
�rea de entrada/sa�da); nas suas descri��es se encontram maiores detalhes.

.sp
Quando um arquivo n�o possui �rea de entrada/sa�da, a informa��o � posta
imediatamente no terminal ou no arquivo em disco, assim que ela � escrita;
com uma �rea de entrada/sa�da regular, muitos caracteres s�o
guardados e  escritos como um bloco quando a �rea estiver cheia;
com uma �rea de entrada/sa�da de linha, cada linha da sa�da � posta
no terminal assim que a linha for terminada, isto �, assim que o <nl>
for escrito, ou se a �rea estiver cheia.

.in
.sp
.b DIAGN�STICOS
.in 5
Ponteiros FILE inv�lidos em geral causam erros graves, incluindo
a termina��o do programa. As descri��es individuais das
fun��es d�o detalhes das poss�veis condi��es de erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open, close, lseek, pipe, read, write
.br
.wo "(libc):"
fclose, ferror, fopen, fread, fseek, getc, gets,
.br
.nf
             popen, printf, putc, puts, scanf, setbuf, system,
             ungetc
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
