/*
 ****************************************************************
 *								*
 *			putinfo.c				*
 *								*
 *	Escrita de informa��es sobre terminais			*
 *								*
 *	Vers�o 2.0.0, de 21.04.87				*
 *	       3.0.0, de 21.02.95				*
 *								*
 *	Modulo: putinfo						*
 *		libcurses/terminfo				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termio.h>
#include <errno.h>
#include <terminfo.h>

#include "../h/defs.h"

/*
 ****************************************************************
 *	Defini��o de Constantes					*
 ****************************************************************
 */
#define		FNAMESZ		100
#define		MAXNAMES	10

static const char TERMINFO[] =	"/usr/lib/terminfo";

#ifdef	TAIL
static char	tail[]=		"/?";
#endif	TAIL

#define		MAGIC	0x011B	/* Magic Number */

#define		DPROT	0111	/* Prot. de Dir.: busca para todos */
#define		FPROT	0444	/* Prot. de Arq.: leitura para todos */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
static void	putshort (short, FILE *output);
static void	unpack (char *, char **);
static int	mklink (char *, const char *, char *);

/*
 ****************************************************************
 *	Escrita	das Informa��es					*
 ****************************************************************
 */
int
putinfo (INFO *pinfo, char *testnm)
{
	register int	i;
	char		tnbuf[FNAMESZ];	/* Nome do Arq. com Terminfo */
	char		*tmpname;
	const char	*dir;
	FILE		*fp;
	short		*offsets;	/* �rea para a Se��o Offsets */
	char		*copy;
	char		*inames[MAXNAMES + 1];

	/*
	 *	Nome do diret�rio, se presente usa $TERMINFO
	 */
	dir = getenv ("TERMINFO");

	/*
	 *	Monta nome completo para tempor�rio: dir/term
	 */
	if (dir != NOSTR)
		strncpy (tnbuf, dir, FNAMESZ);
	else
		strncpy (tnbuf, TERMINFO, FNAMESZ);

	strncat (tnbuf, "/", FNAMESZ);
	strncat (tnbuf, "XXXXXX", FNAMESZ);

	if ((tmpname = mktemp (tnbuf)) == NOSTR)
		return (0);

	/*
	 *	Abre arquivo tempor�rio
	 */
	if ((fp = fopen (tmpname, "w")) == NOFILE)
	{
		fprintf
		(	stderr,
			"N�o consigo escrever tempor�rio: \"%s\" (%s)\n",
			tmpname, strerror (errno)
		);
		return (0);
	}
#ifdef	DEBUG
	else
	{
		printf ("\nEscrevendo \"%s\"\n", tmpname);
	}
#endif	DEBUG

	/*
	 *	Aloca espa�o para offsets
	 */
	offsets = malloc (pinfo->i_strno * sizeof (short));

	if (offsets == (short *)NULL)
		{ fclose (fp); unlink (tmpname); return (0); }

	/*
	 *	Convers�o i_strings -> offsets
	 */
	for (i = 0; i < pinfo->i_strno; i++)
	{
		if (pinfo->i_strings[i] != NOSTR)
			offsets[i] = pinfo->i_strings[i] - pinfo->i_table;
		else
			offsets[i] = -1;
	}

	/*
	 *	Escrita do Header
	 */
	putshort (MAGIC, fp);
	putshort (strlen (pinfo->i_names) + 1, fp);
	putshort (pinfo->i_boolno, fp);
	putshort (pinfo->i_numno, fp);
	putshort (pinfo->i_strno, fp);
	putshort (pinfo->i_tabsz, fp);

#ifdef	DEBUG
	printf
	(	"HEADER: %d, %d, %d, %d, %d, %d\n",
		MAGIC, strlen(pinfo->i_names) +1,
		pinfo->i_boolno,
		pinfo->i_numno,
		pinfo->i_strno,
		pinfo->i_tabsz
	);
#endif	DEBUG

	/*
	 *	Escrita das Se��es Names, Boooleans, Numbers,
	 *		Offsets e String Table.
	 */
#ifdef	DEBUG
	printf ("In�cio de Names: %ld\n", ftell (fp));
#endif	DEBUG

	fputs (pinfo->i_names, fp);
	putc ('\0', fp);

	if (((strlen (pinfo->i_names) & 1)) == 0)
		putc ('\0', fp);

#ifdef	DEBUG
	printf ("In�cio de Booleans: %ld\n", ftell (fp));
#endif	DEBUG

	fwrite (pinfo->i_booleans, sizeof (char), pinfo->i_boolno, fp);

#ifdef	DEBUG
	printf ("In�cio de Numbers: %ld\n", ftell (fp));
#endif	DEBUG

	fwrite (pinfo->i_numbers, sizeof (short), pinfo->i_numno, fp);

#ifdef	DEBUG
	printf ("In�cio de Offsets: %ld\n", ftell (fp));
#endif	DEBUG

	fwrite (offsets, sizeof (short), pinfo->i_strno, fp);

#ifdef	DEBUG
	printf ("In�cio da String Table: %ld\n", ftell (fp));
#endif	DEBUG

	fwrite (pinfo->i_table, sizeof (char), pinfo->i_tabsz, fp);


	/*
	 *	Libera offsets
	 */
	free (offsets);

	/*
	 *	Encerra Escrita no Tempor�rio
	 */
	if (ferror (fp))
		{ fclose (fp); unlink (tmpname); return (0); }

	fclose (fp);

	/*
	 *	Separa os Nomes do Terminal
	 */
	if ((copy = malloc (strlen (pinfo->i_names) + 1)) == NOSTR)
		{ unlink (tmpname); return (0); }

	strcpy (copy, pinfo->i_names);
	unpack (copy, inames);

	/*
	 *	Link arquivo tempor�rio aos arquivos definitivos
	 */
	if (testnm)
	{
		mklink (tmpname, dir, testnm);
	}
	else
	{
		for (i = 0; inames[i] != NOSTR; i++)
			mklink (tmpname, dir, inames[i]);
	}

	/*
	 *	Remove arquivo Tempor�rio
	 */
	if (unlink (tmpname) < 0)
	{
		fprintf
		(	stderr,
			"N�o consigo apagar tempor�rio: \"%s\" (%s)\n",
			tmpname, strerror (errno)
		);
		return (0);
	}

#ifdef	DEBUG
	printf ("Removi \"%s\"\n", tmpname);
#endif	DEBUG

	return (1);

}	/* end putinfo */

/*
 ****************************************************************
 *	Escreve um Short					*
 ****************************************************************
 */
static void
putshort (short n, FILE	*output)
{
	fwrite (&n, 1, sizeof (short), output);

}	/* end putshort */

/*
 ****************************************************************
 *	Separa os Nomes do Terminal				*
 ****************************************************************
 */
static void
unpack (register char *copy, register char **inames)
{
	register char	*next;
	register char	**names;

	names = inames;

	/*
	 *	O �ltimo nome (nome completo) � desprezado
	 */
	while ((next = strchr (copy, '|')) != NOSTR)
	{
		*next = '\0';

		if (names < inames + MAXNAMES - 1)
			*names++ = copy;

		copy = next + 1;
	}

	*names = NOSTR;

}	/* end unpack */

/*
 ****************************************************************
 *	Associa mais um nome a um arquivo			*
 ****************************************************************
 */
static int
mklink (char *original, const char *dir, char *newname)
{
	char	fname[FNAMESZ];		/* Novo Nome Completo */

	/*
	 *	Nome do diret�rio, se presente usa $TERMINFO
	 */
	if (dir == NOSTR)
	{
		strncpy (fname, TERMINFO, FNAMESZ);
#ifdef	TAIL
		tail[1] = newname[0];
		strncat (fname, tail, FNAMESZ);
#endif	TAIL
	}
	else
	{
		strncpy (fname, dir, FNAMESZ);
	}

	/*
	 *	Se o diret�rio n�o existe, ent�o � criado
	 */
	if (access (fname, F_OK) < 0)
	{
		if (mkdir (fname, DPROT) < 0)
		{
			fprintf
			(	stderr,
				"N�o consegui criar o diret�rio \"%s\" (%s)\n",
				fname, strerror (errno)
			);
			return (0);
		}
	}

	/*
	 *	Monta nome completo: dir/term
	 */
	strncat (fname, "/", FNAMESZ);
	strncat (fname, newname, FNAMESZ);

	/*
	 *	Se o arquivo existe, ent�o � removido
	 */
	if (access (fname, F_OK) == 0)
	{
		fprintf
		(	stderr,
			"A descri��o \"%s\" j� existe. Reescreve? (n): ",
			fname
		);

		if (askyesno () > 0)
			unlink (fname);
		else
			return (0);
	}

	printf ("Instalando \"%s\": (\"%s\")\n", newname, fname);

	/*
	 *	Realiza a liga��o
	 */
	if (link (original, fname) < 0)
	{
		fprintf
		(	stderr,
			"N�o consegui criar a descri��o \"%s\" (%s)\n",
			fname, strerror (errno)
		);
		return (0);
	}

	/*
	 *	Troca a prote��o
	 */
	chmod (fname, FPROT);

	return (1);

}	/* end mklink */
