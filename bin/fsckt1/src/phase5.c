/*
 ****************************************************************
 *								*
 *			phase5.c				*
 *								*
 *	Fase 5: Verifica as refer�ncias				*
 *								*
 *	Vers�o	4.3.0, de 23.07.02				*
 *		4.3.0, de 16.08.02				*
 *								*
 *	M�dulo: fsckt1						*
 *		Utilit�rios Especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/t1.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include "../h/fsckt1.h"

/*
 ****************************************************************
 *	Fase 5: Verifica as refer�ncias				*
 ****************************************************************
 */
int
phase5 (void)
{
	T1SB		*sp = (T1SB *)sb.b_area;
	INO_HASH	*ip, **hp;
	T1DINO		*np;

	printf ("*** Fase 5: Verifica as refer�ncias\n");

	/*
	 *	Percorre todos os INODEs
	 */
	for (hp = &inode_hash_tb[0]; hp < &inode_hash_tb[INO_HASH_SZ]; hp++)
	{
		for (ip = *hp; ip != NO_INO_HASH; ip = ip->i_next)
		{
			switch (ip->i_state)
			{
				/*
				 ******	Arquivos e diret�rios j� referenciados
				 */
			    case FILE_STATE:
			    case SEEN_DIR_STATE:
				/*
				 *	Se a contagem difere, ...
				 */
				if (ip->i_mem_link != ip->i_disk_link)
					{ adjust_dev_link (ip); break; }

				/*
				 *	Se o arquivo est� referenciado, ...
				 */
				if (ip->i_disk_link != 0)
					break;

				/*
				 *	O arquivo N�O est� referenciado
				 *	Tenta reconectar
				 */
				if (link_up (ip, lost_found_ip) != CONTINUE)
				{
					inode_clr (ip, "Continua desconectado. ");
				}
				else	/* Conseguiu reconectar */
				{
					np = inode_get (ip->i_ino);
					np->n_nlink = 1;
	
					ip->i_disk_link = 1;
					inoblk.b_dirty++;
				}

				break;

				/*
				 ******	Diret�rios N�O referenciados
				 */
			    case DIR_STATE:
				inode_clr (ip, "Diret�rio n�o referenciado. ");
				break;

				/*
				 ******	INODE deve ser removido
				 */
			    case CLR_STATE:
				inode_clr (ip, "INODE com problemas. ");
				break;

				/*
				 ******	OUTROS *********************
				 */
			    default:
				error ("Estado inv�lido: %d", ip->i_state);
				break;

			}	/* end switch (get_inode_map (ino)) */

		}

	}	/* end percorrendo os INODEs */

	/*
	 *	Confere o n�mero de INODEs no SB
	 */
	if (sp->s_busy_ino != fs_busy_ino)
	{
		printf
		(	"\nTotal de INODEs Ocupados incorreto (%d :: %d). ",
			sp->s_busy_ino, fs_busy_ino 
		);

		if (faskyesno ("Ajusta") > 0)
		{
			sp->s_busy_ino = fs_busy_ino;

			sb.b_dirty++;
		}
	}

	/*
	 *	Confere o n�mero de Blocos no SB
	 */
	if (sp->s_busy_bl != fs_busy_bl)
	{
		printf
		(	"\nTotal de Blocos Ocupados incorreto (%d :: %d). ",
			sp->s_busy_bl, fs_busy_bl 
		);

		if (faskyesno ("Ajusta") > 0)
		{
			sp->s_busy_bl = fs_busy_bl;

			sb.b_dirty++;
		}
	}

	return (CONTINUE);

}	/* end phase5 */

/*
 ****************************************************************
 *	Ajusta o Numero de Refer�ncias				*
 ****************************************************************
 */
void
adjust_dev_link (INO_HASH *ip)
{
	T1DINO		*np;

	np = inode_get (ip->i_ino);

	if (np->n_nlink != ip->i_disk_link)
		error ("adjust_dev_link: erro interno");

	if (ip->i_mem_link == 0)
	{
		/*
		 *	Apenas arquivos atingem este ponto (eu suponho)
		 *
		 *	E Eu concordo!
		 */
		if (link_up (ip, lost_found_ip) != CONTINUE)
		{
			inode_clr (ip, "Continua desconectado. ");
		}
		else
		{
			/*
			 *	Conseguiu reconectar. Incrementa o no.
			 *	de links no disco, pois "link_up" j�
			 *	incrementa na memoria.
			 */
			np = inode_get (ip->i_ino);
			np->n_nlink = 1;

			ip->i_disk_link = 1;
			inoblk.b_dirty++;
		}
	}
	else	/* mem_link != 0 && mem_link != disk_link */
	{
		print_inode (ip->i_ino, np);
		printf
		(	"N�mero de referencias incorreto (%d :: %d). ",
			ip->i_disk_link, ip->i_mem_link
		);

		if (faskyesno ("Ajusta") > 0)
		{
		   /***	ip->i_disk_link = ip->i_mem_link; ***/
			np->n_nlink = ip->i_mem_link;

			ip->i_disk_link = ip->i_mem_link;
			inoblk.b_dirty++;
		}
	}

}	/* end adjust_dev_link */

/*
 ****************************************************************
 *	Elimina um INODE					*
 ****************************************************************
 */
void
inode_clr (INO_HASH *ip, const char *msg)
{
	T1DINO		*np;

	/*
	 *	S� confirma se tiver mensagem
	 */
	np = inode_get (ip->i_ino);

	if (msg != NOSTR)
	{
		print_inode (ip->i_ino, np);

		printf (msg);

		if (faskyesno ("Remove") <= 0)
			return;
	}

	/*
	 *	Dereferencia os blocos do mapa de blocos alocados
	 */
	file_block_scan (np, ip, dereference_file_block);

	fs_busy_ino--;

	memset (np, 0, sizeof (T1DINO));
	np->n_magic = T1_SBMAGIC;

	inoblk.b_dirty++;

}	/* end inode_clr */

/*
 ****************************************************************
 *	Dereferencia um bloco do mapa de blocos alocados	*
 ****************************************************************
 */
int
dereference_file_block (T1DINO *np, INO_HASH *ip, daddr_t bno, int type)
{
	DUPBLK		*dup_p;
	int		i;

	if (bno <= T1_BMNO || bno >= ((T1SB *)sb.b_area)->s_fs_sz)
		return (SKIP);

	if (T1_GET_MAP (mem_block_map, bno) == T1_MAP_FREE)
		return (CONTINUE);

	for (dup_p = dup_block_tb, i = 0; i < dup_block_sz; dup_p++, i++)
	{
		if (dup_p->dup_bno == bno)
		{
			if (dup_p->dup_n <= 0)
				break;

			dup_p->dup_n--;

			return (CONTINUE);
		}
	}

	T1_PUT_MAP (mem_block_map, bno, T1_MAP_FREE);

	fs_busy_bl--;

	return (CONTINUE);

}	/* end dereference_file_block */
