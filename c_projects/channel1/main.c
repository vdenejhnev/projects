#include <stdio.h>  // Для printf, fflush
#include <unistd.h>  // Для sleep
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>


int low, high;
int sig_count = 0;
int fd[2];
int fd_out;
char str;
int num;

void findSimple(int low_num, int high_low) {
    for (int curr_num = low_num; curr_num <= high_low; curr_num++) {
        num = 0;

        if (curr_num == 1 || curr_num == 3){
            num = curr_num;
        } else if (curr_num == -1 || curr_num == -3){
            num = curr_num;
        } else {
            if (((curr_num * curr_num) % 24) == 1) {
                num = curr_num;
                printf("%d\n", num);
            }
        }
    }
}


void sigHndlr1(int s) {
    findSimple(low, high);
    //printf("%d\n", ++sig_count);
    sig_count++;
    if(sig_count == 4) {
        exit(0);
    } else {
        printf("%d\n", num);
        signal(SIGINT, sigHndlr1);
    }
}

void sigHndlr2(int s) {
    exit(0);
}


int main ()
{
    printf("Print low number: ");
    scanf("%d", &low);
    printf("Print high number: ");
    scanf("%d", &high);
    printf("%d\n", getpid());

    if (pipe(fd) == 0) {
        fd_out = open("fd_out", O_CREAT|O_RDWR|O_APPEND|0666);


        //dup2(fd_out, 1);
        //close(fd_out);

       // while (read(fd[1], &str, 1)) {

           // write(fd_out, &str, 1);
       //}
        //printf("12345");
       /* fflush(stdout);
        while (read(fd[0], str, 5)) {
            printf("%s", str);
        }*/



        signal(SIGINT, sigHndlr1);
        signal(SIGTERM, sigHndlr2);
        if (fork() == 0) {
            findSimple(low, high);
        }

        while(1);
        return 0;
    } else {
        perror("Error created pipe");
        return -1;
    }
}
