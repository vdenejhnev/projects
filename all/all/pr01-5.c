#include <stdio.h>
#include <stdlib.h>

struct num_file {
	FILE* fp;
	int data;
};

struct num_file *create(int argc, char ** argv);
void print(struct num_file *data, int n);
int check(struct num_file *data, int n);
int find(struct num_file *data, int n);
int min_num(struct num_file *A, int n);

int main(int argc, char ** argv) {
	struct num_file *data = create(argc, argv);
	print(data, argc - 1);
	printf("\n");
	free(data);
	return 0;
}

struct num_file *create(int argc, char ** argv) {
	int i;
	struct num_file * A = malloc(sizeof(struct num_file) * (argc - 1));
	for (i = 0; i < argc - 1; ++i) {
		A[i].fp = fopen(argv[i + 1], "r");
		fscanf(A[i].fp, "%d", &(A[i].data));
	}
	return A;
}


void print(struct num_file *A, int n) {
	while (check(A, n)) {
		printf("%d ", find(A, n));
	}
}


int check(struct num_file *A, int n) {
	int i;
	for (i = 0; i < n; ++i)
		if (!feof(A[i].fp))
			return 1;
	return 0;
}

int find(struct num_file *A, int n) {
	int num = min_num(A, n), ans;
	
	ans = A[num].data;
	fscanf(A[num].fp, "%d", &(A[num].data));
	return ans;
}

int min_num(struct num_file *A, int n) {
	int i = 0, min = 0;
	
	while (feof(A[min].fp))
		min++;
	
	for (i = min; i < n; ++i)
		if (!feof(A[i].fp) && A[min].data > A[i].data) {
			min = i;
		}
	return min;
}
