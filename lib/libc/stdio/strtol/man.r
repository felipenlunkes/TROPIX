.bp 1
.he 'STRTOL (libc)'TROPIX: Manual de Refer�ncia'STRTOL (libc)'
.fo 'Atualizado em 11.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Convers�o de cadeias em inteiros:
.sp
.wo "strtol  -"
cadeias em qualquer base num�rica
.br
.wo "strtuol -"
cadeias em qualquer base num�rica (sem sinal)
.br
.wo "atol    -"
cadeias decimais em longos
.br
.wo "atoi    -"
cadeias decimais em inteiros
.br

.in
.sp
.b SINTAXE
.in 5
.(l
long		strtol (const char *str, const char **ptr,
						int base);
unsigned long	strtoul (const char *str, const char **ptr,
						int base);
long		atol (const char *str);
int		atoi (const char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "strtol" retorna como um inteiro longo o valor representado
pela cadeia de caracteres apontada por "str". A cadeia � percorrida
at� o primeiro caracter inconsistente com a "base" dada.
Caracteres brancos e tabula��es (<ht>) antes do in�cio do n�mero s�o ignorados.

.sp
Se o valor de "ptr" n�o for NULO, um ponteiro para o primeiro caracter
ap�s o n�mero reconhecido � armazenado na posi��o apontada por "ptr". 
Se nenhum inteiro p�de ser obtido, a fun��o devolve zero.

.sp
Se a "base" � positiva (e n�o maior do que 36), ela � usada como
base para a convers�o. Ap�s um sinal opcional, zeros � esquerda
s�o ignorados, e "0x" ou "OX" � ignorado se a base for 16.
Os d�gitos acima de 9 s�o representados pelas letras mai�sculas
ou min�sculas: "A" para 10, "B" para 11, ......, "Z" para 35.

.sp
Se a "base" � zero, a base � determinada pela pr�pria cadeia
utilizado as conven��es da linguagem "C":
ap�s um sinal opcional, um zero determina convers�o octal,
e "0x" ou "0X" determina convers�o hexadecimal. Em outros casos,
ser� utilizada convers�o decimal. 

.sp
A fun��o "strtoul" � an�loga � "strtol", por�m devolve um valor
"unsigned long".

.sp
A chamada "atol (str)" � equivalente a
.sp
.nf
		"strtol (str, (char **)0, 10)",
.fi

.sp
e a chamada "atoi (str)" � equivalente a
.sp
.nf
		"(int)strtol (str, (char **)0, 10)".
.fi

.(t
.in
.sp
.b OBSERVA��ES
.in 5
Condi��es de "overflow" s�o ignoradas.

.sp
Como no TROPIX os inteiros s�o sempre longos (32 bits), as fun��es
"atol" e "atoi" s�o identicas.
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
ctype, scanf, strtod
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
