.bp
.he 'ALLOCA (libc)'TROPIX: Manual de Refer�ncia'ALLOCA (libc)'
.fo 'Atualizado em 05.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "alloca  -"
aloca��o de mem�ria na pilha de execu��o do processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void	*alloca (size_t size);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "alloca" retorna um ponteiro para uma �rea de pelo menos
"size" bytes, j� adequadamente alinhada para qualquer uso.
A �rea � alocada na pilha de execu��o do processo, e � automaticamente
desalocada quando a fun��o que chamou "alloca" retorna.
Esta �rea � funcionalmente equivalente a uma vari�vel
local (autom�tica) da fun��o que chamou "alloca". 

.sp
Este modo de aloca��o de mem�ria (na pilha de execu��o do processo)
� diferente do usado nas diversas fun��es
da s�rie "malloc" (libc), que obt�m mem�ria
na �rea de dados do processo atrav�s da chamada ao sistema "sbrk" (sys).

.sp
A aloca��o de mem�ria atrav�s de "alloca" � extremamente r�pida,
e como a �rea � automaticamente
desalocada quando a fun��o que chamou "alloca" retorna,
n�o � necess�ria uma fun��o do tipo "free" (libc).
Dependendo da aplica��o, esta desaloca��o autom�tica pode 
ser vantajosa: n�o h� necessidade de se preocupar com a desaloca��o -
ou desvantajosa: n�o � poss�vel colocar um resultado na �rea alocada
para a utiliza��o global por todas as outras fun��es
(pois a �rea alocada s� � dispon�vel para a fun��o
que chamou "alloca" e as fun��es chamadas por ela).

.in
.sp
.b DIAGN�STICOS
.in 5
Se n�o houver espa�o dispon�vel na pilha de execu��o para a �rea solicitada,
o processo � cancelado ainda durante a execu��o da fun��o "alloca".

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "alloca" JAMAIS deve ser utilizada em um
argumento de outra fun��o, pois neste caso ela altera os ponteiros da
pilha de execu��o justamente durante o empilhamento
dos argumentos. No exemplo abaixo

.sp
.nf
		ret = ftn (alloca (256), 123, 456);
.fi
.sp
os ponteiros da pilha s�o alterados depois que os argumentos
"123" e "456" j� foram empilhados, e portanto a fun��o "ftn"
ser� chamada com argumentos inv�lidos.

.sp
Nunca � demais relembrar que o acesso a itens fora da regi�o
alocada pode causar resultados imprevis�veis, principalmente
tratando-se da pilha de execu��o.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
sbrk
.br
.wo "(libc):"
malloc, free
.br
.)t

.in
.sp
.(t
.b EXEMPLO
.in 5
No exemplo abaixo, mostramos como "alloca" pode ser usada para
a aloca��o de um vetor de tamanho vari�vel, "vetor_var", de "n"
elementos. Repare que o seu uso e desaloca��o s�o similares ao do
vetor de tamanho fixo, "vetor_fixo".
.sp
.nf
	int
	func (int n /* N�mero de elementos do vetor */)
	{
		int	vetor_fixo[10];
		int	*vetor_var;

		vetor_var = alloca (n * sizeof (int));

		......

		vetor_fixo[3] = 5;
		vetor_var[3] = 5;

		......

		return (...);	/* Desaloca os dois vetores */ 

	}	/* end func */
.fi
.)t
.sp

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
