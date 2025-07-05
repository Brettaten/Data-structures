typedef struct SinglyLinkedList SinglyLinkedList;
typedef struct SinglyLinkedListNode SinglyLinkedListNode;

SinglyLinkedList *singlyLinkedListCreate(int size);
void *singlyLinkedListGet(SinglyLinkedList *pList, int index);
int singlyLinkedListSet(SinglyLinkedList *pList, void *value, int index);
int singlyLinkedListAdd(SinglyLinkedList *pList, void *value);
int singlyLinkedListAddIndex(SinglyLinkedList *pList, void *value, int index);
int singlyLinkedListRemove(SinglyLinkedList *pList, int index);
int singlyLinkedListLength(SinglyLinkedList *pList);
int singlyLinkedListSize(SinglyLinkedList *pList);
SinglyLinkedListNode *singlyLinkedListGetHead(SinglyLinkedList *pList);
void singlyLinkedListFree(SinglyLinkedList *pList);