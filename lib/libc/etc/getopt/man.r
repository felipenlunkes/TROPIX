.bp 1
.he 'GETOPT (libc)'TROPIX: Manual de Refer�ncia'GETOPT (libc)'
.fo 'Atualizado em 22.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "getopt -"
obt�m as op��es dadas a um programa
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>
#include <stdlib.h>

int getopt (int argc, const char *argv[], const char *optstr);
	
extern const char	*optarg;
extern int		optind;
extern int		opterr;
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "getopt" � uma ferramenta para auxiliar a decodifica��o
das diversas op��es dadas para um programa. Ela tem a dupla finalidade
de verificar se a sintaxe est� correta e a de fornecer cada op��o
juntamente com o seu (poss�vel) argumento.

.sp
A cada chamada, "getopt" devolve a op��o seguinte dada ao programa,
relativa ao conjunto de argumentos e op��es passados em
"argv", "argc" e "optstr".

.sp
A cadeia "optstr" deve conter todas as op��es v�lidas para o programa.
Se nesta cadeia uma op��o � seguida de dois pontos (':'), espera-se
que a op��o tenha um argumento, e neste caso o ponteiro para este argumento
� devolvido em "optarg".

.sp
Quando a lista de op��es for exaurida, "getopt" devolve o valor
EOF (definido em <stdio.h>).
Neste momento,
a vari�vel "optind" contem
o �ndice de "argv" do pr�ximo argumento (do comando) a ser processado.
Um modo simples de acessar estes argumentos �
incrementar a vari�vel "argv" do valor de "optind", de tal
modo que "*argv" aponte para o primeiro argumento.

.in
.sp
.b DIAGN�STICOS
.in 5
Encontrando uma op��o inv�lida ou um erro de sintaxe,
"getopt" imprime uma mensagem
de erro em "stderr",
posiciona "optarg" para apontar para a op��o envolvida com o erro
e devolve '?'.
A mensagem de erro pode ser suprimida zerando-se a vari�vel "opterr".

.in
.sp
.b OBSERVA��ES
.in 5
A op��o especial "--" pode ser usada como delimitador
para indicar o final
das op��es. Ao encontrar este delimitador, "getopt"
devolve EOF, e "--" �  pulado. 

.sp
Ao final das op��es, "getopt" � reinicializada, de modo
a permitir a sua reutiliza��o em outro conjunto de argumentos
e op��es.

.(t
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(fmt): "
cmd
.br
.)t

.in
.sp
.b EXEMPLO
.nf
	#include <stdio.h>
	#include <stdlib.h>

	main (int argc, const char *argv[])
	{
		int		opc,
		int		hflag;
		char		*ifile, *ofile;

		   . . .

		while ((opc = getopt (argc, argv, "hi:o:H")) != EOF)
		{
			switch (opc)
			{
			    case 'h' :
				hflag++;
				break;

			    case 'i' :
				ifile = optarg;
				break;

			    case 'o' :
				ofile = optarg;
				break;

			    case 'H' :
				help ();

			    default:
				help ();

			}	/*  end switch (opc)  */

		}	/* end while (opc != EOF)  */

		argc -= optind;
		argv += optind;

		     . . .

	}	/* end main */
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
