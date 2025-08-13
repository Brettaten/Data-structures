#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "singlyLinkedList.h"

/**
 * Function used to get a node at the passed index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: pointer to a node | Failure: NULL
 */
SinglyLinkedListNode *singlyLinkedListGetNode(SinglyLinkedList *pList, int index);

/**
 * Function used determine whether an index is in bounds
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return true or false
 */
bool isIndexInBoundsSingly(SinglyLinkedList *pList, int index);

/**
 * Function used to free a node
 *
 * @param pNode pointer to the node
 *
 * @return NULL
 *
 * @note This function only frees the pointer. If a struct is stored, that itself contains a pointer,
 * this pointer will not be freed.
 */
void freeNode(SinglyLinkedListNode *pNode);

typedef struct SinglyLinkedList
{
    SinglyLinkedListNode *head;
    int length;
    int size;
} SinglyLinkedList;

typedef struct SinglyLinkedListNode
{
    SinglyLinkedListNode *next;
    void *value;
} SinglyLinkedListNode;

SinglyLinkedList *singlyLinkedListCreate(int size)
{
    SinglyLinkedList *pList = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));

    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListCreate \n");
        return NULL;
    }

    pList->head = NULL;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *singlyLinkedListGet(SinglyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListGet \n");
        return NULL;
    }

    if (!isIndexInBoundsSingly(pList, index))
    {
        printf("[INFO] : Index out of bounds | singlyLinkedListGet \n");
        return NULL;
    }

    SinglyLinkedListNode *pNode = singlyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        printf("[ERROR] : Function singlyLinkedListGetNode failed | singlyLinkedListGet \n");
        return NULL;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListCreate \n");
        return NULL;
    }

    memcpy_s(cp, pList->size, pNode->value, pList->size);

    return cp;
}

int singlyLinkedListSet(SinglyLinkedList *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | singlyLinkedListSet \n");
        return -1;
    }

    if (!isIndexInBoundsSingly(pList, index))
    {
        printf("[INFO] : Index out of bounds | singlyLinkedListSet \n");
        return -1;
    }

    SinglyLinkedListNode *pNode = singlyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        printf("[ERROR] : Function singlyLinkedListGetNode failed | singlyLinkedListSet \n");
        return -1;
    }

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListSet \n");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    pNode->value = cp;

    return 0;
}

int singlyLinkedListAdd(SinglyLinkedList *pList, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListAdd \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | singlyLinkedListAdd \n");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListAdd \n");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("[ERROR] : Memory allocation failed | singlyLinkedListAdd \n");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    if (pList->length == 0)
    {
        pList->head = pNodeNew;
    }
    else
    {
        SinglyLinkedListNode *node = singlyLinkedListGetNode(pList, pList->length - 1);

        if (node == NULL)
        {
            free(pNodeNew);
            printf("[ERROR] : Function singlyLinkedListGetNode failed | singlyLinkedListAdd \n");
            return -1;
        }

        node->next = pNodeNew;
    }

    pList->length++;

    return 0;
}

int singlyLinkedListAddIndex(SinglyLinkedList *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListAddIndex \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | singlyLinkedListAddIndex \n");
        return -1;
    }

    if (!isIndexInBoundsSingly(pList, index))
    {
        printf("[INFO] : Index out of bounds | singlyLinkedListAddIndex \n");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("[ERROR] : Memory allocation failed | singlyLinkedListAddIndex \n");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    SinglyLinkedListNode *pNodeP;
    SinglyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head,

        pList->head = pNodeNew;
        pNodeNew->next = pNodeC;
    }
    else
    {
        pNodeP = singlyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            freeNode(pNodeNew);
            printf("[ERROR] : Function singlyLinkedListGetNode failed | singlyLinkedListAddIndex \n");
            return -1;
        }

        pNodeC = pNodeP->next;

        pNodeP->next = pNodeNew;
        pNodeNew->next = pNodeC;
    }

    pList->length++;

    return 0;
}

int singlyLinkedListRemove(SinglyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListRemove \n");
        return -1;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | singlyLinkedListRemove \n");
        return -1;
    }

    if (!isIndexInBoundsSingly)
    {
        printf("[INFO] : Index out of bounds | singlyLinkedListRemove \n");
        return -1;
    }

    SinglyLinkedListNode *pNodeP;
    SinglyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head->next;

        freeNode(pList->head);
        pList->head = pNodeC;
    }
    else
    {
        pNodeP = singlyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            printf("[ERROR] : Function singlyLinkedListGetNode failed | singlyLinkedListRemove \n");
            return -1;
        }

        pNodeC = pNodeP->next->next;

        freeNode(pNodeP->next);
        pNodeP->next = NULL;
        pNodeP->next = pNodeC;
    }

    pList->length--;

    return 0;
}

int singlyLinkedListLength(SinglyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListLength \n");
        return -1;
    }

    return pList->length;
}

int singlyLinkedListSize(SinglyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListSize \n");
        return -1;
    }

    return pList->size;
}

SinglyLinkedListNode *singlyLinkedListGetHead(SinglyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListGetHead \n");
        return NULL;
    }

    return pList->head;
}

SinglyLinkedListNode *singlyLinkedListNodeNext(SinglyLinkedListNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | singlyLinkedListNodeNext \n");
        return NULL;
    }

    return pNode->next;
}

void *singlyLinkedListNodeGet(SinglyLinkedList *pList, SinglyLinkedListNode *pNode)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListNodeGet \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | singlyLinkedListNodeGet \n");
        return NULL;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListNodeGet \n");
        return NULL;
    }

    memcpy_s(cp, pList->size, pNode->value, pList->size);

    return cp;
}

int singlyLinkedListNodeSet(SinglyLinkedList *pList, SinglyLinkedListNode *pNode, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListNodeSet \n");
        return -1;
    }

    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | singlyLinkedListNodeSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | singlyLinkedListNodeSet \n");
        return -1;
    }

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListNodeSet \n");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    pNode->value = cp;

    return 0;
}

void singlyLinkedListFree(SinglyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[INFO] : Pointer to list is NULL | singlyLinkedListFree \n");
        return;
    }

    SinglyLinkedListNode *pNode = pList->head;

    for (int i = 0; i < pList->length; i++)
    {
        SinglyLinkedListNode *pNodeTemp = pNode->next;

        freeNode(pNode);
        pNode = pNodeTemp;
    }

    free(pList);
}

SinglyLinkedListNode *singlyLinkedListGetNode(SinglyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListGetNode \n");
        return NULL;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | singlyLinkedListGetNode \n");
        return NULL;
    }

    if (!isIndexInBoundsSingly(pList, index))
    {
        printf("[INFO] : Index out of bounds | singlyLinkedListGetNode \n");
        return NULL;
    }

    SinglyLinkedListNode *node = pList->head;

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

bool isIndexInBoundsSingly(SinglyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | isIndexInBoundsSingly \n");
        return -1;
    }

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

void freeNode(SinglyLinkedListNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | freeNode \n");
        return;
    }

    free(pNode->value);
    pNode->value = NULL;
    pNode->next = NULL;
    free(pNode);

    pNode = NULL;
}
