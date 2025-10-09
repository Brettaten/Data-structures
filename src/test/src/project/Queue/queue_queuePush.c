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




int queuePush(Queue *pQueue, void *value)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queuePush \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to the value is null | queuePush \n");
        return -1;
    }

    int st1 = doublyLinkedListAdd(pQueue->list, value);

    if (st1 == -1)
    {
        printf("[ERROR] : Function doublyLinkedListAdd failed | queuePush \n");
        return -1;
    }

    return 0;
}
