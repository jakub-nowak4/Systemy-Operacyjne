#include "common.h"

void sigint_handler(int sig)
{
    usun_kolejke();
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler);
    utworz_kolejke();

    printf("[SERWER PID:%d] Oczekuje na wiadomosci...\n", getpid());

    while(1)
    {
        struct msgbuf_klient msg;
        odbierz_msg(&msg, sizeof(struct msgbuf_klient) - sizeof(long), MSG_KLIENT_SERWER);

        printf("[SERWER PID:%d] Otrzymałem: %s od %d\n", getpid(), msg.mtext, msg.klient_pid);

        struct msgbuf_serwer odpowiedz;
        odpowiedz.mtype = msg.klient_pid;
        
        for(int i = 0; msg.mtext[i]; i++)
        {
            odpowiedz.mtext[i] = toupper((unsigned char)msg.mtext[i]);
        }

        odpowiedz.mtext[strlen(msg.mtext)] = '\0';

        wyslij_msg(&odpowiedz, sizeof(struct msgbuf_serwer) - sizeof(long));
        printf("[SERWER PID:%d] Wysłalem: %s dla %d\n", getpid(), odpowiedz.mtext, msg.klient_pid);
        
    }

    return 0;
}