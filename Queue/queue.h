/**
 * Struct that represents a queue
 * 
 * @note Only use this queue to store data that has the same size as specified.
 * @note Only store one data type in each queue to be safe.
 * @note When storing elements, that itself contain dynamic memory, make sure to free it 
 * before freeing the element or the queue.
 */
typedef struct Queue Queue;

/**
 * Function that allocated memory for a queue struct
 * 
 * @param size the size of the elements that will be stored in the queue
 * 
 * @return Success: Pointer to the created queue | Failure: NULL
 */
Queue *queueCreate(int size);

/**
 * Function that adds an element to the queue
 * 
 * @param pStack the pointer to the queue
 * @param value the pointer to the element
 * 
 * @return Success: 0 | Failure: -1
 */
int queuePush(Queue *pQueue, void *value);

/**
 * Function that removes an element from the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the pointer to the removed element | Failure: NULL
 */
void *queuePop(Queue *pQueue);

/**
 * Function that retrieves the top element from the queue
 * 
 * @param pStack the pointer to the queue
 * 
 * @return Success: the pointer to top element | Failure: NULL
 */
void *queuePeek(Queue *pQueue);

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
 * @note This function frees the pointers of the stored data. If a struct is stored, that itself contains a pointer, 
 * this pointer will not be freed.
 */
void queueFree(Queue *pQueue);