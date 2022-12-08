.bp 1
.he 'GETMNTENT (libc)'TROPIX: Manual de Refer�ncia'GETMNTENT (libc)'
.fo 'Atualizado em 06.10.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
Leitura de uma linha do arquivo de sistemas de arquivos

.in
.sp
.b SINTAXE
.(l
#include <mntent.h>
#include <stdio.h>

int getmntent (FILE *fp, char *dev, char *dir,
					struct mntent *flags);

void defmntent (struct mntent *flags);

int getmntopt (const char *str, struct mntent *flags);

const char *editmntopt (char *str,
			const struct mntent *flags, int vflag);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es destinam-se a analisar linhas do arquivo de informa��es
dos sistemas de arquivos (normalmente "/etc/fstab").
Cada linha deste arquivo cont�m 3 campos (separados por espa�os ou <ht>):
o nome de um dispositivo, o nome de um diret�rio, e uma lista de op��es de montagem
(separadas por v�rgulas), como no exemplo:

.sp
.(l
		/dev/zip   /zip   noauto,user,noexec
.)l

.sp
A cada chamada, a fun��o "getmntent" l� uma linha do arquivo dado por "fp",
copia o nome do dispositivo na �rea apontada por "dev",
copia o nome do diret�rio na �rea apontada por "dir" e atribui os valores dos indicadores
associados �s op��es de montagem na estrutura apontada por "flags"
(indicadores N�O presentes na lista dada recebem os valores "default", veja abaixo).
Com sucessivas chamadas a esta fun��o, pode-se obter seq�encialmente t�das as entradas do arquivo.

.sp
Antes de chamar esta fun��o, o arquivo deve ser aberto atrav�s da fun��o "fopen" (libc) ou
equivalentes, e o ponteiro FILE retornado usado como o valor para argumento "fp".

.sp
A fun��o "defmntent" atribui os valores "default" (veja abaixo) aos indicadores
da estrutura apontada por "flags". Ela pode ser �til antes de uma chamada � fun��o "getmntopt"
(veja abaixo).

.sp
A fun��o "getmntopt" recebe valores iniciais dos indicadores associados �s op��es de montagem
atrav�s da estrutura apontada por "flags", analisa uma lista de op��es de montagem dada em "str"
(alterando estes indicadores), e atribui os valores atualizados na (mesma) estrutura apontada por "flags".

.sp
A fun��o "editmntopt" edita no vetor de caracteres apontado por "str" uma linha contendo
os indicadores da estrutura apontada por "flags" em sua forma simb�lica, an�loga �
linha fornecida para a fun��o "getmntopt".
Se "vflag" for n�o NULO, edita a lista completa; em caso contr�rio inclui somente
os indicadores com valores diferentes dos "default".

.in
.sp
.(t
.b "OPC�ES DE MONTAGEM"
.in 5
As op��es de montagem s�o dadas abaixo
(os indicadores associados est�o definidos no arquivo <mntent.h>):

.in +3
.ip "ro" 9
Monta o sistema de arquivos apenas para leituras
(indicador SB_RONLY ligado).
.)t

.ip "rw" 9
Monta o sistema de arquivos para leituras/escritas
(indicador SB_RONLY desligado,
valor "default").

.ip "user" 9
Permite que usu�rios regulares montem este sistema de arquivos
(somente o mesmo usu�rio ou o superusu�rio poder� desmont�-lo).
Esta op��o implica nas op��es "noexec", "nosuid" e "nodev"
(a n�o ser elas sejam alteradas subseq�entemente).

.sp
Caso o sistema de arquivos n�o possua
identifica��o de usu�rios/grupos, todos os arquivos pertencer�o ao usu�rio/grupo
do usu�rio que o montou
(indicador SB_USER ligado).

.ip "nouser" 9
Apenas o superusu�rio pode montar/desmontar este sistema de arquivos
(indicador SB_USER desligado, valor "default").

.ip "atime" 9
Atualiza o tempo de acesso aos arquivos
(indicador SB_ATIME ligado).

.ip "noatime" 9
N�O atualiza o tempo de acesso aos arquivos
(indicador SB_ATIME desligado, valor "default").

.ip "dev" 9
Interpreta os arquivos especiais estruturados/n�o estruturados
(de bloco/caracteres)
(indicador SB_DEV ligado, valor "default").

.ip "nodev" 9
N�O interpreta os arquivos especiais estruturados/n�o estruturados
(de bloco/caracteres)
(indicador SB_DEV desligado).

.ip "exec" 9
Permite a execu��o de programas deste sistema de arquivos
(indicador SB_EXEC ligado, valor "default").

.ip "noexec" 9
N�O permite a execu��o de programas deste sistema de arquivos
(indicador SB_EXEC desligado).

.ip "suid" 9
Permite que os indicadores "set user ID" e "set group ID" dos arquivos fa�am efeito
(indicador SB_SUID ligado, valor "default").

.ip "nosuid" 9
N�O permite que os indicadores "set user ID" e "set group ID" dos arquivos fa�am efeito
(indicador SB_SUID desligado).

.ip "eject" 9
Tenta ejetar o meio remov�vel do dispositivo ap�s a desmontagem
(indicador SB_EJECT ligado).

.ip "noeject" 9
N�O tenta ejetar o meio remov�vel do dispositivo ap�s a desmontagem
(indicador SB_EJECT desligado, valor "default").

.ip "case" 9
Distingue letras ma�usculas de min�sculas em compara��es de nomes de arquivos do sistema de
arquivos FAT12, FAT16, FAT32 e ISO9660 (indicador SB_CASE ligado, valor "default").

.ip "nocase" 9
N�O distingue letras ma�usculas de min�sculas em compara��es de nomes de arquivos do sistema de
arquivos FAT12, FAT16, FAT32 e ISO9660 (indicador SB_CASE desligado).

.ip "rock" 9
Para o caso de CDROMs, use a extens�o "Rock Ridge", se presente
(indicador SB_ROCK ligado, valor "default").
A extens�o "Rock Ridge" tem preced�ncia sobre a "Joliet".

.ip "norock" 9
Para o caso de CDROMs, N�O use a extens�o "Rock Ridge", mesmo se presente
(indicador SB_ROCK desligado).

.ip "joliet" 9
Para o caso de CDROMs, use a extens�o "Joliet", se presente
(indicador SB_JOLIET ligado, valor "default").

.ip "nojoliet" 9
Para o caso de CDROMs, N�O use a extens�o "Joliet", mesmo se presente
(indicador SB_JOLIET desligado).

.ip "lfn" 9
Usa os nomes longos ("long file names") durante a leitura e escrita
em arquivos do sistema de arquivos FAT12, FAT16 e FAT32 (indicador SB_LFN ligado, valor "default").

.ip "nolfn" 9
Usa os nomes estilo DOS ("8.3") durante a leitura e escrita
em arquivos do sistema de arquivos FAT12, FAT16 e FAT32 (indicador SB_LFN desligado).

.bc	/*************************************/
.ip "uid=<user>" 9
.ip "gid=<group>" 9
.ec	/*************************************/

.ip "auto" 9
Sinaliza o programa "mount" (cmd) para montar este dispositivo, quando executado
com a op��o "-a" (indicador SB_AUTO ligado, valor "default").

.ip "noauto" 9
Sinaliza o programa "mount" (cmd) para N�O montar este dispositivo, quando executado
com a op��o "-a" (indicador SB_AUTO desligado).

.ip "fsck" 9
Indicador para o programa "fsck" (cmd) para verificar o sistema de arquivos
(na realidade n�o � exatamente uma op��o de montagem)
(indicador SB_FSCK ligado).

.ip "nofsck" 9
Indicador para o programa "fsck" (cmd) para N�O verificar o sistema de arquivos
(indicador SB_FSCK desligado, valor "default").

.ip "default" 9
Equivalente a "rw,nouser,noatime,dev,exec,suid, noeject,case,auto,nofsck,rock,joliet,lfn".
Estas s�o as op��es v�lidas se n�o for dada nenhuma op��o explicitamente.

.ep
.in -3

.in
.sp
.(t
.b "OPC�ES DE MONTAGEM NFS"
.in 5
Para os sistemas de arquivos NFS temos as seguintes op��es de montagem adicionais:

.in +3
.ip "soft" 12
Se o servidor NFS n�o responder, retransmite 8 vezes (veja "retrans", abaixo), ap�s o qual desiste,
reportando um erro ao programa cliente (indicador SB_HARD desligado, valor "default").
.)t

.ip "hard" 12
Se o servidor NFS n�o responder, continua retransmitindo indefinidamente
(indicador SB_HARD ligado).

.ip "rsize=<n>" 12
O n�mero de bytes a usar para os pedidos de leitura ao servidor NFS. O valor "default" � 1024.

.ip "wsize=<n>" 12
O n�mero de bytes a usar para os pedidos de escrita ao servidor NFS. O valor "default" � 1024.

.ip "timeout=<n>" 12
O n�mero de segundos a esperar entre as retransmiss�es ao servidor NFS. O valor "default" � 1 segundo. 

.ip "retrans=<n>" 12
O n�mero m�ximo de retransmiss�es ao servidor NFS. O valor "default" � 8 vezes. 

.ip "port=<n>" 12
Para contactar o servidor NFS, use a porta <n> dada, ao inv�s da porta fornecida pelo "port mapper".
Ainda n�o implementado, na presente vers�o sempre � consultado o "port mapper".

.ip "nfsvers=<n>" 12
A vers�o do protocolo NFS a usar. No momento, somente a vers�o 2 est� dispon�vel.

.ep
.in -3


.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "getmntent" retorna um c�digo de retorno indicando o sucesso (ou n�o) da opera��o.
Em caso de sucesso, retorna um valor positivo; em caso de campo(s) faltando e/ou com erros,
retorna 0, ap�s emitir um diagn�stico em "stderr"; caso o arquivo tenha chegado ao final,
retorna EOF.

.sp
A fun��o "getmntopt" retorna um c�digo de retorno indicando o sucesso (ou n�o) da opera��o.
Em caso de sucesso, retorna um valor positivo; em caso de op��es inv�lidas,
retorna 0, ap�s emitir um diagn�stico em "stderr".

.in
.sp
.b OBSERVA��O
.in 5
Repare que a fun��o "getmntent" supo�e que os vetores de caracteres nos
quais ir� armazenar "dev" e "dir" ser�o suficientes paras as cadeias de caracteres.

.sp
Repare que a fun��o "editmntopt" supo�e que os vetor "str" de caracteres
ser� de tamanho suficientes para a linha editada.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc): "
fopen
.br
.wo "(cmd):  "
mount, umount, fsck
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
.(l
/etc/fstab
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
