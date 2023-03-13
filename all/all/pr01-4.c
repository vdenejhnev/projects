#include <string.h>
#include <stdlib.h>

struct Node* addelem(struct Node* L, char* s) {
    if (!L) {
        L = malloc(sizeof(struct Node));
        L->prev = NULL;
        L->next = NULL;
        L->elem = s;
    } else {
        struct Node * p = L;
        while (p->next)
            p = p->next;
        p->next = malloc(sizeof(struct Node));
        p->next->elem = s;
        p->next->next = NULL;
        p->next->prev = p;
    }
    return L;
}

void process(struct List *pl, const char *str) {
    struct Node *L = pl->first, *L1 = NULL, *L2 = NULL;
    while (L) {
        int cmp = strcmp(L->elem, str);
        struct Node *next = L->next;
        if (cmp > 0)
            L2 = addelem(L2, L->elem);
        if (!cmp)
            free(L->elem);
        if (cmp < 0)
            L1 = addelem(L1, L->elem);
        free(L);
        L = next;
    }
    pl->first = L1?L1:L2;

    while (L1 && L1->next)
        L1 = L1->next;
    if (L1) {
        L1->next = L2;
        if (L2)
            L2->prev = L1;
    } else {
        L1 = L2;
    }
    while (L1 && L1->next)
        L1 = L1->next;
    pl->last = L1;
}

