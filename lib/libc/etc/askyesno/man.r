.bp
.he 'ASKYESNO (libc)'TROPIX: Manual de Refer�ncia'ASKYESNO (libc)'
.fo 'Atualizado em 18.10.98'Vers�o 3.1'Pag. %'

.b NOME
.in 5
.wo "askyesno -"
obt�m uma resposta afirmativa ou negativa
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int		askyesno (void);
void		askyesno_set (int mode);

extern FILE	*askyesno_stdin, *askyesno_stderr;
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "askyesno" consulta o usu�rio de um utilit�rio interativo
para saber se ele deseja (ou n�o) realizar uma certa opera��o.

.sp
A fun��o tem 2 modos de opera��o: o modo "regular" e o modo "de for�a".
Inicialmente descreveremos o modo "regular" (no qual a fun��o inicia).

.sp 2
Em seu modo "regular", a fun��o l� uma linha (normalmente de "stdin",
veja abaixo) e devolve o valor:

.in +3
.ip " 1" 5
Resposta afirmativa:
caso o primeiro caractere da linha seja "s", "S", "y" ou "Y".

.ip " 0" 5
Resposta indefinida:
caso a linha esteja vazia
(isto �, o usu�rio teclou apenas um <nl>).

.ip "-1" 5
Resposta negativa:
caso o primeiro caractere da linha seja "n" ou "N".

.ep
.in -3

.sp 2
Em seu modo "de for�a", a fun��o "askyesno" faz distin��o entre
as letras min�sculas e mai�sculas.
Enquanto forem dadas letras apenas min�sculas, ela se porta como
em seu modo "regular" (veja acima).

.sp
No momento em que for dada uma linha come�ando por uma letra mai�scula,
isto �, come�ando por "S", "Y" ou "N", t�das as perguntas seguintes
ser�o respondidas automaticamente. As respostas ser�o afirmativas
caso tenha sido dado um "S" ou "Y" e negativas no caso de um "N".


.sp 2
A fun��o "askyesno_set" altera o modo de funcionamento de "askyesno",
de acordo com o seu argumento "mode":

.in +3
.ip "0" 5
A fun��o "askyesno" entra em seu modo "regular" de funcionamento. As letras
ma�sculas e min�sculas t�m o mesmo significado.

.ip "1" 5
A fun��o "askyesno" entra em seu modo "de for�a" de funcionamento.
As letras ma�sculas t�m significado especial, como descrito acima.
Se a fun��o "askyesno" j� estava no modo "de for�a",
a resposta autom�tica � cancelada (e s� ser� restabelecida caso
seja dada novamente uma letra mai�scula).

.ep
.in -3

.sp
Normalmente, a fun��o "askyesno" l� de "stdin" e escreve em "stderr".
Para alterar os dispositivos de entrada/sa�da, basta alterar os
valores das vari�veis externas "askyesno_stdin" e/ou "askyesno_stderr".

.in
.sp
.b OBSERVA��ES
.in 5
Antes de ler a linha, a fun��o "askyesno" descarrega a �rea de sa�da de
"askyesno_stderr", para garantir a impress�o da pergunta
(j� que ela em geral N�O termina por "\n").
Portanto � importante atualizar o valor de "askyesno_stderr",  caso
a pergunta n�o seja escrita atrav�s de "stderr".

.sp
Se for teclada uma linha come�ando por caracteres distintos dos
discutidos acima, "askyesno" ir� pedir outra linha.

.sp
Se a fun��o "askyesno" n�o conseguir ler nenhuma linha
(erro de leitura em "askyesno_stdin"), ela retorna o valor 0.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fflush
.br

.(t
.in
.sp
.b EXEMPLO
.in 7
No exemplo abaixo, uma resposta indefinida (linha em branco) ser�
interpretada como indica��o para n�o remover o arquivo. 

.sp
.nf
		fprintf (stderr, "Deseja remover o arquivo? (n): ");

		/* O "fflush (stderr)" � realizado por "askyesno" */

		if (askyesno () > 0)
		{
			/*
			 *	Remove o arquivo
			 */
		}
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
