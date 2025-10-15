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
