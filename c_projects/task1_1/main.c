#include <stdio.h>
#include <stdlib.h>

#define MEMORY_BLOCK 4

char* input_string() {
    char* str = malloc(MEMORY_BLOCK * sizeof(char)), c;
    *str = '\0';
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        str[i++] = c;
        if ((i + 1) % MEMORY_BLOCK == 0)
            str = realloc(str, ((i + 1) + MEMORY_BLOCK) * sizeof(char));
    }
    str[i] = '\0';
    return str;
}

int main() {
    char* str = NULL;
    str = input_string();
    if (str) {
        printf("%s\n", str);
        free(str);
    } else {
        printf("BIG STRING\n");
    }
}


