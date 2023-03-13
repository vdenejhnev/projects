#include <stdio.h>
#include <stdlib.h>

#define BLOCK 4

char* input_string();  // ������� �����

int main() {
    char* s = NULL;
    s = input_string();  // ������ ������
    if (s) {
        printf("%s\n", s);  // ����� ������
        free(s);
    } else {
        printf("BIG STRING\n");
    }
}

char* input_string() {
    char* s = malloc(BLOCK * sizeof(char)), c;  // ��������� ������� �����
    *s = '\0';
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n') {  // ������ � �������� �������
        s[i++] = c;
        if ((i + 1) % BLOCK == 0)  // ���� ������ �� ���������� ��� ������� ������
            s = realloc(s, ((i + 1) + BLOCK) * sizeof(char));  // ��������� ��� ������ ����� ������
    }
    s[i] = '\0';  // ������ ������ ����� ������
    return s;
}
