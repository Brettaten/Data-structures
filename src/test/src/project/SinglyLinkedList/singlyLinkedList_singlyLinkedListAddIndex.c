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
