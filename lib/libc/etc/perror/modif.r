.bp
.he 'PERROR (libc)'TROPIX: Manual de Modifica��es'PERROR (libc)'
.fo 'Atualizado em 28.07.91'Vers�o 2.3.2'Pag. %'

.b NOME
.in 5
Manipula��o das mensagens de erro das chamadas ao sistema:
.sp
.wo "perror      -"
imprime a mensagem de erro
.br
.wo "errtostr    -"
obt�m uma cadeia com o nome do erro 
.br
.wo "errno       -"
o n�mero do erro
.br
.wo "sys_errlist -"
tabela de nomes de erros
.br
.wo "sys_nerr    -"
n�mero de nomes de erros na tabela

.in
.sp 2
.ip "01.12.87  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "08.07.88  2.0.0" 20
Foi inserida a mensagem de "programa objeto de vers�o/modifica��o
descontinuada" em "errlst".

.ip "28.07.91  2.3.2" 20
Foi modificada toda a fam�lia de fun��es, para utilizar a tabela
agora residente no n�cleo do sistema operacional, atrav�s de "kcntl".

.sp
As vari�veis "sys_errlist" e "sys_nerr" n�o s�o mais suportadas.
