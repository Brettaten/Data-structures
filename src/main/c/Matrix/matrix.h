#include <stdbool.h>

/**
 * Struct that represents a matrix
 */
typedef struct Matrix Matrix;

/**
 * Function that creates a new matrix with the passed data
 *
 * @param data the elements of the matrix
 * @param rows the amount of rows
 * @param cols the amount of cols
 *
 * @return Success: Pointer to the created matrix | Failure: NULL
 * 
 * @note The passed data does not have to be allocated on the heap.
 * The function creates a deep copy of the data before adding it to the matrix.
 */
Matrix *matrixCreate(float *data, int rows, int cols);

/**
 * Function that creates a new matrix with the passed value
 *
 * @param rows the amount of rows
 * @param cols the amount of cols
 * @param value the initial value
 *
 * @return Success: Pointer to the created matrix | Failure: NULL
 */
Matrix *matrixCreateValue(int rows, int cols, float value);

/**
 * Function that creates a new identity matrix
 *
 * @param size the amount of rows and columns of the square matrix
 *
 * @return Success: Pointer to the created matrix | Failure: NULL
 */
Matrix *matrixCreateIdentity(int size);

/**
 * Function that creates a new matrix with the passed value
 *
 * @param rows the amount of rows
 * @param cols the amount of cols
 * @param lowerBound the min value
 * @param upperBound the max value
 * @param isInteger if this flag is set, all values are integers
 *
 * @return Success: Pointer to the created matrix | Failure: NULL
 */
Matrix *matrixCreateRandom(int rows, int cols, float lowerBound, float upperBound, bool isInteger);

/**
 * Function used to retrieve the element of the passed matrix at the passed position
 *
 * @param pMatrix pointer to the matrix
 * @param row the row of the element
 * @param col the column of the element
 *
 * @return Success: the float value of the element | Failure: -1
 */
float matrixGetElement(Matrix *pMatrix, int row, int col);

/**
 * Function used to retrieve the passed row of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row the row
 *
 * @return Success: the row vector | Failure: NULL
 */
Matrix *matrixGetRow(Matrix *pMatrix, int row);

/**
 * Function used to retrieve the passed column of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param col the col
 *
 * @return Success: the col vector | Failure: NULL
 * 
 * @note Retrieving a column is slower than retrieving a row
 */
Matrix *matrixGetCol(Matrix *pMatrix, int col);

/**
 * Function used to retrieve the passed rows of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 *
 * @return Success: the matrix of the row vectors | Failure: NULL
 */
Matrix *matrixGetRows(Matrix *pMatrix, int row1, int row2);

/**
 * Function used to retrieve the passed columns of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param col1 the first column
 * @param col2 the second column
 *
 * @return Success: the matrix of the column vectors | Failure: NULL
 * 
 * @note Retrieving a column is slower than retrieving a row
 */
Matrix *matrixGetCols(Matrix *pMatrix, int col1, int col2);

/**
 * Function used to delete the passed row of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param row the row
 * 
 * @return Success: the matrix without the row | Failure: NULL
 */
Matrix *matrixDelRow(Matrix *pMatrix, int row);

/**
 * Function used to delete the passed column of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param col the column
 * 
 * @return Success: the matrix without the column | Failure: NULL
 * 
 * @note Deleting a column is slower than deleting a row
 */
Matrix *matrixDelCol(Matrix *pMatrix, int col);

/**
 * Function used to delete the passed rows of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 * 
 * @return Success: the matrix without the rows | Failure: NULL
 */
Matrix *matrixDelRows(Matrix *pMatrix, int row1, int row2);

/**
 * Function used to delete the passed columns of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param col1 the first column
 * @param col2 the second column
 * 
 * @return Success: the matrix without the columns | Failure: NULL
 * 
 * @note Deleting a column is slower than deleting a row
 */
Matrix *matrixDelCols(Matrix *pMatrix, int col1, int col2);

/**
 * Function used to create the adjoint of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param row the row that should be deleted
 * @param col the col that should be deleted
 * 
 * @return Success: the new matrix | Failure: NULL
 */
Matrix *matrixAdjoint(Matrix *pMatrix, int row, int col);

/**
 * Function used to return the data array of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * 
 * @return Success: the data array | Failure: NULL
 * 
 * @note The returned array is a deep copy and thus has to be freed by the caller
 */
float *matrixGetData(Matrix *pMatrix);

/**
 * Function used to return the passed row of the data array of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param row the row
 * 
 * @return Success: the data array | Failure: NULL
 * 
 * @note The returned array is a deep copy and thus has to be freed by the caller
 */
float *matrixGetDataRow(Matrix *pMatrix, int row);

/**
 * Function used to return the passed column of the data array of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param col the column
 * 
 * @return Success: the data array | Failure: NULL
 * 
 * @note The returned array is a deep copy and thus has to be freed by the caller
 */
float *matrixGetDataCol(Matrix *pMatrix, int col);

/**
 * Function used to swap two rows
 * 
 * @param pMatrix the pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixSwapRows(Matrix *pMatrix, int row1, int row2);

/**
 * Function used to swap two column
 * 
 * @param pMatrix the pointer to the matrix
 * @param col1 the first column
 * @param col2 the second column
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixSwapCols(Matrix *pMatrix, int col1, int col2);

/**
 * Function used to scale a row by a certain factor
 * 
 * @param pMatrix the pointer to the matrix
 * @param row the row
 * @param factor the factor
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixScaleRow(Matrix *pMatrix, int row, float factor);

/**
 * Function used to scale a column by a certain factor
 * 
 * @param pMatrix the pointer to the matrix
 * @param col the column
 * @param factor the factor
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixScaleCol(Matrix *pMatrix, int col, float factor);

/**
 * Function used to add the second row, which can be scaled by a factor, to the first
 * 
 * @param pMatrix the pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 * @param factor the factor
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixAddRows(Matrix *pMatrix, int row1, int row2, float factor);

/**
 * Function used to add the second column, which can be scaled by a factor, to the first
 * 
 * @param pMatrix the pointer to the matrix
 * @param col1 the first column
 * @param col2 the second column
 * @param factor the factor
 * 
 * @return Success: 0 | Failure: -1
 */
int matrixAddCols(Matrix *pMatrix, int col1, int col2, float factor);

/**
 * Function used to set the transpose flag of the passed matrix
 * 
 * @param pMatrix pointer to the matrix
 * @param val the flag
 * 
 * @note The function does not really transpose the matrix or the matrix data.
 * It just sets the flag and every methods checks whether a matrix is transposed or not.
 * If it is transposed, the function internally swaps the meaning of row and column to achieve the desired effect.
 */
void matrixTranspose(Matrix *pMatrix, bool val);

/**
 * Function used to return the transpose state of a matrix
 * 
 * @param pMatrix the matrix
 * 
 * @return true if the matrix is transposed otherwise false
 */
bool matrixIsTransposed(Matrix *pMatrix);

/**
 * Function used to get the amount of rows
 * 
 * @param pMatrix pointer to the matrix
 * 
 * @return Success: the amount of rows | Failure: -1
 */
int matrixRows(Matrix *pMatrix);

/**
 * Function used to get the amount of columns
 * 
 * @param pMatrix pointer to the matrix
 * 
 * @return Success: the amount of columns | Failure: -1
 */
int matrixCols(Matrix *pMatrix);

/**
 * Function used to compare two matrices
 * 
 * @param pMatrix1 the first matrix
 * @param pMatrix2 the second matrix
 * 
 * @return true if both matrices have the same layout and values otherwise false
 */
bool matrixEquals(Matrix *pMatrix1, Matrix *pMatrix2);

/**
 * Function used to add two matrices
 * 
 * @param pMatrix1 the first matrix
 * @param pMatrix2 the second matrix
 * 
 * @return Success: the result matrix M1 + M2 | Failure: NULL
 */
Matrix *matrixAdd(Matrix *pMatrix1, Matrix *pMatrix2);

/**
 * Function used to subtract two matrices
 * 
 * @param pMatrix1 the first matrix
 * @param pMatrix2 the second matrix
 * 
 * @return Success: the result matrix M1 - M2 | Failure: NULL
 */
Matrix *matrixSubtract(Matrix *pMatrix1, Matrix *pMatrix2);

/**
 * Function used to perform a scalar multiplication on a passed matrix
 * 
 * @param pMatrix the matrix
 * @param scalar the scalar
 * 
 * @return Success: the result matrix x * M | Failure: NULL
 */
Matrix *matrixScalarMult(Matrix *pMatrix, float scalar);

/**
 * Function used to solve a system of linear equation
 * 
 * @param a the matrix A
 * @param b the matrix b, pass NULL for a zero matrix
 * 
 * @return Success: the result matrix x of Ax=b | Failure: NULL
 */
Matrix *matrixGauss(Matrix *a, Matrix *b);

/**
 * Function used to compute the inverse of a nonsingular matrix
 * 
 * @param a the matrix A
 * 
 * @return Success: the inverse | Failure: NULL
 */
Matrix *matrixInverse(Matrix *a);

/**
 * Function used to compute the rank of a matrix
 * 
 * @param a the matrix a
 * 
 * @return Success: the rank | Failure: -1
 */
int matrixRank(Matrix *a);

/**
 * Function used to determine whether a matrix is invertible / nonsingular
 * 
 * @param a the matrix a
 * 
 * @return true if invertible, otherwise false
 */
bool matrixIsInvertible(Matrix *a);

/**
 * Function used to perform a matrix multiplication
 * 
 * @param pMatrix1 the first matrix
 * @param pMatrix2 the second matrix
 * 
 * @return Success: the result matrix M1 * M2 | Failure: NULL
 */
Matrix *matrixMult(Matrix *pMatrix1, Matrix *pMatrix2);

/**
 * Function used to create a deep copy of a matrix
 *
 * @param pMatrix the pointer to the matrix
 *
 * @return Success: the copy of the matrix | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside a data structure and thus function pointers
 *      with void datatype are needed
 */
void *matrixCopy(void *pMatrix);

/**
 * Function used to free the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside a data structure and thus function pointers
 *      with void datatype are needed
 */
void matrixFree(void *pMatrix);

/**
 * Function used to print a Matrix on the console
 * 
 * @param pMatrix pointer to the matrix
 */
void matrixDump(Matrix *pMatrix);

