.bp 1
.he 'ISO (fmt)'TROPIX: Manual de Refer�ncia'ISO (fmt)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Tabelas de c�digos de cararacteres:
.sp
.wo "iso   -"
c�digo de caracteres padr�o ISO (ou CBII, ou BRASCII)
.br
.wo "ascii -"
c�digo de caracteres padr�o ASCII
.br

.in
.sp
.b DESCRI��O
.in 5
O c�digo de padr�o ISO (International Standard Organization)
que � igual ao c�digo CBII (C�digo Brasileiro para o 
Interc�mbio de Informa��es) � o c�digo padr�o do TROPIX.
Este � um c�digo de 8 bites.

.sp
O c�digo ASCII (American Standard Code for Information 
Interchange) � um c�digo de 7 bites. 

.sp
Os 128 caracteres poss�veis de serem representados no c�digo
ASCII coincidem com os 128 primeiros caracteres da representa��o do
c�digo ISO, que permite 256 combina��es. Os c�digos s�o
representados pela tabela abaixo onde aparecem o valor do caracter
em hexadecimal seguido do seu nome.

.sp
.nf
  | 00 nul| 01 soh| 02 stx| 03 etx| 04 eot| 05 enq| 06 ack| 07 bel|
  | 08 bs | 09 ht | 0A nl | 0B vt | 0C np | 0D cr | 0E so | 0F si |
  | 10 dle| 11 dc1| 12 dc2| 13 dc3| 14 dc4| 15 nak| 16 syn| 17 etb|
  | 18 can| 19 em | 1A sub| 1B esc| 1C fs | 1D gs | 1E rs | 1F us |
  | 20 sp | 21  ! | 22  " | 23  # | 24  $ | 25  \% | 26  & | 27  ' |
  | 28  ( | 29  ) | 2A  * | 2B  + | 2C  , | 2D  - | 2E  . | 2F  / |
  | 30  0 | 31  1 | 32  2 | 33  3 | 34  4 | 35  5 | 36  6 | 37  7 |
  | 38  8 | 39  9 | 3A  : | 3B  ; | 3C  < | 3D  = | 3E  > | 3F  ? |
  | 40  @ | 41  A | 42  B | 43  C | 44  D | 45  E | 46  F | 47  G |
  | 48  H | 49  I | 4A  J | 4B  K | 4C  L | 4D  M | 4E  N | 4F  O |
  | 50  P | 51  Q | 52  R | 53  S | 54  T | 55  U | 56  V | 57  W |
  | 58  X | 59  Y | 5A  Z | 5B  [ | 5C  \ | 5D  ] | 5E  ^ | 5F  _ |
  | 60  ` | 61  a | 62  b | 63  c | 64  d | 65  e | 66  f | 67  g |
  | 68  h | 69  i | 6A  j | 6B  k | 6C  l | 6D  m | 6E  n | 6F  o |
  | 70  p | 71  q | 72  r | 73  s | 74  t | 75  u | 76  v | 77  w |
  | 78  x | 79  y | 7A  z | 7B  { | 7C  | | 7D  } | 7E  ~ | 7F del|

  | 80    | 81    | 82    | 83    | 84    | 85    | 86    | 87    |
  | 88    | 89    | 8A    | 8B    | 8C    | 8D    | 8E    | 8F    |
  | 90    | 91    | 92    | 93    | 94    | 95    | 96    | 97    |
  | 98    | 99    | 9A    | 9B    | 9C    | 9D    | 9E    | 9F    |
  | A0 nbs| A1  � | A2  � | A3  � | A4  � | A5  � | A6  � | A7  � |
  | A8  � | A9  � | AA  � | AB  � | AC  � | AD  � | AE  � | AF  � |
  | B0  � | B1  � | B2  � | B3  � | B4  � | B5  � | B6  � | B7  � |
  | B8  � | B9  � | BA  � | BB  � | BC  � | BD  � | BE  � | BF  � |
  | C0  � | C1  � | C2  � | C3  � | C4  � | C5  � | C6  � | C7  � |
  | C8  � | C9  � | CA  � | CB  � | CC  � | CD  � | CE  � | CF  � |
  | D0  � | D1  � | D2  � | D3  � | D4  � | D5  � | D6  � | D7  � |
  | D8  � | D9  � | DA  � | DB  � | DC  � | DD  � | DE  � | DF  � |
  | E0  � | E1  � | E2  � | E3  � | E4  � | E5  � | E6  � | E7  � |
  | E8  � | E9  � | EA  � | EB  � | EC  � | ED  � | EE  � | EF  � |
  | F0  � | F1  � | F2  � | F3  � | F4  � | F5  � | F6  � | F7  � |
  | F8  � | F9  � | FA  � | FB  � | FC  � | FD  � | FE  � | FF  � |

.fi
.in
.sp
.b OBSERVA��O
.in 5
Como o c�digo ISO � o padr�o para o TROPIX, o
oitavo bite dos caracteres nunca � desprezado.
Para garantir a
compatibilidade de caracteres em c�digo ASCII  com o 
c�digo ISO, o oitavo bite do
c�digo ASCII deve ser mantido em zero.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sort
.br
.wo "(libc):"
strcmp, memcmp, cmptb
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
