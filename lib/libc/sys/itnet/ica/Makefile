#*
#****************************************************************
#*	Makefile para a chamada ao sistema "itnet"		*
#****************************************************************
#*
LIBC	= /lib/libc
DIR	= sys
PGM	= itnet
MAN	= sys

.virtual	cp cmp man prman modif gar

$PGM.o:
		@echo N?o dispon?vel para o ICARUS

cp:
		@echo N?o dispon?vel para o ICARUS

cmp:
		@echo N?o dispon?vel para o ICARUS

man:
		@echo Veja $libxti

prman:
		@echo Veja $libxti

modif:		../modif.r
		sroff ../modif.r >$mandir/modif/$MAN/$PGM
		modif $PGM

gar:
		cd ..; gar -ovs0 $PGM
		cd ..; gar -icv0
