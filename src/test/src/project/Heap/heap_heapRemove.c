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






int heapRemove(Heap *pHeap)
{
    if (pHeap == NULL)
    {
        printf("[WARN] : heap is null | heapRemove \n");
        return -1;
    }

    int length = heapLength(pHeap);
    if (length == 0)
    {
        printf("[INFO] : heap is empty | heapRemove \n");
        return 0;
    }

    if (length == 1)
    {
        listRemove(pHeap->listValue, 0);
        listRemove(pHeap->listComp, 0);

        return 0;
    }

    length = heapLength(pHeap);

    int st1 = listSwap(pHeap->listValue, 0, length - 1);
    int st2 = listSwap(pHeap->listComp, 0, length - 1);
    int st3 = listRemove(pHeap->listValue, length - 1);
    int st4 = listRemove(pHeap->listComp, length - 1);

    if (st1 == -1 || st2 == -1 || st3 == -1 || st4 == -1)
    {
        printf("[ERROR] : heap removal failed! | heapRemove \n");
        return -1;
    }

    int st5 = downHeapify(pHeap);

    if (st5 == -1)
    {
        printf("[ERROR] : upheapify failed! | heapRemove \n");
        return -1;
    }

    return 0;
}
