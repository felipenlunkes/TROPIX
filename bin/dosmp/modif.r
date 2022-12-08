.bp
.he 'DOSMP (cmd)'TROPIX: Manual de Modifica��es'DOSMP (cmd)'
.fo 'Atualizado em 28.08.07'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "dosmp -"
processa um sistema de arquivos no formato MS-DOS
.br

.in
.sp 2
.ip "05.03.96  3.0.0" 20
VERS�O CORRENTE
.sp

.ip "24.05.96  3.0.1" 20
Criada o novo indicador de estado "lfn_mode".

.ip "02.06.96  3.0.2" 20
Criado o comando "du". Consertado o comprimento do identificador
em "ftw" (max_len).

.ip "09.06.96  3.0.3" 20
Criado o comando "waste".

.ip "21.06.96  3.0.4" 20
Consertado o pequeno detalhe do "dev_mode".

.ip "14.02.97  3.0.5" 20
Alterada a filosofia do cache da FAT. Agora s� s�o lidas/escritas
as entradas necess�rias.

.ip "25.04.97  3.0.6" 20
Uma pequena revis�o.

.ip "04.08.97  3.0.7" 20
Introduzida a op��o "-P".

.ip "27.10.97  3.0.8" 20
Consertado o detalhe da compara��o das duas FATs em "fsck".
Introduzido o comando "chsize".

.ip "09.11.98  3.1.0" 20
Introduzido (finalmente) o algoritmo de "checksum" do Win95
dos nomes longos.

.sp
Acrecentados os dispositivos "-2" e "-3" para os "zip"s.

.ip "15.01.99  3.1.1" 20
Foi atualizada a chamada � fun��o "askyesno".

.ip "30.04.99  3.1.8" 20
Adicionado FAT32, comando "compac" e as cores para "lc", "ls" e "walk".

.ip "11.07.99  3.2.2" 20
Consertado o "compac", que estava parando quando um CLUSTER iria ser
movido para cima.

.ip "27.07.00  4.0.0" 20
Atualizados os c�digos das diversas parti��es DOS FAT*, e tamb�m
verificado se n�o s�o criados CLUSTERs maiores do que 32 KB.

.ip "11.08.01  4.0.0" 20
Usando "readdir".

.ip "17.04.02  4.2.0" 20
Adicionadas as cores brilhantes.

.ip "29.10.02  4.4.0" 20
Alterado o "lseek" para "llseek", agora sem a limita��o de 4 GB.

.ip "03.10.03  4.5.0" 20
Alterado a convers�o para/de min�sculas/ma�usculas conforme o n�cleo.

.ip "02.05.04  4.6.0" 20
Pequeno conserto no DEV do dispositivo (em "do_mount.c").

.ip "17.05.04" 20
Criado o comando "sys".

.ip "11.09.04" 20
Consultando a "fstab" se for dado um diret�rio.

.ip "07.07.05  4.8.0" 20
Alterados "src/mkv.c" e "src/do_mv.c" para consertar o detalhe dos
nomes de volumes.

.ip "09.07.05" 20
Agora possibilitando a atualiza��o da c�pia do SB.

.ip "23.09.05" 20
Criado o comando "edbad".

.ip "19.10.05" 20
Incorporada a op��o "-c" do "mkfs".

.ip "05.09.06  4.9.0" 20
Revis�o na aloca��o de CLUSTERs FAT32/FAT16 para alinh�-los em 4KB.

.ip "28.08.07" 20
Revis�o da obten��o dos caracteres 8.3 (em "do_lfn.c").
