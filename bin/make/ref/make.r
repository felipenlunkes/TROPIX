.bp
.tp
.sp 10
.nf
      *******   *******  *******   *******    *    *     *
         *      *     *  *     *   *     *    *     *   *
         *      *     *  *     *   *     *    *      * *
         *      *******  *     *   *******    *       *
         *      *  *     *     *   *          *      * *
         *      *   *    *     *   *          *     *   *
         *      *    *   *******   *          *    *     *
.fi
.sp 10
.ce
MAKE - Gerenciador de Manuten��o de Programas
.sp 2
.ce
Vers�o 3.2.3
.sp 4
.ce
Guia
.sp 11
.ce
Dezembro de 1999
.bp
.sp 10
.ce
CONTE�DO
.sp 5
.nf
	Cap. 1 - Introdu��o ...........................	 2

	Cap. 2 - Defini��es B�sicas ...................  3

	Cap. 3 - Formato do Arquivo de Descri��o ......  5

	Cap. 4 - Macros ...............................	 7

	Cap. 5 - Uso do Comando ....................... 10
.fi
.bp
.he 'Sistema TROPIX'Guia'MAKE'
.fo 'Escrito em 13.12.99'Vers�o 3.2.3'Pag. %'
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 1			     *
     *							     *
     *	     		INTRODU��O			     *
     *							     *
     *********************************************************
.fi
.sp 4
.pp
Normalmente, um programa grande e complexo � dividido em m�dulos
de tamanhos menores, mais f�ceis de manipular.
Estes m�dulos em geral recebem tratamentos diversos:
alguns s�o programas fonte em "C"
e necessitam ser processados pelo compilador "C",
outros s�o programas fonte em "assembly"
e necessitam ser processados pelo montador, etc...
Os m�dulos objetos gerados por este tradutores
s�o em seguida geralmente "link-editados" com
certas bibliotecas, e o m�dulo final instalado em algum diret�rio.

.pp
Infelizmente, � muito f�cil para um programador esquecer
que arquivos dependem de outros, que arquivos
foram modificados recentemente e a seq��ncia exata de opera��es
necess�rias para construir uma nova vers�o do programa.
Ap�s a edi��o de v�rios arquivos, � natural que se perca a vis�o
geral dos arquivos modificados e dos m�dulos
objetos ainda v�lidos, j� que a altera��o de um arquivo
de declara��es ("*.h") pode tornar obsoletos dezenas de m�dulos
objetos.

.pp
Esquecer de recompilar um m�dulo que foi modificado ou que
inclui um arquivo de declara��es modificado resultar� em um programa
que n�o executa corretamente.
Por outro lado, recompilar sistematicamente todos os m�dulos a cada
altera��o desperdi�a tempo.

.pp
O programa "make", objeto deste manual, automatiza muitas das atividades
de desenvolvimento e manuten��o de programas. Se as informa��es
de interdepend�ncia dos arquivos e a seq��ncia de opera��es
s�o armazenadas em um arquivo (chamado de "arquivo de 
descri��o"), o simples comando
.sp
.nf
		make
.fi
.sp
� suficiente para atualizar os arquivos necess�rios,
independentemente do n�mero de arquivos editados desde o �ltimo
"make". Na maioria dos casos, o arquivo de descri��o � simples,
e n�o necessita de mudan�as freq�entes.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 2			     *
     *							     *
     *	     	    DEFINI��ES B�SICAS			     *
     *							     *
     *********************************************************
.fi
.sp 4
.pp
A opera��o b�sica do "make" � a atualiza��o de um m�dulo, que
consiste em:
.in 2
.ip 1. 3
providenciar para que todos os arquivos dos quais
o m�dulo dependa existam e estejam atualizados;
.ip 2. 3
criar o m�dulo (se ele n�o existe), ou atualiz�-lo (caso n�o esteja atualizado)
em rela��o �s suas depend�ncias, executando uma seq��ncia de opera��es
especificada.
.in 0
.lp
Vamos dar um exemplo: 
um programa "pgm" � criado a partir da 
compila��o e "link-edi��o" de tr�s m�dulos escritos em "C": 
"md1.c", "md2.c" e "md3.c". Os m�dulos "md1.c" e "md2.c" usam declara��es 
definidas em "md0.h" (isto �, cont�m a linha "#include md0.h").
.pp
As interdepend�ncias e opera��es necess�rias
para a cria��o do programa podem ser resumidas no seguinte texto:
.sp
.nf
	pgm:	md1.o md2.o md3.o
		cc -n -o pgm md1.o md2.o md3.o

	md1.o:	md0.h md1.c
		cc -O -c md1.c

	md2.o:	md0.h md2.c
		cc -O -c md2.c

	md3.o:	md3.c
		cc -O -c md3.c
.fi
.pp
Se este texto estiver em um arquivo com o nome de "Makefile",
o comando
.sp
.nf
	make
.fi
.sp
ir� executar as opera��es estritamente necess�rias para criar/recriar
o programa "pgm" ap�s qualquer mudan�a realizada em alguns dos
arquivos "md1.c", "md2.c", "md3.c" ou "md0.h". 
.pp
Suponhamos que este programa ("pgm") seja novo, isto �, os seus componentes
nunca foram compilados. Neste caso, o "make" far� executar 
os seguintes comandos:
.sp
.nf
		=> cc -c md1.c
		=> cc -c md2.c
		=> cc -c md3.c
		=> cc -n -o pgm md1.o md2.o md3.o
.fi
.sp
O "make" lista cada comando antes de execut�-lo, precedendo-o do sinal "=>".
.pp
Suponhamos agora que, ao executarmos o programa "pgm", constatamos a
necessidade de uma altera��o no m�dulo "md2.c".
Se, ap�s a edi��o de "md2.c", invocarmos novamente o "make", ser�o
executados apenas os seguinte comandos:
.sp
.nf
		=> cc -c md2.c
		=> cc -n -o pgm md1.o md2.o md3.o
.fi
.sp
que, como podemos ver, s�o exatamente os necess�rios.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 3			     *
     *							     *
     *	       FORMATO DO ARQUIVO DE DESCRI��O		     *
     *							     *
     *********************************************************
.fi
.sp 4

.pp
Normalmente, o comando "make" procura o arquivo de descri��o no diret�rio
em que � invocado com os nomes "Makefile" ou "makefile", nesta ordem.
Caso seja chamado com a op��o "-f" (ver "make" (cmd)),
outros nomes podem ser utilizados.

.pp
O arquivo de descri��o � constitu�do de quatro tipos de entradas:
.in 2
.ip 1. 3
entradas para especifica��o de depend�ncias;
.ip 2. 3
entradas para declara��o de alvos virtuais;
.ip 3. 3
entradas para declara��o de macros;
.ip 4. 3
entradas para inclus�o de macros como vari�veis do ambiente.
.in 0

.pp
As entradas para especifica��o de depend�ncias podem estender-se por diversas
linhas consecutivas do arquivo de descri��o, possuindo o seguinte
formato geral:

.sp
.nf
	<alvos>:	<pr�-requisitos>
			<opera��o 1>
			<opera��o 2>
			   .   .
			   .   .
			<opera��o n>
.fi

.sp
onde <alvos> s�o os nomes do m�dulos a serem criados/atualizados e
<pr�-requisitos> s�o nomes de m�dulos dos quais os alvos dependem.
Os nomes podem ser separados por brancos (<sp>) ou tabuladores (<ht>).

.pp
As linhas <opera��o 1> a <opera��o n> cont�m os comandos necess�rios �
cria��o/atualiza��o dos alvos e devem iniciar com um tabulador (<ht>).

.pp
O conjunto de opera��es � executado, visando a cria��o/atualiza��o dos
alvos, quando:

.in 2
.ip 1. 3
s�o especificados pr�-requisitos e o tempo de �ltima modifica��o de um
deles for mais recente que o tempo de �ltima modifica��o de um dos alvos;
.ip 2. 3
n�o s�o especificados pr�-requisitos;
.ip 3. 3
� especificada a palavra reservada ".exist" no lugar de pr�-requisitos
e um dos alvos � inexistente.
.in 0

.pp
As opera��es s�o listadas na tela imediatamente antes de
serem executadas; havendo erros, o processamento do "make" � interrompido.
Podemos utilizar as variantes <@opera��o>, para que ela n�o seja listada,
ou <-opera��o>, para que o "make" continue o processamento
mesmo em caso de erro nesta opera��o.

.pp
Normalmente, o conjunto de opera��es especificadas para atualizar um
alvo deve produzir altera��o do tempo de �ltima modifica��o do alvo,
tornando-o mais recente que todos os seus pr�-requisitos, como 
� o caso de compila��es e link-edi��es.
Do contr�rio, a cada chamada do "make", este conjunto ser�
re-executado.

.pp
Quando uma linha termina pelo caractere "\", a linha seguinte � considerada
uma continua��o. Isto permite estender as listas de alvos e pr�-requisitos
ou mesmo uma linha de opera��o.

.pp
O arquivo de descri��o pode conter coment�rios,
que s�o iniciados pelo caractere "#" e se estendem at� o fim da linha
em que iniciam.
Linhas vazias s�o ignoradas.

.pp
Normalmente, alvos correspondem a arquivos, que devem existir fisicamente.
Alvos virtuais s�o declarados com entradas do tipo
.sp
.ce
".virtual <alvo> ..."
.pp
Tais alvos n�o correspondem a arquivos, funcionando apenas como �ndices
para seq��ncias de comandos. Um exemplo comum de aplica��o � declarar
um alvo cujo efeito � copiar o programa-objeto final para o diret�rio
apropriado. 
.pp
Utilizando o exemplo anterior, vamos introduzir o alvo virtual "cp",
que possui como pre-requisito "pgm".
A opera��o utilizada para atualizar o alvo "cp" consiste em copiar "pgm"
para o diret�rio "/usr/bin".
.sp
.nf
	.virtual cp

	pgm:	md1.o md2.o md3.o
		cc -n -o pgm md1.o md2.o md3.o

	md1.o:	md0.h md1.c
		cc -O -c md1.c

	md2.o:	md0.h md2.c
		cc -O -c md2.c

	md3.o:	md3.c
		cc -O -c md3.c

	cp:	pgm
		cp -f pgm /usr/bin
.fi
.pp
O comando
.sp
.nf
	make cp
.fi
.sp
compila e linkedita, se necess�rio, o programa "pgm", copiando-o para
o diret�rio "/usr/bin".

.pp
As entradas para declara��o de macros e inclus�o no ambiente ser�o analisadas
no pr�ximo cap�tulo.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 4			     *
     *							     *
     *	       		  MACROS			     *
     *							     *
     *********************************************************
.fi
.sp 4
.pp
O "make" prov� um mecanismo simples de substitui��o de macros no
arquivo de descri��o.

.pp
Uma entrada no arquivo de descri��o para declara��o de macro tem a forma:
.sp
.nf
	<macro> = <texto>
.fi
.sp
onde <macro> � um identificador (seq��ncia de letras, d�gitos e "_" iniciada
por letra) e <texto> � uma seq��ncia qualquer de caracteres.
O sinal de "=" pode ser precedido e sucedido de separadores (<sp> ou <ht>),
que s�o ignorados. O <texto> se encerra com o fim da linha de declara��o,
ou prossegue em linhas de continua��o com o uso do caractere "\".

.pp
S�o exemplos de declara��es de macros:
.sp
.nf
	PGM	= pgm
	OBJ	= md1.o	\
		  md2.o \
		  md3.o
	FLAGS	= -n
.fi

.pp
A refer�ncia a uma macro consiste em preceder seu nome do caractere "$",
como "$PGM", "$OBJ" e "$FLAGS". Este mecanismo provoca a inser��o do
texto da macro no lugar onde foi referenciada.

.pp
�s vezes, � conveniente, na refer�ncia a uma macro, delimitar seu nome por
par�nteses: $(PGM), $(OBJ) e $(FLAGS).

.pp
Com as defini��es acima, o arquivo de descri��o do cap�tulo 2
pode ser reescrito da seguinte maneira:
.sp
.nf
	PGM	= pgm
	OBJ	= md1.o md2.o md3.o
	INC	= md0.h
	CC	= cc
	CFLAGS	= -O
	LDFLAGS	= -n

	$PGM:	$OBJ
		$CC $LDFLAGS -o $PGM $OBJ

	md1.o:	md1.c $INC
		$CC $CFLAGS -c md1.c

	md2.o:	md2.c $INC
	 	$CC $CFLAGS -c md2.c

	md3.o:	md3.c
		$CC $CFLAGS -c md3.c
.fi

.pp
Com a utiliza��o de macros, evitamos a repeti��o dos nomes dos
m�dulos, o que pode abreviar substancialmente o tamanho do arquivo
de descri��o, bem como facilitar-lhe a manuten��o.

.pp
Existem algumas macros especiais, para as quais o pr�prio "make"
atribui valores intrinsecamente.
Seus nomes s�o: "$", "@", "*", "<" e "?", e correspondem aos seguintes
textos:

.in 1
.ip $$ 4
o caractere "$";
.ip $@ 4
nome do alvo a criar/atualizar;
.ip $* 4
nome do alvo a criar/atualizar sem a extens�o;
.ip $< 4
nomes dos pr�-requisitos dos quais dependem o alvo;
.ip $? 4
nomes dos pr�-requisitos mais recentes que o alvo e, portanto, causadores
de sua atualiza��o/cria��o.
.in 0
.lp
Os valores das macros @, *, < e ? s�o atualizados de acordo com a lista de
depend�ncias que estiver sendo processada durante a execu��o. Estas
macros s� t�m utilidade em linhas de comandos.

.sp
 Exemplo:

.sp
.nf
	pgm:	md1.o md2.o md3.o
		cc -n -o pgm $<

	md1.o:	md0.h md1.c
		cc -c $*.c

	md2.o:	md0.h md2.c
		cc -c md2.c

	md3.o:	md3.c
		cc -c md3.c

	print:	md0.h md1.c md2.c md3.c
		pr $?
		touch print
.fi

.pp
Repare o m�dulo "print": a id�ia � imprimir os programas fontes que tenham
sido alterados desde a �ltima impress�o. 

.pp
Al�m das macros definidas no arquivo de descri��o, todas as cadeias do
ambiente (ver "environ" (fmt)) s�o automaticamente dispon�veis como macros.

.pp
O terceiro tipo de entrada poss�vel em um arquivo de descri��o destina-se
a inserir como vari�veis do ambiente macros declaradas no arquivo de
descri��o ou transmitidas ao "make" atrav�s da op��o "-D" (ver "make" (cmd)).
Com linhas do tipo

.sp
.ce
".putenv <macro> ..."
.sp

colocamos macros selecionadas como vari�veis no ambiente,
para que os programas executados
possam obter os seus valores (por exemplo, o "cpp" (cmd)).

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 5			     *
     *							     *
     * 		      USO DO COMANDO			     *
     *							     *
     *********************************************************
.fi
.sp 4
.pp
A sintaxe do comando "make" �
.sp
.nf
	make [-intvab] [-f <desc>] [-D <macro>=<valor>] ...
	<m�dulo> ...
.fi

.pp
A op��o "-i" funciona como se todas as linhas de comandos no arquivo
de descri��o estivesses precedidas de "-" (ignorar erros).

.pp
A op��o "-n" permite
listar as opera��es necess�rias � atualiza��o sem execut�-las.

.pp
Cuidado com a op��o "-t", pois ela atualiza as datas de modifica��o
dos arquivos sem na realidade atualiz�-los.
Com isto, a mem�ria dos m�dulos n�o atualizados � perdida.

.pp
A op��o "-v" explica o motivo das atualiza��es.

.pp
A op��o "-a" apenas lista os alvos especificados no arquivo de
descri��o, exceto os da forma "*.o". Se for duplicada ("-aa"),
todos os alvos, sem exce��o, s�o listados.

.pp
A op��o "-b" provoca a atualiza��o de todos os m�dulos,
independentemente das datas.

.pp
A op��o "-f" permite especificar o nome do arquivo de descri��o.

.pp
A op��o "-D" define a macro <macro> com o texto <valor>.
Esta defini��o prevalece sobre defini��es hom�nimas
no arquivo de descri��o e/ou no ambiente.
