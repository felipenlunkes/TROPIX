#define	A_H	1
#define	B_H	2

TEXTO: A_H, B_H

#if defined A_H
A_H est� definido
#endif

#if defined (B_H)
B_H est� definido
#endif

#if defined (A_H) && defined (B_H)
Ambos est�o definidos
#endif

LINE=__LINE__;
DATE=__DATE__;
TIME=__TIME__;
STDC=__STDC__;
FILE=__FILE__;
