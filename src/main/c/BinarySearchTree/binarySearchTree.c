#include <stdlib.h>
#include <stdio.h>

#include "binarySearchTree.h"
#include "../Stack/stack.h"

/**
 * 1.   Every node is either red or black.
 * 2.   All null nodes are considered black.
 * 3.   A red node does not have a red child.
 * 4.   Every path from a given node to any of its leaf nodes (that is, to any descendant null node) goes through the same number of black nodes.
 */

/**
 * Function that creates a node
 *
 * @param value pointer to the value
 * @param key the key that is used to order the tree
 *
 * @return Success: Pointer to the node | Failure: NULL
 *
 * @note The returned pointer has to be freed by the caller
 */
BinarySearchTreeNode *binaryTreeNodeCreate(void *value, int key);

/**
 * Function that fixes the tree after insertion
 *
 * @param pTree pointer to the tree
 * @param pNode pointer to the node
 */
void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode);

/**
 * Function that fixes the tree after deletion
 *
 * @param pTree pointer to the tree
 * @param pNode pointer to the node
 */
void fixDeletion(BinarySearchTree *pTree, BinarySearchTreeNode *pNode);

/**
 * Function that returns the case of the tree
 *
 * @param pNode pointer to the node
 * @param pSibling pointer to the sibling
 * @param isRight
 *
 * @return Success: The case | Failure: -1
 */
int getCase(BinarySearchTreeNode *pNode, BinarySearchTreeNode *pSibling, int isRight);

/**
 * Function that returns the color of a node
 *
 * @param pNode pointer to the node
 *
 * @return The color
 */
int getColor(BinarySearchTreeNode *pNode);

/**
 * Function that performs a left rotation
 *
 * @param pTree pointer to the tree
 * @param pNodeU pointer to the node
 */
void rotateLeft(BinarySearchTree *pTree, BinarySearchTreeNode *pNodeU);

/**
 * Function that performs a right rotation
 *
 * @param pTree pointer to the tree
 * @param pNodeV pointer to the node
 */
void rotateRight(BinarySearchTree *pTree, BinarySearchTreeNode *pNodeV);

/**
 * Function that returns the in order successor of the passes node
 *
 * @param pNode pointer to the node
 *
 * @return Success: The pointer to the node | Failure: NULL
 *
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *inOrderSuccessor(BinarySearchTreeNode *pNode);

/**
 * Function used to free a node
 *
 * @param pNode pointer to the node
 */
void binarySearchTreeFreeNode(BinarySearchTreeNode *pNode);

typedef struct BinarySearchTree
{
    BinarySearchTreeNode *root;
    int length;
    int size;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} BinarySearchTree;

typedef struct BinarySearchTreeNode
{
    BinarySearchTreeNode *left;
    BinarySearchTreeNode *right;
    BinarySearchTreeNode *parent;
    void *value;
    int key;
    int color;
} BinarySearchTreeNode;

enum Color
{
    BLACK,
    RED
};

BinarySearchTree *binarySearchTreeCreate(int size, void *(copyElement)(void *), void(freeElement)(void *))
{
    BinarySearchTree *pTree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));

    if (pTree == NULL)
    {
        printf("[ERROR] : Memory allocation failed | binarySearchTreeCreate \n");
        return NULL;
    }
    pTree->root = NULL;
    pTree->length = 0;
    pTree->size = size;
    pTree->copyElement = copyElement;
    pTree->freeElement = freeElement;

    return pTree;
}

BinarySearchTreeNode *binarySearchTreeGetRoot(BinarySearchTree *pTree)
{
    if (pTree == NULL)
    {
        printf("[ERROR] : The tree is null | binarySearchTreeGetRoot \n");
        return NULL;
    }

    return pTree->root;
}

BinarySearchTreeNode *binarySearchTreeNodeGetLeft(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : The node is null | binarySearchTreeNodeGetLeft \n");
        return NULL;
    }

    return pNode->left;
}

BinarySearchTreeNode *binarySearchTreeNodeGetRight(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : The node is null | binarySearchTreeNodeGetRight \n");
        return NULL;
    }

    return pNode->right;
}

BinarySearchTreeNode *binarySearchTreeNodeGetParent(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : The node is null | binarySearchTreeNodeGetParent \n");
        return NULL;
    }

    return pNode->parent;
}

void *binarySearchTreeNodeGetValue(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : The node is null | binarySearchTreeNodeGetValue \n");
        return NULL;
    }

    return pNode->value;
}

void binarySearchTreeNodeSetValue(BinarySearchTreeNode *pNode, void *value)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : The node is null | binarySearchTreeNodeSetValue \n");
        return;
    }

    if (value == NULL)
    {
        printf("[ERROR] : The value is null | binarySearchTreeNodeSetValue \n");
        return;
    }

    pNode->value = value;
}

void binarySearchTreeInsert(BinarySearchTree *pTree, void *value, int key)
{
    BinarySearchTreeNode *pNode = binaryTreeNodeCreate(value, key);

    if (pTree->root == NULL)
    {
        pNode->color = BLACK;
        pTree->root = pNode;
    }
    else
    {
        BinarySearchTreeNode *pTemp = pTree->root;
        while ((pTemp->left != NULL && key < pTemp->key) || (pTemp->right != NULL && key > pTemp->key))
        {
            if (key < pTemp->key)
            {
                pTemp = pTemp->left;
            }
            else if (key > pTemp->key)
            {
                pTemp = pTemp->right;
            }
            else
            {
                printf("[ERROR] : Multiple elements with the same key are not allowed | binarySearchTreeInsert \n");
                return;
            }
        }
        if (key < pTemp->key)
        {
            pTemp->left = pNode;
        }
        else if (key > pTemp->key)
        {
            pTemp->right = pNode;
        }
        pNode->parent = pTemp;

        if (pNode->parent->color == RED)
        {
            fixInsert(pTree, pNode);
        }
    }
    pTree->length++;
}

BinarySearchTreeNode *binarySearchTreeGet(BinarySearchTree *pTree, int key)
{
    if (pTree == NULL)
    {
        printf("[ERROR] : The tree is null | binarySearchTreeGet \n");
        return NULL;
    }

    if (pTree->length == 0)
    {
        printf("[INFO] : The tree is empty | binarySearchTreeGet \n");
        return NULL;
    }

    BinarySearchTreeNode *pNode = pTree->root;

    while (pNode->key != key)
    {
        if (key < pNode->key)
        {
            if (pNode->left == NULL)
            {
                return NULL;
            }
            pNode = pNode->left;
        }
        else
        {
            if (pNode->right == NULL)
            {
                return NULL;
            }
            pNode = pNode->right;
        }
    }
    return pNode;
}

void binarySearchTreeRemove(BinarySearchTree *pTree, int key)
{
    BinarySearchTreeNode *pNode = binarySearchTreeGet(pTree, key);

    if (pNode == NULL)
    {
        printf("Node not found!");
        return;
    }

    if (pNode->left == NULL && pNode->right == NULL)
    {
        if (pNode->parent == NULL)
        {
            pTree->root = NULL;
            binarySearchTreeFreeNode(pNode);
            return;
        }
        else if (pNode == pNode->parent->left)
        {
            pNode->parent->left = NULL;
        }
        else
        {
            pNode->parent->right = NULL;
        }

        if (pNode->color == BLACK)
        {
            fixDeletion(pTree, pNode);
        }
    }

    else if (pNode->left != NULL)
    {
        if (pNode->parent == NULL)
        {
            pNode->left->parent = NULL;
            pTree->root = pNode->left;
            pNode->left->color = BLACK;
            binarySearchTreeFreeNode(pNode);
            return;
        }
        else if (pNode == pNode->parent->left)
        {
            pNode->parent->left = pNode->left;
            pNode->left->parent = pNode->parent;
        }
        else
        {
            pNode->parent->right = pNode->left;
            pNode->left->parent = pNode->parent;
        }

        if (pNode->color == RED || pNode->left->color == RED)
        {
            pNode->left->color = BLACK;
        }
        else
        {
            fixDeletion(pTree, pNode);
        }
    }
    else if (pNode->right != NULL)
    {
        if (pNode->parent == NULL)
        {
            pNode->right->parent = NULL;
            pTree->root = pNode->right;
            pNode->right->color = BLACK;
            binarySearchTreeFreeNode(pNode);
            return;
        }
        else if (pNode == pNode->parent->left)
        {
            pNode->parent->left = pNode->right;
            pNode->right->parent = pNode->parent;
        }
        else
        {
            pNode->parent->right = pNode->right;
            pNode->right->parent = pNode->parent;
        }
        if (pNode->color == RED || pNode->right->color == RED)
        {
            pNode->right->color = BLACK;
        }
        else
        {
            fixDeletion(pTree, pNode);
        }
    }
    else
    {
        BinarySearchTreeNode *pSuccessor = inOrderSuccessor(pNode);

        void *pTemp = pNode->value;
        int temp = pNode->key;

        pNode->value = pSuccessor->value;
        pNode->key = pSuccessor->key;

        pSuccessor->value = pTemp;
        pSuccessor->key = temp;

        if (pSuccessor->right != NULL)
        {
            pSuccessor->parent->left = pSuccessor->right;
            pSuccessor->right->parent = pSuccessor->parent;

            if (pSuccessor->color == RED || pSuccessor->right->color == RED)
            {
                pSuccessor->right->color = BLACK;
            }
            else
            {
                fixDeletion(pTree, pSuccessor);
            }
        }
        else
        {
            pSuccessor->parent->left = NULL;

            if (pSuccessor->color == BLACK)
            {
                fixDeletion(pTree, pSuccessor);
            }
        }
        pNode = pSuccessor;
    }
    binarySearchTreeFreeNode(pNode);
}

void binarySearchTreeFree(BinarySearchTree *pTree)
{
    // Stack *pStack = stackCreate(sizeof(BinarySearchTreeNode), )
}

void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode)
{
    while (pNode != pTree->root && pNode->parent->color == RED)
    {
        if (pNode->parent == pNode->parent->parent->left)
        {
            BinarySearchTreeNode *u = pNode->parent->parent->right;
            if (u->color == RED)
            {
                pNode->parent->color = BLACK;
                u->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }
            else
            {
                if (pNode == pNode->parent->right)
                {
                    pNode = pNode->parent;
                    rotateLeft(pTree, pNode);
                }
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                rotateRight(pTree, pNode->parent->parent);
            }
        }
        else
        {
            BinarySearchTreeNode *u = pNode->parent->parent->left;
            if (u->color == RED)
            {
                pNode->parent->color = BLACK;
                u->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }
            else
            {
                if (pNode == pNode->parent->left)
                {
                    pNode = pNode->parent;
                    rotateRight(pTree, pNode);
                }
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                rotateLeft(pTree, pNode->parent->parent);
            }
        }
    }
    pTree->root->color = BLACK;
}

void fixDeletion(BinarySearchTree *pTree, BinarySearchTreeNode *pNode)
{
    BinarySearchTreeNode *pTemp = pNode;
    int isDoubleBlack = 1;

    while (pNode != pTree->root || isDoubleBlack == 1)
    {
        BinarySearchTreeNode *pSibling;
        int isRight = 0;
        if (pNode = pNode->parent->left)
        {
            pSibling = pNode->parent->right;
            isRight = 1;
        }
        else
        {
            pSibling = pNode->parent->left;
        }

        int deletionCase = getCase(pNode, pSibling, isRight);

        if (deletionCase == 4)
        {
            pNode->parent->color = BLACK;
            pSibling->color = RED;
            isDoubleBlack = 0;
        }
        else if (deletionCase == 6)
        {
            if (isRight == 1)
            {
                rotateLeft(pTree, pNode->parent);
                pSibling->right->color = BLACK;
            }
            else
            {
                rotateRight(pTree, pNode->parent);
                pSibling->left->color = BLACK;
            }
            int pColor = pNode->parent->color;
            pNode->parent->color = pSibling->color;
            pSibling->color = pColor;

            isDoubleBlack = 0;
        }
        else if (deletionCase == 2)
        {
            pSibling->color = RED;
            pNode = pNode->parent;
        }
        else if (deletionCase == 3)
        {
            if (isRight == 1)
            {
                rotateLeft(pTree, pNode->parent);
                int sColor = pSibling->color;
                pSibling->color = pSibling->left->color;
                pSibling->left->color = sColor;
            }
            else
            {
                rotateRight(pTree, pNode->parent);
                int sColor = pSibling->color;
                pSibling->color = pSibling->right->color;
                pSibling->right->color = sColor;
            }
        }
        else if (deletionCase == 5)
        {
            if (isRight == 1)
            {
                rotateRight(pTree, pSibling);
            }
            else
            {
                rotateLeft(pTree, pSibling);
            }
            int sColor = pSibling->color;
            pSibling->color = pSibling->parent->color;
            pSibling->parent->color = sColor;
        }
    }
    pNode = pTemp;
    pTree->root->color = BLACK;
}

int getCase(BinarySearchTreeNode *pNode, BinarySearchTreeNode *pSibling, int isRight)
{
    if (pNode->parent->color == RED)
    {
        if (pSibling == NULL || (getColor(pSibling) == BLACK && getColor(pSibling->left) == BLACK && getColor(pNode->right) == BLACK))
        {
            return 4;
        }
    }
    else if (pSibling != NULL && pSibling->color == BLACK)
    {
        if ((isRight == 1 && getColor(pSibling->right) == RED) || (isRight == 0 && getColor(pSibling->left) == RED))
        {
            return 6;
        }
        else if ((isRight == 1 && getColor(pSibling->left) == RED && getColor(pSibling->right) == BLACK) || (isRight == 0 && getColor(pSibling->right) == RED && getColor(pSibling->left) == BLACK))
        {
            return 5;
        }
    }
    else if (getColor(pSibling) == BLACK)
    {
        if (pSibling == NULL || (getColor(pSibling->left) == BLACK && getColor(pSibling->right) == BLACK))
        {
            return 2;
        }
    }
    else if (getColor(pSibling) == RED)
    {
        return 3;
    }
}

int getColor(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL || pNode->color == BLACK)
    {
        return BLACK;
    }
    return RED;
}

void rotateLeft(BinarySearchTree *pTree, BinarySearchTreeNode *pNodeU)
{
    BinarySearchTreeNode *pNodeV = pNodeU->right;
    pNodeU->right = pNodeV->left;

    if (pNodeV->left != NULL)
    {
        pNodeV->left->parent = pNodeU;
    }
    pNodeV->parent = pNodeU->parent;

    if (pNodeU->parent == NULL)
    {
        pTree->root = pNodeV;
    }
    else if (pNodeU->parent->left == pNodeU)
    {
        pNodeU->parent->left = pNodeV;
    }
    else
    {
        pNodeU->parent->right = pNodeV;
    }
    pNodeV->left = pNodeU;
    pNodeU->parent = pNodeV;
}

void rotateRight(BinarySearchTree *pTree, BinarySearchTreeNode *pNodeV)
{
    BinarySearchTreeNode *pNodeU = pNodeV->left;
    pNodeV->left = pNodeU->right;

    if (pNodeU->right != NULL)
    {
        pNodeU->right->parent = pNodeV;
    }
    pNodeU->parent = pNodeV->parent;

    if (pNodeV->parent == NULL)
    {
        pTree->root = pNodeU;
    }
    else if (pNodeV->parent->right == pNodeV)
    {
        pNodeV->parent->right = pNodeU;
    }
    else
    {
        pNodeV->parent->left = pNodeU;
    }
    pNodeU->right = pNodeV;
    pNodeV->parent = pNodeU;
}

BinarySearchTreeNode *inOrderSuccessor(BinarySearchTreeNode *pNode)
{
    if (pNode->right == NULL)
    {
        printf("The in-order successor for the given node does not exist!");
        return NULL;
    }

    pNode = pNode->right;

    while (pNode->left != NULL)
    {
        pNode = pNode->left;
    }
    return pNode;
}

BinarySearchTreeNode *binaryTreeNodeCreate(void *value, int key)
{
    BinarySearchTreeNode *pNode = (BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));

    if (pNode == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    pNode->key = key;
    pNode->value = value;
    pNode->color = RED;
    pNode->left = NULL;
    pNode->right = NULL;
    pNode->parent = NULL;

    return pNode;
}

void binarySearchTreeFreeNode(BinarySearchTreeNode *pNode)
{
    pNode->left = NULL;
    pNode->right = NULL;
    pNode->parent = NULL;

    free(pNode->value);
    free(pNode);
}
