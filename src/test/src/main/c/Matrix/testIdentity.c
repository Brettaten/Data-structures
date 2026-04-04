#include "../../../../../main/c/Matrix/matrix.h"
#include "../util/cbuilderTest.h"

void testMatrixCreateIdentityHappyflow(){

    int size = 3;

    Matrix *matrix = matrixCreateIdentity(size);

    assert(matrixCols(matrix) == 3);
    assert(matrixRows(matrix) == 3);
    assert(matrixGetElement(matrix, 1, 2) == 0.0);
    assert(matrixGetElement(matrix, 1, 1) == 1);
    assert(!matrixIsTransposed(matrix));
}

void testMatrixCreateIdentityRowColLimit() {
    
    Matrix *matrix = matrixCreateIdentity(0);

    assert(matrix == NULL);

    Matrix *matrix2 = matrixCreateIdentity(-12);

    assert(matrix2 == NULL);
}