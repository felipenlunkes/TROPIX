.bp 1
.he 'A.OUT (fmt)'TROPIX: Manual de Refer�ncia'A.OUT (fmt)'
.fo 'Atualizado em 28.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "a.out -"
formato do m�dulo objeto
.br

.in
.sp
.b DESCRI��O
.sp
.in 5
Este documento descreve o formato dos m�dulos objeto do sistema TROPIX.
S�o descritas as seguintes estruturas:
cabe�alho, tabela de s�mbolos e reloca��o.
Outros detalhes podem ser vistos no arquivo de inclus�o <a.out.h>.

.sp
.b
Componentes de um m�dulo objeto
.r
.ip
M�dulos objeto no sistema TROPIX s�o gerados como sa�da
do montador "as" (cmd), e por raz�es de homogeneidade, seus nomes devem
conter o sufixo ".o".
Um m�dulo objeto � composto das seguintes partes:

.in +5
.ip a. 3
Cabe�alho. Al�m de permitir a identifica��o do arquivo como objeto,
o cabe�alho cont�m informa��es sobre os tamanhos de todas as outras partes
integrantes do m�dulo. S�o as seguintes as informa��es presentes:

.in +5
.ip - 2
Computador de destino.

.ip - 2
N�mero m�gico, que identifica o m�dulo como objeto. Pode ser (em octal)
0407 ou 0410, indicando respectivamente que o processo de cuja imagem far�
parte o m�dulo em quest�o ser� regular ou reentrante.

.ip - 2
Identifica��o da vers�o do m�dulo objeto.

.ip - 2
Diversos indicadores informando se o m�dulo � execut�vel, se
� necess�rio o processador de ponto flutuante, etc...

.ip - 2
Data e hora da gera��o do m�dulo.

.ip - 2
N�mero de s�rie do computador de destino.

.ip - 2
Endere�o (virtual) do in�cio da se��o TEXT.

.ip - 2
Endere�o (virtual) do in�cio da se��o DATA.

.ip - 2
Endere�o inicial de execu��o do programa.

.ip - 2
Tamanho (em bytes) da se��o TEXT.

.ip - 2
Tamanho (em bytes) da se��o DATA.

.ip - 2
Tamanho (em bytes) da se��o BSS.

.ip - 2
Tamanho (em bytes) da tabela de s�mbolos.

.ip - 2
Tamanho (em bytes) da reloca��o do TEXT.

.ip - 2
Tamanho (em bytes) da reloca��o do DATA.

.ip - 2
Tamanho (em bytes) da tabela de n�meros de linha para ser
utilizado pelo depurador simb�lico "wsdb" (cmd).

.ip - 2
Tamanho (em bytes) da tabela de s�mbolos para ser
utilizado pelo depurador simb�lico "wsdb" (cmd).

.in -5
.ip b. 3
.wo "Se��o TEXT."
Nesta se��o do m�dulo encontram-se normalmente instru��es de m�quina
que foram traduzidas pelo "as", que constituir�o a parte execut�vel
do m�dulo.

.ip c. 3
.wo "Se��o DATA."
Encontram-se na se��o DATA as �reas de mem�ria destinadas �s vari�veis
inicializadas do m�dulo.

.ip d. 3
.wo "Tabela de s�mbolos."
A tabela de s�mbolos de um m�dulo � composta de entradas que descrevem
a natureza dos s�mbolos constantes daquele m�dulo. O montador "as"
gera, se nada for especificado, entradas apenas para os s�mbolos 
externos, j� que apenas estes s�mbolos
realmente participam do processo de "link-edi��o". No entanto, entradas
podem ser geradas para todos os s�mbolos, se desejado.
O formato da tabela ser� visto no pr�ximo item.

.ip e. 3
Estrutura de reloca��o para TEXT.
O processo de "link-edi��o" consiste, acima de tudo, em atribuir endere�os
definitivos a posi��es do c�digo consideradas reloc�veis pelo montador.
Para cada posi��o reloc�vel � gerada uma entrada na estrutura respectiva,
dependendo da se��o � qual ela pertence. Neste caso, aplica-se �s
posi��es que se encontram na se��o TEXT.

.ip f. 3
Estrutura de reloca��o para DATA.
O mesmo que o item anterior aplicado �s posi��es que se encontram
na se��o DATA.

.ip g. 3
Tabela dos n�meros das linhas.
Cont�m informa��o sobre os n�meros das linhas do c�digo fonte
que geraram este m�dulo objeto, de forma que o depurador simb�lico
"wsdb" possa
identificar as linhas do c�digo fonte a partir do m�dulo objeto.

.ip h. 3
Tabela dos s�mbolos para o depurador simb�lico "wsdb".
Cont�m informa��o sobre as vari�veis do c�digo fonte
que geraram este m�dulo objeto, de forma que "wsdb" possa
consultar/alterar as diversas vari�veis do m�dulo objeto
durante a execua��o.

.in -5
.ep
.(t
.b
Formato da tabela de s�mbolos
.r

.ip
Uma entrada na tabela de s�mbolos cont�m as seguintes informa��es:
.)t

.in +5
.ip a. 3
Nome do s�mbolo.
Um identificador de at� 31 caracteres.

.ip b. 3
Tipo do S�mbolo, que pode ser:

.in +3
.ip "UNDEF:" 7
O s�mbolo ainda n�o possui tipo associado.

.ip "ABS:  " 7
O s�mbolo � absoluto.

.ip "TEXT: " 7
O s�mbolo pertence � se��o TEXT.

.ip "DATA: " 7
O s�mbolo pertence � se��o DATA.

.ip "BSS:  " 7
O s�mbolo pertence � se��o BSS.

.ep
.in -3
.ip c. 3
Uma indica��o de s�mbolo externo.

.ip d. 3
Uma indica��o de s�mbolo j� referenciado.

.ip e. 3
O valor associado ao s�mbolo.

.ep
.in -5
.ip
S�mbolos declarados em ".common" referenciam o in�cio de uma �rea
a ser reservada pelo "link-editor" na se��o BSS, cujo tamanho vem 
especificado como valor do s�mbolo. Um s�mbolo nestas condi��es �
inicialmente considerado do tipo UNDEF
e o "link-editor" percebe que se trata de
".common" em virtude de seu valor ser diferente de zero.

.sp 
Embora o usu�rio tenha a op��o de ver inclu�dos na tabela mesmo os
s�mbolos locais, o "link-editor" simplesmente ignorar� tais entradas na 
tabela, servindo apenas para onerar o arquivo em tamanho.

.sp
O "link-editor" testa tamb�m se os s�mbolos declarados s�o utilizados 
realmente pelo programa ou n�o, produzindo uma advert�ncia na segunda
hip�tese. Esta advert�ncia � particularmente �til quando, por exemplo,
durante a depura��o de um programa inclu�mos vari�veis ou mesmo
fun��es auxiliares e esquecemos de remov�-las por fim. O "link-editor"
avisar� que tais objetos nunca s�o referenciados pelo programa, sendo
de bom alvitre remov�-los.

.ep
.sp
.b
Formato das estruturas de reloca��o
.r
.ip
Cada entrada da estrutura de reloca��o � constitu�da pelas seguintes
informa��es:

.in +5
.(t
.ip a. 3
Tamanho do objeto a ser relocado:

.in +3
.ip "RBYTE: " 7
N�o � utilizado, pois n�o � suportado pelo "link-editor".
.)t

.ip "RWORD: " 7
O objeto a ser relocado � uma palavra (WORD).

.ip "RLONG: " 7
O objeto a ser relocado � um longo (LONG).

.ep
.in -3
.ip b. 3
Tipo da Reloca��o:
.in +3

.ip "RTEXT: " 9
A posi��o refere-se a um endere�o da se��o TEXT.

.ip "RDATA: " 9
A posi��o refere-se a um endere�o da se��o DATA.

.ip "RBSS:  " 9
A posi��o refere-se a um endere�o da se��o BSS.

.ip "REXT:  " 9
A posi��o relocada ser� atribu�do um valor que depender� de um s�mbolo
ainda indefinido. Neste caso, acrescentamos a posi��o deste s�mbolo dentro
da tabela de s�mbolos como informa��o adicional � estrutura de reloca��o.

.ip "REXTREL:" 9
Esta reloca��o � uma variante da anterior (REXT) necess�ria para os
processadores da fam�lia INTEL (386, 486, PENTIUM), que n�o possuem
desvios com endere�os absolutos.

.ep
.in -3
.ip c. 3
Deslocamento dentro da se��o.
Esta informa��o indica a quantos bytes do in�cio da se��o figura a
posi��o a ser relocada.

.ip d. 3
Posi��o do s�mbolo na tabela.
Esta informa��o s� tem sentido quando o tipo da reloca��o � REXT ou REXTREL,
conforme j� explicado acima.

.in -5
.ep
.sp
.b
Formato da tabela de n�meros das linhas.
.r
.ip
Cada entrada cont�m um n�mero de linha do programa fonte
juntamente com o respectivo endere�o do c�digo objeto. 

.ep
.sp
.b
Formato da tabela dos s�mbolos do depurador simb�lico "wsdb".
.r
.ip
O formato desta tabela � espec�fica do "wsdb", e n�o ser� discutida
aqui.

.ep
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ld, mklib, nm, wsdb
.br
.wo "(sys): "
exec
.br
.wo "(fmt): "
lib
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/a.out.h

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
