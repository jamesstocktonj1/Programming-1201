#include <stdio.h>
#include "math.h"

#define PI 3.1415
#define FREQ 1



int main() {
    unsigned long x = 0.0;
    float y;

    while(1) {
        x++;

        y = 0.5 +  sin(x * (PI / 180) * FREQ) * 0.5;

        printf("X: %d", x);
        printf("\tY: %.2f\n", y);
    }
    return 0;
}