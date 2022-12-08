
.bp
.sp 4
.nf
     *********************************************************
     *                                                       *
     *                      CAP�TULO  4                      *
     *                                                       *
     *        ENTRADA E INSER��O DE TEXTO VIA TECLADO        *
     *                                                       *
     *********************************************************
.fi
.sp 4
.pp
Este cap�tulo descreve a inclus�o
de texto teclado no terminal no texto em edi��o.
A inclus�o via teclado � chamada de
.b
inser��o
.r
quando realizada a partir do modo Visual
e de
.b
entrada
.r
quando realizada a partir do modo Comandos.
Em ambos os casos, o texto digitado
� editado linha a linha,
permitindo ao usu�rio
corrigir erros de digita��o em uma linha ainda n�o terminada.

.pp
A edi��o da entrada/inser��o
� comandada pelos caracteres de edi��o (descritos abaixo);
os outros caracteres s�o simplesmente inseridos ou escritos
na posi��o apontada pelo cursor.
Os caracteres de edi��o n�o s�o ecoados,
mas seus efeitos s�o percebidos instantaneamente pelo usu�rio
atrav�s do movimento do cursor
e/ou da altera��o da linha no v�deo do terminal.

.pp
Neste cap�tulo est�o descritos todos os caracteres
que t�m significado especial para a entrada e inser��o de texto.
O nome que acompanha a explica��o de cada caractere
� o nome atrav�s do qual ele pode ser alterado pelo comando "stty" (cmd).

.pp
Os caracteres de edi��o s�o apresentados a seguir:

.in +3
.ip <erase>: 11
Este caractere remove o caractere imediatamente � esquerda do cursor.
Valor normal: <del>.

.ip <aerase>: 11
Este caractere � uma alternativa ao caractere "erase".
Valor normal: <bs>.

.ip <word>: 11
Este caractere remove a palavra imediatamente � esquerda do cursor.
Uma palavra � definida como uma seq��ncia de caracteres
que n�o contenha <sp> nem <ht>.
Valor normal: <^W>.

.ip <kill>: 11
Este caractere remove toda a linha teclada at� o momento.
Valor normal: <^X>.

.ip <retype>: 11
Este caractere reescreve o v�deo do terminal.
Ele � �til quando processos executando em "background"
enviam mensagens ao v�deo que interferem
na apresenta��o do texto em edi��o.
Valor normal: <^R>.

.ip <eol>: 11
No modo Inser��o este caractere � usado para terminar a inser��o.
Sem efeito no modo Entrada.
Valor normal: <esc>.

.ip <eof>: 11
Caractere alternativo a "eol".
Valor normal: <^D>.

.ip <nl>: 11
Este caractere indica o t�rmino da linha corrente
e o in�cio de uma nova linha.

Quando um <nl> � teclado no modo Inser��o
uma nova linha � inserida e o cursor � posicionado no seu in�cio;
se existiam caracteres � direita do cursor
estes caracteres s�o transferidos para a nova linha inserida.

.ip <cr>: 11
Caractere alternativo a <nl>.

.ip ". (ponto):"  11
O modo Entrada termina quando uma linha contendo
apenas o caractere "." (ponto) � teclada.

.ip <^V>: 11
Este caractere anula o significado especial do caractere que o segue,
exceto <nl> e "." (ponto).

.ep
.in -3
