#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

void append(char*, int);
void duplication(int, int);

int main(int argc, char** argv) {
    int N;
    sscanf(argv[2], "%d", &N);
    if (argc == 3)
        append(argv[1], N);
    return 0;
}

void append(char* s, int N) {
    int fd = open(s, O_RDWR | O_APPEND, 0);
    if (fd + 1) {
        duplication(fd, N);
        close(fd);
    } else {
        fprintf(stderr, "incorrect file name.\n");
    }
}

void duplication(int fd, int N) {
    int pos = 0, item = 0, end = lseek(fd, 0, SEEK_END);
    char c;
    if (end < 1024) {
        while (pos < N) {
            lseek(fd, (N * item + pos), SEEK_SET);
            read(fd, &c, 1);
            lseek(fd, 0, SEEK_END);
            write(fd, &c, 1);

            if (pos + 1 < N) {
                pos++;
            } else {
                item++;
                if (end - (N*item) > N) {
                    pos = 0;
                } else {
                    break;
                }
            }

        }
    }
}
