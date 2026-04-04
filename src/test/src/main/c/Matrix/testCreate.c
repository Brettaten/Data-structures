#include "../../../../../main/c/Matrix/matrix.h"
#include "../util/cbuilderTest.h"

void testMatrixCreateHappyflow() {

    float data[] ={1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    int rows = 2;
    int cols = 3;

    Matrix *matrix = matrixCreate(data, rows, cols);

    assert(matrixCols(matrix) == 3);
    assert(matrixRows(matrix) == 2);
    assert(matrixGetElement(matrix, 1, 2) == 6.0);
    assert(!matrixIsTransposed(matrix));
    assert(data != NULL);
}

void testMatrixCreateNullData() {
    
    Matrix *matrix = matrixCreate(NULL, 1, 1);

    assert(matrix == NULL);
}

void testMatrixCreateRowColLimit() {
    
    float data[] = {0.0};
    Matrix *matrix = matrixCreate(data, 0, 1);

    assert(matrix == NULL);

    Matrix *matrix2 = matrixCreate(data, 1, -14);

    assert(matrix2 == NULL);
}

