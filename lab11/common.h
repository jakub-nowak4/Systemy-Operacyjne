#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

#define MAX_MSG_SIZE 256

extern int msgqid;

struct msgbuf_klient
{
    long mtype;
    pid_t klient_pid;
    char mtext[MAX_MSG_SIZE];
};

struct msgbuf_serwer
{
    long mtype;
    char mtext[MAX_MSG_SIZE];
};

extern long MSG_KLIENT_SERWER;

void utworz_kolejke();
void wyslij_msg(void *msg, size_t size);
void odbierz_msg(void *msg, size_t size, long mtype);
void usun_kolejke();







#endif