/**
 * Struct that represents a heap
 * 
 * @note Only use this heap to store data that has the same size as specified.
 * @note Only store one data type in each heap to be safe.
 * @note When storing elements, that itself contain dynamic memory, make sure to free it 
 * before freeing the element or the heap.
 */
typedef struct Heap Heap;

/**
 * Function that allocated memory for a heap struct
 * 
 * @param size the size of the elements that will be stored in the heap
 * @param isMaxHeap boolean that determines whether the heap should be a max or a min heap
 * 
 * @return Success: Pointer to the created heap | Failure: NULL
 */
Heap *heapCreate(int size, bool isMaxHeap);

/**
 * Function that adds an element to the heap
 * 
 * @param pHeap the pointer to the heap
 * @param value the pointer to the element
 * @param comparator the value that is used to sort all elements in the heap
 * 
 * @return Success: 0 | Failure: -1
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
 */
void *heapGetRoot(Heap *pHeap);

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
 * @note This function frees the pointers of the stored data. If a struct is stored, that itself contains a pointer, 
 * this pointer will not be freed.
 */
void heapFree(Heap *pHeap);
