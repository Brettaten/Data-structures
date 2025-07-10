#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef struct List
{
    void **data;
    int size;
    int buffer;
    int length;
} List;

bool isIndexInBounds(List *pList, int index);

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

    void *value = *(pList->data + index);
    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    return cp;
}

int listSet(List *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    void *lp = *(pList->data + index);

    free(lp);
    lp = NULL;

    *(pList->data + index) = cp;

    return 0;
}

int listAdd(List *pList, void *value)
{
    if (pList->length == pList->buffer)
    {
        pList->data = (void **)realloc(pList->data, sizeof(void *) * pList->buffer * 2);
        if (pList->data == NULL)
        {
            printf("Memory allocation failed!");
            return -1;
        }

        pList->buffer = pList->buffer * 2;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    (pList->data[pList->length]) = cp;
    pList->length++;

    return 0;
}

int listAddIndex(List *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    void *p1 = *(pList->data + pList->length - 1);

    int st1 = listAdd(pList, p1);

    if (st1 == -1)
    {
        return -1;
    }

    for (int i = pList->length - 2; i > index; i--)
    {
        void *p2 = *(pList->data + i - 1);

        int st2 = listSet(pList, p2, i);

        if (st2 == -1)
        {
            return -1;
        }
    }

    int st3 = listSet(pList, value, index);

    if (st3 == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int listSwap(List *pList, int index1, int index2)
{
    if (pList == NULL || !isIndexInBounds(pList, index1) || !isIndexInBounds(pList, index2))
    {
        return -1;
    }

    void *temp = pList->data[index1];
    pList->data[index1] = pList->data[index2];
    pList->data[index2] = temp;

    return 0;
}

int listRemove(List *pList, int index)
{
    if (pList->length == 0)
    {
        printf("List is empty!");
        return -1;
    }

    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    for (int i = index + 1; i < pList->length; i++)
    {
        void *p1 = *(pList->data + i);

        int st1 = listSet(pList, p1, i - 1);

        if (st1 == -1)
        {
            return -1;
        }
    }

    void *lastP = *(pList->data + pList->length - 1);

    free(lastP);
    lastP = NULL;
    pList->length--;

    return 0;
}

void listFree(List *pList)
{
    for (int i = 0; i < pList->length; i++)
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

bool isIndexInBounds(List *pList, int index)
{
    if (pList == NULL)
    {
        return false;
    }

    if (index < 0 || index >= pList->length)
    {
        return false;
    }
    return true;
}
