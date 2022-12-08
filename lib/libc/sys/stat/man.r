.bp
.he 'STAT (sys)'TROPIX: Manual de Refer�ncia'STAT (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
Obtem o estado de um arquivo:
.sp
.wo "stat  -"
dado o nome do arquivo (acompanha os elos simb�licos)
.br
.wo "lstat -"
dado o nome do arquivo (N�O acompanha os elos)
.br
.wo "fstat -"
dado o descritor do arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/syscall.h>
#include <stat.h>

int	stat (const char *path, STAT *sp);
int	lstat (const char *path, STAT *sp);
int	fstat (int fd, STAT *sp);
.)l

.in
.sp
.b DESCRI��O
.in 5
As chamadas ao sistema "stat", "lstat" e "fstat" obt�m o estado
(isto �, uma s�rie de informa��es) de um arquivo.

.sp
Nas chamadas "stat" e "lstat", � dado o nome do arquivo "path".
N�o � necess�rio ter permiss�o para ler, escrever ou executar 
o arquivo, mas todos os diret�rios contidos em seu caminho devem
ter acesso de busca.

.sp
A chamada "lstat" � igual � "stat", exceto quando o arquivo "path"
� um elo simb�lico, caso no qual "lstat" retorna informa��es sobre
o elo, enquanto que "stat" retorna informa��es sobre o arquivo
apontado pelo elo.

.sp
Na chamada "fstat", o arquivo j� est� aberto, e � dado
o seu descritor "fd" obtido de uma chamada ao sistema "open", "creat", "dup",
"fcntl", ou "pipe".

.sp
O argumento "sp" � um ponteiro para uma estrutura "STAT", que
� preenchida com as informa��es sobre o arquivo.
A estrutura cont�m os seguintes membros:

.sp
.nf
	dev_t	st_dev;		/* Dispositivo de residencia */
	ino_t	st_ino;		/* No. do Inode */
	long	st_mode;	/* Modo do Arquivo (ver <stat.h>) */
	int	st_nlink;	/* No. de Pont. para este Arq. */
	ushort 	st_uid;		/* UID do Arquivo */
	ushort 	st_gid;		/* GID do Arquivo */
	dev_t	st_rdev;	/* Dispositivo (BLK e CHR) */
	off_t	st_size;	/* Tamanho do Arquivo */
	time_t	st_atime;	/* Tempo de Acesso */
	time_t	st_mtime;	/* Tempo de Modifica��o */
	time_t	st_ctime;	/* Tempo de Cria��o */
.fi

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chmod, chown, creat, link, mknod, pipe, read, time,
.br
.wo "        unlink, utime, write, instat, upstat"
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
