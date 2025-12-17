#include "utils.h"

int main()
{
    FILE *plik = fopen("./producent.txt", "r");
    if (plik == NULL)
    {
        perror("Nie udalo sie otworzyc pliku producent.txt");
        exit(EXIT_FAILURE);
    }

    printf("Producent zaczyna prace PID:%d\n", getpid());

    key_t klucz_pam;
    key_t klucz_sem;
    char *data;

    wygenreuj_klucz(&klucz_pam, 1);
    wygenreuj_klucz(&klucz_sem, 2);

    utworz_semafor(klucz_sem);
    utworz_shm(klucz_pam);

    przylacz_pamiec(&data);

    int znak;
    while((znak = getc(plik)) != EOF)
    {
        semafor_p(0);
        printf("Wysyłam wartość do konsumenta: %c\n", znak);
        *data = znak;
        sleep(1);
        semafor_v(1);
    }

    printf("Producent skonczyl wysylanie\n");
    semafor_v(2);

    if (shmdt(data) == -1)
    {
        perror("Nie udalo sie odlaczyc pamiec dzielonej od pamiec wirtualenj procesu");
        exit(EXIT_FAILURE);
    }

    if(fclose(plik) != 0)
    {
        perror("Nie udalo sie poprawnie zamknac pliku");
        exit(EXIT_FAILURE);
    }

    return 0;
}