#include "semafory.h"

int main()
{
    char buffer[100];
    int len = 0;

    int fd = otworz_plik();

    utworz_semafor();

    printf("Sekcja t21 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t21 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);
    semafor_v(0);

    semafor_p(1);
    printf("Sekcja t22 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t22 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);
    semafor_v(2);

    semafor_p(3);
    printf("Sekcja t23 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t23 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);
    semafor_v(4);

    close(fd);

    return 0;
}