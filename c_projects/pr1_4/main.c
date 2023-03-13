#include <stdio.h>
#include <stdlib.h>

/*int a, b, c, *a_p, *b_p;
//void l;


long int *arr1 = NULL, curr_num;
int count_arr = 0;*/

typedef struct Node {
    int val;
    struct Node * next;
} Node;

Node *head = NULL;

void push (int value, Node **head) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->val = value;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(Node **head) {
    Node * prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }

    prev = (*head);
    val = prev->val;
    (*head) = (*head)->next;
    free(prev);
    return val;
}


Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}


Node* getLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

/*

struct Node
{
    struct Node *prev, *next;
    char *elem;
};

struct List
{
    struct Node *first, *last;
};
*/
/*
typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}


int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}
*/
int main()
{
    push(1, &head);
    push(2, &head);
    push(3, &head);
    push(4, &head);
    push(5, &head);
    printf("%d", pop(&head));
    printf("%d", pop(&head));
    printf("%d", pop(&head));
    printf("%d", pop(&head));
    printf("%d", pop(&head));
  /*  a = 5;
    b = 2;
    c = 6;
    a_p = &a;
    b_p = &b;
    a = *a_p;
    b = *b_p;
    printf("%p %p %d %d\n", a_p, b_p, a, b);
    a_p++;
    b_p++;
    printf("%p %p %d %d\n", a_p, b_p, *a_p, *b_p);
    printf("%d\n", l);*/
  /*  arr1_p = &arr1[0];
    printf("%p\n", arr1);
    printf("%p\n", arr1_p);
    printf("%p\n", arr1_p+1);
    printf("%p\n", &arr1[1]);

    while (*arr1_p) {
        printf("%d", arr1_p);
        arr1_p++;
    }*/
    //printf("%d", sizeof(arr1));

  /*  arr1 = (int *)malloc(sizeof(long int) * 0);
    while (scanf("%ld", &curr_num) != EOF) {
        count_arr++;
        arr1 =  (int *)realloc(arr1, sizeof(long int) * count_arr);
        arr1[count_arr - 1] = curr_num;
        printf("%d \n", sizeof(*arr1));
    }

    for (int item = 0; item < count_arr; item++) {
        printf("%d \n", arr1[item]);
    }

    free(arr1);*/
 /*
    arr1 = malloc(sizeof(int) * 2);

    *arr1 = 2;
     *(arr1+1) = 4;
     *(arr1+2) = 8;

    printf("%d %d %d\n", sizeof(arr1), arr1[0], arr1[1]);

    arr1 = realloc(arr1, sizeof(int)* 4);
    *(arr1+2) = 8;



    printf("%d %d %d\n", sizeof(arr1), arr1[1], arr1[2]);
    free(arr1);*/

    return 0;
}
