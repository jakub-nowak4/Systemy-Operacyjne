#include "common.h"

int main(int argc, char *argv[]) {

    int fd = atoi(argv[1]);
    int ilosc_znakow = atoi(argv[2]);

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "we_%d.txt", getpid());

    FILE * plik = fopen(buffer, "w");
    if (plik == NULL) {
        printf("Blad przy tworzeniu pliku\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL) ^ getpid());

    for(int i=0; i < ilosc_znakow; i++) {
        char znak = 'a' + rand() % 26;
        fputc(znak, plik);
        if(write(fd, &znak, 1) == -1)
        {
            perror("Blad przy zapisywaniu do pipe\n");
            fclose(plik);
            close(fd);
            exit(EXIT_FAILURE);
        }

        printf("Producent %d zapisal znak %c\n", getpid(), znak);
        sleep(1);
    }

    printf("Producent %d zakonczyl dzialanie\n", getpid());
    
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