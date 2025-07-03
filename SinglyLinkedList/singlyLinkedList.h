typedef struct SinglyLinkedList SinglyLinkedList;
typedef struct SinglyLinkedListNode SinglyLinkedListNode;

SinglyLinkedList *singlyLinkedListCreate(int size);
void *singlyLinkedListGet(SinglyLinkedList *pList, int index);
void singlyLinkedListSet(SinglyLinkedList *pList, void *value, int index);
void singlyLinkedListAdd(SinglyLinkedList *pList, void *value);
void singlyLinkedListAddIndex(SinglyLinkedList *pList, void *value, int index);
void singlyLinkedListRemove(SinglyLinkedList *pList, int index);
int singlyLinkedListLength(SinglyLinkedList *pList);
int singlyLinkedListSize(SinglyLinkedList *pList);
SinglyLinkedListNode *singlyLinkedListGetHead(SinglyLinkedList *pList);
void singlyLinkedListFree(SinglyLinkedList *pList);