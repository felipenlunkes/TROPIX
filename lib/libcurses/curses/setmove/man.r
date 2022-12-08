.bp
.he 'SETMOVE (curses)'TROPIX: Manual de Refer�ncia'SETMOVE (curses)'
.fo 'Atualizado em 31.08.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.sp
.wo "setmove -"
estabelece a rotina de troca de contexto

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void setmove (void  (*func) ());
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "setmove" permite ao programador especificar
uma rotina a ser chamada quando a posi��o que o cursor ocuparia
n�o est� no v�deo.

.in
.sp
.b OBSERVA��O
.in 5
Se o endere�o fornecido da rotina de troca de contexto � nulo,
a entrada do caractere "switch" � simplesmente ignorada.
Este � o modo inicial de funcionamento.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd)   :"
stty
.br
.wo "(sys)   :"
ioctl
.br
.wo "(curses):"
refset
.br

.in
.sp
.b EXEMPLOS
.in 10
.(l
void	getswitch ();

main (argc, argv)
int	argc;
char	*argv[];
{
	...

	setmove (getswitch);

	...

	incurses (argv[0]);

	...
}

void
getswitch (signal)
int	signal;
{
	...
}
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
