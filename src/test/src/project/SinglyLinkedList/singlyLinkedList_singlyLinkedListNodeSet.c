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
