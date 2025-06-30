#include <stdlib.h>

#include "stack.h"
#include "list.h";

typedef struct Stack{
    List *list;
    int length;
} Stack;

Stack *stackCreate()
{
    Stack *pStack = (Stack*) malloc(sizeof(Stack));

    if(pStack == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    List *pList = listCreate();
    pStack->list = pList;
    pStack->length = 0;

    return pStack;
}

void stackPush(Stack *pStack, void *value)
{
    listAdd(pStack->list, value);
    pStack->length++;
}

void *stackPop(Stack *pStack)
{
    if(listLength(pStack->list) == 0){
        return NULL;
    }

    void* value = listGet(pStack->list, listLength(pStack->length)-1);
    listSet(pStack->list, NULL, listLength(pStack->length)-1);
    listRemove(pStack->list, listLength(pStack->length)-1);
    pStack->length--;

    return value;
}

int stackLength(Stack *pStack)
{
    return pStack->length;
}

void stackFree(Stack * pStack)
{
}
