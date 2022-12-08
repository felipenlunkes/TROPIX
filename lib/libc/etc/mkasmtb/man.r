.bp 1
.he 'MKASMTB (libc)'TROPIX: Manual de Refer�ncia'MKASMTB (libc)'
.fo 'Atualizado em 23.02.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "mkasmtb -"
gera m�dulos em linguagem simb�lica ("assembly")

.in
.sp
.b SINTAXE
.(l
#include <mkasmtb.h>

int
mkasmtb
(
  const char *as_nm,	/* Nome do m�dulo a gerar (com ".s") */
  const char *tb_nm,	/* Nome da tabela dada (sem o '_') */
  const void *tb_addr,	/* Endereco da tabela dada */
  long tb_sz,		/* Tamanho da tabela (em bytes) */
  ROW tb_access,		/* Tipo da prote��o da tabela */
  int tb_ent_sz,		/* Tamanho de cada entrada da tabela */
  const OBJENT *tb_ent_desc /* Vetor de descri��o das entradas */
);

.)l

.sp
.b DESCRI��O
.in 5
A fun��o "mkasmtb" gera um arquivo contendo um programa
em linguagem simb�lica ("assembly")
a partir de uma tabela previamente constru�da.
Este programa por sua vez, quando montado ir�
produzir um programa objeto (contendo a tabela), pronto para
ser "link-editado".
.sp

A principal aplica��o � a de criar automaticamente tabelas
que s�o complexas demais para serem definidas diretamente.
O exemplo classico � a tabela "hash" de um compilador: antes
de come�ar a compila��o, a tabela "hash" j� deve conter as
palavras reservadas da linguagem. Uma solu��o lenta (que em
geral � usada), � a de em uma fase de inicializa�ao, colocar as
palavras reservadas na tabela "hash". Uma outra solu��o, bem mais
r�pida e elegante � a de, na fase de gera��o do compilador,
preparar a tabela "hash", e por interm�dio da fun��o "mkasmtb"
e do montador, gerar um modulo objeto, que � ent�o "link-editado"
com o compilador.

.sp
O par�metro "tb_access" d� a �rea de endere�amente da tabela no
programa: no caso de "RO" e "ROL" a tabela residir� na �rea do texto
(que ser� protegida contra escritas se o programa for
"link-editado" como reentrante), e no caso de "RW" e "RWL" a tabela
residir� na �rea de dados do programa.
A diferen�a entre "RO" e "ROL" (que � a mesma entre "RW" e "RWL"),
� a de que com o "L" a tabela � gerada localmente ao programa,
e neste caso, ela deve ser concatenada com outros programas em
linguagem simb�lica antes de ser montada.

.sp
Normalmente (isto �, com um ponteiro NULO para o argumento "tb_ent_desc"),
o m�dulo � gerado
como uma seq��ncia de "bytes" ("chars") sem reloca��o.
Se um ou mais membros da entrada da tabela
forem "words" ("shorts"), "longs" ou se
forem ponteiros (isto �, elementos reloc�veis do ponto de vista
do montador/"link-editor"), temos de informar isto
� fun��o "mkasmtb", dando um ponteiro para um vetor de
estruturas "OBJENT" (o argumento "tb_ent_desc").

.sp
Para cada membro da tabela nas condi��es acima corresponde
a uma entrada do vetor de estruturas "OBJENT", com os seguintes elementos:
"o_size": tamanho do membro; "o_offset": posi��o do membro na entrada;
"o_count": no. de exemplares deste membro (se for um vetor);
"o_rel_nm": nome da vari�vel reloc�vel (ponteiro NULO se for absoluto)
"o_rel_addr": endere�o da vari�vel relocadora.
Um membro com "o_size" NULO marca o final de "tb_ent_desc".

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
Normalmente, a fun��o devolve zero. No caso de n�o conseguir
criar o arquivo contendo o programa em linguagem simb�lica, devolve (-1).
.)t

.in
.sp
.b OBSERVA��ES
.in 5
Cada chamada a "mkasmtb" produz exatamente
um arquivo com um programa em linguagem simb�lica,
contendo uma tabela.
Para obter um m�dulo objeto �nico contendo
v�rias tabelas, pode-se montar
conjuntamente os diversos arquivos gerados
por v�rias chamadas a "mkasmtb".

.sp
No caso de ponteiros, ponteiros NULOs s�o conservados, isto �,
o ponteiro NULO � convertido na constante zero, e n�o no valor
reloc�vel de uma tabela menos uma constante.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cc, as, ld
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/mkasmtb.h

.in
.sp
.b EXEMPLOS
.in 5
.br
(Nas p�ginas seguintes)

.in
.sp
.(t
.b EXEMPLO
(Sem ponteiros):
.in 5
Repare que � necess�rio marcar o final do vetor de estruturas "OBJENT".
.sp
.nf
	#include <stddef.h>
	#include <mkasmtb.h>

	#define	NULL	0
	#define	NOSTR	(char *)NULL
	#define	NOVOID	(void *)NULL

	typedef	struct
	{
		short	a;
		short	c;

	}	HASH;

	HASH	hash[4] =
	{
		{ 0, 6 },
		{ 1, 5 },
		{ 2, 4 },
		{ 3, 3 }
	};

	const OBJENT tab[] =
	{
		{ sizeof (short), offsetof (HASH, a),
					1, NOSTR, NOVOID },
		{ sizeof (short), offsetof (HASH, c),
					1, NOSTR, NOVOID },
		{ 0 }
	};

	main ()
	{
		mkasmtb
		(	"hash.s",
			"hash",
			hash,
			sizeof hash,
			RWL, 
			sizeof (HASH),
			tab
		);
	}
.fi
.)t
.sp 2
ir� gerar a tabela "hash.s":
.sp 2
.nf
		.data

	_hash:
		.word	0x0000
		.word	0x0006

		.word	0x0001
		.word	0x0005

		.word	0x0002
		.word	0x0004

		.word	0x0003
		.word	0x0003
.fi

.in
.sp
.b EXEMPLO
(Com ponteiros):
.in 5
No programa dado abaixo, cada entrada da tabela contem 2 ponteiros.
.in
.sp
.nf
	#include <stddef.h>
	#include <mkasmtb.h>

	#define NOSTR	(char *)NULL
	#define NOVOID	(void *)NULL

	typedef	struct
	{
		short	a;
		short	c;
		short	*b[2];
		long	*d;

	}	HASH;

	short	symtb[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	long	abs[]	=
	{
		9, 8, 7, 6, 5, 4, 3, 2,
		1, 9, 8, 7, 6, 5, 4
	};

	HASH	hash[4] =
	{
		{ 0, 6, &symtb[1], &symtb[1], &abs[7] },
		{ 1, 5, &symtb[2], NOVOID,    &abs[1] },
		{ 2, 4, &symtb[3], &symtb[0], &abs[9] },
		{ 3, 3, &symtb[4], &symtb[2], &abs[0] }
	};

	const OBJENT tab[] =
	{
		{ sizeof (short),   offsetof (HASH, a),
					1, NOSTR, NOVOID },
		{ sizeof (short),   offsetof (HASH, c),
					1, NOSTR, NOVOID },
		{ sizeof (short *), offsetof (HASH, b[0]),
					2, "symtb", symtb },
		{ sizeof (long *),  offsetof (HASH, d),
					1, "abs", abs },
		{ 0 }

	};

	main ()
	{
		mkasmtb
		(	"table.s",
			"hash",
			hash,
			sizeof hash,
			RO, 
			sizeof (HASH),
			tab
		);
	}
.fi
.sp 2
ir� gerar a tabela "table.s":
.sp 2
.nf
		.global	_hash
		.global	_symtb
		.global	_abs
		.const

	_hash:
		.word	0x0000
		.word	0x0006
		.long	_symtb+2
		.long	_symtb+2
		.long	_abs+28

		.word	0x0001
		.word	0x0005
		.long	_symtb+4
		.long	0
		.long	_abs+4

		.word	0x0002
		.word	0x0004
		.long	_symtb+6
		.long	_symtb
		.long	_abs+36

		.word	0x0003
		.word	0x0003
		.long	_symtb+8
		.long	_symtb+4
		.long	_abs
.fi
.in

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
