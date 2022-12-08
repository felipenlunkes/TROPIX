.tp
.sp 10
.nf
      *******   *******  *******   *******    *    *     *
         *      *     *  *     *   *     *    *     *   *
         *      *     *  *     *   *     *    *      * *
         *      *******  *     *   *******    *       *
         *      *   *    *     *   *          *      * *
         *      *    *   *     *   *          *     *   *
         *      *     *  *******   *          *    *     *
.fi
.sp 10
.ce
VI - Editor Visual de Textos
.sp 2
.ce
Vers�o 3.0.1
.sp 4
.ce
Guia
.sp 10
.ce
Abril de 1997
.he ' '- ii - ' '
.bp
.sp 4
.ce
.b
APRESENTA��O
.r
.sp 2

.pp
Este � o guia do Editor Visual de Textos "vi",
o editor de textos padr�o do Sistema Operacional Multiprocessado TROPIX.

.pp
O editor "vi" foi desenvolvido a partir
das especifica��es da interface com o usu�rio
de um editor hom�nimo criado e implementado
na Universidade da California, em Berkeley,
e adotado pela AT&T para o Unix System V.

.pp
Desde a vers�o 2.0 o "vi" incorpora em seu modo Comandos
toda a funcionalidade do editor "ed"
(incluindo express�es regulares,
substitui��es e transfer�ncia/c�pia de blocos)
e em seu modo Visual v�rias extens�es
(incluindo a marca��o de linhas,
a capacidade de repeti��o do �ltimo comando de edi��o
e um conjunto de novos comandos para a localiza��o no texto).

.pp
Este manual descreve os comandos do editor "vi" em sua Vers�o 3.0.1.
O Cap�tulo 1 introduz os conceitos b�sicos
para a compreens�o do funcionamento do editor "vi".
O Cap�tulo 2 descreve os comandos do modo Visual;
s�o apresentados os comandos para observa��o e localiza��o no texto em edi��o,
os comandos para altera��o do texto em edi��o e
as opera��es de c�pia e transfer�ncia de blocos de texto.
O Cap�tulo 3 descreve o modo Comandos;
s�o apresentados os comandos e
como especificar a sua abrang�ncia no texto em edi��o.
O Cap�tulo 4 descreve a inclus�o de texto novo via teclado.
O Cap�tulo 5 descreve o subconjunto de express�es regulares
reconhecidas pelo editor.

.pp
As formas de evoca��o do editor "vi" a partir do Interpretador de Comandos
podem ser encontradas nas p�ginas do Manual de refer�ncia do Sistema TROPIX
referentes ao editor "vi" (cmd).

.he ' '- iii - ' '
.bp
.sp 10
.ce
CONTE�DO
.sp 5
.in +3
Cap. 1 - Conceitos Fundamentais ............................ 1
.sp
Cap. 2 - Modo Visual ....................................... 3
.sp
.in +3
2.1 - Observa��o e Localiza��o no Texto ................. 3
.sp
2.2 - Edi��o B�sica do Texto ............................ 5
.sp
2.3 - C�pia e Transfer�ncia de Blocos de Texto .......... 7
.in -3
.sp
Cap. 3 - Modo Comandos ..................................... 8
.sp
.in +3
3.1 - Endere�amento ..................................... 8
.sp
3.2 - Comandos .......................................... 9
.in -3
.sp
Cap. 4 - Entrada e Inser��o de Texto via Teclado ........... 15
.sp
Cap. 5 - Express�es Regulares .............................. 17
.in -3

.bp 1
.he 'Sistema TROPIX'Guia'VI'
.fo 'Atualizado em 30.04.97'Vers�o 3.0.1'Pag. %'

