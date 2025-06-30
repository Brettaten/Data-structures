typedef struct Queue Queue;

Queue *queueCreate();
void queuePush(Queue *pQueue, void *value);
void *queuePop(Queue *pQueue);
int queueLength(Queue *pQueue);

void queueFree(Queue *pQueue);