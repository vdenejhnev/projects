#include <stdio.h>
#include <stdlib.h>

#define BLOCK 4

struct list {
    char* data;
    struct list* next;
    struct list* previous;
};
//1) ������� �������� ���������������� ������.
struct list* init();
//������� ������ ������
char* input_string();
//2) ������� �������� ������.
void clr(struct list*);
//3) ������� ������ ������ �� �����.
void output(struct list**);
//4) ������� �������� �������� �� ��������� ������
void del(struct list**);
//5) ������� ������� �������� ����� �������� � �������� �������
void add(struct list**);

int main() {
    struct list* L;
    int mode;
    void (*operations_list[3]) (struct list**) = {output, del, add};  // ������ ���������� �� �������
    if ((L = init()) && !feof(stdin)) {  // ����

           output(&L);

        printf(">> 1 - displaying the list on the screen\
           \n>> 2 - deleting a list item\
           \n>> 3 - adding an item to a list\
           \n>> 0 - exiting the program\n");

        while (scanf("%d", &mode) == 1 && !feof(stdin) && mode > 0 && mode < 4)
            operations_list[mode - 1](&L);  // ����� ������ ������� ������������ �� ���������� ������
    }
    clr(L);  // ��������
}

//1) ������� �������� ���������������� ������.
struct list* init() {
    struct list* q = NULL;
    struct list* L = q;
    int n, i, c;
    printf(">> input the number of list items:\n");
    if (scanf("%d", &n) == 1 && !feof(stdin) && n >= 0) {  // ������ ���������� ��������� ������
        while ((c = getchar()) != '\n' && c != EOF);  // ���� ������� �� ������ ����� ������ ������ ������, ������� ����� ��������� ������
        printf(">> input the list items (string):\n");

        if (n) {
            q = L = malloc(sizeof(struct list));  // �������� ������ �� ������ ��������
            L->data = input_string();
            L->previous = L->next = NULL;
        }
        for (i = 1; i < n; ++i) {
            L->next = malloc(sizeof(struct list));  // ���������� �������� i
            L->next->previous = L;
            L = L->next;
            L->data = input_string();  // ������ �������� ������
            L->next = NULL;
        }
    } else {
        printf(">> incorrect\n");
    }
    if (feof(stdin))
        printf(">> reading past the end of the file\n");
    return q;
}

//������� ������ ������
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

//2) ������� �������� ������.
void clr(struct list* q) {
    while (q) {
        struct list* p = q;
        q = q->next;
        free(p->data);  // �������� ������
        free(p);  // �������� ��������
    }
    free(q);
}

//3) ������� ������ ������ �� �����.
void output(struct list** L) {
    struct list* q = *L;
    printf(">> LIST:\n");
    if (!q)   //��������� ������ �� �������
        printf(">> empty\n");  // ���� ����, �� ������� �����. ��������
    else {

    printf(">> direct order:\n");
    while (q->next) {
        printf(">> \"%s\"\n", q->data);  // ����� �������� �������� ������
        q = q->next;
    }
    printf(">> \"%s\"\n", q->data);

    printf(">> reverse order:\n");
    while (q) {
        printf(">> \"%s\"\n", q->data);  // ����� �������� �������� ������
        q = q->previous;
    }
    }

}

//4) ������� �������� �������� �� ��������� ������
void del(struct list** L) {
    struct list* q = *L;
    int n;
    printf(">> input the number of the item you want to delete:\n");
    if (scanf("%d", &n) == 1 && n > 0) {  // ������ ������ ���������� ��������
        int i;
        for (i = 1; i < n && q; ++i)
            q = q->next;  // ������� �� �������� � ������� n
        if (q) {
            if (q->next)
                q->next->previous = q->previous;  // ������������ ��������� �������� ���������
            if (q->previous)
                q->previous->next = q->next;
            if (q == *L)
                *L = q->next;
            free(q->data);  // ������� ������ ���������� ��������
            free(q);
            printf(">> item removed\n");
        } else {
            printf(">> not found\n");
        }
    } else {
        printf(">> incorrect\n");
    }
}

//5) ������� ������� �������� ����� �������� � �������� �������
void add(struct list** L) {
    struct list* q = *L;
    int n;
    printf(">> input the item number:\n");
    if (scanf("%d", &n) == 1 && n > 0) {  // ������ ������ � �������� �� ������������
        int i;
        for (i = 1; i < n && q; ++i)
            q = q->next;  // ����� �������� � ������� n
        if (q) {
            struct list* p = malloc(sizeof(struct list));  // ��������� ������ ��� ����� ������� ������
            int c;
            printf(">> input string:\n");
            while ((c = getchar()) != '\n' && c != EOF);
            p->data = input_string();
            p->next = q->next;
            p->previous = q;  // ������������� ������ �������� ������
            if (q->next)
                q->next->previous = p;  // ��������� ���������� �� �������� ���������
            q->next = p;
            printf(">> item added\n");
        } else {
            printf(">> not found\n");
        }
    } else {
        printf(">> incorrect\n");
    }
}


