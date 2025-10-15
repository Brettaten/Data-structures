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








void *queuePeek(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queuePeek \n");
        return NULL;
    }

    int length = queueLength(pQueue);
    if (length == 0)
    {
        printf("[INFO] : List is empty | queuePeek \n");
        return NULL;
    }

    void *value = doublyLinkedListGet(pQueue->list, 0);

    if (value == NULL)
    {
        printf("[ERROR] : Function doublyLinkedListGet failed | queuePeek \n");
        return NULL;
    }

    return value;
}
