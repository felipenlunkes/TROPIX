.bp

.he 'LICEN�A (ref)'Detalhes de Licenciamento do TROPIX'LICEN�A (ref)'
.fo 'Atualizado em 16.06.99'Vers�o 2'Pag. %'

.sp 2
.nf
		DETALHES DE LICENCIAMENTO DO TROPIX
		===================================
.fi

.sp 3
.pp
O licenciamento do Sistema Operacional TROPIX � feito segundo
a LICEN�A P�BLICA GERAL DO GNU. Ela � dada em portugu�s a partir da
p�gina 3, e o documento original, em ingl�s, a partir da p�gina 11.

.pp
Alguns dos "drivers" para os dispositivos do PC foram baseados/inspirados
em trechos do n�cleo do Sistema Operacional FreeBSD
(Copyright � 1990 The Regents of the University of California,
Reservados todos os direitos).
Na p�gina 19 � dado o documento original desta licen�a.

.sp
A lista completa dos "drivers" �:

.in +3
.ip 1. 4
Disquete (arquivos "fd.c"):

.sp
C�digo derivado de "software" contribu�do para Berkeley por Don Ahn.

.sp
Copyright � 1993, 1994 por jc@irbs.UUCP (John Capo),
vak@zebub.msk.su (Serge Vakulenko), ache@astral.msk.su (Andrew A. Chernov).

.sp
Copyright � 1993, 1994, 1995 por joerg_wunsch@uriah.sax.de (Joerg Wunsch)
dufault@hda.com (Peter Dufault).

.ip 2. 4
Discos IDE (arquivos "hd.c"):

.sp
C�digo derivado de "software" contribu�do para Berkeley por William Jolitz.

.ip 3. 4
Controlador SCSI Adaptec 2940: (arquivos "sc*.c"):

.sp
Copyright � 1994 John Aycock

.sp
Copyright � 1995, 1996, 1997 Justin T. Gibbs.
Reservados todos os direitos.

.ip 4. 4
Controlador SCSI Adaptec 1542: (arquivos "sd*.c"):

.sp
(Quase totalmente) Escrito por Julian Elischer (julian@tfs.com)
para a TRW Financial Systems para o uso sob o sistema operacional MACH (2.5).

.sp
Transportado para o sistema operacional 386BSD  por Julian Elischer (julian@tfs.com)
setembro de 1992.

.ip 5. 4
Placa ethernet, compat�vel com NE2000 (arquivo "ed.c"):

.sp
Copyright � 1995, David Greenman.
Reservados todos os direitos.
      
.ip 6. 4
Porta Paralela (arquivo "lp.c"):

.sp
Copyright � 1990 William F. Jolitz, TeleMuse.
Reservados todos os direitos.

.ip 7. 4
Controle do barramento PCI (arquivos "pci.*"):

.sp
Copyright � 1994 Wolfgang Stanglmeier.
Reservados todos os direitos.

.ip 8. 4
Portas Serias (arquivos "sio.c"):

.sp
(sem autores expl�citos).

.ip 9. 4
Disco ZIP IOMEGA 100 MB, porta paralela (arquivo "zip.c"):

.sp
Copyright � 1997 Nicolas Souchu.
Reservados todos os direitos.

.ep
.in -3

.sp 2
Al�m disto, usamos o programa FDIMAGE para a distribui��o do TROPIX:
Copyright � 1996-7 Robert Nordier.




.bc	/*************************************/
.he ''------ LICEN�A P�BLICA GERAL DO GNU (vers�o 2) ------''
.fo 'Atualizado em 9.6.99''Pag. %'
.ec	/*************************************/

.bc	/*************************************/
 NOTE! This copyright does *not* cover user programs that use kernel
 services by normal system calls - this is merely considered normal use
 of the kernel, and does *not* fall under the heading of "derived work".
 Also note that the GPL below is copyrighted by the Free Software
 Foundation, but the instance of code that it refers to (the Linux
 kernel) is copyrighted by me and others who actually wrote it.

			Linus Torvalds

----------------------------------------

		    GNU GENERAL PUBLIC LICENSE
		       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.
                          675 Mass Ave, Cambridge, MA 02139, USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

.ec	/*************************************/

.bp
.nf
		    LICEN�A P�BLICA GERAL DO GNU
		    ============================
		     Vers�o 2, de Junho de 1991
.fi
.in +3
.sp
Copyright � 1989, 1991 Free Software Foundation, Inc.
675 Mass Ave, Cambridge, MA 02139, USA

.sp
Qualquer pessoa pode copiar e distribuir c�pias verbatim deste
documento de licen�a, mas n�o � permitido alter�-lo.

.sp
Esta � uma tradu��o da licen�a original, realizada pela equipe do TROPIX
para facilitar a sua leitura; o documento original � dado a partir da
p�gina 11.

.bc	/*************************************/
			    Preamble

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.
.ec	/*************************************/

.sp 3
.nf
			    PRE�MBULO
.fi
.sp
A maioria das licen�as de "software" � concebida para tirar a sua
liberdade de compartilh�-lo e modific�-lo. Em contraste, a inten��o da
Licen�a P�blica Geral do GNU � a de garantir a sua liberdade em compartilhar
e modificar "software" livre -- para garantir que o "software" seja livre
para todos os seus usu�rios. Esta Licen�a P�blica Geral aplica-se
para a maioria do "software" da "Free Software Foundation" e para
qualquer outro programa cujos autores decidiram-se a us�-lo.
(Certos outros "softwares" da "Free Software Foundation" s�o cobertos
pela Licen�a P�blica Geral de bibliotecas do GNU). Voc� tamb�m pode
aplic�-la aos seus programas.

.bc	/*************************************/
  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.
.ec	/*************************************/

.sp
Quando falamos de "software" livre, estamos nos referindo � liberdade,
n�o ao pre�o. Nossas Licen�as P�blicas Gerais s�o projetadas para
garantir que voc� possua a liberdade de distribuir c�pias de um
"software" livre (e cobrar por este servi�o, se desejar), que voc�
receba o c�digo fonte ou possa receb�-lo se desejar, que voc� possa
modificar o "software", ou dele usar partes em novos programas;
e que voc� saiba que pode fazer estas coisas.

.bc	/*************************************/
  To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.
.ec	/*************************************/

.sp
Para proteger os seus direitos, precisamos fazer restri��es que pro�bam
qualquer pessoa de tirar estes seus direitos ou pedir-lhe que desista
destes direitos. Estas restri��es implicam certas responsabilidades
para voc� se voc� distribuir c�pias do "software", ou se voc� o
modificar.

.bc	/*************************************/
  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.
.ec	/*************************************/

.sp
Por exemplo, se voc� distribui c�pias de um destes programas,
independente se gr�tis ou por uma taxa, voc� necessita dar a todos
os novos usu�rios todos os direitos que voc� possui. Voc� precisa
garantir que tamb�m eles, recebam, ou possam receber o c�digo fonte.
Al�m disto, voc� precisa mostrar a eles estes termos para que eles 
conhe�am os seus direitos.

.bc	/*************************************/
  We protect your rights with two steps: (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.
.ec	/*************************************/

.sp
N�s protegemos os seus direitos atrav�s de 2 passos: (1) obter o
direito de c�pia ("copyright")
do "software" e (2) oferecer esta licen�a que lhe d� permiss�o legal
para copiar, distribuir e/ou modificar o "software".

.bc	/*************************************/
  Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.
.ec	/*************************************/

.sp
Al�m disto, para a nossa prote��o e a de cada autor, queremos certificar-nos
de que n�o h� garantia para este "software" livre. Se o "software" for
modificado por certa pessoa e passado adiante, queremos que esta �ltima
pessoa saiba que o que ela recebeu n�o � mais o original, de tal modo que
problemas introduzidos por outros n�o ir�o se refletir na reputa��o do
autor original.

.bc	/*************************************/
  Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.
.ec	/*************************************/

.sp
Finalmente, qualquer programa livre � permanentemente amea�ado por
patentes de "software". N�s queremos evitar o perigo de que redistribuidores
de um programa livre obtenham licen�as de patentes individualmente,
tornando em efeito, o programa propriet�rio. Para evitar isto, n�s
esclarecemos que qualquer patente dever� ser feita para o uso livre
de todos, ou ent�o n�o ser licenciada para ningu�m.

.bc	/*************************************/
  The precise terms and conditions for copying, distribution and
modification follow.

		    GNU GENERAL PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
.ec	/*************************************/

.sp
Os termos precisos e condi��es para a c�pia, distribui��o e
modifica��o s�o:

.sp 3
.nf
		   LICEN�A P�BLICA GERAL DO GNU
		   ============================
     TERMOS E CONDI��ES PARA A C�PIA, DISTRIBUI��O E MODIFICA��O
.fi

.bc	/*************************************/
  0. This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law:
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".
.ec	/*************************************/

.sp 2
.ip 0. 4
Esta Licen�a aplica-se a qualquer programa ou outro trabalho que
contenha uma nota colocada pelo dono do direito de c�pia dizendo que
ele pode ser distribu�do sob os termos desta Licen�a P�blica Geral.
A palavra "programa", abaixo, refere-se a qualquer destes programas
ou trabalhos, e um "trabalho baseado no programa" refere-se ou ao
programa ou a qualquer trabalho derivado sob a lei do direito de c�pia:
isto �, um trabalho contendo o programa ou parte deste, ou "verbatim"
ou com modifica��es e/ou tradu��es para outra linguagem. (A partir
deste ponto, uma tradu��o � inclu�da sem limita��es no termo
"modifica��o".) Cada pessoa licenciada � denominada "voc�".

.bc	/*************************************/
Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.
.ec	/*************************************/

.sp
Atividades outras al�m de copiar, distribuir ou modificar n�o est�o
cobertas por esta licen�a; elas est�o fora do seu escopo. O ato
de executar o programa n�o � restrito, e a sa�da do programa �
coberta apenas se o seu conte�do constituir um trabalho baseado
no programa (independentemente se foi obtido atrav�s da execu��o
do programa). Se isto � verdadeiro ou n�o, depende do que o programa faz.

.bc	/*************************************/
  1. You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.
.ec	/*************************************/

.sp
.ip 1. 4
Voc� pode copiar e distribuir c�pias "verbatim" do c�digo fonte
do programa quando voc� o recebe, atrav�s de qualquer meio, desde que
voc� publique consp�cua e apropriadamente em cada c�pia uma
nota de direito de c�pia adequada, e a aus�ncia de garantia; mantenha
intactas todas as notas que se referem a esta licen�a e � aus�ncia de qualquer
garantia; e dar a todos os outros recipientes do programa uma c�pia
desta licen�a juntamento com o programa.

.bc	/*************************************/
You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.
.ec	/*************************************/

.sp
Voc� pode cobrar uma taxa para o ato f�sico de transferir uma c�pia,
e pode opcionalmente oferecer uma garantia atrav�s de uma taxa.

.bc	/*************************************/
  2. You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:
.ec	/*************************************/

.pp
.ip 2. 4
Voc� pode modificar sua c�pia ou c�pias do programa ou qualquer
parte dele, deste modo formando um trabalho baseado no programa, e
copiar e distribuir estas modifica��es ou trabalho segundo os termos
da se��o 1. acima, desde que voc� tamb�m satisfa�a todas as seguintes
condi��es:

.bc	/*************************************/
    a) You must cause the modified files to carry prominent notices
    stating that you changed the files and the date of any change.
.ec	/*************************************/

.in +5
.ip a. 3
Voc� deve anexar aos arquivos modificados notas indicando que voc�
modificou os arquivos e a data desta modifica��o.

.bc	/*************************************/
    b) You must cause any work that you distribute or publish, that in
    whole or in part contains or is derived from the Program or any
    part thereof, to be licensed as a whole at no charge to all third
    parties under the terms of this License.
.ec	/*************************************/

.ip b. 3
Voc� deve tomar provid�ncias para que todo trabalho que voc� distribua
ou publique, o qual contenha totalmente/parcialmente o programa,
ou seja derivado deste ou de qualquer parte sua, seja licenciado como um todo,
sem nenhum custo para todos os interessados, segundo os termos desta
licen�a.

.bc	/*************************************/
    c) If the modified program normally reads commands interactively
    when run, you must cause it, when started running for such
    interactive use in the most ordinary way, to print or display an
    announcement including an appropriate copyright notice and a
    notice that there is no warranty (or else, saying that you provide
    a warranty) and that users may redistribute the program under
    these conditions, and telling the user how to view a copy of this
    License.  (Exception: if the Program itself is interactive but
    does not normally print such an announcement, your work based on
    the Program is not required to print an announcement.)
.ec	/*************************************/

.ip c. 3
Se o programa modificado normalmente l� comandos interativamente
quando executado, voc� deve fazer com que ele, durante o in�cio
da sua execu��o em tal modo interativo no maneira mais usual, a
imprimir ou exibir um texto incluindo uma ressalva apropriada de
direito de c�pia e uma nota de que n�o h� garantia (ou se for o caso,
dizendo que voc� fornece uma garantia) e que usu�rios podem redistribuir
o programa segundo estas condi��es, e explicando ao usu�rio como
ele pode ler uma c�pia desta licen�a. (Exce��o: se o programa
for interativo, mas normalmente n�o indica nada a este respeito, seu
trabalho baseado no programa n�o necessita de imprimir a ressalva.)

.bc	/*************************************/
These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.
.ec	/*************************************/

.in -5

.sp
Estes requerimentos aplicam-se apenas ao trabalho modificado como um todo.
Se partes identific�veis do trabalho n�o s�o derivados do programa,
e podem ser razoavelmente consideradas trabalhos independentes e
separados, ent�o esta licen�a e seus termos n�o se aplicam a estas
se��es quando voc� as distribui como trabalhos separados. No entanto,
se voc� distribuir estas se��es como parte de um todo que � um trabalho
baseado no programa, a distribui��o deste todo dever� ser nos termos
desta licen�a, cujas permiss�es para outros licenciados estendem-se
para o todo, e portanto para cada parte, independente de quem a escreveu.

.bc	/*************************************/
Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.
.ec	/*************************************/

.sp
Portanto, n�o � a inten��o desta se��o exigir direitos ou contestar
seus direitos sobre um trabalho inteiramente escrito por voc�; ao contr�rio,
a inten��o � a de controlar a distribui��o de um derivado ou trabalhos
coletivos baseados no programa.

.bc	/*************************************/
In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.
.ec	/*************************************/

.sp
Al�m disto, a mera adi��o de outro trabalho n�o baseado no programa
ao programa (ou a um trabalho baseado no programa) em um volume
de armazenamento ou meio de distribui��o n�o p�e o outro trabalho
sob o escopo desta licen�a.

.bc	/*************************************/
  3. You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following:
.ec	/*************************************/

.ip 3. 4
Voc� pode copiar e distribuir o programa (ou um trabalho baseado nele,
de acordo com a se��o 2) em c�digo objeto/execut�vel sob os termos
das se��es 1. e 2. acima, desde que voc� tamb�m fa�a um dos itens abaixo:

.bc	/*************************************/
    a) Accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of Sections
    1 and 2 above on a medium customarily used for software interchange; or,
.ec	/*************************************/

.in +5
.ip a. 3
Acompanhe-o do c�digo fonte correspondente completo, em forma leg�vel
por computador, que dever� ser distribu�do sob os termos das
se��es 1. e 2. acima em um meio normalmente usado para o interc�mbio
de "software"; ou,

.bc	/*************************************/
    b) Accompany it with a written offer, valid for at least three
    years, to give any third party, for a charge no more than your
    cost of physically performing source distribution, a complete
    machine-readable copy of the corresponding source code, to be
    distributed under the terms of Sections 1 and 2 above on a medium
    customarily used for software interchange; or,
.ec	/*************************************/

.ip b. 3
Acompanhe-o de uma oferta escrita, v�lida por no m�nimo 3 anos,
para dar a qualquer pessoa, por uma taxa n�o superior ao seu custo
de f�sicamente efetuar a distribui��o do c�digo fonte, uma c�pia
completa e em forma leg�vel por computador, do c�digo
fonte correspondente, a ser distribu�do de acordo com as se��es 1. 
e 2. acima, em um meio normalmente usado para o interc�mbio
de "software"; ou,

.bc	/*************************************/
    c) Accompany it with the information you received as to the offer
    to distribute corresponding source code.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form with such
    an offer, in accord with Subsection b above.)
.ec	/*************************************/

.ip c. 3
Acompanhe-o da informa��o que voc� recebeu na oferta de distribuir
o c�digo fonte correspondente. (Esta alternativa s� � permitida em
distribui��es n�o-comerciais e somente se voc� recebeu o programa
em c�digo objeto/execut�vel com tal oferta, de acordo com a subse��o
b. acima.)

.bc	/*************************************/
The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.
.ec	/*************************************/

.in -5
.sp
O c�digo fonte de um trabalho constitui a forma preferida para nele
realizar modifica��es. Para um trabalho execut�vel, um c�digo fonte
completo inclui o c�digo fonte para todos os seus m�dulos,
todos os arquivos de interface associados, e arquivos usados para
controlar a compila��o e a instala��o dos programas execut�veis.
No entanto, como um exce��o especial, o c�digo fonte distribu�do
n�o necessita incluir nada que � normalmente distribu�do (seja
em c�digo fonte ou objeto) com os componentes regulares (compiladores,
n�cleo, ...) do sistema operacional no qual o programa execut�vel
funciona, a n�o ser que aquele pr�prio componente acompanha o execut�vel.

.bc	/*************************************/
If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.
.ec	/*************************************/

.sp
Se a distribui��o de um programa objeto/execut�vel � realizada atrav�s
da oferta de acesso para a c�pia de determinado lugar,
ent�o a oferta equivalente de acesso para a c�pia do c�digo fonte
conta como uma distribui��o do c�digo fonte, mesmo que n�o seja
obrigat�ria a c�pia do c�digo fonte juntamente com o c�digo objeto.

.bc	/*************************************/
  4. You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.
.ec	/*************************************/

.ip 4. 4
Voc� somente pode copiar, modificar, sublicenciar ou distribuir o
programa nos modos expressamente definidos nesta licen�a. Qualquer
tentativa de copiar, modificar, sublicenciar ou distribuir o programa
de outro modo � nula, e ir� automaticamente terminar os seus direitos
atrav�s desta licen�a. No entanto, outras pessoas que receberam c�pias
ou direitos atrav�s desta licen�a, n�o ter�o as suas licen�as terminadas,
enquanto elas as respeitarem.



.bc	/*************************************/
  5. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.
.ec	/*************************************/

.ip 5. 4
Voc� n�o � obrigado a aceitar esta licen�a, j� que voc� n�o a assinou.
No entanto, nada al�m disto lhe d� permiss�o para modificar ou
distribuir o programa ou os seus trabalhos derivados. Estas a��es
s�o proibidas por lei, se voc� n�o aceitar esta licen�a. Portanto,
pela modifica��o ou distribui��o do programa (ou qualquer trabalho
nele baseado), voc� indica a sua aceita��o desta licen�a e de todos
os seus termos e condi��es para copiar, modificar, ou
distribuir o programa ou trabalhos nele baseado.

.bc	/*************************************/
  6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.
.ec	/*************************************/

.ip 6. 4
Cada vez que voc� redistribuir o programa (ou qualquer trabalho nele baseado),
o recipiente automaticamente recebe a licen�a do licenciador original
para copiar, modificar, ou distribuir o programa, sujeito a estes
termos e condi��es. Voc� n�o pode impor nenhuma restri��o adicional
aos direitos dos recipientes. Voc� n�o � respons�vel por controlar
a obedi�ncia de outras pessoas a esta licen�a.


.bc	/*************************************/
  7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.
.ec	/*************************************/

.ip 7. 4
Se, por conseq��ncia de um julgamento legal ou alega��o de uma
infra��o de patente, ou por qualquer outra raz�o (n�o limitada a
assuntos de patentes), s�o impostas condi��es a voc� (por ordem
judicial, acordos ou outros modos) que contradizem as condi��es
desta licen�a, elas n�o o liberam das condi��es desta licen�a.
Se voc� n�o puder realizar a distribui��o de tal modo a satisfazer
simultaneamente suas obriga��es oriundas desta licen�a e todas
as outras obrigac�es pertinentes, ent�o, como conseq��ncia,
voc� n�o pode distribuir o programa. Por exemplo, se uma licen�a
de patente n�o permitir a redistribui��o gratuita do programa
por todos aqueles que recebem c�pias direta ou indiretamente atrav�s
de voc�, ent�o o �nico modo que voc� pode satisfazer a ambos
seria deixar inteiramente de distribuir o programa.

.bc	/*************************************/
If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.
.ec	/*************************************/

.sp
Se alguma por��o desta se��o for considerada inv�lida ou
n�o puder ser efetivada em alguma circunst�ncia particular,
as demais por��es desta se��o devem ser aplicadas, e a se��o integral
deve ser aplicada em outras circunst�ncias.

.bc	/*************************************/
It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.
.ec	/*************************************/

.sp
N�o � a inten��o desta se��o induzi-lo a infringir qualquer patente
ou outros direitos de propriedade, nem contestar a validade de
tais direitos; esta se��o tem o �nico objetivo de proteger a
integridade do sistema de distribui��o de "software" livre, que �
implementado atrav�s das licen�as p�blicas. Muitas pessoas t�m
feito contribui��es generosas � larga gama de "software" distribu�do
atrav�s deste sistema em concord�ncia na aplica��o consistente
deste sistema; o autor/doador � que deve decidir se ele est� disposto
a distribuir o seu "software" atrav�s de qualquer outro sistema e
nenhum licenciado pode impor esta escolha.

.bc	/*************************************/
This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.
.ec	/*************************************/

.sp
Esta se��o pretente esclarecer o que se acredita ser uma conseq��ncia
do resto desta licen�a.

.bc	/*************************************/
  8. If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.
.ec	/*************************************/

.ip 8. 4
Se a distribui��o e/ou o uso do programa � restrito a certos pa�ses
seja por patentes ou por interfaces de direito de c�pia, o dono do
direito de c�pia original que p�e o programa sob esta licen�a pode adicionar
uma limita��o geogr�fica expl�cita excluindo estes pa�ses, de tal modo
que a distribui��o s� seja permitida nos pa�ses n�o exclu�dos. Neste caso,
a licen�a incorpora a limita��o como se estivesse escrita no corpo
desta licen�a.

.bc	/*************************************/
  9. The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.
.ec	/*************************************/

.ip 9. 4
A "Free Software Foundation" pode publicar vers�es revisadas e/ou novas
da Licen�a P�blica Geral periodicamente. Estas novas vers�es ser�o
similares em esp�rito � presente vers�o, mas podem diferir em detalhes
para resolver novos problemas ou preocupa��es.

.bc	/*************************************/
Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.
.ec	/*************************************/

.sp
Cada vers�o recebe um n�mero un�voco. Se um programa especificar
um n�mero de vers�o desta licen�a que a ele aplica e a "qualquer vers�o
posterior", voc� tem a op��o de seguir os termos e condi��es desta vers�o  
ou de qualquer vers�o posterior publicada pela "Free Software Foundation".
Se o programa n�o especificar a vers�o desta licen�a, voc� pode escolher
qualquer vers�o j� publicada pela "Free Software Foundation".

.bc	/*************************************/
  10. If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.
.ec	/*************************************/

.ip 10. 4
Se voc� desejar incluir partes do programa em outros programas livres,
mas cujas condi��es de distribui��o s�o diferentes, escreva para o autor
e pe�a permiss�o. Para "software" cujo direito de c�pia pertence �
"Free Software Foundation", escreva para ela; n�s �s vezes fazemos exe��es
para tais casos. Nossa decis�o ser� guiada pelos 2 objetivos de preservar
o estado livre de todos os derivados de "software" livre e promover
o compartilhamento e reuso de "software" em geral.


.bc	/*************************************/
			    NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.
.ec	/*************************************/

.sp 2
.nf
			N�O H� GARANTIA
.fi

.ip 11. 4
EM VIRTUDE DO FATO DO PROGRAMA SER LICENCIADO GRATUITAMENTE,
N�O H� NENHUMA GARANTIA
PARA O PROGRAMA, DENTRO DOS LIMITES PERMITIDOS PELA LEI. EXCETO QUANDO H�
UMA NOTA INDICANDO OUTRA COISA, OS DETENTORES DO DIREITO DE C�PIA E/OU OUTRAS
PESSOAS FORNECEM O PROGRAMA "COMO EST�", SEM GARANTIA DE NENHUM TIPO,
SEJA EXPRESSA OU IMPL�CITA, INCLUINDO, MAS N�O LIMITADO �S GARANTIAS
DE COMERCIALIZA��O E APLICABILIDADE A UM DETERMINADO OBJETIVO EM PARTICULAR.
VOC� ASSUME
TODO O RISCO DA QUALIDADE E DESEMPENHO DO PROGRAMA. SE O PROGRAMA CONTIVER
DEFEITOS, VOC� ASSUMIR� O CUSTO DE TODOS OS SERVI�OS E CONSERTOS NECESS�RIOS.


.bc	/*************************************/
  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

		     END OF TERMS AND CONDITIONS
.ec	/*************************************/

.ip 12. 4
EM NENHUM CASO, A N�O SER IMPOSTO PELA LEI APLIC�VEL OU EM UM ACORDO
ESCRITO, TER� QUALQUER DONO DO DIREITO DE C�PIA, OU OUTRAS PESSOAS QUE
TENHAM MODIFICADO E/OU REDISTRIBU�DO O PROGRAMA DA FORMA COMO PERMITIDO
ACIMA, SER� RESPONS�VEL POR PREJU�ZOS, INCLUINDO QUAISQUER PREJU�ZOS
GERAIS, ESPECIAIS, INCIDENTAIS OU COMO CONSEQ��NCIA OCASIONADOS
ATRAV�S DO USO OU INABILIDADE PARA USAR O PROGRAMA (INCLUINDO, MAS N�O
LIMITADO � PERDA/DESTRUI��O PARCIAL DE DADOS OCASIONADOS POR VOC�
OU TERCEIROS, OU POR UMA FALHA DO PROGRAMA EM INTEROPERAR CORRETAMENTE
COM OUTROS PROGRAMAS), MESMO QUE O DONO OU OUTRAS PESSOAS TENHAM SIDO
AVISADOS DA POSSIBILIDADE DE TAIS PREJU�ZOS.

.sp
.nf
		FIM DOS TERMOS E CONDI��ES
.fi
.ep

.bc	/*************************************/
	Appendix: How to Apply These Terms to Your New Programs

  If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.
.ec	/*************************************/

.sp 3
.nf
	Ap�ndice: Como aplicar estes termos ao seu novo programa
.fi

.sp
Se voc� desenvolveu um novo programa, e deseja que ele seja do m�ximo
proveito poss�vel para o p�blico, o melhor modo de conseguir isto, �
faz�-lo um "software" livre, o qual todos podem redistribuir e modificar
segundo estes termos.

.bc	/*************************************/
  To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.
.ec	/*************************************/

.sp
Para fazer isto, anexe as seguintes notas ao programa. O mais seguro
� anex�-las no in�cio de cada arquivo fonte para conter do modo mais
eficiente a indica��o da aus�ncia de garantia; e em cada arquivo
deve haver pelo menos a linha com o direito de c�pia e um ponteiro
para onde a licen�a completa pode ser encontrada.

.bc	/*************************************/
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 19yy  <name of author>
.ec	/*************************************/


.sp 2
.in +5
<algumas linhas para dar o nome do programa e uma breve descri��o do que ele faz.>
.br
Copyright � 19aa <nome do autor>
.br

.bc	/*************************************/
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
.ec	/*************************************/

.sp
Este programa � um "software" livre; voc� pode redistribu�-lo e/ou
modific�-lo segundo os termos da Licen�a P�blica Geral do GNU, como
publicada pela "Free Software Foundation"; a vers�o 2 da licen�a, ou
(de acordo com a sua op��o), qualquer vers�o posterior.

.bc	/*************************************/
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
.ec	/*************************************/

.sp
Este programa � distribu�do na esperan�a de que seja �til, mas
SEM NENHUMA GARANTIA; nem mesmo a garantia impl�cita de 
COMERCIALIDADE ou APLICABILIDADE PARA UM DETERMINADO OBJETIVO.
Veja a Licen�a P�blica Geral do GNU para maiores detalhes.

.bc	/*************************************/
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
.ec	/*************************************/

.sp
Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral do GNU
juntamente com este programa; se n�o foi o caso, escreva para a
"Free Software Foundation, Inc.", 675 Mass Ave, Cambridge, MA 02139, USA.

.bc	/*************************************/
Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode:
.ec	/*************************************/

.in -5
.sp
Inclua tamb�m informa��es de como contact�-lo atrav�s de correio eletr�nico
e correio tradicional.

.sp
Se o programa for interativo, fa�a-o escrever uma pequena nota como a
abaixo quando ele entrar no modo interativo:

.bc	/*************************************/
    Gnomovision version 69, Copyright (C) 19yy name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.
.ec	/*************************************/

.sp
.in +5
Gnomovision, vers�o 69, Copyright � 19aa <nome do autor>
Gnomovision vem ABSOLUTAMENTE SEM GARANTIA; para maiores detalhes,
tecle "show w". Isto � um "software" livre, e voc� � bemvindo para
redistribu�-lo sob certas condi��es; tecle "show c" para maiores detalhes.
.in -5

.bc	/*************************************/
The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.
.ec	/*************************************/

.sp
Os comando hipot�ticos "show w" e "show c" devem mostrar as partes apropriadas
da Licen�a P�blica Geral do GNU. Obviamente, os comandos que voc� usar� podem
ser diferentes de "show w" e "show c"; poder�o inclusive ser cliques do
"mouse" ou itens de um "menu" -- o que melhor se adequar ao seu programa.

.bc	/*************************************/
You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names:
.ec	/*************************************/

.sp
Voc� deve tamb�m obter do seu empregador (caso voc� trabalhe como programador)
ou da sua escola, se for o caso, a assinatura de um documento desistindo do direito
de c�pia para o programa, se for necess�rio. Abaixo damos um exemplo; altere
os nomes:

.bc	/*************************************/
  Yoyodyne, Inc., hereby disclaims all copyright interest in the program
  `Gnomovision' (which makes passes at compilers) written by James Hacker.

  <signature of Ty Coon>, 1 April 1989
  Ty Coon, President of Vice
.ec	/*************************************/

.sp
.in +5
A Companhia Yoyodyne, Inc., desiste de todo direito de c�pia do programa
"Gnomovision" (que realiza passos de compiladores) escrito por James Hacker.
.in -5

.sp
.nf
	<assinatura de TY Coon>, 1 de abril de 1989

		Ty Coon, presidente
.fi

.bc	/*************************************/
This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Library General
Public License instead of this License.
.ec	/*************************************/

.sp
Esta Licen�a P�blica Geral n�o permite a incorpora��o do seu programa em
programas propriet�rios. Se o seu programa for uma biblioteca de subrotinas,
voc� poder� considerar mais �til usar a Licen�a P�blica Geral de bibliotecas
do GNU ao inv�s desta licen�a.

.bp

.nf
		     GNU GENERAL PUBLIC LICENSE
		     ==========================
		        Version 2, June 1991
.fi

.sp
Copyright � 1989, 1991 Free Software Foundation, Inc.
675 Mass Ave, Cambridge, MA 02139, USA

.sp
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.

.sp 3
.nf
			    PREAMBLE
.fi

.sp
The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.

.sp
When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.

.sp
To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.

.sp
For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.

.sp
We protect your rights with two steps: (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.

.sp
Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.

.sp
Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.

.sp
The precise terms and conditions for copying, distribution and
modification follow.

.sp 3
.nf
		    GNU GENERAL PUBLIC LICENSE
		    ==========================
    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
.fi

.sp 2
.ip 0. 4
This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law:
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".

.sp
Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

.ip 1. 4
You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.

.sp
You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

.ip 2. 4
You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:

.in +5
.ip a. 3
You must cause the modified files to carry prominent notices
stating that you changed the files and the date of any change.

.ip b. 3
You must cause any work that you distribute or publish, that in
whole or in part contains or is derived from the Program or any
part thereof, to be licensed as a whole at no charge to all third
parties under the terms of this License.

.ip c. 3
If the modified program normally reads commands interactively
when run, you must cause it, when started running for such
interactive use in the most ordinary way, to print or display an
announcement including an appropriate copyright notice and a
notice that there is no warranty (or else, saying that you provide
a warranty) and that users may redistribute the program under
these conditions, and telling the user how to view a copy of this
License.  (Exception: if the Program itself is interactive but
does not normally print such an announcement, your work based on
the Program is not required to print an announcement.)

.in -5

.sp
These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.

.sp
Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.

.sp
In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

.ip 3. 4
You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following:

.in +5
.ip a. 3
Accompany it with the complete corresponding machine-readable
source code, which must be distributed under the terms of Sections
1 and 2 above on a medium customarily used for software interchange; or,

.ip b. 3
Accompany it with a written offer, valid for at least three
years, to give any third party, for a charge no more than your
cost of physically performing source distribution, a complete
machine-readable copy of the corresponding source code, to be
distributed under the terms of Sections 1 and 2 above on a medium
customarily used for software interchange; or,

.ip c. 3
Accompany it with the information you received as to the offer
to distribute corresponding source code.  (This alternative is
allowed only for noncommercial distribution and only if you
received the program in object code or executable form with such
an offer, in accord with Subsection b above.)

.in -5
.sp
The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.

.sp
If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.

.ip 4. 4
You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

.ip 5. 4
You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

.ip 6. 4
Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

.ip 7. 4
If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.

.sp
If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.

.sp
It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

.sp
This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

.ip 8. 4
If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

.ip 9. 4
The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

.sp
Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

.ip 10. 4
If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.

.sp 2
.nf
			  NO WARRANTY
.fi


.sp
.ip 11. 4
BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

.ip 12. 4
IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

.sp
.nf
		END OF TERMS AND CONDITIONS
.fi
.ep

.sp 3
.nf
	Appendix: How to Apply These Terms to Your New Programs
.fi


.sp
If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.

.sp
To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.

.sp 2
.in +5
<some lines to give the program's name and a brief idea of what it does.>
.br
Copyright � 19yy  <name of author>
.br

.sp
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

.sp
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

.sp
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

.in -5
.sp
Also add information on how to contact you by electronic and paper mail.

.sp
If the program is interactive, make it output a short notice like this
when it starts in an interactive mode:

.in +5
.sp
Gnomovision version 69, Copyright � 19yy <name of author>
.br
Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
.br
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.

.in -5
.sp
The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

.sp
You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names:

.in +5
.sp
Yoyodyne, Inc., hereby disclaims all copyright interest in the program
`Gnomovision' (which makes passes at compilers) written by James Hacker.

.sp
<signature of Ty Coon>, 1 April 1989
.br
Ty Coon, President of Vice

.in -5
.sp
This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Library General
Public License instead of this License.

.bp
.sp 2
.nf
		 LICENSE OF THE UNIVERSITY OF CALIFORNIA
		 =======================================
.fi
.sp 2
Copyright � 1991 The Regents of the University of California.
All rights reserved.

.sp
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

.in +3
.ip 1. 3
Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

.ip 2. 3
Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

.ip 3. 3
All advertising materials mentioning features or use of this software
must display the following acknowledgement:
This product includes software developed by the University of
California, Berkeley and its contributors.

.ip 4. 3
Neither the name of the University nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

.ep
.in -3
.sp
THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
