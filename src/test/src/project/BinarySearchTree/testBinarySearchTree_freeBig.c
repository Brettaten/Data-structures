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










void freeBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    free(pBig->str);
    free(pBig);
}
