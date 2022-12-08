.bp
.he 'ENDIAN (libc)'TROPIX: Manual de Refer�ncia'ENDIAN (libc)'
.fo 'Atualizado em 20.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Convers�o da ordem dos bytes ("big/little endian")
.sp
.wo "short_endian_cv -"
de valor de 16 bits
.br
.wo "long_endian_cv -"
de valor de 32 bits
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	short_endian_cv (int);
long	long_endian_cv (long);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es convertem valores de 16 e 32 bits entre os
formatos "big-endian" e "little-endian".

.sp
O formato "big endian" � o que contem os bytes mais significativos
em endere�os de mem�ria mais baixos, enquanto que o "little endian"
contem os bytes mais significativos em endere�os de mem�ria mais altos.

.sp
Repare que as convers�es s�o sim�tricas, isto �
.sp
.nf
		long_endian_cv (long_endian_cv (l)) == l
	e
		short_endian_cv (short_endian_cv (s)) == s
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
