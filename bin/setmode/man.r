.bp
.he 'SETMODE (cmd)'TROPIX: Manual de Refer�ncia'SETMODE (cmd)'
.fo 'Atualizado em 16.04.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "setmode -"
atribui as prote��es corretas aos arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
setmode [-ueaf]
.)l

.in
.sp
.b DESCRI��O
.in 5
.bc	/*************************************/
O utilit�rio "setmode" atribui as prote��es corretas aos diversos arquivos do sistema
operacional TROPIX.
.ec	/*************************************/
O utilit�rio "setmode" analisa o modo dos diversos arquivos do sistema operacional TROPIX.
Para cada um deles, verifica se o dono/grupo/prote��o est�o corretos.

.sp
Isto � feito para os principais diret�rios, m�dulos execut�veis, membros das bibliotecas e arquivos
de inclus�o, mas N�O para arquivos e/ou diret�rios dos usu�rios.

.sp
Sem op��es, "setmode" apenas indica as incorre��es encontradas, e as respectivas
corre��es sugeridas.

.sp
As op��es do comando s�o:

.in +3
.ip -u
Corrige as incorre��es encontradas. Para cada uma delas � pedida a confirma��o do
usu�rio (veja a op��o "-f", abaixo).

.ip -e
Informa sobre arquivos n�o encontrados. Normalmente, "setmode" nada diz sobre estes
arquivos.

.ip -a
Analisa o sistema de arquivos da raiz alternativa "/aroot" ao inv�s de "/".

.ip -f
Normalmente, para cada atualiza��o a efetuar, � pedida a confirma��o do usu�rio.
Com a op��o "-f" isto N�O � feito.

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
referentes ao mesmo diret�rio
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chmod, chown, chgrp
.br
.wo "(libc):"
askyesno
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
