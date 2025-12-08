#include "semafory.h"

int main()
{
    utworz_semafor();

    printf("Sekcja t21 procesu o PID=%d\n", getpid());
    sleep(1);
    semafor_v(0);

    semafor_p(1);
    printf("Sekcja t22 procesu o PID=%d\n", getpid());
    sleep(1);
    semafor_v(2);

    semafor_p(3);
    printf("Sekcja t23 procesu o PID=%d\n", getpid());
    sleep(1);
    semafor_v(4);

    return 0;
}