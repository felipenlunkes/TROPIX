#include "./pcntl.h"

main ()
{

	int	stackrgsz;
	int	pri;

	stackrgsz = pcntl (P_GETSTKRGSZ);
	printf ("Stack region original = %08X\n", stackrgsz);
	printf ("For�ando stack de 3 p�ginas\n");
	stackrgsz = pcntl (P_SETSTKRGSZ, 12000);
	printf ("Stack region alterada = %08X\n", stackrgsz);

	pri = pcntl (P_GETPRI);
	printf ("Prioridade original = %d\n", pri);
	printf ("For�ando prioridade 550\n");
	pcntl (P_SETPRI, 550);
	pri = pcntl (P_GETPRI);
	printf ("Prioridade alterada = %d\n", pri);

}
