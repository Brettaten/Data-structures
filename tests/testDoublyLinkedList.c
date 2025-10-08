#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublyLinkedList.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(DoublyLinkedList *pDoublyLinkedList);
void addBig(DoublyLinkedList *pDoublyLinkedList, char *cp);
void *copyBig(void *big);
void freeBig(void *big);

int main()
{
    DoublyLinkedList *pDoublyLinkedList = doublyLinkedListCreate(sizeof(int), NULL, NULL);

    add(pDoublyLinkedList);

    doublyLinkedListRemove(pDoublyLinkedList, 5);

    int val = 1;
    int *temp = &val;
    doublyLinkedListAddIndex(pDoublyLinkedList, temp, 10);
    doublyLinkedListSet(pDoublyLinkedList, temp, 2);

    for (int i = 0; i < doublyLinkedListLength(pDoublyLinkedList); i++)
    {
        printf("%d\n", *(int *)doublyLinkedListGet(pDoublyLinkedList, i));
    }
    DoublyLinkedList *copy = doublyLinkedListCopy(pDoublyLinkedList); 
    doublyLinkedListFree(pDoublyLinkedList);

    DoublyLinkedList *pBigDoublyLinkedList = doublyLinkedListCreate(sizeof(BigObj), &copyBig, &freeBig);
    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigDoublyLinkedList, cp);

    doublyLinkedListRemove(pBigDoublyLinkedList, 5);

    BigObj *big = (BigObj *)malloc(sizeof(BigObj));
    big->id = 1;
    big->str = cp;

    doublyLinkedListAddIndex(pBigDoublyLinkedList, big, 10);
    doublyLinkedListSet(pBigDoublyLinkedList, big, 2);

    BigObj *bigg = (BigObj *)doublyLinkedListGet(pBigDoublyLinkedList, 0);
    free(bigg->str);

    for (int i = 0; i < doublyLinkedListLength(pBigDoublyLinkedList); i++)
    {
        BigObj *big = (BigObj *)doublyLinkedListGet(pBigDoublyLinkedList, i);
        printf("%d\n", big->id);
    }

    doublyLinkedListFree(pBigDoublyLinkedList);

    return 0;
}

void add(DoublyLinkedList *pDoublyLinkedList)
{
    for (int i = 0; i < 15; i++)
    {
        doublyLinkedListAdd(pDoublyLinkedList, &i);
    }
}

void addBig(DoublyLinkedList *pDoublyLinkedList, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        doublyLinkedListAdd(pDoublyLinkedList, big);
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
