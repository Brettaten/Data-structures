#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

typedef struct List
{
    void **data;
    int size;
    int buffer;
    int length;
} List;

List *listCreate(int size)
{
    List *pList = (List *)malloc(sizeof(List));
    if (pList == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->data = (void **)malloc(sizeof(void *) * 8);
    if (pList->data == NULL)
    {
        free(pList);
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->buffer = 8;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *listGet(List *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    return *(pList->data + index);
}

void listSet(List *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return;
    }

    void *cp = (void *)malloc(sizeof(void *));

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return;
    }
    memcpy_s(cp, sizeof(void *), value, pList->size);

    void *lp = listGet(pList, index);
    free(lp);
    lp = NULL;

    *(pList->data + index) = cp;
}

void listAdd(List *pList, void *value)
{
    if (pList->length == pList->buffer)
    {
        pList->data = (void **)realloc(pList->data, sizeof(void *) * pList->buffer * 2);
        if (pList->data == NULL)
        {
            printf("Memory allocation failed!");
            return;
        }

        pList->buffer = pList->buffer * 2;
    }

    void *cp = (void *)malloc(sizeof(void *));

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return;
    }
    memcpy_s(cp, sizeof(void *), value, pList->size);

    (pList->data[pList->length]) = cp;
    pList->length++;
}

void listAddIndex(List *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return;
    }

    listAdd(pList, listGet(pList, pList->length - 1));

    for (int i = pList->length - 2; i > index; i--)
    {
        listSet(pList, listGet(pList, i - 1), i);
    }

    listSet(pList, value, index);
}

void listRemove(List *pList, int index)
{
    if (pList->length == 0)
    {
        printf("List is empty!");
        return;
    }

    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return;
    }

    for (int i = index + 1; i < pList->length; i++)
    {
        listSet(pList, listGet(pList, i), i - 1);
    }

    void *lastP = listGet(pList, pList->length - 1);
    free(lastP);
    lastP = NULL;
    pList->length--;
}

void listFree(List *pList)
{
    for (int i = 0; i < pList->buffer; i++)
    {
        free(*(pList->data + i));
    }

    free(pList->data);
    free(pList);
}

int listLength(List *plist)
{
    return plist->length;
}

int listSize(List *pList)
{
    return pList->size;
}
