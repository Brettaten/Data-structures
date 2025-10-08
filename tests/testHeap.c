#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "heap.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(Heap *pHeap);
void addBig(Heap *pHeap, char *cp);
void *copyBig(void *big);
void freeBig(void *big);

int main(){
    Heap *pHeap = heapCreate(sizeof(int), true, NULL, NULL);

    add(pHeap);

    heapRemove(pHeap);

    int length = heapLength(pHeap);
    for(int i = 10; i < length; i++){
        printf("%d\n",*(int*)heapGetRoot(pHeap));
        heapRemove(pHeap);
    }

    Heap *copy = heapCopy(pHeap);
    
    heapFree(pHeap);
    
    Heap *pBigHeap = heapCreate(sizeof(BigObj), false, &copyBig, &freeBig);

    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigHeap, cp);

    heapRemove(pBigHeap);
    
    for(int i = 0; i < heapLength(pBigHeap); i++){
        BigObj *big = (BigObj*) heapGetRoot(pBigHeap);
        printf("%d\n", big->id);
    }

    free(cp);

    heapFree(pBigHeap);


    return 0;
}

void add(Heap *pHeap){
     for(int i = 0; i < 15; i++){
        heapAdd(pHeap, &i, i);
    }
}

void addBig(Heap *pHeap, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        heapAdd(pHeap, big, i);
    }
}

void *copyBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    char *cp = (char *)malloc(sizeof(char) * (pBig->id + 1));

    if (cp == NULL)
    {
        printf("LOL");
    }

    memcpy(cp, pBig->str, sizeof(char) * (pBig->id + 1));

    BigObj *cpp = (BigObj *)malloc(sizeof(BigObj));

    memcpy(cpp, pBig, sizeof(BigObj));

    cpp->id = pBig->id;
    cpp->str = cp;

    return cpp;
}

void freeBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    free(pBig->str);
    free(pBig);
}
