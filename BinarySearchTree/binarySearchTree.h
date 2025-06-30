typedef struct BinarySearchTree BinarySearchTree;
typedef struct BinarySearchTreeNode BinarySearchTreeNode;

BinarySearchTree *binarySearchTreeCreate();
BinarySearchTreeNode *binarySearchTreeGetRoot(BinarySearchTree *pTree);
BinarySearchTreeNode *binaryTreeNodeCreate(void *value, int key);
BinarySearchTreeNode *binarySearchTreeNodeGetLeft(BinarySearchTreeNode *pNode);
BinarySearchTreeNode *binarySearchTreeNodeGetRight(BinarySearchTreeNode *pNode);
BinarySearchTreeNode *binarySearchTreeNodeGetParent(BinarySearchTreeNode *pNode);
void *binarySearchTreeNodeGetValue(BinarySearchTreeNode *pNode);
void binarySearchTreeNodeSetValue(BinarySearchTreeNode *pNode, void *value);
void binarySearchTreeInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode);
BinarySearchTreeNode *binarySearchTreeGet(BinarySearchTree *pTree, int key);
void binarySearchTreeRemove(BinarySearchTree *pTree, int key);

void binarySearchTreeFree(BinarySearchTree *pTree);