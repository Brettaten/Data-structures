#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

LinkedListNode *linkedListGetNode(LinkedList *pList, int index);
void freeNode(LinkedListNode *pNode);

typedef struct LinkedList
{
    LinkedListNode *head;
    int length;
    int size;
} LinkedList;

typedef struct LinkedListNode
{
    LinkedListNode *next;
    void *value;
} LinkedListNode;

LinkedList *LinkedListCreate(int size)
{
    LinkedList *pList = (LinkedList *)malloc(sizeof(LinkedList));

    if (pList == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->head = NULL;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *linkedListGet(LinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNode = linkedListGetNode(pList, index);

    return pNode->value;
}

void linkedListSet(LinkedList *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    void *pValue = linkedListGet(pList, index);
    free(pValue);
    pValue = NULL;

    void *cp = (void *)malloc(sizeof(void *));

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    memcpy(cp, value, pList->size);

    pValue = cp;
}

void linkedListAdd(LinkedList *pList, void *value)
{
    LinkedListNode *pNodeNew = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (pNodeNew == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    void *cp = (void *)malloc(sizeof(void *));

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    memcpy(cp, value, pList->size);

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    if (pList->length == 0)
    {
        pList->head = pNodeNew;
    }
    else
    {
        LinkedListNode *node = linkedListGetNode(pList, pList->length - 1);

        node->next = pNodeNew;
    }

    pList->length++;
}

void linkedListAddIndex(LinkedList *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNodeNew = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (pNodeNew == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    void *cp = (void *)malloc(sizeof(void *));

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    memcpy(cp, value, pList->size);

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    LinkedListNode *pNodeP;
    LinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head,

        pList->head = pNodeNew;
        pNodeNew->next = pNodeC;
    }
    else
    {
        pNodeP = linkedListGet(pList, index - 1);
        pNodeC = pNodeP->next;

        pNodeP->next = pNodeNew;
        pNodeNew->next = pNodeC;
    }

    pList->length++;
}

void linkedListRemove(LinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNodeP;
    LinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head->next;

        freeNode(pList->head);
        pList->head = pNodeC;
    }
    else
    {
        pNodeP = linkedListGetNode(pList, index - 1);
        pNodeC = pNodeP->next->next;

        freeNode(pNodeP->next);
        pNodeP->next = pNodeC;
    }

    pList->length--;
}

int linkedListLength(LinkedList *pList)
{
    return pList->length;
}

int linkedListSize(LinkedList *pList)
{
    return pList->size;
}

void linkedListFree(LinkedList *pList)
{
    LinkedListNode *pNode = pList->head;

    for (int i = 0; i < pList->length; i++)
    {
        LinkedListNode *pNodeTemp = pNode->next;

        freeNode(pNode);
        pNode = pNodeTemp;
    }

    free(pList);
}

LinkedListNode *linkedListGetNode(LinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    if (pList->length == 0)
    {
        printf("Can not get a node from an empty list!");
        return NULL;
    }

    LinkedListNode *node = pList->head;

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

void freeNode(LinkedListNode *pNode)
{
    free(pNode->value);
    free(pNode);

    pNode = NULL;
}
