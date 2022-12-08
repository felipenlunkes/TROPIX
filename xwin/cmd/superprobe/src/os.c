/*
 ****************************************************************
 *								*
 *			os.c					*
 *								*
 *	Rotinas dependentes do Sistema Operacional		*
 *								*
 *	Vers�o	1.0.0, de 10.01.97				*
 *								*
 *	M�dulo: SuperProbe					*
 *		Baseado no software hom�nimo de David Wexelblat	*
 *		Categoria ?					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/pcntl.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

#include "Probe.h"

/*
 ****************************************************************
 *	Habilita o acesso �s portas de E/S			*
 ****************************************************************
 */
int
OpenVideo (void)
{
	if (geteuid () != 0)
	{
		fprintf
		(	stderr, 
			"%s: n�o sou o superusu�rio\n", 
			pgname
		);

		return (-1);
	}

	if (pcntl (P_ENABLE_USER_IO) < 0)
		return (-1);

	return (0);

}	/* end enable_user_io */

/*
 ****************************************************************
 *	Desabilita o acesso �s portas de E/S			*
 ****************************************************************
 */
void
CloseVideo (void)
{
	pcntl (P_DISABLE_USER_IO);

}	/* end disable_user_io */

/*
 ****************************************************************
 *	Mapeia a mem�ria de v�deo				*
 ****************************************************************
 */
Byte *
MapVGA (void)
{
	void	*base;

	base = phys ((void *)0xA0000, 0x10000, O_RDWR|O_PHYS);

	if (base == (void *)-1)
	{
		fprintf (stderr, "%s: n�o pude mapear a mem�ria de v�deo\n", pgname);
		return (NULL);
	}

	return ((Byte *)base);

}	/* end MapVGA */

/*
 ****************************************************************
 *	Desfaz o mapeamento					*
 ****************************************************************
 */
void
UnMapVGA (Byte *base)
{
	phys ((void *)base, 0, 0);

}	/* end UnMapVGA */

Byte *
MapMem (ulong address, ulong size)
{
	void	*base;

	base = phys ((void *)address, size, O_RDWR|O_PHYS);

	if (base == (void *)-1)
	{
		fprintf (stderr, "%s: n�o pude mapear a mem�ria\n", pgname);
		return (NULL);
	}

	return ((Byte *)base);

}	/* end MapMem */

void
UnMapMem (Byte *base, ulong size)
{
	phys ((void *)base, 0, 0);

}	/* end UnMapMem */

/*
 ****************************************************************
 *	L� um trecho do BIOS					*
 ****************************************************************
 */
int
ReadBIOS (const unsigned Offset, Byte *Buffer, const int Len)
{
	ushort		tmp;
	Byte		*Base = Bios_Base + Offset;
	static int	fd = -1;

	if (fd == -1)
	{
		if ((fd = open ("/dev/mem", O_RDONLY, 0)) < 0)
		{
			fprintf(stderr, "%s: cannot open /dev/mem\n", pgname);
			return(-1);
		}
	}

	if ((off_t)((off_t)Base & 0x7FFF) != (off_t)0)
	{
		/*
	 	 *	Sanity check...
	 	 */
		(void)lseek (fd, (off_t)((off_t)Base & 0xF8000), SEEK_SET);
		(void)read (fd, &tmp, 2);

		if (tmp != 0xAA55)
		{
			fprintf
			(	stderr, 
				"%s: BIOS sanity check failed, addr=%x\n",
				pgname, (int)Base
			);

			return (-1);
		}
	}

	if (lseek (fd, (off_t)Base, SEEK_SET) < 0)
	{
		fprintf (stderr, "%s: BIOS seek failed\n", pgname);
		return (-1);
	}

	if (read (fd, Buffer, Len) != Len)
	{
		fprintf (stderr, "%s: BIOS read failed\n", pgname);
		return (-1);
	}

	return (Len);

}	/* end ReadBIOS */

#if (0)	/*******************************************************/
/*
 ****************************************************************
 *	Imprime mensagens de erro				*
 ****************************************************************
 */
void
error (char *fmt, ...)
{
	va_list	ap;
	int	must_exit;

	va_start (ap, fmt);

	must_exit = 0;
	if (*fmt == '$')
		must_exit++, fmt++;

	fprintf (stderr, "%s: ", pgname);
	vfprintf (stderr, fmt, ap);
	fprintf (stderr, "\n");
	va_end (ap);

	if (must_exit)
		exit (1);

}	/* end error */
#endif	/*******************************************************/
