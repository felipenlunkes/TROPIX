.bp
.he 'FEXCEP (libc)'TROPIX: Manual de Refer�ncia'FEXCEP (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manuseio de exce��es em opera��es de ponto flutuante:
.sp
.wo "fexcep -"
habilita a ocorr�ncia de exce��es
.br
.wo "_fgsr  -"
obt�m o valor do "Status Register"
.br
.wo "_fssr  -"
armazena um valor no "Status Register"
.br
.wo "_fgcr  -"
obt�m o valor do "Control Register"
.br
.wo "_fscr  -"
armazena um valor no "Control Register"
.br
.wo "_fgiar -"
obt�m o valor do "Instruction Address Register"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

long	fexcep (long cond);
long	_fgsr (void);
long	_fssr (long x);
long	_fgcr (void);
void	_fscr (long x);
long	_fgiar (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es operam com o "Floating-Point Status Register" (fsr), 
o "Floating-Point Control Register" (fcr) e o "Floating-Point
Instruction Address Register" (fiar).
Estes registros controlam e informam a corre��o das opera��es
em n�meros de ponto flutuante.

.sp
A fun��o "fexcep" indica ao processador num�rico
quais as condi��es que devem causar exce��o, isto �, quais as condi��es
em que o processador num�rico deve gerar uma chamada ao sistema operacional.
Tipicamente essas condi��es s�o "overflow", "underflow", divis�o
por zero, etc... O m�dulo "math.h" cont�m as defini��es dessas condi��es.
.sp
Normalmente as exce��es est�o mascaradas e, embora o resultado num�rico
possa estar incorreto, o processador num�rico n�o gera exce��es.
Mesmo n�o gerando exce��es, as poss�veis causas dos resultados incorretos
s�o sempre indicadas cumulativamente por bits do "Status Register".

.sp
A fun��o "_fgsr" acessa o "Status Register" que cont�m informa��es
cumulativas sobre condi��es pass�veis de gerar exce��es. Os bits deste
registro s�o sempre ligados quando estas exce��es ocorrem e n�o s�o
desligados automaticamente. Cumpre ao usu�rio deslig�-los, usando
a fun��o "_fssr". 

.sp
A fun��o "_fgcr" acessa o "Control Register" que cont�m informa��es sobre
a a��o a tomar no caso da ocorr�ncia de algum tipo de exce��o.
Um bit ligado indica que um sinal SIGFPE deve ser mandado
para o programa quando uma determinada exce��o ocorrer.
Normalmente nenhum sinal � mandado. Cumpre ao usu�rio, utilizando a
fun��o "fexcep" (ou mesmo, "_fscr"), indicar para quais exce��es o sinal
"SIGFPE" deve ser mandado para o processo em execu��o. O sinal mandado
normalmente cancela o processo, a n�o ser que seja interceptado.

.sp
A fun��o "_fgiar" obt�m o conte�do do registro "Instruction Address
Register" que indica o endere�o da instru��o que causou a exce��o.

.in
.sp
.b OBSERVA��ES
.in 5
Todas as fun��es que carregam um valor em algum registro retornam o valor
anterior ali encontrado.

.sp
Alguns processadores num�ricos (como os da Intel) n�o s�o capazes de
desligar seletivamente os bits do "Status Register". Neste caso, a fun��o
"_fssr" desliga todos os bits que estavam indicando as condi��es de exce��o
independentemente do valor do argumento.

.sp
No caso dos modernos processadores num�ricos que se utilizam de
"pipeline", o "Instruction Address Register" pode n�o indicar exatamente
o endere�o da instru��o que causou a exce��o mas um endere�o pr�ximo a ele.

.sp
Para se trabalhar diretamente com os registros do processador num�rico,
recomenda-se consultar o manual do processador (veja "Refer�ncias" abaixo).

.in
.sp
.b REFER�NCIAS
.in 5
Intel Corporation, "Intel486 Microprocessor Family Programmer's
Reference Manual", 1993.

.(t
.in
.sp
.b EXEMPLO
.in 7
No programa abaixo, as exce��es que ocorrem geram um sinal que
� interceptado para melhor an�lise da causa dos erros.
.sp 2
.nf
	#include <math.h>
	#include <signal.h>
	
	main ()
	{
		int	fexcepid ();
	
		fexcep (FP_OVERFLOW | FP_UNDERFLOW | FP_ZERODIV);

		signal (SIGFPE, fexcepid);	/* Arma o signal */
	
		/*
		 *	Aqui colocar o programa a ser monitorado
		 */
	}
	
	int
	fexcepid (int sig)
	{
		if ((_fgsr () & FP_OVERFLOW) == FP_OVERFLOW)
			printf ("Exce��o de overflow\n");
	
		if ((_fgsr () & FP_UNDERFLOW) == FP_UNDERFLOW)
			printf ("Exce��o de underflow\n");
	
		if ((_fgsr () & FP_ZERODIV) == FP_ZERODIV)
			printf ("Exce��o de divis�o por zero\n");
	
		if ((_fgsr () & FP_INVALOPER) == FP_INVALOPER)
			printf ("Exce��o de opera��o inv�lida\n");
	
		_fssr ();	/* Desliga a indica��o das exce��es */

		signal (SIGFPE, fexcepid);	/* Rearma o signal */
	}
.fi
.)t

.sp
.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
