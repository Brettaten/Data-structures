#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void add(List *pList);

int main(){

    List *pList = listCreate(sizeof(int));

    add(pList);

    listRemove(pList, 5);

    int val = 1;
    int *temp = &val;
    listAddIndex(pList, temp, 10);
    listSet(pList, temp, 2);

    for(int i = 0; i < listLength(pList); i++){
        printf("%d\n",*(int*)listGet(pList, i));
    }

    listFree(pList);

    return 0;
}

void add(List *pList){
     for(int i = 0; i < 15; i++){
        listAdd(pList, &i);
    }
}