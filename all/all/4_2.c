#include <stdio.h>
#include <stdlib.h>

struct file_string {
	int size;
	int pos;
};

void create_arr(char* name, struct file_string** A, int *M);
void print_string(char* name, struct file_string* A, int n);
void sortfile(char* name, struct file_string* A, int m);
void swap(int* A, int* B);

int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "r");
	if (argc > 1 && fp) {
		struct file_string* A;
		int m, i, n;
		
		create_arr(argv[1], &A, &m);
		fclose(fp);
		for (i = 0; i < m; ++i)
			printf("%d %d\n", A[i].pos, A[i].size);
		
		printf("input string number:\n");
		scanf("%d", &n);
		
		print_string(argv[1], A, n);
		
		sortfile(argv[1], A, m);
		free(A);
	}
}

void create_arr(char* name, struct file_string** A, int *M) {
	FILE* fp = fopen(name, "r");
	int c, prev = 0, size = 0, pos = 0, i = 1;
	*A = malloc(sizeof(struct file_string));
	(*A)[0].pos = 0;
	
	
	while ((c = getc(fp)) != EOF) {
		size++;
		pos++;
		if (c == '\n') {
			*A = realloc(*A, sizeof(struct file_string) * (i + 1));
			(*A)[i - 1].size = size;
			i++;
			(*A)[i - 1].pos = pos;
			size = 0;
		}
		
		
		prev = c;
	}
	fclose(fp);
	
	if (prev != '\n') {
		fp = fopen(name, "w+");
		fprintf(fp, "\n");
		fclose(fp);
		size++;
		i++;
	}
	*M = i - 1;
}


void print_string(char* name, struct file_string* A, int n) {
	FILE * fp = fopen(name, "r");
	int i;
	if (n > 0) {
		fseek(fp, A[n - 1].pos, SEEK_SET);
	
	for (i = 0; i < A[n - 1].size; ++i)
		printf("%c", getc(fp));
	} else {
		printf("ERROR");
	}
}

void sortfile(char* name, struct file_string* A, int m) {
	int i, j;
	FILE * fpout = fopen("sort.txt", "w");
	for (i = 0; i < m - 1; ++i)
		for (j = i + 1; j < m; ++j) {
			if (A[i].size > A[j].size) {
				swap(&(A[i].pos), &(A[j].pos));
				swap(&(A[i].size), &(A[j].size));
			}
		}
		
	for (i = 0; i < m; ++i) {
		FILE * fp = fopen(name, "r");
		int j;
		
		fseek(fp, A[i].pos, SEEK_SET);
		
		for (j = 0; j < A[i].size; ++j) {
			fprintf(fpout, "%c", getc(fp));
			//printf("%d %d\n", j, A[i].size);
		}
	}
}

void swap(int* A, int* B) {
	int C = *A;
	*A = *B;
	*B = C;
}
