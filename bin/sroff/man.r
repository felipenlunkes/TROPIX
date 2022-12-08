.bp 1
.he 'SROFF (cmd)'TROPIX: Manual de Refer�ncia'SROFF (cmd)'
.fo 'Atualizado em 07.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
sroff - formatador de textos

.in
.sp
.b SINTAXE
.in 5
sroff [-lN] [<texto> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "sroff" formata o texto contido nos arquivos <texto> dados,
escrevendo o texto formatado na sa�da padr�o.

.sp
As op��es do comando s�o:

.in +3
.ip -l
Gera o texto formatado para impressora "laser".

.ip -N
Le os nomes dos arquivos <texto> da entrada padr�o "stdin".

.ep
.in -3

.sp
Caso N�O sejam dados nomes de arquivos <texto> nem a op��o "-N",
� editado o texto lido de "stdin".

.in
.sp
.b "COMANDOS DE EDI��O"
.in 5
A edi��o � controlada pelos seguintes comandos:

.sp
.wo '- '
Padroniza��o vertical:
.sp
.in +3
 .pl - N�mero de linhas por p�gina
 .m1 - Espa�o no in�cio da p�gina
 .m2 - Espa�o abaixo do cabe�alho (se houver)
 .m3 - Espa�o entre a �ltima linha e o p� de p�gina
.in +6
(se houver)
.in -6
 .m4 - Espa�o no fim da p�gina
 .ls - Espa�o entre duas linhas consecutivas no texto
.in -3

.sp
.wo '- '
Padroniza��o horizontal:
.sp
.in +3
 .ll - comprimento da linha, em caracteres
 .po - margem � esquerda de todas as linhas do texto
.br
.wo '.in - n�mero'
de caracteres em branco a partir da margem
.in +6
esquerda
.in -9

.sp
.wo '- '
Cabe�alho e p� de p�gina:
.sp
.in +3
 .he '<esq>'<centro>'<dir>' - Cabe�alho
 .eh '<esq>'<centro>'<dir>' - Cabe�alho de p�ginas pares
 .oh '<esq>'<centro>'<dir>' - Cabe�alho de p�ginas �mpares
 .fo '<esq>'<centro>'<dir>' - P� de p�gina
 .ef '<esq>'<centro>'<dir>' - P� de p�gina de p�ginas pares
 .of '<esq>'<centro>'<dir>' - P� de p�gina de p�ginas
.in +29
�mpares
.in -29
.in -3

.sp
.wo '- '
Controle de p�gina:
.sp
.in +3
 .bp - T�rmino da p�gina corrente e come�o da outra
 .pn - Especifica o n�mero da p�gina corrente
 .tp - T�rmino da p�gina e come�o da p�gina de t�tulo
.in -3

.sp
.wo '- '
Controle de linha:
.sp
.br
.in +3
.wo '.br (ou branco na primeira coluna) -'
.in +6
Quebra a linha corrente
.in -6
 .wo - Define uma palavra entre '...' ou "..."
 .ce - Centra linhas no texto
.br
.wo ".tl '<esq>'<centro>'<dir>' -"
.in +6
Imprime uma linha da mesma forma que um cabe�alho
.in -6
 .sp - Quebra a linha atual e pula linhas
 .ul - Sublinha as pr�xima linhas do texto
 .nf - Imprime as linhas como est�o, sem formatar
 .li - Como ".nf"
 .fi - Retorna ao modo de ajustamento normal (termina ".nf")
.br
.wo ".sh - Numera"
o cap�tulo automaticamente
 .nr - Indenta os t�tulos dos cap�tulos
.in -3
        
.sp
.wo '- '
Controle de par�grafo:
.sp
.br
.in +3
.wo '.pp -'
Quebra a linha corrente, pula outra e imprime a
.in +6
pr�xima com indenta��o
.in -6

 .lp - Idem sem indenta��o
.br
.wo ".ip '<titulo>' <n> -"
.in +6
Quebra, pula uma linha e imprime o <t�tulo>, com linhas a seguir sendo
impressas com indenta��o constante <n> (valor por omiss�o: 5)
.in -6
.wo ".ep -"
Termina um par�grafo
.in -3

.sp
.wo '- '
Controle de blocos:
.sp
.in +3

.(l
   .bc		- Coment�rios: o <texto> ser� ignorado.
   <texto>
   .ec
.)l
.sp

.(l
   .(q		- Indenta o <texto> � esquerda e � direita
   <texto>		  em 5 caracteres
   .)q
.)l
.sp

.(l
   .(l		- Impress�o literal do <texto> indentado �
   <texto>		  esquerda em 5 caracteres
   .)l
.)l
.sp

.(l
   .(b [f]		- Impress�o de bloco fixo (sem o par�metro
   <texto>		  "f") ou flutuante
   .)b
.)l
.sp

.(l
   .(t		- Impress�o de bloco fixo sem altera��o
   <texto>		  automatica da indenta��o anterior 
   .)t
.)l
.sp

.(l
   .(f		- Impress�o de rodap� de p�gina
   <texto>
   .)f
.)l
.sp

.in -3

.(t
.wo '- '
Controle do tipo de caracter:
.sp
.in +3
  .r [<pal>] - Caracter tipo romano (normal)
.)t
  .i [<pal>] - Caracter it�lico
  .b [<pal>] - Muda o tipo dos caracteres para negrito

.ip OBS.: 6
Se a palavra <pal> for passada como par�metro, somente esta ser� impressa
com o tipo determinado no comando. Em caso contr�rio, o tipo de caracter
ser� v�lido para todo o texto at� um novo comando de
controle de tipo de caracter.
.lp
.in -3

.sp
.wo '- '
Formata��o de tabelas:
.sp
.in +3
 .ts - In�cio da tabela  
 .t& - Redefini��o dos formatos das linhas da tabela
 .te - Fim da tabela

.sp
Op��es:
.sp
.in +3
.wo "center -     Centra a tabela" 
.br
.wo "expand -     Expande a tabela"
.br
.wo "box -        Coloca a tabela em uma moldura"
.br
.wo "allbox -     Coloca todos os elementos da tabela em"
.br
.wo "             molduras"
.br
.wo "doublebox -  Coloca a tabela em uma moldura dupla"
.br
.wo "tab (<x>) -  Troca o caracter separador dos dados"
.br
.wo "             por <x>"
.br
.wo "title <n> -  A <n>-�sima linha de dados ser� usada como"
.br
.wo "             t�tulo em cada p�gina que a tabela"
.br
.wo "             continuar"
.in -3

.sp
Formatos:
.in +3
.sp
.wo "l - Campo ajustado � esquerda"
.br
.wo "c - Campo centrado"
.br
.wo "r - Campo ajustado � direita"
.br
.wo "n - Campo num�rico (ajustado pelo ponto decimal)"
.br
.wo "a - Subcoluna"
.br
.wo "s - Campo incorporado ao anterior"
.br
.wo "^ - Campo em branco"
.br
.wo "- - Campo com uma linha ('-')"
.br
.wo "= - Campo com uma linha dupla ('=')"
.br
.wo "| - Linha vertical entre duas colunas"
.in -3

.sp
Atributos dos formatos:
.sp
.in +3
.wo "f -       Troca o tipo de caracter do campo"
.br
.wo "b -       Campo em negrito"
.br
.wo "r -       Campo em romano"
.br
.wo "i -       Campo em it�lico"
.br
.wo "e -       Colunas com mesmo tamanho"
.br
.wo 'w (<n>) - <n> � a largura m�nima da coluna'
.br
.wo '<n> -     <n> � o espacejamento m�nimo entre esta'
.br
.wo '          e a pr�xima coluna'
.in -3

.sp
Dados:
.sp
.in +3
- Comando para o "sroff"
 - '-' ou '=' - Linha simples ou dupla (na linha inteira)
 - Campos separados por <tb>:
.in +3
- '-' ou '=' - Linha simples ou dupla no campo
 - '\-' ou '\=' - Linha simples ou dupla no elemento 
 - 'Rx' - 'x' em toda a extens�o do campo
 - '\&x' - 'x' � o elemento do campo
 - '\^' - Campo em branco
 - <s> - <s> � a cadeia de caracteres (elemento)
 - Campo vazio (dois <tb> seguidos) - campo em branco
.in -3
.in -3

.sp
Exemplo:
.sp
.in +3

.nf
              .ts
              allbox;
              c s s
              r c s
              l n n.
              titulo
              nome	valores
              x		1.2	45
              y		3.5	120
              z		34	490
              .te
.fi

.sp
Ir� gerar:

.sp
.ts
allbox;
c s s
r c s
l n n.
titulo
nome	valores
x	1.2	45
y	3.5	120
z	34	490
.te

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi
.br

.in
.sp
.b EXEMPLOS
.in 7
.sp
sroff arquivo
.sp
.in +3
formata o "arquivo" pondo o texto editado na sa�da padr�o.
.in -3
.sp

.(t
sroff man.* >manual
.sp
.in +3
concatena todos os arquivos cujos nomes come�am por "man.",
formata-os, e p�e o texto editado no arquivo "manual".
.in -3
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo

.in
