#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

typedef struct List{
    void **data;
    int size;
    int buffer;
    int length;
} List;

List *listCreate(int size){
    List *pList = (List*) malloc(sizeof(List));
    if(pList == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->data = (void**) malloc(sizeof(void*) * 8);
    if(pList->data == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->buffer = 8;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void* listGet(List *pList, int index){
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return NULL;
    }

    return *(pList->data + index);
}

void listSet(List *pList,void *value, int index){ 
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return;
    }

    free(*(pList->data + index));
    *(pList->data + index) = NULL;

    void* cp = (void*) malloc(sizeof(void*));
    memcpy(cp, value, pList->size);

    *(pList->data + index) = cp;
}

void listAdd(List *pList, void *value){ 
    if(pList->length == pList->buffer){
        pList->data = (void**) realloc(pList->data, sizeof(void*) * pList->buffer * 2);
        if(pList->data == NULL){
            printf("Memory allocation failed!");
            return;
        }

        pList->buffer = pList->buffer * 2;
    }

    
    void* cp = (void*) malloc(sizeof(void*));
    memcpy(cp, value, pList->size);
    
    (pList->data[pList->length]) = cp;
    pList->length++;
}

void listAddIndex(List *pList, void *value, int index){ 
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return;
    }

    listAdd(pList, *(pList->data + pList->length - 1));

    printf("%d", pList->length-2);
    for(int i = pList->length-2; i > index; i--){
        *(pList->data + i) = *(pList->data + i - 1);
    }

    void* cp = (void*) malloc(sizeof(void*));
    memcpy(cp, value, pList->size);

    *(pList->data + index) = cp;
}

void listRemove(List *pList, int index){ 
    if(index >= pList->length || index < 0){
        printf("Index out of bounds!");
        return;
    }

    free(*(pList->data + index));
    *(pList->data + index) = NULL;

    for(int i = index+1; i < pList->length; i++){
        *(pList->data + i - 1) = *(pList->data + i);
    }

    *(pList->data + pList->length-1) = NULL;
    pList->length--;
}

void listFree(List *pList){
    for(int i = 0; i < pList->buffer; i++){
        free(*(pList->data + i));
    }

    free(pList->data);
    free(pList);
}

int listLength(List *plist){
    return plist->length;
}

int listSize(List *pList){
    return pList->size;
}
