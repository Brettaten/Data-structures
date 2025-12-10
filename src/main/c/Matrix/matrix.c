#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

typedef struct Matrix
{
    float *data;
    int rows;
    int cols;
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

Matrix *matrixCreate(float *data, int rows, int cols)
{
    if (data == NULL)
    {
        printf("[ERROR] : data can not be null | matrixCreate \n");
        return NULL;
    }
    if (rows <= 1 || cols <= 1)
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

    return pMatrix;
}

float matrixGetElement(Matrix *pMatrix, int row, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetElement \n");
        return -1.0f;
    }

    if (row < 0 || row >= pMatrix->rows || col < 0 || col >= pMatrix->cols)
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

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixGetRow \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRow \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->cols);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRow \n");
        return NULL;
    }

    int index = matrixGetIndex(pMatrix, row, 0);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetRow \n");
        return NULL;
    }

    float *src = pMatrix->data + index;
    int rowSize = sizeof(float) * pMatrix->cols;

    memcpy(pCopy, src, rowSize);

    pNew->data = pCopy;
    pNew->rows = 1;
    pNew->cols = pMatrix->cols;

    return pNew;
}

Matrix *matrixGetCol(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetCol \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixGetCol \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetCol \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetCol \n");
        return NULL;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        int index = matrixGetIndex(pMatrix, i, col);

        if (index == -1)
        {
            printf("[ERROR] : function matrixGetIndex failed | matrixGetCol \n");
            return NULL;
        }

        memcpy(pCopy + i, pMatrix->data + index, sizeof(float));
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = 1;

    return pNew;
}

Matrix *matrixGetRows(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetRows \n");
        return NULL;
    }

    if ((row1 < 0 || row1 >= pMatrix->rows) || (row2 < 0 || row2 >= pMatrix->rows))
    {
        printf("[ERROR] : out of bounds | matrixGetRows \n");
        return NULL;
    }

    if (row1 > row2)
    {
        printf("[ERROR] : the index of the second row can not be higher than the first | matrixGetRows \n");
        return NULL;
    }

    int rowAmount = row2 - row1 + 1;

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRows \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->cols * rowAmount);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetRows \n");
        return NULL;
    }

    int index = matrixGetIndex(pMatrix, row1, 0);

    if (index == -1)
    {
        printf("[ERROR] : function matrixGetIndex failed | matrixGetRows \n");
        return NULL;
    }

    float *src = pMatrix->data + index;
    int rowSize = sizeof(float) * pMatrix->cols * rowAmount;

    memcpy(pCopy, src, rowSize);

    pNew->data = pCopy;
    pNew->rows = rowAmount;
    pNew->cols = pMatrix->cols;

    return pNew;
}

Matrix *matrixGetCols(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetCols \n");
        return NULL;
    }

    if ((col1 < 0 || col1 >= pMatrix->cols) || (col2 < 0 || col2 >= pMatrix->cols))
    {
        printf("[ERROR] : out of bounds | matrixGetCols \n");
        return NULL;
    }

    if (col1 > col2)
    {
        printf("[ERROR] : the index of the second column can not be higher than the first | matrixGetCols \n");
        return NULL;
    }

    int colAmount = col2 - col1 + 1;

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetCols \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * pMatrix->rows * colAmount);

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixGetCols \n");
        return NULL;
    }

    for (int i = 0; i < pMatrix->rows; i++)
    {
        int index = matrixGetIndex(pMatrix, i, col1);

        if (index == -1)
        {
            printf("[ERROR] : function matrixGetIndex failed | matrixGetCols \n");
            return NULL;
        }

        memcpy(pCopy + i * colAmount, pMatrix->data + index, sizeof(float) * colAmount);
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = colAmount;

    return pNew;
}

Matrix *matrixDelRow(Matrix *pMatrix, int row)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRow \n");
        return NULL;
    }

    if (row < 0 || row >= pMatrix->rows)
    {
        printf("[ERROR] : out of bounds | matrixDelRow \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRow \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->cols * (pMatrix->rows - 1)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRow \n");
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

    return pNew;
}

Matrix *matrixDelCol(Matrix *pMatrix, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelCol \n");
        return NULL;
    }

    if (col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixDelCol \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelCol \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->rows * (pMatrix->cols - 1)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelCol \n");
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

    return pNew;
}

Matrix *matrixDelRows(Matrix *pMatrix, int row1, int row2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelRows \n");
        return NULL;
    }

    if ((row1 < 0 || row1 >= pMatrix->rows) || (row2 < 0 || row2 >= pMatrix->rows))
    {
        printf("[ERROR] : out of bounds | matrixDelRows \n");
        return NULL;
    }

    if (row1 > row2)
    {
        printf("[ERROR] : the index of the second row can not be higher than the first | matrixDelRows \n");
        return NULL;
    }

    int rowAmount = row2 - row1 + 1;

    if (rowAmount == pMatrix->rows)
    {
        printf("[ERROR] : It is not possible to delete all rows | \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRows \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->cols * (pMatrix->rows - rowAmount)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelRows \n");
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

    return pNew;
}

Matrix *matrixDelCols(Matrix *pMatrix, int col1, int col2)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixDelCols \n");
        return NULL;
    }

    if ((col1 < 0 || col1 >= pMatrix->cols) || (col2 < 0 || col2 >= pMatrix->cols))
    {
        printf("[ERROR] : out of bounds | matrixDelCols \n");
        return NULL;
    }

    if (col1 > col2)
    {
        printf("[ERROR] : the index of the second column can not be higher than the first | matrixDelCols \n");
        return NULL;
    }

    int colAmount = col2 - col1 + 1;

    if (colAmount == pMatrix->cols)
    {
        printf("[ERROR] : It is not possible to delete all columns | \n");
        return NULL;
    }

    Matrix *pNew = (Matrix *)malloc(sizeof(Matrix));

    if (pNew == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelCols \n");
        return NULL;
    }

    float *pCopy = (float *)malloc(sizeof(float) * (pMatrix->rows * (pMatrix->cols - colAmount)));

    if (pCopy == NULL)
    {
        printf("[ERROR] : memory allocation failed | matrixDelCols \n");
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

    return pNew;
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

int matrixGetIndex(Matrix *pMatrix, int row, int col)
{
    if (pMatrix == NULL)
    {
        printf("[ERROR] : pMatrix is null | matrixGetIndex \n");
        return -1;
    }

    if (row < 0 || row >= pMatrix->rows || col < 0 || col >= pMatrix->cols)
    {
        printf("[ERROR] : out of bounds | matrixGetIndex \n");
        return -1;
    }

    return (row * pMatrix->cols) + col;
}
