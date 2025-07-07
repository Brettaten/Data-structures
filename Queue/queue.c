#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"
#include "../DoublyLinkedList/doublyLinkedList.h"

typedef struct Queue
{
    DoublyLinkedList *list;
    int size;
    int length;
} Queue;

Queue *queueCreate(int size)
{
    Queue *pQueue = (Queue *)malloc(sizeof(Queue));

    if (pQueue == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    DoublyLinkedList *pList = doublyLinkedListCreate(size);
    pQueue->list = pList;
    pQueue->size = size;
    pQueue->length = 0;

    return pQueue;
}

int queuePush(Queue *pQueue, void *value)
{
    int st1 = doublyLinkedListAdd(pQueue->list, value);

    if (st1 == -1)
    {
        return -1;
    }

    pQueue->length++;

    return 0;
}

void *queuePop(Queue *pQueue)
{
    void *value = queuePeek(pQueue);

    if (value == NULL)
    {
        return NULL;
    }

    int st1 = doublyLinkedListRemove(pQueue->list, 0);

    if (st1 == -1)
    {
        free(value);
        return NULL;
    }

    pQueue->length--;

    return value;
}

void *queuePeek(Queue *pQueue)
{
    if (pQueue->list == 0)
    {
        printf("List is empty!");
        return NULL;
    }

    void *value = doublyLinkedListGet(pQueue->list, 0);

    if (value == NULL)
    {
        return NULL;
    }

    return value;
}

int queueLength(Queue *pQueue)
{
    return pQueue->length;
}

int queueSize(Queue *pQueue)
{
    return doublyLinkedListSize(pQueue->list);
}

void queueFree(Queue *pQueue)
{
    doublyLinkedListFree(pQueue->list);

    free(pQueue);
}
