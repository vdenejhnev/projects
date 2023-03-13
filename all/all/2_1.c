/* Массив char как одну сторку
 * посчитать количество областей из единиц
 * найти наибольшее количество подряд идущих нулей
 * вывести первые n битов
*/
#include <stdio.h>
#include <stdlib.h>
#define char unsigned char

int f1(char* A, int size_A, int n);
int f2(char* A, int size_A);
int f3(char* A, int size_A, int n);
void input(char **A, int *size_A);  //  чтение количества элементов и массива
void output(char *A, int size_A);  // вывод массива

int main() {
	char* A;
	int size_A;
	
	input(&A, &size_A);
	output(A, size_A);
	
	int n1, n3;
	scanf("%d", &n1);
	printf("n1 == %d\n", n1);
	
	scanf("%d", &n3);
	printf("n3 == %d\n", n3);
	
	printf("1 - %d\n", f1(A, size_A, n1));
	printf("2 - %d\n", f2(A, size_A));
	printf("3 - %d\n", f3(A, size_A, n3));
	return 0;
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

int f1(char* A, int size_A, int n) {
	int i, j, ans = 0, k = 0;
	for (i = 0; i < size_A; ++i) {
		for (j = sizeof(char) * 8 - 1; j >= 0 ; --j) {
			if (((A[i] >> j) & 1) == 0) {
				k++;
			} else {
				if (k > n)
					ans++;
				k = 0;
			}
		}
	}
	if (k > n)
		ans++;
	return ans;
}

int f2(char* A, int size_A) {
	int i, j, ans = 0, k = 0;
	for (i = 0; i < size_A; ++i) {
		for (j = sizeof(char) * 8 - 1; j >= 0 ; --j) {
			if (((A[i] >> j) & 1) == 0) {
				k++;
			} else {
				if (k > ans)
					ans = k;
				k = 0;
			}
		}
	}
	if (k > ans)
		ans = k;
	return ans;
}

int f3(char* A, int size_A, int n) {
	int s = sizeof(char);
	return A[n / (s * 8)] >> 
		   (n % (s * 8)) & 1;
}
