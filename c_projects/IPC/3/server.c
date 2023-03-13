#include <stdio.h>
#include <stdlib.h>
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
int semid, shmid;

int main(int argc, char** argv) {

    if (argc = 3) {
        sscanf(argv[2], "%s", &char_proc);

        key1 = ftok(argv[1], char_proc);

        semid = semget(key1, 1, 0666 | IPC_CREAT);
        shmid = shmget(key1, MAXLEN, 0666 | IPC_CREAT);
        shmaddr = shmat(shmid, 0, 0);
        semctl(semid, 0, SETVAL, (int) 0);
        S.sem_flg = 0;
        S.sem_num = 0;
        while (str[0] != 'Q') {
            printf("Enter string:");

            if (fgets(str, MAXLEN, stdin) == NULL) {
                strcpy(str, "Q");
            }

            strcpy(shmaddr, str);

            S.sem_op = 4;
            semop(semid, &S, 1);
            S.sem_op = 0;
            semop(semid, &S, 1);

            strcpy(str, shmaddr + MAXLEN);
            printf("%s\n", str);
            strcpy(str, shmaddr + MAXLEN * 2);
            printf("%s\n", str);

           /* S.sem_op = 1;
            semop(semid, &S, 1);
            S.sem_op = 0;
            semop(semid, &S, 1);

            strcpy(str, shmaddr);
            printf("%s\n", str);*/

        }


        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID, (int) 0);

        return 0;
    } else {
        exit(1);
    }
}

/*key_t key1;
struct shmid_ds * ds1;
char * file_name, str[256];
int char_proc = 111, * shm_adr, * ds_adr, d_queue;
int shmid;

struct {
    long mtype;
    char msg[256];
} Message;

int main(int argc, char** argv)
{
    if (argc = 3) {
        sscanf(argv[2], "%d", &char_proc);

        key1 = ftok(argv[1], char_proc);

        d_queue = msgget(key1, 0666 | IPC_CREAT | IPC_EXCL);
        for(;;) {
            msgrcv(d_queue, (struct msgbuf*)(&Message), 256, 2, 0);
            printf("%s", Message.msg);
        }
        return 0;
    } else {
        exit(1);
    }


}*/
