#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

void append(char*, int);
void duplication(int, int);

int main(int argc, char** argv) {
    int N;
    sscanf(argv[2], "%d", &N);  // переделываем строку в число
    if (argc == 3)  // проверка на количество параметров
        append(argv[1], N);  // ддобавление блока
    return 0;
}

void append(char* s, int N) {
    int fd = open(s, O_RDWR | O_APPEND, 0);  // открываем файл на чтение и дозапись
    if (fd + 1) {  // проверка на существование файла
        duplication(fd, N);  // дублирование
        close(fd);
    } else {
        fprintf(stderr, "incorrect file name.\n");
    }
}

void duplication(int fd, int N) {
    int pos = 0, end = lseek(fd, 0, SEEK_END);
    char c;
    while (lseek(fd, 0, SEEK_END) < 1024 && pos < N && pos < end) {  // проверка нужно ли добавлять символ (без дублирования)
        lseek(fd, pos, SEEK_SET);
        read(fd, &c, 1);  // чтение дублируемого символа
        lseek(fd, 0, SEEK_END);
        write(fd, &c, 1);  // запись в конец файла дублируемого символа
        pos++;
    }
}
