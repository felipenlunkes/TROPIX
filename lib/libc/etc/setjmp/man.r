.bp 1
.he 'SETJMP (libc)'TROPIX: Manual de Refer�ncia'SETJMP (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Desvios n�o-locais:
.sp
.wo "setjmp  -"
prepara o desvio
.br
.wo "longjmp -"
executa o desvio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <setjmp.h>

int	setjmp (jmp_buf env);
void	longjmp (jmp_buf env, int val);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es s�o utilizadas para o tratamento de erros e interrup��es
em fun��es de baixo n�vel de programas. 

.sp
A fun��o "setjmp" guarda os valores dos registros e o estado da
pilha de execu��o em "env" para posterior uso de "longjmp".
Se o retorno � de uma chamada direta a "setjmp", ela retorna o
valor zero. Se o retorno � de uma chamada � fun��o "longjmp"
(ver adiante), a fun��o "setjmp" retorna um valor n�o-nulo.

.sp
A fun��o "longjmp" restaura os valores dos registros e o estado da
pilha de execu��o, que foram salvos pela �ltima chamada a "setjmp" com o
mesmo argumento "env".
Se n�o houve esta chamada a "setjmp", ou se a fun��o contendo a chamada
a "setjmp" j� retornou neste interim, o resultado ser� imprevis�vel.
Ap�s a execu��o de "longjmp", o programa
continua como se o "setjmp" correspondente tivesse retornado o valor "val".

.sp
A fun��o "longjmp" n�o pode causar "setjmp" retornar zero.
Se "longjmp" for chamado com "val" igual a zero, "setjmp" retornar� o valor um.

.in
.sp
.b OBSERVA��ES
.in 5
No instante do segundo retorno de "setjmp", todas as vari�veis ter�o os
valores do momento em que "longjmp" foi chamada, exceto as vari�veis
autom�ticas alocadas em registros. Estas vari�veis ter�o os valores
do momento em que "setjmp" foi chamada (veja o exemplo).

.sp
Um modo de impedir que uma vari�vel autom�tica seja alocada em um
registro � atrav�s do uso do atributo "volatile".
Repare que o compilador n�o garante que vari�veis com o atributo
"register" seja efetivamente alocadas em registros.

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (sys): signal
.fi

.in
.(t
.sp
.b EXEMPLO
.br
.in 5
Estamos supondo que a presen�a/aus�ncia do atributo "register"
seja levada em conta:
.sp
.nf
	#include <setjmp.h>

	jmp_buf		env;

	int		g = 0;

	main (...)
	{
		int		s = 0;
		register int 	r = 0;

		if (setjmp (env) != 0)
		{
			printf
			(	"Segundo retorno, "
				"g = \%d, s = \%d, r = \%d\n",
				g, s, r
			);
			exit (0);
		}

		printf
		(	"Primeiro retorno, "
			"g = \%d, s = \%d, r = \%d\n",
			g, s, r
		);

		g = s = r = 1;

		sub ();

	}	/* end main */

	sub ()
	{
		longjmp (env, 1);

	}	/* end sub */


   O programa ir� escrever:


	Primeiro retorno, g = 0, s = 0, r = 0
	Segundo retorno,  g = 1, s = 1, r = 0
.fi
.)t


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
