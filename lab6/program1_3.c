#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int status;
    pid_t parent_pid = getpid();

    printf("Proces macierzysty PID: %d | PPID: %d | UID: %d | GID: %d\n", getpid(), getppid(), getuid(), getgid());

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("Blad wywolania funkcji fork().");
            exit(EXIT_FAILURE);

        case 0:
            execl("./program1_1", "program1_1", NULL);
            perror("Blad przy wywolaniu funkcji excel()");
            exit(EXIT_FAILURE);
        }
    }

    pid_t dziecko_pid;
    while ((dziecko_pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
        {
            int kod_zakonczenia = WEXITSTATUS(status);
            printf("Proces o PID: %d zakonczyl sie kodem %d\n", dziecko_pid, kod_zakonczenia);
        }
    }

    if (errno == ECHILD)
    {
        printf("Nie ma juz zadnych procesow potomnych\n");
    }
    else
    {
        perror("Funckja wait zakonczyla sie bledem.");
    }

    return 0;
}
