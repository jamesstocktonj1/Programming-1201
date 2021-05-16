#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "string.h"

#define PI 3.1415
#define FREQ 1

#define CONSOL_WIDTH 80

#define TICK_INTERVAL 10

void plotval(float val, int width, int num);

int main() {
    unsigned long x = 0.0;
    float y;

    while(1) {
        x++;

        y = 0.5 +  sin(x * (PI / 180) * FREQ) * 0.5;

        printf("X: %d\t", x);
        //printf("Y: %.2f\n", y);

        plotval(y, CONSOL_WIDTH, x);
    }
    return 0;
}



void plotval(float val, int width, int num) {

    //array of characters to be printed
    char *cons;
    cons = (char *) malloc(width);
    memset(cons, ' ', width);

    //y axis marker (ish)
    cons[0] = '|';

    //inserts tick into array if num is at tick interval
    if((num % TICK_INTERVAL) == 0) {

        for(int i=1; i<4; i++) {
            cons[i] = '-';
        }
    }

    //calculates which character should be *
    int charNum = (int) (width * val);
    cons[charNum] = '*';

    for(int i=0; i<width; i++) {
        printf("%c",cons[i]);
    }
    printf("\n");
}