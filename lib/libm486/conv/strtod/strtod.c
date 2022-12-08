/*
 ****************************************************************
 *								*
 *			strtod.c				*
 *								*
 *	Converte uma cadeia de digitos em um flutuante		*
 *								*
 *	Vers�o	3.0.0, de 08.07.95				*
 *		3.0.0, de 18.07.95				*
 *								*
 *	M�dulo: strtod						*
 *		libm/conv					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>
#include <math.h>

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
#undef	INVERT_LAST_ENTRY	/* Usa a tabela toda sem exce��es */

#define	elif	else if

/*
 ****************************************************************
 *	Tabela de pot�ncias					*
 ****************************************************************
 */
typedef	struct
{
	double	e_pot;		/* Pot�ncia */
	int	e_exp;		/* Expoente */

}	POTTB;

extern const POTTB	_pottb[];	/* A tabela est� em "pottb" */

#define	POTTBSZ		9	/* Ela vai de 1.0e1 a 1.0e256 */
#define LASTEXP		256	/* valor do �ltimo expoente */

/*
 ****************************************************************
 *	Converte n�meros de ponto flutuante			*
 ****************************************************************
 */
double
strtod (const char *str, register const char **ptr)
{
	register const char	*cp = str;
	register double		n = 0.0;
	register const POTTB	*ep;
	register int		exp_value = 0;
	int			num_digs  = 0, frac_digs = 0, exp_digs = 0;
	int			e_seen    = 0, num_minus = 0, exp_minus = 0;

	/*
	 *	Pula os brancos
	 */
	while (cp[0] == ' ' || cp[0] == '\t')
		cp++;

	/*
	 *	Le o sinal do n�mero
	 */
	if   (cp[0] == '-')
		{ num_minus++; cp++; }
	elif (cp[0] == '+')
		cp++;

	/*
	 *	Calcula a parte inteira do n�mero
	 */
	while (cp[0] >= '0' && cp[0] <= '9')
		{ n *= 10.0; n += *cp++ - '0'; num_digs++; }

	/*
	 *	Processa a parte fracion�ria
	 */
	if (cp[0] == '.')
	{
		cp++;

		while (cp[0] >= '0' && cp[0] <= '9')
			{ n *= 10.0; n += *cp++ - '0'; frac_digs++; }
	}

	/*
	 *	Processa o expoente
	 */
	if (cp[0] == 'e' || cp[0] == 'E')
	{
		cp++; e_seen++;

		if   (cp[0] == '-')
			{ exp_minus++; cp++; }
		elif (cp[0] == '+')
			cp++;

		while (cp[0] >= '0' && cp[0] <= '9')
			{ exp_value *= 10; exp_value += *cp++ - '0'; exp_digs++; }

		if (exp_minus)
			exp_value = -exp_value;
	}

	/*
	 *	Verifica se a sintaxe � v�lida
	 */
	if (num_digs + frac_digs == 0 || (e_seen && exp_digs == 0))
	{
		if (ptr)
			*ptr = str;

		return (0.0);
	}

	/*
	 *	Ajusta o expoente para um n�mero sem ponto decimal
	 */
	exp_value -= frac_digs;

	/*
	 *	Divide ou multiplica o n�mero pelo expoente
	 */
	if   (exp_value > 0)
	{
		for (ep = &_pottb[0]; ep < &_pottb[POTTBSZ]; ep++)
		{
			if (exp_value == 0)
				break;

			if (exp_value & ep->e_exp)
			{
#ifdef	INVERT_LAST_ENTRY
				if (ep->e_exp == LASTEXP)
					n = n / (1.0 / ep->e_pot);
				else
#endif	INVERT_LAST_ENTRY
					n *= ep->e_pot;

				exp_value &= ~ep->e_exp;
			}
		}

		if (exp_value)
			n = fhuge ();

	}
	elif (exp_value < 0)
	{
		exp_value = -exp_value;

		for (ep = &_pottb[0]; ep < &_pottb[POTTBSZ]; ep++)
		{
			if (exp_value == 0)
				break;

			if (exp_value & ep->e_exp)
			{
#ifdef	INVERT_LAST_ENTRY
				if (ep->e_exp == LASTEXP)
					n = n * (1.0 / ep->e_pot);
				else
#endif	INVERT_LAST_ENTRY
					n /= ep->e_pot;

				exp_value &= ~ep->e_exp;
			}
		}

		if (exp_value)
			n = 0.0;
	}

	/*
	 *	Armazena um ponteiro para o primeiro caractere ap�s o n�mero
	 */
	if (ptr)
		*ptr = cp;

	return (num_minus ? -n : n);

}	/* end strtod */
