.bp
.he 'SELECT (sys)'TROPIX: Manual de Refer�ncia'SELECT (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "select -"
multiplexa��o de entrada s�ncrona
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/times.h>
#include <sys/select.h>

int	select (int n, fd_set *read, fd_set *write,
				fd_set *excep, const MUTM *timeout);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "select" examina os conjuntos de descritores de arquivos
cujos endere�os s�o dados em "read", "write" e "excep", para ver se algum
dos descritores est�o prontos para a leitura, escrita, ou se h� alguma
condi��o de erro pendente.

.sp
Os primeiros "n" descritores s�o examinados de cada conjuntos, isto �,
s�o examinados os descritores de n�meros "0" a "n-1" de cada conjunto.
Ap�s o retorno, "select" substitui os conjuntos por subconjuntos contendo
os descritores que est�o prontos para as opera��es correspondentes.
� retornado o n�mero total de descritores prontos de todos os conjuntos.

.sp
Os conjuntos de descritores s�o armazenados em campos de bits de um inteiro.
As segunites macros est�o dispon�veis para a manipula��o destes campos:

.in +3  
.ip "FD_ZERO (&fdset):" 23
Inicializa o conjunto de descritores "fdset" como o conjunto vazio.

.ip "FD_SET (fd, &fdset):" 23
Inclui o descritor "fd" no conjunto "fdset".

.ip "FD_CLR (fd, &fdset):" 23
Remove o descritor "fd" do conjunto "fdset".

.ip "FD_ISSET (fd, &fdset):" 23
Retorna N�O NULO se o descritor "fd" pertence ao conjunto "fdset".

.ep
.in -3  

.sp
Estas macros s� s�o definidas se o valor do descritor for n�o negativo
e menor do que FD_SETSIZE.

.sp
Se "timeout" for um ponteiro N�O NULO, ele especifica um intervalo
m�ximo de tempo para que a chamada a "select" retorne. Se "timeout"
for um ponteiro NULO, a espera ser� ilimitada. Se "timeout" for um
ponteiro apontando para um valor NULO, o retorno ser� imediato
("polling").

.sp
Cada um dos ponteiros "read", "write" ou "excep" pode ser um ponteiro
NULO, se os respectivos descritores n�o forem de interesse.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Normalmente, a chamada ao sistema "select" devolve
o n�mero total de descritores prontos de todos os conjuntos;
em caso de �rro, devolve "-1". Se o limite de tempo for expirado,
devolve "0". Se o valor retornado n�o foi positivo, os conjuntos
de descritores n�o s�o modificados.

.in
.sp
.b OBSERVA��ES
.in 5
A chamada ao sistema "select" N�O est� dispon�vel para todos os dispositivos.
No momento, s� est� implementada para terminais (linhas de comunica��es,
dispositivos "/dev/console", "/dev/tty*", "/dev/video*"),
pseudo-terminais (tanto do lado do cliente como do servidor, 
dispositivos "/dev/ptyc*" e "/dev/ptys*"), na internet (dispositivos
"/dev/udp", "/dev/tcp", "/dev/raw"), arquivos "pipe"
e na espera por um processo filho
terminado (dispositivo "/dev/grave").

.sp
Al�m disto, nesta vers�o, s� est� implementado o conjunto "read".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
attention, open, read, wait, pipe
.br
.wo "(fmt): "
termio
.br
.wo "(xti): "
t_open
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
