#include "semafory.h"

int main()
{
    utworz_semafor();

    semafor_p(0);
    printf("Sekcja t31 procesu o PID=%d\n", getpid());
    sleep(1);

    printf("Sekcja t32 procesu o PID=%d\n", getpid());
    sleep(1);
    semafor_v(1);

    semafor_p(4);
    printf("Sekcja t33 procesu o PID=%d\n", getpid());
    sleep(1);

    return 0;
}