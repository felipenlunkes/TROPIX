.bp
.he 'WRITEBUF (libc)'TROPIX: Manual de Modifica��es'WRITEBUF (libc)'
.fo 'Atualizado em 08.09.90'Vers�o 2.3.0'Pag. %'

.b NOME
.in 5
.wo "writebuf -"
escrita de um bloco da STDIO
.br

.in
.sp 2
.ip "08.09.90  2.3.0" 20
Foi incorporado o teste do "\n" na fun��o, para que a macro "putc"
funcione com constru��es do tipo "putc (*cp++, fp)";
