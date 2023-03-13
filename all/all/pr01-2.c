#include <stdio.h>

int main() {
	long long int sum = 0;
	int c;
	while ((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9')
			sum += c - '0';
		if (c >= 'a' && c <= 'f')
			sum += c - 'a' + 10;
		if (c >= 'A' && c <= 'F')
			sum += c - 'A' + 10;
	}
	printf("%lld\n", sum);
	return 0;
}
