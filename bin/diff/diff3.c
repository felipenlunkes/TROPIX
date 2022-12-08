/*
 ****************************************************************
 *								*
 *			diff3.c					*
 *								*
 *	Compara��o diferencial de dois arquivos			*
 *								*
 *	Vers�o	2.3.0, de 25.01.90				*
 *		3.0.0, de 24.04.97				*
 *								*
 *	M�dulo: diff						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/kcntl.h>

#include <a.out.h>
#include <stat.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "diff.h"

/*
 ****************************************************************
 *	Defini��es e vari�veis globais				*
 ****************************************************************
 */
#define	INCR		4192	/* Tamanho Basico para Alocacao */

#define	ROUND(x) ((x + 3) & ~3)	/* Arredondamento do tamanho */

entry char	*mem0,		/* Ponteiros para a �rea dispon�vel */
		*mem1,
		*mem2;

static char	*tempfile;	/* Usado para a c�pia da entrada padr�o */

/*
 ****************************************************************
 *	Copia o arquivo da entrada padr�o			*
 ****************************************************************
 */
char *
copytemp (void)
{
	char		buf[BUFSIZ];
	int		i, fd;

	signal (SIGHUP,  on_signal);
	signal (SIGINT,  on_signal);
	signal (SIGQUIT, on_signal);
	signal (SIGPIPE, on_signal);
	signal (SIGTERM, on_signal);

	tempfile = mktemp ("/tmp/diffXXXXXX");

	if ((fd = creat (tempfile, 0600)) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui criar o arquivo tempor�rio \"%s\" (%s)\n",
			pgname, tempfile, strerror (errno)
		);
		done ();
	}

	while ((i = read (0, buf, BUFSIZ)) > 0)
	{
		if (write (fd, buf, i) != i)
		{
			fprintf
			(	stderr,
				"%s: Erro de escrita no arquivo "
				"tempor�rio \"%s\" (%s)\n",
				pgname, tempfile, strerror (errno)
			);
			done ();
		}
	}

	if (i < 0)
	{
		fprintf
		(	stderr,
			"%s: Erro de leitura da entrada padr�o (%s)\n",
			pgname, strerror (errno)
		);
		done ();
	}

	close (fd);

	return (tempfile);

}	/* end copytemp */

/*
 ****************************************************************
 *	Comp�e o nome do arquivo, se for dado como diret�rio	*
 ****************************************************************
 */
char *
dirfilenm (const char *dir, const char *file, int copy)
{
	const char	*tail;
	char		buf[BUFSIZ];

	if (copy)
	{
		fprintf
		(	stderr,
			"%s: N�o podemos especificar a entrada padr�o "
			"e um diret�rio\n\n",
			pgname
		);
		help ();
	}

	tail = strrchr (file, '/');

	if ((tail = strrchr (file, '/')) == NOSTR)
		tail = file;
	else
		tail++;

	sprintf (buf, "%s/%s", dir, tail);

	return (strdup (buf));

}	/* end  dirfilenm */

/*
 ****************************************************************
 *	L� um arquivo						*
 ****************************************************************
 */
void
readfile (const char *filenm, STAT *files, char **fileaddr)
{
	char		*addr, *cp;
	HEADER		*hp;
	int		fd;

	/*
	 *	Em primeiro lugar, aloca mem�ria
	 */
	if (files->st_size <= 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o tamanho de \"%s\"\n",
			pgname, filenm
		);
		done ();
	}

	addr = diff_malloc (files->st_size + 2);

	/*
	 *	Abre o arquivo fonte
	 */
	if ((fd = open (filenm, O_RDONLY)) < 0)
	{
		fprintf
		(	stderr,
			"N�o consegui abrir \"%s\" (%s)\n",
			filenm, strerror (errno)
		);
		done ();
	}

	/*
	 *	L� o conte�do do arquivo (addr � m�ltiplo de 4)
	 */
	if (read (fd, addr, files->st_size) != files->st_size)
	{
		fprintf
		(	stderr,
			"Erro na leitura de \"%s\" (%s)\n",
			filenm, strerror (errno)
		);
		done ();
	}

	close (fd);

	/*
	 *	Verifica se � um m�dulo objeto 
	 */
	if (files->st_size >= sizeof (HEADER))
	{
		hp = (HEADER *)addr;

		if (hp->h_magic == FMAGIC || hp->h_magic == NMAGIC)
		{
			fprintf
			(	stderr,
				"%s: O arquivo \"%s\" � um m�dulo objeto\n",
				pgname, filenm
			);
			done ();
		}
	}

	/*
	 *	Prepara o final do programa
	 */
	cp = addr + files->st_size - 1;

	if (*cp != '\n')
	{
		fprintf
		(	stderr,
			"%s: O arquivo \"%s\" n�o termina por um \"\\n\"\n",
			pgname, filenm
		);
		*++cp = '\n';
	}

	*++cp = '\0';

	*fileaddr = addr;

}	/* end readfile */

/*
 ****************************************************************
 *	Aloca��o de Mem�ria					*
 ****************************************************************
 */
void *
diff_malloc (int size)
{
	void		*addr;

	size = ROUND (size);

	/*
	 *	Verifica se tem espa�o
	 */
	while (mem1 + size > mem2)
	{
		if (mem0 == NOSTR)
		{
			addr = mem0 = mem1 = sbrk (INCR);
			mem2 = mem1 + INCR;
		}
		else
		{
			addr = sbrk (INCR);
			mem2 += INCR;
		}

		if ((int)addr < 0)
		{
			fprintf (stderr, "%s: Mem�ria excedida", pgname);
			done ();
		}
	}

	/*
	 *	Acerta os indicadores
	 */
	addr = mem1;
	mem1 += size;

	return (addr);

}	/* end diff_malloc */

#if (0)	/*******************************************************/
/*
 ****************************************************************
 *	Rotina de libera��o de mem�ria dummy			*
 ****************************************************************
 */
void
free (void *a)
{
	if (vflag)
		printf ("Free: %P\n", a);

}	/* end free */
#endif	/*******************************************************/

#undef	MDEALLOC
#ifdef	MDEALLOC
/*
 ****************************************************************
 *	Devolve um trecho n�o usado de mem�ria			* 
 ****************************************************************
 */
void
mdealloc (void *addr)
{
	char		*a;

	a = (void *)ROUND ((int)addr);

	if (a >= mem0 && a <= mem1) 
	{
		mem1 = a;
	}
	else
	{
		fprintf
		(	stderr,
			"%s: Devolu��o inv�lida de mem�ria: %X\n",
			pgname,
			addr
		);
	}

}	/* end mdealloc */
#endif	MDEALLOC

/*
 ****************************************************************
 *	Em caso de sinal, ...					*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	done ();

}	/* end on_signal */

/*
 ****************************************************************
 *	Encerra o programa					*
 ****************************************************************
 */
void
done (void)
{
	/*
	 *	Remove, se for o caso, a c�pia da entrada padr�o
	 */
	if (tempfile)
		unlink (tempfile);

	/*
	 *	Imprime a Mem�ria ocupada
	 */
	if (vflag)
	{
		KPSZ		kpsz;
		char		*endbrk;

		kcntl (K_GETPSZ, &kpsz);
		endbrk = sbrk (0);

		fprintf
		(
			stderr,
			"Texto = %d, Data = %d, Bss = (%d + %d), "
			"Stack = %d, Total = %d\n",
			(int)&etext,
			(int)&edata - (int)&etext,
			(int)&end - (int)&edata,
			endbrk - (int)&end,
			kpsz.k_ssize,
			endbrk + kpsz.k_ssize
		);
	}

	exit (status);

}	/* end done */

#undef	DEBUG
#ifdef	DEBUG
/*
 ****************************************************************
 *	Imprime uma linha terminada com '\n'			*
 ****************************************************************
 */
void
printline (char *cp, int n)
{
	int		c;

	while ((c = *cp++) != '\n' && n-- > 0)
		fputc (c, stdout);

	fputc ('\n', stdout);

}	/* end printline */
#endif	DEBUG
