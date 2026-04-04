#include "../../../../../main/c/Matrix/matrix.h"
#include "../util/cbuilderTest.h"

void testMatrixCreateHappyflow() {

    int rows = 2;
    int cols = 3;

    Matrix *matrix = matrixCreateValue(rows, cols, 0.0);

    assert(matrixCols(matrix) == 3);
    assert(matrixRows(matrix) == 2);
    assert(matrixGetElement(matrix, 1, 2) == 0.0);
    assert(!matrixIsTransposed(matrix));
}

void testMatrixCreateRowColLimit() {
    
    Matrix *matrix = matrixCreateValue(0, 1, 1.0);

    assert(matrix == NULL);

    Matrix *matrix2 = matrixCreateValue(1, -14, -13.0);

    assert(matrix2 == NULL);
}