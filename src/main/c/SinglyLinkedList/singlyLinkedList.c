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
 * Function used to create a deep copy of a node
 *
 * @param pList the pointer to the list
 * @param pNode the pointer to the node
 *
 * @return Success: the copy of the node | Failure: NULL
 *
 * @note The value is deep copied while next is set to null
 */
SinglyLinkedListNode *singlyLinkedListNodeCopy(SinglyLinkedList *pList, SinglyLinkedListNode *pNode);

/**
 * Function used to free a node
 *
 * @param pNode pointer to the node
 *
 * @return NULL.
 */
void singlyLinkedListFreeNode(SinglyLinkedList *pList, SinglyLinkedListNode *pNode);

typedef struct SinglyLinkedList
{
    SinglyLinkedListNode *head;
    int length;
    int size;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} SinglyLinkedList;

typedef struct SinglyLinkedListNode
{
    SinglyLinkedListNode *next;
    void *value;
} SinglyLinkedListNode;

SinglyLinkedList *singlyLinkedListCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *))
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
    pList->copyElement = copyElement;
    pList->freeElement = freeElement;

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
    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListCreate \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListGet \n");
            return NULL;
        }
    }

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

    if (pList->freeElement == NULL)
    {
        free(pNode->value);
    }
    else
    {
        pList->freeElement(pNode->value);
    }

    pNode->value = NULL;
    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListSet \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListSet \n");
            return -1;
        }
    }

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

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListAdd \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListAdd \n");
            return -1;
        }
    }

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        if (pList->freeElement == NULL)
        {
            free(cp);
        }
        else
        {
            pList->freeElement(cp);
        }

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
            singlyLinkedListFreeNode(pList, pNodeNew);
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

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListAddIndex \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListAddIndex \n");
            return -1;
        }
    }

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        if (pList->freeElement == NULL)
        {
            free(cp);
        }
        else
        {
            pList->freeElement(cp);
        }

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
            singlyLinkedListFreeNode(pList, pNodeNew);
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

void *singlyLinkedListCopy(void *pList)
{
    SinglyLinkedList *cp = (SinglyLinkedList *)pList;

    if (cp == NULL)
    {
        printf("[ERROR] : List is null | singlyLinkedListCopy \n");
        return NULL;
    }

    SinglyLinkedList *copy = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;
    copy->length = cp->length;
    copy->size = cp->size;

    if (cp->head != NULL)
    {
        copy->head = singlyLinkedListNodeCopy(cp, cp->head);

        SinglyLinkedListNode *dest = copy->head;
        SinglyLinkedListNode *src = cp->head;

        while (src->next != NULL)
        {
            dest->next = singlyLinkedListNodeCopy(cp, src->next);

            if (dest->next == NULL)
            {
                printf("[ERROR] : Function singlyLinkedListNodeCopy failed | singlyLinkedListCopy \n");
                return NULL;
            }

            dest = dest->next;
            src = src->next;
        }
    }
    else{
        copy->head = NULL;
    }
    return copy;
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

        singlyLinkedListFreeNode(pList, pList->head);
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

        singlyLinkedListFreeNode(pList, pNodeP->next);
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

int singlyLinkedListContentSize(SinglyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | singlyLinkedListSize \n");
        return -1;
    }

    return pList->size;
}

int singlyLinkedListSize()
{
    return sizeof(SinglyLinkedList);
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

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListNodeGet \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListNodeGet \n");
            return NULL;
        }
    }

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

    if (pList->freeElement == NULL)
    {
        free(pNode->value);
    }
    else
    {
        pList->freeElement(pNode->value);
    }

    pNode->value = NULL;

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | singlyLinkedListNodeSet \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | singlyLinkedListNodeSet \n");
            return -1;
        }
    }

    pNode->value = cp;

    return 0;
}

void singlyLinkedListFree(void *pList)
{
    SinglyLinkedList *cp = (SinglyLinkedList *)pList;

    if (cp == NULL)
    {
        printf("[INFO] : Pointer to list is NULL | singlyLinkedListFree \n");
        return;
    }

    SinglyLinkedListNode *pNode = cp->head;

    for (int i = 0; i < cp->length; i++)
    {
        SinglyLinkedListNode *pNodeTemp = pNode->next;

        singlyLinkedListFreeNode(cp, pNode);
        pNode = pNodeTemp;
    }

    free(cp);
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

SinglyLinkedListNode *singlyLinkedListNodeCopy(SinglyLinkedList *pList, SinglyLinkedListNode *pNode)
{
    if (pList == NULL)
    {
        printf("[ERROR] : List is null | singlyLinkedListNodeCopy \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | sinlgyLinkedListNodeCopy \n");
        return NULL;
    }

    if (pNode->value == NULL)
    {
        printf("[ERROR] : Value is null | singlyLinkedListNodeCopy \n");
        return NULL;
    }

    SinglyLinkedListNode *copy = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | singlyLinkedListNodeCopy \n");
        return NULL;
    }

    copy->next = NULL;

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | sinlgyLinkedListNodeCopy \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | sinlgyLinkedListNodeCopy \n");
            return NULL;
        }
    }

    copy->value = cp;

    return copy;
}

void singlyLinkedListFreeNode(SinglyLinkedList *pList, SinglyLinkedListNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | singlyLinkedListFreeNode \n");
        return;
    }

    if (pList->freeElement == NULL)
    {
        free(pNode->value);
    }
    else
    {
        pList->freeElement(pNode->value);
    }

    pNode->value = NULL;
    pNode->next = NULL;
    free(pNode);

    pNode = NULL;
}
