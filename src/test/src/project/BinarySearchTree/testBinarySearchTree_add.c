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




void add(BinarySearchTree *pBinarySearchTree)
{
    for (int i = 0; i < 15; i++)
    {
        binarySearchTreeInsert(pBinarySearchTree, &i, i);
        printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
    }
}
