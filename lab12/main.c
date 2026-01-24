#include "common.h"

int main(int argc, char *argv[]) {
    
    
    if (argc < 4) {
        printf("Blad: nieprawidlowa liczba argumentow\n");
        printf("Uzycie: %s arg1 arg2 arg3\n", argv[0]);
        printf("arg1 - liczba konsumentow\n");
        printf("arg2 - liczba producentow\n");
        printf("arg3 - liczba znakow wyprodukowanych przez producenta w buforze\n");
        exit(EXIT_FAILURE);
    }

    int liczba_konsumentow = atoi(argv[1]);
    int liczba_producentow = atoi(argv[2]);
    int liczba_znakow = atoi(argv[3]);

    printf("Konfiguracja: konsumentow=%d, producentow=%d, znakow=%d\n", liczba_konsumentow, liczba_producentow, liczba_znakow);

    FILE * p = popen("bash -c 'ulimit -u'", "r");
    if (p == NULL) {
        printf("Blad przy otwarciu pliku\n");
        exit(EXIT_FAILURE);
    }

    char bufor[128];
    if (fgets(bufor, sizeof(bufor), p) != NULL) {
        printf("Limit ulimit -u: %s", bufor);
        int limit = atoi(bufor);
        if (limit < liczba_konsumentow + liczba_producentow + 1) {
            printf("Blad: liczba procesow jest wieksza niz limit ulimit -u\n");
            exit(EXIT_FAILURE);
        }
    }
    pclose(p);

    int fd[2];

    if(pipe(fd) == -1) {
        printf("Blad przy tworzeniu pipe\n");
        exit(EXIT_FAILURE);
    }

    char producent_fd_str[10];
    char konsument_fd_str[10];
    sprintf(producent_fd_str, "%d", fd[1]); 
    sprintf(konsument_fd_str, "%d", fd[0]); 


    for(int i=0; i < liczba_producentow; i++) {
        switch(fork())
        {
            case -1:
                printf("Blad przy tworzeniu procesu\n");
                exit(EXIT_FAILURE);
            case 0:
                close(fd[0]);
                printf("Producent %d\n", i);
                execlp("./producent", "producent", producent_fd_str, argv[3], NULL);
                exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i < liczba_konsumentow; i++) {
        switch(fork())
        {
            case -1:
                printf("Blad przy tworzeniu procesu\n");
                exit(EXIT_FAILURE);
            case 0:
                close(fd[1]);
                printf("Konsument %d\n", i);
                execlp("./konsument", "konsument", konsument_fd_str, NULL);
        }
    }

    if(close(fd[0]) == -1) {
        perror("Blad przy zamykaniu fd[0]");
        exit(EXIT_FAILURE);
    }
    if(close(fd[1]) == -1) {
        perror("Blad przy zamykaniu fd[1]");
        exit(EXIT_FAILURE);
    }

    while(wait(NULL) > 0);
    return 0;
}
