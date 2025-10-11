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

int main()
{
    BinarySearchTree *pBinarySearchTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    add(pBinarySearchTree);

    binarySearchTreeRemove(pBinarySearchTree, 5);
    printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");

    int val = 2;
    BinarySearchTreeNode *temp = binarySearchTreeGet(pBinarySearchTree, 1);
    binarySearchTreeNodeSetValue(pBinarySearchTree, temp, &val);

    int length = binarySearchTreeLength(pBinarySearchTree);

    for (int i = 0; i < length; i++)
    {
        BinarySearchTreeNode *pNode = binarySearchTreeGet(pBinarySearchTree, i);
        if (pNode != NULL)
        {
            printf("%d\n", *(int *)binarySearchTreeNodeGetValue(pBinarySearchTree, pNode));
            binarySearchTreeRemove(pBinarySearchTree, i);
            printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
        }
    }
    BinarySearchTree *copy = binarySearchTreeCopy(pBinarySearchTree);
    binarySearchTreeFree(pBinarySearchTree);

    BinarySearchTree *pBigBinarySearchTree = binarySearchTreeCreate(sizeof(BigObj), &copyBig, &freeBig);
    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigBinarySearchTree, cp);

    binarySearchTreeRemove(pBigBinarySearchTree, 5);
    printf("%s\n", isRedBlackTree(pBigBinarySearchTree) ? "true" : "false");

    BigObj *big = (BigObj *)malloc(sizeof(BigObj));
    big->id = 1;
    big->str = cp;

    BinarySearchTreeNode *temp2 = binarySearchTreeGet(pBigBinarySearchTree, 1);
    binarySearchTreeNodeSetValue(pBigBinarySearchTree, temp2, big);

    BinarySearchTreeNode *temp3 = binarySearchTreeGet(pBigBinarySearchTree, 0);
    BigObj *bigg = (BigObj *)binarySearchTreeNodeGetValue(pBigBinarySearchTree, temp3);
    free(bigg->str);

    for (int i = 0; i < binarySearchTreeLength(pBigBinarySearchTree); i++)
    {
        BinarySearchTreeNode *pNode = binarySearchTreeGet(pBigBinarySearchTree, i);
        if (pNode != NULL)
        {
            BigObj *obj = (BigObj *)binarySearchTreeNodeGetValue(pBigBinarySearchTree, pNode);
            printf("%d\n", obj->id);
        }
    }

    binarySearchTreeFree(pBigBinarySearchTree);

    return 0;
}

void add(BinarySearchTree *pBinarySearchTree)
{
    for (int i = 0; i < 15; i++)
    {
        binarySearchTreeInsert(pBinarySearchTree, &i, i);
        printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
    }
}

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
