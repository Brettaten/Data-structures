#include "../../../../../main/c/Matrix/matrix.h"
#include "../util/cbuilderTest.h"
#include <math.h>
#include <stdio.h>

void testMatrixCreateRandomHappyflow(){

    int rows = 3;
    int cols = 2;
    float lowerBound = -1.5f;
    float upperBound = 4.2f;
    bool isInteger = false;

    Matrix *matrix = matrixCreateRandom(rows, cols, lowerBound, upperBound, isInteger);

    assert(matrixRows(matrix) == 3);
    assert(matrixCols(matrix) == 2);

    float val1 = matrixGetElement(matrix, 1, 1);

    assert(val1 >= lowerBound && val1 <= upperBound);
    assert(!matrixIsTransposed(matrix));

    Matrix *matrix2 = matrixCreateRandom(rows, cols, lowerBound, upperBound, !isInteger);

    float val2 = matrixGetElement(matrix2, 1, 1);

    assert(ceilf(val2) == val2);

    Matrix *matrix3 = matrixCreateRandom(rows, cols, -1.2, -1.2, false);

    float val3 = matrixGetElement(matrix3, 1, 1);

    assert(val3 == -1.2f);

    Matrix *matrix4 = matrixCreateRandom(rows, cols, -1.2, -1.0, true);

    float val4 = matrixGetElement(matrix4, 1, 1);

    assert(val4 == -1.0f);

    Matrix *matrix5 = matrixCreateRandom(rows, cols, -1.2, -0.00001, true);

    float val5 = matrixGetElement(matrix5, 1, 1);

    assert(val5 == -1.0f);
}

void testMatrixCreateRandomRowColLimit() {
    
    Matrix *matrix = matrixCreateRandom(0, 1, 0.0, 1.0, true);

    assert(matrix == NULL);

    Matrix *matrix2 = matrixCreateRandom(1, -14, 0.0, 1.0, false);

    assert(matrix2 == NULL);
}

void testMatrixCreateRandomBound() {

    Matrix *matrix1 = matrixCreateRandom(1, 1, 0.1, 0.0, true);

    assert(matrix1 == NULL);
}

void testMatrixCreateRandomIntegerRange() {

    Matrix *matrix1 = matrixCreateRandom(1, 1, -1.2, -1.2, true);

    assert(matrix1 == NULL);

    Matrix *matrix2 = matrixCreateRandom(1, 1, -1.999999, -1.000001, true);

    assert(matrix2 == NULL);
}