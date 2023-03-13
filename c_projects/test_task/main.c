#include <stdio.h>
#include <stdlib.h>

main()
{
    int c, m[256]={0}, i, j, max;

    while((c = getchar())!='\
          n') {
        m[c]++;
    }

    for(i = 1, max = m[0];i < 256;i++){
        if(max<m[i]) {
            max = m[i];
        }
    }

    for(i = 0; i < 256; i++) {
        if(m[i]) {
            printf("%c", i);
            for(j = 0; j<80*m[i]/max;j++) {
                putchar('*');
            }
            putchar('\n');
        }
    }
}
