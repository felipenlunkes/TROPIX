.bp
.he 'DIRENT (etc)'TROPIX: Manual de Refer�ncia'DIRENT (etc)'
.fo 'Atualizado em 06.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "dirent -"
opera��es em diret�rios
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <dirent.h>

DIR	*opendir (const char *dirnm);
DIR	*inopendir (int dev, int ino);
DIRENT	*readdir (DIR *dp);
off_t	telldir (const DIR *dp);
int	seekdir (DIR *dp, off_t offset);
int	rewinddir (DIR *dp);
int	closedir (DIR *dp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A s�rie "dirent" de fun��es possibilita a leitura de diret�rios em
um formato independente do sistema de arquivos (veja o arquivo <sys/sysdirent.h>).

.sp
A fun��o "opendir" abre o diret�rio "dirnm" e retorna um ponteiro para
a estrutura DIR a ele associado, que ser� usado para identificar
o diret�rio nas futuras opera��es.
Um ponteiro NULO � retornado em caso do diret�rio n�o puder ser acessado,
ou n�o houver mem�ria dispon�vel para as estruturas de dados necess�rias. 

.sp
A fun��o "inopendir" � similar � "opendir", mas o diret�rio � identificado pelo
par (dispositivo, n�-�ndice) ao inv�s do nome.
Este par pode ser obtido atrav�s de uma chamada "stat" ou "fstat" (sys).

.sp
A fun��o "readdir" retorna um ponteiro para a entrada seguinte do diret�rio.
O nome contido no membro "d_name" sempre � terminado com um NULO.
Entradas vazias do diret�rio s�o puladas, mas as entradas "." e ".."
s�o fornecidas.
Um ponteiro NULO � retornado no final do diret�rio, ou no caso de algum erro.

.sp
A fun��o "telldir" retorna um valor representando a posi��o corrente do diret�rio.
Repare que os valores retornados por "telldir" s�o v�lidos apenas enquanto o
diret�rio n�o for fechado.

.sp
A fun��o "seekdir" atribui a posi��o corrente do diret�rio para a pr�xima
leitura atrav�s de "readdir". O valor "offset" dever� ser um valor obtido anteriormente
atrav�s de "telldir"; se for dado um valor inv�lido, os resultados ser�o imprevis�veis.

.sp
A fun��o "rewinddir" atribui a posi��o corrente do diret�rio para a primeira entrada.

.sp
A fun��o "closedir" fecha o diret�rio e libera a mem�ria associada
�s estruturas de dados.

.in
.sp
.b
VALORES DE RETORNO
.r
.in 5
Em caso de erro, as fun��es retornam um ponteiro NULO ou o valor
inteiro -1, e indicam em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
stat, fstat, getdirent
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
