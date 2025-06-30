#include <stdlib.h>

#include "binaryTree.h"

typedef struct BinaryTree
{
    struct node *root;
} BinaryTree;

typedef struct BinaryTreeNode
{
    struct node *nodeLeft;
    struct node *nodeRight;
    void *value;

} BinaryTreeNode;

BinaryTree *binaryTreeCreate()
{
    BinaryTree *pTree = (BinaryTree *)malloc(sizeof(BinaryTree));

    if (pTree == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    pTree->root = NULL;
    return pTree;
}

BinaryTreeNode *binaryTreeGetRoot(BinaryTree *pTree)
{
    return pTree->root;
}

// void binaryTreeSetRoot(BinaryTree *pTree, BinaryTreeNode *pRoot)
// {
//     pTree->root = pRoot;
// }

BinaryTreeNode *binaryTreeNodeCreate(void *value)
{
    BinaryTreeNode *pNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));

    if (pNode == NULL)
    {
        return NULL;
    }

    pNode->value = value;
    pNode->nodeLeft = NULL;
    pNode->nodeRight = NULL;
    return pNode;
}

BinaryTreeNode *binaryTreeNodeGetLeft(BinaryTreeNode *pNode)
{
    return pNode->nodeLeft;
}

BinaryTreeNode *binaryTreeNodeGetRight(BinaryTreeNode *pNode)
{
    return pNode->nodeRight;
}

void *binaryTreeNodeGetValue(BinaryTreeNode *pNode)
{
    return pNode->value;
}

void binaryTreeNodeSetLeft(BinaryTreeNode *pNode, BinaryTreeNode *pNodeLeft)
{
    pNode->nodeLeft = pNodeLeft;
}

void binaryTreeNodeSetRight(BinaryTreeNode *pNode, BinaryTreeNode *pNodeRight)
{
    pNode->nodeRight = pNodeRight;
}

void binaryTreeNodeSetValue(BinaryTreeNode *pNode, void *value)
{
    pNode->value = value;
}

void binaryTreeNodeRemove(BinaryTreeNode * pNode)
{
}

void binaryTreeFree(BinaryTree * pTree)
{
}

