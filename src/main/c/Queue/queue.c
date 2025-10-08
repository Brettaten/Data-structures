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

void *queueCopy(void *pQueue)
{
    Queue *cp = (Queue *) pQueue;

    if(cp == NULL){
        printf("[ERROR] : Queue is null | queueCopy \n");
        return NULL;
    }

    Queue *copy = (Queue *) malloc(sizeof(Queue));

    if(copy == NULL){
        printf("[ERROR] : Memory allocation failed | queueCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;

    DoublyLinkedList *copyList = (DoublyLinkedList *) doublyLinkedListCopy(cp->list);

    if(copyList == NULL){
        printf("[ERROR] : Function doublyLinkedListCopy failed | queueCopy \n");
        return NULL;
    }

    copy->list = copyList;

    return copy;
}

int queueLength(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueLength \n");
        return -1;
    }

    return doublyLinkedListLength(pQueue->list);
}

int queueContentSize(Queue *pQueue)
{
    if (pQueue == NULL)
    {
        printf("[WARN] : Pointer to the queue is null | queueSize \n");
        return -1;
    }

    return doublyLinkedListSize(pQueue->list);
}

int queueSize(){
    return sizeof(Queue);
}

void queueFree(void *pQueue)
{
    Queue *cp = (Queue *) pQueue;
    
    if(cp == NULL){
        printf("[WARN] : queue is null | queueFree \n");
        return;
    }

    doublyLinkedListFree(cp->list);

    free(cp);
}
