/**
 * Struct that represents a queue
 * 
 * @note Only use this queue to store data that has the same size as specified.
 * @note Only store one data type in each queue to be safe.
 */
typedef struct Queue Queue;

/**
 * Function that allocated memory for a queue struct
 * 
 * @param size the size of the elements that will be stored in the queue
 * @param copyElement pointer to a function that deep copies an element, pass NULL for elements, where a shallow copy is sufficient
 * @param freeElement pointer to a function that deep frees an element, pass NULL for elements, where a shallow free is sufficient
 * 
 * @return Success: Pointer to the created queue | Failure: NULL
 */
Queue *queueCreate(int size, void *(*copyElement)(void *), void(*freeElement)(void *));

/**
 * Function that adds an element to the queue
 * 
 * @param pStack the pointer to the queue
 * @param value the pointer to the element
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int queuePush(Queue *pQueue, void *value);

/**
 * Function that removes an element from the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the pointer to the removed element | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *queuePop(Queue *pQueue);

/**
 * Function that retrieves the top element from the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the pointer to top element | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *queuePeek(Queue *pQueue);

/**
 * Function used to create a deep copy of a queue
 *
 * @param pStack the pointer to the queue
 *
 * @return Success: the copy of the queue | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *queueCopy(void *pQueue);

/**
 * Function that returns the length of the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the length of the queue | Failure: -1
 */
int queueLength(Queue *pQueue);

/**
 * Function that returns the size of the data that is stored in the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the size | Failure: -1
 */
int queueSize(Queue *pQueue);

/**
 * Function used to free the passed queue
 * 
 * @param pQueue the pointer to the queue
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void queueFree(void *pQueue);