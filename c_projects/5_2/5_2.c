#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int count_signal1 = 0;
int count_signal2 = 0;

void handler2(int sig) {
    count_signal2++;
}

void handler1(int sig) {
    count_signal1++;
}

int main() {
    signal(SIGINT, handler1);
	signal(SIGTSTP, SIG_IGN);

	while (count_signal1 < 6) {
	    if (count_signal1 == 2) {
            signal(SIGTSTP, handler2);
        }
        if (count_signal1 == 4) {
            signal(SIGTSTP, SIG_IGN);
        }
        pause();
	}

	printf("\nCount of signals 'SIGTSTP':%d\n", count_signal2);
	return 0;
}
