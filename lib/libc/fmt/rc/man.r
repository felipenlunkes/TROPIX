.bp
.he 'RC (fmt)'TROPIX: Manual de Refer�ncia'RC (fmt)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "rc -"
arquivo de comandos de inicializa��o
.br

.in
.sp
.b DESCRI��O
.in 5
O arquivo "/etc/rc" cont�m uma s�rie de comandos que ir�o
ser executados durante a carga do sistema operacional, entre a fase de
"monousu�rio" e "multiusu�rio" (ver "init" (cmd)). 

.sp
O arquivo cont�m simplesmente um comando por linha, e pode
ser editado diretamente pelo administrador do sistema atrav�s
de "ed" (cmd) ou "vi" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
init, ed, vi
.br

.in
.sp
.b ARQUIVOS
.in 5
 /etc/rc

.in
.sp
.b EXEMPLO
.sp
.nf
	/etc/mount -w /dev/sys /src/sys
	/etc/update
	rm -f /tmp/*
	rm -f /usr/tmp/*
	/usr/lib/lpd 
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
