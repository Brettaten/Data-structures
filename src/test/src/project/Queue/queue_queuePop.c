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






void *queuePop(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queuePop \n");
        return NULL;
    }

    void *value = queuePeek(pQueue);

    if (value == NULL)
    {
        printf("[ERROR] : Function queuePeek failed | queuePop \n");
        return NULL;
    }

    int st1 = doublyLinkedListRemove(pQueue->list, 0);

    if (st1 == -1)
    {
        if(pQueue->freeElement == NULL){
            free(value);
        }
        else{
            pQueue->freeElement(value);
        }

        printf("[ERROR] : Function doublyLinkedListRemove failed | queuePop \n");
        return NULL;
    }

    return value;
}
