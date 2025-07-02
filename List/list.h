typedef struct List List;

List *listCreate(int size);
void *listGet(List *pList, int index);
void listSet(List *pList, void *value, int index);
void listAdd(List *pList, void *value);
void listAddIndex(List *pList, void *value, int index);
void listRemove(List *pList, int index);
int listLength(List *pList);
int listSize(List *pList);
void listFree(List *pList);
