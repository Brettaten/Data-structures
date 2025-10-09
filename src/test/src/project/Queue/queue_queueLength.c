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












int queueLength(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueLength \n");
        return -1;
    }

    return doublyLinkedListLength(pQueue->list);
}
