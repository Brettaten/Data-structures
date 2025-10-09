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










void *heapCopy(void *pHeap)
{
    Heap *cp = (Heap *) pHeap;

    if(cp == NULL){
        printf("[ERROR] : Heap is null | heapCopy \n");
        return NULL;
    }

    Heap *copy = (Heap *) malloc(sizeof(Heap));

    if(copy == NULL){
        printf("[ERROR] : Memory allocation failed | heapCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;
    copy->isMaxHeap = cp->isMaxHeap;

    List *copyListValue = (List *) listCopy(cp->listValue);

    if(copyListValue == NULL){
        printf("[ERROR] : Function listCopy failed | heapCopy \n");
        return NULL;
    }

        List *copyListComp = (List *) listCopy(cp->listComp);

    if(copyListComp == NULL){
        printf("[ERROR] : Function listCopy failed | heapCopy \n");
        return NULL;
    }

    copy->listValue = copyListValue;
    copy->listComp = copyListComp;

    return copy;
}
