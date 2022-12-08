.bp
.he 'MAKE (cmd)'TROPIX: Manual de Modifica��es'MAKE (cmd)'
.fo 'Atualizado em 09.01.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "make -"
Gerencia a manuten��o de grupos de programas
.br

.in
.sp 2
.ip "25.07.88  2.0.0" 20
VERS�O CORRENTE
.sp

.ip "09.09.88  2.1.0" 20
As vari�veis definidas no "makefile" agora s�o exportadas
para o ambiente.
Alterado "src/parser.c".

.ip "29.09.88  2.1.1" 20
No caso do "make" executar um comando indiretamente atrav�s
do "sh", n�o estava sendo passado o ambiente correto.
Modificado "src/update". 

.ip "03.09.89  2.3.0" 20
Introduzida a op��o "-D", alterado "src/main.c".

.sp
Introduzida a linha do tipo ".putenv". As vari�veis N�O s�o mais
automaticamente colocadas no ambiente.

.ip "20.03.96  3.0.0" 20
O programa foi reescrito por Oswaldo Vernet.

.ip "17.10.96  3.0.0" 20
Corrigida a relibera��o de um bloco.

.ip "25.10.96  3.0.0" 20
Aumentado o tamanho da tabela hash de 511 para 1009. Modificado "h/sym.h"

.ip "30.10.96  3.0.0" 20
Corrigido o valor passado para o "exit" em "src/make.c".
Modificados: "src/make.c", "src/update.c" e "h/proto.h".

.ip "03.02.97  3.0.0" 20
Corrigido o processamento da op��o "-n", que passa a funcionar tamb�m com "-t"
(modificados "src/make.c", "h/extern.h" e "src/update.c").
Corrigido o tratamento de coment�rios (modificado "src/scan.c").

.ip "03.03.97  3.0.1" 20
Suprimida a op��o "-c", que tornou-se "default".
Introduzido o conceito de "alvos virtuais", declarados com a palavra
reservada ".virtual".
(modificados os m�dulos "h/sym.h", "h/extern.h", "src/make.c", "src/parse.c",
"src/scan.c", "tbl/mksym.c" e "src/update.c").

.ip "01.05.97  3.0.1" 20
Introduzida a op��o "-a", cujo efeito � listar os alvos constantes do
arquivo de descri��o.
(modificados os m�dulos "h/sym.h", "h/extern.h", "h/proto.h", "src/make.c"
e "src/parse.c").

.ip "25.01.99  3.1.0" 20
Quando um "putenv" � redefinido, agora verifica se por acaso a cadeia
� a mesma.

.ip "14.12.99  3.2.3" 20
Introduzida a op��o "-b", cujo efeito � reconstruir todos os m�dulos,
independentemente das datas.

.sp
Introduzida a propaga��o das op��es "-a", "-b", "-i", "-n", "-t" e "-v".
Quando o programa "make" � chamado dentro de um Makefile, essas op��es,
se estiverem ativas, s�o propagadas.

.sp
A expans�o de uma macro pode, agora, fazer parte do nome de outra.

.ip "28.08.01  4.1.0" 20
As vari�veis definidas no ambiente prevalecem sobre as macros hom�nimas
no Makefile.
