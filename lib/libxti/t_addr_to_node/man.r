.bp
.he 'T_ADDR (xti)'TROPIX: Manual de Refer�ncia'T_ADDR (xti)'
.fo 'Escrito em 05.07.99'Vers�o 3.2.1'Pag. %'

.b NOME
.in 5
Convers�es entre os diversos formatos de endere�os INTERNET:
.sp
.wo "t_addr_to_name  -"
endere�o de 32 bits em nome de n� simb�lico
.br
.wo "                  (com consulta a um servidor DNS)"
.br
.wo "t_addr_to_node  -"
endere�o de 32 bits em nome de n� simb�lico
.br
.wo "                  (sem consulta a um servidor DNS)"
.br
.wo "t_addr_to_str   -"
endere�o de 32 bits em 4 n�meros decimais
.br
.wo "t_node_to_addr  -"
nome de n� simb�lico em endere�o de 32 bits
.br
.wo "t_str_to_addr   -"
4 n�meros decimais em endere�o de 32 bits
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

char	*t_addr_to_name (int fd, long addr);

char	*t_addr_to_node (int fd, long addr);

char	*t_addr_to_str (long addr);

long	t_node_to_addr (int fd, const char *node,
						long *my_addr);

long 	t_str_to_addr (const char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es auxiliam na convers�o entre os diversos formatos
de endere�os INTERNET.
Os formatos de endere�os s�o:

.in +3
.ip - 2
O endere�o de 32 bits � o formato interno utilizado por todas
as fun��es que requerem um endere�o INTERNET (membro "a_addr"
da estrutura "INADDR", ver <xti.h>).

.ip - 2
O formato de 4 n�meros decimais ("dd.dd.dd.dd") � uma nota��o
externa para facilitar a leitura dos endere�os em documentos t�cnicos
ou em programas de aplica��o.

.ip - 2
O nome de n� simb�lico � a nota��o mais c�moda para um endere�o, em
que se utiliza um identificador para represent�-lo.
O n�cleo do sistema operacional cont�m uma tabela para associar
os nomes de n�s simb�licos aos endere�os (e vice-versa).

.ep
.in -3

.sp
Para a utiliza��o das fun��es "t_addr_to_name", "t_addr_to_node"
e "t_node_to_addr" � necess�rio j� haver algum "endpoint" de transporte
dispon�vel (argumento "fd"), isto �, elas s� podem ser utilizadas
ap�s um "t_open" (libxti).

.sp
A fun��o "t_addr_to_name" consulta a tabela mencionada acima e
devolve um ponteiro para uma cadeia contendo o nome do n� simb�lico
correspondente ao endere�o INTERNET de 32 bits "addr".
Se o endere�o dado N�O for encontrado na tabela, � iniciada uma
consulta a um servidor DNS para obter o nome do n� simb�lico.

.sp
A fun��o "t_addr_to_node" consulta a tabela mencionada acima e
devolve um ponteiro para uma cadeia contendo o nome do n� simb�lico
correspondente ao endere�o INTERNET de 32 bits "addr".
Se o endere�o dado N�O for encontrado na tabela, � devolvido um
ponteiro para uma cadeia contendo um endere�o no formato de
4 n�meros decimais (isto �, n�o � feita a consulta conforme acima).

.sp
A fun��o "t_addr_to_str" devolve um ponteiro para uma cadeia
contendo um endere�o no formato de 4 n�meros decimais
correspondente ao endere�o INTERNET de 32 bits "addr".

.sp
A fun��o "t_node_to_addr"  consulta a tabela mencionada acima
e devolve um endere�o INTERNET no formato de 32 bits correspondente
a um n� remoto "node". Este n� remoto pode ser dado como um
nome de n� simb�lico ou um endere�o no formato de 4 n�meros decimais.
Se "node" for um ponteiro NULO, ser� devolvido o endere�o do pr�prio n� local.
A posi��o de mem�ria apontada pelo ponteiro "my_addr" (se n�o NULO)
receber� o endere�o INTERNET no formato de 32 bits correspondente
ao pr�prio n� local.

.sp
A fun��o "t_str_to_addr" devolve um endere�o INTERNET no formato
de 32 bits correspondente ao endere�o no formato de 4 n�meros decimais
"str".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Estas fun��es n�o fazem parte da XTI, e portanto seu uso deve ser evitado
se for desejada portabilidade para outras implementa��es.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, as fun��es devolvem os endere�os no formatos
descritos acima.

.sp
Em caso de falha:
a fun��o "t_addr_to_node" devolve um ponteiro para uma cadeia
contendo um endere�o no formato de 4 n�meros decimais (como
"t_addr_to_str");
"t_addr_to_name" e "t_node_to_addr" devolvem -1 e um c�digo de erro em "t_errno";
"t_str_to_addr" devolve -1.
A fun��o "t_addr_to_str" nunca retorna com falha.

.in
.sp
.b OBSERVA��O
.in 5
A fun��es "t_addr_to_name", "t_addr_to_node" e "t_addr_to_str"
devolvem um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
a fun��o ser chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.br
.wo "(xti): "
t_intro, t_open
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
