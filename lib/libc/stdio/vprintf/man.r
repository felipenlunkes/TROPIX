.bp
.he 'VPRINTF (libc)'TROPIX: Manual de Refer�ncia'VPRINTF (libc)'
.fo 'Atualizado em 09.09.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
Formata a sa�da (com lista vari�vel de argumentos):
.sp
.wo "vprintf   -"
escreve na sa�da padr�o
.br
.wo "vfprintf  -"
escreve no arquivo dado
.br
.wo "vsprintf  -"
armazena em um vetor dado
.br
.wo "vsnprintf -"
armazena em um vetor de tamanho dado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdarg.h>
#include <stdio.h>

int   vprintf (const char *format, va_list arg);
int   vfprintf (FILE *fp, const char *format, va_list arg);
int   vsprintf (char *str, const char *format, va_list arg);
int   vsnprintf (char *str, size_t size, const char *format,
						va_list arg);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "vprintf", "vfprintf", "vsprintf" e "vsnprintf", s�o equivalentes
respectivamente �s fun��es "printf", "fprintf", "sprintf", "snprintf",
com a lista vari�vel de argumentos substitu�da por "arg", que
foi inicializado pela macro "va_start" (e poss�veis chamadas a "va_arg").
Nenhuma das fun��es "vprintf", "vfprintf", "vsprintf" e "vsnprintf" invoca
a macro "va_end".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es "vprintf" e "vfprintf" retornam o
n�mero de caracteres escritos no arquivo, ou um valor negativo
caso tenha ocorrido um erro de sa�da.

.sp
As fun��es "vsprintf" e "vsnprintf" retornam o
n�mero de caracteres escritos no vetor, sem contar o caracter NULO.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
printf, va_list
.br

.in
.sp
.(t
.b EXEMPLO
.in 5
O exemplo abaixo mostra o uso de "vfprintf" em uma fun��o de
emiss�o de mensagens gen�ricas de erro.
.sp
.nf
	#include <stdarg.h>
	#include <stdio.h>

	void error (char *name, char *format, ...)
	{
		register va_list args;

		/* Inicializa "args" */

		va_start (args, format);

		/* Imprime o nome da fun��o com o erro */

		fprintf (stderr, "ERRO na fun��o \"\%s\": ", name);

		/* Imprime o resto da mensagem */

		vfprintf (stderr, format, args);

		va_end (args);
	}
.fi
.)t
.nf

     que pode ser chamada como

	error ("soma", "valor inv�lido: \%d\n", valor);

     ou

	error
	(	"soma",
		"valores inv�lidos: \%d, \%d, \%d\n",
		valor1, valor2, valor3
	);
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
