typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeNode BinaryTreeNode;

BinaryTree *binaryTreeCreate();
BinaryTreeNode *binaryTreeGetRoot(BinaryTree *pTree);
// void binaryTreeSetRoot(BinaryTree *pTree, BinaryTreeNode *pRoot);
BinaryTreeNode *binaryTreeNodeCreate(void *value);
BinaryTreeNode *binaryTreeNodeGetLeft(BinaryTreeNode *pNode);
BinaryTreeNode *binaryTreeNodeGetRight(BinaryTreeNode *pNode);
void *binaryTreeNodeGetValue(BinaryTreeNode *pNode);
void binaryTreeNodeSetLeft(BinaryTreeNode *pNode, BinaryTreeNode *pNodeLeft);
void binaryTreeNodeSetRight(BinaryTreeNode *pNode, BinaryTreeNode *pNodeRight);
void binaryTreeNodeSetValue(BinaryTreeNode *pNode, void *value);
void binaryTreeNodeRemove(BinaryTreeNode *pNode);

void binaryTreeFree(BinaryTree *pTree);