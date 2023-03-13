#include <stdio.h>

int main() {
    int a, b, n, i, j;
    scanf("%d %d %d", &a, &b, &n);
    printf("%*c", n + 1, ' ');
    for (i = a; i < b - 1; ++i)
        printf("%*i ", n, i);
    printf("%*i\n", n, i);

    for (i = a; i < b; ++i) {
        printf("%*i ", n, i);
        for (j = a; j < b - 1; ++j) {
            printf("%*lld ", n, (long long)i * j);
        }
        printf("%*lld\n", n, (long long)i * (b - 1));
    }
}
