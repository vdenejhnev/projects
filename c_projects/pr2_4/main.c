#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int sec;
long int start_time, curr_time;

void sigHndlr1(int s) {
    printf("%d \n", getpid());

    if (fork() == 0) {
        printf("%d \n", getpid());
        exit(0);
    } else {
        wait(NULL);
        signal(SIGTSTP, sigHndlr1);
    }
}

void sigHndlr3(int s) {
    signal(SIGUSR1, sigHndlr3);

    if (s == 0) {
        start_time = time(NULL);
    }

    curr_time = time(NULL);
    if (difftime(curr_time, start_time) >= 3) {
        exit(0);
    }

    if (fork() == 0) {
        printf("S");
        fflush(stdout);
        exit(0);
    } else {
        wait(NULL);
        printf("F");
        fflush(stdout);
        kill(getpid(), SIGUSR1);
    }
}

void sigHndlr2(int s) {
    signal(SIGTSTP, SIG_IGN);
    sigHndlr3(0);
}

int main() {
    signal(SIGTSTP, sigHndlr1);
    signal(SIGALRM, sigHndlr2);
    alarm(5);
    while(1);
    return 0;
}
