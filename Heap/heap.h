/**
 * Struct that represents a heap
 * 
 * @note Only use this heap to store data that has the same size as specified.
 * @note Only store one data type in each heap to be safe.
 */
typedef struct Heap Heap;

/**
 * Function that allocated memory for a heap struct
 * 
 * @param size the size of the elements that will be stored in the heap
 * @param isMaxHeap boolean that determines whether the heap should be a max or a min heap
 * @param copyElement pointer to a function that deep copies an element, pass NULL for elements, where a shallow copy is sufficient
 * @param freeElement pointer to a function that deep frees an element, pass NULL for elements, where a shallow free is sufficient
 * 
 * @return Success: Pointer to the created heap | Failure: NULL
 */
Heap *heapCreate(int size, bool isMaxHeap, void *(*copyElement)(void *), void(*freeElement)(void *));

/**
 * Function that adds an element to the heap
 * 
 * @param pHeap the pointer to the heap
 * @param value the pointer to the element
 * @param comparator the value that is used to sort all elements in the heap
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int heapAdd(Heap *pHeap, void *value, int comparator);

/**
 * Function that removes the root element from the heap
 * 
 * @param pHeap the pointer to the heap
 * 
 * @return Success: 0 | Failure: -1
 */
int heapRemove(Heap *pHeap);

/**
 * Function that retrieves the root element from the heap
 * 
 * @param pHeap the pointer to the heap
 * 
 * @return Success: the pointer to top element | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *heapGetRoot(Heap *pHeap);

/**
 * Function used to create a deep copy of a heap
 *
 * @param pHeap the pointer to the heap
 *
 * @return Success: the copy of the heap | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *heapCopy(void *pHeap);

/**
 * Function that returns the length of the heap
 * 
 * @param pHeap the pointer to the heap
 * 
 * @return Success: the length of the heap | Failure: -1
 */
int heapLength(Heap *pHeap);

/**
 * Function that returns the size of the data that is stored in the heap
 * 
 * @param pHeap the pointer to the heap
 * 
 * @return Success: the size | Failure: -1
 */
int heapSize(Heap *pHeap);

/**
 * Function used to free the passed heap
 * 
 * @param pHeap the pointer to the heap
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void heapFree(void *pHeap);
