#include "utils.h"

int main()
{
    FILE *plik = fopen("konsument.txt","a");
    if(plik == NULL)
    {
        perror("Nie udalo sie otworzyc pliku konsument.txt");
        exit(EXIT_FAILURE);
    }
    printf("Konsument zaczyna prace PID:%d\n", getpid());

    key_t klucz_pam;
    key_t klucz_sem;
    char *data;

    wygenreuj_klucz(&klucz_pam, 1);
    wygenreuj_klucz(&klucz_sem, 2);

    utworz_semafor(klucz_sem);
    utworz_shm(klucz_pam);

    przylacz_pamiec(&data);

    while(odczytaj_wartosc_semafora() != 1)
    {
        semafor_p(1);
        printf("Odbieram  wartość od producenta: %c\n",*data);
        putc(*data,plik);
        sleep(2);
        semafor_v(0);
    }

    printf("Producent odebral plik\n");

    usun_semafor();

     if(shmdt(data) == -1)
    {
        perror("Nie udalo sie odlaczyc pamiec dzielonej od pamiec wirtualenj procesu");
        exit(EXIT_FAILURE);
    }

    usun_shm();

    if(fclose(plik) != 0)
    {
        perror("Nie udalo sie zamknac pliku konsument.txt");
        exit(EXIT_FAILURE);
    }

    return 0;
}