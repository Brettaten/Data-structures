#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"
#include "../DoublyLinkedList/doublyLinkedList.h"

typedef struct Queue
{
    DoublyLinkedList *list;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} Queue;


Queue *queueCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *))
{
    Queue *pQueue = (Queue *)malloc(sizeof(Queue));

    if (pQueue == NULL)
    {
        printf("[ERROR] : Memory allocation failed | queueCreate \n");
        return NULL;
    }

    DoublyLinkedList *pList = doublyLinkedListCreate(size, copyElement, freeElement);
    pQueue->list = pList;
    pQueue->copyElement = copyElement;
    pQueue->freeElement = freeElement;

    return pQueue;
}
