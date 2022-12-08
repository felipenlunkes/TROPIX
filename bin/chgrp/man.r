.bp 1
.he 'CHGRP (cmd)'TROPIX: Manual de Refer�ncia'CHGRP (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "chgrp -"
troca a identifica��o do grupo (GID) de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
chgrp [-N] <grupo> [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "chgrp" troca a identifica��o do grupo 
de um ou mais arquivos para o novo <grupo> dado.

.sp
O <grupo> pode ser dado na forma num�rica
(conforme as conven��es da linguagem "C", ver "strtol" (libc")),
ou na forma do nome de um grupo, encontrado no arquivo "/etc/group".

.sp
Se for utilizada a op��o "-N", ou se N�O forem dados nomes de arquivos,
estes ser�o lidos da entrada padr�o.


.in
.sp
.b
OBSERVA��ES
.r
.in 5
Somente o dono do arquivo (ou o superusu�rio)
pode trocar a identifica��o do grupo deste arquivo.

.sp
Se a troca � realizada por um usu�rio que n�o �
superusu�rio, os bites S_ISUID ("set user ID") e S_ISGID ("set group ID")
do modo do arquivo s�o zerados (ver "chmod" (sys)). 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chown, chmod
.br
.wo "(sys): "
chown, chmod
.br
.wo "(libc):"
strtol
.br
.wo "(fmt): "
group, passwd
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/group
 /etc/passwd

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
