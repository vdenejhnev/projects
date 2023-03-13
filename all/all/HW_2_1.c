#include <stdio.h>
#include <stdlib.h>

void heapify(int*, int, int);  //  пирамидальная сортировка
void heapSort(int*, int);
int input(int**, int*);
void output(int*, int, void (int));
void swap(int*, int*);
int comp(int, int);
int count(int);
void print10(int);
void print2(int);

int main() {
    int* A, n;
    if (input(&A, &n)) {
    printf("INPUT DATA:\n");
        output(A, n, print10);
        output(A, n, print2);
        heapSort(A, n);
        printf("OUTPUT DATA:\n");
        output(A, n, print10);
        output(A, n, print2);
        free(A);
    }
}

void heapify(int* arr, int n, int i) {  // рекурсия
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && comp(arr[l], arr[largest]))
        largest = l;

    if (r < n && comp(arr[r], arr[largest]))
        largest = r;

    if (largest != i) {
        swap(arr + i, arr + largest);
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {  // основная функция сортировки
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr, arr + i);
        heapify(arr, i, 0);
    }
}

int input(int** A, int* n) {  // ввод массива
    printf("input the number of array numbers:\n");
    if (scanf("%d", n) != 1 || *n < 0) {
        printf("incorrect\n");
        *A = NULL;
        *n = 0;
        return 0;
    }
    printf("input the array:");
    *A = malloc(*n * sizeof(int));
    for (int i = 0; i < *n; ++i)
        if (scanf("%d", *A + i) != 1) {
            free(*A);
            return 0;
        }
    return 1;
}

void output(int* A, int n, void print(int)){  // вывод массива void print(int) - передача функции с помощью которой будут выводиться элементы
    for (int i = 0; i < n; ++i)
        print(A[i]);
    printf("\n");
}

void swap(int* a, int* b) {  // замена чисел местами
    int c = *a;
    *a = *b;
    *b = c;
}

int comp(int a, int b) {  // условие для сортировки
    int A = count(a), B = count(b);
    return A > B || (A == B && a < b);  // возвращает 1, если в числе а больше битов с 1
}

int count(int a) {  // подсчет битов с 1
    int A = 0;
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i)
        A += (a >> i) & 1;
    return A;
}

void print10(int a) {  // вывод в десятичной СС
    printf("%d ", a);
}

void print2(int a) {  // вывод в двоичной СС
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i)
        printf("%d", (a >> i) & 1);
    printf("\n");
}
