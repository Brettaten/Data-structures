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

    int length = heapLength(pHeap);
    if (index <= 0 || index >= length)
    {
        return -1;
    }
    else
    {
        return index;
    }
}
