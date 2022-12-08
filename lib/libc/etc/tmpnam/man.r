.bp
.he 'TMPNAM (libc)'TROPIX: Manual de Refer�ncia'TMPNAM (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "tmpnam -"
gera um nome para um arquivo tempor�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

char	*tmpnam (char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "tmpnam" gera uma cadeia de caracteres que � um nome v�lido de um
arquivo, e que n�o � o mesmo de algum arquivo existente.

.sp
Ela gera um nome diferente a cada chamada,
pelo menos nas "TMP_MAX" primeiras chamadas.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se "str" for um ponteiro NULO, a fun��o "tmpnam" gera o nome em um vetor
est�tico interno, e devolve um ponteiro para ele. Chamadas subseq��ntes
a "tmpnam" podem modificar o mesmo vetor.

.sp
Se "str" for um ponteiro n�o NULO, a fun��o "tmpnam" sup�e que aponte
para um vetor de no m�nimo "L_tmpnam" caracteres; ela armazena o nome
do arquivo neste vetor e devolve o pr�prio valor de "str". 

.sp
Se a fun��o n�o conseguir obter um nome de arquivo ainda inexistente,
devolve um ponteiro NULO.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "tmpnam" apenas gera nomes para arquivos tempor�rios,
N�O removendo-os automaticamente ao final do uso.
� necess�rio usar a fun��o "remove" (libc) ou "unlink" (sys) para remove-los.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
mktemp, tmpfile
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
