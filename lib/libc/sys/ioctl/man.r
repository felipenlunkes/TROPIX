.bp
.he 'IOCTL (sys)'TROPIX: Manual de Refer�ncia'IOCTL (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "ioctl -"
controla dispositivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	ioctl (int fd, int cmd, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "ioctl" efetua uma s�rie de controles em
dispositivos de blocos (estruturados) ou de caracteres (n�o estrurados).
Estes controles s�o normalmente dependentes do dispositivo em quest�o.

.sp
O Argumento "fd" � um descritor de um arquivo aberto, que se refere
ao dispositivo desejado.
O argumento "cmd" seleciona a fun��o de controle
a ser executada no dispositivo.

.sp
Dependendo da fun��o de controle e do tipo de dispositivo podem 
ser necess�rios argumentos e/ou arquivos de inclus�o adicionais.
Por exemplo, para linhas de comunica��o, a chamada "ioctl" toma a
forma (ver "termio" (fmt)):

.(l

		#include <sys/types.h>
		#include <sys/syscall.h>

		#include <termio.h>

		int	ioctl (int fd, int cmd, TERMIO *tp);

.)l

Como outro exemplo, para determinar se um dispositivo �
uma fita magn�tica, a chamada "ioctl" toma a
forma (ver <sys/ioctl.h>):

.(l

		#include <sys/ioctl.h>
		#include <sys/syscall.h>

		int	ioctl (int fd, MTISATAPE);

.)l

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve um valor que depende
da fun��o de controle e do dispositivo, mas sempre � um valor positivo. 
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(fmt): "
termio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
