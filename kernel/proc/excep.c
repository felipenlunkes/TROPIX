/*
 ****************************************************************
 *								*
 *			excep.c					*
 *								*
 *	Atendimento de exce��es					*
 *								*
 *	Vers�o	3.0.0, de 15.07.94				*
 *		4.6.0, de 24.07.04				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"
#include "../h/scb.h"
#include "../h/sync.h"
#include "../h/region.h"

#include "../h/frame.h"
#include "../h/mmu.h"
#include "../h/a.out.h"
#include "../h/seg.h"
#include "../h/cpu.h"
#include "../h/intr.h"
#include "../h/uerror.h"
#include "../h/signal.h"
#include "../h/uproc.h"

#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	USER	20

const ushort	IRQ_vec[16] =
{
	IRQ0, IRQ1, IRQ2,  IRQ3,  IRQ4,  IRQ5,  IRQ6,  IRQ7,
	IRQ8, IRQ9, IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15
};

entry int		irq_pl_vec[16];		/* N�veis definitivos dos IRQs */

entry VECDEFLINE	vecdef[16];		/* A matriz de controle */

/*
 ****************************************************************
 *	Nomes das exce��es					*
 ****************************************************************
 */
const char	* const excep_nm_table[] =
{
	"Divide error",			/*  0 */
	"Debug exception",		/*  1 */
	"NMI interrupt",		/*  2 */
	"Breakpoint",			/*  3 */
	"INTO-detected overflow",	/*  4 */
	"BOUND range exceeded",		/*  5 */
	"Invalid operation code",	/*  6 */
	"Device not available",		/*  7 */
	"Double fault",			/*  8 */
	"Coprocessor segment overrun",	/*  9 */
	"Invalid task state segment",	/* 10 */
	"Segment not present",		/* 11 */
	"Stack fault",			/* 12 */
	"General protection",		/* 13 */
	"Page fault",			/* 14 */
	"(Reserved)",			/* 15 */
	"Floating-point error",		/* 16 */
	"Alignment check"		/* 17 */
};

/*
 ****************************************************************
 *	Exce��es internas					*
 ****************************************************************
 */
void
excep (struct excep_frame frame)
{
	int		excepno, signo = 0;
	void		*fa = NOVOID;

	/*
	 *	Reparar que esta chamada n�o � t�pica: tudo se passa
	 *	como se o argumento "frame" fosse dado "por refer�ncia".
	 */
	excepno = (unsigned)frame.ef_excepno < 18 ? frame.ef_excepno : 15;

#ifdef	DEBUG
	printf
	(	"excep: Recebi exce��o #%d (%s)\n",
		excepno, excep_nm_table[excepno]
	);

	printf
	(	"EXCEP %d: cs = %P, pc = %P, errcode = %P\n",
		frame.ef_excepno, frame.ef_cs, frame.ef_pc, frame.ef_errcode
	);
#endif	DEBUG

	/*
	 *	Verifica se foi de usu�rio
	 */
	if (SEL_PL (frame.ef_cs) != 0)
		excepno += USER;

	/*
	 *	Toma as provid�ncias devidas
	 */
	switch (excepno)
	{
	/** case 0: 		/* Divide error (KERNEL) */
	    case USER+0:	/* Divide error (USER) */
		signo = SIGDVZ;
		break;

	/** case 1: 		/* Debug exception (KERNEL) */
	    case USER+1: 	/* Debug exception (USER) */
		signo = SIGTRAP;
		break;

	/** case 2: 		/* NMI interrupt (KERNEL) */
	    case USER+2: 	/* NMI interrupt (USER) */
		signo = SIGIOT;
		break;

	/** case 3: 		/* Breakpoint (KERNEL) */
	    case USER+3: 	/* Breakpoint (USER) */
		signo = SIGTRAP;
		break;

	/** case 4: 		/* INTO-detected overflow (KERNEL) */
	    case USER+4: 	/* INTO-detected overflow (USER) */
		signo = SIGIOT;
		break;

	/** case 5: 		/* BOUND range exceeded (KERNEL) */
	    case USER+5:	/* BOUND range exceeded (USER) */
		signo = SIGCHK;
		break;

	/** case 6: 		/* Invalid operation code (KERNEL) */
	    case USER+6: 	/* Invalid operation code (USER) */
		signo = SIGILL;
		break;

	/** case 7: 		/* Device not available (KERNEL) */
	    case USER+7: 	/* Device not available (USER) */
		if (scb.y_fpu_enabled)
		{
			/*
			 *	Se a FPU est� habilitada, vai haver uma exce��o 7
			 *	na primeira instru��o de FP de cada time-slice
			 *	e aqui n�o pode haver preemption
			 */
			preemption_flag[CPUID] = 0;

			u.u_fpu_lately_used = 1;

			fpu_reset_embit ();	/* Para n�o entrar em loop */

			/*
			 *	Se a FPU j� havia sido usada antes por este
			 *	processo, apenas restaura o estado;
			 *	caso contr�rio, inicializa
			 */
			if (u.u_fpu_used)
				fpu_restore (u.u_fpstate);
			else
				{ fpu_init (); u.u_fpu_used = 1; }

			if (scb.y_preemption_mask[CPUID])
				preemption_flag[CPUID]++;

			goto out;
		}

		signo = SIGILL;
		break;

	/** case 8: 		/* Double fault (KERNEL) */
	    case USER+8: 	/* Double fault (USER) */
		signo = SIGILL;
		break;

	/** case 9: 		/* Coprocessor segment overrun (KERNEL) */
	    case USER+9: 	/* Coprocessor segment overrun (USER) */
		signo = SIGSEGV;
		break;

	/** case 10: 		/* Invalid task state segment (KERNEL) */
	    case USER+10: 	/* Invalid task state segment (USER) */
		signo = SIGILL;
		break;

	/** case 11: 		/* Segment not present (KERNEL) */
	    case USER+11: 	/* Segment not present (USER) */
		signo = SIGSEGV;
		break;

	/** case 12: 		/* Stack fault (KERNEL) */
	    case USER+12: 	/* Stack fault (USER) */
		signo = SIGILL;
		break;

	/** case 13: 		/* General protection (KERNEL) */
	    case USER+13: 	/* General protection (USER) */
		signo = SIGILL;
		break;

		/*
		 ******	Page fault (KERNEL) *********************
		 */
	    case 14:
	    {
		const SYM	*sp;

		fa = get_cr2 ();

		printf ("\n%g: pc = %P, fa = %P\n", frame.ef_pc, fa);

#if (0)	/*************************************/
		if (frame.ef_pc >= SYS_ADDR && frame.ef_pc < &etext)
#endif	/*************************************/
		if ((sp = getsyment ((unsigned)frame.ef_pc)) != NOSYM)
			printf ("%g: fun��o \"%s\", offset = %P\n", sp->s_name, frame.ef_pc - sp->s_value);

		panic ("KERNEL PAGE FAULT");
	    }

		/*
		 ******	Page fault (USER) ***********************
		 */
	    case USER+14:
		fa = get_cr2 ();
#ifdef	MSG
		if (CSWT (3))
			printf ("%g: USER PAGE FAULT: pc = %P, fa = %P\n", frame.ef_pc, fa);
#endif	MSG
		/*
		 *	Verifica se � um endere�o que ainda
		 *	possa ser considerado parte da "stack"
		 */
		if (USER_STACK_PGA - BYTOPG (fa) < BYTOPG (16 * MBSZ))
		{
			if (setstacksz (fa) > 0)
				goto out;

			signo = SIGSEGV;
		}
		else
		{
			signo = SIGBUS;
		}
#ifdef	MSG
		if (CSWT (3))
			printf ("%g: FATAL USER PAGE FAULT: pc = %P, fa = %P\n", frame.ef_pc, fa);
#endif	MSG
		break;

	/** case 15: 		/* (Reserved) (KERNEL) */
	    case USER+15: 	/* (Reserved) (USER) */
		signo = SIGILL;
		break;

	/** case 16: 		/* Floating-point error (KERNEL) */
	    case USER+16: 	/* Floating-point error (USER) */
		signo = SIGFPE;
		break;

	/** case 17: 		/* Alignment check (KERNEL) */
	    case USER+17: 	/* Alignment check (USER) */
		signo = SIGADR;
		break;

	    default:	 	/* Exce��o inesperada */
		fa = get_cr2 ();

		printf ("%g: pc = %P, fa = %P\n", frame.ef_pc, fa);

		if (excepno >= USER)
		{
			printf
			(	"USER #%d (%s)\n",
				excepno-USER, excep_nm_table[excepno-USER]
			);
		}
		else	/* KERNEL */
		{
			printf
			(	"KERNEL #%d (%s)\n",
				excepno, excep_nm_table[excepno]
			);
		}

		printf
		(	"cs = %P, pc = %P, errcode = %P\n",
			frame.ef_cs, frame.ef_pc, frame.ef_errcode
		);

if (excepno == 7)
{
	/*
	 *	Provis�rio para fazer debug do c�digo da FPU	
	 *	e evitar o sistema entrar em loop.
	 *	Na realidade deve dar panic mesmo j� que
	 * 	n�o pode haver exce��o #7 em modo supervisor.
	 */
	fpu_reset_embit ();	/* Para n�o entrar em loop */
	print_calls ();
}
else
{
		panic ("UNEXPECTED EXCEPTION");
}
	

	}	/* end switch (excepno) */

	/*
	 *	Analisa os sinais
	 */
	sigproc (u.u_myself, signo);

    out:
	if (u.u_sig)
		sigexec (fa, frame.ef_pc);

}	/* end excep */

/*
 ****************************************************************
 *	Exce��es esp�rias					*
 ****************************************************************
 */
void
spurious_int (struct intr_frame frame)
{
	/*
	 *	Reparar que esta chamada n�o � t�pica: tudo se passa
	 *	como se o argumento "frame" fosse dado "por refer�ncia".
	 */
	printf
	(	"spurious_int: Recebi interrup��o esp�ria irq = %d\n",
		frame.if_unit & 0xFFFF
	);

}	/* end spurious_int */

/*
 ****************************************************************
 *	Adiciona a interrup��o de um dispositivo		*
 ****************************************************************
 */
int
set_dev_irq (int irq, int pl, int unit, void (*func) ())
{
	VECDEF		*vp;
	int		i;
	ulong		IRQMASK, *up;

	/*
	 *	Pequena consist�ncia
	 */
	if ((unsigned)irq >= 16)
	{
		printf ("set_dev_irq: irq %d inv�lido\n", irq);
		return (-1);
	}

	if (pl == 0 || (unsigned)pl > 7)
	{
		printf ("set_dev_irq: n�vel %d inv�lido\n", pl);
		return (-1);
	}

	/*
	 *	Percorre a linha dos dispositivos compartilhados
	 */
	vp = &vecdef[irq][0];

	for (i = 0; /* abaixo */; i++, vp++)
	{
		if (i >= VECLINESZ - 1)
		{
			printf
			(	"set_dev_irq: N�mero excessivo de "
				"dispositivos compartilhados no IRQ %d\n",
				irq
			);
			return (-1);
		}

		if (vp->vec_func == (void (*) ())NULL)
			break;
	}

	/*
	 *	Preenche a nova entrada
	 */
   	vp->vec_unit = unit;
   	vp->vec_func = func;

	/*
	 *	Altera as m�scaras dos n�veis
	 */
	IRQMASK = IRQ_vec[irq];

	if (IRQMASK & 0xFF00)
		IRQMASK |= IRQ_SLAVE;

	for (i = 0, up = pl_mask; i < pl; i++, up++)
		up[0] &= ~IRQMASK;

	/*
	 *	Coloca o n�vel definitivo (por enquanto) do IRQ
	 */
	if (irq_pl_vec[irq] < pl)
	{
		if (irq_pl_vec[irq] != 0)
			printf ("set_dev_irq: Alterando o n�vel do IRQ %d (%d => %d)\n", irq, irq_pl_vec[irq], pl);

		irq_pl_vec[irq] = pl;
	}

	/*
	 *	Inicializa o descritor de exce��es
	 */
	set_idt (32 + irq, vecdefaddr[irq], INTR_GATE, KERNEL_PL);

	return (0);

}	/* end set_dev_irq */

/*
 ****************************************************************
 *	Inicializa um descritor de exce��es			*
 ****************************************************************
 */
void
set_idt (int excep_no, const void (*func) (), int type, int dpl)
{
	extern EXCEP_DC	idt[];
	EXCEP_DC	*ip = idt + excep_no;

	ip->ed_low_offset  = (unsigned)func;
	ip->ed_selector	   = KERNEL_CS;
	ip->ed_args	   = 0;
	ip->ed_reser0	   = 0;
	ip->ed_type	   = type;
	ip->ed_dpl	   = dpl;
	ip->ed_present	   = 1;
	ip->ed_high_offset = ((unsigned)func) >> 16;

}	/* end set_idt */
