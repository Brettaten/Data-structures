#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binarySearchTree.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;


void add(BinarySearchTree *pBinarySearchTree);

void addBig(BinarySearchTree *pBinarySearchTree, char *cp);

void *copyBig(void *big);

void freeBig(void *big);








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
