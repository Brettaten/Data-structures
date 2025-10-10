/**
 * Struct that represents a binary search tree
 *
 * @note Only use this tree to store data that has the same size as specified.
 * @note Only store one data type in each list to be safe.
 */
typedef struct BinarySearchTree BinarySearchTree;

/**
 * Struct that represents node of a binary search tree
 */
typedef struct BinarySearchTreeNode BinarySearchTreeNode;

/**
 * Function that allocates memory for a binary search tree struct
 *
 * @param size the size of the elements that will be stored in the list
 * @param copyElement pointer to a function that deep copies an element, pass NULL for elements, where a shallow copy is sufficient
 * @param freeElement pointer to a function that deep frees an element, pass NULL for elements, where a shallow free is sufficient
 *
 * @return Success: Pointer to the created list | Failure: NULL
 */
BinarySearchTree *binarySearchTreeCreate(int size, void *(copyElement)(void *), void(freeElement)(void *));

/**
 * Function that returns the root of the tree
 * 
 * @param pTree pointer to the tree
 * 
 * @return Success: Pointer to the root | Failure: NULL
 * 
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeGetRoot(BinarySearchTree *pTree);

/**
 * Function that returns the left child of a node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: Pointer to the node | Failure: NULL
 * 
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeNodeGetLeft(BinarySearchTreeNode *pNode);

/**
 * Function that returns the right child of a node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: Pointer to the node | Failure: NULL
 * 
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeNodeGetRight(BinarySearchTreeNode *pNode);

/**
 * Function that returns the parent of a node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: Pointer to the node | Failure: NULL
 * 
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeNodeGetParent(BinarySearchTreeNode *pNode);

/**
 * Function that returns the value of the passed node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: Pointer to the value | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *binarySearchTreeNodeGetValue(BinarySearchTreeNode *pNode);

/**
 * Function that sets the value of the passed node
 * 
 * @param pNode pointer to the node
 * @param value pointer to the value
 * 
 * @return Success: Pointer to the value | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void binarySearchTreeNodeSetValue(BinarySearchTreeNode *pNode, void *value);

/**
 * Function that inserts a node
 * 
 * @param pTree pointer to the tree
 * @param value pointer to the value
 * @param key the key
 * 
 * @note The new node will be red, if a red violation occurrs it has to be fixed
 */
void binarySearchTreeInsert(BinarySearchTree *pTree, void *value, int key);

/**
 * Function that searches a node with the passed key
 * 
 * @param pTree pointer to the tree
 * @param key the key
 * 
 * @return Success: Pointer to the node | Failure: NULL
 * 
 * @note The returned pointer does not have to be freed by the caller
 */
BinarySearchTreeNode *binarySearchTreeGet(BinarySearchTree *pTree, int key);

/**
 * Function that removes a node with the passed key
 * 
 * @param pTree pointer to the tree
 * @param key the key
 */
void binarySearchTreeRemove(BinarySearchTree *pTree, int key);

/**
 * Function used to copy the passed tree
 * 
 * @param pTree pointer to the tree
 * 
 * @return Success: Pointer to the copied tree | Failure: NULL
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *binarySearchTreeCopy(void *pTree);

/**
 * Function used to free the passed tree
 *
 * @param pTree pointer to the tree
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 * 
 */
void binarySearchTreeFree(void *pTree);