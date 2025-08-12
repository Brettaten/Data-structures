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

/**
 * Function used to sort the heap upwards
 *
 * @param pHeap the pointer to the heap
 *
 * @return Success: 0 | Failure: -1
 */
int upHeapify(Heap *pHeap);

/**
 * Function used to sort the heap downwards
 *
 * @param pHeap the pointer to the heap
 *
 * @return Success: 0 | Failure: -1
 */
int downHeapify(Heap *pHeap);

/**
 * Function used to get the parent's index from the passed index
 *
 * @param i the index
 *
 * @return Success: the index | Failure: -1
 */
int getParent(int i);

/**
 * Function used to get the sibling's index from the passed index
 *
 * @param pHeap the pointer to the heap
 * @param i the index
 *
 * @return Success: the index | Failure: -1
 */
int getSibling(Heap *pHeap, int i);

/**
 * Function used to get the left child's index from the passed index
 *
 * @param pHeap the pointer to the heap
 * @param i the index
 *
 * @return Success: the index | Failure: -1
 */
int getChildLeft(Heap *pHeap, int i);

/**
 * Function used to get the right child's index from the passed index
 *
 * @param pHeap the pointer to the heap
 * @param i the index
 *
 * @return Success: the index | Failure: -1
 */
int getChildRight(Heap *pHeap, int i);

Heap *heapCreate(int size, bool isMaxHeap)
{
    Heap *pHeap = (Heap *)malloc(sizeof(Heap));

    if (pHeap == NULL)
    {
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
        return NULL;
    }

    List *pListValue = listCreate(size);

    if (pListValue == NULL)
    {
        free(pHeap);
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
        return NULL;
    }

    List *pListComp = listCreate(sizeof(int));

    if (pListComp == NULL)
    {
        listFree(pListValue);
        free(pHeap);
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
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
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapAdd \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : value is null | heapAdd \n");
        return -1;
    }

    int st1 = listAdd(pHeap->listValue, value);
    int st2 = listAdd(pHeap->listComp, &comparator);

    if (st1 == -1 || st2 == -1)
    {
        printf("[ERROR] : heap insert failed! | heapAdd \n");
        return -1;
    }

    pHeap->length++;

    int st3 = upHeapify(pHeap);

    if (st3 == -1)
    {
        printf("[ERROR] : upheapify failed! | heapAdd \n");
        return -1;
    }

    return 0;
}

int heapRemove(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapRemove \n");
        return -1;
    }

    if (pHeap->length == 0)
    {
        printf("[INFO] : heap is empty | heapRemove \n");
        return 0;
    }

    if (pHeap->length == 1)
    {
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
        printf("[ERROR] : heap removal failed! | heapRemove \n");
        return -1;
    }

    pHeap->length--;

    int st5 = downHeapify(pHeap);

    if (st5 == -1)
    {
        printf("[ERROR] : upheapify failed! | heapRemove \n");
        return -1;
    }

    return 0;
}

void *heapGetRoot(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapGetRoot \n");
        return NULL;
    }

    if (pHeap->length == 0)
    {
        printf("[INFO] : heap is empty | heapGetRoot \n");
        return NULL;
    }

    void *value = listGet(pHeap->listValue, 0);

    return value;
}

int heapLength(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapLength \n");
        return -1;
    }

    return pHeap->length;
}

int heapSize(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapSize \n");
        return -1;
    }

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
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | upHeapify \n");
        return -1;
    }

    int index = pHeap->length - 1;

    while (index != 0)
    {
        int iParent = getParent(index);
        int *parent = listGet(pHeap->listComp, iParent);
        int *cp = listGet(pHeap->listComp, index);

        if (parent == NULL || cp == NULL)
        {
            printf("[Error] : parent can not be null! | upHeapify \n");
            return -1;
        }

        bool isBreak = false;

        if (pHeap->isMaxHeap == true)
        {
            if (*parent < *cp)
            {
                int st1 = listSwap(pHeap->listValue, index, iParent);
                int st2 = listSwap(pHeap->listComp, index, iParent);

                if (st1 == -1 || st2 == -1)
                {
                    printf("[ERROR] : function listSwap failed | upHeapify \n");
                    return -1;
                }
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
                int st3 = listSwap(pHeap->listValue, index, iParent);
                int st4 = listSwap(pHeap->listComp, index, iParent);

                if (st3 == -1 || st4 == -1)
                {
                    printf("[ERROR] : function listSwap failed | upHeapify \n");
                    return -1;
                }
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
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | downHeapify \n");
        return -1;
    }

    int index = 0;
    int iLeftChild = getChildLeft(pHeap, index);
    int iRightChild = getChildRight(pHeap, index);

    while (iLeftChild != -1)
    {

        int *parent = listGet(pHeap->listComp, index);
        int *leftChild = listGet(pHeap->listComp, iLeftChild);
        int *rightChild = NULL;
        if (iRightChild != -1)
        {
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
            printf("[Error] : pointers can not be null! | downHeapify\n");
            return -1;
        }

        bool isBreak = false;

        if (pHeap->isMaxHeap == true)
        {
            if (*parent < *bigSibling)
            {
                int st1 = listSwap(pHeap->listValue, index, iBigSibling);
                int st2 = listSwap(pHeap->listComp, index, iBigSibling);

                if (st1 == -1 || st2 == -1)
                {
                    printf("[ERROR] : function listSwap failed | downHeapify \n");
                    return -1;
                }

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
                int st3 = listSwap(pHeap->listValue, index, iSmallSibling);
                int st4 = listSwap(pHeap->listComp, index, iSmallSibling);

                if (st3 == -1 || st4 == -1)
                {
                    printf("[ERROR] : function listSwap failed | downHeapify \n");
                    return -1;
                }

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
    if (pHeap == NULL)
    {
        printf("[ERROR] : heap is null | getSibling \n");
        return -1;
    }

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
    if (pHeap == NULL)
    {
        printf("[ERROR] : heap is null | getChildLeft \n");
        return -1;
    }

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
    if (pHeap == NULL)
    {
        printf("[ERROR] : heap is null | getChildRight \n");
        return -1;
    }

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
