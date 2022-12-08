.bp 1
.he 'GETRAND (libc)'TROPIX: Manual de Refer�ncia'GETRAND (libc)'
.fo 'Atualizado em 19.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Gera��o de n�meros pseudo-aleat�rios:
.sp
.wo "getrand -"
gera um n�mero
.br
.wo "setrand -"
inicializa os par�metros do gerador
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

unsigned long getrand (unsigned long num);
void setrand (unsigned long mult, unsigned long incr, int iter);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getrand" gera n�meros pseudo-aleat�rios entre 0 e 4294967295
.wo "(2 ** 32 - 1)."
A cada chamada de "getrand" deve ser fornecido como argumento o
n�mero pseudo-aleat�rio obtido na �ltima chamada. Na primeira
vez pode ser dado um n�mero qualquer (como por exemplo o valor "1").

.sp
A fun��o utiliza o conhecido m�todo congruencial linear,
que utiliza 3 parametros: o multiplicador, o incremento e
o n�mero de itera��es.
Normalmente, os valores utilizados s�o "314159269" para o multiplicador,
"453806245" para o incremento e "1" para o n�mero de itera��es.

.sp
Estes parametros podem ser alterados atrav�s da fun��o "setrand".
Os seus 3 argumentos correspondem aos 3 parametros do m�todo:
"mult" para o multiplicador, "incr" para o incremento e "iter" para o
n�mero de itera��es.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A cada chamada, "getrand" retorna o pr�ximo n�mero pseudo-aleat�rio.

.in
.sp
.b OBSERVA��O
.in 5
Estas fun��es fazem a multiplica��o, soma, truncamento
e controle do n�mero das itera��es em tempo m�nimo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
crypt
.br
.wo "(libc):"
rand, crypt
.br

.(t
.in
.b EXEMPLO
.in 7
.sp
A fun��o "rand" da "libc" � aproximadamente a seguinte:
.sp
.nf
	#define	MULT	314159269
	#define	INCR	453806245

	static long	seed;

	void
	srand (long a)
	{
		setrand (MULT, INCR, 1);
		seed = a;
	}

	long
	rand (void)
	{
		seed = getrand (seed);
		return (seed & 0x7FFFFFFF);
	}
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
