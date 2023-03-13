#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        DIR *directory_open;
        FILE *file_open
        if (opendir(argc[1])))
    } else {
        fprintf(stderr, "Error: File not specified");
    }

    return 0;
}
/*int main() {
    pid_t pid1, pid2;
    int status = -1;

    if ((pid1 = fork()) < 0) {
        return -1;
    } else if (!pid1) {
        if ((pid2 = fork()) < 0) {
            return -1;
        } else if (!pid2) {
            printf("3 ");
            exit(0);
        }

        wait(&status);
        printf("2 ");
        exit(0);
    }

    wait(NULL);
    printf("1\n");
    exit(0);
    return 0;

}*/


/*int main(int argc, char **argv)
{
    int i;
    for (i = 1; i<argc; i++) {
        int status;
        pid_t pid;

        if (fork() > 0) {
            pid = wait(&status);
            printf("process %d finished\n", pid);
            continue;
        }

        execlp(argv[i], argv[i], (char*)0);
        return -1;
    }
    return 0;
}*/
