.bp
.he 'SH (cmd)'TROPIX: Manual de Modifica��es'SH (cmd)'
.fo 'Atualizado em 12.11.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "sh -"
Interpretador de comandos.
.br

.in
.sp 2
.ip "01.05.89  2.1" 20
VERS�O CORRENTE
.sp

.ip "15.04.87  1.0.1" 20
O redirecionamento '<<' que permite a especifica��o
do conte�do da entrada padr�o do comando a ser executado,
foi corrigido. Antes a leitura do conte�do era realizada
pelo processo filho e assim a shell n�o a descartava
ap�s a execu��o do comando. Agora a leitura � realizada
pela pr�pria shell, antes da cria��o de um processo
para executar o comando.

.ip "30.06.89  1.0.2" 20
A partir de agora, se a shell for ativada por um login, o arquivo
"/etc/profile" � executado antes do arquivo "$HOME/.profile".

.ip "04.02.91  2.3.1" 20
Foi inserido "setvbuf" em "main.c" para que "stdout" e "stderr"
seja sempre com buffer de linha.

.ip "22.06.91  2.3.2" 20
Foi removido o  "setvbuf" em "main.c" (esta id�ia ser� executada pelo
pseudo-terminal).

.sp
Agora s�o fechados os arquivos "16", "17", "18" e "19", que antes
eram esquecidos abertos.

.ip "04.09.92  3.0.0" 20
O comando "cd" agora permite escolher de v�rios diret�rios dados.

.ip "03.10.94  3.0.1" 20
Incorporado o comando "logout".

.ip "09.04.96  3.0.5" 20
O "sh" foi religado para utilizar a nova vers�o de "execvp".

.ip "26.09.96  3.0.6" 20
Introduzida a vari�vel "$%" para representar o nome do n�.

.ip "07.07.97  3.0.7" 20
Alterado o "exit" para terminar a sess�o.
Introduzida a op��o "-d" para especificar se <^D> termina ou
n�o o "sh".

.ip "24.04.00  3.2.3" 20
O programa foi integralmente reescrito.

.ip "06.06.00  4.0.0" 20
Consertado o erro na abertura do "script".

.ip "07.07.01  4.0.0" 20
Consertado um erro de an�lise sint�tica.

.ip "31.07.01  4.0.0" 20
Consertado um erro no comando "time".

.ip "31.07.01  4.0.0" 20
Modificado o m�dulo "src/expand.c", para usar "<dirent.h>".

.ip "28.08.01  4.1.0" 20
Consertado o comando "export", quando a vari�vel tem valor NULO.

.ip "25.10.01  4.2.0" 20
S� permite executar "spy" a partir de "/dev/console" ou "/dev/video*".

.ip "01.10.02  4.3.0" 20
Verifica a validade de um "script" antes de tentar execut�-lo.

.ip "15.10.02  4.3.0" 20
Consertado o aumento da �rea de leitura, no m�dulo "src/scan.c".

.ip "21.11.02  4.4.0" 20
A entrada padr�o � tratada em modo RAW. Inclu�do o m�dulo "src/fnrgets.c"
e alterado o m�dulo "src/scan.c"

.ip "24.11.02  4.4.0" 20
Introduzida a Tabela HASH de execut�veis, para evitar buscas nos diversos
diret�rios do PATH. Introduzido tamb�m o comando "rehash", que refaz
a tabela. Modificados os m�dulos "src/exec.c", "src/func.c",
"src/sh.c", "src/sym.c" e "tbl/mksym.c".

.ip "05.12.02  4.4.0" 20
Introduzido o tratamento do sinal SIGWINCH. Alterado o m�dulo
"src/fnrgets.c".

.ip "12.06.03  4.5.0" 20
Consertado (mais um) um erro no comando "time".

.ip "10.10.03" 20
Introduzida a vari�vel "$~", cujo valor � o caminho para o diret�rio corrente,
e o metacaractere "~" como sin�nimo de $HOME.

.ip "14.10.03" 20
Introduzida a vari�vel "$&", cujo valor � "#" se o usu�rio efetivo for
o superusu�rio ou "$" caso contr�rio.

.ip "21.10.03" 20
Consertado o problema do prompt invis�vel.

.ip "05.11.03" 20
Consertado o problema do teclado ABNT.

.ip "12.11.03" 20
Modificada a tabela de categorias, para defini��o de acentos.
