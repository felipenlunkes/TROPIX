.bp
.he 'ATTENTION (sys)'TROPIX: Manual de Refer�ncia'ATTENTION (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "attention -"
multiplexa��o de entrada s�ncrona
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	attention (int n, const int vector[],
					int index, int timeout);
extern int	_attention_index;
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "attention" examina os "n" descritores de arquivos
do vetor "vector" para ver se algum deles tem dados dispon�veis
(e portanto est� pronto para ser lido).
Cada descritor � obtido por uma das chamadas "creat", "open",
"dup", "fcntl", "pipe" (sys) ou t_open (xti).

.sp
O vetor "vector" dado deve conter "n" descritores
(cujos �ndices s�o "0" a "n - 1").
Os descritores s�o examinados ascendentemente e circularmente
a partir do descritor SEGUINTE ao de �ndice "index".
O valor de "index" dado deve ser de "0" a "n - 1",
ou ainda "-1" (que � equivalente a "n - 1").

.sp
Se no momento da chamada ao sistema um ou mais dos descritores j� tiver dados
dispon�veis, "attention" retorna imediatamente com o �ndice do primeiro
descritor com dados dispon�veis
(encontrado de acordo com a busca circular descrita acima).
A vari�vel "_attention_index" retorna o mesmo �ndice, exceto nos casos
de erro (veja abaixo em VALOR DE RETORNO).

.sp
Em caso contr�rio (isto �, se no momento da chamada ao sistema NENHUM
dos descritores tiver dados dispon�veis), a a��o de "attention" depende
do valor de "timeout", de acordo com os seguintes casos:

.in +3
.ip 1. 3
"timeout" < 0 ("polling"): a chamada ao sistema retorna imediatamente
com o valor "-1", indicando o erro "EINTR" em "errno";

.ip 2. 3
"timeout" == 0 ("espera ilimitada"): a chamada ao sistema retorna
apenas quando um dos descritores passar a ter dados dispon�veis,
e retorna o seu �ndice;

.ip 3. 3
"timeout" > 0 ("espera limitada"): a chamada ao sistema
espera no m�ximo "timeout" segundos - se durante este intervalo de tempo
algum dos descritores passar a ter dados dispon�veis, retorna o seu �ndice.
Em caso contr�rio retorna o valor "-1" indicando o erro "EINTR".

.ep
.in -3

.sp
De acordo com os valores de "index" fornecidos, podemos construir v�rias
estrategias de prioridades.
Assim, por exemplo, se o valor de "index" for:

.in +3
.ip 1. 3
o valor de retorno da �ltima chamada a "attention", daremos prioridades
iguais aos dispositivos, pois a busca ser� iniciada a partir do
descritor seguinte ao que acabou de ser lido;

.ip 2. 3
sempre "-1", daremos prioridade m�xima para o primeiro descritor do vetor,
com prioridades descrescendo � medida que caminhamos para o seu final.

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de dados dispon�veis, a chamada ao sistema "attention" devolve
o �ndice "i" do vetor (de "0" a "n - 1"), de tal modo que "vector[i]"
cont�m o descritor de arquivos com dados dispon�veis.
Este �ndice tamb�m � atribu�do � vari�vel "_attention_index".

.sp
Em caso de um erro associado a um certo descritor de arquivos,
"attention" devolve o valor "-1" e atribui � vari�vel "_attention_index"
o �ndice do vetor contendo o descritor no qual ocorreu o erro.
Em "errno" � indicada a causa do erro.

.sp
Em caso de erros que n�o s�o associados a nenhum descritor de arquivos em
particular, "attention" devolve o valor "-1" e tamb�m
atribui este valor � vari�vel "_attention_index".
Como � usual, em "errno" � indicada a causa do erro.

.sp
No caso de dados n�o dispon�veis imediatamente ("polling") ou ap�s o tempo
esgotado ("espera limitada"), "attention" devolve o valor "-1"
(e atribui este valor � vari�vel "_attention_index")
indicando o erro "EINTR".

.in
.sp
.b OBSERVA��ES
.in 5
A chamada ao sistema "attention" N�O est� dispon�vel para todos os dispositivos.
No momento, s� est� implementada para terminais (linhas de comunica��es,
dispositivos "/dev/console", "/dev/tty*", "/dev/video*"),
pseudo-terminais (tanto do lado do cliente como do servidor, 
dispositivos "/dev/ptyc*" e "/dev/ptys*"), na internet (dispositivos
"/dev/udp", "/dev/tcp", "/dev/raw"), arquivos "pipe"
e na espera por um processo filho
terminado (dispositivo "/dev/grave").

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
select, open, read, wait, pipe
.br
.wo "(fmt): "
termio
.br
.wo "(xti): "
t_open
.br

.in
.sp
.(t
.b EXEMPLO
.in 5
O exemplo abaixo implementa prioridades iguais, e espera indefinida:
.nf

	.................

	#define	N	...	/* N�mero de dispositivos */

	main (....)
	{
		int		fd_vec[N];
		int		fd;
		int		i;
		int		r;

		i = -1;		/* Para o primeiro "attention" */
		...........................

		if ((fd_vec[0] = open (disp0, O_RDONLY)) < 0)
			......................

		if ((fd_vec[1] = open (disp1, O_RDONLY)) < 0)
			......................

		...........................

		for (;;)
		{
			if ((i = attention (N, fd_vec, i, 0)) < 0)
			{
				......................
				fd = fd_vec[_attention_index];
				......................
			}

			fd = fd_vec[i];

			if ((r = read (fd, ..., ...)) < 0)
				......................
		}
	}
.fi
.)t


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
