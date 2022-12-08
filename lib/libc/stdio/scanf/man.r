.bp 1
.he 'SCANF (libc)'TROPIX: Manual de Refer�ncia'SCANF (libc)'
.fo 'Atualizado em 25.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Leitura formatada:
.sp
.wo "scanf  -"
da entrada padr�o ("stdin")
.br
.wo "fscanf -"
de um arquivo dado
.br
.wo "sscanf -"
de uma cadeia dada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	scanf (const char *format, ...)
int	fscanf (FILE *fp, const char *format, ...)
int	sscanf (const char *str, const char *format, ...)
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "scanf" l� da entrada padr�o ("stdin"), "fscanf"
l� do arquivo identificado pelo ponteiro "fp", e "sscanf"
l� da cadeia de caracteres apontada por "str".
.bc	/*************************************/
No texto abaixo, para o caso da fun��o "sscanf", o "arquivo" deve
ser entendido como a cadeia "s".
.ec	/*************************************/

.sp
Cada uma destas fun��es l� caracteres da entrada sob o contr�le
da cadeia de formato apontada por "format", que especifica as
seq��ncias de entrada admiss�veis e como elas s�o convertidas
para as atribui��es. Os argumentos subseq�entes a "format" s�o
usados como ponteiros para os objetos a receber as entradas convertidas.
Se forem dados argumentos insuficientes para a cadeia de formato,
o comportamento � imprevis�vel; por outro lado, argumentos em excesso
s�o simplesmente ignorados.

.sp
A cadeia de formato � composta de zero ou mais diretivas:
um ou mais caracteres brancos (conforme "isspace" (libc));
um caractere regular (diferente de "\%"); ou uma especifica��o de convers�o.

.sp
Cada especifica��o de convers�o � introduzida pelo caractere "\%",
ap�s o qual temos (na ordem dada):

.in +3
.ip * 2
Um caractere opcional de supress�o de atribui��o "*".

.ip * 2
Uma cadeia decimal opcional especificando o "tamanho de campo" m�ximo.

.ip * 2
Um "h" opcional especificando que uma convers�o "d", "i" ou "n" se refere
a um argumento que � um ponteiro para um "short int" ao inv�s de "int";
um "h" opcional especificando que uma convers�o "o", "u" ou "x" se refere
a um argumento que � um ponteiro para um "unsigned short int" ao inv�s
de "unsigned int";
um "l" opcional especificando que uma convers�o "d", "i" ou "n" se refere
a um argumento que � um ponteiro para um "long int" ao inv�s de "int";
um "l" opcional especificando que uma convers�o "o", "u" ou "x" se refere
a um argumento que � um ponteiro para um "unsigned long int" ao inv�s
de "unsigned int";
um "l" opcional especificando que uma convers�o "e", "f" ou "g" se refere
a um argumento que � um ponteiro para um "double" ao inv�s de "float";
um "L" opcional especificando que uma convers�o "e", "f" ou "g" se refere
a um argumento que � um ponteiro para um "long double" ao inv�s de "float";

.ip * 2
O caractere que indica o tipo da convers�o a ser realizada
(ver abaixo).

.ep
.in -3
.sp
As diretivas s�o executadas seq�encialmente. Se uma delas falhar,
como descrito abaixo, a fun��o retorna. Falhas s�o classificadas
em falhas de fim-de-arquivo (devido � falta de caracteres de entrada) ou
falhas de formato (devido � entrada inapropriada).

.in +3
.ip * 2
Uma diretiva composta de brancos � executada pela leitura
de caracteres, at� o primeiro caractere n�o-branco (que permanece n�o-lido),
ou at� que seja atingido o final do arquivo.

.ip * 2
Uma diretiva que � um caractere regular � executada pela leitura
de um caractere do arquivo. Se o caractere n�o for igual � pr�pria
diretiva, ela falha, e o caractere que diferiu e os subseq�entes
permanecem n�o-lidos.

.ip * 2
Uma diretiva que � uma especifica��o de convers�o define um conjunto
de seq�encias de entrada admiss�veis, como descritas abaixo para
cada especificador. 
Uma especifica��o de convers�o � executada nos seguintes passos:

.in +3
.ip 1. 3
Caracteres brancos da entrada s�o pulados (conforme "isspace"),
exceto no caso dos especificadores "[", "c" ou "n". 

.ip 2. 3
Um item de entrada � lido, exceto no caso do especificador "n".
Um item de entrada � definido como a seq�encia mais longa de caracteres
de entrada (at� o m�ximo comprimento do campo, se dado), que �
uma subseq�encia inicial aceita pelo formato definido pelo
especificador (as seq��ncias admiss�veis).
O primeiro caractere (se houver) ap�s o item de entrada
permanece n�o-lido. Se o comprimento do item de entrada � zero,
a execu��o da diretiva falha: esta condi��o � uma falha de formato
a n�o ser que n�o havia mais caracteres dispon�veis,
tratando-se ent�o de uma falha de fim-de-arquivo.

.ip 3. 3
Exceto no caso de um especificador "\%", o item de entrada
(ou o n�mero de caracteres j� lidos, no caso da diretiva "\%n") 
� convertido para o tipo apropriado do especificador de convers�o.
Se o item de entrada n�o for uma seq�encia de caracteres admiss�vel,
a execu��o da diretiva falha: esta condi��o � uma falha de formato.
A n�o ser que a supress�o da atribui��o foi indicada por um "*",
o resultado da convers�o � posto no objeto apontado pelo primeiro
argumento seguindo o argumento "formato" que ainda n�o tenha
recebido um resultado. Se este objeto n�o tem o tipo apropriado,
ou se o resultado da convers�o n�o pode ser representado
no espa�o dispon�vel, o comportamento � indefinido.

.ep
.in -3
.in -3
.sp
Os especificadores de convers�o v�lidos s�o os seguintes:

.in +3
.ip d 7
Aceita um inteiro decimal opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtol" (libc) com o valor
"10" para o argumento "base".
O argumento correspondente deve ser um ponteiro para um inteiro.

.ip i 7
Aceita um inteiro opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtol" (libc) com o valor
"0" para o argumento "base".
O argumento correspondente deve ser um ponteiro para um inteiro.

.ip o 7
Aceita um inteiro octal opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtoul" (libc) com o valor
"8" para o argumento "base".
O argumento correspondente deve ser um ponteiro para um inteiro sem sinal.

.ip u 7
Aceita um inteiro decimal opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtoul" (libc) com o valor
"10" para o argumento "base".
O argumento correspondente deve ser um ponteiro para um inteiro sem sinal.

.ip x 7
Aceita um inteiro hexadecimal opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtoul" (libc) com o valor
"16" para o argumento "base".
O argumento correspondente deve ser um ponteiro para um inteiro sem sinal.

.ip e,f,g 7
Aceita um n�mero flutuante opcionalmente com sinal, cujo formato
� o mesmo esperado pela fun��o "strtod" (libc).
O argumento correspondente deve ser um ponteiro para um flutuante.

.ip s 7
Aceita uma seq�encia de caracteres n�o-brancos.
O argumento correspondente deve ser um ponteiro para um
vetor de caracteres com tamanho suficiente para receber
a seq�encia e mais o caractere NULO conclusivo,
que � adicionado automaticamente. 

.ip [ 7
Aceita uma seq�encia n�o vazia de caracteres de um conjunto
de caracteres admiss�veis (o "scanset").
O argumento correspondente deve ser um ponteiro para um
vetor de caracteres com tamanho suficiente para receber
a seq�encia e mais o caractere NULO conclusivo,
que � adicionado automaticamente. 

.sp
A especifica��o de convers�o inclui todos os caracteres subseq�entes
na cadeia do "formato" at� (e incluindo) o "]" final.
Os caracteres entre os colchetes (a "scanlist") comp�e o "scanset",
a n�o ser que o primeiro caractere ap�s o "[" seja um "^", caso no
qual o "scanset" cont�m todos os caracteres que N�O est�o na "scanlist"
(entre o "^" e o "]").

.sp
Em particular, se a especifica��o come�ar por "[]" ou "[^]",
o "]" pertence � "scanlist", e � procurado um outro "]", que ir� indicar
o final da especifica��o.

.sp
Um intervalo de caracteres pode ser representado pela constru��o
<come�o>-<final>: assim "[0123456789]" pode ser expresso por "[0-9]".
Em particular, se a especifica��o come�ar por "[-",  "[]-" ou "[^]-",
o "-" pertence � "scanlist"; este modo deve ser usado para incluir
o "-" na "scanlist" sem indicar uma constru��o <come�o>-<final>.

.ip c 7
Aceita uma seq�encia de "n" caracteres, onde "n" � o tamanho do campo
dado (ou "1", se ele n�o foi dado). 
O argumento correspondente deve ser um ponteiro para um
vetor de caracteres com tamanho suficiente para receber a seq�encia.
N�O � adicionado um caractere NULO ao final.

.ip p 7
Aceita um inteiro hexadecimal (representando o valor de um ponteiro),
cujo formato � o mesmo que � produzido pela convers�o "\%p" ou "\%#p"
da fun��o "printf" (ou seja, "XXXX XXXX" ou "0xXXXXXXXX).
O argumento correspondente deve ser um ponteiro para um ponteiro para "void".

.ip n 7
N�o s�o lidos caracteres da entrada.
O argumento correspondente deve ser um ponteiro para um inteiro,
no qual � armazenado o n�mero de caracteres lidos da entrada
at� este ponto por esta chamada da fun��o.
A execu��o de uma diretiva "\%n" n�o incrementa o contador de atribui��es,
que � devolvido quando do retorno da fun��o.

.ip \% 7
Aceita um �nico "\%"; n�o ocorre nenhuma convers�o nem atribui��o.
A especifica��o completa deve ser "\%\%".

.ep
.in -3
.sp 2
Os especificadores de convers�o "E", "G", "X" e "P" tamb�m s�o aceitos
e s�o equivalentes aos respectivos especificadores min�sculos.

.sp
Se � encontrado um fim-de-arquivo durante a entrada de caracteres,
a convers�o � encerrada. Se isto ocorrer antes de se encontrar
caracteres admiss�veis pela diretiva corrente (al�m de caracteres
brancos, onde permitidos), a execu��o da diretiva corrente termina
com um erro de fim-de-arquivo; em caso contr�rio, a n�o ser
que a diretiva corrente � terminada por um erro de formato, a
execu��o da diretiva seguinte (caso haja) � terminada por
um erro de fim-de-arquivo.

.sp
Se a convers�o termina por um caractere n�o admiss�vel, este caractere
� deixado n�o-lido no arquivo de entrada. Caracteres brancos
(incluindo caracteres <nl>) ap�s o item n�o s�o lidos, a n�o ser
que haja uma diretiva apropriada (por exemplo, um ou mais caracteres brancos).
O sucesso de diretivas literais (caracteres regulares do "formato",
que devem se encontrar literalmente no arquivo) e atribui��es
suprimidas somente pode ser determinado pela diretiva "\%n".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Estas fun��es devolvem o n�mero de �tens que foram lidos e atribu�dos
com sucesso. Este n�mero pode ser menor do que o esperado, ou at� zero,
no caso de uma falha de formato prematura.

.sp
Se ocorrer uma falha de fim-de-arquivo antes de alguma atribui��o,
ou se a cadeia de formato tiver constru��es inv�lidas,
as fun��es devolvem EOF.

.in
.sp
.b OBSERVA��O
.in 5
Repare que "\%E" � equivalente a "\%e" e N�O a "\%le".
O mesmo vale para "\%G" e "\%g".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
isspace, getc, printf, stdio, strtod, strtol, strtoul
.br

.in
.sp
.b EXEMPLOS
.in 5
.(t
A chamada:
.sp
.nf
		#include <stdio.h>
		int i, n; float x; char name[50];
		n = fscanf (stdin, "\%d\%f\%s", &i, &x, name);

.fi
.)t
com a entrada:
.nf

		25  54.32e-1 thompson

.fi
ir� atribuir "3" a "n", "25" a "i", "5.432" a "x" e "thompson"
(com caractere NULO no final) a "name".
.sp 2
A chamada:
.sp
.nf
		#include <stdio.h>
		int i;  float x; char name[50];
		scanf ("\%2d\%f\%*d \%[0123456789]", &i, &x, name);

.fi
.(t
com a entrada:
.nf

		56789 0123 56a72

.fi
.)t
ir� atribuir "56" a "i", "789.0" a "x", ir� pular "0123",
e atribuir "56" (com caractere NULO no final) a "name".
O pr�ximo caractere a ser lido da entrada ser� um "a". 
.sp 2
.(t
Finalmente, para ler repetidamente da entrada padr�o
uma quantidade, um unidade e o nome de um item:
.sp
.nf
	int count; float quant; char units[21], item[21];
	do
	{
	    count = scanf ("\%f\%20s of \%20s", &quant, units, item);
	    scanf ("\%*[^\n]");
	}
	while (count != EOF);

.fi
Se "stdin" contiver as seguintes linhas:
.nf

	2     quarts		of            oil
	-12.8degrees Celsius
	lots of luck
	10.0LBS        of        fertilizer
	100joules       of       energy
	
.fi
.)t
a execu��o do exemplo � equivalente � execu��o das seguintes
atribui��es:
.sp

.nf
+-------+-------+---------+------------+-------------------------+
| count	| quant	| units	  |    item    |	observa��o	 |
+-------+-------+---------+------------+-------------------------+
| 3	| 2.0	| quarts  | oil	       |			 |
| 2	| -12.8	| degrees | -	       | "C" n�o aceito por "o"  |
| 0	| -	| -	  | -	       | "l" n�o aceito por "\%f" |
| 3	| 10.0	| LBS	  | fertilizer |			 |
| 3	| 100.0	| joules  | energy     |			 |
| EOF	|	|	  |	       |			 |
+-------+-------+---------+------------+-------------------------+
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
