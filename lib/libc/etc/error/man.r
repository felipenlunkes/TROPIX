.bp
.he 'ERROR (libc)'TROPIX: Manual de Refer�ncia'ERROR (libc)'
.fo 'Atualizado em 14.03.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "error -"
Imprime uma mensagem de erro
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void		error (const char *format, ...);

const char  	*error_default_text;
void		(*error_default_function) (int);
int		error_default_value;
int		error_standard_count;
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "error" imprime a mensagem de erro "format" na sa�da padr�o
de mensagens de erro ("stderr"). A cadeia "format" pode conter especifica��es
de convers�o ("\%..."), conforme as conven��es de "printf" (libc).

.sp
Se o primeiro caractere de "format" for "$",
ap�s a impress�o da mensagem (sem o "$"),
ser� chamada a fun��o "error_default_function"
com o argumento "error_default_value"
(cujos valores iniciais s�o a fun��o "exit" (sys) e "1").
Isto significa que, normalmente, o caractere inicial "$" ir� causar
o t�rmino do programa.

.bc	/*************************************/
O valor inicial de "error_default_function" � a fun��o "exit" (sys),
e o valor inicial de "error_default_value" � "1".
Isto significa que, normalmente, 
(o que normalmente ir� causar o t�rmino do programa, veja abaixo).
.ec	/*************************************/

.sp
Se o caractere seguinte for "*", � adicionada ao final do texto,
entre par�ntesis, a
mensagem de erro (relativa �s chamadas ao sistema) eventualmente presente
na vari�vel global "errno" (veja "strerror" (libc)).

.sp
Se o caractere seguinte for "@", a vari�vel "error_standard_count" �
incrementada de 1. Isto � �til para obter o n�mero total de erros ocorridos
de certa classe (que s�o indicados atrav�s de um "@" na mensagem).

.sp
Finalmente, um caractere <nl> � automaticamente anexado ao final de "format".

.sp
Se o argumento "format" for um ponteiro NULO, ser� utilizada a cadeia
"error_default_text", cujo valor inicial � "$Mem�ria esgotada",
ou seja, o programa ser� encerrado ap�s a impress�o do texto "Mem�ria esgotada".

.sp
As 3 primeiras vari�veis globais definidas acima podem ser alteradas,
para configurar o funcionamento de "error" conforme desejado.

.bc	/*************************************/
; os valores iniciais s�o:
.in +3
.ip "1." 3
O valor inicial de "error_default_text", � "$Mem�ria esgotada".

.ip "2." 3
O valor inicial de "error_default_function" � a fun��o "exit" (sys).

.ip "3." 3
O valor inicial de "error_default_value" � "1".

.ep
.in -3
.ec	/*************************************/

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exit
.br
.wo "(libc):"
printf, strerror
.br

.(t
.in
.sp
.b EXEMPLO
.in 7
Se o valor de "file_nm" for "arquivo" e
a vari�vel "errno" contiver o valor EACCES,
.sp
.nf
		error ("*N�o consegui abrir \"\%s\"", file_nm);

.fi

ir� imprimir

.sp
.nf
	 N�o consegui abrir "arquivo" (N�o tem Permiss�o de Acesso)

.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
