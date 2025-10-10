#include "testInsert.h"
#include "../util/cbuilderTest.h"
#include "../../../../../main/c/BinarySearchTree/binarySearchTree.h"

bool called = false;
int freed = 0;
int copied = 0;

void testbinarySearchTreeInsertRoot()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;

    binarySearchTreeInsert(pTree, &value, 1);

    assert(called == false);
}

void testbinarySearchTreeInsert()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value, 2);

    assert(called == false);
}

void testbinarySearchTreeFree()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value2, 2);

    int value3 = 10;
    binarySearchTreeInsert(pTree, &value3, 3);

    int value4 = 10;
    binarySearchTreeInsert(pTree, &value4, 4);

    binarySearchTreeFree(pTree);

    assert(freed == 4);
}

void testbinarySearchTreeCopy()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value2, 2);

    int value3 = 10;
    binarySearchTreeInsert(pTree, &value3, 3);

    int value4 = 10;
    binarySearchTreeInsert(pTree, &value4, 4);

    binarySearchTreeCopy(pTree);

    assert(copied == 4);
}

void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode)
{
    called = true;
}

void binarySearchTreeFreeNode(BinarySearchTreeNode *pNode)
{
    freed++;
}

void *binarySearchTreeCopyNode(void *pTree)
{
    copied++;
    return pTree;
}