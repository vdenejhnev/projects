#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>

void substring(char* file_name, char* str);
void del(int fd, char* str);

int main(int argc, char** argv) {
    if (argc == 3)
        substring(argv[1], argv[2]);
    return 0;
}

void substring(char* file_name, char* str) {
    int fd = open("file.txt", O_RDWR, 0);
    if (fd != -1) {
        del(fd, str);
        close(fd);
    } else {
        fprintf(stderr, "incorrect file name.\n");
    }
}

void del(int fd, char* str) {
    int pos = 0, sizestr = strlen(str);
    char *fds = malloc(sizestr + 1);
    lseek(fd, 0, SEEK_SET);
    while (read(fd, fds, sizestr) == sizestr) {
        fds[sizestr] = '\0';
        if (!strcmp(fds, str)) {
            int sizefile = lseek(fd, 0, SEEK_END), p = pos;
            while (p + sizestr < sizefile) {
                char c;
                lseek(fd, p + sizestr, SEEK_SET);
                read(fd, &c, 1);
                lseek(fd, p, SEEK_SET);
                write(fd, &c, 1);
                p++;
            }
            ftruncate(fd, p);
        } else {
            pos++;
        }
        lseek(fd, pos, SEEK_SET);
    }
    free(fds);
}

