#include "testInsert.h"
#include "../util/cbuilderTest.h"
#include "../../../../../main/c/BinarySearchTree/binarySearchTree.h"

bool called = false;

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

void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode){
    called = true;
}
