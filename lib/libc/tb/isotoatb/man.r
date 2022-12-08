.bp
.he 'CVTB (libc)'TROPIX: Manual de Refer�ncia'CVTB (libc)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Tabelas de convers�es de caracteres:
.sp
.wo "isotoatb   -"
tabela para convers�o de ISO para ASCII 
.br
.wo "isotoabitb -"
tabela para convers�o de ISO para ABICOMP
.br
.wo "isotoisotb -"
tabela para convers�o de ISO para ISO


.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

extern const char	isotoatb[];
extern const char	isotoabitb[];
extern const char	isotoisotb[];
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas tabelas s�o usadas para a convers�o de
caracteres de um c�digo para outro.
O c�digo padr�o do TROPIX � o ISO (ver "iso" (fmt)),
mas em certas aplica��es especiais pode tornar-se
necess�rio o processamento de informa��es em outros c�digos.

.sp
A tabela "isotoatb" converte o c�digo ISO para ASCII.
Como o c�digo ISO cont�m 256 caracteres e o ASCII apenas 128,
esta convers�o n�o � biun�voca.
As letras acentuadas s�o mapeadas nas letras correspondentes sem acento;
alguns caracteres que n�o t�m equivalente exato em ASCII s�o
mapeados em caracteres similares do ASCII quando existe existe
esta possibilidade; em caso contr�rio s�o convertidos em '.'.

.sp
A tabela "isotoabitb" converte o c�digo ISO para ABICOMP.
alguns caracteres que n�o t�m equivalente exato em ABICOMP s�o
mapeados em caracteres similares do ABICOMP quando existe existe
esta possibilidade; em caso contr�rio s�o convertidos em '.'.

.sp
A tabela "isotoisotb" converte o c�digo ISO para ISO, isto �,
n�o realiza convers�o alguma. Ela � �til quando n�o se deseja
relizar nenhuma convers�o, mas no entanto, o caracter deve
passar por uma tabela de convers�o. Isto pode ocorrer durante
a utiliza��o das fun��es da s�rie "str" e "mem" (libc) ou
em algum utilit�rio especial.

.in
.sp
.b OBSERVA��O
.in 5
Todas as tabelas assumem um c�digo de representa��o de
caracteres contendo 8 bits. Desta forma, todas elas tem
um tamanho de 256 bytes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
strtcmp, strntcmp, strttcmp, strnttcmp, memtcmp,
.br
.wo "        memttcmp"
.br
.wo "(fmt): "
iso
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
