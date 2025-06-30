#include <stdlib.h>

#include "queue.h"
#include "list.h";

typedef struct Queue{
    List *list;
    int length;
} Queue;

Queue *queueCreate()
{
    Queue *pQueue = (Queue*) malloc(sizeof(Queue));

    if(pQueue == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    List *pList = listCreate();
    pQueue->list = pList;
    pQueue->length = 0;

    return pQueue;
}

void queuePush(Queue *pQueue, void *value)
{
    listAdd(pQueue->list, value);
    pQueue->length++;
}

void *queuePop(Queue *pQueue)
{
    if(listLength(pQueue->list) == 0){
        return NULL;
    }

    void* value = listGet(pQueue->list, 0);
    listSet(pQueue->list, NULL, 0);
    listRemove(pQueue->list, 0);
    pQueue->length--;

    return value;
}

int queueLength(Queue *pQueue)
{
    return pQueue->length;
}

void queueFree(Queue *pQueue)
{
}
