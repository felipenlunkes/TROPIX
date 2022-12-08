.bp
.he 'VA_LIST (libc)'TROPIX: Manual de Refer�ncia'VA_LIST (libc)'
.fo 'Atualizado em 18.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
lista vari�vel de argumentos:
.sp
.wo "va_start -"
inicializa a lista de argumentos
.br
.wo "va_arg   -"
obt�m o argumento seguinte
.br
.wo "va_end   -"
encerra a utiliza��o da lista de argumentos
.br
.wo "va_first -"
obt�m o endere�o do primeiro argumento
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdarg.h>

void	va_start (va_list ap, parmN);
type	va_arg (va_list ap, type);
void	va_end (va_list ap);
void	*va_first (parmN);
.)l

.in
.sp
.b DESCRI��O
.in 5
As macros "va_start", "va_arg", "va_end" e "va_first"
(definidas em <stdarg.h>) possibilitam a elabora��o de uma
fun��o com um n�mero e tipo vari�vel de par�metros.

.sp
Uma fun��o deste tipo tem "N" par�metros antes das retic�ncias ("..."),
que indica o come�o da parte vari�vel. O �ltimo par�metro tem um
papel importante no mecanismo de acesso aos argumentos, e ser� chamado
de "parmN" neste descri��o.

.sp
A macro "va_start" deve ser invocada antes do acesso aos argumentos
da parte vari�vel. Ela inicializa "ap" para o uso subseq��nte por
"va_arg" e "va_end".

.sp
A macro "va_arg" expande em uma express�o que tem o tipo e o valor
do pr�ximo argumento na chamada.
Cada invoca��o de "va_arg" modifica "ap" de tal modo, que os sucessivos
argumentos s�o devolvidos um a um.

.sp
A macro "va_end" executa opera��es para possibilitar o retorno normal
da fun��o que utilizou as macros anteriores.

.sp
Em certos casos, necessitamos apenas o endere�o do primeiro argumento
ap�s "parmN", que � fornecido pela macro "va_first". Neste caso,
n�o precisamos utilizar as macros anteriores.

.in
.sp
.b OBSERVA��ES
.in 5
A macro "va_arg" sup�e que possa ser criado um tipo que � o ponteiro
para o "tipo" dado, apenas acrescentando-se o caractere "*" ao final.
Isto � v�lido para muitos tipos simples (tal como "int" em "int *"),
mas n�o no caso geral. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
vprintf
.br

.in
.sp
.(t
.b EXEMPLO
.in 5
A fun��o "f1" re�ne em um vetor uma lista de argumentos que s�o
ponteiros para cadeias, e em seguida passa o vetor como um �nico
argumento para  fun��o "f2". O n�mero de ponteiros � dado como o
primeiro argumento de "f1". 
.(l

	#include <stdarg.h>

	#define	MAXARGS 31

	void f1 (int n_ptrs, ...)
	{
		register va_list ap;
		register int	ptr_no = 0;
		char		*array[MAXARGS];

		if (n_ptrs > MAXARGS)
			n_ptrs = MAXARGS;

		/* Inicializa "ap" */

		va_start (ap, n_ptrs);

		/* Copia os argumentos no vetor */

		while (ptr_no < n_ptrs)
			array[ptr_no++] = va_arg (ap, char *);

		/* Encerra a opera��o de acesso aos argumentos */ 

		va_end (ap);

		f2 (n_ptrs, array);
	} 
.)l
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
