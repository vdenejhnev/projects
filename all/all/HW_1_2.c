#include <stdio.h>
#include <string.h>

#define TYPE int
#define mkstr(TYPE) "int"

int read(char*, TYPE*);
void conversion(TYPE);

int main(int argc, char** argv) {
    TYPE n;
    if (argc > 1) {
        if (read(argv[1], &n))
            conversion(n);
        else
            fprintf(stderr, "incorrect type in macros\n");
    } else {
        printf("no argument\n");  // нет числа при вызове исполнительного файла
    }
}

int read(char* s, TYPE* n) {
    int q = 1;
    if (!strcmp("char", mkstr(TYPE)) ||
        !strcmp("signed char", mkstr(TYPE)))
        sscanf(s, "%hhi", n);
    else if (!strcmp("unsigned char", mkstr(TYPE)))
        sscanf(s, "%hhu", n);
    else if (!strcmp("short", mkstr(TYPE)) ||
             !strcmp("short int", mkstr(TYPE)) ||
             !strcmp("signed short", mkstr(TYPE)) ||
             !strcmp("signed short int", mkstr(TYPE)))
        sscanf(s, "%hi", n);
    else if (!strcmp("unsigned short", mkstr(TYPE)) ||
             !strcmp("unsigned short int", mkstr(TYPE)))
        sscanf(s, "%hu", n);
    else if (!strcmp("int", mkstr(TYPE)) ||
             !strcmp("signed", mkstr(TYPE)) ||
             !strcmp("signed int", mkstr(TYPE)))
        sscanf(s, "%d", n);
    else if (!strcmp("unsigned", mkstr(TYPE)) ||
             !strcmp("unsigned int", mkstr(TYPE)))
        sscanf(s, "%u", n);
    else if (!strcmp("long", mkstr(TYPE)) ||
             !strcmp("long int", mkstr(TYPE)) ||
             !strcmp("signed long", mkstr(TYPE)) ||
             !strcmp("signed long int", mkstr(TYPE)))
        sscanf(s, "%ld", n);
    else if (!strcmp("unsigned long", mkstr(TYPE)) ||
             !strcmp("unsigned long int", mkstr(TYPE)))
        sscanf(s, "%lu", n);
    else if (!strcmp("long long", mkstr(TYPE)) ||
             !strcmp("long long int", mkstr(TYPE)) ||
             !strcmp("signed long long", mkstr(TYPE)) ||
             !strcmp("signed long long int", mkstr(TYPE)))
        sscanf(s, "%lld", n);
    else if (!strcmp("unsigned long long", mkstr(TYPE)) ||
             !strcmp("unsigned long long int", mkstr(TYPE)))
        sscanf(s, "%llu", n);
    else return 0;
    return 1;
}
void conversion(TYPE n) {
    for (int i = sizeof(TYPE) * 8 - 1; i >= 0; --i)
        printf("%d", n >> i & 1);
    printf("\n");
}

