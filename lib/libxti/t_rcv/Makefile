#*
#****************************************************************
#*	Makefile para a fun??o "t_rcv"				*
#****************************************************************
#*
PGM	= t_rcv
PROT	= u=rw,a+r
MAN	= xti
DEF	= -D PC -D LITTLE_ENDIAN

COUNT	= 100

.virtual	lint t at wt cp cmp man prman modif gar

$PGM.o:		$PGM.c
		cc $DEF -O -c $PGM.c
		size $PGM.o
		ls -l $PGM.o
		nm $PGM.o | /usr/bin/c

lint:		$PGM.c
		cc $DEF -T $PGM.c

t:		s c
		s -v

s:		s.o $PGM.o
		cc -f -o s s.o $PGM.o -lxti

s.o:		s.c
		cc -c s.c

c:		c.o $PGM.o
		cc -f -o c c.o $PGM.o -lxti

c.o:		c.c
		cc -c c.c

at:		as ac
		as -v

as:		as.o $PGM.o
		cc -f -o as as.o $PGM.o -lxti

as.o:		as.c
		cc -c as.c

ac:		ac.o $PGM.o
		cc -f -o ac ac.o $PGM.o -lxti

ac.o:		ac.c
		cc -c ac.c

wt:		ws wc
		ws $COUNT

ws:		ws.o $PGM.o
		cc -f -o ws ws.o $PGM.o -lxti

ws.o:		ws.c
		cc -c ws.c

wc:		wc.o $PGM.o
		cc -f -o wc wc.o $PGM.o -lxti

wc.o:		wc.c
		cc -c wc.c

cp:		$PGM.o
		mklib -rv /lib/libxti $PGM.o
		chmod -v $PROT /lib/libxti/$PGM.o

cmp:
		-cmpobj $PGM.o /lib/libxti

man:		man.r
		sroff man.r >$mandir/$MAN/$PGM
		man $PGM

prman:
		sroff man.r | lpr

modif:		modif.r
		sroff modif.r >$mandir/modif/$MAN/$PGM
		modif $PGM

gar:
		cd ..; gar -ovs9 $PGM
		cd ..; gar -icv9
