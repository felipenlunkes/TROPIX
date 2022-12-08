/*
 ****************************************************************
 *								*
 *			sync.c					*
 *								*
 *	Atualiza os blocos do cache dos discos			*
 *								*
 *	Vers�o	1.0.0, de 09.06.86				*
 *		3.0.1, de 12.07.97				*
 *								*
 *	Modulo: sync						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Variaveis globais					*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.1, de 12.07.97";

entry const char *pgname;	/* Nome do programa */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Atualiza os blocos do cache dos discos			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	pgname = argv[0];

	/*
	 *	Verifica uso correto do programa
	 */
	if (getopt (argc, argv, "H") != EOF  ||  argc != 1)
		help ();

	if (sync () < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui dar \"sync\" (%s)\n",
			pgname, strerror (errno)
		);
		exit (1);
	}

	return (0);

}	/* end main */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - Atualiza os blocos do cache nos discos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
