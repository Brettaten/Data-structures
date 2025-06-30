#include <stdlib.h>

#include "linkedList.h"

typedef struct LinkedList{
    LinkedListNode *head;
    int length;
} LinkedList;

typedef struct LinkedListNode{
    LinkedListNode *next;
    void *value;
} LinkedListNode;

LinkedList *LinkedListCreate()
{
    LinkedList *pList = (LinkedList*) malloc(sizeof(LinkedList));
    
    if(pList == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->head = NULL;
    pList->length = 0;

    return pList;
}

void *linkedListGet(LinkedList *pList, int index)
{
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNode = pList->head;

    for(int i = 0; i < index; i++){
        pNode = pNode->next;
    }
    return pNode->value;
}

void linkedListSet(LinkedList *pList, void *value, int index)
{
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNode = pList->head;

    for(int i = 0; i < index; i++){
        pNode = pNode->next;
    }
    pNode->value = value;
}

void linkedListAdd(LinkedList *pList, void *value)
{
    LinkedListNode *pNodeNew = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    if(pNodeNew == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    LinkedListNode *pNode = pList->head;

    while(pNode->next != NULL){
        pNode = pNode->next;
    }
    pNodeNew->value = value;
    pNodeNew->next = NULL;
    pNode->next = pNodeNew;

    pList->length++;
}

void linkedListAddIndex(LinkedList *pList, void *value, int index)
{
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNodeNew = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    if(pNodeNew == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    LinkedListNode *pNodeP = NULL;
    LinkedListNode *pNodeC = pList->head;

    for(int i = 0; i < index; i++){
        if(pNodeP == NULL){
            pNodeP = pList->head;
        }
        else{
            pNodeP = pNodeP->next;
        }
        pNodeC = pNodeC->next;
    }

    pNodeNew->value = value;
    pNodeNew->next = pNodeC;

    if(pNodeP == NULL){
        pList->head = pNodeNew;
    }
    else{
        pNodeP->next = pNodeNew;
    }

    pList->length++;
}

void linkedListRemove(LinkedList *pList, int index)
{
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return NULL;
    }

    LinkedListNode *pNodeP = NULL;
    LinkedListNode *pNodeC = pList->head;

    for(int i = 0; i < index; i++){
        if(pNodeP == NULL){
            pNodeP = pList->head;
        }
        else{
            pNodeP = pNodeP->next;
        }
        pNodeC = pNodeC->next;
    }

    if(pNodeP == NULL){
        pList->head = pNodeC->next;
    }
    else if(pNodeC->next == NULL){
        pNodeP->next = NULL;
    }
    else{
        pNodeP->next = pNodeC->next;
    }
    free(pNodeC);
    pList->length--;
}

int linkedListLength(LinkedList *pList)
{
    return pList->length;
}

void listFree(LinkedList *pList)
{
}
