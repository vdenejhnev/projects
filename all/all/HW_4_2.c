#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>

void substring(char* file_name, char* str);
void del(int fd, char* str);

int main(int argc, char** argv) {
    if (argc == 3)  // проверка на количество параметров
        substring(argv[1], argv[2]);  // функция вдаление всех вхождений строки в файл
    return 0;
}

void substring(char* file_name, char* str) {
    int fd = open(file_name, O_RDWR, 0);  // открываем на чтение и запись
    if (fd + 1) {  //проверяем существует ли такой файл
        del(fd, str);  // удаление
        close(fd);
    } else {
        fprintf(stderr, "incorrect file name.\n");
    }
}

void del(int fd, char* str) {
    int pos = 0, sizestr = strlen(str);  // pos - позиция в файле
    char *fds = malloc(sizestr + 1);  // текущая строка в файле
    lseek(fd, 0, SEEK_SET);
    while (read(fd, fds, sizestr) == sizestr) {  // пока читается строка полностью
        fds[sizestr] = '\0';  // добавляем конец файла
        if (!strcmp(fds, str)) {  // проверяем на равенство строк
            int sizefile = lseek(fd, 0, SEEK_END), p = pos;  // если равны, то удаляем строку
            while (p + sizestr < sizefile) {  // скрываем удаляемую строку правым куском
                char c;
                lseek(fd, p + sizestr, SEEK_SET);
                read(fd, &c, 1);  // достаем символ из правого куска
                lseek(fd, p, SEEK_SET);
                write(fd, &c, 1);  // передвигаем его влево на размер поданой строки
                p++;
            }
            ftruncate(fd, p);  // обрезаем файл до нужного размера
        } else {
            pos++;
        }
        lseek(fd, pos, SEEK_SET);  // перемещаемся на след. символ
    }
    free(fds);
}

