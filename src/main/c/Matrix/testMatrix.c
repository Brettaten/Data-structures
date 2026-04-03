#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matrix.h"

int main()
{
    float data[] = {1/80};
    Matrix *pMatrix = matrixCreate(data, 1, 1);

    float data2[] = {0.1f};
    Matrix *pMatrix2 = matrixCreate(data2, 1, 1);

    Matrix *result = matrixGauss(pMatrix, pMatrix2);

    matrixDump(result);

    Matrix *inverse = matrixInverse(pMatrix);

    matrixDump(inverse);
}