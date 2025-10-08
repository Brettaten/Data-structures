#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "singlyLinkedList.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(SinglyLinkedList *pSinglyLinkedList);
void addBig(SinglyLinkedList *pSinglyLinkedList, char *cp);
void *copyBig(void *big);
void freeBig(void *big);

int main()
{
    SinglyLinkedList *pSinglyLinkedList = singlyLinkedListCreate(sizeof(int), NULL, NULL);

    add(pSinglyLinkedList);

    singlyLinkedListRemove(pSinglyLinkedList, 5);

    int val = 1;
    int *temp = &val;
    singlyLinkedListAddIndex(pSinglyLinkedList, temp, 10);
    singlyLinkedListSet(pSinglyLinkedList, temp, 2);

    for (int i = 0; i < singlyLinkedListLength(pSinglyLinkedList); i++)
    {
        printf("%d\n", *(int *)singlyLinkedListGet(pSinglyLinkedList, i));
    }
    SinglyLinkedList *copy = singlyLinkedListCopy(pSinglyLinkedList); 
    singlyLinkedListFree(pSinglyLinkedList);

    SinglyLinkedList *pBigSinglyLinkedList = singlyLinkedListCreate(sizeof(BigObj), &copyBig, &freeBig);
    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigSinglyLinkedList, cp);

    singlyLinkedListRemove(pBigSinglyLinkedList, 5);

    BigObj *big = (BigObj *)malloc(sizeof(BigObj));
    big->id = 1;
    big->str = cp;

    singlyLinkedListAddIndex(pBigSinglyLinkedList, big, 10);
    singlyLinkedListSet(pBigSinglyLinkedList, big, 2);

    BigObj *bigg = (BigObj *)singlyLinkedListGet(pBigSinglyLinkedList, 0);
    free(bigg->str);

    for (int i = 0; i < singlyLinkedListLength(pBigSinglyLinkedList); i++)
    {
        BigObj *big = (BigObj *)singlyLinkedListGet(pBigSinglyLinkedList, i);
        printf("%d\n", big->id);
    }

    singlyLinkedListFree(pBigSinglyLinkedList);

    return 0;
}

void add(SinglyLinkedList *pSinglyLinkedList)
{
    for (int i = 0; i < 15; i++)
    {
        singlyLinkedListAdd(pSinglyLinkedList, &i);
    }
}

void addBig(SinglyLinkedList *pSinglyLinkedList, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        singlyLinkedListAdd(pSinglyLinkedList, big);
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
