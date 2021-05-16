#include <stdio.h>
#include <stdlib.h>

char c = 'A';

int main() {
    FILE *f;
    char buf;

    f = fopen("new.txt", "r");
    printf("%d\n", c);

    while((buf = fgetc(f)) != EOF) {
        printf("%c", buf);
    }

    fclose(f);
    return 0;
}