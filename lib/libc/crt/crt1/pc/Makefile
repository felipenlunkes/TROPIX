#*
#****************************************************************
#*	Makefile para a fun??o "crt1"				*
#****************************************************************
#*
DIR	= crt
PGM	= crt1
PROT	= u=rw,a+r
MAN	= libc

.virtual	cp cmp man prman modif gar

$PGM.o:		$PGM.s
		as -o $PGM.o -l $PGM.l $PGM.s
		size $PGM.o
		ls -l $PGM.o
		nm $PGM.o

t:		../t.c $PGM.o
		cc -o t ../t.c $PGM.o

cp:		$PGM.o
		mklib -crv $DIR/$PGM.o
		chmod -v $PROT /lib/libc/$DIR/$PGM.o

cmp:
		-cmpobj $PGM.o /lib/libc/$DIR

man:		../man.r
		sroff ../man.r >$mandir/$MAN/$PGM
		-ln $mandir/$MAN/$PGM $mandir/$MAN/lcrt1
		man -l $PGM

modif:		../modif.r
		sroff ../modif.r >$mandir/modif/$MAN/$PGM
		modif $PGM

prman:		
		sroff ../man.r | lpr

gar:
		cd ..; gar -ovs0 $PGM
		cd ..; gar -icv0
