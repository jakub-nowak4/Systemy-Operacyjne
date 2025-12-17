#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

int semafor_id;
int shmid;

void wygenreuj_klucz(key_t *klucz, int arg)
{

    *klucz = ftok(".", arg);
    if (*klucz == -1)
    {
        perror("Nie udalo sie utworzyc klucza");
        exit(EXIT_FAILURE);
    }
}

void init_semafor(void)
{
    if (semctl(semafor_id, 0, SETVAL, 1) == -1)
    {
        perror("Nie udalo sie ustawic wartosci poczatkowej semafora");
        exit(EXIT_FAILURE);
    }

    if (semctl(semafor_id, 1, SETVAL, 0) == -1)
    {
        perror("Nie udalo sie ustawic wartosci poczatkowej semafora");
        exit(EXIT_FAILURE);
    }

    if (semctl(semafor_id, 2, SETVAL, 0) == -1)
    {
        perror("Nie udalo sie ustawic wartosci poczatkowej semafora");
        exit(EXIT_FAILURE);
    }
}

void utworz_semafor(key_t klucz_sem)
{
    semafor_id = semget(klucz_sem, 3, IPC_CREAT | IPC_EXCL | 0600);
    if (semafor_id == -1)
    {
        if (errno == EEXIST)
        {
            semafor_id = semget(klucz_sem, 3, 0600);
            if (semafor_id == -1)
            {
                perror("Nie udalo sie przylaczyc do zbioru semaforow");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            perror("Nie udalo sie utworzyc zbioru semaforow");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        init_semafor();
    }
}

int odczytaj_wartosc_semafora(void)
{
    int wartosc = semctl(semafor_id, 2, GETVAL);
    if (wartosc == -1)
    {
        perror("Nie udalo sie odczytac wartosc semafora");
        exit(EXIT_FAILURE);
    }

    return wartosc;
}

void semafor_p(int semNum)
{
    struct sembuf buffor;
    buffor.sem_num = semNum;
    buffor.sem_op = -1;
    buffor.sem_flg = 0;

    if (semop(semafor_id, &buffor, 1) == -1)
    {
        perror("Nie udalo sie wykonac operacji semaforowej P");
        exit(EXIT_FAILURE);
    }
}

void semafor_v(int semNum)
{
    struct sembuf buffor;
    buffor.sem_num = semNum;
    buffor.sem_op = 1;
    buffor.sem_flg = 0;

    if (semop(semafor_id, &buffor, 1) == -1)
    {
        perror("Nie udalo sie wykonac operacji semaforowej V");
        exit(EXIT_FAILURE);
    }
}

void usun_semafor(void)
{
    if (semctl(semafor_id, 0, IPC_RMID) == -1)
    {
        perror("Nie udalo sie usuanc zbioru semaforow");
        exit(EXIT_FAILURE);
    }
}

void utworz_shm(key_t klucz_pam)
{
    shmid = shmget(klucz_pam, sizeof(char), IPC_CREAT | IPC_EXCL | 0600);
    if (shmid == -1)
    {
        if (errno == EEXIST)
        {
            shmid = shmget(klucz_pam, sizeof(char), 0600);
            if (shmid == -1)
            {
                perror("Nie udalo sie przylaczyc pamieci dzielonej");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            perror("Nie udalo sie utworzyc pamieci dzielonej");
            exit(EXIT_FAILURE);
        }
    }
}

void przylacz_pamiec(char **arg)
{
    *arg= (char *)shmat(shmid,NULL,0);
    if(*arg ==(char *)-1)
    {
        perror("Nie udalo sie przylaczc segmentu pamieci dzielonej do przestrzeni adresowej");
        exit(EXIT_FAILURE);
    }
}

void usun_shm(void)
{
    if(shmctl(shmid,IPC_RMID,NULL) == -1)
    {
        perror("Nie udalo sie usunac pamiec wspoldzielonej");
        exit(EXIT_FAILURE);
    }
}

#endif