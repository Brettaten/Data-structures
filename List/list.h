typedef struct List List;

List *listCreate(int size);
void *listGet(List *pList, int index);
int listSet(List *pList, void *value, int index);
int listAdd(List *pList, void *value);
int listAddIndex(List *pList, void *value, int index);
int listRemove(List *pList, int index);
int listLength(List *pList);
int listSize(List *pList);
void listFree(List *pList);
