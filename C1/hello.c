/* hello.c */
/* A famous test for the C build process. */

#include <stdio.h>

#define SUCCESS 0

int main() {
    /* A new-line control character (\n)   */
    /* is used here, in case the terminal  */
    /* collects complete lines before      */
    /* showing them.                       */
    printf("Hello world!\n");
    return SUCCESS;
}
