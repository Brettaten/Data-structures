#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "doublyLinkedList.h"

DoublyLinkedListNode *doublyLinkedListGetNode(DoublyLinkedList *pList, int index);
void freeNode(DoublyLinkedListNode *pNode);

typedef struct DoublyLinkedList
{
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
    int length;
    int size;
} DoublyLinkedList;

typedef struct DoublyLinkedListNode
{
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
    void *value;
} DoublyLinkedListNode;

DoublyLinkedList *doublyLinkedListCreate(int size)
{
    DoublyLinkedList *pList = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));

    if (pList == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *doublyLinkedListGet(DoublyLinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    DoublyLinkedListNode *pNode = doublyLinkedListGetNode(pList, index);

    return pNode->value;
}

int doublyLinkedListSet(DoublyLinkedList *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    DoublyLinkedListNode *pNode = doublyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        return -1;
    }

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    pNode->value = cp;

    return 0;
}

int doublyLinkedListAdd(DoublyLinkedList *pList, void *value)
{
    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    DoublyLinkedListNode *pNodeNew = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("Memory allocation failed!");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;
    pNodeNew->prev = NULL;

    if (pList->length == 0)
    {
        pList->head = pNodeNew;
        pList->tail = pNodeNew;
    }
    else
    {
        DoublyLinkedListNode *node = pList->tail;

        node->next = pNodeNew;
        pNodeNew->prev = node;

        pList->tail = pNodeNew;
    }

    pList->length++;

    return 0;
}

int doublyLinkedListAddIndex(DoublyLinkedList *pList, void *value, int index)
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

    DoublyLinkedListNode *pNodeNew = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("Memory allocation failed!");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;
    pNodeNew->prev = NULL;

    DoublyLinkedListNode *pNodeP;
    DoublyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head,

        pList->head = pNodeNew;
        pNodeNew->next = pNodeC;

        if (pList->length == 0)
        {
            pList->tail = pNodeNew;
        }
    }
    else
    {
        pNodeP = doublyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            return -1;
        }

        pNodeC = pNodeP->next;

        pNodeP->next = pNodeNew;
        pNodeNew->prev = pNodeP;
        pNodeNew->next = pNodeC;
        pNodeC->prev = pNodeNew;
    }

    pList->length++;

    return 0;
}

int doublyLinkedListRemove(DoublyLinkedList *pList, int index)
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

    DoublyLinkedListNode *pNodeP;
    DoublyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head->next;

        freeNode(pList->head);
        pList->head = pNodeC;

        if (pNodeC == NULL)
        {
            pList->tail = NULL;
        }
        else
        {
            pNodeC->prev = NULL;
        }
    }
    else
    {
        pNodeP = doublyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            return -1;
        }

        pNodeC = pNodeP->next->next;

        freeNode(pNodeP->next);
        pNodeP->next = NULL;
        pNodeP->next = pNodeC;

        if (pNodeC == NULL)
        {
            pList->tail = pNodeP;
        }
        else
        {
            pNodeC->prev = pNodeP;
        }
    }

    pList->length--;

    return 0;
}

int doublyLinkedListLength(DoublyLinkedList *pList)
{
    return pList->length;
}

int doublyLinkedListSize(DoublyLinkedList *pList)
{
    return pList->size;
}

DoublyLinkedListNode *doublyLinkedListGetHead(DoublyLinkedList *pList)
{
    return pList->head;
}

DoublyLinkedListNode *doublyLinkedListGetTail(DoublyLinkedList *pList)
{
    return pList->tail;
}

void doublyLinkedListFree(DoublyLinkedList *pList)
{
    DoublyLinkedListNode *pNode = pList->head;

    for (int i = 0; i < pList->length; i++)
    {
        DoublyLinkedListNode *pNodeTemp = pNode->next;

        freeNode(pNode);
        pNode = pNodeTemp;
    }

    free(pList);
}

DoublyLinkedListNode *doublyLinkedListGetNode(DoublyLinkedList *pList, int index)
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

    DoublyLinkedListNode *node;

    if (index <= pList->length / 2)
    {
        node = pList->head;

        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
    }
    else
    {
        node = pList->tail;

        for (int i = pList->length - 1; i > index; i--)
        {
            node = node->prev;
        }
    }

    return node;
}

void freeNode(DoublyLinkedListNode *pNode)
{
    free(pNode->value);
    pNode->value = NULL;
    pNode->next = NULL;
    pNode->prev = NULL;
    free(pNode);

    pNode = NULL;
}
