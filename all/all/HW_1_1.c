#include <stdio.h>
#include <stdlib.h>

#define BLOCK 4

char* input_string();  // функция ввода

int main() {
    char* s = NULL;
    s = input_string();  // чтение строки
    if (s) {
        printf("%s\n", s);  // вывод строки
        free(s);
    } else {
        printf("BIG STRING\n");
    }
}

char* input_string() {
    char* s = malloc(BLOCK * sizeof(char)), c;  // выеделние первого блока
    *s = '\0';
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n') {  // чтение и проверка символа
        s[i++] = c;
        if ((i + 1) % BLOCK == 0)  // если строка не помещается под текущий размер
            s = realloc(s, ((i + 1) + BLOCK) * sizeof(char));  // выделение еще одного блока памяти
    }
    s[i] = '\0';  // ставим символ конца строки
    return s;
}
