while true do
   #
	echo -n 'Continua? '
#
#	Corpo do WHILE.
#
	if askyesno -s then
#
		echo '   In�cio do FOR'
#
		for i in * do
			echo -n '   Pr�ximo arquivo? '
			if askyesno -s then
				echo '      ' $i
			else
				break
			fi
		done
#
		echo '   Fim do FOR'
	else
		break
	fi
#
	echo 'Mais uma itera��o do while completa'
done
