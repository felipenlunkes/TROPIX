.bp
.he 'SORT (cmd)'TROPIX: Manual de Refer�ncia'SORT (cmd)'
.fo 'Atualizado em 05.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "sort -"
ordena e/ou intercala arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
sort [-vcraidf]   [-o <sa�da>] [-t <d>] [-k "x:y.zot ... "]
						[<entrada>]

sort -m [-vraidf] [-o <sa�da>] [-t <d>] [-k "x:y.zot ... "]
						<entrada> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "sort" ordena/intercala as linhas
dos arquivos de <entrada> dados. O resultado da ordena��o/intercala��o
� escrito na sa�da padr�o ou no arquivo <sa�da>, se este for dado
(atrav�s da op��o "-o").

.sp
Em sua primeira forma (sem a op��o "-m"), "sort" ordena as linhas
do arquivo <entrada> (ou da entrada padr�o se este n�o for dado).

.sp
Em sua segunda forma (com a op��o "-m"), "sort" intercala ("merge") as linhas
dos v�rios arquivos <entrada> ..., supondo que as linhas destes arquivos
j� estejam ordenadas.

.sp
As compara��es s�o realizadas baseadas em uma ou mais chaves
contidas nas linhas de entrada (veja as op��es abaixo).
Normalmente (isto �, sem op��es), � considerada apenas uma chave
(a linha inteira), e a ordena��o � lexicogr�fica pelos caracteres
na ordem normal da m�quina.

.sp
As op��es do comando s�o:

.in +3
.ip -m
Intercala��o: ao inv�s de uma ordena��o, "sort" realiza a intercala��o
("merge") das linhas dos v�rios arquivos <entrada> ..., supondo que
as linhas destes arquivos j� estejam ordenadas.

.ip -v
Verboso: "sort" imprime algumas informa��es acerca da ordena��o/intercala��o.

.ip -c
Verifica se o arquivo j� est� ordenado: apenas escreve uma mensagem informando
se o arquivo de entrada est� ou n�o ordenado (N�O escreve a sa�da ordenada).
Al�m disto, o c�digo de retorno de "sort" � ZERO se o arquivo de entrada
j� est� ordenado e um valor N�O-NULO em caso contr�rio.
Esta op��o � util (por exemplo) para certificar-se de que as diversas entradas
de uma futura intercala��o est�o ordenadas.

.ip -r
Ordem reversa: inverte o sentido das compara��es, isto �, ordena
descendentemente ao inv�s de ascendentemente.

.ip -a
Tipo de ordena��o LEXICOGR�FICA (tipo por omiss�o).

.ip -i
Tipo de ordena��o ISO: Usa o codigo padr�o ISO (BRASCII ou CBII)
para as compara��es. Com este tipo de ordena��o, as letras acentuadas
t�m o mesmo valor das letras sem acento, e � o tipo 
recomendado quando as chaves contem letras acentuadas
(veja "iso" (fmt)).

.ip -d
Tipo de ordena��o DICION�RIO: para as compara��es s�o levados em
conta apenas as letras e d�gitos das chaves, e al�m disto, as letras
mai�sculas/min�sculas/com acento/sem acento t�m o mesmo valor.

.ip -f
Tipo de ordena��o FOLD: as letras mai�sculas e min�sculas das chaves t�m
o mesmo valor (embora as min�sculas precedam as mai�sculas numa ordena��o
ascendente).

.ip -o
Escreve o arquivo ordenado em <sa�da> ao inv�s de "stdout".

.ip -t
Utiliza o caracter <d> como delimitador de campos:
Normalmente, os campos s�o delimitados por um ou mais <sp> ou <ht> (n�o
existem campos vazios). Com a op��o "-t", o delimitador usado ser�
o caractere <d>. Neste caso, cada ocorr�ncia de <d> � significativa:
a cadeia "...<d><d>..." cont�m um campo vazio. A delimita��o dos campos
de uma linha � importante para a especifica��o das chaves. 

.ip -k
Define as chaves pelas quais a ordena��o deve ser feita:
ap�s a delimita��o dos v�rios campos de uma linha (veja acima),
os seguintes par�metros podem ser dados para definir quais os trechos
de quais campos ser�o utilizados como chaves:

.in +5
.ip "x -"
N�mero do campo: se for zero, a chave considerada � a linha
inteira. Neste caso, o n�mero do campo pode ser omitido mas o
caractere ":" deve ser especificado caso outros par�metros sejam
desejados para a ordena��o.

.ip "y -"
N�mero do caractere dentro do campo onde come�a a chave:
se n�o for especificado, a chave come�a no in�cio do campo.

.ip "z -"
Largura da chave em caracteres: se n�o for especificada,
a chave termina no final do campo.

.ip "o -"
Letra que define o sentido da ordena��o:
"a" para ascendente e "d" para descendente. 
Se for omitido, a ordena��o ser� ascendente.

.ip "t - "
Letra que define o tipo da ordena��o:
"a" para LEXICOGR�FICO, "i" para ISO, "d" para DICION�RIO e "f" para FOLD
(veja as respectivas op��es acima).
Se for omitido, a ordena��o ser� LEXICOGR�FICA.

.ep
.in -5

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O programa "sort" (em sua vers�o atual) � capaz de ordenar
apenas arquivos que caibam integralmente na mem�ria interna dispon�vel do
sistema. Se isto n�o for o caso, � responsabilidade do usu�rio
dividir o arquivo em peda�os menores, orden�-los
separadamente e depois usar uma intercala��o (op��o "-m").

.sp
O programa "sort" � orientado por linhas (de tamanho vari�vel),
isto �, ele assume que os registros sejam delimitados por <nl>.
Caso este n�o seja o caso, tamb�m � responsabilidade do usu�rio
inserir um caractere <nl> ao final de cada registro.

.sp
Na vers�o atual da opera��o de intercala��o, assume-se que as linhas
n�o tenha mais de 1024 caracteres.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
comm, uniq
.br
.wo "(libc):"
qsort, qtsort, cmptb
.br
.wo "(fmt): "
iso
.br

.in
.sp
.b EXEMPLOS
.in 5
.nf
		sort alpha
.fi

.sp
ordena o arquivo "alpha" em ordem ascendente e p�e a sa�da em "stdout".

.sp 2
.nf
		sort -t : -k "3 4 1" beta
.fi

.sp
ordena o arquivo "beta", que tem campos delimitados pelo
caractere ":", em ordem ascendente considerando primeiro o
campo 3, depois o 4 e finalmente o 1.

.sp 2
.nf
	sort -t : -m -k "3 4 1" arq1 arq2 arq3 arq4 arq5
.fi

.sp
faz a intercala��o dos cinco arquivos mencionados 
seguindo as chaves conforme o exemplo anterior.

.sp 2
.nf
		sort -k :ai
.fi

.sp
ordena o arquivo lido do "stdin" em ordem ascendente utilizando tipo de
ordena��o ISO usando a linha inteira como chave.

.sp 2
.nf
		sort -t = -k "3:2.3af 4:3.2di" est�tuas
.fi

.sp
ordena o arquivo "est�tuas", que tem campos delimitados pelo
caractere "=", em primeiro lugar pelo campo 3 a partir da
posi��o 2 com uma chave de largura 3 em ordem ascendente e
considerando letras mai�sculas e min�sculas indistintamente e,
a seguir, pelo campo 4 a partir da posi��o 3 com uma chave de
largura 2 em ordem descendente utilizando tipo de ordena��o ISO.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
