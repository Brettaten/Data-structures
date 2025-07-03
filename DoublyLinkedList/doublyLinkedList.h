typedef struct DoublyLinkedList DoublyLinkedList;
typedef struct DoublyLinkedListNode DoublyLinkedListNode;

DoublyLinkedList *doublyLinkedListCreate(int size);
void *doublyLinkedListGet(DoublyLinkedList *pList, int index);
void doublyLinkedListSet(DoublyLinkedList *pList, void *value, int index);
void doublyLinkedListAdd(DoublyLinkedList *pList, void *value);
void doublyLinkedListAddIndex(DoublyLinkedList *pList, void *value, int index);
void doublyLinkedListRemove(DoublyLinkedList *pList, int index);
int doublyLinkedListLength(DoublyLinkedList *pList);
int doublyLinkedListSize(DoublyLinkedList *pList);
DoublyLinkedListNode *doublyLinkedListGetHead(DoublyLinkedList *pList);
DoublyLinkedListNode *doublyLinkedListGetTail(DoublyLinkedList *pList);
void doublyLinkedListFree(DoublyLinkedList *pList);