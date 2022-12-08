.bp
.sp 4
.nf
     *********************************************************
     *                                                       *
     *                      CAP�TULO 5                       *
     *                                                       *
     *                 EXPRESS�ES REGULARES                  *
     *                                                       *
     *********************************************************
.fi
.sp 4

.pp
O editor "vi" suporta uma forma limitada de express�es regulares.
Elas s�o usadas no modo Comandos,
em endere�os para especificar linhas
e no comando "s" (substitute)
para especificar a parte da linha que ser� substitu�da,
e no modo Visual,
para localiza��o no texto em edi��o.

.pp
Uma express�o regular especifica um conjunto de cadeias de caracteres.
Dizemos que um membro deste conjunto de cadeias
corresponde � express�o regular.
As regras a seguir definem
as express�es regulares aceitas pelo editor:

.in +3
.(t
.ip 1. 4
Qualquer caractere (*) exceto um caractere especial corresponde a si pr�prio.
Caracteres especiais s�o o delimitador da express�o regular
e mais os caracteres "\", "[", "." e em alguns casos "^", "*" e "$".
.)t

.(f
A palavra "caractere"
significa qualquer caractere do conjunto ISO � exce��o do <nl>.
.)f

.(t
.ip 2. 4
Um "\" (barra invertida) seguido de qualquer caractere corresponde
ao pr�prio caractere.
O significado especial dos caracteres especiais
� anulado quando eles s�o precedidos por uma barra invertida.
.)t

.(t
.ip 3. 4
Um "." (ponto) corresponde a qualquer caractere.
.)t

.(t
.ip 4. 4
Uma cadeia n�o vazia "s" entre colchetes "[s]" (ou "[^s]")
corresponde a qualquer caractere presente (ou ausente) em "s".
Uma sub-cadeia na forma "a-b" dentro de "s",
com "a" e "b" em ordem crescente ISO,
significa o conjunto de caracteres ISO entre "a" e "b", inclusive.
Os caracteres "]", "-" e "\" podem ser especificados precedendo-os com "\".
.)t

.(t
.ip 5. 4
Uma express�o regular da forma 1 at� 4 seguido de "*"
corresponde a zero ou mais ocorr�ncias da express�o regular.
.)t

.(t
.ip 6. 4
Uma express�o regular "x" da forma 1 at� 6, seguida
de uma express�o regular "y" da forma 1 at� 5
corresponde a uma ocorr�ncia de "x" seguida de uma ocorr�ncia de "y"
com a correspond�ncia para "x" sendo a mais longa
que permita a correspond�ncia para "y".
.)t

.(t
.ip 7. 4
Uma express�o regular da forma 1 at� 6 precedida por "^"
(ou seguida de "$"),
� restrita a correspond�ncias no in�cio (ou no fim)
de uma linha.
.)t

.(t
.ip 8. 4
Uma express�o regular da forma 1 at� 7 corresponde
� mais longa das correspond�ncias mais � esquerda da linha.
.)t

.(t
.ip 9. 4
Uma express�o regular vazia
equivale a c�pia da �ltima express�o regular procurada.
.)t
.ep
.in -3
