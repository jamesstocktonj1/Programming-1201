#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

int main() {


    printf(RED "Hello World!" RESET);

    return 0;
}