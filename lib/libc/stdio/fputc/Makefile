#*
#****************************************************************
#*	Makefile para a fun??o "fputc"				*
#****************************************************************
#*
DIR	= stdio
PGM	= fputc
MAN	= libc
LIBC	= /lib/libc
CC	= cc

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

modif:		modif.r
		sroff modif.r >$mandir/modif/$MAN/$PGM
		modif $PGM

man:
		@echo Veja ../putc

prman:
		@echo Veja ../putc

gar:
		cd ..; gar -ovs0 $PGM
		cd ..; gar -icv0
