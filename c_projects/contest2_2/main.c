#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

pid_t pid, pid1, pid2;
int status = -1;
int N;

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        pid = fork();
        if (pid < 0) {
            return -1;
        } else if (pid == 0){
            printf("Created %d\n", getpid());

            if (i == N-1) {
                printf("Stoped %d\n", getpid());
                exit(0);
            } else {
                wait(&status);
            }



        }

        printf("Stoped %d\n", );
        exit(0);



       // pid = wait(&status);



        //printf("Closed %d\n", wait(&status));

    }

/*
    if ((pid1 = fork()) < 0) {
        return -1;
    } else if(!pid1) {
        printf("Created %d\n", getpid());
        if((pid2 = fork()) < 0) {
            return -1;
        } else if (!pid2) {
            printf("Created %d\n", getpid());
            printf("3 ");
            exit(0);
        }
        printf("Closed %d\n", wait(&status));
        printf("2 ");
        exit(0);
    }

    printf("Closed %d\n", wait(NULL));
    printf("1\n");*/
    //printf("%d", N);
   // wait(NULL);

    exit(0);
    return 0;
}
