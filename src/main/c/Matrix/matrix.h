
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

Matrix *matrixTranspose(Matrix *pMatrix);



