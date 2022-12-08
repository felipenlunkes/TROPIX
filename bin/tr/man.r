.bp
.he 'TR (cmd)'TROPIX: Manual de Refer�ncia'TR (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "tr -"
traduz caracteres
.br

.in
.sp
.b SINTAXE
.in 5
.(l
tr [-cds] [-1 <cadeia1>] [-2 <cadeia2>] [<entrada> [<sa�da>]] 
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "tr" copia o arquivo de <entrada> para o arquivo de <sa�da>,
com a substitui��o ou remo��o de caracteres selecionados.

.sp
No modo normal (sem a op��o "-d"), os caracteres de entrada
presentes em <cadeia1> s�o substitu�dos pelos caracteres correspondentes
de <cadeia2>.

.sp
Se <sa�da> n�o for dado, "tr" escreve na sa�da padr�o.
Se <entrada> n�o for dado ou for "-", "tr" l� da entrada padr�o.

.sp
As op��es do comando s�o:

.in +3
.ip -c
Complementa o conjunto de caracteres da <cadeia1> em rela��o
ao universo de caracteres ISO, exceto o caractere '\0'.
Em outras palavras, a <cadeia1> efetiva ser� composta de todos os caracteres
ISO (em ordem lexicogr�fica) de 0x01 a 0xFF, menos os dados.

.ip -d
Ao inv�s de substituir, remove os caracteres da <entrada>
presentes na <cadeia1>.

.ip -s
Compacta os caracteres da <sa�da> presentes na <cadeia2>, isto �,
substitui todas as cadeias de caracteres da <sa�da> repetidos  
presentes na <cadeia2> por um �nico exemplar do caractere.

.ep
.in -3

.sp
Para facilitar a defini��o das <cadeia>s, podemos usar as seguintes
abrevia��es:

.in +3
.ip [a-z] 7
Representa a cadeia de caracteres cujos c�digos ISO v�o de "a" a "z".

.ip [a*n] 7
Representa a cadeia de caracteres contendo "n" repeti��es de "a".
O n�mero "n" pode ser dado em decimal, octal ou hexadecimal, de acordo
com as conven��es da linguagem "C" (ver "strtol" (libc)).
Se "n" for ZERO ou n�o for dado, assume-se um valor "enorme";
isto normalmente � usado para completar a <cadeia2> em rela��o ao
universo do c�digo ISO.

.ip \... 7
O caractere "\" pode ser usado para tirar o efeito especial de qualquer
caractere em uma cadeia. Al�m disto podem ser usadas as conven��es da
linguagem "C", tais como "\x34" (hexadecimal), "\123" (octal),
"\n", "\t", etc ...

.ep
.in -3

.in
.sp
.(t
.b OBSERVA��O
.in 5
Todas as combina��es de op��es s�o v�lidas.
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ed, vi
.br
.wo "(libc):"
strtol
.br
.wo "(fmt): "
iso
.br

.in
.sp
.b EXEMPLOS
.in 5
Substitui��o:
.sp
.nf
		tr -1 "abc" -2 "xy"
.fi
.sp
substitui "a" por "x" e "b" por "y" ("c" n�o � modificado).

.sp 2
Substitui��o e compacta��o:
.sp
.nf
	tr -cs -1 "[A-Z][a-z]" -2 "[\n*]" caixas | sort | uniq 
.fi
.sp
Constr�i uma lista de todas as palavras do arquivo "caixas", com
uma palavra por linha (uma palavra � considerada a seq��ncia m�xima
de letras n�o acentuadas). Em seguida, esta lista � ordenada e 
finalmente, as palavras repetidas s�o eliminadas.

.sp 2
Remo��o:
.sp
.nf
		tr -cd -1 "aeiouAEIOU" texto | wc -c
.fi
.sp
imprime o n�mero de vogais (n�o acentuadas) do arquivo "texto".

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
