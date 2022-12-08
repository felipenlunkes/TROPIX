.bp 1
.he 'GETC (libc)'TROPIX: Manual de Refer�ncia'GETC (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
L� um caracter ou palavra de um arquivo
.sp
.wo "getc    -"
l� um caracter de um arquivo
.br
.wo "getchar -"
l� um caracter da entrada padr�o ("stdin")
.br
.wo "fgetc   -"
l� um caracter de um arquivo (fun��o)
.br
.wo "getw    -"
l� uma palavra de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
int	getc (FILE *fp);
int	getchar (void);
int	fgetc (FILE *fp);
int	getw (FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A macro "getc" l� um caracter do arquivo de entrada "fp".
O ponteiro da posi��o do arquivo (se definido) � atualizado para o caracter
seguinte.

.sp
A macro  "getchar" � equivalente a "getc (stdin)".

.sp
A fun��o "fgetc" � equivalente �
macro "getc". A fun��o � mais lenta do que a macro, 
mas cada chamada ocupa menos espa�o na mem�ria,
e o seu nome pode ser passado como um argumento
para uma fun��o.

.sp
A fun��o "getw" l� uma palavra (ou seja, um inteiro de 4 bytes)
do arquivo de entrada  "fp". O ponteiro da posi��o do arquivo
(se definido) � atualizado para a palavra seguinte.
A fun��o n�o exige nenhum tipo de alinhamento da palavra.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Estas fun��es retornam a constante EOF na condi��o de final de arquivo
ou em caso de  erro.
Como EOF � um inteiro v�lido, "feof" e "ferror"
devem ser usadas para detetar erros da fun��o "getw".

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "getw" � dependente de implementa��o, pois
nem todas as m�quinas tem o inteiro com 4 bytes, nem a ordem
dos bytes dentro da palavra � padronizada.
Isto significa que um arquivo escrito com "putw" (libc) em um computador
pode n�o ser lido corretamente com "getw" em outro computador.

.sp
Se o valor retornado  pelas fun��es
"getc", "getchar" e "fgetc" for armazenado
em uma vari�vel do tipo "char",
e em seguida comparado com a constante EOF, esta compara��o poder� nunca
ser verdadeira  por problemas de extens�o de sinal.

.sp
� importante lembrar que "getc" e "getchar" s�o macros,
e portanto constru��es do tipo "getc (fp++)" podem n�o produzir
o efeito esperado. Deve-se utilizar "fgetc" para estes casos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
stdio, ferror, fread, gets, putc, scanf, putw
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
