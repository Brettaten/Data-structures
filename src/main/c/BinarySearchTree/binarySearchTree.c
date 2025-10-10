#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
BinarySearchTreeNode *binarySearchTreeNodeCreate(BinarySearchTree *pTree, void *value, int key);

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
 * Function used to copy a node
 *
 * @param pNode pointer to the node
 *
 * @return The copy of the passed node
 *
 * @note The returned pointer is a deep copy and thus has to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeCopyNode(BinarySearchTreeNode *pNode);

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
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
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
    if (pTree == NULL)
    {
        printf("[ERROR] : Tree is null | binarySearchTreeInsert \n");
        return;
    }
    if (value == NULL)
    {
        printf("[ERROR] : Value is null | binarySearchTreeInsert \n");
        return;
    }

    BinarySearchTreeNode *pNode = binarySearchTreeNodeCreate(pTree, value, key);

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
    if (pTree == NULL)
    {
        printf("[ERROR] : Tree is null | binarySearchTreeRemove \n");
        return;
    }

    BinarySearchTreeNode *pNode = binarySearchTreeGet(pTree, key);

    if (pNode == NULL)
    {
        printf("[ERROR] : There is no Node with the passed key in the tree | binarySearchTreeRemove \n");
        return;
    }

    if (pNode->left == NULL && pNode->right == NULL)
    {
        if (pNode->parent == NULL)
        {
            pTree->root = NULL;
            binarySearchTreeFreeNode(pNode);
            pTree->length--;
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

    else if (pNode->left != NULL && pNode->right == NULL)
    {
        if (pNode->parent == NULL)
        {
            pNode->left->parent = NULL;
            pTree->root = pNode->left;
            pNode->left->color = BLACK;
            binarySearchTreeFreeNode(pNode);
            pTree->length--;
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
        pNode->left->color = BLACK;
    }
    else if (pNode->right != NULL && pNode->left == NULL)
    {
        if (pNode->parent == NULL)
        {
            pNode->right->parent = NULL;
            pTree->root = pNode->right;
            pNode->right->color = BLACK;
            binarySearchTreeFreeNode(pNode);
            pTree->length--;
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
        pNode->right->color = BLACK;
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

            pSuccessor->right->color = BLACK;
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
    pTree->length--;
}

void *binarySearchTreeCopy(void *pTree)
{
    BinarySearchTree *cp = (BinarySearchTree *)pTree;

    if (cp == NULL)
    {
        printf("[ERROR] : Tree is null | binarySearchTreeCopy \n");
        return NULL;
    }

    BinarySearchTree *copy = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | binarySearchTreeCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;
    copy->length = cp->length;
    copy->size = cp->size;

    BinarySearchTreeNode *pNode = cp->root;
    BinarySearchTreeNode *pCopy = binarySearchTreeCopyNode(pNode);
    copy->root = pCopy;

    Stack *pStackNode = stackCreate(sizeof(BinarySearchTreeNode), cp->copyElement, cp->freeElement);
    stackPush(pStackNode, pNode);

    Stack *pStackCopy = stackCreate(sizeof(BinarySearchTreeNode*), NULL, NULL);
    stackPush(pStackCopy, &pCopy);

    while (stackLength(pStackNode) > 0)
    {
        BinarySearchTreeNode *tempNode = (BinarySearchTreeNode *)(stackPop(pStackNode));
        pNode = tempNode;

        BinarySearchTreeNode **tempCopy = (BinarySearchTreeNode **)(stackPop(pStackCopy));
        pCopy = *tempCopy;

        if (pNode->left != NULL)
        {
            pCopy->left = binarySearchTreeCopyNode(pNode->left);
            pCopy->left->parent = pCopy;

            stackPush(pStackNode, pNode->left);
            stackPush(pStackCopy, &pCopy->left);
        }
        if (pNode->right != NULL)
        {
            pCopy->right = binarySearchTreeCopyNode(pNode->right);
            pCopy->right->parent = pCopy;

            stackPush(pStackNode, pNode->right);
            stackPush(pStackCopy, &pCopy->right);
        }

        binarySearchTreeFreeNode(tempNode);
        free(tempCopy);
    }

    stackFree(pStackNode);
    stackFree(pStackCopy);

    return copy;
}

void binarySearchTreeFree(void *pTree)
{
    BinarySearchTree *cp = (BinarySearchTree *)pTree;

    if (cp == NULL)
    {
        printf("[ERROR] : Tree is null | binarySearchTreeFree \n");
        return;
    }

    if (cp->root == NULL)
    {
        free(pTree);
        return;
    }

    BinarySearchTreeNode *pNode = cp->root;

    Stack *pStack = stackCreate(sizeof(BinarySearchTreeNode *), NULL, NULL);
    stackPush(pStack, &pNode);

    while (stackLength(pStack) > 0)
    {
        BinarySearchTreeNode **temp = (BinarySearchTreeNode **)(stackPop(pStack));
        pNode = *temp;

        if (pNode->left != NULL)
        {
            stackPush(pStack, &pNode->left);
        }
        if (pNode->right != NULL)
        {
            stackPush(pStack, &pNode->right);
        }

        binarySearchTreeFreeNode(pNode);
        free(temp);
    }

    free(cp);

    stackFree(pStack);
}

void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode)
{
    if (pTree == NULL)
    {
        printf("[ERROR] : Tree is null | fixInsert \n");
        return;
    }
    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | fixInsert \n");
        return;
    }

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
    if (pTree == NULL)
    {
        printf("[ERROR] : Tree is null | fixDeletion \n");
        return;
    }
    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | fixDeletion \n");
        return;
    }

    BinarySearchTreeNode *pTemp = pNode;
    bool isDoubleBlack = true;

    while (pNode->parent != NULL && isDoubleBlack)
    {
        BinarySearchTreeNode *pSibling;
        bool isRight = false;
        if (pNode = pNode->parent->left)
        {
            pSibling = pNode->parent->right;
            isRight = true;
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
            isDoubleBlack = false;
        }
        else if (deletionCase == 6)
        {
            if (isRight)
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

            isDoubleBlack = false;
        }
        else if (deletionCase == 2)
        {
            pSibling->color = RED;
            pNode = pNode->parent;
        }
        else if (deletionCase == 3)
        {
            if (isRight)
            {
                rotateLeft(pTree, pNode->parent);
                pSibling->color = BLACK;
                pSibling->left->color = RED;
            }
            else
            {
                rotateRight(pTree, pNode->parent);
                pSibling->color = BLACK;
                pSibling->right->color = RED;
            }
        }
        else if (deletionCase == 5)
        {
            if (isRight)
            {
                rotateRight(pTree, pSibling);
            }
            else
            {
                rotateLeft(pTree, pSibling);
            }
            pSibling->color = RED;
            pSibling->parent->color = BLACK;
        }
    }

    if (pNode->parent == NULL)
    {
        pTree->root = pNode;
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
        if ((isRight == true && getColor(pSibling->right) == RED) || (isRight == false && getColor(pSibling->left) == RED))
        {
            return 6;
        }
        else if ((isRight == true && getColor(pSibling->left) == RED && getColor(pSibling->right) == BLACK) || (isRight == false && getColor(pSibling->right) == RED && getColor(pSibling->left) == BLACK))
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

    printf("[ERROR] : No case was found | getCase \n");
    return -1;
}

int getColor(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : Node can not be null | getColor \n");
        return -1;
    }

    if (pNode == NULL || pNode->color == BLACK)
    {
        return BLACK;
    }
    return RED;
}

void rotateLeft(BinarySearchTree *pTree, BinarySearchTreeNode *pNodeU)
{
    if (pTree == NULL)
    {
        printf("[ERROR] : The tree is null | rotateLeft \n");
        return;
    }
    if (pNodeU == NULL)
    {
        printf("[ERROR] : The node is null | rotateLeft \n");
        return;
    }
    if (pNodeU->right == NULL)
    {
        printf("[ERROR] : The node needs a right child to perform a left rotation | rotateLeft \n");
        return;
    }

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
    if (pTree == NULL)
    {
        printf("[ERROR] : The tree is null | rotateLeft \n");
        return;
    }
    if (pNodeV == NULL)
    {
        printf("[ERROR] : The node is null | rotateLeft \n");
        return;
    }
    if (pNodeV->left == NULL)
    {
        printf("[ERROR] : The node needs a left child to perform a left rotation | rotateLeft \n");
        return;
    }

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
        printf("[ERROR] : The in-order successor for the given node does not exist | inOrderSuccessor \n");
        return NULL;
    }

    BinarySearchTreeNode *successor = pNode->right;

    while (successor->left != NULL)
    {
        successor = successor->left;
    }
    return successor;
}

BinarySearchTreeNode *binarySearchTreeNodeCreate(BinarySearchTree *pTree, void *value, int key)
{
    if (pTree == NULL)
    {
        printf("[ERROR] : Tree is null | binarySearchTreeNodeCreate \n");
        return NULL;
    }
    if (value == NULL)
    {
        printf("[ERROR] : Value is null | binarySearchTreeNodeCreate \n");
        return NULL;
    }
    BinarySearchTreeNode *pNode = (BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));

    if (pNode == NULL)
    {
        printf("[ERROR] : Memory allocation failed | binarySearchTreeNodeCreate \n");
        return NULL;
    }
    pNode->key = key;
    pNode->value = value;
    pNode->color = RED;
    pNode->left = NULL;
    pNode->right = NULL;
    pNode->parent = NULL;
    pNode->copyElement = pTree->copyElement;
    pNode->freeElement = pTree->freeElement;

    return pNode;
}

BinarySearchTreeNode *binarySearchTreeCopyNode(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | binarySearchTreeCopyNode \n");
        return NULL;
    }

    void *value = pNode->copyElement(pNode->value);

    BinarySearchTreeNode *pCopy = (BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));

    if (pNode == NULL)
    {
        printf("[ERROR] : Memory allocation failed | binarySearchTreeNodeCreate \n");
        return NULL;
    }

    pNode->key = pNode->key;
    pNode->value = value;
    pCopy->color = pNode->color;
    pCopy->left = pNode->left;
    pCopy->right = pNode->right;
    pCopy->parent = pNode->parent;
    pNode->copyElement = pNode->copyElement;
    pNode->freeElement = pNode->freeElement;

    return pCopy;
}

void binarySearchTreeFreeNode(BinarySearchTreeNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | binarySearchTreeFreeNode \n");
        return;
    }

    pNode->left = NULL;
    pNode->right = NULL;
    pNode->parent = NULL;

    if (pNode->freeElement == NULL)
    {
        free(pNode->value);
    }
    else
    {
        pNode->freeElement(pNode->value);
    }
    free(pNode);
}
