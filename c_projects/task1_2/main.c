#include <stdio.h>
#include <string.h>

#define TYPE int
#define STRING_TYPE "int"

int read(char* s, TYPE* n) {
    int q = 1;
    if (!strcmp("char", STRING_TYPE) ||
        !strcmp("signed char", STRING_TYPE))
        sscanf(s, "%hhi", n);
    else if (!strcmp("unsigned char", STRING_TYPE))
        sscanf(s, "%hhu", n);
    else if (!strcmp("short", STRING_TYPE) ||
             !strcmp("short int", STRING_TYPE) ||
             !strcmp("signed short", STRING_TYPE) ||
             !strcmp("signed short int", STRING_TYPE))
        sscanf(s, "%hi", n);
    else if (!strcmp("unsigned short", STRING_TYPE) ||
             !strcmp("unsigned short int", STRING_TYPE))
        sscanf(s, "%hu", n);
    else if (!strcmp("int", STRING_TYPE) ||
             !strcmp("signed", STRING_TYPE) ||
             !strcmp("signed int", STRING_TYPE))
        sscanf(s, "%d", n);
    else if (!strcmp("unsigned", STRING_TYPE) ||
             !strcmp("unsigned int", STRING_TYPE))
        sscanf(s, "%u", n);
    else if (!strcmp("long", STRING_TYPE) ||
             !strcmp("long int", STRING_TYPE) ||
             !strcmp("signed long", STRING_TYPE) ||
             !strcmp("signed long int", STRING_TYPE))
        sscanf(s, "%ld", n);
    else if (!strcmp("unsigned long", STRING_TYPE) ||
             !strcmp("unsigned long int", STRING_TYPE))
        sscanf(s, "%lu", n);
    else if (!strcmp("long long", STRING_TYPE) ||
             !strcmp("long long int", STRING_TYPE) ||
             !strcmp("signed long long", STRING_TYPE) ||
             !strcmp("signed long long int", STRING_TYPE))
        sscanf(s, "%lld", n);
    else if (!strcmp("unsigned long long", STRING_TYPE) ||
             !strcmp("unsigned long long int", STRING_TYPE))
        sscanf(s, "%llu", n);
    else return 0;
    return 1;
}
void conversion(TYPE n) {
    for (int i = sizeof(TYPE) * 8 - 1; i >= 0; --i)
        printf("%d", n >> i & 1);
    printf("\n");
}



int main(int argc, char** argv) {
    TYPE n;
    if (argc > 1) {
        if (read(argv[1], &n))
            conversion(n);
        else
            fprintf(stderr, "incorrect type in macros\n");
    } else {
        printf("no argument\n");
    }
}

