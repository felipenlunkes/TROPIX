.bp 1
.he 'REGCMP (libc)'TROPIX: Manual de Refer�ncia'REGCMP (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Processamento de express�es regulares:
.sp
.wo "regcmp -"
compila a express�o
.br
.wo "regex  -"
executa a express�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

char	*regcmp (const char *pattern);
char	*regex (const char *automata,
				const char *str, char *match);
extern char *_loc1;
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "regcmp" compila a express�o regular
dada na cadeia apontada por "pattern"
e retorna um ponteiro para a descri��o do aut�mato gerado.

.sp
A fun��o "regex" executa a descri��o do aut�mato "automata" na cadeia "str".
A sub-cadeia em "str" correspondente � express�o regular "pattern"
� copiada em "match".
A fun��o "regex" retorna um ponteiro para
o pr�ximo caractere em "str" ap�s esta sub-cadeia.

.sp
O ponteiro "_loc1" aponta para o in�cio de "match" em "str".

.sp
Normalmente um caractere da express�o regular corresponde a si pr�prio.
No entanto, os seguintes meta-caracteres t�m significado especial:

.in 10

.ip ^ 4
No in�cio de uma express�o regular, corresponde ao in�cio
da cadeia "str".

.ip $ 4
No final de uma express�o regular, corresponde ao final
da cadeia "str".

.ip . 4
Corresponde a qualquer caractere, exceto <nl>.

.ip [] 4
Uma sequ�ncia n�o vazia de caracteres dentro de um par de colchetes
especifica um conjunto de caracteres,
que corresponde a um caractere pertencente a este conjunto.

.sp
Existem algumas conven��es que simplificam a especifica��o
de um conjunto de caracteres.
Um "-" (menos) entre dois caracteres (em ordem crescente ISO),
na forma "<ch1>-<ch2>",
equivale a todos os caracteres entre <ch1> e <ch2>, inclusive.
Um "^" (acento circunflexo) logo ap�s o colchete esquerdo
indica que o conjunto de caracteres equivalente ser� 
o complemento do conjunto especificado a seguir.

.ip * 4
Corresponde a zero ou mais repeti��es do caractere anterior.

.ip + 4
Corresponde a uma ou mais repeti��es do caractere anterior.

.ip \ 4
Um meta-caractere perde o seu significado especial
se vier precedido do caractere "\" (barra invertida).

.ep
.sp
O reconhecimento de express�es regulares tenta sempre
obter a cadeia mais longa poss�vel.

.in
.sp
.b
DIAGN�STICOS
.r
.in 5
Em caso de erro na cadeia com a express�o regular,
"regcmp" retorna um ponteiro NULO.
.br
.sp
Se o aut�mato n�o puder ser executado,
"regex" retorna um ponteiro NULO.

.in
.sp
.b OBSERVA��O
.in 5
O espa�o de mem�ria necess�rio para armazenar a descri��o do aut�mato
� obtido atrav�s de "malloc" (libc).
Ap�s o uso, o usu�rio (se deseja) pode liberar este espa�o
usando "free" (libc).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
(libc): patmatch, malloc, free

.in
.sp
.b EXEMPLOS
.in 5
O trecho de programa abaixo l� uma linha da entrada padr�o
e caso haja um identificador presente na linha, escreve-o na sa�da padr�o:
.sp
.nf
	char	*automato, linha[128], identificador[128];

		. . .

	automato = regcmp ("[a-zA-Z_][a-zA-Z_0-9]*");

	gets (linha);

	if (regex (automato, linha, identificador) != NULL)
	{
		printf
		(	"Achei o identificador: '%s'\n",
			identificador
		);
	}
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
