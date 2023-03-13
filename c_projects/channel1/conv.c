#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

int fd_in, status = -1;

int main() {

    if (fork() == 0) {
        fd_in=open("file1", O_RDONLY, 0660);
        dup2(fd_in, 0);
        close(fd_in);
        execlp("cat", "cat", NULL);
    } else {
        wait(&status);
    }
    return 0;
}

/*int semid;
key_t key1;
char *shmaddr, str[256], str2[256];
struct sembuf sem;

int main() {
    if ((key1 = ftok("f.txt", 's')) != -1) {
        semid = semget(key1, 1, 0666|IPC_CREAT);
        semctl(semid, 0, SETVAL, (int) 0);
        sem.sem_num = 0;
        sem.sem_flg = 0;
        sem.sem_op = 3;
        semop(semid, &sem, 1);
        sleep(3);
        sem.sem_op = -3;
        semop(semid, &sem, 1);
        sem.sem_op = 0;
        semop(semid, &sem, 1);
        printf("%d", sem.sem_op);
        semctl(semid, 0, IPC_RMID, (int) 0);
        return 0;
    } else {
        perror("Key created fail");
        return -1;
    }
}
/*
int shmid;
key_t key1;
char *shmaddr, str[256], str2[256];

int main() {
    if ((key1 = ftok("f.txt", 's')) != -1) {

        shmid = shmget(key1, 256, 0666 | IPC_CREAT);
        shmaddr = shmat(shmid, 0, 0);

        if (fgets(str, 256, stdin)) {
            strcpy(shmaddr, str);
        }

        strcpy(str2, shmaddr);

        printf("%s", str2);

        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        perror("Key created fail");


        return 0;
    } else {
        perror("Key created fail");
        return -1;
    }
}*/
/*
int fd1, fd2, fd_curr[2], msd;
int status = -1;
pid_t pid1, pid2;
key_t key1;
char str[256];

struct {
    long mtype;
    char Data[256];
} Message;

int main(int argc, char**argv) {
    if (ftok("file2", 's') != -1) {
        if ((msd = msgget(key1, IPC_CREAT)) != -1) {

        } else {
            printf("%d", msd);
            gets(str);
            strcpy(Message.Data, "abcdef");
            msgsnd(msd, (struct msgbuf*)(&Message), 256, 0);
            msgrcv(msd, str, 256, 1, 0);
            msgctl(msd, IPC_RMID, NULL);
            while(1);
            perror("Message list created fail");
        }
        return 0;
    } else {
        perror("Key created fail");
        return -1;
    }

    /*
    if (argc == 6) {
        fd1 = open(argv[4], O_RDONLY| 0666);
        fd2 = open(argv[5], O_CREAT|O_RDWR| O_APPEND| 0666);

        pipe(fd_curr);
        if (fork() == 0) {
            if (fork() == 0) {

                dup2(fd1, 0);
                close(fd1);
                dup2(fd2, 1);
                close(fd2);
                execlp(argv[1], argv[1], NULL);
            } else {
                wait(&status);
                if (!WIFEXITED(status)) {
                    perror("process fail finished");
                    exit(1);
                }
            }

            if (fork() == 0) {
                execlp(argv[2], argv[2], NULL);
            } else {
                wait(&status);
                if (!WIFEXITED(status)) {
                    perror("process fail finished");
                    exit(1);
                }
            }
            exit(0);
        } else {
            wait(&status);
            if (!WIFEXITED(status)) {
                exit(1);
            }

        }

         wait(&status);

        if (fork() == 0) {
            printf("%d", fd_curr[1]);
            fflush(stdout);
            dup2(fd_curr[0], 0);
            close(fd_curr[0]);
            dup2(fd2, 1);
            close(fd2);
            execlp(argv[3], argv[3], NULL);
        } else {
            wait(&status);
            if (!WIFEXITED(status)) {
                perror("process fail finished");
                exit(1);
            }
        }

        wait(&status);
        close(fd1);
        close(fd2);
        return 0;
    } else {
        return -1;
    }*/


   /* pid1 = fork();
    if (pid1 > 0) {
        sleep(10);
    } else {
        exit(0);
    }*/


//}
