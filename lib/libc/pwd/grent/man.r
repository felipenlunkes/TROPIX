.bp 1
.he 'GRENT (libc)'TROPIX: Manual de Refer�ncia'GRENT (libc)'
.fo 'Atualizado em 07.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Leitura do arquivo de grupos:
.sp
 getgrent - obt�m a entrada seguinte do arquivo
 setgrent - prepara a releitura do arquivo
 endgrent - conclui a leitura do arquivo
 getgrgid - obt�m a entrada do grupo de n�mero dado
 getgrnam - obt�m a entrada do grupo de nome dado
.br
.wo "grcache  -"
obt�m rapidamente o nome do grupo 

.in
.sp
.b SINTAXE
.(l
#include <sys/types.h>
#include <grp.h>

GROUP	*getgrent (void);
void	setgrent (void);
void	endgrent (void);
GROUP	*getgrgid (int gid)
GROUP	*getgrnam (const char *name)
char 	*grcache (int gid)
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getgrent" fornece, a cada chamada, uma entrada do arquivo de grupos
("/etc/group"), no formato da estrutura "GROUP". Com sucessivas
chamadas a esta fun��o, pode-se ler sequencialmente todo o arquivo.

.sp
A fun��o "setgrent" prepara o arquivo para que seja feita uma nova leitura.
N�o � necess�rio cham�-la para o primeiro processamento.

.sp
A fun��o "endgrent" encerra o processamento do arquivo.

.sp
A fun��o "getgrgid" procura no arquivo a entrada com o n�mero do grupo dado,
e "getgrnam" a entrada com o nome do grupo dado.
.sp

A fun��o "grcache" fornece o nome do grupo, dado o seu n�mero,
mantendo uma lista interna de todos os nomes j� fornecidos.
Atrav�s desta lista, � capaz de fornecer rapidamente nomes
j� pedidos anteriormente.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "getgrent" retorna um ponteiro para a estrutura GROUP contendo
a entrada seguinte do arquivo. No caso de final do arquivo,
ela devolve um ponteiro NULO. 

.sp
As fun��es "getgrgid", "getgrnam" e "grcache"
devolvem ponteiros NULOs, caso a entrada desejada
n�o seja encontrada.

.in
.sp
.b OBSERVA��ES
.in 5
O processamento do membro "gr_mem" N�O est� implementado.
A fun��o "getgrent" devolve sempre um ponteiro NULO.

.sp
A fun��es "getgrent", "getgrgid" e "getgrnam"
devolvem um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
as fun��es serem chamadas novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
pwent
.br
.wo "(fmt): "
group
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/group

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
