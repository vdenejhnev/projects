#include <stdio.h>
#include <stdlib.h>
#define char unsigned char

void input(char **A, int *size_A);  //  чтение количества элементов и массива
void output(char *A, int size_A);  // вывод массива
void sort(char *A, int size_A);
void swap(char *a, char* b);
int comp(char a, char b);
int ones(char a);


int main() {
	char* A;
	int size_A;
	
	input(&A, &size_A);
	output(A, size_A);
	
	sort(A, size_A);
	output(A, size_A);
}


void input(char **A, int *size_A) {  //  чтение количества элементов и массива
	scanf("%d", size_A);
	int i;
	*A = malloc(*size_A * sizeof(char));
	for (i = 0; i < *size_A; ++i)
		scanf("%hhu", *A + i);
}

void output(char *A, int size_A) {
	int i;
	for (i = 0; i < size_A; ++i) {
		int j;
		for (j = sizeof(char) * 8 - 1; j >= 0 ; --j)
			printf("%d", ((A[i] >> j) & 1) == 1);
		printf(" ");
	}
	printf("\n");
}

void sort(char *A, int size_A) {
	int i, j;
	for (i = 0; i < size_A - 1; ++i)
		for (j = i + 1; j < size_A; ++j)
			if (comp(A[i], A[j]))
				swap(A + i, A + j);
}

void swap(char *a, char* b) {
	char c = *a;
	*a = *b;
	*b = c;
}

int comp(char a, char b) {
	int a1 = ones(a), b1 = ones(b);
	//printf("a = %hhu\n a1 == %d\n",a, a1 );
	if (a1 > b1 || (a1 == b1 && a > b))
		return 1;
	else 
		return 0;
}

int ones(char a) {
	int ans = 0;
	while (a) {
		if (a & 1)
			ans++;
		a >>= 1;
	}
	return ans;
}
