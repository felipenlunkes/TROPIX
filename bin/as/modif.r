.bp
.he 'AS.486 (cmd)'TROPIX: Manual de Modifica��es'AS.486 (cmd)'
.fo 'Atualizado em 05.12.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "as.486 -"
montador para INTEL-80386/486/PENTIUM
.br

.in
.sp 2
.ip "07.07.94  3.0.0" 20
VERS�O CORRENTE
.sp

.ip "25.07.94  3.0.1" 20
Agora s� aceitando 2 d�gitos hexadecimais em seq��ncias de "escape" do
tipo "....\x12....".

.ip "07.08.94  3.0.2" 20
Agora, as opera��es "<<" e ">>" s�o SEM sinal.

.ip "12.08.94  3.0.3" 20
Pequeno esquecimento de permitir reloca��o na se��o CONST.

.ip "16.08.94  3.0.4" 20
Agora, podendo ter valores reloc�veis do CONST para TEXT e vice-versa.

.ip "26.08.94  3.0.5" 20
Consertado o esquecimento das vers�es "far" de "ret".
.sp
Adicionados os sin�nimos "enable", "disable", "inten" e "intdis".

.ip "04.09.94  3.0.6" 20
Acrescentados "callgw" e "callgl".
.sp
Trocado "enable" por "enint" e "disable" por "disint".
.sp
Corrigido os "pushs" e "pops" para registros de segmenta��o.
.sp
Criado o conceito de "NEEDED" para gerenciar imediatos e deslocamentos
indefinidos no primeiro passo.
.sp
Feita uma revis�o no m�dulo "expr.c".

.ip "16.09.94  3.0.7" 20
Foram criadas as pseudos ".ifnz", ".ifdef", ".elif", ".else" e outras.
.sp
Foi acrescentada a op��o "-D".
.sp
Agora "[" � sin�nimo de "{".

.ip "26.09.94  3.0.8" 20
M�dulo "if.c": as express�s n�o s�o mais avaliadas se "false_level"
diferente de zero.
.sp
M�dulos "regular1.c" e "regular2.c": a an�lise de
operandos agora permite termos operandos opcionais.
.sp
A Tabela "src_op_table.c"
foi alterada para refletir os operandos opcionais (em particular do
"muls").
.sp
Acrescentados os operadores relacionais "==", "!=", ">", ">=", "<" e "<=".
.sp
Acrescentados os operadores l�gicos "&&", "||" e "!".

.ip "??.??.??  3.0.9" 20
.wo .............

.ip "??.??.??  3.0.10" 20
.wo .............

.ip "08.04.97  3.0.11" 20
.wo .............

.ip "07.08.97  3.0.12" 20
Introduzida a sintaxe "call *alpha" e "jmp *alpha".

.ip "23.01.00  3.2.3" 20
A vers�o do programa objeto passa a ser 0.

.ip "16.11.00  4.0.0" 20
Incorporadas as novas instru��es de m�quina:
"bswap", "cpuid", "invd", "invlpg", "rdmsr", "rsm", "wbinvd", wrmsr", "xadd", e "rdtsc".

.sp
No momento faltando apenas "cmpxchg" e "cmpxchg8b" para completar o
repert�rio do Pentium.

.ip "22.08.01  4.0.0" 20
Novo formato da tabela de s�mbolos SYM.

.ip "24.08.01  4.1.0" 20
Identificadores sem limite de tamanho.

.ip "20.08.02  4.3.0" 20
Novo c�lculo (simplificado) dos SDIs.

.ip "17.03.03  4.4.0" 20
Agora vetor de indefini��es do passo 1 din�mico. Usando "malloc" da libc.

.ip "05.12.03  4.5.0" 20
Estendido o processamento de SDIs para ALIGNs.
