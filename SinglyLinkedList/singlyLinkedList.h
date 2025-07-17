/**
 * Struct that represents a singly linked list
 */
typedef struct SinglyLinkedList SinglyLinkedList;

/**
 * Struct that represents node of a singly linked list
 */
typedef struct SinglyLinkedListNode SinglyLinkedListNode;

/**
 * Function that allocated memory for a singly linked list struct
 * 
 * @param size the size of the elements that will be stored in the list
 * 
 * @return Success: Pointer to the created list | Failure: NULL
 */
SinglyLinkedList *singlyLinkedListCreate(int size);

/**
 * Function that retrieves the element of the list at the passed index
 * 
 * @param pList pointer to the list
 * @param index position in the list
 * 
 * @return Success: Pointer to the element at the passed index | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *singlyLinkedListGet(SinglyLinkedList *pList, int index);

/**
 * Function that replaces the element of the list at the passed index with a new one
 * 
 * @param pList pointer to the list
 * @param value pointer to the element that should replace the old element
 * @param index position in the list
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap. 
 * The function creates a deep copy of the value before adding it to the list.
 */
int singlyLinkedListSet(SinglyLinkedList *pList, void *value, int index);

/**
 * Function used to add the passed value to the end of the list
 * 
 * @param pList pointer to the list
 * @param value pointer to a value
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap. 
 * The function creates a deep copy of the value before adding it to the list.
 */
int singlyLinkedListAdd(SinglyLinkedList *pList, void *value);

/**
 * Function used to add the passed value at a specific index
 * 
 * @param pList pointer to the list
 * @param value pointer to a value
 * @param index position in the list
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap. 
 * The function creates a deep copy of the value before adding it to the list.
 */
int singlyLinkedListAddIndex(SinglyLinkedList *pList, void *value, int index);

/**
 * Function used to remove the data at the specified index
 * 
 * @param pList pointer to the list
 * @param index position in the list
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note This function only frees the pointer. If a struct is stored, that itself contains a pointer, 
 * this pointer will not be freed.
 */
int singlyLinkedListRemove(SinglyLinkedList *pList, int index);

/**
 * Function used to return the length of the list
 * 
 * @param pList pointer to the list
 * 
 * @return Success: length | Failure: -1
 */
int singlyLinkedListLength(SinglyLinkedList *pList);

/**
 * Function used to return the size of the data that the list stores
 * 
 * @param pList pointer to the list
 * 
 * @return Success: size | Failure: -1
 */
int singlyLinkedListSize(SinglyLinkedList *pList);

/**
 * Function used to return the head of the list
 * 
 * @param pList pointer to the list
 * 
 * @return Success: pointer to the head of the list | Failure: NULL
 * 
 * @note This function is used to get the head of the list. This is useful for traversing the list.
 */
SinglyLinkedListNode *singlyLinkedListGetHead(SinglyLinkedList *pList);

/**
 * Function used to get the next node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: pointer to the next node | Failure: NULL
 */
SinglyLinkedListNode *singlyLinkedListNodeNext(SinglyLinkedListNode *pNode);

/**
 * Function used to get the value of a node
 * 
 * @param pList pointer to the list
 * @param pNode pointer to the node
 * 
 * @return Success: value of the node | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *singlyLinkedListNodeGet(SinglyLinkedList *pList, SinglyLinkedListNode *pNode);

/**
 * Function used to set the value of a node directly
 * 
 * @param pList pointer to the list
 * @param pNode pointer to the list
 * @param value ponter to the value
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap. 
 * The function creates a deep copy of the value before adding it to the list.
 */
int singlyLinkedListNodeSet(SinglyLinkedList *pList, SinglyLinkedListNode *pNode, void *value);

/**
 * Function used to free the passed list
 * 
 * @param pList pointer to the list
 * 
 * @return void
 * 
 * @note This function frees the pointers of the stored data. If a struct is stored, that itself contains a pointer, 
 * this pointer will not be freed.
 */
void singlyLinkedListFree(SinglyLinkedList *pList);