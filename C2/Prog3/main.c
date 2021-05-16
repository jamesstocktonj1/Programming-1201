#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "string.h"

#define PI 3.1415
#define FREQ 1

#define CONSOL_WIDTH 80

void plotval(float val, int width);

int main() {
    unsigned long x = 0.0;
    float y;

    while(1) {
        x++;

        y = 0.5 +  sin(x * (PI / 180) * FREQ) * 0.5;

        printf("X: %d\t", x);
        //printf("Y: %.2f\n", y);

        plotval(y, CONSOL_WIDTH);
    }
    return 0;
}



void plotval(float val, int width) {

    char *cons;
    cons = (char *) malloc(width);
    memset(cons, ' ', width);

    int charNum = (int) (width * val);

    cons[charNum] = '*';

    for(int i=0; i<width; i++) {
        printf("%c",cons[i]);
    }
    printf("\n");
}