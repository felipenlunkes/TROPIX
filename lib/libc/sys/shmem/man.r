.bp
.he 'SHMEM (sys)'TROPIX: Manual de Refer�ncia'SHMEM (sys)'
.fo 'Atualizado em 04.01.99'Vers�o 3.1'Pag. %'

.b NOME
.in 5
.wo "shmem -"
cria uma regi�o compartilhada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

void	*shmem (int fd, int size);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "shmem" permite a obten��o de uma regi�o de mem�ria
que pode ser compartilhada entre v�rios processos.

.sp
A identifica��o de uma regi�o de mem�ria compartilhada no TROPIX
� feita atrav�s de um arquivo regular cujo nome � conhecido pelos
diversos processos. O arquivo em si n�o � usado; apenas o seu
nome � utilizado como uma refer�ncia comum.

.sp
Inicialmente deve-se criar ("creat" (sys)) e/ou abrir ("open" (sys))
o arquivo, obtendo-se o descritor "fd", que ser� usado em seguida na
chamada a "shmem".
O acesso � regi�o ter� os mesmos privil�gios
(de leitura/escrita) do arquivo aberto.

.sp
Se a regi�o compartilhada ainda n�o existia, ela � criada com o tamanho
"size" bytes. Se ela j� existia (isto �, um outro processo j� chamou
"shmem" com o mesmo arquivo), o tamanho dado deve ser o mesmo.

.sp
A regi�o compartilhada � liberada quando o �ltimo dos processos
que a usam der o "close" (sys) referente ao arquivo.


.bc	/*************************************/
.sp
Se por acaso a regi�o ("fd", "n") dada j� tinha mem�ria alocada
(por exemplo, por um outro processo),
"shmem" utiliza a �rea de mem�ria j� alocada
(certificando-se de que os tamanhos s�o iguais).
Deste modo, os dois (ou mais) processos podem compartilhar esta mesma
�rea de mem�ria.
.ec	/*************************************/

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o endere�o virtual que deve ser
usado para acessar a regi�o.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Os tamanhos das �reas de mem�ria efetivamente alocados �s regi�es
s�o arredondados de acordo com as caracter�sticas da ger�ncia de
mem�ria de cada computador.

.sp
Na presente vers�o, o arredondamento � de 4 KB,
e um processo pode ter no m�ximo 32 regi�es,
com um total de 4 MB alocados.

.bc	/*************************************/
.sp
No TROPIX as regi�es de mem�ria compartilhadas existem enquanto o
seu arquivo associado estiver aberto.
Quando o arquivo associado a um conjunto de regi�es � fechado, o processo
perde o acesso a estas regi�es. Quando o �ltimo processo fecha este arquivo
as regi�es s�o destru�das.
Desta forma, a libera��o de regi�es � feita,
simplesmente, fechando-se seus arquivos associados.
.ec	/*************************************/

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
creat, open, close
.br

.in
.sp
.(t
.b EXEMPLO
.in 7
A aplica��o usual da chamada ao sistema para se obter uma regi�o
de mem�ria que pode ser compartilhada entre processos � feita
da seguinte forma:
.sp
.nf
	#include <sys/syscall.h>

	   ..........

	int		fd, size, *ip, n;

	/*
	 *	Abrindo o arquivo associado
	 */
	fd = open ("nome", ...);

	/*
	 *	Alocando/referindo a regi�o compartilhada
	 */
	ip = shmem (fd, size);

	if ((int)ip == -1)
	{
		/* Erro ... */
	}

	/*
	 *	Acessando a regi�o
	 */
	n = *ip;	/* Acessa a regi�o */

	/*
	 *	Libera a regi�o alocada
	 */
	close (fd);
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
