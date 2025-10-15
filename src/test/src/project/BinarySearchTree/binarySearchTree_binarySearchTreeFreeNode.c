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












































void binarySearchTreeFreeNode(void *node)
{
    BinarySearchTreeNode *pNode = (BinarySearchTreeNode *)node;
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
