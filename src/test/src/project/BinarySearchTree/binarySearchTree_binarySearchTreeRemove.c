#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
 * @param isSibRight location of the sibling
 */

void fixDeletion(BinarySearchTree *pTree, BinarySearchTreeNode *pNode, bool isSibRight);


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
 * @param nree pointer to the node
 *
 * @return The copy of the passed node
 *
 * @note The returned pointer is a deep copy and thus has to be freed by the caller
 */

void *binarySearchTreeCopyNode(void *node);


/**
 * Function used to free a node
 *
 * @param nde pointer to the node
 */

void binarySearchTreeFreeNode(void *node);


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
    int size;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} BinarySearchTreeNode;


enum Color
{
    BLACK,
    RED
};




















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
        bool isSibRight;

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
            isSibRight = true;
        }
        else
        {
            pNode->parent->right = NULL;
            isSibRight = false;
        }

        if (pNode->color == BLACK)
        {
            fixDeletion(pTree, pNode, isSibRight);
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
        bool isSibRight;

        void *pTemp = pNode->value;
        int temp = pNode->key;

        pNode->value = pSuccessor->value;
        pNode->key = pSuccessor->key;

        pSuccessor->value = pTemp;
        pSuccessor->key = temp;

        if (pSuccessor->right != NULL)
        {
            if (pSuccessor == pSuccessor->parent->left)
            {
                pSuccessor->parent->left = pSuccessor->right;
            }
            else
            {
                pSuccessor->parent->right = pSuccessor->right;
            }

            pSuccessor->right->parent = pSuccessor->parent;
            pSuccessor->right->color = BLACK;
        }
        else
        {
            if (pSuccessor == pSuccessor->parent->left)
            {
                pSuccessor->parent->left = NULL;
                isSibRight = true;
            }
            else
            {
                pSuccessor->parent->right = NULL;
                isSibRight = false;
            }

            if (pSuccessor->color == BLACK)
            {
                fixDeletion(pTree, pSuccessor, isSibRight);
            }
        }
        pNode = pSuccessor;
    }
    binarySearchTreeFreeNode(pNode);
    pTree->length--;
}
