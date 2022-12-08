.bp 1
.he 'FOPEN (libc)'TROPIX: Manual de Refer�ncia'FOPEN (libc)'
.fo 'Atualizado em 08.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es para abertura de arquivos:
.sp
.wo "fopen    -"
abre um arquivo dado o nome
.br
.wo "freopen  -"
reabre um arquivo antigo 
.br
.wo "fdopen   -"
abre um arquivo dado o descritor
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

FILE *fopen (const char *nome, const char *modo);
FILE *freopen (const char *nome, const char *modo, FILE *fp);
FILE *fdopen (int fd, const char *modo);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "fopen" abre o arquivo cujo nome � dado em "nome", e
retorna um ponteiro para a estrutura FILE associada ao arquivo.

.sp
O argumento "modo" � um ponteiro para uma cadeia de caracteres
que define como o arquivo deve ser aberto.
Ela deve ter um dos seguintes valores:

.in +5
.ip '"r", "rb"' 20
abre para leitura.
.ip '"w", "wb"' 20
abre truncando ou cria o arquivo para escrita.
.ip '"a", "ab"' 20
acr�scimo: abre para escrita no final do arquivo ou cria para escrita.
.ip '"r+", "r+b", "rb+"' 20
abre para atualiza��o, ou seja, para leitura e escrita.
.ip '"w+", "w+b", "wb+"' 20
abre truncando ou cria o arquivo para atualiza��o.
.ip '"a+", "a+b", "ab+"' 20
acr�scimo: abre ou cria para atualiza��o no final do arquivo.
.ep
.in -5

.sp
A fun��o "freopen" abre o arquivo cujo nome � dado em "nome", e
associa o ponteiro de arquivo "fp" a ele.
O argumento "modo" � similar ao da fun��o "fopen" visto acima.
Se o ponteiro de arquivo "fp" dado apontava para um arquivo aberto,
ele � fechado antes da associa��o.
Esta fun��o � normalmente usada para associar ponteiros de arquivos
j� abertos como "stdin", "stdout" e "stderr" a outros arquivos.

.sp
A fun��o "fdopen" associa um ponteiro de arquivo a um descritor de arquivo.
Descritores de arquivos s�o obtidos atrav�s das chamadas ao sistema
"open", "dup", "creat", "fcntl", ou "pipe" (sys),
que abrem o arquivo mas n�o retornam um ponteiro de arquivo e sim
um descritor de arquivos. O argumento "modo"
deve coincidir com o modo do arquivo aberto.

.sp
Quando um arquivo � aberto para atualiza��o, opera��es
tanto de entrada como de sa�da podem ser realizadas no arquivo.
No entanto, uma opera��o de sa�da n�o pode ser
seguida diretamente de uma opera��o de entrada sem que um 
"fseek" ou um "rewind" (libc)
tenha sido executado neste meio tempo.
Analogamente, uma opera��o de entrada n�o pode ser 
seguida diretamente de uma opera��o de sa�da sem que um
"fseek" ou um "rewind"
tenha sido executado neste meio tempo,
ou que a opera��o de entrada
tenha encontrado o final do arquivo (EOF).

.sp
Quando um arquivo � aberto para "acr�scimo" (isto �, quando o
"modo" for  "a", "a+", "ab+" ou "a+b"), � imposs�vel reescrever informa��es
j� presentes no arquivo.
A fun��o "fseek" pode ser usada para alterar o ponteiro do
arquivo para qualquer posi��o no arquivo, mas quando h� uma escrita no
arquivo, o ponteiro de arquivo corrente � ignorado e todas
as escritas s�o feitas no final do arquivo.

.sp
Caso dois processos distintos
abram o mesmo arquivo para "acr�scimo", cada processo pode escrever livremente
no arquivo sem que um processo destrua os dados escritos
pelo outro processo.
A sa�da dos dois processos ser�o misturadas no arquivo, na ordem
em que eles os escrevem.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es "fopen", "freopen" e "fdopen" 
retornam um ponteiro NULO caso haja algum erro.
Neste caso, a vari�vel externa "errno"
contem a raz�o do erro.

.in
.sp
.b OBSERVA��O
.in 5
Repare que no sistema TROPIX, o caractere "b" do modo de abertura
de um arquivo n�o � relevante, j� que n�o h� distin��o entre
arquivos de textos ou bin�rios.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
creat, dup, open, pipe
.br
.wo "(libc):"
fclose, fseek, stdio, perror, strerror
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
