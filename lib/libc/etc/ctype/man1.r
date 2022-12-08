.bp 1
.he 'CONV (libc)'TROPIX: Manual de Refer�ncia'CONV (libc)'
.fo 'Escrito em 20.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Macros para a convers�o de caracteres:
.sp
.in 5
.wo "toupper  -"
converte um caractere min�sculo em mai�sculo
.br
.wo "tolower  -"
converte um caractere mai�sculo em min�sculo
.br
.wo "_toupper -"
converte um caractere para mai�sculo
.br
.wo "_tolower -"
converte um caractere para min�sculo
.br
.wo "toiso    -"
converte um caractere para ISO
.br
.wo "toascii  -"
converte um caractere para ASCII
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <ctype.h>

int	toupper (int c);
int	tolower (int c);
int	_toupper (int c);
int	_tolower (int c);
int	toiso (int c);
int	toascii (int c);
.)l

.in
.sp
.b DESCRI��O
.in 5
A macro "toupper" converte uma letra min�scula na letra mai�scula
correspondente.
Se o argumento dado for ISO, mas n�o for uma letra min�scula,
ele � retornado sem modifica��o.
Se o argumento n�o for ISO, o resultado ser� imprevis�vel.

.sp
A macro "tolower" converte uma letra mai�scula na letra min�scula 
correspondente.
Se o argumento dado for ISO, mas n�o for uma letra mai�scula
ele � retornado sem modifica��o.
Se o argumento n�o for ISO, o resultado ser� imprevis�vel.

.sp
As macros "_toupper" e "_tolower" s�o simplifica��es, respectivamente,
das macros "toupper" e "tolower", sendo mais r�pidas pois n�o testam
o argumento. Se o argumento n�o for, respectivamente,
uma letra min�scula ou uma letra mai�scula, o resultado ser� imprevis�vel.

.sp
.(t
A macro "toiso" zera os bites (8 - 31) de um caractere,
para obter um valor que necessariamente
faz parte do conjunto de caracteres ISO. 
.)t

.sp
A macro "toascii" zera os bites (7 - 31) de um caractere,
para obter um valor que necessariamente
faz parte do conjunto de caracteres ASCII.
Repare que esta macro N�O converte vogais acentuadas do ISO nas
vogais correspondentes sem acento do ASCII.

.in
.sp
.b
OBSERVA��ES
.r
.in 5
O conjunto de caracteres do TROPIX � o c�digo ISO, de 8 bites,
e as vogais acentuadas e o "c�-cedilha" s�o levados em conta
pelas macros "toupper", "tolower", etc ...

.sp
Repare, que existe um (e apenas um) caso em que a macro de convers�o
"toupper" falha: no caso do caractere 0xFF ("y" com trema, do franc�s),
ela fornece 0xDF ("s" forte alem�o), que certamente n�o � o seu
correspondente mai�sculo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.br
.wo "(libc):"
ctype, getc
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
