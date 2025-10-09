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


Heap *heapCreate(int size, bool isMaxHeap, void *(*copyElement)(void *), void (*freeElement)(void *))
{
    Heap *pHeap = (Heap *)malloc(sizeof(Heap));

    if (pHeap == NULL)
    {
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
        return NULL;
    }

    List *pListValue = listCreate(size, copyElement, freeElement);

    if (pListValue == NULL)
    {
        free(pHeap);
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
        return NULL;
    }

    List *pListComp = listCreate(sizeof(int), NULL, NULL);

    if (pListComp == NULL)
    {
        listFree(pListValue);
        free(pHeap);
        printf("[ERROR] : Memory allocation failed! | heapCreate \n");
        return NULL;
    }

    pHeap->listValue = pListValue;
    pHeap->listComp = pListComp;
    pHeap->copyElement = copyElement;
    pHeap->freeElement = freeElement;
    pHeap->isMaxHeap = isMaxHeap;

    return pHeap;
}
