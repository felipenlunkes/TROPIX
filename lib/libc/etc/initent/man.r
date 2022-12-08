.bp 1
.he 'INITENT (libc)'TROPIX: Manual de Refer�ncia'INITENT (libc)'
.fo 'Atualizado em 15.07.05'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
Leitura do arquivo de inicializa��o do sistema:
.sp
.nf
     getinitent  - obt�m a entrada seguinte do arquivo
     setinitent  - prepara a releitura do arquivo
     endinitent  - conclui a leitura do arquivo
     getinitnam  - obt�m a entrada da linha de nome dado
.fi
.in

.sp
.b SINTAXE
.(l
#include <sys/types.h>
#include <init.h>

INITAB	*getinitent (void);
void	setinitent (void);
void	endinitent (void);
INITAB	*getinitnam (const char *name);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getinitent" fornece, a cada chamada,
uma entrada do arquivo de inicializa��o do sistema
("/etc/initab"), no formato da estrutura "INITAB". Com sucessivas
chamadas a esta fun��o, pode-se ler sequencialmente todo o arquivo.

.sp
A fun��o "setinitent" prepara o arquivo para que seja feita uma nova leitura.
N�o � necess�rio cham�-la para o primeiro processamento.

.sp
A fun��o "endinitent" encerra o processamento do arquivo.

.sp
A fun��o "getinitnam" procura a entrada com o nome da linha dada
(sem "/dev/"); n�o � necess�rio chamar "setinitent".

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "getinitent" retorna um ponteiro para a estrutura INITAB contendo
a entrada seguinte do arquivo. No caso de final do arquivo,
ela devolve um ponteiro NULO. 
.)t

.sp
A fun��es "getinitnam" devolve um ponteiro NULO, caso a entrada desejada
n�o seja encontrada.

.in
.sp
.b OBSERVA��O
.in 5
A fun��es "getinitent" e "getinitnam" devolvem ponteiros para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
as fun��es serem chamadas novamente.

.sp
A fun��o "getinitnam" simula entradas para os pseudo terminais, cujos nomes s�o
"ptyc??".

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (cmd):  init
     (libc): getpty
     (fmt):  initab
.fi

.in
.sp
.b ARQUIVOS
.in 5
/etc/initab

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
