#include "semafory.h"

int main()
{
    utworz_semafor();

    semafor_p(2);
    printf("Sekcja t11 procesu o PID=%d\n", getpid());
    sleep(1);

    printf("Sekcja t12 procesu o PID=%d\n", getpid());
    sleep(1);

    semafor_v(3);

    return 0;
}