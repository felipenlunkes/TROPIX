.bp
.he 'MKLIB (cmd)'TROPIX: Manual de Modifica��es'MODIF (cmd)'
.fo 'Atualizado em 01.10.01'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "mklib -"
cria/mant�m bibliotecas de m�dulos objeto
.br

.in
.sp 2
.ip "01.04.87  1.0.0" 20
VERS�O CORRENTE
.sp

.ip "23.07.87  1.0.1" 20
Foi corrigido o problema de prote��o do arquivos "~LIBSYM~"
(agora � "rw-r--r--").

.in
.sp 2
.ip "01.01.88  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "18.12.90  2.3.0" 20
Alterado para trabalhar com s�mbolos externos de 31 caracteres.

.ip "24.12.93  3.0.0" 20
Foi feita uma revis�o geral, incluindo logo a ordena��o.
O ponteiro "lf_last" agora aponta para o primeiro s�mbolo do m�dulo seguinte.

.ip "25.04.95  3.0.1" 20
Adapta��o para o PC.

.ip "30.05.97  3.0.2" 20
Uma pequena revis�o.

.ip "20.11.97  3.0.3" 20
Corrigidos os problemas da n�o exist�ncia de "~LIBSYM~" e do diret�rio
intermedi�rio faltando.

.ip "23.01.00  3.2.3" 20
Trocado ~LIBSYM~ por .LIBSYM.

.ip "11.08.01  4.0.0" 20
Usando "readdir".

.ip "21.08.01  4.0.0" 20
Novo formato da tabela de s�mbolos SYM.
.sp
Novo formato ISO de ".LIBSYM".

.ip "01.10.01  4.2.0" 20
Corrigido para m�dulos sem s�mbolos.
