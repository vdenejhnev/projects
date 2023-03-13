#include <stdio.h>
#include <stdlib.h>

#define BLOCK 4

struct list {
    char* data;
    struct list* next;
    struct list* previous;
};
//1) Функция создания двунаправленного списка.
struct list* init();
//функция чтения строки
char* input_string();
//2) Функция удаления списка.
void clr(struct list*);
//3) Функция вывода списка на экран.
void output(struct list**);
//4) Функция удаления элемента по заданному номеру
void del(struct list**);
//5) Функция вставки элемента после элемента с заданным номером
void add(struct list**);

int main() {
    struct list* L;
    int mode;
    void (*operations_list[3]) (struct list**) = {output, del, add};  // массив указателей на функции
    if ((L = init()) && !feof(stdin)) {  // меню

           output(&L);

        printf(">> 1 - displaying the list on the screen\
           \n>> 2 - deleting a list item\
           \n>> 3 - adding an item to a list\
           \n>> 0 - exiting the program\n");

        while (scanf("%d", &mode) == 1 && !feof(stdin) && mode > 0 && mode < 4)
            operations_list[mode - 1](&L);  // вызов нужной функции взависимости от выбранного режима
    }
    clr(L);  // очищение
}

//1) Функция создания двунаправленного списка.
struct list* init() {
    struct list* q = NULL;
    struct list* L = q;
    int n, i, c;
    printf(">> input the number of list items:\n");
    if (scanf("%d", &n) == 1 && !feof(stdin) && n >= 0) {  // чтение колчиества элементов списка
        while ((c = getchar()) != '\n' && c != EOF);  // ищем переход на строку чтобы начать чтение строки, которая будет элементом списка
        printf(">> input the list items (string):\n");

        if (n) {
            q = L = malloc(sizeof(struct list));  // создание списка из одного элемента
            L->data = input_string();
            L->previous = L->next = NULL;
        }
        for (i = 1; i < n; ++i) {
            L->next = malloc(sizeof(struct list));  // добавление элемента i
            L->next->previous = L;
            L = L->next;
            L->data = input_string();  // чтение элемента списка
            L->next = NULL;
        }
    } else {
        printf(">> incorrect\n");
    }
    if (feof(stdin))
        printf(">> reading past the end of the file\n");
    return q;
}

//функция чтения строки
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

//2) Функция удаления списка.
void clr(struct list* q) {
    while (q) {
        struct list* p = q;
        q = q->next;
        free(p->data);  // очищение строки
        free(p);  // очищение элемента
    }
    free(q);
}

//3) Функция вывода списка на экран.
void output(struct list** L) {
    struct list* q = *L;
    printf(">> LIST:\n");
    if (!q)   //проверяем список на пустоту
        printf(">> empty\n");  // если пуст, то выводим соотв. значение
    else {

    printf(">> direct order:\n");
    while (q->next) {
        printf(">> \"%s\"\n", q->data);  // вывод текущего элемента списка
        q = q->next;
    }
    printf(">> \"%s\"\n", q->data);

    printf(">> reverse order:\n");
    while (q) {
        printf(">> \"%s\"\n", q->data);  // вывод текущего элемента списка
        q = q->previous;
    }
    }

}

//4) Функция удаления элемента по заданному номеру
void del(struct list** L) {
    struct list* q = *L;
    int n;
    printf(">> input the number of the item you want to delete:\n");
    if (scanf("%d", &n) == 1 && n > 0) {  // чтение номера удаляемого элемента
        int i;
        for (i = 1; i < n && q; ++i)
            q = q->next;  // доходим до элемента с номером n
        if (q) {
            if (q->next)
                q->next->previous = q->previous;  // переделываем указатели соседних элементов
            if (q->previous)
                q->previous->next = q->next;
            if (q == *L)
                *L = q->next;
            free(q->data);  // очищаем память удаляемого элемента
            free(q);
            printf(">> item removed\n");
        } else {
            printf(">> not found\n");
        }
    } else {
        printf(">> incorrect\n");
    }
}

//5) Функция вставки элемента после элемента с заданным номером
void add(struct list** L) {
    struct list* q = *L;
    int n;
    printf(">> input the item number:\n");
    if (scanf("%d", &n) == 1 && n > 0) {  // чтение номера и проверка на корректность
        int i;
        for (i = 1; i < n && q; ++i)
            q = q->next;  // поиск элемента с номером n
        if (q) {
            struct list* p = malloc(sizeof(struct list));  // выделение помять под новый элемент списка
            int c;
            printf(">> input string:\n");
            while ((c = getchar()) != '\n' && c != EOF);
            p->data = input_string();
            p->next = q->next;
            p->previous = q;  // инициализация нового элемента списка
            if (q->next)
                q->next->previous = p;  // изменение указателей на соседних элементах
            q->next = p;
            printf(">> item added\n");
        } else {
            printf(">> not found\n");
        }
    } else {
        printf(">> incorrect\n");
    }
}


