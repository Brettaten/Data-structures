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

    if(pNode->value == NULL){
        printf("[ERROR] : Value is null | singlyLinkedListNodeCopy \n");
        return NULL;
    }

    SinglyLinkedListNode *copy = (SinglyLinkedListNode *) malloc(sizeof(SinglyLinkedListNode));

    if(copy == NULL){
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
