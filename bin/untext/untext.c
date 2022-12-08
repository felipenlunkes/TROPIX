/*
 ****************************************************************
 *								*
 *			untext.c				*
 *								*
 *	Libera os recursos de programas reentrantes		*
 *								*
 *	Vers�o	1.0.0, de 30.06.87				*
 *		3.0.0, de 14.07.97				*
 *								*
 *	M�dulo: untext						*
 *		Utilit�rios Especiais				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 14.07.97";

#define	NOVOID	(void *)NULL
#define	elif	else if
#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */

/*
 ****** Vari�veis globais ***************************************
 */
entry const char *env_path;	/* Caminho do ambiente */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);
void		untext_file (const char *);

/*
 ****************************************************************
 *	Libera os recursos de programas reentrantes		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vNH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	/*
	 *	Se n�o foram dados os prefixo de caminhos, ...
	 */
	if ((env_path = getenv ("PATH")) == NOSTR)
		env_path = ".:/bin:/usr/bin";

	/*
	 *	Foram dados argumentos
	 */
	for (/* vazio */; *argv; argv++)
	{
		untext_file (*argv);
	}

	return (exit_code);

}	/* end untext */

/*
 ****************************************************************
 *	Processa uma programa reentrante			*
 ****************************************************************
 */
void
untext_file (const char *file_nm)
{
	register char		*cp;
	const char		*prefixp = env_path;
	char			path[512];

	/*
	 *	Se o nome dado tiver um "/", n�o utiliza os prefixos
	 */
	if (strchr (file_nm, '/'))
		prefixp = ".";

	/*
	 *	Tenta os v�rios prefixos
	 */
	while (*prefixp)
	{
		cp = path;

		/*
		 *	Copia um prefixo
		 */
		while (*prefixp && (*cp = *prefixp++) != ':')
			cp++;

		if (cp != path)
			*cp++ = '/';

		/*
		 *	Copia no final o nome do arquivo dado
		 */
		strcpy (cp, file_nm);

		/*
		 *	Tira o "./" do in�cio
		 */
		cp = path;

		if (cp[0] == '.'  &&  cp[1] == '/')
			cp += 2;

		/*
		 *	Tenta liberar os recursos
		 */
		errno = NOERR;

		untext (cp);
#undef	DEBUG
#ifdef	DEBUG
		if (vflag)
			printf ("=> \"%s\", errno = %s\n", cp, strerror (errno));
#endif	DEBUG

		/*
		 *	Verifica se conseguiu
		 */
		switch (errno)
		{
			/*
			 *	Conseguiu
			 */
		    case NOERR:
			fprintf
			(	stderr,
				"Liberei os recursos de \"%s\"\n",
				cp
			);
			return;

			/*
			 *	Arquivo desconhecido: tenta o pr�ximo nome
			 */
		    case ENOENT:
		    case ENOTDIR:
			continue;

			/*
			 *	O arquivo n�o tem recursos alocados
			 */
		    case EINVAL:
			fprintf
			(	stderr,
				"O arquivo \"%s\" n�o tem recursos alocados\n",
				cp
			);
		
			exit_code++;
			return;

			/*
			 *	Outros erros
			 */
		    default:
			break;

		}	/* end switch */

		break;

	}	/* end while */	

	/*
	 *	Outros erros
	 */
	fprintf
	(	stderr,
		"%s: N�o consegui liberar os recursos de \"%s\" (%s)\n",
		pgname, file_nm, strerror (errno)
	);

	exit_code++;

}	/* end untext_file */

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
	 	"%s - libera os recursos de programas reentrantes\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <texto> ...\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
