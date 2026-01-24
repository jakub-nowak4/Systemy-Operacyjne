#include "common.h"

int main(int argc, char *argv[]) {

    int fd = atoi(argv[1]);

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "wy_%d.txt", getpid());

    FILE * plik = fopen(buffer, "w");
    if (plik == NULL) {
        printf("Blad przy tworzeniu pliku\n");
        exit(EXIT_FAILURE);
    }

    char znak;
    int bytes_read;
    while((bytes_read = read(fd, &znak, 1)) > 0)
    {
        fputc(znak, plik);
        printf("Konsument %d odczytał znak %c\n", getpid(), znak);
        sleep(1);
    }

    if(bytes_read == -1)
    {
        perror("Blad przy czytaniu z pipe\n");
        fclose(plik);
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Konsument %d zakonczyl dzialanie\n", getpid());
    if (fclose(plik) != 0) {
        perror("Blad przy zamykaniu pliku\n");
        exit(EXIT_FAILURE);
    }
    if (close(fd) == -1) {
        perror("Blad przy zamykaniu potoku\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}