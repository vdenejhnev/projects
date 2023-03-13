#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int n = 0;

void handler1(int sig) {
    n -= 4;
    printf("\n%d 'SIGINT' %d\n", sig, n);
}

void handler2(int sig) {
    n += 3;
    printf("\n%d 'SIGTSTP' %d\n", sig, n);
}

int main(int argc, char** argv) {
    argv[1] = 10;
    n = argv[1];

    signal(SIGINT, handler1);
	signal(SIGTSTP, handler2);

	while (n >= 0) {
        pause();
	}

	return 0;
}
