#include <math.h>
#include <stdio.h>
#include <signal.h>

void	fexcepid (int sig);

main ()
{
	int	i;
	int	x, y;
	double	a;
	double	b, c, d, e;

	signal (SIGFPE, fexcepid);

	y = (FP_INVALOPER | FP_DENORMAL | FP_ZERODIV |
		FP_OVERFLOW | FP_UNDERFLOW);

	printf ("Condi��es pass�veis de gerar exce��o:\n");
	printf ("\t1  -> Opera��o inv�lida\n");
	printf ("\t2  -> Operando n�o normalizado\n");
	printf ("\t4  -> Divis�o por zero\n");
	printf ("\t8  -> Overflow\n");
	printf ("\t16 -> Underflow\n");
	printf ("\t32 -> Precis�o\n");

	printf ("D� o conjunto de condi��es desejadas: ");
	scanf ("%d", &y);

	x = fexcep (y);
	printf ("Exce��es anteriores habilitadas: %04X\n", x);
	x = fexcep (y);
	printf ("Exce��es pedidas: %04X\n", y);
	printf ("Exce��es habilitadas: %04X\n", x);

	printf ("a < -307 ----> underflow em exp10\n");
	printf ("a > 308  ----> overflow em exp10\n");
	printf ("a < 0    ----> opera��o inv�lida em sqrt\n");
	printf ("a = 0    ----> divis�o por zero em 1/a\n");
	printf ("Entre com o valor de a\n");

	for (;;)
	{
		if (scanf ("%Lg", &a) < 0)
			exit (0);

		printf ("a = %25.20G\n", a);
		e = exp10 (a);
		printf ("exp10 = %25.20G\n", e);
		b = sqrt (a);
		printf ("sqrt = %25.20G\n", b);
		d = 1.0 / a;
		printf ("1/a = %25.20G\n", d);
	}
}

void
fexcepid (int sig)
{
	printf ("fexcepid: interceptou o sinal -> status = %04X endere�o = %P\n",
		 _fgsr (), _fgiar ());

	if ((_fgsr () & FP_INVALOPER) == FP_INVALOPER)
		printf ("fexcepid: exce��o de opera��o inv�lida\n");

	if ((_fgsr () & FP_DENORMAL) == FP_DENORMAL)
		printf ("fexcepid: eexce��o de operando n�o normalizado\n");

	if ((_fgsr () & FP_ZERODIV) == FP_ZERODIV)
		printf ("fexcepid: exce��o de divis�o por zero\n");

	if ((_fgsr () & FP_OVERFLOW) == FP_OVERFLOW)
		printf ("fexcepid: exce��o de overflow\n");

	if ((_fgsr () & FP_UNDERFLOW) == FP_UNDERFLOW)
		printf ("fexcepid: exce��o de underflow\n");

	if ((_fgsr () & FP_PRECISION) == FP_PRECISION)
		printf ("fexcepid: exce��o de precis�o\n");

	_fssr (0);

	signal (SIGFPE, fexcepid);
}
