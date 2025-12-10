#include "semafory.h"

int main()
{
    char buffer[100];
    int len = 0;

    int fd = otworz_plik();

    utworz_semafor();

    semafor_p(2);

    printf("Sekcja t11 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t11 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);

    printf("Sekcja t12 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t12 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);

    semafor_v(3);

    close(fd);

    return 0;
}