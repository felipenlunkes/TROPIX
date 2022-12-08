.bp
.he 'DIFF (cmd)'TROPIX: Manual de Refer�ncia'DIFF (cmd)'
.fo 'Atualizado em 24.04.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "diff -"
comparador diferencial de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
diff [-efc] [-i <nm>] [-C <n>] [-b] <arquivo1> <arquivo2>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "diff" compara os arquivos de texto <arquivo1> e <arquivo2>,
indicando todas as linhas diferentes entre eles.

.sp
Se um dos <arquivo>s (mas n�o ambos) for "-", ele � lido da entrada padr�o.

.sp
Se um dos <arquivo>s (mas n�o ambos) for um diret�rio, ser� utilizado
o arquivo hom�nimo ao outro neste diret�rio.
Neste caso n�o pode ser dado "-".

.sp 2
As diferen�as entre os <arquivo>s podem ser indicadas de v�rios modos,
dependendo da chave dada:

.in +3
.ip -- 9
Se n�o for dada nenhuma das chaves abaixo, � emitida a sa�da "normal"
do comando, que consiste em linhas nas formas:
.sp
.(l
			n1     a  n3,n4
			n1,n2  d  n3
			n1,n2  c  n3,n4
.)l
.sp
Estas linhas s�o semelhantes a comandos do editor "ed" (cmd) para converter
o <arquivo1> no <arquivo2>. 
Os n�meros ap�s as letras s�o referentes ao <arquivo2>.
Como no "ed", se n1 = n2 ou n3 = n4, o par de n�meros �
abreviado em um n�mero �nico.

.sp
Al�m disto, se as letras "a" e "d" dos comandos forem intercambiadas,
e as linhas forem lidas de tr�s para frente, obtemos comandos para
converter o <arquivo2> no <arquivo1>. 

.sp
Seguindo cada uma destas linhas, vem todas as linhas afetadas do
<arquivo1> indicadas por "<", e todas as linhas afetadas do
<arquivo2> indicadas por ">".

.ip -e 9
Gera uma seq��ncia de comandos "a", "c" e "d" para o "ed", que converte
o <arquivo1> no <arquivo2>.

.ip -f 9
Gera uma seq��ncia de comandos semelhante � chave "-e",
na ordem inversa, mas que n�o pode ser utilizada pelo "ed".

.ip -c 9
Para cada diferen�a entre os <arquivo>s, mostra a regi�o afetada de cada
<arquivo> incluindo <n> linhas antes e <n> linhas ap�s a regi�o (o contexto).
O valor de <n> � normalmente 2, mas pode ser alterado atrav�s da op��o "-C"
(veja abaixo).

.sp
Se houve substitui��o de linhas, isto � indicado atrav�s 
do prefixo "!"; a remo��o de linhas do <arquivo1> � indicada pelo
prefixo "-"; a adi��o de linhas no <arquivo2> � indicada
atrav�s do prefixo "+".

.ip '-i <nm>' 9
Gera um arquivo "universal" contendo tanto o <arquivo1> como o 
<arquivo2> onde as distin��es entre os <arquivo>s  
est�o codificadas na forma das diretivas "#ifdef <nm>", "#ifndef <nm>",
"#else" e "#endif" do pr�processador da linguagem "C"
(veja "cpp" (cmd)).

.sp
A partir deste arquivo "universal" podemos recuperar tanto o <arquivo1>
como o <arquivo2> atrav�s do comando "ifdef" (cmd)
utilizando a op��o "-U <nm>" ou "-D <nm>" respectivamente.

.sp
Se os <arquivo>s n�o possu�rem macros/diretivas do "cpp", ou ainda,
se se tratarem de programas fontes em "C" que desejamos
compilar, podemos aplicar o "cpp" (ou "cc" (cmd)) diretamente
ao arquivo "universal".
 
.ep
.in -3

.sp 2
Al�m das chaves, temos ainda as op��es:

.in +3
.ip -b 8
Ignora brancos nos finais das linhas e considera outras seq��ncias
de brancos iguais entre si.

.ip '-C <n>' 8
O n�mero de linhas de contexto deve ser <n> ao inv�s de 2 (valor por omiss�o).

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Retorna 0 para arquivos iguais, 1 para arquivos diferentes e 2 para
arquivos inacess�veis ou erros. 

.in
.sp
.b OBSERVA��ES
.in 5
O comando "diff" obt�m o conjunto m�nimo de diferen�as, exceto em
(raros) casos patol�gicos.  

.sp
Uma seq��ncia de comandos gerada pelas chaves "-e" e "-f"
pode n�o funcionar corretamente se alguma das linhas modificadas
consistir de apenas um ponto.

.sp
Um arquivo "universal" gerado pela chave "-i"
pode n�o funcionar corretamente se alguma das linhas modificadas
consistir justamente de uma diretiva para o "cpp".

.(t
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cmp, comm, ed, cpp, cc, ifdef, show
.br
.)t

.in
.sp
.b ARQUIVO
.in 5
/tmp/diff??????

.in
.sp
.b EXEMPLO
.in 5
Uma das maneiras mais c�modas para a utiliza��o do comando
utiliza a sa�da das diferen�as com contexto associado ao comando "show":

.sp
.ce
	diff -c fonte.c ../old | show 


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
