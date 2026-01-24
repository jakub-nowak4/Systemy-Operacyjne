#include "common.h"

int msgqid;
long MSG_KLIENT_SERWER = 1;

void utworz_kolejke()
{
    key_t key = ftok(".", 22);
    if(key == -1)
    {
        perror("Blad ftok()");
        exit(EXIT_FAILURE);
    }

    msgqid = msgget(key, 0600 | IPC_CREAT | IPC_EXCL);
    if(msgqid == -1)
    {
        if(errno == EEXIST)
        {
            msgqid = msgget(key, 0600);
            if(msgqid == -1)
            {
                perror("Blad msgget()");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            perror("Blad msgget()");
            exit(EXIT_FAILURE);
        }
    }

}

void wyslij_msg(void *msg, size_t size)
{
    if(msgsnd(msgqid, msg, size, 0) == -1)
    {
        perror("Blad msgsnd()");
        exit(EXIT_FAILURE); 
    }
}

void odbierz_msg(void *msg, size_t size, long mtype)
{
    if(msgrcv(msgqid, msg, size, mtype, 0) == -1)
    {
        perror("Blad msgrcv()");
        exit(EXIT_FAILURE);
    }
}

void usun_kolejke()
{
    if(msgctl(msgqid, IPC_RMID, NULL) == -1)
    {
        perror("Blad msgctl()");
        exit(EXIT_FAILURE);
    }
}