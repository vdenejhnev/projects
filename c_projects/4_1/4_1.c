#include <stdio.h>

int print_file(char* name);

int main(int argc, char** argv) {
	if (argc > 1) {
		int n = print_file(argv[1]);
		printf("\ncount of strings:%d\n", n);
	}
}


int print_file(char* name) {
	int n = 0, c, prev = 0;
	FILE * fp = fopen(name, "r");
	
	while ((c = getc(fp)) != EOF) {
		printf("%c", c);
		n += c == '\n';
		prev = c;
	}
	fclose(fp);
	
	if (prev != '\n') {
		n++;
		fp = fopen(name, "w+");
		fprintf(fp, "\n");
		fclose(fp);
	}
	return n;
}
