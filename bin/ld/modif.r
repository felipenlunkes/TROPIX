.bp
.he 'LD (cmd)'TROPIX: Manual de Modifica��es'LD (cmd)'
.fo 'Atualizado em 12.07.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
ld - editor-ligador de m�dulos objeto
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "13.06.88  2.0.1" 20
Foi retirado do "ld" o uso de "bit-fields", que n�o �
eficiente. Alterados os m�dulos "pass1.c", "pass2.c" e "sub.c".
.sp

.ip "21.07.88  2.0.4" 20
Foi alterada a op��o "-u" para que liste apenas os s�mbolos
n�o referenciados dos m�dulos dados explicitamente.
Se foi dada duas vezes ("-uu"), lista todos os s�mbolos
n�o referenciados, inclusive dos m�dulos das bibliotecas.

.sp
Foi intruduzida o contr�le da vers�o dos m�dulos.
Se um m�dulo n�o for da vers�o corrente, nem da anterior,
� emitido uma advertencia.

.ip "20.07.89  2.2.0" 20
Foi corrigido a reloca��o em rela��o a s�mbolos absolutos
que estava incorreta com o uso da op��o "-r".
Alterado "pass2.c".

.sp
Utilizando-se a op��o "-r" agora n�o s�o mais impressas as
vari�veis indefinidas.
Alterado "pass1.c".

.ip "04.08.89  2.2.1" 20
Foi alterado o crit�rio de superposi��o de TEXT com DATA,
para possibilitar termos DATA abaixo do TEXT.

.ip "01.04.90  2.3.0" 20
Foram feitas diversas altera��es em todos m�dulos para substituir
todas as tabelas de aloca��o est�tica para aloca��o din�mica.
A tabela "hash" foi dobrada de tamanho.

.sp
Se n�o for dada a op��o "-e", ser� usado o s�mbolo "start".

.ip "19.12.90  2.3.1" 20
Alterado para trabalhar com s�mbolos externos de 31 caracteres.

.ip "08.01.91  2.3.2" 20
Introduzida a op��o "-.".

.ip "11.02.91  2.3.3" 20
O Algoritmo de "hash" dos s�mbolos foi convertido de colis�es internas
para externas, o que remove o limite do n�mero de
s�mbolos que podem ser armazenados.

.ip "13.04.95  3.0.0" 20
Adapta��o para o PC.

.ip "20.05.97  3.0.1" 20
O programa sofreu (ou deliciou-se com) uma revis�o global.

.sp
Al�m disto, consertado o problema do "-r", que n�o funcionava.

.ip "22.08.01  4.0.0" 20
Usando o novo formato da tabela de s�mbolos SYM.
.sp
Usando o novo formato da tabela de sinopse .LIBSYM.

.ip "26.09.01  4.2.0" 20
Alterado  passo 1, compondo inicialmente uma tabela de todos os s�mbolos
definidos em todas as bibliotecas.

.ip "11.06.02  4.3.0" 20
O programa foi completamente revisto, devido � inclus�o da tabela de
refer�ncias externas. Foi suprimida a op��o '-a'.

.ip "12.07.02" 20
Foi novamente totalmente revisto, para entender a op��o "-r", e
criar bibliotecas compartilhadas (op��o "-b").
