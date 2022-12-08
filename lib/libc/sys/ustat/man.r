.bp
.he 'USTAT (sys)'TROPIX: Manual de Refer�ncia'USTAT (sys)'
.fo 'Atualizado em 21.11.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "ustat -"
obtem o estado de um sistema de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/syscall.h>
#include <ustat.h>

int	ustat (dev_t dev, USTAT *up);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "ustat" fornece uma s�rie de informa��es
sobre um sistema de arquivos montado.
O argumento "dev" d� a
identifica��o do dispositivo contendo o sistema de arquivos
(que pode ser obtido atrav�s de um "stat" (sys)).
O argumento "up" � um ponteiro para uma estrutura "USTAT", que
� preenchida pela chamada ao sistema.

.sp
A estrutura "USTAT" cont�m os seguintes membros:

.sp
.nf
	int	f_type;		/* Tipo/subtipo do sistema de arquivos */
	int	f_sub_type;
	int	f_bsize;	/* Tamanho do bloco */
	int	f_nmsize;	/* Tamanho m�ximo do identificador */
	daddr_t	f_fsize;	/* No. total de blocos */
	daddr_t	f_tfree;	/* No. total de blocos livres */
	ino_t	f_isize;	/* No. total de n�s-�ndice */
	ino_t	f_tinode;	/* No. total de n�s-�ndice livres */
	char	f_fname[16];	/* Nome do sistema de arquivos */
	char	f_fpack[16];	/* Nome do volume */
	short	f_m, f_n;	/* Fator de entrela�amento */
	int	f_symlink_sz;	/* Tamanho a partir do qual est� no disco */
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
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
stat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
