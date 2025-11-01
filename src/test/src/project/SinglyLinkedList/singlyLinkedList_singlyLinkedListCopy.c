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
