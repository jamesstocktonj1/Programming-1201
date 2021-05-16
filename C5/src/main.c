#include <stdio.h>
#include "vector.h"
#include "matrix.h"


#define VEC_FILE "example1.vec"
#define MAT_FILE "example1.mat"


Vector v;
Matrix m;

int main() {
    v = createVectorFromFile(VEC_FILE);
    m = createMatrixFromFile(MAT_FILE);


    //printVector(v);
    printMatrix(m);

    destroyVector(v);
    destroyMatrix(m);

    return 0;
}