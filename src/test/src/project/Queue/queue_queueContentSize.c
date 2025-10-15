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














int queueContentSize(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueSize \n");
        return -1;
    }

    return doublyLinkedListSize(pQueue->list);
}
