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




















int upHeapify(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | upHeapify \n");
        return -1;
    }

    int length = heapLength(pHeap);
    int index = length - 1;

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
