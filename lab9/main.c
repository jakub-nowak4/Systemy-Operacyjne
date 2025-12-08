#include "semafory.h"
#include <sys/wait.h>

int main()
{
        utworz_semafor();
        ustaw_zbior_semaforow();

        char paths[][10] = {"./P1", "./P2", "./P3"};
        char names[][10] = {"P1", "P2", "P3"};

        for (int i = 0; i < 3; i++)
        {
                switch (fork())
                {
                case -1:
                        perror("fork error");
                        exit(EXIT_FAILURE);
                case 0:
                        execl(paths[i], names[i], NULL);
                        exit(EXIT_FAILURE);
                }
        }

        while (wait(NULL) > 0)
        {
        }

        usun_semafor();
        return 0;
}
