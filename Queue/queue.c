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
        printf("[ERROR] : Memory allocation failed | queueCreate \n");
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

    pQueue->length++;

    return 0;
}

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
        printf("[ERROR] : Function doublyLinkedListRemove failed | queuePop \n");
        free(value);
        return NULL;
    }

    pQueue->length--;

    return value;
}

void *queuePeek(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queuePeek \n");
        return NULL;
    }

    if (pQueue->length == 0)
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

int queueLength(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueLength \n");
        return -1;
    }

    return pQueue->length;
}

int queueSize(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueSize \n");
        return -1;
    }

    return doublyLinkedListSize(pQueue->list);
}

void queueFree(Queue *pQueue)
{
    doublyLinkedListFree(pQueue->list);

    free(pQueue);
}
