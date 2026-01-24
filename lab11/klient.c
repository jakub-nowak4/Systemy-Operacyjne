#include "common.h"

pthread_t watki[2];

void *func_wyslij(void *arg) {
    (void)arg;
    struct msgbuf_klient msg;
    msg.mtype = MSG_KLIENT_SERWER;
    msg.klient_pid = getpid();
    
    printf("Wpisz wiadomosc: ");
    while(fgets(msg.mtext, MAX_MSG_SIZE, stdin) != NULL) {
        size_t len = strlen(msg.mtext);
        if (len > 0 && msg.mtext[len - 1] == '\n') {
            msg.mtext[len - 1] = '\0';
        }

        struct msqid_ds buf;
        while(1) {
            if (msgctl(msgqid, IPC_STAT, &buf) == -1) {
                perror("msgctl");
                break; 
            }
            
            if (buf.__msg_cbytes + sizeof(pid_t) + strlen(msg.mtext) + 1 > buf.msg_qbytes - 512) {
                 printf("Kolejka pelna! (%ld/%ld bajtow). Czekam...\n", buf.__msg_cbytes, buf.msg_qbytes);
                 sleep(1);
                 continue;
            }
            break;
        }

        wyslij_msg(&msg, sizeof(pid_t) + strlen(msg.mtext) + 1);
        
        printf("[Klient %d] Wysłalem: %s\n", getpid(), msg.mtext);

        printf("Wpisz wiadomosc: ");
    }

    struct msgbuf_serwer koniec;
    koniec.mtype = getpid();
    strcpy(koniec.mtext, "KONIEC");
    msgsnd(msgqid, &koniec, sizeof(struct msgbuf_serwer) - sizeof(long), 0);

    return NULL;
}

void *func_odbierz(void *arg) {
    (void)arg;
    struct msgbuf_serwer msg;
    
    while(1) {
        odbierz_msg(&msg, sizeof(struct msgbuf_serwer) - sizeof(long), getpid());
        
        if (strcmp(msg.mtext, "KONIEC") == 0) {
            break;
        }

        printf("\n[Klient %d] Otrzymalem: %s\n", getpid(), msg.mtext);
        printf("Wpisz wiadomosc: ");
        fflush(stdout);
    }
    return NULL;
}

int main()
{
    utworz_kolejke();
    
    if(pthread_create(&watki[0], NULL, func_wyslij, NULL) != 0) {
        perror("pthread_create sender");
        exit(EXIT_FAILURE);
    }
    
    if(pthread_create(&watki[1], NULL, func_odbierz, NULL) != 0) {
        perror("pthread_create receiver");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(watki[0], NULL);
    pthread_join(watki[1], NULL);
    
    return 0;
}