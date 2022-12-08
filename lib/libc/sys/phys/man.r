.bp
.he 'PHYS (sys)'TROPIX: Manual de Refer�ncia'PHYS (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "phys -"
acessa diretamente a memoria f�sica
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <fcntl.h>

void	*phys (const void *area, int count, int oflag);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "phys" prepara a unidade de ger�ncia de mem�ria
da UCP na qual o processo est� sendo executado para modificar
o mapeamento de endere�os virtuais em endere�os f�sicos. 
Com isto, abre-se a possibilidade de um processo acessar regi�es
de mem�ria fora das regi�es pr�prias do processo, tais como
as regi�es de outros processos ou do n�cleo do sistema operacional
TROPIX. 

.sp
O argumento "oflag" � constru�do a partir dos indicadores da lista
abaixo (somente um dos dois primeiros e um dos dois
�ltimos pode ser usado):

.in 8
.ip O_RDONLY 10
O mapeamento � realizado apenas para leituras.

.ip O_RDWR 10
O mapeamento � realizado para leituras e escritas.

.ip O_PHYS 10
O endere�o dado "area" � de um endere�o f�sico da mem�ria
que desejamos acessar. 

.ip O_KERNEL 10
O endere�o dado "area" � de um endere�o virtual do espa�o do
n�cleo do TROPIX
que desejamos acessar. 

.ep
.sp
.in 5
O argumento "count" fornece o tamanho (em bytes) da regi�o mapeada.
Se for NULO, desfaz um mapeamento anterior, e neste caso, em
"area" temos que dar o endere�o virtual retornado na chamada
que realizou o mapeamento. 

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Obtendo sucesso: no caso de realiza��o de um mapeamento,
a chamada ao sistema devolve o endere�o virtual que deve ser
usado para acessar a �rea; no caso de desfazer o mapeamento,
ela devolve zero. 
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Esta chamada ao sistema � relativamente dependente da
m�quina, e somente o superusu�rio pode utiliz�-la.
Normalmente ela � reservada para utilit�rios especiais.

.sp
As unidades de ger�ncia de mem�ria tem normalmente um n�mero m�ximo
de mapeamentos que podem realizar simultaneamente.
Quando este limite for atingido, somente podemos
realizar novos mapeamentos desfazendo mapeamentos anteriores.

.sp
O tamanho m�ximo da �rea mapeada tamb�m � dependente
das unidades de ger�ncia de mem�ria. 

.in
.sp
.b EXEMPLO
.nf
	#include <sys/syscall.h>
	#include <fcntl.h>

	   ..........

	register int	*ip, n;

	/*
	 *	Preparando o acesso ao inteiro cujo endere�o na
	 *	mem�ria f�sica � 0x50CDE, apenas para leitura
	 */ 
	ip = phys ((char *)0x50CDE, sizeof (int), O_PHYS|O_RDONLY);

	if ((int)ip == -1)
	{
		/* Erro ... */
	}

	/*
	 *	Acessando o inteiro
	 */
	n = *ip;

	/*
	 *	Desfazendo o mapeamento
	 */
	phys (ip, 0, 0);
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.
