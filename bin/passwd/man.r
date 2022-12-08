.bp
.he 'PASSWD (cmd)'TROPIX: Manual de Refer�ncia'PASSWD (cmd)'
.fo 'Atualizado em 03.06.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "passwd -"
altera a senha do usu�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
passwd [<conta>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "passwd" instala ou altera uma senha associada ao usu�rio <conta>.
A senha controla o acesso de um usu�rio ao sistema (veja "login" (cmd)).

.sp
Usu�rios regulares (isto �, que n�o s�o "superusu�rios", veja "intro" (sys))
podem instalar/alterar apenas a pr�pria senha, caso em que a <conta>
n�o precisa ser dada.

.sp
Por quest�es de seguran�a, as senhas devem satisfazer as seguintes
regras de forma��o:

.in +5
.ip 1. 3
Cada senha deve ser composta de caracteres do c�digo ISO exceto <nl> e <cr>.
O caractere "kill" (normalmente <^U>) tamb�m deve ser evitado
(veja "getpass" (libc)). Apenas s�o considerados os primeiros 14 caracteres.

.ip 2. 3
Caso a senha contenha letras, algarismos e caracteres especiais,
ela deve ter no m�nimo 6 caracteres.

.ip 3. 3
Caso a senha contenha apenas letras e algarismos,
ela deve ter no m�nimo 7 caracteres.

.ip 4. 3
Caso a senha contenha apenas letras, ela deve ter no m�nimo 8 caracteres.

.ip 5. 3
Caso a senha contenha apenas algarismos, ela deve ter no m�nimo 11 caracteres.

.ep
.in -5

.sp
Antes de alterar uma senha, o comando "passwd" pede e confere a senha antiga.
A seguir, � pedida a senha nova duas vezes; em caso de diverg�ncia
entre as duas vers�es, ou se a senha n�o segue as regras
dadas acima, a senha nova � pedida novamente (at� um m�ximo de 4 vezes).

.sp
Usu�rios regulares (mas n�o superusu�rios) podem possuir uma senha nula
(isto �, podem n�o necessitar de uma senha para entrar em sess�o) teclando
apenas <nl> ou <cr> para as duas vers�es da senha nova.

.in
.sp
.b OBSERVA��ES
.in 5
O comando "passwd" n�o dispensa os superusu�rios das
regras de forma��o das senhas.

.sp
O TROPIX n�o utiliza a t�cnica de envelhecimento de senhas
por ter sido considerada in�cua para a seguran�a do sistema.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login
.br
.wo "(sys): "
intro
.br
.wo "(libc):"
crypt, getpass
.br
.wo "(fmt): "
passwd
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
/etc/passwd

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
