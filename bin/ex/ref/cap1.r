.bp
.sp 5
.nf
     *********************************************************
     *                                                       *
     *                      CAP�TULO 1                       *
     *                                                       *
     *                CONCEITOS FUNDAMENTAIS                 *
     *                                                       *
     *********************************************************
.fi
.sp 4

.pp
.b
Editores de texto
.r
s�o programas interativos para cria��o 
e modifica��o de
.b
textos.
.r
Textos s�o geralmente documentos como este ou c�digo fonte de programas
e s�o armazenados em mem�ria secund�ria no Sistema de Arquivos.
Tipicamente, a edi��o de um texto consiste em copi�-lo
para uma �rea intermedi�ria de mem�ria,
modific�-lo por meio de uma s�rie de comandos
dados pelo usu�rio em um terminal
e, finalmente, copi�-lo de volta para o Sistema de Arquivos,
a partir do que o texto modificado torna-se efetivo.

.pp
O utilit�rio "vi" � um editor 
.b
visual
.r
de textos,
isto significa que o "vi" transforma o v�deo do terminal
em uma 
.b
janela
.r
sobre o texto em edi��o
e o cursor do terminal em um apontador no texto.
Existem comandos que movem a janela
e comandos que movem o cursor em unidades de linhas, palavras ou caracteres.
Assim, qualquer parte do texto pode ser alcan�ada e observada
e qualquer caractere do texto pode ser apontado.
De modo geral, os comandos de edi��o s�o relativos � posi��o corrente
(linha e caractere apontados pelo cursor)
e as altera��es no texto s�o acompanhadas instantaneamente pelo usu�rio
atrav�s da janela sobre o texto.

.pp
O editor "vi" tem dois modos principais de funcionamento:
o modo 
.b Visual
.r
e o modo 
.b
Comandos.
.r
O modo Visual � o modo principal e inicial do editor "vi".
No modo Visual podemos passear pelo texto
e realizar altera��es localizadas pelo cursor.
O modo Comandos � usado para  escrita e leitura no Sistema de Arquivos,
para intera��o com o Interpretador de Comandos ("sh" (cmd))
e para a realiza��o de opera��es de edi��o orientadas a linhas.

.pp
Alguns caracteres especiais s�o importantes
para a utiliza��o do editor "vi",
por isso � importante localiz�-los no teclado do terminal.
O caractere ISO <esc> deve estar pr�ximo ao canto superior esquerdo,
provavelmente denominado ESC ou ALT.
Os caracteres <cr> e <nl> devem estar localizados
pr�ximos e no lado direito; eles s�o normalmente indicados por
CR ou ENTER e LF ou NL respectivamente.
Os caracteres <bs> e <del>
podem ser encontrados sob os nomes BS e DEL.
Os caracteres ISO de controle s�o gerados
teclando-se uma letra enquanto a tecla CTRL � pressionada,
e ser�o representados neste manual na forma <^X>,
onde "X" � a letra teclada.

.pp
Os caracteres de controle da comunica��o com terminais
estabelecidos pelo comando "stty"
s�o reconhecidos pelo editor "vi"
em determinados contextos,
normalmente conservando as suas fun��es originais.
Os caracteres de controle referenciados neste manual s�o os seguintes:
<erase>, <aerase>, <word>, <kill>, <retype> e <eol>.

.pp
Nos pr�ximos cap�tulos ser�o descritos todos os comandos do editor "vi".
Quando oportuno, ser� indicado junto aos comandos
e entre par�nteses os verbos ou nomes em ingl�s
que motivaram a escolha de determinados caracteres para represent�-los.
