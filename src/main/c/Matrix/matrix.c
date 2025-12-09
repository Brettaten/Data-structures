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

        pCopy[i] = pMatrix->data[index];
    }

    pNew->data = pCopy;
    pNew->rows = pMatrix->rows;
    pNew->cols = 1;

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
    int index2 = (row * pMatrix->cols) + pMatrix->cols;
    int length2 = (pMatrix->rows - (row + 1)) * pMatrix->cols;

    memcpy(pCopy, pMatrix->data + index1, length1 * sizeof(float));

    if (length2 > 0)
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

    for(int i = 0; i < pMatrix->rows - 1; i++){
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
