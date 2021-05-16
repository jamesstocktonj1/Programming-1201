/* helloyou.c */
/* Hello with text string. */

#include <stdio.h>

#define SUCCESS 0
#define DEBUG

int num = 10;

char name[]="human";



#ifndef DEBUG
#define MARK printf("%d\n", __LINE__);
#endif

int main() {
    printf("Hello %s!\n", name);
#ifndef DEBUG  
    MARK
#endif
    return SUCCESS;
}
