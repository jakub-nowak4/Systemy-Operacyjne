#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MIN 10
#define MAX 100
#define ROW 2
#define COL 10

int tab[ROW][COL] = {0};

void wyswietl_tablice();
void *oblicz_sume_wiersza(void *numerWiersza);

int main()
{
    srand(time(NULL));

    for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
    {
        for (int j = 0; j < sizeof(tab[0]) / sizeof(int); j++)
        {
            tab[i][j] = (rand() % (MAX - MIN + 1)) + MIN;
        }
    }

    pthread_t watek1;
    pthread_t watek2;

    if (pthread_create(&watek1, NULL, oblicz_sume_wiersza, (void *)0) != 0 || pthread_create(&watek2, NULL, oblicz_sume_wiersza, (void *)1) != 0)
    {
        printf("Nie udalo sie utworzyc watkow\n");
        exit(EXIT_FAILURE);
    }

    int *watek1_suma;
    int *watek2_suma;

    if (pthread_join(watek1, (void **)&watek1_suma) != 0)
    {
        printf("Nie udalo sie przylaczyc watku 1.\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(watek2, (void **)&watek2_suma) != 0)
    {
        printf("Nie udalo sie przylaczyc watku 2.\n");
        exit(EXIT_FAILURE);
    }

    int suma = *watek1_suma + *watek2_suma;
    printf("Suma calkowita tabeli: %d\n", suma);

    wyswietl_tablice();

    free(watek1_suma);
    free(watek2_suma);

    return 0;
}

void wyswietl_tablice()
{
    for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
    {
        for (int j = 0; j < sizeof(tab[0]) / sizeof(int); j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void *oblicz_sume_wiersza(void *numerWiersza)
{
    long i = (long)numerWiersza;
    int *sum = malloc(sizeof(int));

    if (sum == NULL)
    {
        perror("Nie udalo sie alokowac pamieci.");
        exit(EXIT_FAILURE);
    }

    *sum = 0;

    for (int j = 0; j < COL; j++)
    {
        *sum += tab[i][j];
    }

    return sum;
}
