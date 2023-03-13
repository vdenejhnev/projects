#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


pid_t pid;
int n, status, fd[2];
char s, *str;

int main()
{
    pipe(fd);

    if (fork() == 0) {
       printf("%d %d\n", n, getpid());
    } else {
        wait(&status);
        scanf("%d", &n);
    }

    for (int i = 0; i < n; i++) {
        scanf("%s", &s);
        str = (char *)realloc(str, sizeof(char)* (i + 1));
        str[i] = s;
        write(fd[1], str, i+1);

        if (fork() == 0) {
            lseek(fd[0], 0, SEEK_SET);
            read(fd[0], str, i+1);
            printf("%d %s\n", i+1, str);
            exit(0);
        } else {
            wait(&status);
        }
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
