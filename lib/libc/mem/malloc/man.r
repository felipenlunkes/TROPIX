.bp 1
.he 'MALLOC (libc)'TROPIX: Manual de Refer�ncia'MALLOC (libc)'
.fo 'Atualizado em 06.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Aloca��o din�mica de mem�ria:
.sp
.wo "malloc   -"
aloca��o de mem�ria
.br
.wo "free     -"
libera��o de mem�ria
.br
.wo "realloc  -"
realoca��o de mem�ria
.br
.wo "calloc   -"
aloca��o de �rea zerada
.br
.wo "chkalloc -"
teste de consist�ncia
.br
.wo "smalloc  -"
aloca��o r�pida
.br
.wo "sfree    -"
libera��o da aloca��o r�pida
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void	*malloc (size_t size);
void	free (void *ptr);
void	*realloc (void *ptr, size_t newsize);
void	*calloc (size_t n_elem, size_t elem_size);
int	chkalloc (void);

#include <malloc.h>

void	*smalloc (size_t size);
void	sfree (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "malloc" e "free" prov�em um m�todo simples de aloca��o
din�mica de mem�ria.
Quando mem�ria adicional � necess�ria, ela � obtida atrav�s da
chamada ao sistema "brk" (sys), sendo incorporada � se��o
"data" do processo.
Quando esta mem�ria (ou parte dela) � liberada, ela se torna dispon�vel
para futuras aloca��es atrav�s de "malloc" ("realloc", "calloc" ou "smalloc"),
mas n�o � devolvida ao sistema operacional
(isto �, o processo n�o diminui de tamanho).

.sp
A fun��o "malloc" retorna um ponteiro para uma �rea de pelo menos
"size" bytes, j� adequadamente alinhada para qualquer uso.

.sp
A fun��o "free" libera a �rea de endere�o "ptr", que foi
previamente alocada por "malloc" ("realloc" ou "calloc").

.sp
A fun��o "realloc" troca o tamanho da �rea previamente alocada por
"malloc" ("realloc" ou "calloc") apontada por "ptr" para "newsize" bytes
e retorna um ponteiro para a �rea (possivelmente movida).
O conte�do da �rea original permanece inalterado
(at� o menor dos tamanhos novo e velho).

.sp
A fun��o "calloc" aloca uma �rea para um vetor de "n_elem" elementos,
cada um de tamanho "elem_size" bytes.
A �rea alocada � inicializada com ZEROs.

.sp
A fun��o "chkalloc" analisa a consist�ncia da estrutura de dados
manipulada pelas fun��es descritas acima.
Ela emite diagn�sticos na sa�da padr�o de erros ("stderr")
caso hajam inconsist�ncias.

.sp
A macro "smalloc" (juntamente com a fun��o "sfree") forma um sistema
de aloca��o de mem�ria sintonizado para a aloca��o r�pida de muitas
�reas pequenas (at� dezenas de bytes); ela aloca inicialmente uma regi�o
de tamanho m�dio atrav�s de "malloc", e em seguida fornece rapidamente
pequenas �reas cont�guas (dispensando os ponteiros entre as �reas alocadas,
que s�o utilizados por "malloc").

.sp
A macro "smalloc" retorna um ponteiro para uma �rea de pelo
menos "size" bytes, alinhada para qualquer uso.
A fun��o "sfree" libera TODAS as �reas alocadas por "smalloc".

.in
.sp
.(t
.b
VALORES DE RETORNO
.r
.in 5
As fun��es "malloc", "realloc", "calloc" e a macro "smalloc"
retornam um ponteiro NULO quando n�o h� mem�ria dispon�vel suficiente.
.)t

.sp
A fun��o "chkalloc" retorna "0" se n�o encontrar inconsist�ncias
e "-1" em caso contr�rio.

.in
.sp
.b OBSERVA��ES
.in 5
Alterar as �reas fornecidas al�m de seus tamanhos fornecidos, ou chamar
as fun��es "free" ou "realloc" com ponteiros incorretos ir� causar
�rros imprevis�veis.

.sp
A chamada
.sp
.nf
			realloc (NOVOID, newsize)
.fi
.sp
� equivalente a
.sp
.nf
			malloc (newsize).
.fi

.sp
Quando "realloc" retorna NULO, a �rea apontada por "ptr" est� liberada,
e pode estar alterada.

.sp
Repare que �reas alocadas por "smalloc" n�o podem ser argumentos
para "free" e "realloc".
No entanto, �reas liberadas por "free" ou por "sfree" tornam-se
dispon�veis tanto para "malloc" e "realloc" como para "smalloc".

.sp
Lembre-se de que "smalloc" n�o � uma fun��o, mas sim uma macro,
portanto evite constru��es com efeitos colaterais,
tais como "smalloc (size[i++])".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
brk
.br
.wo "(libc):"
alloca
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
