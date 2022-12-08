.bp
.he 'MEM (libc)'TROPIX: Manual de Modifica��es'MEM (libc)'
.fo 'Atualizado em 06.07.91'Vers�o 2.3.0'Pag. %'

.b NOME
.in 5
Opera��es com �reas de mem�ria: 
.sp
.wo "memcpy   -"
copia uma �rea de mem�ria
.br
.wo "memmove  -"
c�pia otimizada de uma �rea de mem�ria
.br
.wo "memocpy  -"
c�pia otimizada de uma �rea de mem�ria
.br
.wo "memccpy  -"
copia uma �rea para outra at� encontrar caractere
.br
.wo "memeq    -"
testa a igualdade de duas �reas de mem�ria
.br
.wo "memcmp   -"
compara duas �reas de mem�ria
.br
.wo "memtcmp  -"
compara duas �reas de mem�ria  usando uma tabela
.br
.wo "memttcmp -"
compara duas �reas de mem�ria usando duas tabelas
.br
.wo "memchr   -"
acha a 1a. ocorr�ncia de um caractere
.br
.wo "memset   -"
preenche uma �rea de mem�ria com um caractere
.br
.wo "memsetw  -"
preenche um vetor de palavras com um valor
.br
.wo "memsetl  -"
preenche um vetor de longos com um valor
.br

.in
.sp 2
.ip "17.10.86  1.0.0" 20
VERS�O CORRENTE
.sp

.ip "13.04.91  2.3.1" 20
Nas fun��es "memset", "memcpy", "memcmp", "memeq", "memtcmp", "memttcmp",
"memsetw", "memsetl" e "memmove" foi estendido o "dbra" para funcionar com
32 bites.
