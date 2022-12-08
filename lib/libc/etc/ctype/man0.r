.bp 1
.he 'CTYPE (libc)'TROPIX: Manual de Refer�ncia'CTYPE (libc)'
.fo 'Escrito em 01.11.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Macros para a classifica��o de caracteres:
.sp
.wo "isalpha  -"
verifica se � uma letra
.br
.wo "isupper  -"
verifica se � uma letra mai�scula
.br
.wo "islower  -"
verifica se � uma letra min�scula
.br
.wo "isdigit  -"
verifica se � um d�gito decimal
.br
.wo "isxdigit -"
verifica se � um d�gito hexadecimal
.br
.wo "isalnum  -"
verifica se � alfanum�rico
.br
.wo "isspace  -"
verifica se � um espa�o
.br
.wo "ispunct  -"
verifica se � um caractere de pontua��o
.br
.wo "isprint  -"
verifica se pode ser impresso
.br
.wo "isgraph  -"
verifica se tem representa��o gr�fica
.br
.wo "iscntrl  -"
verifica se � um caractere de controle
.br
.wo "isascii  -"
verifica se � um caractere ASCII
.br
.wo "isiso    -"
verifica se � um caractere ISO
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <ctype.h>

int	isalpha (int c);
int	isupper (int c);
int	islower (int c);
int	isdigit (int c);
int	isxdigit (int c);
int	isalnum (int c);
int	isspace (int c);
int	ispunct (int c);
int	isprint (int c);
int	isgraph (int c);
int	iscntrl (int c);
int	isascii (int c);
int	isiso (int c);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas macros classificam caracteres atrav�s de uma tabela de acesso direto.
Cada uma delas � um predicado, retornando um valor n�o nulo para verdadeiro,
e zero para falso.

.sp
As macros "isascii" e "isiso" s�o definidas para todos os valores inteiros.
As demais macros, no entanto s�o apenas definidas para os valores
para os quais "isiso" � verdadeira e mais o valor EOF (isto �, de -1 a 255).
Se o argumento dado para algumas destas macros n�o estiver no seu
dom�nio de defini��o, o resultado ser� imprevis�vel.

.sp
As macros s�o:

.in +3
.ip "isalpha" 12
Verifica se � uma letra. Inclui as letras mai�sculas (0x41-0x5A), letras
min�sculas (0x61-0x7A) e as letras mai�sculas/min�sculas acentuadas
(0xC0 a 0xFF).

.ip "isupper" 12
Verifica se � uma letra mai�scula. Inclui as letras sem acento (0x41-0x5A)
e as letras acentuadas (0xC0 a 0xDE).

.ip "islower" 12
Verifica se � uma letra min�scula. Inclui as letras sem acento (0x61-0x7A)
e as letras acentuadas (0xDF a 0xFF).

.ip "isdigit" 12
Verifica se � um d�gito decimal (0-9).

.ip "isxdigit" 12
Verifica se � um d�gito hexadecimal (0-9, A-F, a-f).

.ip "isalnum" 12
Verifica se � alfanum�rico (letra ou d�gito decimal).

.ip "isspace" 12
Verifica se � um espa�o. Inclui <sp> (0x20): o espa�o normal, <nbsp> (0xA0):
o espa�o "no-break", <ht> (0x09): tabula��o horizontal,
<lf> (0x0A): "new-line", <vt> (0x0B): tabula��o vertical,
<ff> (0x0C): "form-feed" e <cr> (0x0D): "carriage-return".

.ip "ispunct" 12
Verifica se � um caractere de pontua��o, ou seja, que n�o � de controle
nem alfanum�rico. Inclui os caracteres  0x20-0x2F, 0x3A-0x4O, 0x5B-0x60,
0x7B-0x7E e 0x80-0xBF.

.ip "isprint" 12
Verifica se � um caractere poss�vel de ser impresso. Inclui os caracteres
0x20-0x7E e 0x80-0xFF.

.ip "isgraph" 12
Verifica se � um caractere com representa��o gr�fica.
Trata-se de uma variante de "isprint", que exclui <sp> e <nbsp>.
Inclui os caracteres 0x21-0x7E, 0x80-0x9F e 0xA1-0xFF.

.ip "iscntrl" 12
Verifica se � um caractere de controle.
Inclui os caracteres EOF, 0x00-0x1F e 0x7F.

.ip "isascii" 12
Verifica se � um caractere ASCII (um inteiro 0-127).

.ip "isiso  " 12
Verifica se � um caractere ISO (um inteiro 0-255).

.ep
.in -3

.sp
.in
.sp
.b OBSERVA��O
.in 5
O conjunto de caracteres do TROPIX � o c�digo ISO, de 8 bites.

.sp
Repare que "isprint" � exatamente o inverso de "iscntrl".

.sp
O caractere EOF � considerado de controle.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
stdio
.br
.wo "(fmt): "
ascii, iso
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
