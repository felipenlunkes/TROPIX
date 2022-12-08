# TROPIX

> Descrição retirada do [site original](http://www.tropix.nce.ufrj.br/). Aparentemente, o sistema teve seu desenvolvimento suspenso.

O TROPIX (pronuncia-se "Trópix") é um Sistema Operacional multiusuário e multitarefa, de filosofia UNIX®, desenvolvido no Núcleo de Computação Eletrônica da Universidade Federal do Rio de Janeiro (NCE/UFRJ).

O TROPIX foi inicialmente concebido durantes os anos de 1982 a 1986 (na época com o nome PLURIX) para o computador PEGASUS. Este computador foi construído também no NCE, e era baseado nos processadores MOTOROLA 68010/20. O sistema foi transportado em 1987 para o computador ICARUS, também baseado nestes mesmos processadores. Em 1994 foi iniciado o transporte para a linha INTEL de processadores (386, 486, Pentium), e desde 1996 o TROPIX já está operacional em PCs, sendo utilizado em diversos computadores.

O TROPIX tem diversas utilidades, tais como o estudo/aprendizado/utilização de um sistema operacional de filosofia UNIX, o desenvolvimento de programas ("software") e a implementação de servidores para a INTERNET (esta página que você está lendo está vindo do servidor WWW de um computador rodando TROPIX). Além disto, é ideal para a utilização em cursos de sistemas operacionais, pois contém primitivas para processos "leves" ("threads"), memória compartilhada, semáforos a nível de usuário, dentre outros.

A distribuição do TROPIX é gratuita, segundo a licença pública do GNU.

Atualmente, o desenvolvimento e manutenção do TROPIX estão sendo feitos por Pedro Salenbauch e Oswaldo Vernet. Para maiores informações, sugestões, comunicação de erros, ou em caso de quaisquer dúvidas sobre a sua instalação e utilização, use o endereço eletrônico syspedrosal@gmail.com.

A continuação deste trabalho é uma homenagem póstuma para Newton Faller, o grande idealizador dos projetos PEGASUS, PLURIX, TROPIX e de tantos outros.

## Requisitos para execução

> Nota: Foram testados o qemu e o VirtualBox para executar o TROPIX em 2022. O sistema só conseguiu ser inicializado utilizando o VirtualBox.

O PC deve possuir um processador Intel 486/PENTIUM ou equivalente. O mínimo razoável de memória principal é 8 MB. Com 4 MB é possível utilizar o sistema, mas pode haver dificuldades em simultaneamente usar a rede INTERNET e compilar programas. Para o Sistema Gráfico X-Window são necessários pelo menos 16 MB.

São suportados disquetes de 3½" e 5¼", e discos rígidos IDE/ATA/SATA. Também são suportados discos rígidos SCSI conectados através dos controladores SCSI Adaptec 1542 (ISA) e 2940/29160 (PCI).

Os discos Iomega ZIP (100 MB) e CDROMs também são suportados, nas versões de porta paralela (ZIP), IDE/ATAPI e SCSI (desde que conectados a um dos controladores SCSI indicados acima).

Para a rede INTERNET, são suportados os controladores "ethernet" Novell (NE1000, NE2000 ISA/PCI), 3Com 3c503 e Realtek RTL 8129/8139 Fast Ethernet (10/100 Mbs), além de linhas seriais com protocolos SLIP ou PPP.

São suportadas também as portas paralelas para o uso de impressoras.

São reconhecidos "mouse"s e "pen drive" USB, desde que conectados à portas USB dos padrões UHCI, OHCI ou EHCI.

São aceitos os Fax-modems ISA e o Fax-modem U.S. Robotics 56K PCI.

É suportada a saída de áudio digital (DSP) das placas de som "Sound Blaster 16" (ou sucessoras), para a execução de músicas PCM (arquivos "*.wav").

