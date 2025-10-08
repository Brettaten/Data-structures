#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(List *pList);
void addBig(List *pList, char *cp);
void *copyBig(void *big);
void freeBig(void *big);

int main()
{
    List *pList = listCreate(sizeof(int), NULL, NULL);

    add(pList);

    listRemove(pList, 5);

    int val = 1;
    int *temp = &val;
    listAddIndex(pList, temp, 10);
    listSet(pList, temp, 2);
    listSwap(pList, 3, 8);

    for (int i = 0; i < listLength(pList); i++)
    {
        printf("%d\n", *(int *)listGet(pList, i));
    }

    listFree(pList);

    List *pBigList = listCreate(sizeof(BigObj), &copyBig, &freeBig);
    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigList, cp);

    listRemove(pBigList, 5);

    BigObj *big = (BigObj *)malloc(sizeof(BigObj));
    big->id = 1;
    big->str = cp;

    listAddIndex(pBigList, big, 10);
    listSet(pBigList, big, 2);
    listSwap(pBigList, 3, 8);

    BigObj *bigg = (BigObj *)listGet(pBigList, 0);
    free(bigg->str);

    for (int i = 0; i < listLength(pBigList); i++)
    {
        BigObj *big = (BigObj *)listGet(pBigList, i);
        printf("%d\n", big->id);
    }

    listFree(pBigList);

    return 0;
}

void add(List *pList)
{
    for (int i = 0; i < 15; i++)
    {
        listAdd(pList, &i);
    }
}

void addBig(List *pList, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        listAdd(pList, big);
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
