.bp
.he 'EDUSR (cmd)'TROPIX: Manual de Refer�ncia'EDUSR (cmd)'
.fo 'Atualizado em 15.01.99'Vers�o 3.1.1'Pag. %'

.b NOME
.in 5
.wo "edusr -"
gerencia as contas/grupos de usu�rios 
.br

.in
.sp
.b SINTAXE
.in 5
.(l
edusr
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "edusr" � uma interface para o gerenciamento das contas
e grupos de usu�rios do sistema TROPIX.
Ele gerencia o arquivos de contas/senhas "/etc/passwd",
o arquivo de grupos "/etc/group",
cria/remove os diret�rios contendo os arquivos
dos usu�rios (diret�rio "home"),
e a suas caixas postais.

.sp
No TROPIX (assim como em outros sistemas operacionais de filosofia
UNIX), cada usu�rio do sistema � identificado por um inteiro
n�o negativo chamado
UID. Al�m disto, ele pertence a um certo grupo de usu�rios,
que (tamb�m) � identificado por um inteiro n�o negativo chamado GID.

.sp
Estes dois n�meros definem as permiss�es que o usu�rio possui para
acessar certos recursos do sistema (tais como ler/escrever um
certo arquivo ou executar um certo programa).
Se o UID de um usu�rio for 0, ele � considerado um "superusu�rio",
e tem permiss�o para acessar todos os recursos do sistema;
em "intro" (sys) s�o dados mais detalhes.

.sp
O programa "edusr" sup�e que os arquivos de contas/senhas e
o arquivo de grupos estejam (respectivamente) ordenados crescentemente
pelo UID e GID.

.sp
O programa "edusr" possui um interpretador de comandos, que le e
processa instru��es do usu�rio.
Para indicar que est� aguardando comandos, "edusr" imprime
uma linha contendo os caracteres
.sp
.nf
		"edusr [n]> "
.fi
.sp
onde "n" � o n�mero
do comando no hist�rico (ver os comandos "h", "eh" e "xh" abaixo). 

.sp
Atrav�s do interpretador de comandos podemos efetuar diversas opera��es,
tais como obter uma lista dos usu�rios, criar novos usu�rios, remover usu�rios,
etc ... A lista completa � dada abaixo.

.in
.sp
.b "INFORMA��ES DO ARQUIVO DE CONTAS"
.in 5
O arquivo de contas/senhas "/etc/passwd" cont�m uma linha para cada usu�rio
do sistema. Cada uma destas linhas cont�m 10 campos separados
pelo caractere ":", contendo diversas informa��es.
Todos estas informa��es podem ser listadas atrav�s do comando "pu"
(veja abaixo).

.sp
Elas s�o (acompanhe no arquivo "/usr/include/pwd.h"):

.in +3
.ip " 1." 4
Nome do Usu�rio: Pode ter no m�ximo 14 caracteres.

.ip " 2." 4
Senha encriptada: Esta senha � consultada pelo programa "login" sempre
que um usu�rio entra em sess�o. O comando "edusr" n�o processa estas senhas;
para um usu�rio regular a linha � criada sem senha e
para um superusu�rio a linha � criada com a senha do "root".
Em ambos os casos, as senhas devem ser modificadas posteriormente
atrav�s do programa "passwd" (cmd).

.ip " 3." 4
Coment�rio: Cont�m normalmente o nome completo do usu�rio.

.ip " 4." 4
Identifica��o do usu�rio (UID).

.ip " 5." 4
Identifica��o do grupo do usu�rio (GID).

.ip " 6." 4
Cota: O n�mero m�ximo de blocos (de 512 bytes) que o usu�rio
pode alocar no disco.
Se este valor for NULO, o usu�rio n�o tem limite de blocos.
Na presente vers�o do sistema, este controle n�o est� implementado.

.ip " 7." 4
Data de expira��o: Indica a data ap�s a qual n�o � mais permitido
ao usu�rio entrar em sess�o no sistema.
Se este valor for NULO, o usu�rio n�o tem data de expira��o.

.ip " 8." 4
Tranca: Informa��o utilizada pelo controle de cotas.

.ip " 9." 4
Diret�rio "home": Diret�rio corrente do usu�rio ap�s entrar em sess�o.
� neste diret�rio que o usu�rio deve criar o seus arquivos.
Como ele pode tamb�m criar subdiret�rios, o diret�rio "home"
� na verdade a raiz da �rvore contendo todos os arquivos do usu�rio.

.ip "10." 4
Interpretador de comandos: Programa que � executado ao entrar em
sess�o. Normalmente � um interpretador de comandos (tal como "/bin/sh" (cmd)).

.ep
.in -3

.in
.sp
.b "VALORES CORRENTES"
.in 5
Para facilitar a cria��o de contas, o programa "edusr" armazena os
uma s�rie de "valores correntes":

.in +3
.ip " 1." 4
O grupo corrente: O grupo a que pertencer� o novo usu�rio.
Pode ser consultado/alterado atrav�s do comando "g".

.ip " 2." 4
A cota corrente: O limite de cotas que ser� atribu�do ao novo usu�rio.
Pode ser consultado/alterado atrav�s do comando "c".

.ip " 3." 4
A data de expira��o corrente: A data de expira��o que ser� atribu�da ao novo usu�rio.
Pode ser consultado/alterado atrav�s do comando "e".

.ip " 4." 4
O diret�rio "home" corrente: O diret�rio que ser� atribu�do ao novo usu�rio.
Pode ser consultado/alterado atrav�s do comando "home".

.ip " 5." 4
O interpretador de comandos corrente: O interpretador que ser� atribu�do
ao novo usu�rio. Pode ser consultado/alterado atrav�s do comando "shell".

.ep
.in -3

.sp
Atrav�s do comando "set" podemos consultar todos os valores correntes
simultaneamente.

.sp
Al�m dos valores descritos acima, "edusr" tamb�m consulta o arquivo
"/usr/pub/lib/profile.sample", que � usado para criar o arquivo
".profile" dos usu�rios.
Este arquivo naturalmente pode ser modificado conforme as necessidades.

.in
.sp
.(t
.b COMANDOS
.in 5
O programa "edusr" reconhece e processa os seguintes comandos:

.bc	/*************************************/
.in +3
.ec	/*************************************/
.ip " 1." 4
?
.sp
Como "help", abaixo.
.)t

.ip " 2." 4
!<comando> [<argumento> ...]
.sp
Executa o <comando> com os respectivos <argumento>s atrav�s do "sh".
Isto vale inclusive para o comando "cd".
Todo o contexto de "edusr" � conservado.

.ip " 3." 4
c [<cota>]
.sp
Como "cota", abaixo.

.ip " 4." 4
cota [<cota>]
.sp
Altera a cota corrente de blocos por usu�rio.
Se a <cota> n�o for dada, imprime a "cota" corrente.
Uma cota de 0 blocos significa a aus�ncia do limite de cotas.

.ip " 5." 4
data [<expir>]
.sp
Como "expir", abaixo.
 
.ip " 6." 4
e [<expir>]
.sp
Como "expir", abaixo.

.ip " 7." 4
eh [<n>]
.sp
Edita (e opcionalmente executa) o comando de n�mero <n> do hist�rico.
Se <n> for omitido, edita o �ltimo comando presente no hist�rico.
A edi��o � realizada pela fun��o "edit" (libc).
Ap�s a edi��o, o usu�rio � consultado se deseja realmente executar
o comando editado.

.(t
.ip " 8." 4
exit
.sp
Como "quit", abaixo.
.)t

.ip " 9." 4
expir [<expir>]
.sp
Altera a data de expira��o da conta de usu�rio.
Se <expir> n�o for dada, � impressa a data de expira��o corrente.
O formato de <expir> deve ser "dd.mm.aa", ou "0" significando
a aus�ncia de data de expira��o.

.ip "10." 4
g [<grupo>]
.sp
Como "mkgrp", abaixo.

.ip "11." 4
h
.sp
Imprime os comandos do hist�rico. Nesta vers�o, o hist�rico armazena
os �ltimos 20 comandos executados.

.ip "12." 4
help
.sp
Imprime uma lista de todos os comandos dispon�veis.
Para obter um resumo de um <comando>, use "<comando> -H" ou "<comando> ?".

.ip "13." 4
home [<diret�rio>]
.sp
Altera o diret�rio "home".
Se o <diret�rio> n�o for dado, imprime o "home" corrente.

.ip "14." 4
mg [<grupo>]
.sp
Como "mkgrp", abaixo.

.ip "15." 4
mkgrp [<grupo>]
.sp
Altera o grupo corrente ou cria um novo grupo.
Se o <grupo> n�o for dado, imprime o grupo corrente.
Se o <grupo> dado ainda n�o existir, ele � criado, e passa a ser
o grupo corrente.

.ip "16." 4
mkusr [-s] <usu�rio> [<coment�rio>]
.sp
Cria o novo <usu�rio> com os valores correntes.
O <coment�rio>, se dado, engloba todos os argumentos ap�s <usu�rio>.
.sp
Sem a op��o "-s", � criado um usu�rio regular sem senha, cujo UID
� escolhido automaticamente pelo programa "edusr".
Com a op��o "-s", � criado um superusu�rio com a senha do "root".
.sp
N�O esque�a de atribuir uma senha posteriormente atrav�s do utilit�rio
"passwd" (cmd).

.ip "17." 4
mu [-s] <usu�rio> [<coment�rio>]
.sp
Como "mkusr", acima.

.(t
.ip "18." 4
pg [<grupo>]
.sp
Como "prgrp", abaixo.
.)t

.ip "19." 4
prgrp [<grupo>]
.sp
Imprime o <grupo>. Se <grupo> n�o for dado, imprime todos os grupos.

.ip "20." 4
prusr [-l] [-g <grupo>] [<usu�rio>]
.sp
Imprime informa��es sobre o <usu�rio>. Se o <usu�rio> n�o for dado,
imprime informa��es sobre todos os usu�rios. Se for dada a op��o
"-g", somente imprime informa��es sobre os usu�rios do <grupo> dado.

.sp
Sem a op��o "-l", imprime o nome do usu�rio, seu UID, o nome (e GID) do grupo
a que pertence, um asterisco se N�O contiver senha e o coment�rio
(normalmente o nome completo do usu�rio).

.sp
Com a op��o "-l", imprime o nome do usu�rio, seu UID, o nome do interpretador
de comandos e o diret�rio "home".

.sp
Com a op��o "-l" dada duas vezes, imprime o nome do usu�rio, seu UID,
a cota, um "L" se a conta estiver "trancada", a data de expira��o e um
"E" caso a conta esteja expirada.
O caractere "." indica a aus�ncia de cota/data de expira��o.
 
.ip "21." 4
pu [-l] [-g <grupo>] [<usu�rio>]
.sp
Como "prusr", acima.

.ip "22." 4
q
.sp
Como "quit", abaixo.

.ip "23." 4
quit
.sp
Termina a execu��o de "edusr".
Um EOF (normalmente <^D>) tem o mesmo efeito.

.ip "24." 4
quota [<cota>]
.sp
Como "cota", acima.

.(t
.ip "25." 4
rg <grupo>
.sp
Como "rmgrp", abaixo.
.)t

.ip "26." 4
rmgrp <grupo>
.sp
Remove o <grupo>, juntamente com os seus usu�rios e arquivos.
Este comando deve ser utilizado com cuidado, para evitar a remo��o
acidental de arquivos de usu�rios.

.ip "27." 4
rmusr <usu�rio>
.sp
Remove o <usu�rio>, juntamente com os seus arquivos e caixa postal.
Este comando deve ser utilizado com cuidado, para evitar a remo��o
acidental de arquivos e/ou cartas das caixas postais dos usu�rios.

.ip "28." 4
ru <usu�rio>
.sp
Como "rmusr", acima.

.ip "29." 4
set
.sp
Imprime os valores correntes.

.ip "30." 4
shell [<shell>]
.sp
Altera o interpretador de comandos ("shell") corrente.
Se <shell> n�o for dado, imprime o interpretador corrente.

.ip "31." 4
u [-s] <usu�rio> [<coment�rio>]
.sp
Como "mkusr", acima.

.ip "32." 4
xh [<n>]
.sp
Excuta o comando de n�mero <n> do hist�rico.
Se <n> for omitido, executa o �ltimo comando presente no hist�rico.

.ep
.bc	/*************************************/
.in -3
.ec	/*************************************/

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys):  "
intro
.br
.wo "(libc): "
edit
.br
.wo "(cmd):  "
passwd, sh
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
/etc/passwd
 /etc/group
 /home/...
 /var/spool/mail/...
 /usr/include/pwd.h
 /usr/pub/lib/profile.sample

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
