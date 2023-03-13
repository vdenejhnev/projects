#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int N, i;

int main()
{
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        if (i < N) {
            printf("%d ", i);
        } else {
            printf("%d\n", i);
        }

        fflush(stdout);
        if(fork() == 0) {
            if (i == N) {
                exit(0);
            }
        } else {
            wait(NULL);
            exit(0);
        }
    }
}
