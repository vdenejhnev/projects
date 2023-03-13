#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#define MAXLEN 256

key_t key1;
struct sembuf S;
char *shmaddr, str[MAXLEN], str_count[MAXLEN], char_proc;
int semid, shmid, i, count;

int main(int argc, char** argv) {
    if (argc = 3) {
        sscanf(argv[2], "%s", &char_proc);

        key1 = ftok(argv[1], char_proc);

        semid = semget(key1, 1, 0666 | IPC_CREAT);
        shmid = shmget(key1, MAXLEN, 0666 | IPC_CREAT);
        shmaddr = shmat(shmid, 0, 0);
        semctl(semid, 0, SETVAL, (int) 0);
        S.sem_num = 0;
        S.sem_flg = 0;
        do {
            S.sem_op = -1;
            semop(semid, &S, 1);
            strcpy(str, shmaddr);

            count = 0;

            for (i = 0; i < strlen(str); i++) {
                if((int)str[i] == 32) {
                    count++;
                }
            }

            if (str[0] == 'Q') {
                shmdt(shmaddr);
            } else {
                sprintf(str_count, "Count spaces: %d", count);
                strcpy(shmaddr + MAXLEN * 2, str_count);
            }

            S.sem_op = -1;
            semop(semid, &S, 1);
            printf("%d\n", count);
        } while (str[0] != 'Q');

        return 0;
    } else {
        exit(-1);
    }
}

