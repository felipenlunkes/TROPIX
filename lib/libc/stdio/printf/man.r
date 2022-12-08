.bp 1
.he 'PRINTF (libc)'TROPIX: Manual de Refer�ncia'PRINTF (libc)'
.fo 'Atualizado em 01.11.02'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
Formata a sa�da:
.sp
.wo "printf   -"
escreve na sa�da padr�o ("stdout")
.br
.wo "fprintf  -"
escreve no arquivo dado
.br
.wo "sprintf  -"
armazena em um vetor dado
.br
.wo "snprintf -"
armazena em um vetor de tamanho dado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int printf (const char *format, ...);
int fprintf (FILE *fp, const char *format, ...);
int sprintf (char *str, const char *format, ...);
int snprintf (char *str, size_t size, const char *format, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "printf" escreve na sa�da padr�o ("stdout"),
"fprintf" escreve no arquivo identificado pelo ponteiro "fp",
"sprintf" e "snprintf" escrevem a sa�da (seguida de um caractere NULO) no vetor apontado por "str".
A fun��o "snprintf" observa para que o tamanho "size" do vetor n�o seja ultrapassado
(o que n�o � o caso de "sprintf").

.sp
Estas fun��es geram a sa�da sob o contr�le da cadeia de formato apontada
por "format", que especifica como os argumentos subseq��ntes s�o
convertidos. Se forem dados argumentos insuficientes para a cadeia de formato,
o comportamento � imprevis�vel; por outro lado, argumentos em excesso
s�o simplesmente ignorados. As fun��es retornam quando � encontrado
o final da cadeia de formato.

.sp
A cadeia de formato � composta de zero ou mais diretivas:
caracteres regulares (diferentes de "\%"), que s�o copiados
sem altera��o para a sa�da e especifica��es de convers�o,
cada um dos quais utiliza zero ou mais argumentos subseq��ntes.
Cada especificac�o de convers�o � introduzida pelo caractere "\%",
ap�s o qual temos os seguintes itens (na ordem dada):

.in +3
.ip * 2
Zero ou mais "indicadores", que alteram o significado
da especifica��o de convers�o (ver abaixo).

.ip * 2
Uma cadeia decimal opcional especificando o "tamanho de campo" m�nimo.
Se o valor convertido tiver menos caracteres do que o tamanho do campo,
ele ser� completado com brancos (caractere <sp>) do lado esquerdo
(ou direito, ver abaixo) para o tamanho pedido.

.ip * 2
Uma "precis�o" opcional que d� o n�mero m�nimo de d�gitos
para as convers�es "b", "B", "d", "i", "o", "u", "x" e "X",
o n�mero de d�gitos ap�s o ponto decimal para as convers�es "e", "E" e "f",
o n�mero m�ximo de d�gitos significativos para as convers�es "g" e "G", ou
o n�mero m�ximo de caracteres impressos de uma cadeia para a convers�o
"s". A precis�o tem a forma de um ponto (".") seguido de uma
cadeia opcional de d�gitos decimais; se a cadeia for otimida o valor
da precis�o � zero.

.ip * 2
Um tamanho opcional:

.in +2
.ip "h" 3
Um "h" especifica que uma convers�o "b", "B", "d", "i", "o",
"u", "x" ou "X" se refere a um argumento "short int" ou
"unsigned short int" (isto �, s� s�o considerados os 16 bits menos
significativos do argumento).

.sp
Um "h" especifica que uma convers�o "n" se refere
a um ponteiro para um argumento "short int".

.ip "l" 3
Um "l" especifica que uma convers�o "b", "B", "d", "i", "o",
"u", "x" ou "X" se refere a um argumento "long int" ou
"unsigned long int".

.sp
Um "l" especifica que uma convers�o "n" se refere
a um ponteiro para um argumento "long int".

.ip "L" 3
Um "L" especifica que uma convers�o "e", "E", "f",
"g" ou "G" se refere a um argumento "long double";

.ip "q" 3
um "q" especifica que uma convers�o "d" ou "u"
se refere a um argumento "long long int" ou "unsigned long long int"
(pode ser usado "ll" no lugar de "q").

.sp
Se um "h", "l", "L" ou "q" for usado com outras convers�es ele ser� ignorado.

.ep
.in -2

.ip * 2
O caractere que indica o tipo da convers�o a ser realizada
(ver abaixo).

.ep
.in -3
.sp
Tanto o tamanho do campo como a precis�o (ou ambos) podem ser indicados
por um asterisco ("*") ao inv�s de uma cadeia de d�gitos.
Neste caso, o tamanho do campo ou a precis�o � fornecido por um
argumento inteiro.
O argumento a ser convertido deve vir ap�s os argumentos referentes
ao tamanho do campo e precis�o. Se o argumento referente ao tamanho
do campo for negativo, ele � interpretado como sendo um indicador "-" seguido
de um tamanho de campo positivo. Se o argumento referente � precis�o
for negativo, ele ser� considerado ausente.

.sp
Os indicadores e os seus significados s�o:

.in +3
.ip - 5
O resultado da convers�o � ajustado � esquerda dentro do campo.

.ip + 5
O resultado de uma convers�o com sinal come�a sempre com um sinal
("+" ou "-").

.ip <sp> 5
Se o primeiro caractere de uma convers�o com sinal n�o � um sinal,
um branco � anteposto ao resultado. Se ambos os indicadores
<sp> e "+" forem dados, o indicador <sp> � ignorado.

.ip # 5
O valor � convertido para uma forma "alternativa".
Para a convers�o "o", a precis�o � aumentada de modo que o
resultado sempre comece por um zero.
Para as convers�es "b", "B", "x" e "X", o resultado � precedido de "0x".
Para as convers�es "p" e "P", o resultado � precedido de "0x",
e � suprimida a separa��o entre os dois grupos de 4 d�gitos hexadecimais.

.ip 0 5
Para as convers�es "b", "B", "d", "i", "o", "u", "x", "X",
"e", "E", "f", "g" e "G" � utilizado o d�gito "0" para ajustar
o campo � esquerda (ap�s o poss�vel sinal) ao inv�s do <sp>.
Se ambos os indicadores "0" e <sp> forem dados, o indicador "0"
� ignorado. Se for dada uma precis�o para uma das convers�es
"b", "B", "d", "i", "o", "u", "x" ou "X", o indicador "0" �
ignorado.

.ep
.in -3

.in 5
.sp
Os caracteres de convers�o e os seus significados s�o:

.in +3
.ip d,i,o,u,x,X 12
O argumento inteiro � convertido para decimal com sinal ("d" ou "i"),
octal sem sinal ("o"), decimal sem sinal ("u"),
hexadecimal sem sinal ("x" ou "X");
as letras "abcdef" s�o usadas para a convers�o "x" e
"ABCDEF" para a convers�o "X".
A precis�o especifica o n�mero m�nimo de d�gitos;
se o valor puder ser representado com menos d�gitos, ser� expandido
com zeros � esquerda. Se a precis�o n�o for dada ser� usado o valor 1.

.ip f 12
O argumento "double" � convertido para a nota��o decimal no estilo
"[-]ddd.ddd", onde o n�mero de d�gitos ap�s o ponto decimal
� dado pela precis�o.
Se a precis�o n�o for  dada, s�o utilizados 6 d�gitos ap�s o ponto decimal;
se a precis�o dada for zero, o ponto decimal � omitido.

.ip e,E 12
O argumento "double" � convertido para a nota��o decimal no estilo
"[-]d.dddesddd", com um d�gito antes do ponto decimal (que � diferente
de zero se o argumento � diferente de zero) e um n�mero de d�gitos
ap�s o ponto decimal que � igual � precis�o; se a precis�o n�o for dada
s�o utilizados 6 d�gitos ap�s o ponto decimal;
se a precis�o dada for zero, o ponto decimal � omitido.
O caractere "s" representa o sinal "+" ou "-" do expoente.
A convers�o "E" gera o n�mero com "E" ao inv�s de "e" introduzindo
o expoente.

.ip g,G 12
O argumento "double" � convertido no estilo "f" ou "e"
(ou "E" no caso de "G"), conforme as descri��es acima.
Se a precis�o dada for zero, � utilizado o valor 1.
O estilo usado depende do valor do argumento:
� usado o estilo "e" se o expoente for menor do que -4 ou maior ou igual
� precis�o. Zeros ao final da parte fracion�ria s�o omitidos;
o ponto decimal � omitido se n�o for seguido de um d�gito.

.ip c 12
O argumento inteiro � convertido para "unsigned char" e escrito.

.ip s 12
O argumento dado deve ser um ponteiro para um vetor de caracteres.
O caracteres do vetor s�o escritos at� (mas n�o incluindo) um
poss�vel caractere NULO indicando o final do vetor.
Se for dada uma precis�o, ela indica o n�mero m�ximo de caracteres
a escrever; se a precis�o n�o for dada ou for maior do que o
vetor, o vetor deve conter um caractere NULO.

.ip p,P 12
O argumento dado deve ser um ponteiro, cujo valor
� convertido para hexadecimal, no formato "XXXX XXXX". 
as letras "abcdef" s�o usadas para a convers�o "p" e
"ABCDEF" para a convers�o "P".
A precis�o (se dada) � ignorada.

.ip n 12
O argumento dado deve ser um ponteiro para um inteiro no qual
� ESCRITO o n�mero de caracteres escritos na sa�da at� este ponto por
esta chamada da fun��o. Esta convers�o n�o produz sa�da.

.ip b,B 12
Esta convers�o espera dois argumentos: o primeiro deve conter um
valor inteiro, que � convertido para hexadecimal no estilo "x"
(ou "X" no caso de "B"), conforme as descri��es acima;
o segundo argumento deve ser um ponteiro para uma cadeia de
caracteres.

.sp
Esta cadeia de caracteres � composta de zero ou mais se��es.
Cada se��o cont�m um caractere inicial com um valor de 1 a 32
(valores de caracteres n�o gr�ficos), indicando um dos
32 bites do primeiro argumento (o valor 1 indica o bite menos
significativo); os caracteres seguintes (gr�ficos) da se��o
d�o uma descri��o deste bite.

.sp
A sa�da produzida � da forma
.wo '"XXX <desc0|desc1|...>",'
onde "XXX" � o valor hexadecimal do primeiro argumento e os v�rios
"desci" s�o as descri��es dos bites iguais a 1 no primeiro argumento,
que s�o obtidas atrav�s da cadeia de caracteres (ver o exemplo abaixo).
A ordem em que as descri��es s�o escritas � dada pela ordem em
que elas est�o na cadeia; se nenhum bite � igual a 1, a descri��o
"<desc0|desc1|...>" � omitida.

.ip \% 12
Escreve o caractere "\%"; nenhum argumento � convertido.
A especifica��o de convers�o completa deve ser "\%\%".

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es "printf", "fprintf", "sprintf" e "snprintf" retornam o
n�mero de caracteres transmitidos 
(n�o incluindo o NULO nos casos de "sprintf" e "snprintf"),
ou um n�mero negativo em caso de erro.

.in
.sp
.(t
.b OBSERVA��ES
.in 5
Em nenhum caso, um tamanho de campo n�o dado ou pequeno ir� causar
o truncamento de um campo; simplesmente o campo ser� aumentado
de modo a nele caber o valor convertido. 
.)t

.sp
No caso da fun��o "sprintf", � de responsabilidade do usu�rio
garantir que o vetor apontado por "str" seja suficientemente grande para receber a sa�da gerada.

.sp
No caso da fun��o "snprintf" � dado o tamanho do vetor atrav�s de "size", e se a sa�da gerada
for maior do que este tamanho, ela � truncada. Esta fun��o � mais segura do
que "sprintf", mas ela n�o pertence ao padr�o ANSI.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
putc, scanf, stdio
.br

.in
.sp
.b EXEMPLO
.in 5
.nf
	O trecho de programa abaixo:

		const char	status_bits[] =
		{
			"\x0C" "Erro de CRC"
			"\x0A" "Setor inv�lido"
			"\x09" "Setor n�o encontrado"
			"\x06" "Prote��o de escrita"
			"\x05" "Cilindro inexistente"
			"\x04" "Erro de DMA"
			"\x03" "Unidade inv�lida"
			"\x01" "Erro irrecuper�vel"
		};

		printf ("\%#0.4B\n", 0x0201, status_bits);

	ir� escrever em <stdout>:

		0x0201 <Setor inv�lido|Erro irrecuper�vel>
.fi

.bc	/*************************************/
Escrever o dia 25 de junho de 1986, quarta-feira �s 9:30h:

	printf
	(	"\%2d:\%02d \%s \%02d/\%02d/\%02d\n",
		hora, min, dia_semana,
		dia, mes, ano
	);

escrever�

	9:30 QUARTA-FEIRA 25/06/85



Escrever PI:

	printf ("PI = \%.5f = \%.5e", 4 * atan (1.0), 4 * atan (1.0));

escrever�

	PI = 3.14159 = 3.14159e+00
.ec	/*************************************/

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
