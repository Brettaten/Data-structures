typedef struct LinkedList LinkedList;
typedef struct LinkedListNode LinkedListNode;

LinkedList *linkedListCreate(int size);
void *linkedListGet(LinkedList *pList, int index);
void linkedListSet(LinkedList *pList, void *value, int index);
void linkedListAdd(LinkedList *pList, void *value);
void linkedListAddIndex(LinkedList *pList, void *value, int index);
void linkedListRemove(LinkedList *pList, int index);
int linkedListLength(LinkedList *pList);
int linkedListSize(LinkedList *pList);
LinkedListNode *linkedListGetHead(LinkedList *pList);
void linkedListFree(LinkedList *pList);