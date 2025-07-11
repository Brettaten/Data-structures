typedef struct Heap Heap;

Heap *heapCreate(int size, bool isMaxHeap);
int heapAdd(Heap *pHeap, void *value, int comparator);
int heapRemove(Heap *pHeap);
void *heapGetRoot(Heap *pHeap);
int heapLength(Heap *pHeap);
int heapSize(Heap *pHeap);
void heapFree(Heap *pHeap);
