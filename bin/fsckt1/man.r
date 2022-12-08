.bp
.he 'FSCKT1 (cmd)'TROPIX: Manual de Refer�ncia'FSCKT1 (cmd)'
.fo 'Atualizado em 12.09.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "fsckt1 -"
verifica a consist�ncia de sistemas de arquivos T1
.br

.in
.sp
.b SINTAXE
.in 5
.(l
fsckt1 [-synpv] [<dev> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "fsckt1" verifica a consist�ncia de sistemas de arquivos T1
contidos em um ou mais dispositivos ou arquivos regulares <dev>.
Em caso de encontrar erros, pede autoriza��o do usu�rio para  
consertar o sistema de arquivos (ver as op��es "-s", "-y" e "-n" abaixo).

.sp
Se <dev> for um diret�rio, "fsckt1" sup�e que seja um ponto de
montagem e procura o dispositivo/arquivo regular correspondente na tabela
"fstab" (veja "fstab" (fmt)).

.sp
Se n�o for dado nenhum dispositivo <dev>, s�o processados os dispositivos
dados no arquivo "/etc/fstab" (veja "getmntent (libc)) que possuem a op��o "fsck".

.sp
Se por acaso, algum dos <dev>s contiver um sistema de arquivos V7,
ser� automaticamente invocado o comando "fsckv7" (cmd).

.sp
Para poder consertar um sistema de arquivos, ele n�o pode estar montado.
A �nica exce��o a esta regra � para o dispositivo contendo a raiz do sistema
("/"), que n�o pode ser desmontado. Neste caso, � importante que
n�o hajam processos escrevendo no dipositivo (o recomendado �
o modo "monousu�rio").

.sp
As inconsist�ncias verificadas s�o as seguintes:
 
.in +3
.ip 1. 4
Blocos pertencentes a arquivos que
estejam fora dos limites f�sicos do sistema de
arquivos.
 
.ip 2. 4
Blocos pertencentes a mais de um arquivo.
 
.ip 3. 4
N�mero incorreto de refer�ncias a um arquivo.
 
.ip 4. 4
Formato inv�lido de diret�rio.
 
.ip 5. 4
Formato inv�lido de n�-�ndice.
 
.ip 6. 4
Arquivo com o n�mero do n�-�ndice inv�lido.
 
.ip 7. 4
Mapas de bits inv�lidos.
 
.ip 8. 4
Total de blocos ou n�s-�ndice livres incorreto
no superbloco.

.in -3
.ep

.sp
Arquivos n�o ligados a nenhum diret�rio podem ser reconectados
ao diret�rio padr�o "lost+found" gerado automaticamente pelo
utilit�rio "mkfst1", caso este diret�rio exista e n�o esteja
repleto.

.sp
As op��es do comando s�o:

.in +3
.ip -s
Com esta op��o s�o automaticamente geradas respostas afirmativas
para todas as consultas feitas pelo programa.

.ip -y
Como acima.

.ip -n
Com esta op��o s�o automaticamente geradas respostas negativas
para todas as consultas feitas pelo programa.

.ip -p
Modo de p�nico: ignora os mapas de bits. Tenta reconstruir o
sistema de arquivos apenas pelos blocos de n�s-�ndice, que
s�o reconhecidos por suas assinaturas.

.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
fsckv7, mkfst1
.br
.wo "(libc): "
getmntent
.br
.wo "(fmt):  "
fstab
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/fstab

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
