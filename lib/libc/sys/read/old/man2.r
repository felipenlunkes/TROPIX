.bp
.he 'SIGREAD (sys)'TROPIX: Manual de Refer�ncia'SIGREAD (sys)'
.fo 'Escrito em 25.09.90'Vers�o 2.3'Pag. %'

.b NOME
.in 5
sigread - leitura ass�ncrona
.sp
.br

.in
.sp
.b DESCRI��O
.in 5
Atrav�s do sinal SIGREAD (veja "signal" (sys)) � poss�vel
ler assincronamente de v�rias linhas de comunica��o simultaneamente.

.sp
Isto � feito atrav�s dos seguintes passos (acompanhe no exemplo):

.in +3
.ip 1. 3
O programa usa a chamada ao sistema "signal" para indicar uma fun��o
interceptadora para o sinal SIGREAD.

.ip 2. 3
Em seguida, ele abre as linhas com o indicador "O_SIGREAD" (veja "open" (sys)).

.ip 3. 3
O programa pode agora esperar atrav�s de "pause" (sys),
"sleep" (libc) ou executar outras tarefas.

.ip 4. 3
Assim que houverem dados dispon�veis em uma ou mais linhas,
� enviado o sinal SIGREAD para o programa, quando ent�o
ser� chamada a fun��o interceptadora com dois argumentos.
O primeiro argumento � o pr�prio n�mero do sinal SIGREAD
e o segundo � o descritor de arquivos referente � linha de comunica��es
com os dados dispon�veis.

.ip 5. 3
A fun��o inteceptadora l� a linha (cujo descritor de arquivos foi dado).

.ip 6. 3
A fun��o interceptadora, antes de retornar, deve reinicializar a
intercepta��o atrav�s de um novo "signal".

.ip 7. 3
Ap�s o sinal, o programa retorna ao ponto onde estava; 
se estava suspenso em virtude de uma chamada ao sistema "pause" ou "sleep",
ele retorna desta chamada.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
Mesmo que v�rias linhas recebam dados simultaneamente,  
a fun��o interceptadora ser� chamada uma vez para cada linha com
dados dispon�veis.

.sp
Uma vez aberta uma linha com o indicador "O_SIGREAD", ser� enviado
um sinal toda vez que ela receber novos dados.
Se isto n�o for mais desejado, pode-se usar "signal" para ignorar
o sinal, ou ent�o fechar a linha.
Lembre-se que um sinal n�o ignorado nem interceptado causa o t�rmino
do programa.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open, read, signal, pause
.br
.wo "(libc):"
sleep
.br

.in
.sp
.(t
.b EXEMPLO
.nf
	#include <signal.h>
	#include <fcntl.h>
	
	void	readfunction ();
	
	main (....)
	{
		int	fd1, fd2, ...;
	
		...........................

		signal (SIGREAD, readfunction);
	
		if ((fd1 = open (linha1, O_RDONLY|O_SIGREAD)) < 0)
			......................
	
		if ((fd2 = open (linha2, O_RDONLY|O_SIGREAD)) < 0)
			......................
	
		...........................
	
		for (;;)
		{
			pause ();
		}
	}
	
	void
	readfunction (signo, fd)
	int signo, fd;
	{
		char	area[128];
		int	n;
	
		if ((n = read (fd, area, 128)) < 0)
			......................
	
		printf ("Mensagem da linha do descritor \%d:", fd);
		write (1, area, n);
	
		signal (SIGREAD, readfunction);
	}
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
