typedef struct Queue Queue;

Queue *queueCreate(int size);
int queuePush(Queue *pQueue, void *value);
void *queuePop(Queue *pQueue);
void *queuePeek(Queue *pQueue);
int queueLength(Queue *pQueue);
int queueSize(Queue *pQueue);
void queueFree(Queue *pQueue);