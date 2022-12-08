
.bp
.he 'DATA (cmd)'TROPIX: Manual de Refer�ncia'DATA (cmd)'
.fo 'Atualizado em 24.04.97'Vers�o 3.0.1'Pag. %'


.b NOME
.in 5
Mostra/atualiza a data/hora corrente do sistema:
.sp
.wo "data    -"
data e hora LOCAL em portugu�s
.br
.wo "date    -"
data e hora LOCAL em ingl�s
.br
.wo "datagmt -"
data e hora UT (GMT) em portugu�s
.br

.in
.sp
.b SINTAXE
.in 5
.(l
data    [[[[[<ano>]<m�s>]<dia>]<hora>]<minuto>][:<segundo>]

date    [[[[[<ano>]<m�s>]<dia>]<hora>]<minuto>][:<segundo>]

datagmt [[[[[<ano>]<m�s>]<dia>]<hora>]<minuto>][:<segundo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
Este comandos manipulam a data/hora corrente do sistema.
Para detalhes sobre o tempo padr�o interno do sistema
e a diferen�a entre os tempos LOCAL e UT (Tempo Universal,
antes chamado de GMT) veja "ctime" (libc).

.sp
Sem argumentos, os comandos imprimem a data e hora corrente do sistema.
Os comandos "data" e "datagmt" apresentam a data/hora em portugu�s,
enquanto que "date" a apresenta em ingl�s.
O comando "data" e "date" d�o a hora
LOCAL (levando em conta o fuso hor�rio, veja "gettzmin" (sys)).

.sp
Se um argumento for dado, ele deve representar uma data/hora no formato
dado acima.
Esta data/hora � utilizada para atualizar o tempo padr�o interno do sistema,
o que s� pode ser feito pelo superusu�rio.

.sp
Cada componente do argumento (<ano>, <m�s>, ...) deve ser dado
no formato de 2 d�gitos decimais.
O caractere "." pode ser usado no lugar de ":".
Cada componente n�o dado ser� obtido a partir da data/hora corrente,
isto �, n�o ser� modificado.
Uma exce��o � o componente <segundo>, que se n�o dado, ser� zerado.

.sp
Se a modifica��o da data/hora foi completada corretamente,
a nova data/hora ser� impressa, como descrito acima.

.in
.sp
.b OBSERVA��ES
.in 5
Os valores de <ano> podem variar de 70 a 99 (para indicar 1970 a 1999)
ou 00 a 37 (para indicar 2000 a 2037).

.sp
N�o � recomendado alterar a data/hora em modo multiusu�rio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys):"
gettzmin
.br
.wo "(libc):"
ctime
.br
.wo "(fmt): "
ambiente
.br

.in
.sp
.(t
.b EXEMPLOS
.in 7
.nf
		date :27
.fi
.in 5
.sp
mant�m a data, hora e minutos correntes, atualizando somente
os segundos.
.)t

.sp 2
.nf
		data 2246
.fi
.sp
atualiza a hora para 22 horas e 46 minutos do dia corrente zerando os segundos.

.sp 2
.nf
		data 8610141745:38
.fi
.sp
atualiza a data para 14 de outubro de 1986 e a hora para 17
horas e 45 minutos e 38 segundos.

.sp 2
.nf
		datagmt 1800
.fi
.sp
atualiza a data para 18 horas UT.


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
