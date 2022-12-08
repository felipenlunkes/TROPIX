/*
 ****************************************************************
 *								*
 *			frame.h					*
 *								*
 *	Disposi��o da pilha durante exce��es e interrup��es	*
 *								*
 *	Vers�o	3.0.0, de 23.08.94				*
 *		3.0.5, de 04.01.97				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#define	FRAME_H			/* Para definir os prot�tipos */

/*
 ******	Disposi��o durante uma exce��o **************************
 */
struct excep_frame
{
	long	ef_type;	/* C�digo da exce��o == 0 */

	long	ef_es;
	long	ef_ds;

	long	ef_r5;		/* Os 8 registros */
	long	ef_r4;
	long	ef_fp;
	long	ef_isp;
	long	ef_r3;
	long	ef_r2;
	long	ef_r1;
	long	ef_r0;

	long	ef_excepno;	/* C�digo da exce��o */
	long	ef_errcode;	/* C�digo de erro */

	void	*ef_pc;		/* Posto pela exce��o */
	long	ef_cs;
	long	ef_sr;

	void	*ef_usp;	/* Somente na troca de privil�gio */
	long	ef_ss;
};

/*
 ******	Disposi��o durante uma interrup��o **********************
 */
struct intr_frame
{
	long	if_type;	/* C�digo da interrup��o == 1 */

	long	if_unit;	/* Unidade */
	long	if_cpl;		/* PL antiga */

	long	if_es;
	long	if_ds;

	long	if_r5;		/* Os 8 registros */
	long	if_r4;
	long	if_fp;
	long	if_isp;
	long	if_r3;
	long	if_r2;
	long	if_r1;
	long	if_r0;

   /*** long	if_irqno;	/* No. do IRQ */

	void	*if_pc;		/* Posto pela interrup��o */
	long	if_cs;
	long	if_sr;

	void	*if_usp;	/* Somente na troca de privil�gio */
	long	if_ss;
};

/*
 ******	Disposi��o durante uma chamada ao sistema ***************
 */
struct syscall_frame
{
	long	sf_type;	/* C�digo do syscall == 2 */

	long	sf_r5;		/* Os 8 registros */
	long	sf_r4;
	long	sf_fp;
	long	sf_isp;
	long	sf_r3;
	long	sf_r2;
	long	sf_r1;
	long	sf_r0;

	long	sf_sr;

	void	*sf_pc;		/* Posto pelo call gate */
	long	sf_cs;

   /***	int	sf_args[N];	/* N�o usados (N == 0) ***/

	void	*sf_usp;
	long	sf_ss;
};

/*
 ****** Uni�o dos acima	*****************************************
 */
union frame
{
	long			type;
	struct excep_frame	e;
	struct intr_frame	i;
	struct syscall_frame	s;
};
