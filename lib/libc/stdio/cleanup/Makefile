#*
#****************************************************************
#*	Makefile para a fun??o "cleanup"			*
#****************************************************************
#*
LIBC	= /lib/libc
CC	= cc
DIR	= stdio
PGM	= _cleanup
MAN	= libc

.virtual	lint cp cmp man prman modif gar

$PGM.o:		$PGM.c
		$CC -O -c $PGM.c
		size $PGM.o
		ls -l $PGM.o
		nm $PGM.o | c

lint:		
		$CC -T $PGM.c

t:		t.o $PGM.o
		$CC -o t t.o $PGM.o

t.o:		t.c
		$CC -c t.c

cp:		$PGM.o
		mklib -rv $LIBC $DIR/$PGM.o
		chmod -v u=rw,a+r $LIBC/$DIR/$PGM.o

cmp:
		-cmpobj $PGM.o $LIBC/$DIR

man:
		@echo Fun??o auxiliar - n?o possui manual

modif:
		@echo Fun??o auxiliar - n?o possui manual

prman:
		@echo Fun??o auxiliar - n?o possui manual

gar:
		cd ..; gar -ovs0 $PGM
		cd ..; gar -icv0
