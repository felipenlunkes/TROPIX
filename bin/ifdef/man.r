.bp
.he 'IFDEF (cmd)'TROPIX: Manual de Refer�ncia'IFDEF (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "ifdef -"
realiza pr�processamentos parciais
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ifdef [-vr] [-D <var>] [-U <var>] <arquivo1> [<arquivo2]
ifdef [-vr] [-D <var>] [-U <var>] <arquivo> ... <diret�rio>
ifdef [-vr] [-D <var>] [-U <var>] -N <diret�rio>
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "ifdef" � um pr�processador simplificado,
realizando um subconjunto das opera��es do "cpp" (cmd).
A fun��o de "ifdef" � a de realizar pr�processamentos parciais, em que
apenas algumas das vari�veis de tempo de pr�processamento
s�o resolvidas.

.sp
O objetivo primordial de "ifdef" � o de, dados programas
com muitas op��es complexas de pr�processamento,
retirar os trechos de programas n�o desejados, para simplificar e
tornar os programas mais compreens�veis.

.sp
Em sua primeira forma, "ifdef" processa o <arquivo1>, colocando
o resultado em <arquivo2>. Se <arquivo2> n�o for dado, escreve
o resultado na sa�da padr�o.

.sp
Na segunda forma, um ou mais <arquivo>s s�o processados, e os
resultados colocados no <diret�rio> especificado, com os mesmos
nomes dos respectivos <arquivo>s.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes dos
<arquivo>s, que s�o lidos da entrada padr�o, um por linha.

.bc	/*************************************/
.sp
Normalmente, a sa�da de "ifdef" � utilizado adiante como entrada
para o pr�processador "cpp" numa etapa de compila��o,
quando ent�o s�o resolvidas as vari�veis restantes.
.ec	/*************************************/

.sp 2
Para a utiliza��o de "ifdef", d�-se uma lista de vari�veis
que devem ser consideradas "definidas" e outra lista de vari�veis
que devem ser consideradas "indefinidas".

.sp
S�o processadas:

.in +3
.ip 1. 3
As pseudo-intru��es "#ifdef", "#ifndef", "#else" e "#endif", que referenciam
alguma das vari�veis dadas.

.ip 2. 3
A pseudo-intru��o "#if", apenas no caso particular
.wo '"#if (0)".'

.ip 3. 3
As pseudo-intru��es "#define" e "#undef"
referentes �s vari�veis dadas, que
s�o eliminadas.

.ep
.in -3
.sp
Todos as demais pseudo-intru��es do pr�processador,
assim como os pseudo-intru��es  
referentes a vari�veis n�o dadas
s�o inclu�das sem altera��o nos <arquivo>s de sa�da.

.sp
As op��es do comando s�o:

.in +3 
.ip "-D <var>" 10
Considera a vari�vel <var> definida. 
Esta defini��o � mais forte do que os "#undef"s encontrados
nos <arquivo>s de entrada.
Todas as referencias a esta vari�vel s�o resolvidas,
incluindo ou n�o os trechos adequados dos <arquivo>s de entrada.
Os <arquivo>s de sa�da n�o cont�m mais refer�ncias a esta vari�vel.

.ip "-U <var>" 10
Considera a vari�vel <var> indefinida. 
Esta indefini��o � mais forte do que os "#define"s encontrados
nos <arquivo>s de entrada.
Todas as refer�ncias a esta vari�vel s�o resolvidas,
incluindo ou n�o os trechos adequados dos <arquivo>s de entrada.
Os <arquivo>s de sa�da n�o cont�m mais refer�ncias a esta vari�vel.

.ip "-N" 10
Le os nomes dos <arquivo>s de entrada da entrada padr�o, um por linha.

.ip "-v" 10
Lista os nomes dos <arquivo>s de entrada durante o processamento.

.ip "-r" 10
Lista as vari�veis residuais, isto �, as que s�o referenciadas
em um "#define", "#undef", "#ifdef" ou "#ifndef" e que n�o
foram dadas em nenhumas das listas de vari�veis do comando.
Estas s�o as vari�veis que ainda s�o referenciadas nos <arquivo>s
de sa�da.

.in -3 
.ep

.in
.sp
.b OBSERVA��O
.in 5
Deve-se lembrar que o programa processa a pseudo-instru��o "#if"
apenas no caso particular "#if (0)".

.sp
Isto significa que ele n�o reconhece que
.sp
.(l
		#if defined (ZETA)

� equivalente a

		#ifdef	ZETA
.)l
.sp
o que pode gerar programas de sa�da errados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cpp
.br

.in
.sp
.b EXEMPLO
.r
.in 5
.wo "				ifdef -D ALPHA -U BETA a.c b.c"
.br
.sp
pr�processa o arquivo "a.c", eliminando todas as refer�ncias �s
vari�veis de pr�processamento "ALPHA" e "BETA" (incluindo ou n�o
os trechos de "a.c" apropriados), pondo o resultado em "b.c".
As pseudo-instru��es referentes �s demais vari�veis s�o copiadas
sem mudan�as no arquivo "b.c". 

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
