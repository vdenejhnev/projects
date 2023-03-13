#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

int status;
bool curr_result;

int execlp_process(char *cmd) {
    if (fork() == 0) {
        execlp(cmd, cmd, NULL);
    } else {
        wait(&status);
        if ((WIFEXITED(status) <= 0) || (WEXITSTATUS(status) != 0)) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        return 1;
    }

    if (!execlp_process(argv[1])) {
        curr_result = execlp_process(argv[2]);
    } else {
        curr_result = true;
    }

    if (curr_result) {
        curr_result = execlp_process(argv[3]);
        return execlp_process(argv[3]);
    } else {
        curr_result = false;
    }




    return 0;
}
