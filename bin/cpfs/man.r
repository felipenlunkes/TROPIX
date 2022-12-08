.bp
.he 'CPFS (cmd)'TROPIX: Manual de Refer�ncia'CPFS (cmd)'
.fo 'Atualizado em 15.01.99'Vers�o 3.1.0'Pag. %'

.b NOME
.in 5
.wo "cpfs -"
copia sistemas de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cpfs <fonte> <destino>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "cpfs" copia sistemas de arquivos.
A c�pia � feita "imagem", isto �, n�o � feita nenhuma
altera��o no conte�do copiado.

.sp
Tanto o sistema de arquivos <fonte> como o <destino> devem
ser dispositivos n�o estruturados (isto �, de caracteres).
Se os sistemas de arquivos n�o tiverem o mesmo tamanho,
o n�mero de blocos copiados � o do menor sistema de arquivos.

.sp
O sistema de arquivo destino n�o pode estar montado.
� prefer�vel que o sistema de arquivo fonte tamb�m esteja n�o montado,
no entanto a c�pia � permitida, ap�s uma advert�ncia.

.in
.sp
.b OBSERVA��O
.in 5
Nesta vers�o do comando, o conte�do � copiado em unidades de 64 KB. 

.sp
Como a tabela de parti��es n�o � atualizada automaticamente,
pode ocorrer (ap�s uma c�pia) que o tipo do sistema de arquivos
n�o corresponda mais ao tipo indicado na tabela de parti��es.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkfs, fsck
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
