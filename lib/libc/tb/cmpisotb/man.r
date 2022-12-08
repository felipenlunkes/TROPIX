.bp
.he 'CMPTB (libc)'TROPIX: Manual de Refer�ncia'CMPTB (libc)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Tabelas de compara��o de caracteres:
.sp
.wo "cmpisotb   -"
tabela para ordena��o de caracteres ISO
.br
.wo "cmpfoldtb  -"
tabela mapeando mai�sculas em min�sculas ("FOLD")
.br
.wo "cmpafoldtb -"
tabela adicional para desempate da "FOLD"
.br
.wo "cmpdictb   -"
tabela onde n�o alfanum�ricos s�o brancos

.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

extern const char	cmpisotb[];
extern const char	cmpfoldtb[];
extern const char	cmpafoldtb[];
extern const char	cmpdictb[];
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas tabelas s�o usadas para compara��o de caracteres quando a
ordem desejada n�o coincide com aquela dada pelo c�digo no qual
os caracteres est�o representados.
Elas podem ser usadas com as fun��es da s�rie "str" tais como
"strtcmp", "strttcmp", "strntcmp", "strnttcmp" e suas an�logas
da s�rie "mem", tais como "memtcmp" e "memttcmp" (libc).

.sp
A tabela "cmpisotb" mapeia todos os caracteres acentuados
em caracteres sem acento, segundo a defini��o do
c�digo ISO.

.sp
A tabela "cmpfoldtb" mapeia todos os caracteres 
mai�sculos em seus respectivos min�sculos.

.sp
A tabela "cmpfoldatb" serve para o desempate no caso de
igualdade quando se utiliza a tabela "cmpfoldtb". Ela
faz com que as letras min�sculas sejam consideradas de
valor menor que as mai�sculas, i.e., as letras min�sculas
ser�o listadas antes das mai�sculas numa classifica��o
ascendente.

.sp
A tabela "cmpdictb" mapeia todos os caracteres que n�o
s�o alfanum�ricos em <sp>. Isto � utilizado para obter a ordem
utilizada em dicion�rios, onde a pontua��o n�o influi na ordena��o
das palavras.

.in
.sp
.b OBSERVA��O
.in 5
Todas as tabelas assumem um c�digo de representa��o de
caracteres contendo 8 bits. Desta forma, todas elas tem
um tamanho de 256 bytes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sort
.br
.wo "(libc):"
strtcmp, strntcmp, strttcmp, strnttcmp, memtcmp,
.br
.wo "        memttcmp"
.br

.in
.sp
.(t
.b EXEMPLO
.in 7
.sp
.nf
	#include <string.h>

	main ()
	{
		char	 	*s1, *s2;
		const char	*tab1, *tab2;
		int	 	i;

		tab1 = cmpfoldtb;
		tab2 = cmpafoldtb;
		. . . . . .

		i = strttcmp (s1, s2, tab1, tab2);
	}


.fi
.)t

A igualdade das cadeias "s1" e "s2" ser� analisada
utilizando-se uma tabela que n�o diferencia letras
mai�sculas de min�sculas. Se a compara��o usando
a tabela "tab1" der igual, usa-se "tab2", onde as
letras min�sculas precedem as mai�sculas numa
classifica��o ascendente.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
