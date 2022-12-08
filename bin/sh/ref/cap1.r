.bp
.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 1			     *
     *							     *
     *			    INTRODU��O			     *
     *							     *
     *********************************************************

.fi

.sp 4


.pp
A "shell" � um interpretador de comandos program�vel, que serve de
interface entre o usu�rio e o sistema operacional TROPIX.
Ap�s o "login", quando o usu�rio ganha acesso ao sistema,
a "shell" �  invocada automaticamente. Neste caso, uma indica��o ("prompt")
� escrita no terminal e a "shell" est� pronta para aceitar comandos.
Ao receber um nome, a "shell" procura um comando com este nome numa
seq��ncia de diret�rios previamente definida e o executa.
Normalmente, a partir deste ponto, o comando executado ganha o controle do
terminal.
Ao t�rmino da execu��o do comando, 
o controle do terminal retorna � "shell".

.pp
A "shell" oferece ao usu�rio uma s�rie de facilidades para
indicar a forma de execu��o dos comandos, basicamente:
redirecionamento da entrada e sa�da, comunica��o entre
processos atrav�s de "pipes", substitui��o de vari�veis,
expans�o de nomes de arquivos, modifica��o do ambiente
dos comandos,  manuten��o e edi��o de um hist�rico de comandos
e disponobilidade de estruturas de controle para programa��o.

.pp
Os comandos que, em geral, s�o lidos do terminal poder�o tamb�m
ser provenientes de um arquivo de comandos, previamente preparado.
