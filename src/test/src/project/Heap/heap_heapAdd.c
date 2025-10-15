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

    int st3 = upHeapify(pHeap);

    if (st3 == -1)
    {
        printf("[ERROR] : upheapify failed! | heapAdd \n");
        return -1;
    }

    return 0;
}
