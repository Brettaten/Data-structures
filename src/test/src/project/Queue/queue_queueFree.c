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
