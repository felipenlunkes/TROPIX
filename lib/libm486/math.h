/*
 ****************************************************************
 *								*
 *			<math.h>				*
 *								*
 *	Vari�veis e constantes matem�ticas			*
 *								*
 *	Vers�o	1.0.0, de 22.11.87				*
 *		3.0.0, de 18.02.96				*
 *								*
 *	M�dulo: math.h						*
 *		/usr/include					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1996 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#ifndef	MATH_H
#define	MATH_H

/*
 ******	Defini��o de macros *************************************
 */
#define M_PI	 	3.1415926535897932384626433	/* PI		*/
#define	M_PI_2	 	1.5707963267948966192313216	/* PI/2		*/
#define	M_PI_4	 	0.7853981633974483096156608	/* PI/4		*/

#define	M_2_PI	 	0.6366197723675813430755350 	/* 2/PI		*/      
#define	M_4_PI	 	1.2732395447351626861510700	/* 4/PI		*/

#define M_SQRT2		1.4142135623730950488016887	/* SQRT(2) 	*/
#define M_1_SQRT2	0.7071067811865475244008443	/* 1/SQRT(2) 	*/
#define M_SQRT2_2	0.7071067811865475244008443	/* SQRT(2)/2 	*/

#define M_E		2.7182818284590452353602874	/* E		*/

#define	M_LOG2E		1.4426950408889634073599246	/* LOG2 (E)	*/
#define	M_LOG210	3.3219280948873623478703194	/* LOG2 (10)	*/

#define	M_LOG102	0.3010299956639811952137388	/* LOG10 (2)	*/
#define	M_LOG10E	0.4342944819032518276511289	/* LOG10 (E)	*/

#define M_LOGE2		0.6931471805599453094172321	/* LOGE (2)	*/
#define M_LOGE10	2.3025850929940456840179914	/* LOGE (10)	*/

#define M_LN2		0.6931471805599453094172321	/* LOGE (2)	*/
#define M_LN10		2.3025850929940456840179914	/* LOGE (10)	*/

#define	M_1_SQRTPI	0.5641895835477562869480794	/* 1/SQRT(PI)	*/
#define	M_2_SQRTPI	1.1283791670955125738961588	/* 2/SQRT(PI)	*/

/*
 ******	Defini��o de tipos **************************************
 */
typedef struct	exception
{
	int	type;		/* x */
	char	*name;		/* x */
	double	arg1;		/* x */
	double	arg2;		/* x */
	double	retval;		/* x */

}	EXCEPTION;

/*
 ******	Vari�veis globais ***************************************
 */
extern double	HUGE_VAL;		/* INFINITO */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern double	acos (double);		/* Arco coseno */
extern double	asin (double);		/* Arco seno */
extern double	atan (double);		/* Arco tangente */
extern double	atan2 (double, double);	/* Arco tangente 2 */
extern double	cos (double);		/* Coseno */
extern double	sin (double);		/* Seno */
extern double	tan (double);		/* Tangente */
extern double	cosh (double);		/* Coseno hiperb�lico */
extern double	sinh (double);		/* Seno hiperb�lico */
extern double	tanh (double);		/* Tangente hiperb�lica */
extern double	exp (double);		/* Exponencial */
extern double	exp2 (double);		/* Pot�ncia base 2 */
extern double	exp10 (double);		/* Pot�ncia base 10 */
extern double	expb (double, double);	/* Pot�ncia base dada */
extern double	pow (double, double);	/* Potencia base dada */
extern double	frexp (double, int *);	/* Fra��o + pot�ncia de 2 */
extern double	ldexp (double, int);	/* Produto por pot�ncia de 2 */
extern double	log (double);		/* Logaritmo natural */
extern double	log2 (double);		/* Logaritmo bin�rio */
extern double	log10 (double);		/* Logaritmo decimal */
extern double	logb (double, double);	/* Logaritmo dada a base */
extern double	modf (double, double *); /* Parte integral + fracion�ria */
extern double	sqrt (double);		/* Raiz quadrada */
extern double	ceil (double);		/* Inteiro mais pr�ximo n�o menor */
extern double	fabs (double);		/* Valor absoluto */
extern double	floor (double);		/* Inteiro mais pr�ximo n�o maior */
extern double	fmod (double, double);	/* Resto flutuante */
extern double	hypot (double, double);	/* Dist�ncia euclidiana */
extern double	fgman (double);		/* Mantissa */
extern int	fgexp (double);		/* Expoente */
extern double	faexp (int, double);	/* Soma ao expoente */
extern double	fgint (double);		/* Parte inteira */
extern double	fgfra (double);		/* Parte fracion�ria */

/*
 ******	Rotinas para o manuseio de exce��es do FPU do 486 ******
 */
extern long	fexcep (int);		/* liga/desliga exce��es no 486 */
extern long	_fgsr (void);		/* obt�m o valor do Status Reg. */
extern long	_fssr (long);		/* armazena um valor no Status Reg. */
extern long	_fgcr (void);		/* obt�m o valor do Control Reg. */
extern long	_fscr (long);		/* armazena um valor no Control Reg. */
extern long	_fgiar (void);		/* obt�m o valor do Instr. Addr. Reg. */

extern double	fhuge (void);		/* Valor infinito */
extern void	smatherr (EXCEPTION *);	/* Manuseio de erros */
extern int	matherr (EXCEPTION *);	/* Manuseio de erros */

/*
 ******	Defini��es para o manuseio de condi��es de erro ********
 */
#define	DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6

/*
 ******	Defini��es para o manuseio de exce��es da FPU do 486 ***
 */
#define FP_INVALOPER	0x0001	/* Opera��o inv�lida */
#define FP_DENORMAL	0x0002	/* Operando n�o normalizado */
#define FP_ZERODIV	0x0004	/* Divis�o por zero */
#define FP_OVERFLOW	0x0008	/* Overflow */
#define FP_UNDERFLOW	0x0010	/* Underflow */
#define FP_PRECISION	0x0020	/* Perda de Precis�o */

#endif
