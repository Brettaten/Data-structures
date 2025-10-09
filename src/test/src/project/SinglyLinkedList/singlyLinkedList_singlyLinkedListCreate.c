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
