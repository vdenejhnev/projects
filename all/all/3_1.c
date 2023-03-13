#include <stdio.h>
#include <stdlib.h>

#define NEW_NODE malloc(sizeof(struct list*))

struct listlist {
	struct list* data;
	struct listlist* next;
};

struct list {
	char data;
	struct list* next;
};

struct listlist* input();
struct list* add(struct list*, char);
//1
void printline(struct listlist*);
int len(struct list*);
//2
void output(struct listlist*);
//3
void clear(struct listlist*);

int main() {
	struct listlist* LL = input();
	
	printline(LL);
	output(LL);
	clear(LL);
}

struct listlist* input() {
	struct listlist* LL = malloc(sizeof(struct listlist));
	LL->data = NULL;
	LL->next = NULL;
	struct listlist* PP = LL;
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (c == ' ') {
			if (LL->data) {
				LL->next = malloc(sizeof(struct listlist));
				LL = LL->next;
				LL->data = NULL;
				LL->next = NULL;
			}
		} else {
			LL->data = add(LL->data, c);
		}
	}
	return PP;
}

struct list* add(struct list* L, char c) {
	struct list* P = L;
	if (L) {
		while (L->next)
			L = L->next;
		L->next = malloc(sizeof(struct list));
		L = L->next;
	} else {
		L = P = malloc(sizeof(struct list));
	}
	L->data = c;
	L->next = NULL;
	return P;
}

void printline(struct listlist* LL) {
	while (LL) {
		if(len(LL->data))
			printf("%d ", len(LL->data));
		LL = LL->next;
	}
	printf("\n\n");
}

int len(struct list* L) {
	int ans = 0;
	while (L) {
		ans++;
		L = L->next;
	}
	return ans;
}

void output(struct listlist* LL) {
	struct listlist* PP = LL;
	int maxlen = 0, i;
	if (LL)
		maxlen = len(LL->data);
	while (PP) {
		if (len(PP->data) > maxlen)
			maxlen = len(PP->data);
		PP = PP->next;
	}
	for (i = 0; i < maxlen; ++i) {
		PP = LL;
		while (PP) {
			struct list* p = PP->data;
			int j;
			
			for (j = 0; j < i && p; ++j)
				p = p->next;
				
			if (p)
				printf("%c ", p->data);
			else
				printf("  ");
				
			PP = PP->next;				
		}
		printf("\n");
	}
}

void clear(struct listlist* LL) {
	while (LL) {
		struct list* l = LL->data;
		
		while (l) {
			struct list* p = l;
			l = l->next;
			free(p);
		}

		struct listlist* PP = LL;
		LL = LL->next;
		free(PP);
	}
}
