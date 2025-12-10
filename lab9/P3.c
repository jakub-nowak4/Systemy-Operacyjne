#include "semafory.h"

int main()
{
    char buffer[100];
    int len = 0;

    int fd = otworz_plik();

    utworz_semafor();

    semafor_p(0);
    printf("Sekcja t31 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t31 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);

    printf("Sekcja t32 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t32 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);
    semafor_v(1);

    semafor_p(4);
    printf("Sekcja t33 procesu o PID=%d\n", getpid());
    len = sprintf(buffer, "Sekcja t33 procesu o PID=%d\n", getpid());
    write(fd, buffer, len);
    sleep(1);

    close(fd);

    return 0;
}