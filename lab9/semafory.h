#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int zbior_semaforow_id;

static void ustaw_zbior_semaforow(void)
{
    for (int i = 0; i < 5; i++)
    {
        int status = semctl(zbior_semaforow_id, i, SETVAL, 0);
        sleep(1);
        if (status == -1)
        {
            printf("Nie udalo ustawic sie wartosci semafora nr %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("Poprawnie ustawiono wartosc 0 dla wszystkich semaforow w zbiorze\n");
}

static void semafor_p(int semNum)
{
    struct sembuf buffor_sem;
    buffor_sem.sem_num = semNum;
    buffor_sem.sem_op = -1;
    buffor_sem.sem_flg = SEM_UNDO;

    int status = semop(zbior_semaforow_id, &buffor_sem, 1);
    if (status == -1)
    {
        printf("Nie udało się zmniejszyć wartości semafora\n");
        exit(EXIT_FAILURE);
    }
}

static void semafor_v(int semNum)
{
    struct sembuf buffor_sem;
    buffor_sem.sem_num = semNum;
    buffor_sem.sem_op = 1;
    buffor_sem.sem_flg = SEM_UNDO;

    int status = semop(zbior_semaforow_id, &buffor_sem, 1);
    if (status == -1)
    {
        printf("Nie udało się zwiększyć wartości semafora\n");
        exit(EXIT_FAILURE);
    }
}

static void utworz_semafor(void)
{
    zbior_semaforow_id = semget(6789, 5, IPC_CREAT | 0600);
    if (zbior_semaforow_id == -1)
    {
        printf("Nie udalo sie utworzyc zbioru semaforow\n");
        exit(1);
    }
    else
    {
        printf("Zbior semaforow zostal utworzony poprawnie.\n");
        printf("Id utworzonego zbioru: %d\n", zbior_semaforow_id);
    }
};

static void usun_semafor(void)
{
    int status = semctl(zbior_semaforow_id, 0, IPC_RMID);
    if (status == -1)
    {
        printf("Wystapil blad podczas usuwania zbioru semaforow\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Poprawnie  usunieto zbior semaforow\n");
    }
}
