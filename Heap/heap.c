#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../List/list.h"
#include "heap.h"

typedef struct Heap
{
    List *listValue;
    List *listComp;
    int length;
    int size;
    bool isMaxHeap;
} Heap;

int upHeapify(Heap *pHeap);
int downHeapify(Heap *pHeap);
int getParent(int i);
int getSibling(Heap *pHeap, int i);
int getChildLeft(Heap *pHeap, int i);
int getChildRight(Heap *pHeap, int i);

Heap *heapCreate(int size, bool isMaxHeap)
{
    Heap *pHeap = (Heap *)malloc(sizeof(Heap));

    if (pHeap == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    List *pListValue = listCreate(size);

    if (pListValue == NULL)
    {
        free(pHeap);
        printf("Memory allocation failed!\n");
        return NULL;
    }

    List *pListComp = listCreate(sizeof(int));

    if (pListComp == NULL)
    {
        listFree(pListValue);
        free(pHeap);
        printf("Memory allocation failed!\n");
        return NULL;
    }

    pHeap->listValue = pListValue;
    pHeap->listComp = pListComp;
    pHeap->size = size;
    pHeap->length = 0;
    pHeap->isMaxHeap = isMaxHeap;

    return pHeap;
}

int heapAdd(Heap *pHeap, void *value, int comparator)
{
    int st1 = listAdd(pHeap->listValue, value);
    int st2 = listAdd(pHeap->listComp, &comparator);

    if (st1 == -1 || st2 == -1)
    {
        printf("[ERROR] : heap insert failed!\n");
        return -1;
    }

    pHeap->length++;

    int st3 = upHeapify(pHeap);

    if (st3 == -1)
    {
        printf("[ERROR] : upheapify failed!\n");
        return -1;
    }

    return 0;
}

int heapRemove(Heap *pHeap)
{
    if(pHeap->length == 0){
        return 0;
    }

    if(pHeap->length == 1){
        listRemove(pHeap->listValue, 0);
        listRemove(pHeap->listComp, 0);

        pHeap->length--;
        return 0;
    }

    int st1 = listSwap(pHeap->listValue, 0, pHeap->length - 1);
    int st2 = listSwap(pHeap->listComp, 0, pHeap->length - 1);
    int st3 = listRemove(pHeap->listValue, pHeap->length - 1);
    int st4 = listRemove(pHeap->listComp, pHeap->length - 1);

    if (st1 == -1 || st2 == -1 || st3 == -1 || st4 == -1)
    {
        printf("[ERROR] : heap removal failed!\n");
        return -1;
    }

    pHeap->length--;

    int st5 = downHeapify(pHeap);

    if (st5 == -1)
    {
        printf("[ERROR] : upheapify failed!\n");
        return -1;
    }

    return 0;
}

void *heapGetRoot(Heap *pHeap)
{
    if(pHeap->length == 0){
        return NULL;
    }

    void *value = listGet(pHeap->listValue, 0);

    return value;
}

int heapLength(Heap *pHeap)
{
    return pHeap->length;
}

int heapSize(Heap *pHeap)
{
    return pHeap->size;
}

void heapFree(Heap *pHeap)
{
    listFree(pHeap->listValue);
    listFree(pHeap->listComp);

    free(pHeap);
}

int upHeapify(Heap *pHeap)
{
    int index = pHeap->length - 1;

    while (index != 0)
    {
        int iParent = getParent(index);
        int *parent = listGet(pHeap->listComp, iParent);
        int *cp = listGet(pHeap->listComp, index);

        if (parent == NULL || cp == NULL)
        {
            printf("[Error] : parent can not be null!\n");
            return -1;
        }

        bool isBreak = false;

        if (pHeap->isMaxHeap == true)
        {
            if (*parent < *cp)
            {
                listSwap(pHeap->listValue, index, iParent);
                listSwap(pHeap->listComp, index, iParent);
            }
            else
            {
                isBreak = true;
            }
        }
        else
        {
            if (*parent > *cp)
            {
                listSwap(pHeap->listValue, index, iParent);
                listSwap(pHeap->listComp, index, iParent);
            }
            else
            {
                isBreak = true;
            }
        }

        free(parent);
        free(cp);

        if (isBreak)
        {
            break;
        }
        index = iParent;
    }
    return 0;
}

int downHeapify(Heap *pHeap)
{
    int index = 0;
    int iLeftChild = getChildLeft(pHeap, index);
    int iRightChild = getChildRight(pHeap, index);

    while (iLeftChild != -1)
    {

        int *parent = listGet(pHeap->listComp, index);
        int *leftChild = listGet(pHeap->listComp, iLeftChild);
        int *rightChild = NULL;
        if(iRightChild != -1){
            rightChild = listGet(pHeap->listComp, iRightChild);
        }

        int *bigSibling = leftChild;
        int iBigSibling = iLeftChild;
        int *smallSibling = leftChild;
        int iSmallSibling = iLeftChild;

        if (rightChild != NULL && *rightChild > *leftChild)
        {
            bigSibling = rightChild;
            iBigSibling = iRightChild;
        }

        if (rightChild != NULL && *rightChild <= *leftChild)
        {
            smallSibling = rightChild;
            iSmallSibling = iRightChild;
        }

        if (parent == NULL || leftChild == NULL)
        {
            printf("[Error] : pointers can not be null!\n");
            return -1;
        }

        bool isBreak = false;

        if (pHeap->isMaxHeap == true)
        {
            if (*parent < *bigSibling)
            {
                listSwap(pHeap->listValue, index, iBigSibling);
                listSwap(pHeap->listComp, index, iBigSibling);

                index = iBigSibling;
                iLeftChild = getChildLeft(pHeap, index);
                iRightChild = getChildRight(pHeap, index);
            }
            else
            {
                isBreak = true;
            }
        }
        else
        {
            if (*parent > *smallSibling)
            {
                listSwap(pHeap->listValue, index, iSmallSibling);
                listSwap(pHeap->listComp, index, iSmallSibling);

                index = iSmallSibling;
                iLeftChild = getChildLeft(pHeap, index);
                iRightChild = getChildRight(pHeap, index);
            }
            else
            {
                isBreak = true;
            }
        }

        free(parent);
        free(leftChild);
        free(rightChild);

        if (isBreak)
        {
            break;
        }
    }
    return 0;
}

int getParent(int i)
{
    int index = (i - 1) / 2;

    if (index < 0)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

int getSibling(Heap *pHeap, int i)
{
    int index;

    if (i % 2 == 0)
    {
        index = i - 1;
    }
    else
    {
        index = i + 1;
    }

    if (index <= 0 || index >= pHeap->length)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

int getChildLeft(Heap *pHeap, int i)
{
    int index = (2 * i) + 1;

    if (index <= 0 || index >= pHeap->length)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

int getChildRight(Heap *pHeap, int i)
{
    int index = (2 * i) + 2;

    if (index <= 0 || index >= pHeap->length)
    {
        return -1;
    }
    else
    {
        return index;
    }
}
