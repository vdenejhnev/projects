#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int low, high, i, num, sig_count = 0;

void sigHndlr1(int s) {
    sig_count++;
    if (sig_count == 4) {
        exit(0);
    }

    printf("%d", num);
    fflush(stdout);
}

void sigHndlr2(int s) {
    exit(0);
}


int main()
{
    scanf("%d", &low);
    scanf("%d", &high);



    if (fork() == 0) {
        signal(SIGINT, sigHndlr1);
        signal(SIGTERM, sigHndlr2);
        printf("%d", getpid());
        num = 0;
        i = low;
        while (i <= high) {
            if ((i == -1) || (i == -3) || (i == 1) || (i == 3)) {
                num = i;
                //printf("%d ", num);
                //fflush(stdout);
            } else if ((i*i) % 24 == 1) {
                num = i;
                //printf("%d ", num);
                //fflush(stdout);
            }

            i++;
        }
         pause();


        printf("%d", -1);
        fflush(stdout);
        exit(0);

    } else {
        wait(NULL);

    }


    return 0;
}
