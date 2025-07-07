#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"
#include "../DoublyLinkedList/doublyLinkedList.h"

typedef struct Stack
{
    DoublyLinkedList *list;
    int size;
    int length;
} Stack;

Stack *stackCreate(int size)
{
    Stack *pStack = (Stack *)malloc(sizeof(Stack));

    if (pStack == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    DoublyLinkedList *pList = doublyLinkedListCreate(size);
    pStack->list = pList;
    pStack->size = size;
    pStack->length = 0;

    return pStack;
}

int stackPush(Stack *pStack, void *value)
{
    int st1 = doublyLinkedListAdd(pStack->list, value);

    if (st1 == -1)
    {
        return -1;
    }

    pStack->length++;

    return 0;
}

void *stackPop(Stack *pStack)
{
    void *value = stackPeek(pStack);

    if (value == NULL)
    {
        return NULL;
    }

    int st1 = doublyLinkedListRemove(pStack->list, pStack->length - 1);

    if (st1 == -1)
    {
        free(value);
        return NULL;
    }

    pStack->length--;

    return value;
}

void *stackPeek(Stack *pStack)
{
    if (pStack->list == 0)
    {
        printf("List is empty!");
        return NULL;
    }

    void *value = doublyLinkedListGet(pStack->list, pStack->length - 1);

    if (value == NULL)
    {
        return NULL;
    }

    return value;
}

int stackLength(Stack *pStack)
{
    return pStack->length;
}

int stackSize(Stack *pStack)
{
    return pStack->size;
}

void stackFree(Stack *pStack)
{
    doublyLinkedListFree(pStack->list);

    free(pStack);
}
