#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(HashMap *pMap);
void addBig(HashMap *pMap, char *cp);
void *copyBig(void *big);
void freeBig(void *big);
uint64_t hashBig(void *value, int size);
bool equalsBig(void *value1, void *value2, int size);

int main()
{
    HashMap *pMap = hashMapCreate(sizeof(int), NULL, NULL, sizeof(int), NULL, NULL, NULL, NULL);
    add(pMap);
    int key = 5;
    int newValue = 6;

    hashMapSet(pMap, &newValue, &key);
    int *value = hashMapGet(pMap, &key);
    printf("Key 5:%d\n", *value);

    hashMapRemove(pMap, &key);
    int lengthHash = hashMapLength(pMap);
    printf("Length: %d\n", lengthHash);

    HashMap *pCopy = hashMapCopy(pMap);
    hashMapAdd(pCopy, &newValue, &key);

    printf("HashMap original\n");
    List *pDump = hashMapToList(pMap);

    for (int i = 0; i < listLength(pDump); i++)
    {
        HashMapNode *temp = listGet(pDump, i);
        int *tempValue = (int *)hashMapNodeGetValue(pMap, temp);
        int *tempKey = (int *)hashMapNodeGetKey(pMap, temp);
        uint64_t hash = hashMapNodeGetHash(temp);
        HashMapNode *tempCopy = hashMapNodeCopy(temp);
        hashMapNodeFree(tempCopy);
        printf("%d\n", *tempValue);
    }

    printf("HashMap copy\n");
    List *pDumpCopy = hashMapToList(pCopy);

    for (int i = 0; i < listLength(pDumpCopy); i++)
    {
        HashMapNode *temp = listGet(pDumpCopy, i);
        int *tempValue = (int *)hashMapNodeGetValue(pCopy, temp);
        printf("%d\n", *tempValue);
    }

    HashMap *pMapBig = hashMapCreate(sizeof(BigObj), &copyBig, &freeBig, sizeof(BigObj), &copyBig, &freeBig, &hashBig, &equalsBig);
    char *c = "rr";
    addBig(pMapBig, c);

    BigObj *keyBig = (BigObj *)malloc(sizeof(BigObj));
    keyBig->id = 5;
    keyBig->str = "rr";

    BigObj *newValueBig = (BigObj *)malloc(sizeof(BigObj));
    newValueBig->id = 6;
    newValueBig->str = "rr";

    hashMapSet(pMapBig, newValueBig, keyBig);
    BigObj *valueBig = hashMapGet(pMapBig, keyBig);
    printf("Key 5:%d\n", valueBig->id);

    hashMapRemove(pMapBig, keyBig);
    int lengthHashBig = hashMapLength(pMapBig);
    printf("Length: %d\n", lengthHashBig);

    HashMap *pCopyBig = hashMapCopy(pMapBig);
    hashMapAdd(pCopyBig, newValueBig, keyBig);

    printf("HashMap original\n");
    List *pDumpBig = hashMapToList(pMapBig);

    for (int i = 0; i < listLength(pDumpBig); i++)
    {
        HashMapNode *tempBig = listGet(pDumpBig, i);
        BigObj *tempValueBig = (BigObj *)hashMapNodeGetValue(pMapBig, tempBig);
        BigObj *tempKeyBig = (BigObj *)hashMapNodeGetKey(pMapBig, tempBig);
        uint64_t hashBig = hashMapNodeGetHash(tempBig);
        HashMapNode *tempCopyBig = hashMapNodeCopy(tempBig);
        hashMapNodeFree(tempCopyBig);
        printf("%d\n", tempValueBig->id);
    }

    printf("HashMap copy\n");
    List *pDumpCopyBig = hashMapToList(pCopyBig);

    for (int i = 0; i < listLength(pDumpCopyBig); i++)
    {
        HashMapNode *tempBig = listGet(pDumpCopyBig, i);
        BigObj *tempValueBig = (BigObj *)hashMapNodeGetValue(pCopyBig, tempBig);
        printf("%d\n", tempValueBig->id);
    }
}

void add(HashMap *pMap)
{
    for (int i = 0; i < 20; i++)
    {
        hashMapAdd(pMap, &i, &i);
    }
}

void addBig(HashMap *pMap, char *cp)
{
    for (int i = 0; i < 20; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        hashMapAdd(pMap, big, big);
    }
}

void *copyBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    char *cp = (char *)malloc(sizeof(char) * (pBig->id + 1));

    if (cp == NULL)
    {
        printf("LOL");
    }

    memcpy(cp, pBig->str, sizeof(char) * (pBig->id + 1));

    BigObj *cpp = (BigObj *)malloc(sizeof(BigObj));

    memcpy(cpp, pBig, sizeof(BigObj));

    cpp->id = pBig->id;
    cpp->str = cp;

    return cpp;
}

void freeBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    free(pBig->str);
    free(pBig);
}

uint64_t hashBig(void *big, int size)
{
    BigObj *pBig = (BigObj *)big;

    char *str = pBig->str;
    int id = pBig->id;

    uint64_t hashStr = hash(str, sizeof(char)*2);
    uint64_t hashId = hash(&id, sizeof(int));

    return hashStr ^ hashId;
}

bool equalsBig(void *big1, void *big2, int size)
{
    BigObj *pBig1 = (BigObj *)big1;
    BigObj *pBig2 = (BigObj *)big2;

    char *str1 = pBig1->str;
    int id1 = pBig1->id;
    char *str2 = pBig2->str;
    int id2 = pBig2->id;

    return equals(str1, str2, sizeof(char)*2) && equals(&id1, &id2, sizeof(int));
}
