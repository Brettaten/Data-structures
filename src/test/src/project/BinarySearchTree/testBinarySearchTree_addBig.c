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






void addBig(BinarySearchTree *pBinarySearchTree, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        binarySearchTreeInsert(pBinarySearchTree, big, i);
        printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
    }
}
