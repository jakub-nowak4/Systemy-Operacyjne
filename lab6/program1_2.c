#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void rysuj_drzewo(pid_t rodzic);

int main()
{
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
            printf("Proces potomny PID: %d | PPID: %d | UID: %d | GID: %d\n", getpid(), getppid(), getuid(), getgid());
            fflush(stdout);
            break;
        }
    }

    if (getpid() == parent_pid)
    {
        rysuj_drzewo(parent_pid);

        while (wait(NULL) > 0)
        {
        }
    }
    else
    {
        sleep(10);
    }

    return 0;
}

void rysuj_drzewo(pid_t rodzic)
{
    char command[100];
    sprintf(command, "pstree -p -c %d", rodzic);
    system(command);
}