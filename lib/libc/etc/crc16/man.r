.bp 1
.he 'CRC16 (libc)'TROPIX: Manual de Refer�ncia'CRC16 (libc)'
.fo 'Atualizado em 20.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es para a gera��o de CRC de 16 bits:
.sp
.wo "crc16    -"
gera o CRC rapidamente
.br
.wo "crc16s   -"
gera o CRC usando pouca mem�ria
.br
.wo "crc1641  -"
gera o CRC (norma V.41) rapidamente
.br
.wo "crc1641s -"
gera o CRC (norma V.41) usando pouca mem�ria

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	crc16 (const void *area, int count);
int	crc16s (const void *area, int count);
int	crc1641 (const void *area, int count);
int	crc1641s (const void *area, int count);
.)l

.in
.sp
.b DESCRI��O
.in 5
Todas estas fun��es calculam um CRC ("Cyclic Redundancy Check") 
de 16 bits para a �rea "area" contendo "count" bytes utilizando o polin�mio
.sp
.nf
		 16    12    5
		x   + x   + x  + 1,
.fi
.sp
padr�o de 16 bits recomendado pela CCITT para transmiss�o de informa��o.

.sp
Nas fun��es "crc16" e "crc16s",
o CRC � definido como o resto da divis�o (m�dulo 2) do conte�do da
mensagem em "area" pelo polin�mio indicado.
As fun��es "crc1641" e "crc1641s" seguem a norma V.41 do CCITT e
o CRC � definido como o resto da divis�o (m�dulo 2) do conte�do da
mensagem em "area" acrescida de 16 bits zero pelo polin�mio indicado.

.sp
As fun��es s�o capazes de detectar todos os erros tipo rajada de
comprimento menor ou igual a 16, detectam 99,997\% dos erros tipo
rajada de 17 bits al�m de todos os erros simples, duplos ou com um n�mero
�mpar de bits errados.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es retornam o CRC calculado (16 bits).

.in
.sp
.b OBSERVA��O
.in 5
As fun��es "crc16" e "crc1641" calculam o CRC indicado de forma bastante
r�pida; elas utilizam uma tabela de 256 entradas para poder
calcular o CRC de cada byte em apenas um passo.

.sp
As fun��es "crc16s" e "crc1641s" n�o s�o t�o r�pidas quanto as fun��es
"crc16" e "crc1641" mas s�o mais curtas. Utilizam uma tabela de apenas
16 entradas e calculam o CRC de cada byte em dois passos.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
