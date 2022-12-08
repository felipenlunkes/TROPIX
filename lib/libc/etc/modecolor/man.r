.bp 1
.he 'MODECOLOR (libc)'TROPIX: Manual de Refer�ncia'MODECOLOR (libc)'
.fo 'Atualizado em 27.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
modecolor - obt�m um vetor de cores para os tipos de arquivos

.in
.sp
.b SINTAXE
.(l
#include <stdlib.h>

int modecolor (int active,
		char **value_vector, const char ***string_vector);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "modecolor" prepara dois vetores ("value_vector" e
"string_vector"), contendo informa��es
s�bre cores que ser�o associadas a cada tipo de arquivo e tamb�m
as cores que devem ser usadas para mensagens de "advert�ncia" e "erro".

Estas informa��es s�o obtidas a partir da vari�vel MODECOLOR
do ambiente (ver "environ" (fmt)).

.sp
Ambos vetores cont�m 19 elementos, que devem ser indexados do seguinte modo:

.in +3
.ip 1. 3
Os 16 primeiros elementos a partir do tipo do arquivo, que
� parte do modo de um arquivo,  tal como obtido de uma chamada
ao sistema "stat" ou "fstat" (ver "stat" (sys), e tabela abaixo).

.ip 2. 3
O elemento de �ndice MC_WARN define a cor que deve ser usada nas
mensagens de "advert�ncia".

.ip 3. 3
O elemento de �ndice MC_ERR define a cor que deve ser usada nas
mensagens de "erro".

.ip 4. 3
O elemento de �ndice MC_DEF (apenas do vetor "string_vector") cont�m a
cadeia de caracteres para restaurar a cor original do v�deo.

.ep
.in -3

.sp
O primeiro vetor fornece valores de cor (de 0 a 15), segundo
o c�digo das cores VGA (ver tabela, abaixo).
O endere�o do vetor � armazenado no conte�do do ponteiro "value_vector".
Se este vetor n�o for de inter�sse, o ponteiro "value_vector" pode ser dado NULO.

.sp
O segundo vetor fornece cadeias para alterar a cor do v�deo/monitor,
segundo os padr�es VT100.
.bc	/*************************************/
Este vetor cont�m um elemento extra, de
�ndice MC_DEF, contendo a cadeia para restaurar a cor original.
.ec	/*************************************/
O endere�o do vetor � armazenado no conte�do do ponteiro "string_vector".
Se este vetor n�o for de inter�sse, o ponteiro "string_vector" pode ser dado NULO.

.sp
Se o argumento "active" for diferente de zero, "modecolor" analisa
a vari�vel MODECOLOR do ambiente (ver "environ (fmt)), obtendo
as cores associadas aos tipos de arquivo presentes no valor da vari�vel,
e prepara os vetores.

.sp
Para cada tipo de arquivo para o qual n�o foi obtida uma informa��o de cor,
o elemento correspondente do primeiro vetor conter� o valor 255 (valor inv�lido) e
o elemento do segundo vetor apontar� para uma cadeia vazia.

.sp
Os vetores devem ser indexados pelo tipo do arquivo/mensagem
(veja o arquivo de inclus�o <stat.h>):

.sp
.nf
	      Valor	Tipo de Arquivo		Nome simb�lico

		 1	Fifo			    fifo
		 2	Especial de caracteres	    chr
		 4	Diret�rio		    dir
		 6	Especial de blocos	    blk
		 8	Regular			    reg
		10	Elo simb�lico		    lnk

			Tipo da mensagem

	     MC_WARN	Advert�ncia		    warn
	     MC_ERR	Erro			    err
.fi

.sp 2
As cores dispon�veis s�o:

.sp
.nf
			Nomes			Valor

		preto		black		 0
		azul		blue		 1
		verde		green		 2
		ciano		cyan		 3
		vermelho	red		 4
		magenta		magenta		 5
		marrom		brown		 6
		branco		white		 7
		azulclaro	lightblue	 9
		verdeclaro	lightgreen	10
		cianoclaro	lightcyan	11
		vermelhoclaro	lightred	12
		magentaclaro	lightmagenta	13
		marromclaro	lightbrown	14
		brancoclaro	lightwhite	15
.fi

.sp
A cadeia MODECOLOR deve ter o seguinte formato:
.nf

		"MODECOLOR=<tipo>=<cor>,..."
.fi

.sp
onde <tipo> � um nome simb�lico de um tipo de arquivo ou mensagem, e <cor>
� o nome ou valor de uma cor (veja as duas tabelas, acima).

.sp
Exemplo:

.sp
.nf
	MODECOLOR=chr=verde,dir=red,blk=6,reg=cyan,err=lightmagenta
.fi

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a fun��o devolve 0. Em caso contr�rio devolve -1;
isto ir� ocorrer caso haja algum erro de sintaxe na cadeia MODECOLOR,
ou a fun��o n�o consiga alocar mem�ria para uma ou mais cadeias.

.sp
De qualquer modo, os vetores preparados podem ser sempre usados
(possivelmente, em caso de erro, n�o contendo as informa��es completas). 
.)t

.in
.sp
.b OBSERVA��O
.in 5
Ao inserir a vari�vel MODECOLOR no ambiente, n�o esque�a de usar
o "export" (veja "sh", (cmd)).

.sp
Se o argumento "active" for dado igual a zero, ou n�o h�
a vari�vel MODECOLOR no ambiente,
o vetor "value_vector"
retornar� todas as cores com o valor 255 (valor inv�lido),
e o vetor "string_vector" apontar� em todos os seus elementos
para uma cadeia vazia.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(sys): "
stat
.br
.wo "(fmt): "
environ
.br

.in
.sp
.b EXEMPLO
.r
.in 5
Abaixo damos um exemplo de uso do vetor de cadeias. Estamos supondo
que a vari�vel "st_mode" cont�m o modo de um arquivo
(como retornado de uma chamada ao sistema "stat" ou "fstat").

.sp
O primeiro "printf" atribui a cor de frente associada ao arquivo
de modo "st_mode", e o �ltimo restaura a cor original.
Repare que as cores somente s�o alteradas se "stdout" for um terminal/v�deo.

.sp
.nf
	#include <stdlib.h>

	...........

	const char	**string_vector;

	...........

	if (modecolor (isatty (fileno (stdout)),
				(void *)0, &string_vector) < 0)
		........

	...........

	printf ("\%s", string_vector[(st_mode & S_IFMT) >> 12]);

	printf (....);

	printf ("\%s", string_vector[MC_DEF]);
.fi

.sp
Para a impress�o de uma mensagem de erro, podemos usar:

.sp
.nf
	printf
	(	"\%sTexto da mensagem de erro\%s\n",
		string_vector[MC_ERR], string_vector[MC_DEF]
	);
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.
