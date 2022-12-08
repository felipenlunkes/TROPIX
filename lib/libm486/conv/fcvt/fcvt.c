/*
 ****************************************************************
 *								*
 *			fcvt.c					*
 *								*
 *	Converte um n�mero real em uma cadeia de d�gitos	*
 *								*
 *	Vers�o	3.0.0, de 08.07.95				*
 *		3.0,0, de 18.07.95				*
 *								*
 *	M�dulo: fcvt 						*
 *		libm/conv					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 * 								*
 *	Cria uma cadeia de N_SIGNIF d�gitos decimais a partir	*
 * 	de um "double" 						*
 * 								*
 *	Indica tambem o sinal e o expoente decimal.		*
 *	A cadeia n�o tem sinal nem ponto.			*
 * 								*
 ****************************************************************
 */

#include <math.h>

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
#define	N_SIGNIF	15
#define	AREA_SZ		(N_SIGNIF + 1)
#define	MAGIC		0.03 

/*
 ******	Tabela de pot�ncias *************************************
 */
typedef	struct
{
	double	e_pot;		/* Pot�ncia */
	int	e_exp;		/* Expoente */

}	POTTB;

#define	POTTBSZ		9

extern const POTTB	_pottb[];

/*
 ****************************************************************
 *	Converte um n�mero real em uma cadeia de d�gitos	*
 ****************************************************************
 */
int
_fcvt (double d, int *minus_ptr, register char *area)
{
	register const POTTB	*ep;
	register double		n = d;
	register double		ffra;
	register double		fint;
	register int		exp_value = -1;
	register char		*cp = area, *bp;
	int			n_signif = 0;

	/*
	 *	d:		No. a ser convertido
	 *	*minus_ptr:	Retorna o sinal do n�mero
	 *	*area:		Area de convers�o (tamanho 32)
	 *
	 *	A fun��o retorna o expoente do n�mero
	 */

	/*
	 *	Inicializa��es	
	 */
	*minus_ptr = 0;

	/*
	 *	Verifica se o n�mero � NULO
	 */
	if (!n)
	{
		for (cp = area; cp <= &area[N_SIGNIF]; /* vazio */)
			*cp++ = '0';

		return (0);
	}

	/*
	 *	Verifica se o n�mero � negativo	
	 */
	if (n < 0.0)
		{ (*minus_ptr)++; n = -n; d = n; }

	/*
	 *	Verifica se o n�mero � INFINITO
	 */
	if (n > HUGE_VAL)
		n = HUGE_VAL;

	/*
	 *	Normaliza n�meros grandes
	 */
	if (n > _pottb[4].e_pot)	/* +1.0E+16 */
	{
		for (ep = &_pottb[POTTBSZ-1]; ep > &_pottb[3]; ep--)
		{
			if (n > ep->e_pot)
				{ n /= ep->e_pot; exp_value += ep->e_exp; }
		}
	}

	/*
	 *	Separa a parte inteira e fracion�ria	
	 */
	ffra = fgfra (n); n = fgint (n);

	/*
	 *	Calcula a parte inteira e o expoente
	 */
	bp = &area[AREA_SZ + 2];

	while (n)
	{
		n /= 10.0;

		*--bp = (int)((fgfra (n) + MAGIC) * 10.0) + '0';

		n_signif++; exp_value++; n = fgint (n);
	}

	/*
	 *	Guarda a parte inteira
	 */
	for (cp = area; bp < &area[AREA_SZ + 2]; /* vazio */)
		*cp++ = *bp++;

	/*
	 *	Normaliza n�meros menores do que 1.0
	 */
	n = d;

	if (n < 1.0)
	{
		fint = n;

		for (ep = &_pottb[POTTBSZ-1]; ep >= &_pottb[0]; ep--)
		{
			n *= ep->e_pot;

			if (n < 1.0)
				{ fint = n; exp_value -= ep->e_exp; }
			else
				n = fint;
		}

		ffra = fint;
	}

	/*
	 *	Calcula a parte fracion�ria
	 */
	n = ffra;

	while (cp < &area[AREA_SZ])
	{
		if (n_signif < N_SIGNIF + 1)
		{
			n *= 10.0; *cp++ = (int)(fgint (n)) + '0';

			n = fgfra (n); n_signif++;
		}
		else
		{
			*cp++ = '0';
		}
	}

	/*
	 *	Arredonda o resultado
	 */
	bp = &area[N_SIGNIF];

	if (*bp != '0')
	{
		*bp += 5;

		while (*bp > '9' && bp > area)
			{ *bp = '0'; (*--bp)++; }

		/*
		 *	Verifica o "overflow" no arredondamento
		 */
		if (*bp > '9')
			{ *bp = '1'; exp_value++; }
	}

	return (exp_value);

}	/* end _fcvt */
