.bp 1
.he 'PWENT (libc)'TROPIX: Manual de Refer�ncia'PWENT (libc)'
.fo 'Atualizado em 07.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Leitura do arquivo de contas/senhas:
.sp
.nf
     getpwent  - obt�m a entrada seguinte do arquivo
     setpwent  - prepara a releitura do arquivo
     endpwent  - conclui a leitura do arquivo
     getpwuid  - obt�m a entrada do usu�rio de n�mero dado
     getpwnam  - obt�m a entrada do usu�rio de nome dado
     pwcache   - obt�m rapidamente o nome do usu�rio 
     getpwpos  - obt�m a posi��o do ponteiro do arquivo
     getpwslot - obt�m o n�mero da linha no arquivo
.fi
.in

.sp
.b SINTAXE
.(l
#include <sys/types.h>
#include <pwd.h>

PASSWD	*getpwent (void);
void	setpwent (void);
void	endpwent (void);
PASSWD	*getpwuid (int uid);
PASSWD	*getpwnam (const char *name);
char	*pwcache (int uid);
off_t	getpwpos (void);
int	getpwslot (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getpwent" fornece, a cada chamada,
uma entrada do arquivo de contas/senhas
("/etc/passwd"), no formato da estrutura "PASSWD". Com sucessivas
chamadas a esta fun��o, pode-se ler sequencialmente todo o arquivo.

.sp
A fun��o "setpwent" prepara o arquivo para que seja feita uma nova leitura.
N�o � necess�rio cham�-la para o primeiro processamento.

.sp
A fun��o "endpwent" encerra o processamento do arquivo.

.sp
A fun��o "getpwuid" procura no arquivo a entrada com
o n�mero do usu�rio dado,
e "getpwnam" a entrada com o nome do usu�rio dado
(n�o � necess�rio chamar "setpwent").

.sp
A fun��o "pwcache" fornece o nome do usu�rio, dado o seu n�mero,
mantendo uma lista interna de todos os nomes j� fornecidos.
Atrav�s desta lista, � capaz de fornecer rapidamente nomes
j� pedidos anteriormente.

.sp
A fun��o "getpwpos" fornece a posi��o corrente do ponteiro do arquivo
de contas/senhas.

.sp
A fun��o "getpwslot" fornece o n�mero da linha do arquivo de
contas/senhas (come�ando de 0) correspondente �s informa��es
fornecidas por uma chamada a uma das
fun��es "getpwent",  "getpwuid" ou  "getpwnam".

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "getpwent" retorna um ponteiro para a estrutura PASSWD contendo
a entrada seguinte do arquivo. No caso de final do arquivo,
ela devolve um ponteiro NULO. 
.)t

.sp
As fun��es "getpwuid", "getpwnam" e "pwcache"
devolvem ponteiros NULOs, caso a entrada desejada
n�o seja encontrada.

.sp
As fun��es "getpwpos" e "getpwslot" devolvem um n�mero negativo,
caso o arquivo n�o esteja aberto.

.in
.sp
.b OBSERVA��O
.in 5
As fun��es "getpwent", "getpwuid", e "getpwnam"
devolvem ponteiros para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
as fun��es serem chamadas novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (libc): grent, getlogin
     (fmt):  passwd
.fi

.in
.sp
.b ARQUIVOS
.in 5
/etc/passwd

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
