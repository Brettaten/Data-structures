#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "matrix.h"

typedef struct Matrix
{
    float *data;
    int rows;
    int cols;

    bool isTransposed;
} Matrix;

/**
 * Function used to get the index of the data array
 *
 * @param pMatrix pointer to the matrix
 * @param row the row
 * @param col the col
 *
 * @return Success: the index | Failure: -1
 */
int matrixGetIndex(Matrix *pMatrix, int row, int col);

/**
 * Function used to retrieve the passed row of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row the row
 *
 * @return Success: the row vector | Failure: NULL
 */
Matrix *matrixGetRowHelper(Matrix *pMatrix, int row);

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
Matrix *matrixGetColHelper(Matrix *pMatrix, int col);

/**
 * Function used to retrieve the passed rows of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 *
 * @return Success: the matrix of the row vectors | Failure: NULL
 */
Matrix *matrixGetRowsHelper(Matrix *pMatrix, int row1, int row2);

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
Matrix *matrixGetColsHelper(Matrix *pMatrix, int col1, int col2);

/**
 * Function used to delete the passed row of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row the row
 *
 * @return Success: the matrix without the row | Failure: NULL
 */
Matrix *matrixDelRowHelper(Matrix *pMatrix, int row);

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
Matrix *matrixDelColHelper(Matrix *pMatrix, int col);

/**
 * Function used to delete the passed rows of the passed matrix
 *
 * @param pMatrix pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 *
 * @return Success: the matrix without the rows | Failure: NULL
 */
Matrix *matrixDelRowsHelper(Matrix *pMatrix, int row1, int row2);

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
Matrix *matrixDelColsHelper(Matrix *pMatrix, int col1, int col2);

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
float *matrixGetDataRowHelper(Matrix *pMatrix, int row);

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
float *matrixGetDataColHelper(Matrix *pMatrix, int col);

/**
 * Function used to swap two rows
 *
 * @param pMatrix the pointer to the matrix
 * @param row1 the first row
 * @param row2 the second row
 *
 * @return Success: 0 | Failure: -1
 */
int matrixSwapRowsHelper(Matrix *pMatrix, int row1, int row2);

/**
 * Function used to swap two column
 *
 * @param pMatrix the pointer to the matrix
 * @param col1 the first column
 * @param col2 the second column
 *
 * @return Success: 0 | Failure: -1
 */
int matrixSwapColsHelper(Matrix *pMatrix, int col1, int col2);

/**
 * Function used to scale a row by a certain factor
 *
 * @param pMatrix the pointer to the matrix
 * @param row the row
 * @param factor the factor
 *
 * @return Success: 0 | Failure: -1
 */
int matrixScaleRowHelper(Matrix *pMatrix, int row, float factor);

/**
 * Function used to scale a column by a certain factor
 *
 * @param pMatrix the pointer to the matrix
 * @param col the column
 * @param factor the factor
 *
 * @return Success: 0 | Failure: -1
 */
int matrixScaleColHelper(Matrix *pMatrix, int col, float factor);

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
int matrixAddRowsHelper(Matrix *pMatrix, int row1, int row2, float factor);

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
int matrixAddColsHelper(Matrix *pMatrix, int col1, int col2, float factor);

Matrix *matrixCreate(float *data, int rows, int cols)
{
    if (data == NULL)
    {
        printf("[ERROR] : data can not be null | matrixCreate \n");
        return NULL;
    }
    if (rows < 1 || cols < 1)
    {
        printf("[ERROR] : the matrix has to have atleast one column and one row | matrixCreate \n");
        return NULL;
    }

    Matrix *pMatrix = (Matrix *)malloc(sizeof(Matrix));

    if (pMatrix == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreate \n");
        return NULL;
    }

    int dataSize = sizeof(float) * rows * cols;
    float *pCopy = (float *)malloc(dataSize);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreate \n");
        return NULL;
    }

    memcpy(pCopy, data, dataSize);

    pMatrix->data = pCopy;
    pMatrix->rows = rows;
    pMatrix->cols = cols;
    pMatrix->isTransposed = false;

    return pMatrix;
}

Matrix *matrixCreateValue(int rows, int cols, float value)
{
    if (rows < 1 || cols < 1)
    {
        printf("[ERROR] : the matrix has to have atleast one column and one row | matrixCreateValue \n");
        return NULL;
    }

    Matrix *pMatrix = (Matrix *)malloc(sizeof(Matrix));

    if (pMatrix == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateValue \n");
        return NULL;
    }

    int dataSize = sizeof(float) * rows * cols;
    float *pCopy = (float *)malloc(dataSize);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateValue \n");
        return NULL;
    }

    for (int i = 0; i < rows * cols; i++)
    {
        pCopy[i] = value;
    }

    pMatrix->data = pCopy;
    pMatrix->rows = rows;
    pMatrix->cols = cols;
    pMatrix->isTransposed = false;

    return pMatrix;
}

Matrix * matrixCreateIdentity(int size)
{
    Matrix *pMatrix = (Matrix *)malloc(sizeof(Matrix));

    if (pMatrix == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateIdentity \n");
        return NULL;
    }

    int dataSize = sizeof(float) * size * size;
    float *pCopy = (float *)malloc(dataSize);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateIdentity \n");
        return NULL;
    }

    for (int i = 0, r = 0, c = -1; i < size * size; i++)
    {
        c++;

        if(c == size){
            c = 0;
            r++;
        }
        if(r == c){
            pCopy[i] = 1;
        }
        else{
            pCopy[i] = 0;
        }
    }

    pMatrix->data = pCopy;
    pMatrix->rows = size;
    pMatrix->cols = size;
    pMatrix->isTransposed = false;

    return pMatrix;
}

Matrix *matrixCreateRandom(int rows, int cols, float lowerBound, float upperBound, bool isInteger)
{
    srand(time(NULL) * 1000 + clock() % 1000);

    if (rows < 1 || cols < 1)
    {
        printf("[ERROR] : the matrix has to have atleast one column and one row | matrixCreateRandom \n");
        return NULL;
    }

    if (lowerBound > upperBound)
    {
        printf("[ERROR] : the lower bound can not be greater than the upper bound | matrixCreateRandom \n");
        return NULL;
    }

    Matrix *pMatrix = (Matrix *)malloc(sizeof(Matrix));

    if (pMatrix == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateRandom \n");
        return NULL;
    }

    int dataSize = sizeof(float) * rows * cols;
    float *pCopy = (float *)malloc(dataSize);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixCreateRandom \n");
        return NULL;
    }

    for (int i = 0; i < rows * cols; i++)
    {

        float rnd;

        if (isInteger)
        {
            rnd = (float)((int)lowerBound + rand() % ((int)upperBound - (int)lowerBound + 1));
        }
        else
        {
            rnd = ((float)rand() / RAND_MAX) * (upperBound - lowerBound) + lowerBound;
        }

        pCopy[i] = rnd;
    }

    pMatrix->data = pCopy;
    pMatrix->rows = rows;
    pMatrix->cols = cols;
    pMatrix->isTransposed = false;

    return pMatrix;
}

float matrixGetElement(Matrix *pMatrix, int row, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetElement \n");
        return -1.0f;
    }

    if (row < 0 || row >= matrixRows(pMatrix) || col < 0 || col >= matrixCols(pMatrix))
    {
        printf("[ERROR] : out of bounds | matrixGetElement \n");
        return -1.0f;
    }

    int index = matrixGetIndex(pMatrix, row, col);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetElement \n");
        return -1.0f;
    }

    return pMatrix->data[index];
}

Matrix *matrixGetRow(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetRow \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetColHelper(pMatrix, row);
    }
    return matrixGetRowHelper(pMatrix, row);
}

Matrix *matrixGetCol(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetCol \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetRowHelper(pMatrix, col);
    }
    return matrixGetColHelper(pMatrix, col);
}

Matrix *matrixGetRows(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetRows \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetColsHelper(pMatrix, row1, row2);
    }
    return matrixGetRowsHelper(pMatrix, row1, row2);
}

Matrix *matrixGetCols(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetCols \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetRowsHelper(pMatrix, col1, col2);
    }
    return matrixGetColsHelper(pMatrix, col1, col2);
}

Matrix *matrixDelRow(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRow \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixDelColHelper(pMatrix, row);
    }
    return matrixDelRowHelper(pMatrix, row);
}

Matrix *matrixDelCol(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelCol \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixDelRowHelper(pMatrix, col);
    }
    return matrixDelColHelper(pMatrix, col);
}

Matrix *matrixDelRows(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRows \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixDelColsHelper(pMatrix, row1, row2);
    }
    return matrixDelRowsHelper(pMatrix, row1, row2);
}

Matrix *matrixDelCols(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelCols \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixDelRowsHelper(pMatrix, col1, col2);
    }
    return matrixDelCols(pMatrix, col1, col2);
}

Matrix *matrixAdjoint(Matrix *pMatrix, int row, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixAdjoint \n");
        return NULL;
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : row out of bounds | matrixAdjoint \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : col out of bounds | matrixAdjoint \n");
        return NULL;
    }

    Matrix *pDelRow = matrixDelRow(pMatrix, row);
    Matrix *pAdjoint = matrixDelCol(pDelRow, col);

    matrixFree(pDelRow);

    return pAdjoint;
}

float *matrixGetData(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixGetData \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows * pMatrix->cols);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetData \n");
        return NULL;
    }

    memcpy(pCopy, pMatrix->data, sizeof(float) * pMatrix->cols * pMatrix->rows);

    return pCopy;
}

float *matrixGetDataRow(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetDataRow \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetDataColHelper(pMatrix, row);
    }
    return matrixGetDataRowHelper(pMatrix, row);
}

float *matrixGetDataCol(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetDataCol \n");
        return NULL;
    }

    if (pMatrix->isTransposed)
    {
        return matrixGetDataRowHelper(pMatrix, col);
    }
    return matrixGetDataColHelper(pMatrix, col);
}

int matrixSwapRows(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixSwapRows \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixSwapColsHelper(pMatrix, row1, row2);
    }
    return matrixSwapRowsHelper(pMatrix, row1, row2);
}

int matrixSwapCols(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixSwapCols \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixSwapRowsHelper(pMatrix, col1, col2);
    }
    return matrixSwapColsHelper(pMatrix, col1, col2);
}

int matrixScaleRow(Matrix *pMatrix, int row, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixScaleRow \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixScaleColHelper(pMatrix, row, factor);
    }
    return matrixScaleRowHelper(pMatrix, row, factor);
}

int matrixScaleCol(Matrix *pMatrix, int col, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixScaleCol \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixScaleRowHelper(pMatrix, col, factor);
    }
    return matrixScaleColHelper(pMatrix, col, factor);
}

int matrixAddRows(Matrix *pMatrix, int row1, int row2, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixAddRows \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixAddColsHelper(pMatrix, row1, row2, factor);
    }
    return matrixAddRowsHelper(pMatrix, row1, row2, factor);
}

int matrixAddCols(Matrix *pMatrix, int col1, int col2, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixAddCols \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return matrixAddRowsHelper(pMatrix, col1, col2, factor);
    }
    return matrixAddColsHelper(pMatrix, col1, col2, factor);
}

void matrixTranspose(Matrix *pMatrix, bool val)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixTranspose \n");
        return;
    }
    pMatrix->isTransposed = val;
}

bool matrixIsTransposed(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : the matrix is null | matrixIsTransposed \n");
        return false;
    }

    return pMatrix->isTransposed;
}

int matrixRows(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixRows \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return pMatrix->cols;
    }

    return pMatrix->rows;
}

int matrixCols(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixCols \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        return pMatrix->rows;
    }

    return pMatrix->cols;
}

bool matrixEquals(Matrix *pMatrix1, Matrix *pMatrix2)
{
    if (pMatrix1 == NULL || pMatrix2 == NULL)
    {
        printf("[ERROR] : a matrix is null | matrixEquals \n");
        return false;
    }

    if ((matrixCols(pMatrix1) != matrixCols(pMatrix2)) || (matrixRows(pMatrix1) != matrixRows(pMatrix2)))
    {
        return false;
    }

    for (int i = 0; i < matrixRows(pMatrix1); i++)
    {
        for (int j = 0; j < matrixCols(pMatrix1); j++)
        {
            if (matrixGetElement(pMatrix1, i, j) != matrixGetElement(pMatrix2, i, j))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix *matrixAdd(Matrix *pMatrix1, Matrix *pMatrix2)
{
    if (pMatrix1 == NULL || pMatrix2 == NULL)
    {
        printf("[ERROR] : a matrix is null | matrixAdd \n");
        return NULL;
    }

    if ((matrixCols(pMatrix1) != matrixCols(pMatrix2)) || (matrixRows(pMatrix1) != matrixRows(pMatrix2)))
    {
        printf("[ERROR] : both matrices need to have the same layout | matrixAdd \n");
        return NULL;
    }

    float *data = (float *)malloc(sizeof(float) * pMatrix1->cols * pMatrix1->rows);

    int counter = 0;

    for (int i = 0; i < matrixRows(pMatrix1); i++)
    {
        for (int j = 0; j < matrixCols(pMatrix1); j++)
        {
            data[counter] = matrixGetElement(pMatrix1, i, j) + matrixGetElement(pMatrix2, i, j);
            counter++;
        }
    }

    return matrixCreate(data, matrixRows(pMatrix1), matrixCols(pMatrix2));
}

Matrix *matrixSubtract(Matrix *pMatrix1, Matrix *pMatrix2)
{
    if (pMatrix1 == NULL || pMatrix2 == NULL)
    {
        printf("[ERROR] : a matrix is null | matrixSubtract \n");
        return NULL;
    }

    if ((matrixCols(pMatrix1) != matrixCols(pMatrix2)) || (matrixRows(pMatrix1) != matrixRows(pMatrix2)))
    {
        printf("[ERROR] : both matrices need to have the same layout | matrixSubtract \n");
        return NULL;
    }

    float *data = (float *)malloc(sizeof(float) * pMatrix1->cols * pMatrix1->rows);

    int counter = 0;

    for (int i = 0; i < matrixRows(pMatrix1); i++)
    {
        for (int j = 0; j < matrixCols(pMatrix1); j++)
        {
            data[counter] = matrixGetElement(pMatrix1, i, j) - matrixGetElement(pMatrix2, i, j);
            counter++;
        }
    }

    return matrixCreate(data, matrixRows(pMatrix1), matrixCols(pMatrix2));
}

Matrix *matrixScalarMult(Matrix *pMatrix, float scalar)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixScalarMult \n");
        return NULL;
    }

    float *data = (float *)malloc(sizeof(float) * pMatrix->cols * pMatrix->rows);

    for (int i = 0; i < pMatrix->rows * pMatrix->cols; i++)
    {
        data[i] = scalar * (pMatrix->data[i]);
    }

    return matrixCreate(data, pMatrix->rows, pMatrix->cols);
}

Matrix *matrixGauss(Matrix *a, Matrix *b)
{
    if (a == NULL)
    {
        printf("[ERROR] : m is null | matrixGauss \n");
        return NULL;
    }

    int rowsA = matrixRows(a);
    int colsA = matrixCols(a);
    int rowsB = 0;
    int colsB = 0;

    if (b != NULL)
    {
        rowsB = matrixRows(b);
        colsB = matrixCols(b);
    }

    if (rowsA != rowsB && b != NULL)
    {
        printf("[ERROR] : matrix a and b must have the same amount of rows | matrixGauss \n");
        return NULL;
    }

    Matrix *copyA = matrixCopy(a);
    Matrix *copyB = NULL;

    if (b != NULL)
    {
        copyB = matrixCopy(b);
    }

    int rowCounter = 0;

    for (int c = 0; c < colsA; c++)
    {

        float pValue = 0.0f;
        int row = 0;

        for (int r = rowCounter; r < rowsA; r++)
        {
            float value = matrixGetElement(copyA, r, c);

            if (pValue == 0.0f)
            {
                pValue = value;

                if (pValue == 0.0f)
                {
                    continue;
                }
                row = r;
                rowCounter++;
            }
            else if (value != 0)
            {
                float factor = -(value / pValue);
                matrixAddRows(copyA, r, row, factor);

                if (copyB != NULL)
                {
                    matrixAddRows(copyB, r, row, factor);
                }
            }
        }
        if (pValue == 0.0f)
        {
            printf("[INFO] : Matrix is inconsistent, infinite solutions | matrixGauss \n");
            matrixFree(copyA);
            matrixFree(copyB);
            return NULL;
        }
        if (pValue != 0.0f && row != (rowCounter - 1))
        {
            matrixSwapRows(copyA, row, rowCounter - 1);

            if (copyB != NULL)
            {
                matrixSwapRows(copyB, row, rowCounter - 1);
            }
        }
    }

    for (int i = rowCounter; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            if (matrixGetElement(copyB, i, j) != 0)
            {
                printf("[INFO] : Matrix is inconsistent, no solution | matrixGauss \n");
                matrixFree(copyA);
                matrixFree(copyB);
                return NULL;
            }
        }
    }

    for (int i = rowCounter - 1, j = colsA - 1; i >= 0, j >= 0; i--, j--)
    {
        float pValue = matrixGetElement(copyA, i, j);

        for (int k = i - 1; k >= 0; k--)
        {
            float value = matrixGetElement(copyA, k, j);

            float factor = -(value / pValue);
            matrixAddRows(copyA, k, i, factor);

            if (copyB != NULL)
            {
                matrixAddRows(copyB, k, i, factor);
            }
        }
        matrixScaleRow(copyA, i, 1/pValue);

        if(copyB != NULL){
            matrixScaleRow(copyB, i, 1/pValue);
        }
    }

    if(rowCounter == rowsA){
        matrixFree(copyA);
        return copyB;
    }

    Matrix *result = matrixDelRows(copyB, rowCounter, rowsB - 1);

    matrixFree(copyA);
    matrixFree(copyB);

    return result;
}

Matrix * matrixInverse(Matrix * a)
{
    if(a == NULL){
        printf("[ERROR] : matrix is null | matrixInverse \n");
        return NULL;
    }

    if(a->cols != a->rows){
        printf("[INFO] : matrix is not square | matrixInverse \n");
        return NULL;
    }

    Matrix *identity = matrixCreateIdentity(a->rows);

    Matrix *inverse = matrixGauss(a, identity);

    matrixFree(identity);

    if(inverse == NULL){
        printf("[INFO] : matrix is not nonsingular | matrixInverse \n");
        return NULL;
    }

    return inverse;
}

int matrixRank(Matrix * a)
{
    if(a == NULL){
        printf("[ERROR] : matrix is null | matrixRank \n");
        return -1;
    }

    int rowsA = matrixRows(a);
    int colsA = matrixCols(a);

    Matrix *copyA = matrixCopy(a);

    int rowCounter = 0;

    for (int c = 0; c < colsA; c++)
    {

        float pValue = 0.0f;
        int row = 0;

        for (int r = rowCounter; r < rowsA; r++)
        {
            float value = matrixGetElement(copyA, r, c);

            if (pValue == 0.0f)
            {
                pValue = value;

                if (pValue == 0.0f)
                {
                    continue;
                }
                row = r;
                rowCounter++;
            }
            else if (value != 0)
            {
                float factor = -(value / pValue);
                matrixAddRows(copyA, r, row, factor);
            }
        }
        if (pValue != 0.0f && row != (rowCounter - 1))
        {
            matrixSwapRows(copyA, row, rowCounter - 1);
        }
    }

    return rowCounter;
}

Matrix *matrixMult(Matrix *pMatrix1, Matrix *pMatrix2)
{
    if (pMatrix1 == NULL || pMatrix2 == NULL)
    {
        printf("[ERROR] : a matrix is null | matrixMult \n");
        return NULL;
    }

    if (matrixCols(pMatrix1) != matrixRows(pMatrix2))
    {
        printf("[ERROR] : the amount of columns of the first matrix and the amount of rows of the second matrix have to be equal | matrixMult \n");
        return NULL;
    }

    float *data = (float *)malloc(sizeof(float) * matrixRows(pMatrix1) * matrixCols(pMatrix2));

    for (int i = 0; i < matrixRows(pMatrix1); i++)
    {
        for (int j = 0; j < matrixCols(pMatrix2); j++)
        {
            float val = 0.0f;

            for (int k = 0; k < matrixCols(pMatrix1); k++)
            {
                val += matrixGetElement(pMatrix1, i, k) * matrixGetElement(pMatrix2, k, j);
            }

            int index = (i * matrixCols(pMatrix2)) + j;
            data[index] = val;
        }
    }

    return matrixCreate(data, matrixRows(pMatrix1), matrixCols(pMatrix2));
}

void *matrixCopy(void *pMatrix)
{
    Matrix *cp = (Matrix *)pMatrix;

    if (cp == NULL)
    {
        printf("[ERROR] : cp is null | matrixCopy \n");
        return NULL;
    }

    Matrix *copy = (Matrix *)malloc(sizeof(Matrix));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | matrixCopy \n");
        return NULL;
    }

    int dataSize = sizeof(float) * cp->rows * cp->cols;

    float *dataCopy = (float *)malloc(dataSize);

    if (dataCopy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | matrixCopy \n");
        return NULL;
    }

    memcpy(dataCopy, cp->data, dataSize);

    copy->data = dataCopy;
    copy->rows = cp->rows;
    copy->cols = cp->cols;
    copy->isTransposed = cp->isTransposed;

    return copy;
}

void matrixFree(void *pMatrix)
{
    Matrix *cp = (Matrix *)pMatrix;

    if (cp == NULL)
    {
        printf("[WARN] : Pointer to matrix is NULL | matrixFree \n");
        return;
    }

    free(cp->data);
    free(cp);

    cp = NULL;
}

void matrixDump(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDump \n");
        return;
    }

    for (int i = 0; i < matrixRows(pMatrix); i++)
    {
        for (int j = 0; j < matrixCols(pMatrix); j++)
        {
            printf("%f\t", matrixGetElement(pMatrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int matrixGetIndex(Matrix *pMatrix, int row, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetIndex \n");
        return -1;
    }

    if (pMatrix->isTransposed)
    {
        int temp = row;
        row = col;
        col = temp;
    }

    if (row < 0 || row >= pMatrix->rows || col < 0 || col >= pMatrix->cols)
    {
        printf("[INFO] : out of bounds | matrixGetIndex \n");
        return -1;
    }

    return (row * pMatrix->cols) + col;
}

Matrix *matrixGetRowHelper(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetRowHelper \n");
        return NULL;
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixGetRowHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRowHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->cols);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRowHelper \n");
        return NULL;
    }

    int index = matrixGetIndex(pMatrix, row, 0);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetRowHelper \n");
        return NULL;
    }

    float *src = pMatrix->data + index;
    int rowSize = sizeof(float) * pMatrix->cols;

    memcpy(pCopy, src, rowSize);

    pNew->data = pCopy;
    pNew->rows = 1;
    pNew->cols = pMatrix->cols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixGetColHelper(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetColHelper \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixGetColHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetColHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetColHelper \n");
        return NULL;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        int index = matrixGetIndex(pMatrix, i, col);

        if (index == -1)
        {
            printf("[ERROR] : function matrixGetIndex failed | matrixGetColHelper \n");
            return NULL;
        }

        memcpy(pCopy + i, pMatrix->data + index, sizeof(float));
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = 1;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixGetRowsHelper(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetRowsHelper \n");
        return NULL;
    }

    if ((row1 < 0 || row1 >= pMatrix->rows) || (row2 < 0 || row2 >= pMatrix->rows))
    {
        printf("[ERROR] : out of bounds | matrixGetRowsHelper \n");
        return NULL;
    }

    if (row1 > row2)
    {
        printf("[ERROR] : the index of the second row can not be higher than the first | matrixGetRowsHelper \n");
        return NULL;
    }

    int rowAmount = row2 - row1 + 1;

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRowsHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->cols * rowAmount);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRowsHelper \n");
        return NULL;
    }

    int index = matrixGetIndex(pMatrix, row1, 0);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetRowsHelper \n");
        return NULL;
    }

    float *src = pMatrix->data + index;
    int rowSize = sizeof(float) * pMatrix->cols * rowAmount;

    memcpy(pCopy, src, rowSize);

    pNew->data = pCopy;
    pNew->rows = rowAmount;
    pNew->cols = pMatrix->cols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixGetColsHelper(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetColsHelper \n");
        return NULL;
    }

    if ((col1 < 0 || col1 >= pMatrix->cols) || (col2 < 0 || col2 >= pMatrix->cols))
    {
        printf("[ERROR] : out of bounds | matrixGetColsHelper \n");
        return NULL;
    }

    if (col1 > col2)
    {
        printf("[ERROR] : the index of the second column can not be higher than the first | matrixGetColsHelper \n");
        return NULL;
    }

    int colAmount = col2 - col1 + 1;

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetColsHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows * colAmount);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetColsHelper \n");
        return NULL;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        int index = matrixGetIndex(pMatrix, i, col1);

        if (index == -1)
        {
            printf("[ERROR] : function matrixGetIndex failed | matrixGetColsHelper \n");
            return NULL;
        }

        memcpy(pCopy + i * colAmount, pMatrix->data + index, sizeof(float) * colAmount);
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = colAmount;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixDelRowHelper(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRowHelper \n");
        return NULL;
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixDelRowHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRowHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->cols * (pMatrix->rows - 1)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRowHelper \n");
        return NULL;
    }

    int index1 = 0;
    int length1 = row * pMatrix->cols;
    int index2 = matrixGetIndex(pMatrix, row + 1, 0);
    int length2 = (pMatrix->rows - (row + 1)) * pMatrix->cols;

    memcpy(pCopy, pMatrix->data + index1, length1 * sizeof(float));

    if (index2 != -1)
    {
        memcpy(pCopy + length1, pMatrix->data + index2, length2 * sizeof(float));
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows - 1;
    pNew->cols = pMatrix->cols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixDelColHelper(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelColHelper \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixDelColHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelColHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->rows * (pMatrix->cols - 1)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelColHelper \n");
        return NULL;
    }

    float *pCopyTemp = pCopy;

    memcpy(pCopyTemp, pMatrix->data, sizeof(float) * col);
    pCopyTemp = pCopyTemp + col;

    int newCols = pMatrix->cols - 1;
    int initPos = col + 1;
    int distance = pMatrix->cols;

    int copiedVals = col;

    for (int i = 0; i < pMatrix->rows - 1; i++)
    {
        memcpy(pCopyTemp, pMatrix->data + initPos + i * distance, sizeof(float) * newCols);
        pCopyTemp = pCopyTemp + newCols;

        copiedVals += newCols;
    }

    int remainingVals = pMatrix->rows * newCols - copiedVals;
    int lastIndex = pMatrix->rows - 1;
    memcpy(pCopyTemp, pMatrix->data + initPos + lastIndex * distance, remainingVals);

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = newCols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixDelRowsHelper(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRowsHelper \n");
        return NULL;
    }

    if ((row1 < 0 || row1 >= pMatrix->rows) || (row2 < 0 || row2 >= pMatrix->rows))
    {
        printf("[ERROR] : out of bounds | matrixDelRowsHelper \n");
        return NULL;
    }

    if (row1 > row2)
    {
        printf("[ERROR] : the index of the second row can not be higher than the first | matrixDelRowsHelper \n");
        return NULL;
    }

    int rowAmount = row2 - row1 + 1;

    if (rowAmount == pMatrix->rows)
    {
        printf("[ERROR] : It is not possible to delete all rows | matrixDelRowsHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRowsHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->cols * (pMatrix->rows - rowAmount)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRowsHelper \n");
        return NULL;
    }

    int index1 = 0;
    int length1 = row1 * pMatrix->cols;
    int index2 = matrixGetIndex(pMatrix, row1 + rowAmount, 0);
    int length2 = (pMatrix->rows - (row1 + rowAmount)) * pMatrix->cols;

    memcpy(pCopy, pMatrix->data + index1, length1 * sizeof(float));

    if (index2 != -1)
    {
        memcpy(pCopy + length1, pMatrix->data + index2, length2 * sizeof(float));
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows - rowAmount;
    pNew->cols = pMatrix->cols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

Matrix *matrixDelColsHelper(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelColsHelper \n");
        return NULL;
    }

    if ((col1 < 0 || col1 >= pMatrix->cols) || (col2 < 0 || col2 >= pMatrix->cols))
    {
        printf("[ERROR] : out of bounds | matrixDelColsHelper \n");
        return NULL;
    }

    if (col1 > col2)
    {
        printf("[ERROR] : the index of the second column can not be higher than the first | matrixDelColsHelper \n");
        return NULL;
    }

    int colAmount = col2 - col1 + 1;

    if (colAmount == pMatrix->cols)
    {
        printf("[ERROR] : It is not possible to delete all columns | matrixDelColsHelper \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelColsHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->rows * (pMatrix->cols - colAmount)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelColsHelper \n");
        return NULL;
    }

    float *pCopyTemp = pCopy;

    memcpy(pCopyTemp, pMatrix->data, sizeof(float) * col1);
    pCopyTemp = pCopyTemp + col1;

    int newCols = pMatrix->cols - colAmount;
    int initPos = col1 + colAmount;
    int distance = pMatrix->cols;

    int copiedVals = col1;

    for (int i = 0; i < pMatrix->rows - 1; i++)
    {
        memcpy(pCopyTemp, pMatrix->data + initPos + i * distance, sizeof(float) * newCols);
        pCopyTemp = pCopyTemp + newCols;

        copiedVals += newCols;
    }

    int remainingVals = pMatrix->rows * newCols - copiedVals;
    int lastIndex = pMatrix->rows - 1;
    memcpy(pCopyTemp, pMatrix->data + initPos + lastIndex * distance, remainingVals);

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = newCols;
    pNew->isTransposed = pMatrix->isTransposed;

    return pNew;
}

float *matrixGetDataRowHelper(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetDataRowHelper \n");
        return NULL;
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixGetDataRowHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->cols);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetDataRowHelper \n");
        return NULL;
    }

    int index = matrixGetIndex(pMatrix, row, 0);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetDataRowHelper \n");
        return NULL;
    }

    float *src = pMatrix->data + index;
    int rowSize = sizeof(float) * pMatrix->cols;

    memcpy(pCopy, src, rowSize);

    return pCopy;
}

float *matrixGetDataColHelper(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetDataColHelper \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixGetDataColHelper \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetDataColHelper \n");
        return NULL;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        int index = matrixGetIndex(pMatrix, i, col);

        if (index == -1)
        {
            printf("[ERROR] : function matrixGetIndex failed | matrixGetDataColHelper \n");
            return NULL;
        }

        memcpy(pCopy + i, pMatrix->data + index, sizeof(float));
    }

    return pCopy;
}

int matrixSwapRowsHelper(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixSwapRowsHelper \n");
        return -1;
    }

    if (row1 < 0 || row1 >= pMatrix->rows || row2 < 0 || row2 >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixSwapRowsHelper \n");
        return -1;
    }

    float *pRow1 = pMatrix->data + (pMatrix->cols * row1);
    float *pRow2 = pMatrix->data + (pMatrix->cols * row2);

    for (int i = 0; i < pMatrix->cols; i++)
    {
        float temp = pRow1[i];
        pRow1[i] = pRow2[i];
        pRow2[i] = temp;
    }

    return 0;
}

int matrixSwapColsHelper(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixSwapColsHelper \n");
        return -1;
    }

    if (col1 < 0 || col1 >= pMatrix->cols || col2 < 0 || col2 >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixSwapColsHelper \n");
        return -1;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        float temp = pMatrix->data[((pMatrix->cols * i) + col1)];
        pMatrix->data[((pMatrix->cols * i) + col1)] = pMatrix->data[((pMatrix->cols * i) + col2)];
        pMatrix->data[((pMatrix->cols * i) + col2)] = temp;
    }

    return 0;
}

int matrixScaleRowHelper(Matrix *pMatrix, int row, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixScaleRowHelper \n");
        return -1;
    }

    if (factor == 0.0f)
    {
        printf("[ERROR] : the factor can not be null | matrixScaleRowHelper \n");
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixScaleRowHelper \n");
        return -1;
    }

    float *pRow = pMatrix->data + (pMatrix->cols * row);

    for (int i = 0; i < pMatrix->cols; i++)
    {
        pRow[i] *= factor;
    }

    return 0;
}

int matrixScaleColHelper(Matrix *pMatrix, int col, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixScaleColHelper \n");
        return -1;
    }

    if (factor == 0.0f)
    {
        printf("[ERROR] : the factor can not be null | matrixScaleColHelper \n");
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixScaleColHelper \n");
        return -1;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        pMatrix->data[((pMatrix->cols * i) + col)] *= factor;
    }

    return 0;
}

int matrixAddRowsHelper(Matrix *pMatrix, int row1, int row2, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixAddRowsHelper \n");
        return -1;
    }

    if (row1 < 0 || row1 >= pMatrix->rows || row2 < 0 || row2 >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixAddRowsHelper \n");
        return -1;
    }

    float *pRow1 = pMatrix->data + (pMatrix->cols * row1);
    float *pRow2 = pMatrix->data + (pMatrix->cols * row2);

    for (int i = 0; i < pMatrix->cols; i++)
    {
        pRow1[i] += pRow2[i] * factor;
    }

    return 0;
}

int matrixAddColsHelper(Matrix *pMatrix, int col1, int col2, float factor)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : matrix is null | matrixAddColsHelper \n");
        return -1;
    }

    if (col1 < 0 || col1 >= pMatrix->cols || col2 < 0 || col2 >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixAddColsHelper \n");
        return -1;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        pMatrix->data[((pMatrix->cols * i) + col1)] += pMatrix->data[((pMatrix->cols * i) + col2)] * factor;
    }

    return 0;
}