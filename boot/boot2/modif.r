.bp
.he 'BOOT (sys)'TROPIX: Manual de Modifica��es'BOOT (sys)'
.fo 'Atualizado em 26.07.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "boot -"
sistema de carga do sistema operacional TROPIX
.br

.in
.sp 2
.ip "01.01.96  3.0.0" 20
VERS�O CORRENTE
.sp

.ip "26.07.96  3.0.1" 20
O m�dulos "boot2" foi estendido para
continuar com a fase seguinte no caso de nada ser teclado
ap�s (aproximadamente) 15 segundos.

.sp
O m�dulo "boot2" agora � carregado em 64 KB (autocopiando-se
para 1 MB).

.ip "16.02.97  3.0.5" 20
Foi consertado o detalhe da tabela de caracteres para as cores 9-15 em
"boot2/seg.16.s". 

.sp
Foi extendida o tamanho de programas que o "boot2" pode ler de 261
para 325 KB.

.ip "06.03.97  3.0.6" 20
Unificado o tratamento dos dispositivos SCSI em "boot2".

.sp
Agora, o dispositivo "ZIP 100" mesmo que n�o presente no momento do "boot2",
pode ser montado mais tarde.

.ip "30.03.97  3.0.7" 20
Estendido todo o sistema do "boot2" para acessar o segundo controlador
IDE.

.ip "02.04.97  3.0.8" 20
Feita uma revis�o geral.

.ip "10.08.98  3.1.0" 20
Adicionada a impress�o de �reas vagas em meio � tabela de parti��es do "fdisk".

.ip "15.12.99  3.1.1" 20
Ordenando os dispositivos SCSI colocando discos remov�veis no final.

.ip "21.01.99  3.1.2" 20
Contando a mem�ria f�sica, ao inv�s de confiar na CMOS.

.ip "14.04.99  3.1.8" 20
Adicionado o FAT 32.

.ip "13.02.00  3.2.2" 20
Introduzida a identifica��o dos dispositivos ATAPI.

.ip "06.04.00  3.2.3" 20
Introduzida a identifica��o do modem U.S. Robotics PCI.

.ip "13.04.00" 20
Colocado o "lbasize" para discos IDE de mais de 8 GB.

.ip "04.05.00" 20
Colocado o JAZ.

.ip "29.06.00  4.0.0" 20
Completada a identifica��o das CPUs incluindo a freq��ncia.
Reestruturada a estrutura BCB, agora com vers�o.
O n�cleo agora herda o valor de DELAY, e as informa��es do
DMA dos discos IDE.

.ip "18.07.00" 20
Atualizado o m�dulo "src/hd.c", utilizando um novo header do n�cleo
("ataparam.h").

.ip "19.07.00" 20
Desligando a interrup��o ("disint") logo antes de entrar
em 32 bits.

.ip "26.07.00" 20
Revistas as mensagens de parti��es com mais de 1024 cilindros.

.ip "27.07.00" 20
Adicionadas mensagens/controles sobre parti��es FAT16/32 G/L.

.ip "15.01.01" 20
Usando a nova interface PCI do kernel.

.ip "10.04.01" 20
Aumentado o n�mero de blocos lidos do arquivo.

.ip "28.04.01" 20
Introduzido o teste de tamanho, para verificar se pode carregar o n�cleo
abaixo de 640Kb.

.ip "12.10.01  4.2.0" 20
Feita uma revis�o na "disktb" (old & new) para permitir v�rias
controladoras SCSI.

.ip "11.07.02  4.3.0" 20
Reescrito integralmente o c�digo para os dispositivos ATA/ATAPI.

.ip "27.08.02" 20
Adicionado o c�digo para processar o sistema de arquivos T1.

.ip "09.09.02" 20
Incorporada a op��o "-i" para simplificar a instala��o.

.ip "13.01.04" 20
Introduzido o reconhecimento dos controladores USB do tipo UHCI e OHCI.

.ip "01.04.04" 20
Introduzido o reconhecimento dos controladores USB do tipo EHCI.

.ip "19.04.04  4.6.0" 20
Iniciado o processamento de carga de CDs.

.ip "03.11.04" 20
Usando a int 0x15, 0xE820 para obter informa��es sobre a mem�ria utiliz�vel.

.ip "09.12.04  4.7.0" 20
Desligado o "wait_for_ctl_Q", pois agora h� o "dmesg".

.ip "10.03.05" 20
Consertado o problema do "timeout" para o comando IDENTIFY em
"ata-all.c".

.sp
Alterado o c�lculo do cilindro na tripla geom�trica da tabela de 
parti��o (1023).

.ip "22.08.05  4.8.0" 20
Alterado "seg.32.s" para permitir o endere�amento de 2 GB de mem�ria.

.ip "03.11.05" 20
Truncando a mem�ria a 2 GB.

.ip "26.07.06" 20
Introduzia a tabela de parti��es de emerg�ncia.
