echo -n "Entre com uma cadeia: ";  read x
case $x in
        [0-9]* ) echo Come�a com d�gito ;;
	a*     ) echo Come�a com a ;;
	b*     ) echo Come�a com b ;;
	*      ) echo N�o come�a nem com a nem com b ;;
esac
