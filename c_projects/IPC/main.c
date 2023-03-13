#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

key_t key1;
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

       // shmid = shmget(key1, 256, 0666 | IPC_CREAT);
      //  shm_adr = shmat(shmid, 0, SHM_RDONLY);
        d_queue = msgget(key1, 0666 | IPC_CREAT | IPC_EXCL);
        for(;;) {
            gets(str);
            strcpy(Message.msg, str);
            Message.mtype = 2;
            printf("%d",d_queue); // msgsnd(d_queue, (struct msgbuf*)(&Message), strlen(str) + 1, 0));

        }
        msgctl(d_queue, IPC_RMID, NULL);

        return 0;
    } else {
        exit(1);
    }


}
