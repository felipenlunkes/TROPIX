.bp
.he 'FTW (libc)'TROPIX: Manual de Modifica��es'FTW (libc)'
.fo 'Atualizado em 25.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "ftw -"
caminha em uma �rvore do sistema de arquivos
.br

.in
.sp 2
.ip "01.04.87  1.1" 20
VERS�O CORRENTE
.sp

.ip "14.01.88  1.1.1" 20
O problema existente na interrup��o do percurso
de sub�rvores, ocorrido em consequ�ncia do n�o 
fechamento dos respectivos diret�rios, foi corrigido.
.sp

.ip "08.05.93  3.0.0" 20
Agora os nomes dos arquivos s�o ordenados.

.ip "14.12.93  3.0.1" 20
Nova implementa��o, recursiva, muito mais r�pida, usando "alloca".
Desvantagem: n�o caminha por largura.

.ip "22.06.95  3.0.2" 20
Pequena melhoria: alocando menos mem�ria atrav�s de "alloca".

.ip "12.04.97  3.0.3" 20
Introduzida as op��es de "pr�" ou "p�s" ordem.

.ip "05.08.01  4.0.0" 20
Usando a fun��o "readdir".

.ip "25.04.02  4.2.0" 20
Adaptada para elos simb�licos.
