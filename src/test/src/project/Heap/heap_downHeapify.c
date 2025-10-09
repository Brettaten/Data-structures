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
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
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
